#include "structures.h"
#include "archive.h"
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
  pc *computer;
  pc *computers;
  int amountPcs;
  int target;
  int rank;
  int counter;
  int c;

  computer = NULL;
  computers = NULL;
  amountPcs = 0;
  target = 0;
  rank = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &amountPcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  computer = (pc*) calloc(sizeof(pc), 1);
  if(computer){
    computer->rank = rank;
    memset(computer->file_name, 0, 10);
    snprintf(computer->file_name, 10, "PC%02d", rank);
    computer->amountNumbers = 0;
    computer->amountFound = 0;
    computer->founds = NULL;
  }else{
    goto ERROR;
  }

  target = atoi(argv[2]);

  if(rank == 0){
    computers = (pc*) calloc(sizeof(pc), amountPcs);
    if(!computers) goto ERROR;

    if(findTarget(target, computer)){
      computers[0].rank = computer->rank;
      computers[0].amountNumbers = computer->amountNumbers;
      computers[0].amountFound = computer->amountFound;
      strncpy(computers[0].file_name, computer->file_name, sizeof(computer->file_name));
      computers[0].founds = calloc(sizeof(int), computer->amountFound);
      if(!computers[0].founds) goto ERROR;
      memcpy(computers[0].founds, computer->founds, sizeof(int) * computer->amountFound);
      for(counter = 1; counter < amountPcs; counter++){
        MPI_Recv(
          &computers[counter].rank,
          sizeof(computers[counter].rank),
          MPI_INT,
          counter,
          0,
          MPI_COMM_WORLD,
          MPI_STATUS_IGNORE);
        MPI_Recv(
          computers[counter].file_name,
          sizeof(computers[counter].file_name),
          MPI_CHAR,
          counter,
          0,
          MPI_COMM_WORLD,
          MPI_STATUS_IGNORE);
        MPI_Recv(
          &computers[counter].amountNumbers,
          sizeof(computers[counter].amountNumbers),
          MPI_INT,
          counter,
          0,
          MPI_COMM_WORLD,
          MPI_STATUS_IGNORE);
        MPI_Recv(
          &computers[counter].amountFound,
          sizeof(computers[counter].amountFound),
          MPI_INT,
          counter,
          0,
          MPI_COMM_WORLD,
          MPI_STATUS_IGNORE);

        computers[counter].founds = (int*) calloc(sizeof(int), computers[counter].amountFound);
        if(!computers[counter].founds) goto ERROR;
        MPI_Recv(
          computers[counter].founds,
          sizeof(int) * computers[counter].amountFound,
          MPI_INT,
          counter,
          0,
          MPI_COMM_WORLD,
          MPI_STATUS_IGNORE);
      }
      for(counter = 0; counter < amountPcs; counter++){
        printf("Rank %d, name %s, numbers %d, amount %d\n",
          computers[counter].rank,
          computers[counter].file_name,
          computers[counter].amountNumbers,
          computers[counter].amountFound);
        for(c = 0; c < computers[counter].amountFound; c++){
          printf("%d, ", computers[counter].founds[c]);
        }
        printf("\n");
      }
    }else{
      goto ERROR;
    }
  }else{
    if(findTarget(target, computer)){
      MPI_Send(
        &computer->rank,
        sizeof(computer->rank),
        MPI_INT, 0, 0, MPI_COMM_WORLD);
      MPI_Send(
        computer->file_name,
        sizeof(computer->file_name),
        MPI_CHAR, 0, 0, MPI_COMM_WORLD);
      MPI_Send(
        &computer->amountNumbers,
        sizeof(computer->amountNumbers),
        MPI_INT, 0, 0, MPI_COMM_WORLD);
      MPI_Send(
        &computer->amountFound,
        sizeof(computer->amountFound),
        MPI_INT, 0, 0, MPI_COMM_WORLD);
      MPI_Send(
        computer->founds,
        sizeof(int) * computer->amountFound,
        MPI_INT, 0, 0, MPI_COMM_WORLD);
    }else{
      goto ERROR;
    }
  }

  goto SUCCESS;

  ERROR:
    printf("Deu ruim!!!\n");
    if(computer) free(computer);
    if(computers) free(computers);
    MPI_Finalize();
    exit(EXIT_FAILURE);

  SUCCESS:
    if(computer) free(computer);
    if(computers) free(computers);

    MPI_Finalize();

  return 0;
}
