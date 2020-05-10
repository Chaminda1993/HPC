#include <mpi.h> 
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	int n; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &n);

	if (myrank == 0) {
		//Collect and calculate
		int factorial=1;
		int cur_recv;
		for(int i=0;i<n-1;i++){
			MPI_Recv(&cur_recv, 1,MPI_INT, MPI_ANY_SOURCE, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			factorial *= cur_recv;
		}

		printf("Factorial %d is %d.\n",n-1,factorial);
	}else {
		// Send data
		MPI_Send(&myrank, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
