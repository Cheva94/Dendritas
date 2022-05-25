#include "core.h"
#include "params.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void init(double* lib, double* dep)
{
    int i, idx = 0;

    FILE *f_initLib;
    f_initLib = fopen("Est0_Lib.csv", "w");

    for (i = 0; i < 2 * NM; i += 2) { // NM it
        *(lib + i + 0) = LONG * rand() / (double)RAND_MAX; // prod div >> 2
        *(lib + i + 1) = LONG * rand() / (double)RAND_MAX; // prod div >> 2
    } // flop = 4 * NM

    fprintf(f_initLib, "x, y\n");
    for (i = 0; i < 2 * NM; i += 2) {
        fprintf(f_initLib, "%f, %f\n", *(lib + i + 0), *(lib + i + 1));
    }
    fclose(f_initLib);

    FILE *f_initDep;
    f_initDep = fopen("Est0_Dep.csv", "w");

    for (i = 0; i < N0; i++) { // N0 it
        *(dep + idx + 0) = i * DATT; // prod >> 1
        idx += 2; // sum >> 1
    } // flop = 2 * N0

    fprintf(f_initDep, "x, y\n");
    for (i = 0; i < 2 * N0; i += 2) {
        fprintf(f_initDep, "%f, %f\n", *(dep + i + 0), *(dep + i + 1));
    }
    fclose(f_initDep);
} // flop = 4 * NM + 2 * N0

double pbc(double coord, const double cell_length)
{
    if (coord < 0) {
        coord += cell_length; // sum >> 1
    } else if (coord > cell_length) {
        coord -= cell_length; // res >> 1
    }
    return coord;
} // flop = 2

double rbc(double coord, const double cell_length)
{
    if (coord < 0) {
        coord = fabs(coord); // abs >> 1
    } else if (coord > cell_length) {
        coord = 2 * cell_length - coord; // mul res >> 2
    }
    return coord;
} // flop = 3

void neutral(double* lib, double* dep, int* count, const int j, int* flopGral, int* flopNeu)
{
    double distx, disty, dist, dist2;

    for (int k = 0; k < 2 * (*count); k += 2) { // count it
        distx = *(lib + j + 0) - *(dep + k + 0); // res >> 1
        disty = *(lib + j + 1) - *(dep + k + 1); // res >> 1
        dist2 = pow(distx, 2) + pow(disty, 2); // pow sum >> 3

        (*flopGral) += 6;
        (*flopNeu) += 6;

        if (dist2 < DATT2) { // comp >> 1
            dist = sqrt(dist2); // sqrt >> 1

            *(dep + 2 * (*count) + 0) = pbc(distx * DATT / dist + *(dep + k + 0), LONG); // mul div sum pbc >> 5
            *(dep + 2 * (*count) + 1) = rbc(disty * DATT / dist + *(dep + k + 1), LONG); // mul div sum rbc >> 6

            *count += 1; // sum >> 1

            *(lib + j + 0) = LONG * rand() / (double)RAND_MAX; // prod div >> 2
            *(lib + j + 1) = LONG * rand() / (double)RAND_MAX; // prod div >> 2

            (*flopGral) += 17;
            (*flopNeu) += 17;
        } // flop dentro del if = 17
    } // flop hasta el if (incluido) = count * 6
} // flop = count * 6 + if * 17

void move(double* lib, double* dep, int* count, int* flopGral, int* flopNeu)
{
    double tita, gx, gy;

    for (int j = 0; j < 2 * NM; j += 2) { // NM it
        tita = 2 * M_PI * rand() / (double)RAND_MAX; // prod div >> 3
        gx = cos(tita); // cos >> 1
        gy = sin(tita); // sin >> 1

        *(lib + j + 0) += Q * gx; // prod sum >> 2
        *(lib + j + 1) += Q * gy; // prod sum >> 2

        *(lib + j + 0) = pbc(*(lib + j + 0), LONG); // pbc >> 2
        *(lib + j + 1) = rbc(*(lib + j + 1), LONG); // rbc >> 3

        (*flopGral) += 14;

        // neutral(lib, dep, count, j); // count * 6 + if * 17
        neutral(lib, dep, count, j, flopGral, flopNeu); // count * 6 + if * 17
    }
} // flop = NM * (14 + count * 6 + if * 17)

void end(double* lib, double* dep, int* count, double tSim)
{
    int i;

    FILE *f_endDep;
    f_endDep = fopen("Est1_Dep.csv", "w");

    fprintf(f_endDep, "x, y\n");
    for (i = 0; i < 2 * N0MAX; i += 2) {
        fprintf(f_endDep, "%f, %f\n", *(dep + i + 0), *(dep + i + 1));
    }
    fclose(f_endDep);

    FILE *f_endLib;
    f_endLib = fopen("Est1_Lib.csv", "w");

    fprintf(f_endLib, "x, y\n");
    for (i = 0; i < 2 * NM; i += 2) {
        fprintf(f_endLib, "%f, %f\n", *(lib + i + 0), *(lib + i + 1));
    }
    fclose(f_endLib);

    FILE *f_params;
    f_params = fopen("Parametros.csv", "w");

    fprintf(f_params, "Parámetro >>> Valor\n");
    fprintf(f_params, "Radio del Li >>> %f m\n", RLI);
    fprintf(f_params, "Longitud de celda >>> %f m\n", LONG);
    fprintf(f_params, "Separación interLi (norm) >>> %f \n", DATT);
    fprintf(f_params, "Paso temporal >>> %f s\n", DT);
    fprintf(f_params, "Coef Dif >>> %f \n", D);
    fprintf(f_params, "Li0 inicial >>> %d \n", N0);
    fprintf(f_params, "Li+ siempre presente >>> %d, \n", NM);
    fprintf(f_params, "Li0 máximo >>> %d \n", N0MAX);
    fprintf(f_params, "Li0 alcanzado >>> %d \n", *count);
    fprintf(f_params, "Tiempo simulado >>> %f s\n", tSim);
    fclose(f_params);
}