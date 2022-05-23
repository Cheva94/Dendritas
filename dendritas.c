#include "core.h"
#include "params.h"
// #include "wtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    int i = 0;
    double tSim;
    double *lib, *dep;
    int* count;

    count = (int*)malloc(sizeof(int));
    lib = (double*)malloc(2 * NM * sizeof(double));
    dep = (double*)malloc(2 * N0MAX * sizeof(double));

    srand(SEED);

    init(lib, dep);

    *count = N0;
    while (*(count) != N0MAX) {
        move(lib, dep, count);
        i++;
        tSim = i * DT;
        if (i % 2000 == 0) {
            printf(">>> Tiempo simulado: %f s >>> Li depositado: %d\n", tSim, *count);
        }
    }

    end(lib, dep, *count, tSim);
    printf("Se alcanzó la cantidad máxima de Li0 (%d) simulando durante %f s\n", *count, tSim);
}
