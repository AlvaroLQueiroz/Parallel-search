#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <stdio.h>

/*
Search for a target in the array numbers.
numbers: array of numbers
amountNumber: Amount of numbers in array "numbers"
target: number to find
founds: array to store the locations where the number was found (Result)
amountFound: number of times than target was found
*/
short searchNumber(int *numbers, int amountNumbers, int target, int **founds, int *amountFound);

#endif
