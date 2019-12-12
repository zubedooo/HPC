#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[])
{
int i, n =10, a[10], sum;

for (i=0; i < n; i++)
a[i] = rand()%100;
sum = 0;

for (i=0; i < n; i++)
printf(" %d ", a[i]);

#pragma omp parallel for reduction(+:sum)
for (i=0; i < n; i++)
sum = sum + a[i];
printf("\n Sum = %d\n",sum);

}
