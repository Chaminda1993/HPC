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
		MPI_Recv(&b, 1, MPI_INT, 1, 200, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Send(&a, 1, MPI_INT, 1, 100, MPI_COMM_WORLD);
		printf("Process %d send: %d and received: %d\n",myrank,a,b);
	}

	else if (myrank == 1) {
		int a = 20;
		int b;
		MPI_Recv(&b, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Send(&a, 1, MPI_INT, 0, 200, MPI_COMM_WORLD);
		printf("Process %d send: %d and received: %d\n",myrank,a,b);
	}

	MPI_Finalize();
}


// In this case both processors wait for received data. Therefore both are unable to send their data. Then deadlock happen here.
