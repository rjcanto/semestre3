#include "myLib.h"

int parseInt(const String string){
	int number=0;
	String i = string;
	
	while (*i!=0 && *i>='0' && *i <='9'){
		number=number*10 +(*i-'0');
		++i;
	}
	if (*i!=0) THROW(INT_EXCEPTION);
    
    return number;
}