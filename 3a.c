#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
#define MAXIMUM 65536

/* Main Program */

main()
{
int *array, i, Noofelements, cur_max, current_value;

printf("Enter the number of elements\n");
scanf("%d", &Noofelements);

if (Noofelements <= 0) {
printf("The array elements cannot be stored\n");
exit(1);
}
/* Dynamic Memory Allocation */

array = (int *) malloc(sizeof(int) * Noofelements);

*array, i, Noofelements, cur_max, current_value;
/* Allocating Random Number Values To The Elements Of An Array */

srand(MAXIMUM);
for (i = 0; i < Noofelements; i++)
array[i] = rand();

if (Noofelements == 1) {
printf("The Largest Number In The Array is %d", array[0]);
exit(1);
}
/* OpenMP Parallel For Directive And Critical Section */

cur_max = 0;
omp_set_num_threads(8);
#pragma omp parallel for
for (i = 0; i < Noofelements; i = i + 1) {
if (array[i] > cur_max)
#pragma omp critical
if (array[i] > cur_max)
cur_max = array[i];
}

/* Serial Calculation */

current_value = array[0];
for (i = 1; i < Noofelements; i++)
if (array[i] > current_value)
current_value = array[i];

printf("The Input Array Elements Are \n");

for (i = 0; i < Noofelements; i++)
printf("\t%d", array[i]);

printf("\n");

/* Checking For Output Validity */

if (current_value == cur_max)
printf("\nThe Max Value Is Same From Serial And Parallel OpenMP Directive\n");
else {
printf("\nThe Max Value Is Not Same In Serial And Parallel OpenMP Directive\n");
exit(1);
}

/* Freeing Allocated Memory */

printf("\n");
free(array);
printf("\nThe Largest Number In The Given Array Is %d\n", cur_max);

}
