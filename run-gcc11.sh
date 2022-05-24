#!/bin/bash

#SBATCH --job-name=dendritas
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

cat flags-gcc.txt | while read p
do
    make clean && make CFLAGS="${p}"
    ./dendritas
done

srun ./dendritas