#include<stdio.h>
#include<stdlib.h>
#include <omp.h>

long long fac(int n)
{
long out =1 ;
for(int i =1  ; i< n+1 ; i++) out *= i;
return out;
}

int main(int argc,char *argv[])
{
omp_set_dynamic(0);
omp_set_num_threads(4);
long long *x;
long long n = 9;

x = (long long *) malloc(sizeof(long) * n);

for(int i = 0 ; i <n ; i++)
x[i] = fac(i);

int j =0;
#pragma omp parallel for firstprivate(j,x)
 for (int i =0; i<n ; i++)
{
j =j +1;
x[i] = j * x[i-1];
}

for(int i = 0 ; i <n ; i++)
printf("fac(%d) = %lld \n",i,fac(i));
printf("*********** \n");
for(int i = 0 ; i <n+1 ; i++)
printf("x[%d] = %lld  \n",i,x[i]);
}
