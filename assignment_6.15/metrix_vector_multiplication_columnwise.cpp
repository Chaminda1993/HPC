#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int rowMatrixVectorMultiply(int n,double *a, double *b, double *x, MPI_Comm comm){
	int i,j;
	int nlocal;
	double *px;
	double *fx;
	int np,rank;
	MPI_Status status;

	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &rank);

	nlocal = n/np;

	px = (double *)malloc(n*sizeof(double));
	fx = (double *)malloc(n*sizeof(double));

	for(i=0; i<n; i++){
		px[i] = 0.0;
		for(j=0; j<nlocal; j++){
			px[i] += a[i*nlocal+j]*b[j];
		}
	}

	MPI_Reduce(px, fx, n, MPI_DOUBLE, MPI_SUM, 0, comm);
	MPI_Scatter(fx, nlocal, MPI_DOUBLE, x, nlocal, MPI_DOUBLE, 0, comm);

	free(fx); free(px);
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
		a[i] = (n*i)+rank;	// Assign column of metric
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
