#!/bin/bash

#SBATCH --job-name=Clang-vers
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

echo "Corriendo con Clang con -O2 -march=native -funroll-loops"
for x in 10 11
do
    echo ">>>>> INICIO Clang-${x}" && make clean && make CC="clang-${x}" all && ./dendritas && echo "<<<<< FIN Clang-${p}"
done
make clean
