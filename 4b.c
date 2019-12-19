#include <mpi.h>
#include<stdio.h>
#include<math.h>

double func(double x)
{
	return (4.0 / (1.0 + x*x));
}

int main(int argc,char *argv[])
{
	int	n,i,rank,size;
	double mypi, pi, h, sum, x;
	double PI25DT = 3.141592653589793238462643;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank == 0){
	printf("\nEnter the number of intervals : ");
	scanf("%d",&n);
	}
    	 
   MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);


   h   = 1.0 / (double)n;
   sum = 0.0;
   for(i = rank + 1; i <= n; i +=size){
   	x = h * ((double)i - 0.5);
   	sum += func(x);
   }
   mypi = h * sum;

   
   MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

   if(rank == 0){
  	printf("pi is approximately %.16f, Error is %.16f\n",
pi, fabs(pi - PI25DT));
   }

   MPI_Finalize();
}
