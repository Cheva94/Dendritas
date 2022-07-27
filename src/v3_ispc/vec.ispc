#include "params.h"

static inline uint32 rotl(const uint32 x, int k) {
	return (x << k) | (x >> (32 - k));
}

static uint32 s[4];

uint32 next() {
	const uint32 result = s[0] + s[3];

	const uint32 t = s[1] << 9;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;

	s[3] = rotl(s[3], 11);

	return result;
}


/* This is the jump function for the generator. It is equivalent
   to 2^64 calls to next(); it can be used to generate 2^64
   non-overlapping subsequences for parallel computations. */

void jump() {
	static const uint32 JUMP[] = { 0x8764000b, 0xf542d2d3, 0x6fa035c3, 0x77f2db5b };

	// uint32 s0 = 0;
	// uint32 s1 = 0;
	// uint32 s2 = 0;
	// uint32 s3 = 0;
	uint32 s0 = 1;
	uint32 s1 = 2;
	uint32 s2 = 3;
	uint32 s3 = 4;
	// for(int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
	for(uint32 i = 0; i < sizeof JUMP / sizeof JUMP[0]; i++)
		for(int b = 0; b < 32; b++) {
			if (JUMP[i] & 1U << b) {
				s0 ^= s[0];
				s1 ^= s[1];
				s2 ^= s[2];
				s3 ^= s[3];
			}
			next();
		}

	s[0] = s0;
	s[1] = s1;
	s[2] = s2;
	s[3] = s3;
}

static float pbc(float x)
{
	if (x < 0) {
        x += LX; // sum
    } else if (x > LX) {
        x -= LX; // res
    }
    return x;
}

static float rbc(float y)
{
	if (y < 0) {
        y = abs(y); // abs
    } else if (y > LY) {
        y = 2 * LY - y; // mul res
    }
    return y;
}

export uniform float dist(uniform float* uniform lib, uniform float* uniform dep, uniform int* uniform count, uniform int* uniform countAux, uniform const int j)
{
    float flop = 0.0f;
    int sum = 0;

	uniform float xj = *(lib + j);
    uniform float yj = *(lib + j + NL);

    foreach(k = 0 ... (*count)) {
		float xk = *(dep + k);
	    float yk = *(dep + k + NMAX);

		float distx = xj - xk;
		float disty = yj - yk;

		float dist2 = distx * distx + disty * disty;

        if (dist2 < DAT2) {
            float dist = sqrt(dist2);

            *(dep + k) = pbc(distx * DAT / dist + xk);
            *(dep + k + (*count) + NMAX) = rbc(disty * DAT / dist + yk);

            *(lib + k) = LX * next() / FNEXT_MAX;
            *(lib + k + (*count) + NL) = LY * (0.1 * next() / FNEXT_MAX + 0.9);

            sum += 1;
            flop += 24;
        } else {
            flop += 6;
        }
    }

    *countAux = reduce_add(sum);
    return reduce_add(flop);
}
