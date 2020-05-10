#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

float calc(int N, int n, int rank){
	// Calculate range based on rank
	int size = N/n;
	int start = ((size*rank)+1);
	int end = (size*(rank+1));
	printf("P%d calculate from %d to %d.\n",rank,start,end);
	
	// Calculate particular summation
	float sum = 0.0;
	for(int i=start;i<=end;i++){
		sum += (1/(1+(pow(((i-0.5)/N),2))));
	}
	return sum;
}
	
int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	int n; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &n);

	int N = 840;

	if (myrank == 0) {
		// Calculate local portion
		float sum = calc(N,n,myrank);

		// Get others portions
		float curRecv;
		for( int i =0; i< n-1;i++){
			MPI_Recv(&curRecv, 1,MPI_FLOAT, MPI_ANY_SOURCE, 100, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += curRecv;
		}
		
		// Calculate pi value
		float pi = (sum/N)*4;

		printf("Approximate value of 'PI' is %f.\n",pi);
	}else {
		// Calculate local portion
		float sum = calc(N,n,myrank);
		MPI_Send(&sum, 1, MPI_FLOAT, 0, 100, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
