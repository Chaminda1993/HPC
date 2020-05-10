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

		MPI_Send(vals, 15, MPI_INT, 1, 1, MPI_COMM_WORLD);
	}

	else if (myrank == 1) {
		int recVals[15];

		MPI_Recv(recVals, 15, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int sml_val = recVals[0];
		for(int i = 1; i< 15;i++){
			if(sml_val > recVals[i]){
				sml_val = recVals[i];
			}
		}
		printf("Smallest value is: %d.\n",sml_val);
	}

	MPI_Finalize();
}
