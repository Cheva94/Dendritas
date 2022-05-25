#include "core.h"
#include "params.h"
#include "wtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    int i = 0;
    double tSim;
    double start = wtime();
    double* lib = (double*)malloc(2 * NM * sizeof(double));
    double* dep = (double*)malloc(2 * N0MAX * sizeof(double));
    int* count = (int*)malloc(sizeof(int));

    srand(SEED);

    init(lib, dep);

    *count = N0; // ver de poner en la definicion en vez del malloc

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
