#!/bin/bash

#SBATCH --job-name=Clang-flags
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

echo "Corriendo con Clang-13"
cat flags-clang.txt | while read p
do
    echo ">>>>> INICIO FLAGS ${p}" && make clean && make CFLAGS="${p}" all && ./dendritas && echo "<<<<< FIN FLAGS ${p}"
done
make clean
