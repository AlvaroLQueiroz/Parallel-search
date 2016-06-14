#include "archive.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short getContent(char file_name[], char **content){
  unsigned size;
  FILE *file;

  file = NULL;

  file = fopen(file_name, "r");
  if(!file) return 0;

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);
  *content = (char*) calloc(sizeof(char), size);
  if(!*content) return 0;

  fread(*content, sizeof(char), size, file);

  fclose(file);

  return 1;
}

short savePositions(int *positions, int amount, int startIndex){
  int counter;
  FILE *file;

  file = NULL;
  file = fopen("result.data", "a");
  if(!file) return 0;

  for(counter = 0; counter < amount; counter++){
    fprintf(file, "%d\n", startIndex + positions[counter]);
  }

  fclose(file);

  return 1;
}
