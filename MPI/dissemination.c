
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

#define ITERS 10000

int rounds;

void mpi_dis_barrier_init(MPI_Comm comm, int num_processes){
	rounds = ceil(log(num_processes)/log(2));		//find the number of rounds - log2numThreads
}

void mpi_dis_barrier(MPI_Comm comm, int num_processes, int my_id) {
	for(int i = 0; i < rounds; i++) {
		MPI_Send(NULL, 0, MPI_INT, (my_id + (int)pow(2, i)) % num_processes, 0, MPI_COMM_WORLD);
		int source = my_id - (int)pow(2,i);
		if(source < 0) {
			source += num_processes;
		}
		MPI_Recv(NULL, 0, MPI_INT, source, 0, MPI_COMM_WORLD, NULL);
	}
}

void mpi_dis_finalize(){
	return;
}


int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Wrong input format\n ./sense NUM_PROCESSES\n");
		return -1;
	}
	
	int num_processes;		
	int my_id;

	MPI_Init(&argc, &argv);
  	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
  	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

	mpi_dis_barrier_init(MPI_COMM_WORLD, num_processes);

	double start, end;
	start = MPI_Wtime();
	
	int iters = atoi(argv[2]);
	for (int i = 0; i < iters; i++) {
		//printf("iters %d: process %d reached\n", i, my_id);
		mpi_dis_barrier(MPI_COMM_WORLD, num_processes, my_id);
	}

	end = MPI_Wtime();
	printf("time: %lf ms\n", (end - start)*1000);
  	
  	MPI_Finalize();
  	mpi_dis_finalize();
	return 0;
}