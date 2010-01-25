#include <stdio.h>
#include <stdlib.h>
#include "myLib.h"
#include "DataLoader.h"
#include "ProgramCourse.h"
#include "Exam.h"


int main() {
	prgcourse* courses;	
	
	TRY{
	puts("START...");
	printf("%i\n", parseInt(jmp,"10"));	
	printf("%i\n", parseInt(jmp,"10a3"));	
	printf("%i\n", parseInt(jmp,"a"));
	printf("%i\n", parseInt(jmp,"1"));
	}CATCH(INT_EXCEPTION){
	puts("INT_EXCEPTION");
	}
}

	courses = ProgramCourse_ctor();


	

	courses = courses->vptr->loadFrom(courses, "LEIC-0809-2.txt");
	printf("#ProgramCourse = %i\n", sizeof(courses)/sizeof(courses[0]));
	puts("---------------------");



return 0;
}
