/*
 * Unidades: MKS - dist: m - tiempo: s
 */

#pragma once

#include <math.h>
#include <time.h>

#ifndef DT // paso temporal en us
#define DT 1.0E-6
#endif

#ifndef NT // cantidad de pasos temporales
#define NT 2400//8000
#endif

#ifndef N0 // cantidad inicial de Li0 depositado en superficie
#define N0 3 //77
#endif

#ifndef NM // cantidad de Li siempre presente en la evol temp
#define NM 5 //50
#endif

#ifndef N0MAX // cantidad máxima de Li0
#define N0MAX 10//600
#endif

#ifndef RLI0 // radio Li0
#define RLI0 1.67E-10
#endif

#ifndef RLIM // radio Li+
#define RLIM 1.2E-10
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

#ifndef MU // permitividad ¿?
#define MU 5.6E-13
#endif

#ifndef E0_X // campo eléctrico en X ¿?
#define E0_X 0.0
#endif

#ifndef E0_Y // campo eléctrico en Y ¿?
#define E0_Y -1.7E7
#endif

#ifndef RX // desplazamiento debido al campo en X ¿?
#define RX (MU * E0_X * DT / LONG)
#endif

#ifndef RY // desplazamiento debido al campo en Y ¿?
#define RY (MU * E0_Y * DT / LONG)
#endif

#ifndef DX // Electrolito con iones en X
#define DX (RLI0 / (2.0 * LONG))
#endif

#ifndef DY // Electrolito con iones en Y
#define DY (RLI0 / (2.0 * LONG))
#endif

#ifndef SEED // rand SEED para
// #define SEED (time(NULL))
#define SEED 2021
#endif
