#include "IPoint.h"

IPoint * create();

int main() {
	IPoint * p;

	p = create();
	printf("point     = "); p->vptr->printTo(p, stdout); putchar('\n');

	p->vptr->set_x(p, 5);
	p->vptr->set_y(p, 8);
	printf("point     = "); p->vptr->printTo(p, stdout); putchar('\n');

	printf("magnitude = %.3f\n", p->vptr->magnitude(p));

	p->vptr->translate(p, 3, -12);
	printf("point     = "); p->vptr->printTo(p, stdout); putchar('\n');

	p->vptr->destroy(p);
	return 0;
}

