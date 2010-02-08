#ifndef PROGRAMCOURSE_H
#define PROGRAMCOURSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "myLib.h"
#include "DataLoader.h"
/*#define IO_ERROR_EXCEPTION 0xFFFD*/
#define MAX_DEP_UC 3
typedef struct ProgramCourse prgcourse;
typedef struct ItemTypeArray PrgCourseArray;

typedef struct ProgramCourse_vtable{
	void 		(*dtor) 			(prgcourse *this);
	int			(*comparator)		(const void *pc1, const void* pc2);
	arrayItem*	(*loadFrom)			(String filename);
	int 		(*indexOf)			(String acr, PrgCourseArray* courses);
} prgcourseMethods;

struct ProgramCourse{
	prgcourseMethods *vptr;
	String 	acronym;
	char 	type;
	int 	terms;
	String*	sdep;
	String*	wdep;
};

#define getAcronym(this)			(((const prgcourse * const)(this))->acronym)
#define getType(this)				(((const prgcourse * const)(this))->type)
#define getTerms(this)				(((const prgcourse * const)(this))->terms)
#define getSDep(this)				(((const prgcourse * const)(this))->sdep)
#define getWDep(this)				(((const prgcourse * const)(this))->wdep)
#define getArrayPC(this)			((prgcourse**)(this->array))
#define getArrayPosPC(var,i)		((prgcourse*)(var->array[i]))

prgcourse* 			ProgramCourse_ctor			(String acronym, char type, int terms, String sdep, String wdep);
void 				ProgramCourse_dtor 			(prgcourse * this);
void				ProgramCourseArray_dtor		(PrgCourseArray * this);
int					pc_comparator				(const void * pc1, const void* pc2);
PrgCourseArray*		pc_loadFrom					(String filename);
int 				pc_indexOf					(String acr, PrgCourseArray* courses);
void**				pc_newArray					(int numEntries);
void* 				pc_newInstance				(String* elems, int nbr);
		   
#endif
