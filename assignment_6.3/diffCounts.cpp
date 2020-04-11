#include <mpi.h> 
#include <iostream>
using namespace std;

template<typename T, size_t n>
void print_array(T const(& arr)[n])
{
	for (size_t i = 0; i < n; i++)
		std::cout << arr[i] << ' ';
	
	cout << endl;
}

int main(int argc, char* argv[])
{
	
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		int send_val[3] = {1,2,3};
		MPI_Send(&send_val, 3, MPI_INT, 1, 1, MPI_COMM_WORLD);
		cout << "Process " << myrank << " sent :";
		print_array(send_val);
	}

	else if (myrank == 1) {
		int rec_val[3];
		MPI_Recv(&rec_val, 3, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Process " << myrank << " received :";
		print_array(rec_val);
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
