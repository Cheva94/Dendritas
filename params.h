#pragma once

#include <math.h>
#include <time.h>

#ifndef SEED
// #define SEED (time(NULL))
#define SEED 2022
#endif

#ifndef DAT // separación entre litios contiguos (en um) - Radio de Li0 = 1.67E-4 um
#define DAT 1.3 * 1.67E-4
#endif

#ifndef DAT2
#define DAT2 pow(DAT, 2)
#endif

#ifndef DT // paso temporal en ms
#define DT 1.0E-3
#endif

#ifndef D // coeficiente de difusion de Li+ en el electrolito, en um^2/ms
#define D 1.4E-5
#endif

#ifndef Q // desplazamiento medio debido a la difusión en um
#define Q sqrt(2.0 * D * DT)
#endif

#ifndef ND // cantidad inicial de Li depositado
#define ND 500
#endif

#ifndef NL // cantidad de Li+ siempre presente
#define NL 100
#endif

#ifndef LX // largo de la caja en x, en um
#define LX 1.0855E-1
#endif

#ifndef LY // largo de la caja en y, en um
#define LY 1.7368E-2
#endif

#ifndef NMAX // cantidad máxima de Li a depositar
#define NMAX 1500
#endif
