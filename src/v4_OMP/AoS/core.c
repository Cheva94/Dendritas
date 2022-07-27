#include "params.h"
#include "xoshiro.h"
#include "core.h"
#include "wtime.h"

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <omp.h>

void init(float* lib, float* dep)
{
    int i, idx = 0;

    FILE *f_initLib;
    f_initLib = fopen("Est0_Lib.csv", "w");

    for (i = 0; i < 2 * NL; i += 2) {
        *(lib + i) = LX * next() / (float)NEXT_MAX;
        *(lib + i + 1) = 2 - (2 - LY) * next() / (float)NEXT_MAX;
    }

    fprintf(f_initLib, "x, y\n");
    for (i = 0; i < 2 * NL; i += 2) {
        fprintf(f_initLib, "%f, %f\n", *(lib + i), *(lib + i + 1));
    }
    fclose(f_initLib);

    FILE *f_initDep;
    f_initDep = fopen("Est0_Dep.csv", "w");

    for (i = 0; i < ND; i++) {
        *(dep + idx) = DAT * i;
        idx += 2;
    }

    fprintf(f_initDep, "x, y\n");
    for (i = 0; i < 2 * ND; i += 2) {
        fprintf(f_initDep, "%f, %f\n", *(dep + i), *(dep + i + 1));
    }
    fclose(f_initDep);
}

float pbc(float x) // flops = 2
{
    if (x < 0) {
        x += LX; // sum
    } else if (x > LX) {
        x -= LX; // res
    }
    return x;
}

float rbc(float y) // flop = 3
{
    if (y < 0) {
        y = fabs(y); // abs
    } else if (y > LY) {
        y = 2 * LY - y; // mul res
    }
    return y;
}

void move(float* lib)
{
    float tita, gx, gy;

    for (unsigned int i = 0; i < 2 * NL; i += 2) {
        tita = 2 * M_PI * next() / (float)NEXT_MAX;

        gx = cos(tita);
        *(lib + i) += Q * gx;
        *(lib + i) = pbc(*(lib + i));

        gy = sin(tita);
        *(lib + i + 1) += Q * gy;
        *(lib + i + 1) = rbc(*(lib + i + 1));
    }
}

float update(float* lib, float* dep, unsigned int* count, unsigned int* countAux)
{
    double startUP = wtime();
    float flop = 0.0f;
    float partialFlop = 0.0f;

    #pragma omp parallel for firstprivate(partialFlop) reduction(+:flop)

    for (unsigned int j = 0; j < 2 * NL; j += 2) {
        float xj = *(lib + j);
        float yj = *(lib + j + 1);

        for (unsigned int k = 0; k < 2 * (*count); k += 2) {
            float xk = *(dep + k);
            float yk = *(dep + k + 1);

            float distx = xj - xk; // 1
            float disty = yj - yk; // 1

            float dist2 = distx * distx + disty * disty; // 3

            if (dist2 < DAT2) { // 1
                float dist = sqrt(dist2); // 1


                *(dep + 2 * (*count)) = pbc(distx * DAT / dist + *(dep + k)); // 5
                *(dep + 2 * (*count) + 1) = rbc(disty * DAT / dist + *(dep + k + 1)); // 6

                *(lib + j) = LX * next() / (float)NEXT_MAX; // 2
                *(lib + j + 1) = LY * (0.1 * next() / (float)NEXT_MAX + 0.9); // 4

                *countAux += 1;
                partialFlop += 24;
            } else {
                partialFlop += 6;
            }
        }
        flop += partialFlop;
    }
    return flop / (wtime() - startUP);
}

void end(float* lib, float* dep, float tSim, double wall, float* pflops)
{
    int i;

    FILE *f_endDep;
    f_endDep = fopen("Est1_Dep.csv", "w");

    fprintf(f_endDep, "x, y\n");
    for (i = 0; i < 2 * NMAX; i += 2) {
        fprintf(f_endDep, "%f, %f\n", *(dep + i), *(dep + i + 1));
    }
    fclose(f_endDep);

    FILE *f_endLib;
    f_endLib = fopen("Est1_Lib.csv", "w");

    fprintf(f_endLib, "x, y\n");
    for (i = 0; i < 2 * NL; i += 2) {
        fprintf(f_endLib, "%f, %f\n", *(lib + i), *(lib + i + 1));
    }
    fclose(f_endLib);

    FILE *f_params;
    f_params = fopen("Parametros.csv", "w");

    fprintf(f_params, "Parámetro >>> Valor\n");
    fprintf(f_params, "Li libre siempre presente >>> %d\n", NL);
    fprintf(f_params, "Li depositado inicial >>> %d\n", ND);
    fprintf(f_params, "Li depositado final >>> %d\n", NMAX);
    fprintf(f_params, "Paso temporal >>> %f ms\n", DT);
    fprintf(f_params, "Separación entre Li >>> %f nm\n", DAT);
    fprintf(f_params, "Longitud de celda en x >>> %f nm\n", LX);
    fprintf(f_params, "Longitud de celda en y >>> %f nm\n", LY);
    fprintf(f_params, "Coeficiente de difusión >>> %d nm^2/s\n", D);
    fprintf(f_params, "Tiempo simulado >>> %.3f ms\n", tSim);
    fprintf(f_params, "WALL TIME >>> %.6f s\n", wall);
    fprintf(f_params, "PFLOPS >>> %f\n", *pflops);
    fclose(f_params);
}
