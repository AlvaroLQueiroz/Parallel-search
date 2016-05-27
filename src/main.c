#include "structures.h"
#include "archive.h"
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  FILE *file;
  pc *computers;
  int *numbers;
  int amountPcs;
  int amountNumbers;
  int amountPerPc;
  int rank;
  int counter;

  file = NULL;
  computers = NULL;
  numbers = NULL;
  amountPcs = 0;
  amountNumbers = 0;
  amountPerPc = 0;
  rank = 0;
  counter = 0;

  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &amountPcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  computers = (pc*) calloc(sizeof(pc), amountPcs);

  file = fopen("entrada.data", "r");
  if(file == NULL){
    printf("File not found.");
    goto ERROR;
  }

  if(rank == 0){
    amountNumbers = calculatesAmountNumbers(file);
    amountPerPc = amountNumbers / amountPcs;
    for(counter = 0;counter < amountPcs;counter++){
      computers[counter].initial = counter * amountPerPc;
      computers[counter].amount = amountPerPc;
    }
    computers[amountPcs - 1].amount += amountNumbers % amountPcs;
    if(splitNumbersInFiles(file, amountPcs, computers) == 0) goto ERROR;

    for(counter=1; counter<amountPcs; counter++){
      MPI_Send(computers, sizeof(pc) * amountPcs, MPI_BYTE, counter, 0, MPI_COMM_WORLD);
    }
  }else if(rank == 1){
    MPI_Recv(computers, sizeof(pc) * amountPcs, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    numbers = (int*) calloc(sizeof(int), computers[rank].amount);
  }

  goto SUCCESS;

  ERROR:
    if(file) fclose(file);
    if(computers) free(computers);
    if(numbers) free(numbers);
    MPI_Finalize();
    exit(EXIT_FAILURE);

  SUCCESS:
    if(file) fclose(file);
    if(computers) free(computers);
    if(numbers) free(numbers);
    MPI_Finalize();

  return 0;
}
