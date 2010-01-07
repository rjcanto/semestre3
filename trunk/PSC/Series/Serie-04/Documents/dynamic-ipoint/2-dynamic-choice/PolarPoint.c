#include "IPoint.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct polar_point {
	IPointMethods * vptr;
	double mag;
	double ang;
} PolarPoint;

static void   destroy         (IPoint * this);
static int    get_x     (const IPoint * this);
static void   set_x           (IPoint * this, int x);
static int    get_y     (const IPoint * this);
static void   set_y           (IPoint * this, int y);
static double magnitude (const IPoint * this);
static void   printTo   (const IPoint * this, FILE * file);
static void   translate       (IPoint * this, int dx, int dy);

static IPointMethods polarPointMethods = {
	destroy,
	get_x,
	set_x,
	get_y,
	set_y,
	magnitude,
	printTo,
	translate
};

IPoint * create() {
	PolarPoint * p = (PolarPoint *)malloc(sizeof(PolarPoint));
	memset(p, 0, sizeof(PolarPoint));
	p->vptr = &polarPointMethods;
	return (IPoint *)p;
}

#define  pp_this ((PolarPoint*)(this))
#define cpp_this ((const PolarPoint*)(this))

static void destroy(IPoint * this) {
	free(this); 
}

static int internal_round(double val) {
	return (int)((val < 0) ? (val - 0.5) : (val + 0.5));
}

static int get_x(const IPoint * this) {
	return internal_round(cpp_this->mag * cos(cpp_this->ang)); 
}

static int get_y(const IPoint * this) {
	return internal_round(cpp_this->mag * sin(cpp_this->ang)); 
}

static void internal_set(PolarPoint * this, int x, int y) {
	this->mag = sqrt(((double)(x)) * x + ((double)(y)) * y);
	this->ang = atan2(y, x);
}

static void set_x(IPoint * this, int x) {
	internal_set(pp_this, x, get_y(this)); 
}

static void set_y(IPoint * this, int y) {
	internal_set(pp_this, get_x(this), y); 
}

static double magnitude(const IPoint * this) {
	return cpp_this->mag;
}

static void printTo(const IPoint * this, FILE * file) {
	fprintf(file, "(%d,%d)|<%.3f,%.3f> ", get_x(this), get_y(this), cpp_this->mag, cpp_this->ang);
}

static void translate(IPoint * this, int dx, int dy) {
	internal_set(pp_this, get_x(this) + dx, get_y(this) + dy);
}

