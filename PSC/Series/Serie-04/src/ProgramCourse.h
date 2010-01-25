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
	int			(*comparator)		(prgcourse *pc1, prgcourse* pc2);
	prgcourse**	(*loadFrom)			(prgcourse **this, String filename);
	int 		(*indexOf)			(String acr, prgcourse* courses);
} prgcourseMethods;

struct ProgramCourse{
	prgcourseMethods *vptr;
	String 	acronym;
	char 	type;
	int 	terms;
	dldr *	loader;
};

static prgcourse* ProgramCourse_init(prgcourse * this, String acronym, char type, int terms);
static prgcourse* ProgramCourse_ctor();


#define acronym(this)		(((const prgcourse * const)(this))->acronym)
#define type(this)			(((const prgcourse * const)(this))->type)
#define terms(this)			(((const prgcourse * const)(this))->terms)
		   
#endif
