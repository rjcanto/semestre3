/**
 * Primeira série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 * Exercicio 2:
 * São utilizadas três funções:
 * -> readlines(const char * search)
 * 	  Função que processa os dados de STDIN. Enquanto houver linhas 
 * chama a função nextline(), obtem a linha e verifica a string a 
 * encontrar através da função xstrstr().
 * -> nextLine()
 * 	  Função que lê do STDIN e forma a frase a ser retornada. 
 * -> xstrstr(char * str1, const char * str2)
 * 	  Função que verifica se str2 passada no argumento se encontra na str1.
 *  
 * Estratégia de resolução: 
 * -> Partiu-se o problema em três partes.
 * -> Uma parte que gere o input recebido, a comparação da string e 
 * colocação no ecrâ.
 * -> Uma parte que obtem a linha a ser comparada
 * -> Uma parte que verifica se a string existe ou não.
 * -> Como controlo verifica-se se existe palavra a pesquisar na linha 
 * de comandos.
 */ 

#include <stdio.h>

#define MAX_LEN 255
char line[MAX_LEN];

char * xstrstr(char * str1, const char * str2){
	int i=0,j=0;
	if (*str2 == 0) return str1;
	for (;*(str1 +i)!=0;++i){
		if (*(str1 +i) == *(str2 +j)){
			j++;
			if (*(str2+j) == 0) return str1+i-j+1;
		}else{
			i=i-j;
			j=0;
		}
	}
	return NULL;
}


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
			index = xstrstr(ln,search) ; 
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
