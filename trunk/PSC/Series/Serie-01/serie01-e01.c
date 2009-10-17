/**
 * Primeira série de exercícios – Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 * Exercicio 1:
 * São utilizadas duas funções:
 * -> getlong() que retorna um inteiro (long) introduzido pelo utilizador.
 * -> minsize(long val) que recebendo um inteiro retorna o numero de bytes
 * minimo necessário para representar o numero.
 * 
 * Estratégia de resolução:
 * -> Verifica-se se o numero recebido é negativo. Esta abordagem tem dois
 * propositos, usa o sinal do numero para retornar o resultado e usa o 
 * mesmo sinal para tornar o numero simétrico (caso seja negativo).
 * -> Utiliza-se uma mascara, na qual se vai deslocando para a direita 
 * uma posição, para encontrar o bit de maior peso a 'UM'. Uma vez 
 * encontrado o bit actualiza-se o indicie.
 * ->No fim retorna o indicie do bit de maior peso multiplicando pelo 
 * numero de BITS do CHAR. Para tal usou-se a Biblioteca limits.h para 
 * obter o valor CHAR_BIT. Em alternativa podia-se ter utilizado o valor
 * constante 8 como forma de obter o byte.
 */ 

#include <stdio.h>
#include <limits.h>


int minsize(long val) {
	int signal=(val<0)?-1:1;
	int bits=0;
	int i=0;
	int mask=0x01;
	if (val==0) return -1;

	if(signal==-1)++i;
			while(mask!=0){
				++i;
				if (!(mask&val)&&(signal==-1))
					bits=i;
				else if ((mask&val)&&(signal!=-1))
					bits=i;
			mask<<=1;
	}
	return signal*((bits%CHAR_BIT)?bits/CHAR_BIT + 1:bits/CHAR_BIT);
}

long getlong(){
	
	int c=getchar();
	int signal=(c == '-')?-1:1;
	long number= (signal != -1)?c-'0':0;

	while ((c=getchar())>='0' && c <='9'){
		number=number*10 +(c-'0');
	}
	return signal*number;
}
void printRange(long val){

	if (val>= CHAR_MIN && val <= CHAR_MAX)
		puts("O valor pode ser colocado num signed char!");
	
	if (val>= 0 && val <= UCHAR_MAX)
		puts("O valor pode ser colocado num unsigned char!");

	if (val>= SHRT_MIN && val <= SHRT_MAX)
		puts("O valor pode ser colocado num signed short!");

	if (val>= 0 && val <= USHRT_MAX)
		puts("O valor pode ser colocado num unsigned short!");

	if (val>= INT_MIN && val <= INT_MAX)
		puts("O valor pode ser colocado num signed int!");

	if (val>= 0 && val <= UINT_MAX)
		puts("O valor pode ser colocado num unsigned int!");

	if (val>= LONG_MIN && val <= LONG_MAX)
		puts("O valor pode ser colocado num signed long!");

	if (val>= 0 && val <= ULONG_MAX)
		puts("O valor pode ser colocado num unsigned long!");
}
int main() {
	long val = 0,val2=0 ;
	printf("PSC Serie Exerc. 1\nFuncao MinSize\n");
	for(;;) {
		printf("Introduza numero inteiro: ") ;
		val = getlong() ;
		val2=minsize(val);
		printf("Número de Bytes a guardar em %ld: %ld\n", val, val2);
		printRange(val);
	}
	return 0 ;
}
