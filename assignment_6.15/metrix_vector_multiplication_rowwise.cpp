#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int rowMatrixVectorMultiply(int n,double *a, double *b, double *x, MPI_Comm comm){
	int i,j;
	int nlocal;
	double *fb;
	int np,rank;
	MPI_Status status;

	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &rank);

	fb = (double *)malloc(n*sizeof(double));

	nlocal = n/np;

	MPI_Allgather(b, nlocal, MPI_DOUBLE, fb, nlocal, MPI_DOUBLE, comm);

	for(i=0; i<nlocal; i++){
		x[i] = 0.0;
		for(j=0; j<n; j++){
			x[i] += a[i*n+j]*fb[j];
		}
	}

	free(fb);
	return 0;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int np; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int n = 4;
	double b = rank+1;
	double a[n]; 
	double x;

	for(int i=0; i<n; i++){
		a[i] = (rank*n)+i;	//Assign row of metrix
	}
	//printf("P%d b part is %f and metric part is",rank,b);
	//for(int i=0; i<n; i++){
	//	printf(" %f,",a[i]);
	//}
	//printf("\n");

	rowMatrixVectorMultiply(n, a, &b, &x, MPI_COMM_WORLD);

	printf("P%d value is\t:%f.\n",rank,x);

	MPI_Finalize();

	return 0;
}
