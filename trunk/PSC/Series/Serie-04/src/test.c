#include <stdio.h>
#include "myLib.h"



int main(){

puts("START...");
printf("%i\n", parseInt("10"));	
printf("%i\n", parseInt("10a3"));	
printf("%i\n", parseInt("a"));
printf("%i\n", parseInt("1"));


return 0;
}
