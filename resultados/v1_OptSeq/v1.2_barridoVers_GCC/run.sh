#!/bin/bash

#SBATCH --job-name=GCC-vers
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

echo "Corriendo con GCC con -O3 -march=native -ffast-math"
for x in 9 10
do
    echo ">>>>> INICIO GCC-${x}" && make clean && make CC="gcc-${x}" all && ./dendritas && echo "<<<<< FIN GCC-${p}"
done
make clean
