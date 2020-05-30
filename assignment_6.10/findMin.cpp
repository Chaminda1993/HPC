#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	int np; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int n = 4, p = 5;
	if(np != p and myrank == 0 ) printf("Program need %d processors.\n",p);
	if(np != p ) return 1;
	int A[n][p];

	if (myrank == 0) {
		int N[n][p] = {{4,6,3,7,5},
				{2,5,6,1,7},
				{6,2,6,8,9},
				{3,1,0,4,4}};
		for(int i=0;i<n;i++){
			for(int j=0;j<p;j++){
				A[i][j] = N[i][j];
			}
		}
	}
	// Broadcast matrix A
	MPI_Bcast(A,n*p,MPI_INT,0,MPI_COMM_WORLD);
	
	// Find minimum value per column
	int colMin = A[0][myrank];
	for(int i=1;i<n;i++){
		if(A[i][myrank]<colMin){
			colMin = A[i][myrank];
		}
	}
	printf("Local min of column %d is %d.\n",myrank,colMin);

	// Collect values from processors
	int globalMin;
	MPI_Reduce(&colMin,&globalMin,1,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);

	if(myrank ==0){
		printf("Global minimum value is %d.\n",globalMin);
	}

	MPI_Finalize();

	return 0;
}
