##Barrier implementation using OpenMP and MPI

This repo is project 2 of CS6210 in Gatech.

This project implemented centralized (sense reversing) barrier and dissemination barrier using OpenMP, and implemented dissemination barrier and MCS barrier using MPI. In addition, we implemented a combined MP-MPI barrier to synchronize between multiple cluster nodes that are each running multiple threads.

We also conducted several performance evaluation, more details can be seen in warpper file.

Group Member: Linhan Wei, Haoran Li
Submission Date: Oct. 22, 2018

##Start-up Instruction

To compile the source code and run the experiment, enter the following code in terminal (tested in Jinx compute cluster in Georgia Tech)

```

omp:
	gcc OpenMp/sense.c -o omp_sense -g -Wall -lm -fopenmp -DLEVEL1_DCACHE_LINESIZE=`getconf LEVEL1_DCACHE_LINESIZE` -std=c99
	gcc OpenMp/dissemination.c -o omp_dis -g -Wall -lm -fopenmp -DLEVEL1_DCACHE_LINESIZE=`getconf LEVEL1_DCACHE_LINESIZE` -std=c99
	qsub wrapper_omp_sense.sh
	qsub wrapper_omp_dis.sh

mpi:
	/usr/lib64/openmpi/bin/mpic++ -o dissemination -g -Wall MPI/dissemination.c -lgomp -lm
	/usr/lib64/openmpi/bin/mpic++ -o MCS -g -Wall MPI/MCS.c -lgomp -lm
	qsub ./wrapper_diss.sh
	qsub ./wrapper_MCS.sh

combine
	/usr/lib64/openmpi/bin/mpic++ -o combine -g -Wall ./Combine/combine.c -lgomp -lm -fopenmp
	qsub ./wrapper_combine.sh
	

```
