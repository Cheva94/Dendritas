// #include "core.h"
#include "params.h"
// #include "wtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * Creo que estoy escribiendo el código de campo cte no nulo (difusión + migracion)
 */

 double pbc(double cordi, const double cell_length)
 {
     // condiciones periodicas de contorno coordenadas entre [0,L) con L=1
     if (cordi <= 0) {
         cordi += cell_length;
     } else if (cordi > cell_length) {
         cordi -= cell_length;
     }
     return cordi;
 }
 
int main()
{
    // 1/5 - Crea el puntero al archivo
    FILE *f_initLi0, *f_endLi0, *f_initLiM, *f_endLiM;

    // 2/5 - Intenta abrir el archivo
    f_initLi0 = fopen("EstadoInicial_Li0.csv", "w");
    f_endLi0 = fopen("EstadoFinal_Li0.csv", "w");
    f_initLiM = fopen("EstadoInicial_LiM.csv", "w");
    f_endLiM = fopen("EstadoFinal_LiM.csv", "w");

    // 3/5 - Corrobora que se hayan abierto los archivos
    if ((f_initLi0 == NULL) || (f_endLi0 == NULL) || (f_initLiM == NULL) || (f_endLiM == NULL)) {
        printf("No se encontró alguno de los archivos.");
        exit(0);
    }

    int i, j, k, l; // Variables mudas
    double tita = 0.0, gx = 0.0, gy = 0.0; // Vector unitario aleatorio
    // En .py aparecen x = y = 0, pero es para plotear ¿?
    // En .py aparecen Rli_mx/y y Rli_0x/y = 0 pero nunca se usan ¿?
    double modd = 0.0; // ¿?

    double *ex, *ey, *ex_0, *ey_0; // vectores espaciales de los iones
    ex = (double*)malloc(NM * sizeof(double));
    ey = (double*)malloc(NM * sizeof(double));
    ex_0 = (double*)malloc(NM * sizeof(double));
    ey_0 = (double*)malloc(NM * sizeof(double));

    double *lix_d, *liy_d; // arreglo de Li depositado sobre al ánodo
    lix_d = (double*)malloc(N0 * sizeof(double));
    liy_d = (double*)malloc(N0 * sizeof(double));

    double *lix_0, *liy_0; // ¿?
    lix_0 = (double*)malloc(N0 * sizeof(double));
    liy_0 = (double*)malloc(N0 * sizeof(double));

    double *lix_aux, *liy_aux; // ¿?
    lix_aux = (double*)malloc(N0MAX * sizeof(double));
    liy_aux = (double*)malloc(N0MAX * sizeof(double));

    // Creación de la monocapa inicial de Li depositado
    for (i = 0; i < N0; i++) {
        lix_d[i] = 1.3 * RLI0 * i / LONG;
        liy_d[i] = 0.0 / LONG;
    }

    // Creación de las posiciones iniciales de los iones en el electrolito
    srand(SEED); // Punto inicial fijo para rand() - reproducibildiad

    for (i = 0; i < NM; i++) { // ¿?
        ex_0[i] = rand() / (double)RAND_MAX;
        ey_0[i] = rand() / (double)RAND_MAX;
        // acá hay un operador modulo 1 que no sé por qué ¿?
    }

    // Guardar coordenadas del sistema inicial. Esto es con fines de graficar
    // ex_init = ex_0
    // ey_init = ey_0
    // ver si conviene hacer un nuevo par de variables, alojar memoria y etc solo para escribir todo de un solo sauqe en un archivo o hacer 4 archivos

    // 4/5 - Escribir en el archivo
    fprintf(f_initLiM, "x, y\n");
    // quizas agrupar este for con el anterior si es que los hago así por separado
    for (i = 0; i < NM; i++) { // ¿?
        fprintf(f_initLiM, "%f, %f\n", ex_0[i], ey_0[i]);
    }

    fprintf(f_initLi0, "x, y\n");
    // quizas agrupar este for con el anterior si es que los hago así por separado
    for (i = 0; i < N0; i++) { // ¿?
        fprintf(f_initLi0, "%f, %f\n", lix_d[i], liy_d[i]);
    }

    // 5/5 - Cierra el archivo al terminar
    fclose(f_initLi0);
    fclose(f_initLiM);

    // Comienza la evolución temporal

    int Li_counter = N0;
    lix_0 = lix_d;
    liy_0 = liy_d;
    int percent = 9, percent_prog;
    // está definido un exys pero solo apendea y no usan
    double distx, disty, dist; // calculo de distancias
    double exs, eys; // escalares para las posiciones ¿?
    double t; // tiempo para la evolucion

    for (i = 0; i < NT; i++) {
        // tiene un break out de i
        for (j = 0; j < NM; j++) {
            // tiene un break out de j
            // Definición del vector unitario
            tita = 2 * M_PI * rand() / (double)RAND_MAX;
            gx = cos(tita);
            gy = sin(tita);
            // Evolución de la posición
            ex[j] = ex_0[j] + Q * gx + RX;
            ey[j] = ey_0[j] + Q * gy + RX;

            // PBC para la caja de tamaño 1x1 normalizada
            ex[j] = pbc(ex[j], 1);
            ey[j] = pbc(ey[j], 1);

            // Definicion de la condicion de neutralización
            for (k = 0; k < Li_counter; k++) {
                if (Li_counter <= N0) {
                    distx = ex[j] - lix_d[k];
                    disty = ey[j] - liy_d[k];
                    dist = sqrt(distx * distx + disty * disty); // Ver si no es mejor escribirlo como potencia en el código intermedio
                }
                else if (Li_counter > N0) {
                    distx = ex[j] - lix_0[k];
                    disty = ey[j] - liy_0[k];
                    dist = sqrt(distx * distx + disty * disty);
                }
                if (dist < DATT) {
                    if (Li_counter <= N0) {
                        modd = sqrt((ex[j] - lix_d[k]) * (ex[j] - lix_d[k]) + (ey[j] - liy_d[k]) * (ey[j] - liy_d[k]));
                        exs = (ex[j] - lix_d[k]) * DATT / modd + lix_d[k];
                        eys = (ey[j] - liy_d[k]) * DATT / modd + liy_d[k];
                    }
                    else if (Li_counter > N0) {
                        modd = sqrt((ex[j] - lix_0[k]) * (ex[j] - lix_0[k]) + (ey[j] - liy_0[k]) * (ey[j] - liy_0[k]));
                        exs = (ex[j] - lix_0[k]) * DATT / modd + lix_0[k];
                        eys = (ey[j] - liy_0[k]) * DATT / modd + liy_0[k];
                    }

                    Li_counter++;

                    if (Li_counter == N0MAX) {
                        printf("Se alcanzó la cantidad máxima de Li0.\n");
                        break; // Sólo sale del loop de partículas, no del temporal
                    }

                    for (l = 0; l < Li_counter; l++) {
                        lix_0[l] = 0;
                        liy_0[l] = 0;
                    }

                    for (l = 0; l < N0; l++) {
                        lix_aux[l] = lix_d[l];
                        liy_aux[l] = liy_d[l];
                    }

                    lix_aux[Li_counter] = exs;
                    liy_aux[Li_counter] = eys;

                    for (l = 0; l < Li_counter; l++) {
                        lix_0[l] = lix_aux[l];
                        liy_0[l] = liy_aux[l];
                    }

                    // PBC
                    for (l = 0; l < Li_counter; l++) {
                        lix_0[l] = pbc(lix_0[l], 1);
                        liy_0[l] = pbc(liy_0[l], 1);
                    }

                    // Repongo el ion
                    ex_0[j] = rand() / (double)RAND_MAX;
                    ey_0[j] = rand() / (double)RAND_MAX;

                    // PBC
                    ex[j] = pbc(ex[j], 1);
                    ey[j] = pbc(ey[j], 1);
                }
            }
        }

        t = (i+1) * DT;
        ex_0 = ex;
        ey_0 = ey;

        // Agrego el pocentaje de corrida del programa
        percent_prog = 100 * i / NT;
        if (percent_prog > percent) {
            if (percent_prog % 10 == 0) {
                printf("Avance del programa = %d\n", percent_prog);
            }
            printf("Paso temporal = %d / %d \n", i, NT);
            percent = percent_prog;
        }

        if (Li_counter == N0MAX) {
            printf("Se alcanzó la cantidad máxima de Li0.\n");
            break; // Sale del loop temporal
        }
    }

    printf("Cantidad de Li0 = %d\n", Li_counter);

    fprintf(f_endLiM, "x, y\n");
    for (i = 0; i < NM; i++) { // ¿?
        fprintf(f_endLiM, "%f, %f\n", ex[i], ey[i]);
    }

    fprintf(f_endLi0, "x, y\n");
    for (i = 0; i < N0; i++) { // ¿?
        fprintf(f_endLi0, "%f, %f\n", lix_0[i], liy_0[i]);
    }

    // 5/5 - Cierra el archivo al terminar
    fclose(f_endLi0);
    fclose(f_endLiM);

    // 1/5 - Crea el puntero al archivo
    FILE *f_params;

    // 2/5 - Intenta abrir el archivo
    f_params = fopen("Parametros.csv", "w");

    // 3/5 - Corrobora que se hayan abierto los archivos
    if (f_params == NULL) {
        printf("No se encontró el archivo.");
        exit(0);
    }

    // 4/5 - Escribir en el archivo
    fprintf(f_params, "Parámetro, Valor, Unidad\n");
    fprintf(f_params, "Paso temporal, %f, us\n", DT);
    fprintf(f_params, "Cantidad de pasos temporales, %d, \n", NT);
    fprintf(f_params, "Li+ siempre presente, %d, \n", NM);
    fprintf(f_params, "Li0 inicial, %d, \n", N0);
    fprintf(f_params, "Li0 máximo, %d, \n", N0MAX);
    fprintf(f_params, "Li0 alcanzado, %d, \n", Li_counter);
    fprintf(f_params, "Tiempo simulado, %f, us\n", t);

    // 5/5 - Cierra el archivo al terminar
    fclose(f_params);
}
