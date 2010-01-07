/* 
 * ISEL - DEETC - LEIC
 * Programação em Sistemas Computacionais
 * João Trindade
 *
 * Point: versão C da classe Point
 */

#ifndef POINT_H
#define POINT_H

struct point;

typedef struct point_methods {
	void   (*dtor)           (struct point * this);
	void   (*print)    (const struct point * this);
	double (*magnitude)(const struct point * this);
} PointMethods;

typedef struct point {
	PointMethods * vptr;

	char * name;
	int x;
	int y;
} Point;

/* Point_getX e Point_getY dão acesso directo a versões const de x e y. */
#define Point_getName(this) (((const Point * const)(this))->name)
#define Point_getX(this)    (((const Point * const)(this))->x)
#define Point_getY(this)    (((const Point * const)(this))->y)

/* Inicialização de instâncias de Point */
#define init_Point(this,name) init_Point_XY(this, 0, 0, name)
void    init_Point_XY(Point * this, int x, int y, const char * name);

/* Finalização de instâncias de Point. */
void    Point_cleanup(Point * this);

void    Point_translate(Point * this, int dx, int dy);
void    Point_print    (const Point * this);
double  Point_magnitude(const Point * this);

#define Point_virtual_cleanup(this)   ((this)->vptr->dtor(this))
#define Point_virtual_print(this)     ((this)->vptr->print(this))
#define Point_virtual_magnitude(this) ((this)->vptr->magnitude(this))

/* Alocação dinâmica de instâncias de Point. */
Point * new_Point(const char * name);
Point * new_Point_XY(int x, int y, const char * name);

/* Libertação de instâncias de Point alocadas dinamicamente. */
void delete_Point(Point * this);

#endif /* POINT_H */

