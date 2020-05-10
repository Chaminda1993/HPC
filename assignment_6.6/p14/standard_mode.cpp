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
		MPI_Send(&a, 1, MPI_INT, 1, 100, MPI_COMM_WORLD);
		MPI_Recv(&b, 1, MPI_INT, 1, 200, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d send: %d and received: %d\n",myrank,a,b);
	}

	else if (myrank == 1) {
		int a = 20;
		int b;
		MPI_Send(&a, 1, MPI_INT, 0, 200, MPI_COMM_WORLD);
		MPI_Recv(&b, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d send: %d and received: %d\n",myrank,a,b);
	}

	MPI_Finalize();
}


// In this case MPI_Send is work as buffered blocking message. Therefore this is not a deadlock for this. Because each processors first send their data to buffer and get the received data
