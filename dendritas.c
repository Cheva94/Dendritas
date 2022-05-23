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

void init(double* lib_x, double* lib_y, double* dep_x, double* dep_y)
{
    int i;

    for (i = 0; i < NM; i++) {
        lib_x[i] = rand() / (double)RAND_MAX;
        lib_y[i] = rand() / (double)RAND_MAX;
    }

    for (i = 0; i < N0; i++) {
        dep_x[i] = 1.3 * RLI0 * i / LONG;
        dep_y[i] = 0.0 / LONG;
    }

    FILE *f_initDep, *f_initLib;
    f_initDep = fopen("Est0_Dep.csv", "w");
    f_initLib = fopen("Est0_Lib.csv", "w");

    fprintf(f_initDep, "x, y\n");
    for (i = 0; i < N0; i++) {
        fprintf(f_initDep, "%f, %f\n", dep_x[i], dep_y[i]);
    }

    fprintf(f_initLib, "x, y\n");
    for (i = 0; i < NM; i++) {
        fprintf(f_initLib, "%f, %f\n", lib_x[i], lib_y[i]);
    }

    fclose(f_initDep);
    fclose(f_initLib);
}

void end(double* lib_x, double* lib_y, double* dep_x, double* dep_y, int counter, double tSim)
{
    int i;

    FILE *f_endDep, *f_endLib, *f_params;

    f_endDep = fopen("Est1_Dep.csv", "w");
    f_endLib = fopen("Est1_Lib.csv", "w");
    f_params = fopen("Parametros.csv", "w");

    fprintf(f_endDep, "x, y\n");
    for (i = 0; i < N0MAX; i++) {
        fprintf(f_endDep, "%f, %f\n", dep_x[i], dep_y[i]);
    }

    fprintf(f_endLib, "x, y\n");
    for (i = 0; i < NM; i++) {
        fprintf(f_endLib, "%f, %f\n", lib_x[i], lib_y[i]);
    }

    fprintf(f_params, "Parámetro, Valor, Unidad\n");
    fprintf(f_params, "Paso temporal, %f, us\n", DT);
    fprintf(f_params, "Li+ siempre presente, %d, \n", NM);
    fprintf(f_params, "Li0 inicial, %d, \n", N0);
    fprintf(f_params, "Li0 máximo, %d, \n", N0MAX);
    fprintf(f_params, "Li0 alcanzado, %d, \n", counter);
    fprintf(f_params, "Tiempo simulado, %f, us\n", tSim);

    fclose(f_endDep);
    fclose(f_endLib);
    fclose(f_params);
}

int main()
{
    int i = 0, j, k;
    int counter = N0;
    double tita, gx, gy;
    double distx, disty, dist, dist2;
    double tSim;
    double *lib_x, *lib_y, *dep_x, *dep_y;

    lib_x = (double*)malloc(NM * sizeof(double));
    lib_y = (double*)malloc(NM * sizeof(double));
    dep_x = (double*)malloc(N0MAX * sizeof(double));
    dep_y = (double*)malloc(N0MAX * sizeof(double));

    srand(SEED);

    init(lib_x, lib_y, dep_x, dep_y);

    while (counter != N0MAX) {
        for (j = 0; j < NM; j++) {
            tita = 2 * M_PI * rand() / (double)RAND_MAX;
            gx = cos(tita);
            gy = sin(tita);

            lib_x[j] += Q * gx;
            lib_y[j] += Q * gy + RY;

            lib_x[j] = pbc(lib_x[j], 1);
            lib_y[j] = rbc(lib_y[j], 1);
            for (k = 0; k < counter; k++) {
                distx = lib_x[j] - dep_x[k];
                disty = lib_y[j] - dep_y[k];
                dist2 = pow(distx, 2) + pow(disty, 2);

                if (dist2 < DATT2) {
                    printf("En la iteracion %d entro con la libre %d y el depositado %d al if\n", i, j, k);
                    dist = sqrt(dist2);
                    printf("SIN PBC - Depositado %d en (x;y) = (%f ; %f)\n", k, dep_x[k], dep_y[k]);
                    printf("CON PBC - Depositado %d en (x;y) = (%f ; %f)\n", k, pbc(distx * DATT / dist + dep_x[k], 1), pbc(disty * DATT / dist + dep_y[k], 1));
                    printf("0 - Depositado %d en (x;y) = (%f ; %f)\n", counter, dep_x[counter], dep_y[counter]);
                    dep_x[counter] = pbc(distx * DATT / dist + dep_x[k], 1);
                    dep_y[counter] = pbc(disty * DATT / dist + dep_y[k], 1);
                    printf("1 - Depositado %d en (x;y) = (%f ; %f)\n", counter, dep_x[counter], dep_y[counter]);
                    counter++;
                    printf("Counter = %d\n", counter);
                    lib_x[j] = rand() / (double)RAND_MAX;
                    lib_y[j] = rand() / (double)RAND_MAX;
                }
            }
        }

        i++;
        tSim = i * DT;

        if (i % 2000 == 0) {
            printf(">>> Tiempo simulado: %f s >>> Li depositado: %d\n", tSim, counter);
        }
    }

    end(lib_x, lib_y, dep_x, dep_y, counter, tSim);
    printf("Se alcanzó la cantidad máxima de Li0 (%d) simulando durante %f s\n", counter, tSim);
}
