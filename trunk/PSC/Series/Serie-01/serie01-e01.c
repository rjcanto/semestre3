#include <stdio.h>


int minsize(long val) {
	int count = 0 ;
	int countZeros = 0 ;
	int mask = 1 ;
	
	while (mask !=0) {
		if (!(val & mask)) {
			countZeros++ ;
		} else {
			count = count +1 + countZeros ;
			countZeros = 0 ;
		}
		mask =	mask << 1 ;
	}
	
	if (val < 0)
		return (count*-1) ;
	/*Necessário adicionar o MSB (a 0) dos números positivos */
	else return ++count ;
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

int main() {
	long val = 0 ;
	printf("PSC Serie Exerc. 1\nFuncao MinSize\n");
	for(;;) {
		printf("Introduza numero inteiro: ") ;
		val = getlong() ;
		printf("Número de bits a guardar em %ld: %d\n", val, minsize(val));
	}
	return 0 ;
}
