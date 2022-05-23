#include "core.h"
#include "params.h"
// #include "wtime.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h> // rand()

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

void init(double* lib, double* dep)
{
    int i, idx = 0;

    for (i = 0; i < 2 * NM; i += 2) {
        *(lib + i + 0) = rand() / (double)RAND_MAX;
        *(lib + i + 1) = rand() / (double)RAND_MAX;
    }

    for (i = 0; i < N0; i++) {
        *(dep + idx + 0) = i * DATT;
        idx += 2;
    }

    FILE *f_initDep, *f_initLib;
    f_initDep = fopen("Est0_Dep.csv", "w");
    f_initLib = fopen("Est0_Lib.csv", "w");

    fprintf(f_initDep, "x, y\n");
    for (i = 0; i < 2 * N0; i += 2) {
        fprintf(f_initDep, "%f, %f\n", *(dep + i + 0), *(dep + i + 1));
    }

    fprintf(f_initLib, "x, y\n");
    for (i = 0; i < 2 * NM; i += 2) {
        fprintf(f_initLib, "%f, %f\n", *(lib + i + 0), *(lib + i + 1));
    }

    fclose(f_initDep);
    fclose(f_initLib);
}

void end(double* lib, double* dep, int* count, double tSim)
{
    int i;

    FILE *f_endDep, *f_endLib, *f_params;

    f_endDep = fopen("Est1_Dep.csv", "w");
    f_endLib = fopen("Est1_Lib.csv", "w");
    f_params = fopen("Parametros.csv", "w");

    fprintf(f_endDep, "x, y\n");
    for (i = 0; i < 2 * N0MAX; i += 2) {
        fprintf(f_endDep, "%f, %f\n", *(dep + i + 0), *(dep + i + 1));
    }

    fprintf(f_endLib, "x, y\n");
    for (i = 0; i < 2 * NM; i += 2) {
        fprintf(f_endLib, "%f, %f\n", *(lib + i + 0), *(lib + i + 1));
    }

    fprintf(f_params, "Parámetro >>> Valor\n");
    fprintf(f_params, "Radio del Li >>> %f m\n", RLI0);
    fprintf(f_params, "Longitud de celda >>> %f m\n", LONG);
    fprintf(f_params, "Separación interLi (norm) >>> %f \n", DATT);
    fprintf(f_params, "Paso temporal >>> %f s\n", DT);
    fprintf(f_params, "Coef Dif >>> %f \n", D);
    fprintf(f_params, "Li0 inicial >>> %d \n", N0);
    fprintf(f_params, "Li+ siempre presente >>> %d, \n", NM);
    fprintf(f_params, "Li0 máximo >>> %d \n", N0MAX);
    fprintf(f_params, "Li0 alcanzado >>> %d \n", *count);
    fprintf(f_params, "Tiempo simulado >>> %f s\n", tSim);

    fclose(f_endDep);
    fclose(f_endLib);
    fclose(f_params);
}

void neutral(double* lib, double* dep, int* count, const int j)
{
    double distx, disty, dist, dist2;

    for (int k = 0; k < 2 * (*count); k += 2) {
        distx = *(lib + j + 0) - *(dep + k + 0);
        disty = *(lib + j + 1) - *(dep + k + 1);
        dist2 = pow(distx, 2) + pow(disty, 2);

        if (dist2 < DATT2) {
            dist = sqrt(dist2);

            *(dep + 2 * (*count) + 0) = pbc(distx * DATT / dist + *(dep + k + 0), 1);
            *(dep + 2 * (*count) + 1) = rbc(disty * DATT / dist + *(dep + k + 1), 1);

            *count += 1;

            *(lib + j + 0) = rand() / (double)RAND_MAX;
            *(lib + j + 1) = rand() / (double)RAND_MAX;
        }
    }
}

void move(double* lib, double* dep, int* count)
{
    double tita, gx, gy;

    for (int j = 0; j < 2 * NM; j += 2) {
        tita = 2 * M_PI * rand() / (double)RAND_MAX;
        gx = cos(tita);
        gy = sin(tita);

        *(lib + j + 0) += Q * gx;
        *(lib + j + 1) += Q * gy;// + RY;

        *(lib + j + 0) = pbc(*(lib + j + 0), 1);
        *(lib + j + 1) = rbc(*(lib + j + 1), 1);

        neutral(lib, dep, count, j);
    }
}
