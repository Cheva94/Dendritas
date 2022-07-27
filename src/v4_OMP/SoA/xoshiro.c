static inline unsigned int rotl(const unsigned int x, int k) {
	return (x << k) | (x >> (32 - k));
}

static unsigned int s[4];

unsigned int next(void) {
	const unsigned int result = s[0] + s[3];

	const unsigned int t = s[1] << 9;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;

	s[3] = rotl(s[3], 11);

	return result;
}

void jump(void) {
	static const unsigned int JUMP[] = { 0x8764000b, 0xf542d2d3, 0x6fa035c3, 0x77f2db5b };

	unsigned int s0 = 1;
	unsigned int s1 = 2;
	unsigned int s2 = 3;
	unsigned int s3 = 4;

	for(unsigned int i = 0; i < sizeof JUMP / sizeof JUMP[0]; i++)
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
