#!/bin/bash

#SBATCH --job-name=OMP_nT7
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --exclusive
#SBATCH --cpus-per-task=7

. /etc/profile
export OMP_NUM_THREADS=7
export MKL_NUM_THREADS=7

echo "#----- ${OMP_NUM_THREADS} hilos -----#"

for N in {1500..10000..500}
do
    echo ">>>>> INICIO CON ${N} PARTÍCULAS" && make clean && make CPPFLAGS="-DNMAX=${N}" all && ./dendritas && echo "<<<<< FIN CON ${N} PARTÍCULAS"
done
make clean
