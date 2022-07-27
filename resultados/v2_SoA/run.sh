#!/bin/bash

#SBATCH --job-name=SoA
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

for N in {1500..10000..500}
do
    echo ">>>>> INICIO CON ${N} PARTÍCULAS" && make clean && make CPPFLAGS="-DNMAX=${N}" all && ./dendritas && echo "<<<<< FIN CON ${N} PARTÍCULAS"
done
make clean
