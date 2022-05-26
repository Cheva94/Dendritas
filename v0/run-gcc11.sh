#!/bin/bash

#SBATCH --job-name=dendritas
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

echo "Corriendo con GCC-11"
cat flags-gcc.txt | while read p
do
    echo ">>>>> INICIO FLAGS ${p}" && make clean && make CFLAGS="${p}" dendritas && ./dendritas && echo "<<<<< FIN FLAGS ${p}"
done
make clean
