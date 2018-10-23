CC = gcc
#CC = gcc-8
CXX = mpic++
MPICC = mpicc
CFLAGS = -g -Wall -lm
CXXFLAGS = -std=c++11
MPFLAGS = -fopenmp -DLEVEL1_DCACHE_LINESIZE=`getconf LEVEL1_DCACHE_LINESIZE`

BIN_DIR = bin
OBJ_DIR = obj
OPENMP_DIR = OpenMP
MPI_DIR = MPI
COM_DIR = Combine

all: omp_sense omp_dissemination mpi_dissemination mpi_MCS combine

omp_sense: $(OPENMP_DIR)/sense.c $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/sense $< $(CFLAGS) $(MPFLAGS)

omp_dissemination: $(OPENMP_DIR)/dissemination.c $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/dissemination $< $(CFLAGS) $(MPFLAGS)

mpi_dissemination: $(MPI_DIR)/dissemination.c $(BIN_DIR)
	$(MPICC) -o $(BIN_DIR)/dissemination_mpi $< $(CFLAGS)

mpi_MCS: $(MPI_DIR)/MCS.c $(BIN_DIR)
	$(MPICC) -o $(BIN_DIR)/MCS $< $(CFLAGS)

combine: $(COM_DIR)/combine.c $(BIN_DIR)
	$(MPICC) -o $(BIN_DIR)/combine $< $(CFLAGS) $(MPFLAGS) 



$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


clean:
	rm -rf $(BIN_DIR)/
	rm -rf $(OBJ_DIR)/
	rm -f *.o gtmp gtmpi