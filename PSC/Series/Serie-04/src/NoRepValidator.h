#ifndef NOREPVALIDATOR_H
#define NOREPVALIDATOR_H

#include <stdio.h>

typedef struct NoRepValidator nrv;

typedef struct nrv_Methods{
	static	void 	(*dtor) 	(nrv *this);
	static	void 	(*setArgs) 	(nrv *this, String dest);
	static	String 	(*ruleName) (nrv *this);
	static	int 	(*isValid) 	(nrv *this, Exam *exam1, Exam *exam2);
} nrvMethods;

struct NoRepValidator{
	nrvMethods *vptr;
	}
	
#endif
