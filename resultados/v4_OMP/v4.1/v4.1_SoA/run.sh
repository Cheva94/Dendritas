#!/bin/bash

#SBATCH --job-name=OMP-SoA
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --exclusive
#SBATCH --cpus-per-task=28

. /etc/profile
export OMP_NUM_THREADS=28
export MKL_NUM_THREADS=28

make clean && make all && ./dendritas && make clean
