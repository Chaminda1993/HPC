#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
	MPI_Init(NULL, NULL);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	printf("Hello DCS! My rank is %d out of %d processors\n", my_rank, world_size);

	MPI_Finalize();
	
	return 0;
}
