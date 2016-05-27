#include "archive.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculatesAmountNumbers(FILE *file){
  int amount;
  int num;

  amount = 0;
  num = 0;

  fseek(file, 0, SEEK_SET);

  while(fscanf(file, " %d\n", &num) != EOF){
    amount++;
  }

  return amount;
}

int splitNumbersInFiles(FILE *file, int amountPcs, pc *computers){
  FILE *new;
  int position;
  int counter;
  int num;

  position = 0;
  num = 0;

  fseek(file, 0, SEEK_SET);

  for(position = 0; position < amountPcs; position++){
    new = NULL;
    counter = 0;
    memset(computers[position].file_name, 0, 10);
    snprintf(computers[position].file_name, 10, "PC%02d.data", position);
    new = fopen(computers[position].file_name, "w");
    if(new == NULL) goto ERROR;

    for(counter = 0; counter < computers[position].amount; counter++){
      fscanf(file, " %d\n", &num);
      fprintf(new, "%d\n", num);
    }

    fclose(new);
  }

  return 1;

  ERROR:
    return 0;
}
