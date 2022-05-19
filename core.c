#include "core.h"
#include "params.h"
// #include "wtime.h"

// #include <math.h>
// #include <stdlib.h> // rand()

// static double pbc(double cordi, const double cell_length)
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
