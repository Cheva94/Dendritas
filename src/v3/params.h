#pragma once

#ifndef ISPC
#include <math.h>
#endif

// Normalización de RNG
#ifndef NEXT_MAX
#define NEXT_MAX 4294967295U
#endif

// Separación entre litios contiguos [nm]
#ifndef DAT
#define DAT 0.167 * 1.3
#endif

#ifndef DAT2
#define DAT2 DAT * DAT
#endif

// Paso temporal [ms]
#ifndef DT
#define DT 1.0E-3
#endif

// Coeficiente de difusion de Li+ en el electrolito [nm^2/ms]
#ifndef D
#define D 14
#endif

// Desplazamiento medio debido a la difusión [nm]
#ifndef Q
#define Q sqrt(DT * D * 2.0)
#endif

// Cantidad inicial de Li depositado
#ifndef ND
#define ND 1000
#endif

// Largo de la caja en x [nm]
#ifndef LX
#define LX DAT * ND
#endif

// Largo de la caja en y [nm]
#ifndef LY
#define LY 0.16 * DAT * ND
#endif

// Cantidad de Li+ siempre presente
#ifndef NL
#define NL 758 // ceil(7.584E-4 * ND * ND))
#endif

// Cantidad máxima de Li depositados
#ifndef NMAX
#define NMAX 4000
#endif
