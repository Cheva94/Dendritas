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
    int flopGral = 0, flopNeu = 0;
    int prog = 0;
    double tSim = 0.0;
    double* lib = (double*)malloc(2 * NM * sizeof(double));
    double* dep = (double*)malloc(2 * N0MAX * sizeof(double));
    int* count = (int*)malloc(sizeof(int));
    srand(SEED);
    *count = N0;

    init(lib, dep);
    flopGral = 4 * NM + 2 * N0;

    while (*(count) != N0MAX) {
        move(lib, dep, count, &flopGral, &flopNeu);
        tSim += DT; // sum >> 1
        flopGral++;

        prog++;
        if (prog % 10000 == 0) {
            printf(">>> Hay %d Li depositados. Progreso = %d %%.\n", (*count), 100 * ((*count) - N0) / (N0MAX - N0));
            printf("Flop Gral = %d \n", flopGral);
            printf("Flop Neu = %d \n", flopNeu);
        }
    }

    end(lib, dep, count, tSim);
    double wall = wtime() - start; // res >> 1
    flopGral++;
    printf("Hay un total de %d Li depositados. Tiempo simulando = %.2f ms --- WALL TIME = %.2f s.\n", N0MAX, tSim, wall);
}
