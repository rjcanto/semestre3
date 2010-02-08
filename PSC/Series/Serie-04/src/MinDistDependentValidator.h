#ifndef MINDISTDEPENDENTVALIDATOR_H
#define MINDISTDEPENDENTVALIDATOR_H

#include <stdio.h>
#include "myLib.h"
#include "ExamValidator.h"

typedef struct MinDistDependentValidator mddv;

typedef struct mddv_Methods{
	void 		(*dtor) 	(twoEV* this);
	String		(*ruleName) ();
	void 		(*setArgs) 	(twoEV* this, String dest);
	int 		(*isValid) 	(twoEV* this, exam* ex1, exam* ex2);
} mddvMethods;

struct MinDistDependentValidator{
	mddvMethods* vptr;
	int mi;
	int md;
};

#define getMdi(this)		(((const mddv * const)(this))->mi)
#define getMdd(this)		(((const mddv * const)(this))->md)

void* 	ctor();
void 	dtor			(twoEV* this);
void 	setArgs			(twoEV* this, String dest);
String 	ruleName		();
int 	isValid			(twoEV* this, exam* ex1, exam* ex2);
int		mdv_parseInt	(const String string);
int 	isConsecTerms	(exam* ex1, exam* ex2);
int 	isSDep			(exam* ex1, exam* ex2);

#endif
