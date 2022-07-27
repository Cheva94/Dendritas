#!/bin/bash

#SBATCH --job-name=barridoParts
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

for N in {24000..40000..4000}
do
    echo ">>>>> INICIO CON ${N} PARTÍCULAS" && make clean && make CPPFLAGS="-DNMAX=${N}" all && ./dendritas && echo "<<<<< FIN CON ${N} PARTÍCULAS"
done
make clean
