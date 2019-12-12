#include <stdio.h>
#include <omp.h>

int main(void)
{
int i;
omp_set_num_threads(4);
#pragma omp parallel private(i)
{ 
// OMP_NUM_THREADS is not a multiple of 26, which can be considered a bug in this code.
// LettersPerThread  = lpt
int lpt = 26 / omp_get_num_threads();
int tid = omp_get_thread_num();
//printf("Thread No: %d \n ", tid );

int StartLetter = 'a'+tid*lpt;
int EndLetter = 'a'+tid*lpt+lpt;
for (i=StartLetter; i<EndLetter; i++)
printf("%c", i);
}
printf("\n");
return 0;
}
