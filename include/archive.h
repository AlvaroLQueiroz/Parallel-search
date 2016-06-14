#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#include <stdio.h>

/*
Copies all content from de input file to memory RAM.
file_name: name of the input file
content: store the content
*/
short getContent(char file_name[], char **content);

/*
Stores the result (positions where the target was found) in a file.
positions: positions where the target was found (result)
amount: amount of times the target was found
startIndex: displacement for calculation of the real position where the target was found in the input file.
*/
short savePositions(int *positions, int amount, int startIndex);

#endif
