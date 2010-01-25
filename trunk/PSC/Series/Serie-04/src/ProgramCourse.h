#ifndef PROGRAMCOURSE_H
#define PROGRAMCOURSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myLib.h"
#include "DataLoader.h"
/*#define IO_ERROR_EXCEPTION 0xFFFD*/

typedef struct ProgramCourse prgcourse;

typedef struct ProgramCourse_vtable{
	void 		(*dtor) 			(prgcourse *this);
	void		(*dtor_array)		(prgcourse **this);
	int			(*comparator)		(const void *pc1, const void* pc2);
	prgcourse**	(*loadFrom)			(prgcourse **this, String filename);
	int 		(*indexOf)			(String acr, prgcourse** courses);
} prgcourseMethods;

struct ProgramCourse{
	prgcourseMethods *vptr;
	String 	acronym;
	char 	type;
	int 	terms;
};

typedef struct ProgramCourseArray{
	prgcourse** array;
	int size;
}pca;


prgcourse* 			ProgramCourse_ctor		(String acronym, char type, int terms);
void 				ProgramCourse_dtor 		(prgcourse * this);
void				ProgramCourse_cleanup	(prgcourse ** this);
int			pc_comparator			(const void * pc1, const void* pc2);
prgcourse**			pc_loadFrom				(prgcourse ** this, String filename);
int 			pc_indexOf				(String acr, prgcourse** courses);
void**		pc_newArray				(int numEntries);
void* 		pc_newInstance			(String* elems);

#define acronym(this)		(((const prgcourse * const)(this))->acronym)
#define type(this)			(((const prgcourse * const)(this))->type)
#define terms(this)			(((const prgcourse * const)(this))->terms)
		   
#endif
