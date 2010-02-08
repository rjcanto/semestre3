#ifndef NOREPVALIDATOR_H
#define NOREPVALIDATOR_H

#include <stdio.h>
#include "myLib.h"
#include "ExamValidator.h"

typedef struct NoRepValidator nrv;

typedef struct nrv_Methods{
	void 	(*dtor) 	(twoEV* this);
	String 	(*ruleName) ();
	void 	(*setArgs) 	(twoEV* this, String dest);
	int 	(*isValid) 	(twoEV* this, exam* exam1, exam* exam2);
} nrvMethods;

struct NoRepValidator{
	nrvMethods* vptr;
};

void* 	ctor();
void 	dtor		(twoEV* this);
void 	setArgs		(twoEV* this, String dest);
String 	ruleName	();
int 	isValid		(twoEV* this, exam* exam1, exam* exam2);

#endif
