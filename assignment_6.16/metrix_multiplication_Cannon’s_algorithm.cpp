#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int multiply(int n, int rank, int *a, int *b, int *x, MPI_Comm comm){
	MPI_Comm cart_comm;
	int dim[] = {n, n};
	int period[] = {1,1};
	MPI_Cart_create(comm, 2, dim, period, 0, &cart_comm);

	int coord[2];
	MPI_Cart_coords(cart_comm, rank, 2, coord);

	// Initial alignment
	int a_to, a_from, b_to, b_from;
	MPI_Cart_shift(cart_comm, 0, coord[1], &b_to, &b_from);
	MPI_Cart_shift(cart_comm, 1, coord[0], &a_to, &a_from);

	if(rank == 0) printf("Initial alignment\n");
	printf("P%d x:%d, y:%d | a_to:%d, a_from:%d, b_to:%d, b_from:%d\n",rank,coord[0],coord[1],a_to,a_from,b_to,b_from);

	*x = 0;
	for(int i=0; i<n; i++){
		int tmp_a, tmp_b;
		MPI_Sendrecv(a, 1, MPI_INT, a_to, 824, &tmp_a, 1, MPI_INT, a_from, 824, cart_comm, MPI_STATUS_IGNORE);
		MPI_Sendrecv(b, 1, MPI_INT, b_to, 824, &tmp_b, 1, MPI_INT, b_from, 824, cart_comm, MPI_STATUS_IGNORE);

		//if(rank ==4) printf("iteration:%d, tmp_a:%d, tmp_b:%d\n",i, tmp_a, tmp_b);
		*x += (tmp_a) * (tmp_b);
		*a = tmp_a; *b = tmp_b;
		
		MPI_Cart_shift(cart_comm, 0, 1, &b_to, &b_from);
		MPI_Cart_shift(cart_comm, 1, 1, &a_to, &a_from);
	}

	return 0;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int np; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &np);
							//		|0 1 2|
	int x, a = rank, b = rank, n = 3;		//	A = B = |3 4 5|
							//		|6 7 8|
	multiply(n, rank, &a, &b, &x, MPI_COMM_WORLD);

	printf("P%d x value is:%d\n",rank,x);

	MPI_Finalize();

	return 0;
}
