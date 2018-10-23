
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

int numThreads;			
bool** messageArray;		
int rounds;

void barrier_init(){
	int i;
	omp_set_num_threads(numThreads);
	rounds = ceil(log(numThreads)/log(2));		//find the number of rounds - log2numThreads

	messageArray = (bool**)malloc(rounds*sizeof(bool*));

	for (i = 0; i < rounds; i++){
		messageArray[i] = (bool*)malloc(numThreads*sizeof(bool));
		for (int j = 0; j< numThreads; j++) {
			messageArray[i][j] = false; 
		}
	}
}

void omp_barrier() {
	int my = omp_get_thread_num();

	for(int i = 0; i < rounds; i++){
		int dest = (my + (int)pow(2,i)) % numThreads;

		while(messageArray[i][dest]);
		messageArray[i][dest] = true; 

		while(!messageArray[i][my]);
		messageArray[i][my] = false; 
	}


}


int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Wrong input format\n ./sense NUM_THREADS NUM_ITERS\n");
		return -1;
	}

	numThreads = atoi(argv[1]);
	int iters = atoi(argv[2]);
	barrier_init();

	double start, end;
	start = omp_get_wtime();
	#pragma omp parallel shared(numThreads,messageArray)
	{
		for (int i = 0; i < iters; i++) {
			omp_barrier();
			//printf("iters %d: thread %d reached\n", i, omp_get_thread_num());
		}
	}
	end = omp_get_wtime();
	printf("time: %lf\n", end - start);


	return 0;
}