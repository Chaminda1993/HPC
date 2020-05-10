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
		int b;
		MPI_Ssend(&a, 1, MPI_INT, 1, 100, MPI_COMM_WORLD);
		MPI_Recv(&b, 1, MPI_INT, 1, 200, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d send: %d and received: %d\n",myrank,a,b);
	}

	else if (myrank == 1) {
		int a = 20;
		int b;
		MPI_Ssend(&a, 1, MPI_INT, 0, 200, MPI_COMM_WORLD);
		MPI_Recv(&b, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d send: %d and received: %d\n",myrank,a,b);
	}

	MPI_Finalize();
}


// In this case deadlock happen. Because in synchronous mode work as non-buffered then both processors send first data and waiting for it send successful. Therefore any processor not not execute second line and received data.
