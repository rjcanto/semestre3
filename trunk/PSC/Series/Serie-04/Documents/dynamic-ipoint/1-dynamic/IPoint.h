#ifndef IPOINT_H
#define IPOINT_H

#include <stdio.h>

typedef struct ipoint IPoint;

typedef struct ipoint_vtable {

	void   (*destroy)         (IPoint * this);

	int    (*get_x)     (const IPoint * this);
	void   (*set_x)           (IPoint * this, int x);

	int    (*get_y)     (const IPoint * this);
	void   (*set_y)           (IPoint * this, int y);

	double (*magnitude) (const IPoint * this);

	void   (*printTo)   (const IPoint * this, FILE * file);

	void   (*translate)       (IPoint * this, int dx, int dy);
	
} IPointMethods;

struct ipoint {
	IPointMethods * vptr;
};

#endif

