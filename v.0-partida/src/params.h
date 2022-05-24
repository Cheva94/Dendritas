#pragma once

#include <math.h>
#include <time.h>

#ifndef SEED
// #define SEED (time(NULL))
#define SEED 2022
#endif

#ifndef RLI // radio del Li en um
#define RLI 1.67E-4
#endif

#ifndef LONG // largo de la caja en um
#define LONG 1.67E-2
#endif

#ifndef DATT // separación entre litios contiguos en um
#define DATT 1.3 * RLI
#endif

#ifndef DATT2
#define DATT2 pow(DATT, 2)
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

#ifndef N0 // cantidad inicial de Li depositado sobre la longtiud LONG
#define N0 77
#endif

#ifndef NM // cantidad de Li+ siempre presente sobre la longtiud LONG
#define NM 50
#endif

#ifndef N0MAX // cantidad máxima de Li a depositar sobre la longtiud LONG
#define N0MAX 600
#endif

#ifndef N02 // cantidad inicial de Li depositado sobre la longtiud LONG
#define N02 pow(N0, 2)
#endif

#ifndef N0MAX2 // cantidad inicial de Li depositado sobre la longtiud LONG
#define N0MAX2 pow(N0MAX, 2)
#endif

#ifndef NM2 // cantidad inicial de Li depositado sobre la longtiud LONG
#define NM2 pow(NM, 2)
#endif
