#include "core.h"
#include "params.h"
#include "wtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    double start = wtime();
    int i = 0;
    double tSim = 0.0;
    int* count = (int*)malloc(sizeof(int));
    double* lib = (double*)malloc(3 * NM2 * sizeof(double));
    double* dep = (double*)malloc(3 * N0MAX2 * sizeof(double));

    *count = N02;
    srand(SEED);
    init(lib, dep);

    while (*(count) != N0MAX) {
        move(lib, dep, count);
        i++;
        tSim = i * DT;
        if (i % 10000 == 0) {
            printf(">>> Tiempo simulado: %.0f ms >>> Li depositado: %d\n", tSim, *count);
        }
    }

    end(lib, dep, count, tSim);
    double elapsed = wtime() - start;
    printf("Se alcanzó la cantidad máxima de Li0 (%d) simulando durante %.2f ms. Tiempo transcrurrido %.2f s.\n", *count, tSim, elapsed);
}
