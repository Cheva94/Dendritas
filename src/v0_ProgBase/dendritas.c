#include "params.h"
#include "xoshiro.h"
#include "core.h"
#include "wtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    unsigned int prog = 0;
    float tSim = 0.0f;
    float* lib = (float*)malloc(2 * NL * sizeof(float));
    float* dep = (float*)calloc(2 * NMAX, sizeof(float));
    unsigned int* count = (unsigned int*)malloc(sizeof(unsigned int));
    unsigned int* countAux = (unsigned int*)malloc(sizeof(unsigned int));
    *count = ND;
    jump();

    init(lib, dep);
    printf(">>> Hay %d Li depositados. Progreso = 0 %%.\n", ND);

    while ((*count) <= NMAX) {
        move(lib);
        *countAux = 0;
        update(lib, dep, count, countAux);
        *count += *countAux;

        tSim += DT;
        prog++;
        if (prog % 10000 == 0) {
            printf(">>> Hay %d Li depositados. Progreso = %d %%.\n", (*count), 100 * ((*count) - ND) / (NMAX - ND));
        }
    }

    end(lib, dep, tSim);

    printf("Hay un total de %d Li depositados (%d %%).\n", (*count), 100 * ((*count) - ND) / (NMAX - ND));
    printf("Tiempo simulado = %.3f ms\n", tSim);

    free(lib);
    free(dep);
    free(count);
    free(countAux);
}
