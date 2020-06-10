#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int AllToAllBCRing(int *sendData, int sendCount, MPI_Datatype sendDatatype, int* recvData, int recvCount, MPI_Datatype recvDatatype, MPI_Comm comm){
	int rk,np;
	MPI_Comm_rank(comm,&rk);
	MPI_Comm_size(comm, &np);
	
	int left = (rk-1)%np;
	int right = (rk+1)%np;
	if(left < 0 ) left = np-1;
	int rp = 0;
	*(recvData+(rp++)) = *sendData;
	int msg = *sendData;

	for(int i=1;i<np; i++){
		MPI_Send(&msg,sendCount,sendDatatype,right,0,comm);
		MPI_Recv(&msg,recvCount,recvDatatype,left,0,comm,MPI_STATUS_IGNORE);
		*(recvData+(rp++)) = msg;
	}

	return 0;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank; // Rank of process
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int np; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int data = rank;
	int recv[np];
	AllToAllBCRing(&data, 1, MPI_INT, recv, 1, MPI_INT, MPI_COMM_WORLD);

	printf("P%d value is: ",rank);
	for(int i=0; i<np; i++){
		printf("%d, ",recv[i]);
	}
	printf("\n");

	MPI_Finalize();

	return 0;
}
