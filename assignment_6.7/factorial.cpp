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
		//Send values to processes
		int init_value = 1;
		MPI_Send(&init_value, 1, MPI_INT, myrank+1, myrank+1, MPI_COMM_WORLD);

		//Collect data
		int factorial;
		MPI_Recv(&factorial, 1,MPI_INT, n-1, n, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("Factorial %d is %d.\n",n,factorial);
	}

	else {
		// Get previous data
		int prev;
		MPI_Recv(&prev, 1, MPI_INT, myrank-1, myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		int nxt = prev * (myrank+1);

		// Send data to next
		if(n-1 == myrank){
			MPI_Send(&nxt, 1, MPI_INT, 0, myrank+1, MPI_COMM_WORLD);
		}else{
			MPI_Send(&nxt, 1, MPI_INT, myrank+1, myrank+1, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
}
