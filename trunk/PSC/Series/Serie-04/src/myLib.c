#include "myLib.h"

int parseInt(jmp_buf jmp, const String string){
	int number=0;
	String i = string;
	
	while (*i!=0 && *i>='0' && *i <='9'){
		number=number*10 +(*i-'0');
		++i;
	}
	if (*i!=0) THROW(INT_EXCEPTION);
    
    return number;
}

String xstrtrim(String str){
	String start, end;
	int lenght;
	
	/*se String for vazia ou não definida retorna a String*/
	if( str == NULL || str[0] == '\0')
            return str;
	
	start = str;
	lenght=strlen(str);
	end = str + lenght-1;
	
	/*retira os espaços no inicio e no fim*/
	while(*start==' ') ++start;
	while(*end==' ' && end>start) --end;
	if(str+lenght-1 != end)
	*(end+1) = '\0';
	
	/*se String apenas tinha espacos torna-a vazia*/
	if(end < start)
		*str='\0';
		
	/* para os casos em que a string foi definida dinamicamente e
	 * para podermos usar o free() então a string tem de se 
	 * iniciar no mesmo local da string que nos foi passada.
	 * usamos o end como ponteiro auxiliar */
	end=str;
	if (start != str){
		while(*start != '\0')
			*(end++) = *(start++);
		*end = '\0';
	}
  return str;
}
