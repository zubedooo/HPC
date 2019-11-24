#include   <stdio.h>
#include <stdlib.h>
#include <string.h>
#include   <mpi.h>

  void main(int argc, char *argv[])
  {
	int rank,size;
	char param[10][10];
	char mine[10];
	char srank[10];
	int sndcnt,rcvcnt;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	sndcnt=10;
	strcpy(mine,"Hello ");
	//srank = itoa(rank,srank,10);
	sprintf(srank, "%d", rank);
	strcat(mine,srank);

	if(rank==0) rcvcnt=10;

	MPI_Gather(&mine,sndcnt,MPI_CHAR,param,rcvcnt,MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank==0)
    	for(i=0;i<size;++i)
     	{
     	printf("PE:%d param[%d] is %s \n",rank,i,param[i]);
     	printf(" %d %d  \n",rank,i);
    	}
	MPI_Finalize();
}
