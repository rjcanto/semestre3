/* 
 * ISEL - DEETC - LEIC
 * Programação em Sistemas Computacionais
 * João Trindade
 *
 * Testes simples às estruturas Point e Point3D.
 *
 * Quando é chamada a função auxiliar printInfo, as instâncias
 * de Point3D passam a ser vistas como Point, não existindo,
 * nesta versão do código, suporte para despacho dinâmico.
 * Assim, a função printInfo apresentará informação errada
 * sobre as instâncias de Point3D, já que são invocadas as 
 * funções de Point.
 *
 * Contrastar com a versão em Java, em que existe despacho
 * dinâmico.
 */

#include "Point.h"
#include "Point3D.h"
#include <stdio.h>

static void printInfo(const Point * p) {
	Point_print(p);
	printf("magnitude: %f\n", Point_magnitude(p));
}

static void printInfo3D(const Point3D * p) {
	Point3D_print(p);
	printf("magnitude: %f\n", Point3D_magnitude(p));
}

int main() {

	Point p;
	Point3D p3;

	init_Point_XY(&p, 1, 2, "p");
	printInfo(&p);

	puts("------------------------");

	Point_translate(&p, 3, 1);
	printInfo(&p);

	puts("------------------------");

	init_Point3D_XYZ(&p3, 1, 2, 3, "p3");
	printInfo(&(p3.super));  /* apresenta resultado errados, devido à falta de despacho dinâmico */
	printInfo3D(&p3);

	puts("------------------------");

	Point3D_translate(&p3, 1, 0, -1);
	printInfo(&(p3.super));  /* apresenta resultado errados, devido à falta de despacho dinâmico */
	printInfo3D(&p3);

	cleanup_Point3D(&p3);
	cleanup_Point(&p);

	return 0;
}
