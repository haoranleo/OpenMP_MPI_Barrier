
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


int count;
bool sense;

void omp_barrier() {
	bool local_sense = !sense;
	if(__sync_fetch_and_sub(&count,1) == 1){//last
		count = omp_get_num_threads();
		sense = !sense;
	}
	else{
		while(local_sense == !sense);
	}
}


int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Wrong input format\n ./sense NUM_THREADS NUM_ITERS\n");
		return -1;
	}

	count = atoi(argv[1]);
	int iters = atoi(argv[2]);
	sense = true;
	omp_set_num_threads(count);

	double start, end;
	start = omp_get_wtime();
	#pragma omp parallel shared(count,sense)
	{
		for (int i = 0; i < iters; i++) {
			//printf("iters %d: thread %d reached\n", i, omp_get_thread_num());
			omp_barrier();
		}
	}
	end = omp_get_wtime();
	printf("time: %lf\n", end - start);


	return 0;
}