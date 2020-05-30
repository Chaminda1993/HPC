#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

void myBcast(void *data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator){
	int worldRank;
	MPI_Comm_rank(communicator,&worldRank);
	int worldSize;
	MPI_Comm_size(communicator,&worldSize);
	
	// d is the count of bits
	int d = 3;

	// Algorithm
	int myVirtualID = worldRank ^ root;
	int mask = pow(2,d)-1;
	for(int i = d-1; i>=0; i--){
		mask = mask ^ int(pow(2,i));
		if((myVirtualID & mask) == 0 ){
			if((myVirtualID & int(pow(2,i))) == 0 ){
				int virtualDest = myVirtualID ^ int(pow(2,i));
				MPI_Send(&data, count, datatype, (virtualDest ^ root), 100, communicator);
			}else{
				int virtualSource = myVirtualID ^ int(pow(2,i));
				MPI_Recv(&data, count, datatype, (virtualSource ^ root), 100, communicator, MPI_STATUS_IGNORE);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	int n; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &n);

	int data;
	if (myrank == 0) data = 44;

	myBcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);

	if(myrank == 0){
		printf("Process %d sent %d.\n",myrank,data);
	}else{
		printf("Process %d received %d.\n",myrank,data);
	}

	MPI_Finalize();
	return 0;
}
