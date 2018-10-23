
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

#define ITERS 10000

typedef struct node {
	int arv_child_id[4];
	int arv_parent_id;
	int wkp_child_id[2];
	int wkp_parent_id;
}mcs_node;

static mcs_node *myNode;

void mpi_mcs_barrier_init(MPI_Comm comm, int my_id, int num_processes) {
	myNode = (mcs_node*)malloc(sizeof(mcs_node));

    for (int i = 0; i < 4; i++) {
        if (4 * my_id + i + 1 < num_processes) {
            myNode->arv_child_id[i] = 4 * my_id + i + 1; //if have child
        } else {
            myNode->arv_child_id[i] = -1; 			   //NOT have child
        }
    }

    for (int i = 0; i < 2; i++) {
        if (2 * my_id + i + 1 < num_processes) {
            myNode->wkp_child_id[i] = 2 * my_id + i + 1; //have wakeup child
        } else {
            myNode->wkp_child_id[i] = -1;
        }
    }

    if (my_id != 0) {
        myNode->arv_parent_id = (my_id - 1) / 4;
        myNode->wkp_parent_id = (my_id - 1) / 2;
    } else {
        myNode->arv_parent_id = -1;
        myNode->wkp_parent_id = -1;
    }
}

void mpi_mcs_barrier(MPI_Comm comm, int my_id, int num_processes) {
	for (int i = 0; i < 4; i++) {
        int child_id = myNode->arv_child_id[i];
        if (child_id != -1) {
            MPI_Recv(NULL, 0, MPI_INT, child_id, 0, comm, NULL);
        }
    }

    if (my_id != 0) {
        MPI_Send(NULL, 0, MPI_INT, myNode->arv_parent_id, 0, comm);
        MPI_Recv(NULL, 0, MPI_INT, myNode->wkp_parent_id, 1, comm, NULL);
    }

    for (int i = 0; i < 2; i++) {
        int child_id = myNode->wkp_child_id[i];
        if (child_id != -1) {
            MPI_Send(NULL, 0, MPI_INT, child_id, 1, comm);
        }
    }
}

void mpi_mcs_finalize() {
	if(myNode) {
		free(myNode);
	}
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

	mpi_mcs_barrier_init(MPI_COMM_WORLD, my_id, num_processes);

    double start, end;
    start = MPI_Wtime();
	
	int iters = atoi(argv[2]);
	for (int i = 0; i < iters; i++) {
		//printf("iters %d: process %d reached\n", i, my_id);
		mpi_mcs_barrier(MPI_COMM_WORLD, my_id, num_processes);
	}

    end = MPI_Wtime();
    printf("%lf\n", (end - start)*1000);
  	
  	MPI_Finalize();
  	mpi_mcs_finalize();
	return 0;
}