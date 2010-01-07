#ifndef MINDISTVALIDATOR_H
#define MINDISTVALIDATOR_H

#include <stdio.h>

typedef struct MinDistValidator mdv;

typedef struct mdv_Methods{
	static	void 	(*dtor) 	(mdv *this);
	static	void 	(*setArgs) 	(String dest);
	static	String 	(*ruleName) ();
	static	int 	(*isValid) 	(Exam *exam);
} mdvMethods;

struct MinDistValidator{
	mdvMethods *vptr;
	static int minDist = 13;
	}
	
#endif
