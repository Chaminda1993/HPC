#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int allToOneReduce(int *data, int *sum, int count, MPI_Datatype datatype, int root, MPI_Comm comm){
	int rk,np;
	MPI_Comm_rank(comm,&rk);
	MPI_Comm_size(comm, &np);

	for(int i=0; i<count; i++){ *(sum+i)= *(data+i);}
	
	int dim = log2(np);
	int mask = 0;
	
	for(int i = 0; i<dim; i++){
		int pow2i = pow(2,i);
		if((rk & mask) == 0){
			if((rk & pow2i)!= 0){
				int dest = rk ^ pow2i;
				MPI_Send(sum, count, datatype, dest, 0, comm);
			}else{
				int src = rk ^ pow2i;
				MPI_Recv(data, count, datatype, src, 0, comm, MPI_STATUS_IGNORE);	
				for(int j=0; j<count; j++) {*(sum+j) = *(sum+j) + *(data+j);}
			}
		}
		mask = mask ^ pow2i;
	}
	
	return 0;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank; // Rank of process
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int np; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int m = 2,data[m], sum[m];
	data[0] = 1;
	data[1] = rank;
	allToOneReduce(data, sum, m, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) for(int i=0; i<m; i++) printf("Reduced value %d is %d.\n",i,sum[i]);

	MPI_Finalize();

	return 0;
}
