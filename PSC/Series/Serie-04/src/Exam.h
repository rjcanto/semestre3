#ifndef EXAM_H
#define EXAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myLib.h"
#include "DataLoader.h"
#include "ProgramCourse.h"
/*#define IO_ERROR_EXCEPTION 0xFFFC*/

typedef struct Exam exam;
typedef struct ExamLoader examldr;

typedef struct Exam_vtable{
	void 		(*dtor) 			(exam *this);
	void		(*dtor_array)		(exam **this);
	int			(*comparator)		(exam *pc1, exam* pc2);
	exam**		(*loadFrom)			(exam **this, String filename, prgcourse** courses);
	int 		(*indexOf)			(String acr, exam** exams);
} examMethods;

struct Exam{
	examMethods *vptr;
	prgcourse course;
	int date1;
	int date2;
	dldr* loader;
};

typedef struct ExamLoader_vtable{
	void			(*dtor)				(examldr * this);
} examLoaderMethods;

struct ExamLoader{
	examldr	*vptr;
	prgcourse* courses;
}



#define course(this)		(((const exam * const)(this))->course)
#define date1(this)			(((const exam * const)(this))->date1)
#define date2(this)			(((const exam * const)(this))->date2)
		   
#endif
