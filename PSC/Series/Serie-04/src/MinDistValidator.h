#ifndef MINDISTVALIDATOR_H
#define MINDISTVALIDATOR_H

#include <stdio.h>
#include "myLib.h"
#include "ExamValidator.h"

typedef struct MinDistValidator mdv;

typedef struct mdv_Methods{
	void 		(*dtor) 	(oneEV* this);
	String		(*ruleName) ();
	void 		(*setArgs) 	(oneEV* this, String dest);
	int 		(*isValid) 	(oneEV* this, exam* ex);
} mdvMethods;

struct MinDistValidator{
	mdvMethods* vptr;
	int minDist;
};

#define getMinDist(this)		(((const mdv * const)(this))->minDist)

void* 	ctor();
void 	dtor			(oneEV* this);
void 	setArgs			(oneEV* this, String dest);
String 	ruleName		();
int 	isValid			(oneEV* this, exam* ex);
int		mdv_parseInt	(const String string);

#endif
