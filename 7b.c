#include<stdio.h>
#include<mpi.h>
  
  void main(int argc, char *argv[])
  {
	int rank,size;
	double param[6],mine;
	int sndcnt,rcvcnt;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	sndcnt=1;
	mine=23.0+rank;
	if(rank==0) rcvcnt=1;

	MPI_Gather(&mine,sndcnt,MPI_DOUBLE,param,rcvcnt,MPI_DOUBLE,0,MPI_COMM_WORLD);

	if(rank==0)
		for(i=0;i<size;++i) 
		 {
		 printf("PE:%d param[%d] is %f \n",rank,i,param[i]); 
		 printf(" %d %d  \n",rank,i); 
		}
	MPI_Finalize();
}
