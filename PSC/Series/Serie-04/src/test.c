#include <stdio.h>
#include <stdlib.h>
#include "myLib.h"
#include "ProgramCourse.h"
#include "Exam.h"
#include "ExamValidator.h"


/*DEBUG*/
void pc_Print(arrayItem* arr){
	int i,j=0;
	String* aux2;
	prgcourse* aux;
	for(i=0; i<arr->size; ++i){
		aux=getArrayPosPC(arr, i);
		printf("num: %d - %s - %c - %d",i,getAcronym(aux), getType(aux), getTerms(aux));
		aux2 = getSDep(aux);
		j=0;
		while(aux2[j]){
			printf(" - %s;",(String)(aux2[j]));
			++j;
		}
		j=0;
		aux2 = getWDep(aux);
		while(aux2[j]){
			printf(" - %s;",(String)(aux2[j]));
			++j;
		}
		printf("\n");
	}
}
void e_Print(arrayItem* arr){
	int i;
	exam* aux;
	for(i=0; i<arr->size; ++i){
		aux=getArrayPosE(arr,i);
		printf("num: %d : %s : %d : %d\n",i,getAcronym(getCourse(aux)), getDate1(aux), getDate2(aux));
	}
}

int main() {
	int res,i;
	PrgCourseArray* courses;
	ExamArray* exams;
	
	oneEVArray* val1;
	twoEVArray* val2;
	
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

	courses = pc_loadFrom("./DataFile/LEIC-0809-2.txt");
	printf("#ProgramCourse = %i\n", courses->size);
	puts("---------------------");
	
/*	pc_Print(courses);*/
	
	res = pc_indexOf("Com", courses);	
	printf("indexOf Com: %i \n", res);
	puts("---------------------");
	
	exams = e_loadFrom("./DataFile/Exames-0809-2.txt",courses);
	printf("#Exams = %i\n", exams->size);
	puts("---------------------");
	
/*	e_Print(exams);*/
	res = e_indexOf("AED", exams);	
	printf("indexOf AED: %i \n", res);
	printf("testes nos dias: %d e %d\n",((exam*)(exams->array[res]))->date1,((exam*)(exams->array[res]))->date2);
	puts("---------------------");
	
	val1 = ev_loadFrom("./DataFile/Validators1.txt");
	val2 = ev_loadFrom("./DataFile/Validators2.txt");
	
	res = validate(exams, val1, val2);
	
	printf("O mapa de exames e' %svalido.\n", res ? "" : "in");
	
	exams->vptr->dtor(exams);
	courses->vptr->dtor(courses);

return 0;
}
