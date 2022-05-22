#include "params.h"
// #include "core.h"
// #include "wtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double pbc(double coord, const double cell_length)
{
    if (coord < 0) {
        coord += cell_length;
    } else if (coord > cell_length) {
        coord -= cell_length;
    }
    return coord;
}

double rbc(double coord, const double cell_length)
{
    if (coord < 0) {
        coord = fabs(coord);
    } else if (coord > cell_length) {
        coord = 2 * cell_length - coord;
    }
    return coord;
}

void init(double* ex_0, double* ey_0, double* dep_x, double* dep_y)
{
    int i;

    for (i = 0; i < NM; i++) { // ¿?
        ex_0[i] = rand() / (double)RAND_MAX;
        ey_0[i] = rand() / (double)RAND_MAX;
    }

    for (i = 0; i < N0; i++) {
        dep_x[i] = 1.3 * RLI0 * i / LONG;
        dep_y[i] = 0.0 / LONG;
    }

    FILE *f_initLi0, *f_initLiM;
    f_initLi0 = fopen("EstadoInicial_Li0.csv", "w");
    f_initLiM = fopen("EstadoInicial_LiM.csv", "w");

    fprintf(f_initLi0, "x, y\n");
    for (i = 0; i < N0; i++) {
        fprintf(f_initLi0, "%f, %f\n", dep_x[i], dep_y[i]);
    }

    fprintf(f_initLiM, "x, y\n");
    for (i = 0; i < NM; i++) {
        fprintf(f_initLiM, "%f, %f\n", ex_0[i], ey_0[i]);
    }

    fclose(f_initLi0);
    fclose(f_initLiM);
}

void end(double* ex, double* ey, double* dep_x, double* dep_y, int counter, double tSim)
{
    int i;

    FILE *f_endLi0, *f_endLiM, *f_params;

    f_endLi0 = fopen("EstadoFinal_Li0.csv", "w");
    f_endLiM = fopen("EstadoFinal_LiM.csv", "w");
    f_params = fopen("Parametros.csv", "w");

    fprintf(f_endLi0, "x, y\n");
    for (i = 0; i < N0MAX; i++) {
        fprintf(f_endLi0, "%f, %f\n", dep_x[i], dep_y[i]);
    }

    fprintf(f_endLiM, "x, y\n");
    for (i = 0; i < NM; i++) { // ¿?
        fprintf(f_endLiM, "%f, %f\n", ex[i], ey[i]);
    }

    fprintf(f_params, "Parámetro, Valor, Unidad\n");
    fprintf(f_params, "Paso temporal, %f, us\n", DT);
    fprintf(f_params, "Li+ siempre presente, %d, \n", NM);
    fprintf(f_params, "Li0 inicial, %d, \n", N0);
    fprintf(f_params, "Li0 máximo, %d, \n", N0MAX);
    fprintf(f_params, "Li0 alcanzado, %d, \n", counter);
    fprintf(f_params, "Tiempo simulado, %f, us\n", tSim);

    fclose(f_endLi0);
    fclose(f_endLiM);
    fclose(f_params);
}

int main()
{
    int i = 0, j, k;
    int counter = N0;
    double tita = 0.0, gx = 0.0, gy = 0.0;
    double distx, disty, dist, dist2;
    double tSim;
    double exs, eys;
    double *ex, *ey, *ex_0, *ey_0; // vectores espaciales de los iones
    double *dep_x, *dep_y;

    ex = (double*)malloc(NM * sizeof(double));
    ey = (double*)malloc(NM * sizeof(double));
    ex_0 = (double*)malloc(NM * sizeof(double));
    ey_0 = (double*)malloc(NM * sizeof(double));
    dep_x = (double*)malloc(N0MAX * sizeof(double));
    dep_y = (double*)malloc(N0MAX * sizeof(double));

    srand(SEED); // Punto inicial fijo para rand() - reproducibildiad

    init(ex_0, ey_0, dep_x, dep_y);

    while (counter != N0MAX) {
        for (j = 0; j < NM; j++) {
            tita = 2 * M_PI * rand() / (double)RAND_MAX;
            gx = cos(tita);
            gy = sin(tita);

            ex[j] = ex_0[j] + Q * gx;
            ey[j] = ey_0[j] + Q * gy + RY;

            ex[j] = pbc(ex[j], 1);
            ey[j] = rbc(ey[j], 1);

            for (k = 0; k < counter; k++) {
                distx = ex[j] - dep_x[k];
                disty = ey[j] - dep_y[k];
                dist2 = pow(distx, 2) + pow(disty, 2);

                if (dist2 < DATT2) {
                    dist = sqrt(dist2);
                    exs = distx * DATT / dist + dep_x[k];
                    eys = disty * DATT / dist + dep_y[k];

                    dep_x[counter] = pbc(exs, 1);
                    dep_y[counter] = pbc(eys, 1);

                    // Repongo el ion
                    ex[j] = rand() / (double)RAND_MAX;
                    ey[j] = rand() / (double)RAND_MAX;

                    counter++;
                }
            }
        }

        i++;
        tSim = i * DT;
        ex_0 = ex;
        ey_0 = ey;

        if (i % 2000 == 0) {
            printf(">>> Tiempo simulado: %f s >>> Li depositado: %d\n", tSim, counter);
        }
    }

    end( ex, ey, dep_x, dep_y, counter, tSim);
    printf("Se alcanzó la cantidad máxima de Li0 (%d) simulando durante %f s\n", counter, tSim);
}
