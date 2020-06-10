#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int oneToAllBC(void *data, int count, MPI_Datatype datatype, int root, MPI_Comm comm){
	int rk,np;
	MPI_Comm_rank(comm,&rk);
	MPI_Comm_size(comm, &np);
	
	int vID = rk ^ root;
	int dim = log2(np);
	int mask = np-1;
	
	for(int i = dim-1;i>=0;i--){
		int pow2i = pow(2,i);
		mask = mask ^ pow2i;
		if((vID & mask) == 0){
			if((vID & pow2i)== 0){
				int vDest = vID ^ pow2i;
				MPI_Send(data, count, datatype, (vDest ^ root), 0, comm);
			}else{
				int vSrc = vID ^ pow2i;
				MPI_Recv(data, count, datatype, (vSrc ^ root), 0, comm, MPI_STATUS_IGNORE);	
			}
		}
	}
	
	return 0;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank; // Rank of process
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int np; // Number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int data;
	if(rank == 1) data = 4;
	oneToAllBC(&data, 1, MPI_INT, 1, MPI_COMM_WORLD);

	printf("P%d value is %d.\n",rank,data);

	MPI_Finalize();

	return 0;
}
