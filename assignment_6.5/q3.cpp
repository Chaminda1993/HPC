#include <mpi.h> 
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	
	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		//Send values to processes
		int vals[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};

		for(int i=0; i<3; i++){
			MPI_Send(vals+(i*5), 5, MPI_INT, i+1, 3, MPI_COMM_WORLD);
		}

		//Collect local avg and calculate global avg
		float asum = 0.0;
		float avg;
		for(int i=0; i<3; i++){
			MPI_Recv(&avg, 1,MPI_FLOAT, MPI_ANY_SOURCE, i+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			asum += avg;
		}
		float comAvg = asum/3.0;
		printf("Complete average value is %f.\n",comAvg);
	}

	else if (myrank == 1|| myrank == 2|| myrank == 3) {
		//Collect data
		int recVals[5];

		MPI_Recv(recVals, 5, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int sum = 0;
		for(int i = 0; i< 5;i++){
			sum += recVals[i];
		}
		//Calculate local avg
		float avg = sum/5.0;
		printf("Average value of P%d is: %f.\n",myrank,avg);
		//Send local avg to P0
		MPI_Send(&avg, 1, MPI_FLOAT, 0, myrank, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
