#include <mpi.h> 
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		int send_val = 10;
		MPI_Send(&send_val, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		cout << "Process " << myrank << " sent " << send_val << endl;
	}

	else if (myrank == 1) {
		int rec_val;
		MPI_Recv(&rec_val, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Process " << myrank << " received " << rec_val << endl;
	}

	MPI_Finalize();
}

// Synopsis
// int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)

// Input Parameters
// buf - initial address of send buffer (choice)
// count - number of elements in send buffer (nonnegative integer)
// datatype - datatype of each send buffer element (handle)
// dest - rank of destination (integer)
// tag - message tag (integer)
// comm - communicator (handle)
