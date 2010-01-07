#include "IPoint.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dlfcn.h>

typedef struct ipoint_factory {
	void * handle;
	IPoint * (*create)();
} IPointFactory;

static int load(IPointFactory * pf, const char * soname) {

	char * dlerr;
	void * handle;
	IPoint * (*create)();

	pf->handle = NULL;
	pf->create = NULL;

	handle = dlopen(soname, RTLD_NOW);
	if (handle == NULL) {
		fprintf(stderr, "Error loading %s: %s\n", soname, dlerror());	
		return -1;
	}

	*(void**)(&create) = dlsym(handle, "create");
	if ((dlerr = dlerror()) != NULL) {
		fprintf(stderr, "Error with symbol 'create' on %s: %s\n", soname, dlerr);
		dlclose(handle);
		return -2;
	}

	pf->handle = handle;
	pf->create = create;
	return 0;
}

static void unload(IPointFactory * pf) {
	if (pf->handle != NULL) {
		pf->create = NULL;
		dlclose(pf->handle);
		pf->handle = NULL;
	}
}

void fill(IPoint * * ps, size_t n);
void show(IPoint * * ps, size_t n);

#define N 5

int main(int argc, char * argv[]) {

	int i;

	IPointFactory pf[2];
	IPoint * p[N];

	srand(time(NULL));

	if (load(&pf[0], "./PointImpl.so") != 0)
		exit(1);

	if (load(&pf[1], "./PolarPoint.so") != 0) {
		unload(&pf[0]);
		exit(1);
	}

	for (i = 0; i < N; ++i)
		p[i] = pf[rand() & 1].create();

	fill(p, N);

	show(p, N);

	for (i = 0; i < N; ++i)
		p[i]->vptr->destroy(p[i]); 

	unload(&pf[1]);
	unload(&pf[0]);

	return 0;
}

void fill(IPoint * * ps, size_t n) {
	int i;
	for (i = 0; i < n; ++i) {
		ps[i]->vptr->set_x(ps[i], (rand() % 199) - 99);
		ps[i]->vptr->set_y(ps[i], (rand() % 199) - 99);
	}
}

void show(IPoint * * ps, size_t n) {
	int i;
	for (i = 0; i < n; ++i) {
		ps[i]->vptr->printTo(ps[i], stdout); putchar('\n');
	}
}

