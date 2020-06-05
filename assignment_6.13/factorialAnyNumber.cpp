#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int calculatePortion(int num,int rank,int np){
	int countPerProcess = ceil(num/np);
	int start = (countPerProcess * rank) + 1;
	int end = countPerProcess * (rank + 1);
	if (rank == np-1) end = num;

	int val = 1;
	for(int i=start; i<=end; i++){
		val *= i;
	}
	return val;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	int np; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int num = atoi(argv[1]);
	
	// Calculate part of each processor
	int ret = calculatePortion(num,myrank,np);
	
	int factorial;
	MPI_Reduce(&ret,&factorial,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);

	if(myrank ==0){
		printf("Factorial value is %d.\n",factorial);
	}

	MPI_Finalize();

	return 0;
}
