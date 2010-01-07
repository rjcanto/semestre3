#include "IPoint.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct point {
	IPointMethods * vptr;
	int x;
	int y;
} PointImpl;

static void   destroy         (IPoint * this);
static int    get_x     (const IPoint * this);
static void   set_x           (IPoint * this, int x);
static int    get_y     (const IPoint * this);
static void   set_y           (IPoint * this, int y);
static double magnitude (const IPoint * this);
static void   printTo   (const IPoint * this, FILE * file);
static void   translate       (IPoint * this, int dx, int dy);

static IPointMethods pointImplMethods = {
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
	PointImpl * p = (PointImpl *)malloc(sizeof(PointImpl));
	memset(p, 0, sizeof(PointImpl));
	p->vptr = &pointImplMethods;
	return (IPoint *)p;
}

#define  pi_this ((PointImpl*)(this))
#define cpi_this ((const PointImpl*)(this))

static void destroy(IPoint * this)      { free(this); }

static int  get_x(const IPoint * this)  { return cpi_this->x; }
static void set_x(IPoint * this, int x) { pi_this->x = x; }

static int  get_y(const IPoint * this)  { return cpi_this->y; }
static void set_y(IPoint * this, int y) { pi_this->y = y; }

static double magnitude(const IPoint * this) {
	return sqrt((double)(cpi_this->x) * cpi_this->x +
	            (double)(cpi_this->y) * cpi_this->y);
}

static void printTo(const IPoint * this, FILE * file) {
	fprintf(file, "(%d,%d)", cpi_this->x, cpi_this->y);
}

static void translate(IPoint * this, int dx, int dy) {
	pi_this->x += dx;
	pi_this->y += dy;
}

