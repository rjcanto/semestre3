#ifndef EXAMVALIDATOR_H
#define EXAMVALIDATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "myLib.h"
#include "ProgramCourse.h"
#include "DataLoader.h"
#include "Exam.h"


/*#define IO_ERROR_EXCEPTION 0xFFFC*/

typedef struct BaseExamValidator baseEV;
typedef struct OneExamValidator oneEV;
typedef struct TwoExamValidator twoEV;

typedef struct ValidatorLoader valLdr;

typedef struct ItemTypeArray oneEVArray;
typedef struct ItemTypeArray twoEVArray;
typedef struct ItemTypeArray evArray;

typedef struct BaseExamValidator_vtable{
	void 		(*dtor) 		(baseEV *this);
	String 		(*ruleName)		();
	void		(*setArgs)		(baseEV* this, String args);
} BaseEVMethods;

typedef struct OneExamValidator_vtable{
	void 	(*dtor) 		(oneEV *this);
	String 	(*ruleName)		();
	void	(*setArgs)		(baseEV* this, String args);
	int		(*isValid)		(oneEV* this, exam* ex);				
} OneEVMethods;

typedef struct TwoExamValidator_vtable{
	void 	(*dtor) 		(twoEV *this);
	String 	(*ruleName)		();
	void	(*setArgs)		(baseEV* this, String args);
	int		(*isValid)		(twoEV* this, exam* ex1, exam* ex2);	
} TwoEVMethods;

struct BaseExamValidator{
	BaseEVMethods*	vptr;
};
struct OneExamValidator{
	OneEVMethods*	vptr;
};
struct TwoExamValidator{
	TwoEVMethods*	vptr;
};

typedef struct ValidatorLoader_vtable{
	void		(*dtor)			(valLdr * this);
} ValidatorLoaderMethods;
struct ValidatorLoader{
	ValidatorLoaderMethods* 	vptr;
	dldr*						loader;
};
	
#define getArrayOneE(this)		((oneEV**)	(this->array))
#define getArrayPosOneE(var,i)	((oneEV*)	(var->array[i]))
#define getArrayTwoE(this)		((twoEV**)	(this->array))
#define getArrayPosTwoE(var,i)	((twoEV*)	(var->array[i]))
#define getRuleName(this)		(this->vptr->ruleName(this))

evArray* 	evArray_ctor		();
valLdr* 	valLdr_ctor			();
void 		valLdr_dtor			(valLdr* this);
void 		evArray_dtor		(evArray* this);
void** 		ev_newArray			(int numEntries);
evArray* 	ev_loadFrom			(String filename);
void* 		ev_newInstance		(String* elems, int nbr);
int 		validate			(ExamArray* exams, evArray* val1, evArray* val2);
String 		getModuleFileName	(String name);

#endif
