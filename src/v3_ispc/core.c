#include "params.h"
#include "vec.h"
#include "core.h"
#include "wtime.h"

#include <stdio.h>
#include <math.h>
#include <stdint.h>

void init(float* lib, float* dep)
{
    int i, idx = 0;

    FILE *f_initLib;
    f_initLib = fopen("Est0_Lib.csv", "w");

    for (i = 0; i < NL; i++) {
        *(lib + i) = LX * next() / (float)NEXT_MAX;
        *(lib + i + NL) = 2 - (2 - LY) * next() / (float)NEXT_MAX;
    }

    fprintf(f_initLib, "x, y\n");
    for (i = 0; i < NL; i++) {
        fprintf(f_initLib, "%f, %f\n", *(lib + i), *(lib + i + NL));
    }
    fclose(f_initLib);

    FILE *f_initDep;
    f_initDep = fopen("Est0_Dep.csv", "w");

    for (i = 0; i < ND; i++) {
        *(dep + idx) = DAT * i;
        idx++;
    }

    fprintf(f_initDep, "x, y\n");
    for (i = 0; i < ND; i++) {
        fprintf(f_initDep, "%f, %f\n", *(dep + i), *(dep + i + ND));
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

    for (unsigned int i = 0; i < NL; i++) {
        tita = 2 * M_PI * next() / (float)NEXT_MAX;

        gx = cos(tita);
        *(lib + i) += Q * gx;
        *(lib + i) = pbc(*(lib + i));

        gy = sin(tita);
        *(lib + i + NL) += Q * gy;
        *(lib + i + NL) = rbc(*(lib + i + NL));
    }
}

float update(float* lib, float* dep, unsigned int* count, unsigned int* countAux)
{
    double startUP = wtime();
    float flop = 0.0f;

    for (unsigned int j = 0; j < NL; j++) {
        flop += dist(lib, dep, count, countAux, j);

        if (((*count) + (*countAux)) > NMAX) {
            break;
        }
    }
    return flop / (wtime() - startUP);
}

void end(float* lib, float* dep, float tSim, double wall, float* pflops)
{
    int i;

    FILE *f_endDep;
    f_endDep = fopen("Est1_Dep.csv", "w");

    fprintf(f_endDep, "x, y\n");
    for (i = 0; i < NMAX; i++) {
        fprintf(f_endDep, "%f, %f\n", *(dep + i), *(dep + i + NMAX));
    }
    fclose(f_endDep);

    FILE *f_endLib;
    f_endLib = fopen("Est1_Lib.csv", "w");

    fprintf(f_endLib, "x, y\n");
    for (i = 0; i < NL; i++) {
        fprintf(f_endLib, "%f, %f\n", *(lib + i), *(lib + i + NL));
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
