#ifndef MANDATORYSAMEDAYVALIDATOR_H
#define MANDATORYSAMEDAYVALIDATOR_H

#include <stdio.h>
#include "myLib.h"
#include "ExamValidator.h"

typedef struct MandatorySameDayValidator msdv;

typedef struct msdv_Methods{
	void 		(*dtor) 	(twoEV* this);
	String		(*ruleName) ();
	void 		(*setArgs) 	(twoEV* this, String dest);
	int 		(*isValid) 	(twoEV* this, exam* ex1, exam* ex2);
} msdvMethods;

struct MandatorySameDayValidator{
	msdvMethods* vptr;
};

void* 	ctor();
void 	dtor					(twoEV* this);
void 	setArgs					(twoEV* this, String dest);
String 	ruleName				();
int 	isValid					(twoEV* this, exam* ex1, exam* ex2);
int 	isSameOrConsecTerms		(exam* ex1, exam* ex2);

#endif
