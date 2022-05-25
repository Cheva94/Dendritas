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
    double tSim = 0.0;
    double* lib = (double*)malloc(2 * NM * sizeof(double));
    double* dep = (double*)malloc(2 * N0MAX * sizeof(double));
    int* count = (int*)malloc(sizeof(int));
    srand(SEED);
    *count = N0;

    init(lib, dep);

    while (*(count) != N0MAX) {
        move(lib, dep, count);
        tSim += DT; // sum >> 1
        if (tSim % 10000 == 0) {
            printf(">>> Contador %d.\n", (*count));
            printf(">>> Progreso del %f %.\n", ((*count) - N0) / (N0MAX - N0));
            printf(">>> Progreso del %f %.\n", ((*count)) / (N0MAX));
        }
    }

    end(lib, dep, count, tSim);
    double wall = wtime() - start; // res >> 1
    printf("Hay un total de %d Li depositados. Tiempo simulando = %.2f ms --- WALL TIME = %.2f s.\n", N0MAX, tSim, wall);
}
