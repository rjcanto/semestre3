#include "IPoint.h"

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

char the_soname[64] = "./";

int main(int argc, char * argv[]) {

	char * dlerr;
	void * dlh;
	IPoint * (*create)();
	IPoint * p;

	if (argc != 2) {
		fprintf(stderr, "use: %s soname\nwhere soname is PointImpl, PolarPoint, or other\n", argv[0]);
		exit(1);
	}

	strcat(the_soname, argv[1]);
	strcat(the_soname, ".so");
	
	dlh = dlopen(the_soname, RTLD_NOW);

	if (dlh == NULL) {
		fprintf(stderr, "Error loading %s: %s\n", the_soname, dlerror());	
		exit(1);
	}

	/* Errado:
	      create = dlsym(dlh, "create")
	   porque:
	      'dlsym' retorna um 'void *'
	      mas 'create' tem como tipo 'IPoint * (*)()'

	   Errado:
	      create = (IPoint * (*)()) dlsym(dlh, "create")
	   porque:
	      A norma da linguagem C proibe cast entre
	      ponteiro para dados e ponteiro para codigo */

	*(void**)(&create) = dlsym(dlh, "create");
	
	if ((dlerr = dlerror()) != NULL) {
		fprintf(stderr, "Error with symbol 'create': %s\n", dlerr);
		exit(1);
	}

	/* O codigo que se segue e' exactamente igual ao do
	   exemplo anterior (0-static), em que nao se usou
	   carregamento dinamico. */

	p = create();
	printf("point     = "); p->vptr->printTo(p, stdout); putchar('\n');

	p->vptr->set_x(p, 5);
	p->vptr->set_y(p, 8);
	printf("point     = "); p->vptr->printTo(p, stdout); putchar('\n');

	printf("magnitude = %.3f\n", p->vptr->magnitude(p));

	p->vptr->translate(p, 3, -12);
	printf("point     = "); p->vptr->printTo(p, stdout); putchar('\n');

	p->vptr->destroy(p);

	dlclose(dlh);
	return 0;
}

