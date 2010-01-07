#ifndef MINDISTVALIDATOR_H
#define MINDISTVALIDATOR_H

#include <stdio.h>

typedef struct MinDistValidator ndv;

typedef struct mdv_vtable{
	static	void 	(*setArgs) 	(String dest);
	static	String 	(*ruleName) ();
	static	int 	(*isValid) 	(Exam *exam);
	static	void 	(*destroy) 	(mdv *this);
} MinDistValidatorMethods;

struct MinDistValidator{
	MinDistValidatorMethods *vptr;
	static int minDist = 13;
	}
	
#endif
