#include <stdio.h>
#include "bomb.h"

#define PHASE(N) doPhase("Senha " #N ": ", phase##N, ok_messages[N - 1])

void doPhase(const char * prompt, int (*phase)(char *), const char * okmsg) {
	char line[256];

	fputs(prompt, stdout);
	if (!fgets(line, sizeof(line), stdin)) {
		puts("Adeus.");
		exit(0);
	}
	line[strlen(line) - 1] = 0;

	if (phase(line))
		puts(okmsg);
	else
		explode_bomb();
}

int main(int argc, char * argv[]) {

	bomb_setup();
	
	PHASE(1);
	PHASE(2);
	PHASE(3);
	PHASE(4);

	return 0;
}

