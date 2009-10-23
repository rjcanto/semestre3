#include "bomb.h"

char * readInteger(char * line, int * dst) {
	int dig, num = 0, ndig = 0;
	for (;;) {
		dig = line[ndig] - '0';
		if (dig < 0 || dig > 9) break;
		num = num * 10 + dig;
		++ndig;
	}
	*dst = num;
	return ndig ? line + ndig : NULL;
}

