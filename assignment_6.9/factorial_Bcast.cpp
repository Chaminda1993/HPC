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

	int num;
	if (myrank == 0) {
		cout << "Enter number for factorial: ";
		cin >> num;	
	}

	// Broadcast value to all
	MPI_Bcast(&num,1,MPI_INT,0,MPI_COMM_WORLD);
	
	int factorial,ret=1;
	if(myrank <= num and myrank != 0){
		ret = myrank;
	}
	MPI_Reduce(&ret,&factorial,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);

	if(myrank ==0){
		printf("Factorial value is %d.\n",factorial);
	}

	MPI_Finalize();

	return 0;
}
