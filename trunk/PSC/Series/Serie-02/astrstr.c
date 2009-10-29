/**
 * Segunda série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 * Exercicio 2:
 * É utilizado o mesmo resolução proposta na serie anterior, exceptuando
 * o facto de estarmos a chamar a função astrstr(char * str1, const 
 * char * str2), definida em assembly.
 */ 

#include <stdio.h>

#define MAX_LEN 255
char line[MAX_LEN];

char * astrstr(char * str1, const char * str2);


char * nextLine(){
	int idx=0;
	char c;
	
	while ((c=getchar()) != EOF && idx <MAX_LEN){
		if (c != '\n'){
			*(line +idx) =c ;
		}else{
			*(line +idx) = 0 ;
			return line;
		}
		idx++;
		
	}
	return NULL;
}

void readlines(const char * search){
	char * ln ; 
	char * index ;
	int idx=0;
	
	do{ 
		ln = nextLine();
		++idx;
		if (ln != NULL){
			index = astrstr(ln,search) ; 
			if (index != NULL){
				printf("[%d]: %s\n",idx,ln);
			}
		}
	}while(ln != NULL);
}


int main (int argc, char *argv[]){
	if (argc>1)
		readlines(argv[1]);
	else
		puts("Need at least one argument to be searched!");
return 0;	 
}
