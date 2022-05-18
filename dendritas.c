// #include "core.h"
#include "params.h"
// #include "wtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <math.h>

/*
 * Creo que estoy escribiendo el código de campo nulo
 */
int main()
{
    double tita = 0.0, gx = 0.0, gy = 0.0; // Vector unitario aleatorio
    double modd = 0.0; // ¿?
    int i; //, j, k; // Variables mudas

    double *ex, *ey, *e0x, *e0y; // vectores espaciales de los iones
    ex = (double*)malloc(NM * sizeof(double));
    ey = (double*)malloc(NM * sizeof(double));
    e0x = (double*)malloc(NM * sizeof(double));
    e0y = (double*)malloc(NM * sizeof(double));

    double *lix_d, *liy_d; // arreglo de Li depositado sobre al ánodo
    lix_d = (double*)malloc(N0 * sizeof(double));
    liy_d = (double*)malloc(N0 * sizeof(double));

    double *lix_aux, *liy_aux; // ¿?
    lix_aux = (double*)malloc(N0MAX * sizeof(double));
    liy_aux = (double*)malloc(N0MAX * sizeof(double));

    printf("Checkpoint 1. Se podría printear las ctes de corrida \n");

    // Creación de la monocapa inicial de Li depositado
    for (i = 0; i < N0; i++) {
        lix_d[i] = 1.3 * RLI0 * i / LONG
        liy_d[i] = 0.0 / LONG
    }

    // Creación de las posiciones iniciales de los iones en el electrolito
    srand(SEED); // Punto inicial fijo para rand()

    for (i = 0; i < NM; i++) { // ¿?
        ex_0[i] =
        ex_0[i] =
    }

    // Guardar coordenadas del sistema inicial

}


// // 1/5 - Crea el puntero al archivo
// FILE *file_dyn;
//
// // 2/5 - Intenta abrir el archivo
// file_dyn = fopen("TAIL.xsf", "r");
//
// // 3/5 - Corrobora que se haya abierto el archivo
// if (file_dyn == NULL) {
//     printf("No se encontró el archivo.");
//     exit(0);
// }
//
// // 4/5 - Leer el archivo
//
//
// // 5/5 - Cierra el archivo al terminar
// fclose(file_dyn);
