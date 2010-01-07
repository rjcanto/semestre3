/* 
 * ISEL - DEETC - LEIC
 * Programação em Sistemas Computacionais
 * João Trindade
 *
 * Point: versão C da classe Point
 */

#include "Point.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static PointMethods Point_vtable = {
	Point_cleanup,
	Point_print,
	Point_magnitude
};

void init_Point_XY(Point * this, int x, int y, const char * name) {
	this->vptr = &Point_vtable;

	this->name = NULL;
	if (name) { this->name = (char *)malloc(strlen(name) + 1); strcpy(this->name, name); }

	this->x = x;
	this->y = y;
}

void Point_cleanup(Point * this) {
	if (this->name) {
		free(this->name);
		this->name = NULL; /* só por precaução */
	}
}

void Point_translate(Point * this, int dx, int dy) {
	this->x += dx;
	this->y += dy;
}

double Point_magnitude(const Point * this) {
	return sqrt((double)(this->x) * (this->x) + (double)(this->y) * (this->y));
}

void Point_print(const Point * this) {
	printf("{ name = \"%s\"; x = %d; y = %d }\n",
	       this->name ? this->name : "",
	       this->x,
	       this->y);
}

Point * new_Point(const char * name) {
	Point * p = (Point *)malloc(sizeof(Point)); /* Alocação dinâmica do espaço. */
	init_Point(p, name);                        /* Inicialização da instância.  */
	return p;
}

Point * new_Point_XY(int x, int y, const char * name) {
	Point * p = (Point *)malloc(sizeof(Point)); /* Alocação dinâmica do espaço. */
	init_Point_XY(p, x, y, name);               /* Inicialização da instância.  */
	return p;
}

void delete_Point(Point * this) {
	if (this != NULL) {
		Point_virtual_cleanup(this); /* Finalização da instância.     */
		free(this);                  /* Libertação do espaço alocado. */
	}
}

