#include <mpi.h> 
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		int a = 10;
		int b = 20;
		MPI_Send(&a, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		printf("Process %d send: %d\n",myrank,a);
		MPI_Send(&b, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
		printf("Process %d send: %d\n",myrank,b);
	}

	else if (myrank == 1) {
		int a;
		int b;
		MPI_Recv(&b, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d received: %d\n",myrank,b);
		MPI_Recv(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d received: %d\n",myrank,a);
	}

	MPI_Finalize();
}


// In this case also deadlock not happen. Because P0 send first value to buffer and send second value then P1 read second value first and after it read first value from buffer. Therefore it work fine in buffered send.
