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
    double tSim = 0.0;
    double* flopGral = (double*)malloc(sizeof(double));
    // double* flopNeu = (double*)malloc(sizeof(double));
    double* lib = (double*)malloc(2 * NL * sizeof(double));
    double* dep = (double*)malloc(2 * NMAX * sizeof(double));
    int* count = (int*)malloc(sizeof(int));
    srand(SEED);
    *count = ND;

    init(lib, dep);
    printf(">>> Hay %d Li depositados. Progreso = 0 %%.\n", ND);

    double start = wtime();
    while (*(count) != NMAX) {
        move(lib, dep, count, flopGral);//, flopNeu);
        tSim += DT; // sum >> 1
        // *flopGral += *flopNeu;

        prog++;
        if (prog % 10000 == 0) {
            printf(">>> Hay %d Li depositados. Progreso = %d %%.\n", (*count), 100 * ((*count) - ND) / (NMAX - ND));
        }
    }
    double wall = wtime() - start; // res >> 1

    // *flopNeu *= 0.000000001 / wall;
    *flopGral *= 0.000000001 / wall;

    end(lib, dep, tSim, wall, flopGral);//, flopNeu);
    printf("Hay un total de %d Li depositados.\n", NMAX);
    printf("Tiempo simulando = %.2f ms\n", tSim);
    printf("WALL TIME = %.2f s\n", wall);
    // printf("GFLOPS neutral() = %f\n", *flopNeu);
    printf("GFLOPS ./dendritas = %f\n\n", *flopGral);

}
