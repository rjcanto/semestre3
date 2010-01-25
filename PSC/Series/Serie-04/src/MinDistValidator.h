#ifndef MINDISTVALIDATOR_H
#define MINDISTVALIDATOR_H

#include <stdio.h>

typedef struct MinDistValidator mdv;

typedef struct mdv_Methods{
	static	void 	(*dtor) 	(mdv *this);
	static	void 	(*setArgs) 	(mdv* this, String dest);
	static	String 	(*ruleName) (mdv* this);
	static	int 	(*isValid) 	(mdv* this, Exam *exam);
} mdvMethods;

struct MinDistValidator{
	mdvMethods *vptr;
	static int minDist = 13;
	}
	
#endif
