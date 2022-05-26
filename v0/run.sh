#!/bin/bash

#SBATCH --job-name=dendritas
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

make clean && make dendritas && ./dendritas
