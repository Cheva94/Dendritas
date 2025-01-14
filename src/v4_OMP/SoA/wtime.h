#pragma once

#include <time.h>

// Graba la hora actual de la computadora al momento de la llamada. 
static double wtime(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

	return 1e-9 * ts.tv_nsec + (double)ts.tv_sec;
}
