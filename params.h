/*
 * Unidades: MKS - dist: m - tiempo: s
 */

#pragma once

#include <math.h>
#include <time.h>

#ifndef DT // paso temporal en us
#define DT 1.0E-6
#endif

#ifndef N0 // cantidad inicial de Li0 depositado en superficie
#define N0 77
#endif

#ifndef N0MAX // cantidad máxima de Li0
#define N0MAX 600
#endif

#ifndef RLI0 // radio Li0
#define RLI0 1.67E-10
#endif

#ifndef RLIM // radio Li+
#define RLIM 1.2E-10
#endif

#ifndef NM // cantidad de Li siempre presente en la evol temp
#define NM 50
#endif

#ifndef D // coef de difusion de Li+ en el electrolito
#define D 1.4E-14
#endif

#ifndef LONG // coef de ¿?
#define LONG 16.7E-9
#endif

#ifndef DATT // RLI0 / (pi/4)
#define DATT (1.3 * RLI0 / LONG)
#endif

#ifndef Q // desplazamiento medio debido a la difusión
#define Q (sqrt(2.0 * D * DT) / LONG)
#endif

#ifndef DX // Electrolito con iones en X
#define DX (RLI0 / (2.0 * LONG))
#endif

#ifndef DY // Electrolito con iones en Y
#define DY (RLI0 / (2.0 * LONG))
#endif

#ifndef SEED // rand SEED para
#define SEED (time(NULL))
#endif
