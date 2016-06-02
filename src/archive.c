#include "archive.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findTarget(int target, pc *computer){
  FILE *file;
  int num;

  file = NULL;
  num = 0;

  file = fopen(computer->file_name, "r");
  if(!file) return 0;

  while(fscanf(file, " %d\n", &num) != EOF){
    computer->amountNumbers++;
    if(num == target){
      computer->amountFound++;
      computer->founds = (int*) realloc(computer->founds, computer->amountFound * sizeof(int));
      computer->founds[computer->amountFound - 1] = computer->amountNumbers;
    }
  }

  fclose(file);
  return 1;
}
