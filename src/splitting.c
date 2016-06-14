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

  /* count amount of numbers reads from input file */
  string = content;
  pointer = strpbrk(string, "\n");
  while(pointer != NULL){
    amountNumbers++;
    pointer = strpbrk(pointer + 1, "\n");
  }

  *amountForFirst = (amountNumbers / amountPcs) + (amountNumbers % amountPcs);
  *amountPerPC = amountNumbers / amountPcs;

  /* Allocates an matrix with a number of lines equal to the number of nodes in the cluster */
  *numbers = (int**) calloc(amountPcs, sizeof(int*));
  if(*numbers == NULL) return 0;

  /* Allocates an array for the numbers of the first PC */
  (*numbers)[0] = NULL;
  (*numbers)[0] = (int*) calloc(*amountForFirst, sizeof(int));
  if((*numbers)[0] == NULL) return 0;

  /* Allocates an array for each of the others PC's */
  for(counter = 1; counter < amountPcs; counter++){
    (*numbers)[counter] = NULL;
    (*numbers)[counter] = (int*) calloc(*amountPerPC, sizeof(int));
    if((*numbers)[counter] == NULL) return 0;
  }

  string = content;
  pointer = strtok(string, "\n");

  /* Copy the numbers for first PC */
  while(pointer != NULL && counter <= *amountForFirst){
    (*numbers)[0][counter] = atoi(pointer);
    pointer = strtok(NULL, "\n");
    counter++;
  }

  /* Copy the number for each of the others PC */
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
