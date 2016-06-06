#include "splitting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned splitNumbers(char *content, int amountPcs, int *amountForFirst, int *amountPerPC, int ***numbers){
  unsigned amountNumbers;
  char *pointer;
  char *string;
  int counter;
  int pc;

  amountNumbers = 0;
  counter = 0;
  pc = 0;
  pointer = NULL;
  string = NULL;

  // Count amount of numbers
  string = content;
  pointer = strpbrk(string, "\n");
  while(pointer != NULL){
    amountNumbers++;
    pointer = strpbrk(pointer + 1, "\n");
  }

  *amountForFirst = (amountNumbers / amountPcs) + (amountNumbers % amountPcs);
  *amountPerPC = amountNumbers / amountPcs;

  // Allocates a vector length equal amount of PC
  *numbers = (int**) calloc(amountPcs, sizeof(int*));
  if(*numbers == NULL) return 0;

  // Allocates an vector for the first pc
  (*numbers)[0] = NULL;
  (*numbers)[0] = (int*) calloc(*amountForFirst, sizeof(int));
  if((*numbers)[0] == NULL) return 0;

  // Allocates a vector for each of the other PC
  for(counter = 1; counter < amountPcs; counter++){
    (*numbers)[counter] = NULL;
    (*numbers)[counter] = (int*) calloc(*amountPerPC, sizeof(int));
    if((*numbers)[counter] == NULL) return 0;
  }

  string = content;
  pointer = strtok(string, "\n");

  // Copy the numbers for first PC
  while(pointer != NULL && counter < *amountForFirst){
    (*numbers)[0][counter] = atoi(pointer);
    pointer = strtok(NULL, "\n");
    counter++;
  }

  // Copy the number for each of the others PC
  for(pc = 1; pc < amountPcs; pc++){
    counter = 0;
    while(pointer != NULL && counter < *amountPerPC){
      (*numbers)[pc][counter] = atoi(pointer);
      pointer = strtok(NULL, "\n");
      counter++;
    }
  }

  pointer = NULL;
  string = NULL;

  return amountNumbers;
}
