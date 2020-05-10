#include <mpi.h> 
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		int vals[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};

		MPI_Send(vals+3, 5, MPI_INT, 1, 2, MPI_COMM_WORLD);
	}

	else if (myrank == 1) {
		int recVals[5];

		MPI_Recv(recVals, 5, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int sum = 0;
		for(int i = 0; i< 5;i++){
			sum += recVals[i];
		}
		float avg = sum/5.0;
		printf("Average value is: %f.\n",avg);
	}

	MPI_Finalize();
}
