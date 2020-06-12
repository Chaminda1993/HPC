#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int calculatePortion(int num,int rank,int np){
	int countPerProcess = floor(num/(float)np);
	int bias = num - (countPerProcess*np);
	int start,end;
	if(rank < bias){
		start = ((countPerProcess+1)*rank)+1;
		end = start + countPerProcess;
	}else{
		start = ((countPerProcess+1)*bias)+(countPerProcess*(rank-bias))+1;
		end = start + (countPerProcess-1);
	}

	printf("P%d, start:%d, end:%d, count:%d\n",rank,start,end,end-start+1);
	if(rank == 0) printf("Ceil for first %d values. others floor value.\n",bias);

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
