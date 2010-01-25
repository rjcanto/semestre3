#include <stdio.h>
#include <stdlib.h>
#include "myLib.h"
#include "DataLoader.h"
#include "ProgramCourse.h"



int main() {
	prgcourse** courses;	
	/*
	TRY{
	puts("START...");
	printf("%i\n", parseInt(jmp,"10"));	
	printf("%i\n", parseInt(jmp,"10a3"));	
	printf("%i\n", parseInt(jmp,"a"));
	printf("%i\n", parseInt(jmp,"1"));
	}CATCH(INT_EXCEPTION){
	puts("INT_EXCEPTION");
	}
}*/
	char** array = (char**) malloc(10 * sizeof(char*));
	printf("size of array: %i\n", sizeof(array));
	printf("size of array[0]: %i\n", sizeof(array[0]));
	
	
	courses = pc_loadFrom(courses, "LEIC-0809-2.txt");
	puts("aaa");
	printf("#ProgramCourse = %i\n", sizeof(courses)/sizeof(courses[0]));
	puts("---------------------");
	


return 0;
}
