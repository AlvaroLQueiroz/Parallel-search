#include "search.h"
#include <stdlib.h>

short searchNumber(int *numbers, int amountPerPC, int target, int **founds, int *amountFound){
  int counter;

  for(counter = 0; counter < amountPerPC; counter++){
    if(numbers[counter] == target){
      (*amountFound)++;
      *founds = (int*) realloc(*founds, (*amountFound) * sizeof(int));
      if(*founds == NULL) return 0;
      (*founds)[(*amountFound) - 1] = counter;
    }
  }

  return 1;
}
