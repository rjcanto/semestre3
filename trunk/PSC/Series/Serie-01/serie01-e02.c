#include <stdio.h>

#define MAX_LEN 255
char line[MAX_LEN];

char * xstrstr(char * str1, const char * str2){
	int i=0,j=0;
	if (*str2 == 0) return str1;
	for (;*(str1 +i)!=0;++i){
		if (*(str1 +i) == *(str2 +j)){
			j++;
			if (*(str2+j) == 0) return str1;
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
	char * ln;
	int idx=0;
	
	do{ 
		ln = nextLine();
		++idx;
		if (ln != NULL){
			if (xstrstr(ln,search) != NULL){
				printf("[%d] - %s\n",idx,ln);
			}
		}
	}while(ln != NULL);
}


int main (int argc, char *argv[]){
	if (argc>1)
		readlines(argv[1]);
	else
		puts("Need at least one argument!");
return 0;	 
}
