#include "ProgramCourse.h"

static void 		ProgramCourse_dtor 		(prgcourse * this);
static void			ProgramCourse_cleanup	(prgcourse ** this);
static int			pc_comparator			(prgcourse * pc1, prgcourse* pc2);
static prgcourse**	pc_loadFrom				(prgcourse ** this, String filename);
static int 			pc_indexOf				(String acr, prgcourse* courses);
static prgcourse*	pc_newArray				(int numEntries);
static prgcourse* 	pc_newInstance			(String* elems);

static prgcourseMethods prgcourse_vtable={
	ProgramCourse_dtor,
	ProgramCourse_cleanup,
	pc_comparator,
	pc_loadFrom,
	pc_indexOf
};

static void ProgramCourse_dtor(prgcourse * this){
	if (this!=NULL){
		if (this->acronym)
			free(this->acronym);
		this->loader->vptr->dtor(this->loader);
		free(this);
	}
}

static void ProgramCourse_cleanup(prgcourse** this){
	int i=0;
	int size = sizeof(this)/sizeof(this[0]);
	for (i=0; i<size; ++i)
		this[i]->vptr->dtor(this[i]);
}
	
static prgcourse* ProgramCourse_init(prgcourse * this, String acronym, char type, int terms){
	if (acronym) {
		this->acronym = (String) malloc(strlen(acronym)+1);
		strcpy(this->acronym, acronym);
	}
	this->type = type;
	this->terms = terms;
	return this;
}
	
static prgcourse* ProgramCourse_ctor(){
	prgcourse *p = (prgcourse *)malloc(sizeof(prgcourse));
	p->vptr = &prgcourse_vtable;
	p->loader = DataLoader_ctor();
	p->loader->vptr->newArray = &pc_newArray;
	p->loader->vptr->newInstance = &pc_newInstance;
	return p;
}

static prgcourse* pc_newArray(int numEntries){
	prgcourse* aux = (prgcourse*) malloc(sizeof(prgcourse*) * numEntries);
	return aux;
}

static prgcourse* pc_newInstance(String* elems){
	char type;
	int trms;	
	if (elems[0] == NULL) 
		return NULL;
	type = ((strlen(elems[1])==1) ? (*elems[1]):'\0');
	if (strlen(elems[2])<10){
		TRY{
		trms=parseInt(jmp,elems[2]);
		} CATCH(INT_EXCEPTION){
			trms=-1;
		}
		}	/* END OF TRY BLOCK */
	}
	return ProgramCourse_ctor(elems, type, trms);
}

static int pc_comparator(prgcourse *pc1, prgcourse *pc2){
	return (strcmp(pc1->acronym, pc2->acronym)); 
}

static prgcourse** pc_loadFrom(prgcourse** courses, String filename){
	courses = (prgcourse**) courses[0]->loader->vptr->loadFrom(loader, filename);
	qsort(courses, sizeof(courses)/sizeof(courses[0]), sizeof(courses[0]), courses[0]->vptr->comparator);
	return courses;
}

static int indexOf(String acr, prgcourse** courses){
	int res;
	prgcourse* key = ProgramCourse_ctor(acr, '\0', -1);
	return (res=bsearch(key, courses, sizeof(courses)/sizeof(courses[0]), sizeof(courses[0]), courses[0]->vptr->comparator)? (res-courses) : -1);
}
	
	
 
