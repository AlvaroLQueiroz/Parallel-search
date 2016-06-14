#ifndef _SPLITTING_H_
#define _SPLITTING_H_

#include <stdio.h>

/*
Divides the array of numbers in subarrays with same quantity of elements for each node,
except for the first, because this receive spare elements if the division is not exact.
content: information read from input file
amountPcs: amount of nodes in the cluster
amountForFirst: stores the amount of elements for first node
amountPerPC: stores the amount of elements for the other nodes
numbers: stores the numbers already divided for the each node in a matrix
*/
unsigned splitNumbers(char *content, int amountPcs, int *amountForFirst, int *amountPerPC, int ***numbers);

#endif
