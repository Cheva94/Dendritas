#include "core.h"
#include "params.h"
#include "wtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    int prog = 0;
    double flopGral = 0.0, flopNeu = 0.0;
    double tSim = 0.0;
    double* lib = (double*)malloc(2 * NM * sizeof(double));
    double* dep = (double*)malloc(2 * N0MAX * sizeof(double));
    int* count = (int*)malloc(sizeof(int));
    srand(SEED);
    *count = N0;

    init(lib, dep);
    printf(">>> Hay %d Li depositados. Progreso = 0 %%.\n", N0);

    double start = wtime();
    while (*(count) != N0MAX) {
        move(lib, dep, count, &flopGral, &flopNeu);
        tSim += DT; // sum >> 1
        flopGral += flopNeu;

        prog++;
        if (prog % 10000 == 0) {
            printf(">>> Hay %d Li depositados. Progreso = %d %%.\n", (*count), 100 * ((*count) - N0) / (N0MAX - N0));
        }
    }
    double wall = wtime() - start; // res >> 1

    // double gFlopNeu = 0.000000001 * flopNeu / wall;
    // double gFlopGral = 0.000000001 * flopGral / wall;
    flopNeu *= 0.000000001 / wall;
    flopGral *= 0.000000001 / wall;

    end(lib, dep, tSim, wall, flopNeu, flopGral);
    printf("Hay un total de %d Li depositados.\n", N0MAX);
    printf("Tiempo simulando = %.2f ms\n", tSim);
    printf("WALL TIME = %.2f s.\n", wall);
    printf("GFLOPS neutral() = %f\n", flopNeu);
    printf("GFLOPS ./dendritas = %f\n\n\n\n\n", flopGral);

}
