#include <stdio.h>
#include <omp.h>
#include<stdlib.h>

#define MINUS_INFINITY -9999
#define MAXIMUM_VALUE 65535

/* Main Program */

main()
{
int *array, i, Noofelements, cur_max, current_value;
omp_lock_t MAXLOCK;

printf("Enter the number of elements\n");
scanf("%d", &Noofelements);

if (Noofelements <= 0) {
printf("The array elements cannot be stored\n");
exit(1);
}
/* Dynamic Memory Allocation */
array = (int *) malloc(sizeof(int) * Noofelements);

/* Allocating Random Number To Array Elements */

srand(MAXIMUM_VALUE);
for (i = 0; i < Noofelements; i++)
array[i] = rand();

if (Noofelements == 1) {
printf("The Largest Element In The Array Is %d", array[0]);
exit(1);
}
/* Initializing The Lock */

printf("The locking is going to start\n");

omp_set_num_threads(8);
omp_init_lock(&MAXLOCK);
cur_max = MINUS_INFINITY;
printf("the lock s initialized\n");
/* OpenMP Parallel For Directive And Lock Functions */

#pragma omp parallel for
for (i = 0; i < Noofelements; i = i + 1) {
if (array[i] > cur_max) {
omp_set_lock(&MAXLOCK);
if (array[i] > cur_max)
cur_max = array[i];
omp_unset_lock(&MAXLOCK);
}
}

/* Destroying The Lock */

omp_destroy_lock(&MAXLOCK);

/* Serial Calculation */
current_value = array[0];
for (i = 1; i < Noofelements; i++)
if (array[i] > current_value)
current_value = array[i];

printf("The Array Elements Are \n");

for (i = 0; i < Noofelements; i++)
printf("\t%d", array[i]);

/* Checking For Output Validity */

if (current_value == cur_max)
printf("\nThe Max Value Is Same For Serial And Using Parallel OpenMP Directive\n");
else {
printf("\nThe Max Value Is Not Same In Serial And Using Parallel OpenMP Directive\n");
exit(1);
}

/* Freeing Allocated Memory */

free(array);

printf("\nThe Largest Number Of The Array Is %d\n", cur_max);
}
