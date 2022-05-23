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

void end(double* lib, double* dep, int count, double tSim)
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
    fprintf(f_params, "Li0 alcanzado >>> %d \n", count);
    fprintf(f_params, "Tiempo simulado >>> %f s\n", tSim);

    fclose(f_endDep);
    fclose(f_endLib);
    fclose(f_params);
}

int main()
{
    int i = 0, j, k;
    // int n0 = ceil(1/DATT);
    int count = N0;
    double tita, gx, gy;
    double distx, disty, dist, dist2;
    double tSim;
    double *lib, *dep;

    lib = (double*)malloc(2 * NM * sizeof(double));
    dep = (double*)malloc(2 * N0MAX * sizeof(double));

    srand(SEED);

    init(lib, dep);

    while (count != N0MAX) {
        for (j = 0; j < 2 * NM; j += 2) {
            tita = 2 * M_PI * rand() / (double)RAND_MAX;
            gx = cos(tita);
            gy = sin(tita);

            *(lib + j + 0) += Q * gx;
            *(lib + j + 1) += Q * gy + RY;

            *(lib + j + 0) = pbc(*(lib + j + 0), 1);
            *(lib + j + 1) = rbc(*(lib + j + 1), 1);

            for (k = 0; k < 2 * count; k += 2) {
                distx = *(lib + j + 0) - *(dep + k + 0);
                disty = *(lib + j + 1) - *(dep + k + 1);
                dist2 = pow(distx, 2) + pow(disty, 2);

                if (dist2 < DATT2) {
                    dist = sqrt(dist2);

                    *(dep + 2 * count + 0) = pbc(distx * DATT / dist + *(dep + k + 0), 1);
                    *(dep + 2 * count + 1) = pbc(disty * DATT / dist + *(dep + k + 1), 1);

                    count++;

                    *(lib + j + 0) = rand() / (double)RAND_MAX;
                    *(lib + j + 1) = rand() / (double)RAND_MAX;
                }
            }
        }

        i++;
        tSim = i * DT;

        if (i % 2000 == 0) {
            printf(">>> Tiempo simulado: %f s >>> Li depositado: %d\n", tSim, count);
        }
    }

    end(lib, dep, count, tSim);
    printf("Se alcanzó la cantidad máxima de Li0 (%d) simulando durante %f s\n", count, tSim);
}
