// #include "core.h"
#include "params.h"
// #include "wtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double pbc(double coord, const double cell_length)
{
    // condiciones periodicas de contorno coordenadas entre [0,L) con L=1
    if (coord < 0) {
        coord += cell_length;
    } else if (coord > cell_length) {
        coord -= cell_length;
    }
    return coord;
}

double rbc(double coord, const double cell_length)
{
    // condiciones reflectivas de contorno coordenadas entre [0,L) con L=1
    if (coord < 0) {
        coord = fabs(coord);
    } else if (coord > cell_length) {
        coord = 2 * cell_length - coord;
    }
    return coord;
}

void init(double* ex_0, double* ey_0, double* lix_d, double* liy_d, double* lix_0, double* liy_0)
{
    int i;

    // Creación de las posiciones iniciales de los iones en el electrolito
    for (i = 0; i < NM; i++) { // ¿?
        ex_0[i] = rand() / (double)RAND_MAX;
        ey_0[i] = rand() / (double)RAND_MAX;
    }

    // Creación de la monocapa inicial de Li depositado
    for (i = 0; i < N0; i++) {
        lix_d[i] = 1.3 * RLI0 * i / LONG;
        liy_d[i] = 0.0 / LONG;
    }

    for (i = 0; i < N0; i++) {
        lix_0[i] = lix_d[i];
        liy_0[i] = liy_d[i];
    }

    FILE *f_initLi0, *f_initLiM;
    f_initLi0 = fopen("EstadoInicial_Li0.csv", "w");
    f_initLiM = fopen("EstadoInicial_LiM.csv", "w");

    fprintf(f_initLi0, "x, y\n");
    for (i = 0; i < N0; i++) {
        fprintf(f_initLi0, "%f, %f\n", lix_d[i], liy_d[i]);
    }

    fprintf(f_initLiM, "x, y\n");
    for (i = 0; i < NM; i++) {
        fprintf(f_initLiM, "%f, %f\n", ex_0[i], ey_0[i]);
    }

    fclose(f_initLi0);
    fclose(f_initLiM);
}

void end(double* ex, double* ey, double* lix_0, double* liy_0, int Li0_counter, double tSim)
{
    int i;

    FILE *f_endLi0, *f_endLiM, *f_params;

    f_endLi0 = fopen("EstadoFinal_Li0.csv", "w");
    f_endLiM = fopen("EstadoFinal_LiM.csv", "w");
    f_params = fopen("Parametros.csv", "w");

    fprintf(f_endLi0, "x, y\n");
    for (i = 0; i < N0MAX; i++) { // ¿?
        fprintf(f_endLi0, "%f, %f\n", lix_0[i], liy_0[i]);
    }

    fprintf(f_endLiM, "x, y\n");
    for (i = 0; i < NM; i++) { // ¿?
        fprintf(f_endLiM, "%f, %f\n", ex[i], ey[i]);
    }

    fprintf(f_params, "Parámetro, Valor, Unidad\n");
    fprintf(f_params, "Paso temporal, %f, us\n", DT);
    fprintf(f_params, "Cantidad de pasos temporales, %d, \n", NT);
    fprintf(f_params, "Li+ siempre presente, %d, \n", NM);
    fprintf(f_params, "Li0 inicial, %d, \n", N0);
    fprintf(f_params, "Li0 máximo, %d, \n", N0MAX);
    fprintf(f_params, "Li0 alcanzado, %d, \n", Li0_counter);
    fprintf(f_params, "Tiempo simulado, %f, us\n", tSim);

    fclose(f_endLi0);
    fclose(f_endLiM);
    fclose(f_params);
}

