#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int AllToAllReduceRing(int *sendData, int *result, int sendCount, MPI_Datatype sendDatatype, MPI_Comm comm){
	int rk,np;
	MPI_Comm_rank(comm,&rk);
	MPI_Comm_size(comm, &np);
	
	int left = (rk-1)%np;
	int right = (rk+1)%np;
	if(left < 0 ) left = np-1;
	int recv = 0, j;

	for(int i=1;i<np; i++){
		j = (rk+i)%np;
		if(j < 0 ) j = np-1;
		int tmp = *(sendData+i) + recv;
		MPI_Send(&tmp,sendCount,sendDatatype,left,0,comm);
		MPI_Recv(&recv,sendCount,sendDatatype,right,0,comm,MPI_STATUS_IGNORE);
	}
	*result = *(sendData+rk)+recv;

	return 0;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank; // Rank of process
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int np; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int data[np];
	for(int i=0; i< np;i++) data[i] = i;
	int recv;
	AllToAllReduceRing(data,&recv, 1, MPI_INT, MPI_COMM_WORLD);

	printf("P%d value is:%d\n",rank,recv);

	MPI_Finalize();

	return 0;
}
