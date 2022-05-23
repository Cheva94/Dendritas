#pragma once

/*
 * Unidades: MKS - dist: m - tiempo: s
 */

#include <math.h>
#include <time.h>

#ifndef SEED // rand SEED para
// #define SEED (time(NULL))
#define SEED 2022
#endif

#ifndef RLI0 // radio Li0 DISTRIBUYE Y NADA MAS
#define RLI0 1.67E-10
#endif

#ifndef LONG // coef de ¿? /LONG ES PARA NORMALIZAR
#define LONG 16.7E-9 // LARGO DE LA CAJA EN X Y EN Y
#endif

#ifndef DATT // RLI0 / (pi/4) // separación entre litios contiguos
#define DATT 1.3 * RLI0 / LONG
#endif

#ifndef DATT2 // RLI0 / (pi/4)
#define DATT2 pow(DATT, 2)
#endif

#ifndef DT // paso temporal en s - afecta la difusión
#define DT 1.0E-6
#endif

#ifndef D // coef de difusion de Li+ en el electrolito
#define D 1.4E-14
#endif

#ifndef Q // desplazamiento medio debido a la difusión
#define Q sqrt(2.0 * D * DT) / LONG
#endif

#ifndef N0 // cantidad inicial de Li0 depositado en superficie COMPARAR CON lixy_d[idx + 0] = i * 1.3 * RLI0 / LONG; usar el DATT
#define N0 77//(ceil(1/DATT))// 77
#endif

#ifndef NM // cantidad de Li siempre presente en la evol temp
#define NM 50
#endif

#ifndef N0MAX // cantidad máxima de Li0
#define N0MAX 600
#endif

#ifndef RY // desplazamiento medio debido a la difusión
#define RY -1.7E7 * 5.6E-13 * DT / LONG
#endif
