#!/bin/bash

#SBATCH --job-name=perf
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

srun make clean && make dendritas && perf record ./dendritas
