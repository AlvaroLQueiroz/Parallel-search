#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#include "structures.h"
#include <stdio.h>

#define LINE_LENGTH 256

int calculatesAmountNumbers(FILE *file);

int splitNumbersInFiles(FILE *file, int amountPcs, pc *computers);

#endif
