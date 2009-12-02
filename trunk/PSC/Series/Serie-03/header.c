/**
 * Terceira série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 */
#include <stdio.h>
#include "imageFormat.h"
#include "myLib.h"
/*
 * Processa multiplos ficheiros de entrada. Necessita de pelo menos 1.
 * */
int main(int argc, char *argv[]) {
    header fhp;
    int nbrChars=0;
    if (argc == 1) {
        puts("Need at least one argument to be processed!");
        return UNSUCCESS;
    }
    while ((argc-1) > 0) {
        argc--;
		nbrChars=processFileHeader(argv[argc],&fhp);
		listfileHeader(argv[argc],&fhp,nbrChars);	
    }

return SUCCESS;
}
