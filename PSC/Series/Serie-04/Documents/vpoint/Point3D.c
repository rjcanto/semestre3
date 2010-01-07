/* 
 * ISEL - DEETC - LEIC
 * Programação em Sistemas Computacionais
 * João Trindade
 *
 * Point3D: versão C da classe Point3D
 */

#include "Point3D.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static PointMethods Point3D_vtable = {
	(void   (*)      (Point *)) Point3D_cleanup,
	(void   (*)(const Point *)) Point3D_print,
	(double (*)(const Point *)) Point3D_magnitude
};

void init_Point3D_XYZ(Point3D * this, int x, int y, int z, const char * name) {
	/* Invocação explícita de função de inicialização da base. */
	init_Point_XY((Point *)this, x, y, name);
	/* Correcção da tabela de métodos virtuais. */
	this->super.vptr = &Point3D_vtable;
	
	this->z = z;
}

/* Finalização de instâncias de Point3D (só finaliza a base, uma vez que não há outros recursos a gerir). */
void Point3D_cleanup(Point3D * this) {

	/* Repor tabela de métodos virtuais de Point3D 
	   (terá sido alterada se this referir instância de tipo derivado) */
	this->super.vptr = &Point3D_vtable;

	/* Eventual código de cleanup dos campos específicos de Point3D */
	/* ... */

	/* Cleanup da base */	
	Point_cleanup((Point *)this);
}

void Point3D_translate(Point3D * this, int dx, int dy, int dz) {
	/* Invocação de código definido na base. */
	Point_translate((Point *)this, dx, dy);
	this->z += dz;
}

double Point3D_magnitude(const Point3D * this) {
	return sqrt((double)(this->super.x) * (this->super.x) + (double)(this->super.y) * (this->super.y) + (double)(this->z) * (this->z));
}

void Point3D_print(const Point3D * this) {
	printf("{ name = \"%s\"; x = %d; y = %d; z = %d }\n",
	       this->super.name ? this->super.name : "",
	       this->super.x,
	       this->super.y,
	       this->z);
}

Point3D * new_Point3D(const char * name) {
	Point3D * p = (Point3D *)malloc(sizeof(Point3D)); /* Alocação dinâmica do espaço. */
	init_Point3D(p, name);                            /* Inicialização da instância.  */
	return p;
}

Point3D * new_Point3D_XYZ(int x, int y, int z, const char * name) {
	Point3D * p = (Point3D *)malloc(sizeof(Point3D)); /* Alocação dinâmica do espaço. */
	init_Point3D_XYZ(p, x, y, z, name);               /* Inicialização da instância.  */
	return p;
}

void delete_Point3D(Point3D * this) {
	if (this != NULL) {
		Point_virtual_cleanup((Point *)this); /* Finalização */
		free(this);                           /* Libertação  */
	}
}

