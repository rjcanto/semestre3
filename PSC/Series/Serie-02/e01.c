/**
 * Segunda série de exercícios – Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 * Exercicio 1:
 * Realize um programa de teste em C que lê valores em hexadecimal do standard input 
 * e os apresenta no standard output com a outra representação.
 * 
 * A função
 *		unsigned int xend(unsigned int val);
 * converte um valor a 32 bits de formato big-endian para little-endian ou vice-versa.
 * 
 * Neste teste introduzimos um teste para saber se o sistema funciona como
 * big-endian ou little endian:
 * 		guardamos o valor 1 num unsigned int. O primeiro ou último byte serão 1 e o 
 * 		resto 0. Verificamos qual o caracter que está no primeiro byte do mesmo (primeiro char). 
 * 		Se for 1 então é porque o sistema é little-endian. Senão vamos verificar se o último é 1
 * 		usando a função sizeof().
 */ 

#include <stdio.h>
#include <stdlib.h>

unsigned int xend(unsigned int val);

int main() {
	unsigned int number = 1;
	char *p;
	int type;		/* 0 -> Little Endian - 1-> Big Endian*/
	
	/* testar o sistema para verificar tipo*/
	p = (char*)&number;
	if (*p == 1)
		type=0;
	else if (*(p + sizeof(int) - 1) == 1)
		type=1;

	puts("Introduza um inteiro a 32 bits no seu formato hexadecimal:");
	scanf("%x", &number);
	
	if(type == 0)
		puts("Este sistema é Little Endian:");
	else
		puts("Este sistema é Big Endian:");
	
	printf("0x%08x\n", number);
	number=xend(number);

	if(type == 0)
		puts("Se fosse Big Endian ficaria:");
	else
		puts("Se fosse Little Endian ficaria:");
	printf("0x%08x\n", number);

	return 0 ;
}
