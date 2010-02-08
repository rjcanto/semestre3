#ifndef EXAM_H
#define EXAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myLib.h"
#include "DataLoader.h"
#include "ProgramCourse.h"
#define INT_MIN_VALUE -32767
/*#define IO_ERROR_EXCEPTION 0xFFFC*/

typedef struct Exam exam;
typedef struct ExamLoader examldr;
typedef struct ItemTypeArray ExamArray;

typedef struct Exam_vtable{
	void 		(*dtor) 			(exam *this);
	int			(*comparator)		(const void *e1, const void* e2);
	arrayItem*	(*loadFrom)			(String filename, ExamArray* courses);
	int 		(*indexOf)			(String acr, ExamArray* examsArr);
} examMethods;

struct Exam{
	examMethods* 	vptr;
	prgcourse* 		course;
	int 			date1;
	int 			date2;
};

typedef struct ExamLoader_vtable{
	void	(*dtor)				(examldr * this);
} examLoaderMethods;

struct ExamLoader{
	examLoaderMethods* 	vptr;
	dldr* 				loader;
	PrgCourseArray* 	coursesArray;
};

void 		Exam_dtor		(exam *this);
void 		ExamArray_dtor	(ExamArray* this);
void 		ExamLoader_dtor	(examldr* this);
exam* 		Exam_ctor		(prgcourse* course, int date1, int date2);
ExamArray* 	ExamArray_ctor	();
int			e_comparator	(const void * e1, const void * e2);
ExamArray*	e_loadFrom		(String filename, ExamArray* courses);
int 		e_indexOf		(String acr, ExamArray* examsArr);
void**		e_newArray		(int numEntries);
void* 		e_newInstance	(String* elems, int nbr);

#define getCourse(this)		(((const exam * const)(this))->course)
#define getDate1(this)		(((const exam * const)(this))->date1)
#define getDate2(this)		(((const exam * const)(this))->date2)
#define getArrayE(this)		((exam**)(this->array))
#define getArrayPosE(var,i)	((exam*)(var->array[i]))
		   
#endif
