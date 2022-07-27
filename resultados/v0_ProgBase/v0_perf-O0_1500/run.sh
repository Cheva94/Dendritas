#!/bin/bash

#SBATCH --job-name=v0Perf
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

make clean && make all && perf record ./dendritas && make clean
