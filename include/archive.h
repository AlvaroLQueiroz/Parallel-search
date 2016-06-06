#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#include "structures.h"
#include <stdio.h>

short getContent(char file_name[], char **content);
short savePositions(int *positions, int amount, int startIndex);

#endif