int main()
{
    int i, j, k, l; // Variables mudas
    int Li0_counter = N0;
    double tita = 0.0, gx = 0.0, gy = 0.0; // Vector unitario aleatorio
    double distx, disty, dist, dist2; // calculo de distancias
    double exs, eys; // escalares para las posiciones ¿?
    double tSim; // tiempo para la evolucion
    double *ex, *ey, *ex_0, *ey_0; // vectores espaciales de los iones
    double *lix_d, *liy_d; // arreglo de Li depositado sobre al ánodo
    double *lix_0, *liy_0; // ¿?
    double *lix_aux, *liy_aux; // ¿?

    ex = (double*)malloc(NM * sizeof(double));
    ey = (double*)malloc(NM * sizeof(double));
    ex_0 = (double*)malloc(NM * sizeof(double));
    ey_0 = (double*)malloc(NM * sizeof(double));
    lix_d = (double*)malloc(N0 * sizeof(double));
    liy_d = (double*)malloc(N0 * sizeof(double));
    lix_0 = (double*)malloc(N0MAX * sizeof(double));
    liy_0 = (double*)malloc(N0MAX * sizeof(double));
    lix_aux = (double*)malloc(N0MAX * sizeof(double));
    liy_aux = (double*)malloc(N0MAX * sizeof(double));

    srand(SEED); // Punto inicial fijo para rand() - reproducibildiad

    init(ex_0, ey_0, lix_d, liy_d, lix_0, liy_0);

    FILE *f_TEST;
    f_TEST = fopen("TEST_BASE.csv", "w");

    i = 0;
    while (Li0_counter != N0MAX) {
        for (j = 0; j < NM; j++) {
            // Definición del vector unitario
            tita = 2 * M_PI * rand() / (double)RAND_MAX;
            gx = cos(tita);
            gy = sin(tita);

            // Evolución de la posición
            ex[j] = ex_0[j] + Q * gx + RX;
            ey[j] = ey_0[j] + Q * gy + RY;

            // PBC para la caja de tamaño 1x1 normalizada
            ex[j] = pbc(ex[j], 1);
            ey[j] = rbc(ey[j], 1);

            fprintf(f_TEST, "tita = %f || gx = %f || gy = %f \n", tita, gx, gy);
            fprintf(f_TEST, "exy_0 = (%f, %f) || exy = (%f, %f) \n", ex_0[j], ey_0[j], ex[j], ey[j]);
            // Definicion de la condicion de neutralización
            for (k = 0; k < Li0_counter; k++) {
                distx = ex[j] - lix_0[k];
                disty = ey[j] - liy_0[k];
                dist2 = pow(distx, 2) + pow(disty, 2);

                fprintf(f_TEST, "distx = %f || disty = %f || dist2 = %f \n", distx, disty, dist2);

                if (dist2 < DATT2) {
                    dist = sqrt(dist2);
                    exs = distx * DATT / dist + lix_0[k];
                    eys = disty * DATT / dist + liy_0[k];

                    fprintf(f_TEST, "exs = %f || exs = %f \n", exs, eys);

                    for (l = 0; l < N0; l++) {
                        lix_aux[l] = lix_d[l];
                        liy_aux[l] = liy_d[l];
                    }

                    lix_aux[Li0_counter] = exs;
                    liy_aux[Li0_counter] = eys;

                    for (l = 0; l < Li0_counter; l++) {
                        lix_0[l] = lix_aux[l];
                        liy_0[l] = liy_aux[l];
                    }

                    // PBC
                    for (l = 0; l < Li0_counter; l++) {
                        lix_0[l] = pbc(lix_0[l], 1);
                        liy_0[l] = rbc(liy_0[l], 1);
                    }

                    // Repongo el ion
                    ex[j] = rand() / (double)RAND_MAX;
                    ey[j] = rand() / (double)RAND_MAX;

                    Li0_counter++;
                }
            }
        }

        i++;
        tSim = i * DT;
        ex_0 = ex;
        ey_0 = ey;

        if (i % 2000 == 0) {
            printf(">>> Tiempo simulado: %f s >>> Li depositado: %d\n", tSim, Li0_counter);
        }
    }

    fclose(f_TEST);

    end( ex, ey, lix_0, liy_0, Li0_counter, tSim);

    printf("Se alcanzó la cantidad máxima de Li0 (%d) simulando durante %f s\n", Li0_counter, tSim);
}
