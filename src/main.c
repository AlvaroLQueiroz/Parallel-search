#include "archive.h"
#include "splitting.h"
#include "search.h"
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
  int amountForFirst;
  int amountFound;
  unsigned amountNumbers;
  int amountPcs;
  int amountPerPC;
  int counter;
  int rank;
  int target;
  int totalFound;

  char *content;
  int *founds;
  int **numbers;
  int *slaveNumbers;
  MPI_Status status;

  if(argc != 3) goto ERROR;

  MPI_Init(&argc, &argv);
    amountForFirst = 0;
    amountFound = 0;
    amountNumbers = 0;
    amountPcs = 0;
    amountPerPC = 0;
    counter = 0;
    rank = 0;
    target = 0;
    totalFound = 0;

    content = NULL;
    founds = NULL;
    numbers = NULL;
    slaveNumbers = NULL;
    memset(&status, 0, sizeof(MPI_Status));


    MPI_Comm_size(MPI_COMM_WORLD, &amountPcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    target = atoi(argv[2]);

    if(rank == 0){
      if(getContent(argv[1], &content)){
        amountNumbers = splitNumbers(content, amountPcs, &amountForFirst, &amountPerPC, &numbers);
        if(amountNumbers){
          for(counter = 1; counter < amountPcs; counter++){
            MPI_Send(&amountPerPC, 1, MPI_INT, counter, 0, MPI_COMM_WORLD);
            MPI_Send(numbers[counter], amountPerPC, MPI_INT, counter, 0, MPI_COMM_WORLD);
          }

          // Search and save in rank 0
          if(searchNumber(numbers[0], amountForFirst, target, &founds, &amountFound)){
            if(!savePositions(founds, amountFound, 0)) goto ERROR;
            printf("Rank %d found %d\n", rank, amountFound);
          }else{
            goto ERROR;
          }
          totalFound += amountFound;

          // Receive founds in other ranks and save.
          for(counter = 1; counter < amountPcs; counter++){
            amountFound = 0;
            free(founds);
            MPI_Recv(&amountFound, 1, MPI_INT, counter, 0, MPI_COMM_WORLD, &status);
            totalFound += amountFound;
            founds = (int*) calloc(amountFound, sizeof(int));
            if(!founds) goto ERROR;
            MPI_Recv(founds, amountFound, MPI_INT, counter, 0, MPI_COMM_WORLD, &status);
            if(!savePositions(founds, amountFound, amountForFirst + (counter * amountPerPC))) goto ERROR;
            printf("Rank %d found %d\n", status.MPI_SOURCE, amountFound);
          }
          printf("Total found: %d\n", totalFound);
        }else{
          goto ERROR;
        }
      }else{
        goto ERROR;
      }
    }else{
      MPI_Recv(&amountPerPC, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      slaveNumbers = (int*) calloc(amountPerPC, sizeof(int));
      if(!slaveNumbers) goto ERROR;
      MPI_Recv(slaveNumbers, amountPerPC, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      if(searchNumber(slaveNumbers, amountPerPC, target, &founds, &amountFound)){
        MPI_Send(&amountFound, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(slaveNumbers, amountFound, MPI_INT, 0, 0, MPI_COMM_WORLD);
      }else{
        goto ERROR;
      }
    }


    goto END;

    ERROR:
      printf("%d - Deu ruim!!!\n", rank);

    END:
      if(content) free(content);
      if(founds) free(founds);
      if(slaveNumbers) free(slaveNumbers);
      memset(&status, 0, sizeof(MPI_Status));
      for(counter = 0; counter < amountPcs; counter++){
        if(numbers){
          if(numbers[counter]) free(numbers[counter]);
        }
      }
      if(numbers) free(numbers);
  MPI_Finalize();

  return 0;
}

// 1668
