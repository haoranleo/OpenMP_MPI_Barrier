#PBS -q cs6210
#PBS -l nodes=1:sixcore
#PBS -l walltime=00:05:00
#PBS -N mpi_diss
OMPI_MCA_mpi_yield_when_idle=0
/usr/lib64/openmpi/bin/mpirun -np 2 $HOME/final/dissemination  2 10000

#PBS -q cs6210
#PBS -l nodes=2:sixcore
#PBS -l walltime=00:05:00
#PBS -N mpi_diss
OMPI_MCA_mpi_yield_when_idle=0
/usr/lib64/openmpi/bin/mpirun -np 4 $HOME/final/dissemination  4 10000

#PBS -q cs6210
#PBS -l nodes=3:sixcore
#PBS -l walltime=00:05:00
#PBS -N mpi_diss
OMPI_MCA_mpi_yield_when_idle=0
/usr/lib64/openmpi/bin/mpirun -np 6 $HOME/final/dissemination  6 10000

#PBS -q cs6210
#PBS -l nodes=4:sixcore
#PBS -l walltime=00:05:00
#PBS -N mpi_diss
OMPI_MCA_mpi_yield_when_idle=0
/usr/lib64/openmpi/bin/mpirun -np 8 $HOME/final/dissemination  8 10000

#PBS -q cs6210
#PBS -l nodes=5:sixcore
#PBS -l walltime=00:05:00
#PBS -N mpi_diss
OMPI_MCA_mpi_yield_when_idle=0
/usr/lib64/openmpi/bin/mpirun -np 10 $HOME/final/dissemination  10 10000 

#PBS -q cs6210
#PBS -l nodes=6:sixcore
#PBS -l walltime=00:05:00
#PBS -N mpi_diss
OMPI_MCA_mpi_yield_when_idle=0
/usr/lib64/openmpi/bin/mpirun -np 12 $HOME/final/dissemination  12 10000 







