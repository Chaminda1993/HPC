#include <mpi.h> 
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 1) {
		int rec_val1;
		int rec_val2;
		MPI_Recv(&rec_val1, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&rec_val2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Process 1:\n\tI have received " << rec_val1 << " and " << rec_val2 << " from process 0" << endl;

		int sum = rec_val1 + rec_val2;
		cout << "\tSum of the received values are " << sum << endl << endl;
		MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	else if (myrank == 0) {
		int val1 = 3;
		int val2 = 5;
		MPI_Send(&val1, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Send(&val2, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

		int rec_sum;
		MPI_Recv(&rec_sum, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Process 0:\n\tI have received the sum from process 1\n\tThe sum is equal to " << rec_sum << endl;
	}



	MPI_Finalize();
}
