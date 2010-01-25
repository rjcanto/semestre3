#include "ProgramCourse.h"



static prgcourseMethods prgcourse_vtable={
	ProgramCourse_dtor,
	ProgramCourse_cleanup,
	pc_comparator,
	pc_loadFrom,
	pc_indexOf
};

void ProgramCourse_dtor(prgcourse * this){
	if (this!=NULL){
		if (this->acronym)
			free(this->acronym);
		free(this);
	}
}

void ProgramCourse_cleanup(prgcourse** this){
	int i=0;
	int size = sizeof(this)/sizeof(this[0]);
	for (i=0; i<size; ++i)
		this[i]->vptr->dtor(this[i]);
}
	
prgcourse* ProgramCourse_ctor(String acronym, char type, int terms){
	prgcourse *p = (prgcourse *)malloc(sizeof(prgcourse));
	
	
	if (acronym) {
		p->acronym = (String) malloc(strlen(acronym)+1);
		strcpy(p->acronym, acronym);
	}
	p->type = type;
	p->terms = terms;
	p->vptr = &prgcourse_vtable;
	return p;
}

void** pc_newArray(int numEntries){
	void** aux =  malloc(sizeof(prgcourse*) * numEntries);
	return aux;
}

void* pc_newInstance(String* elems){
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
	return ProgramCourse_ctor(elems[0], type, trms);
}

int pc_comparator(const void *pc1, const void *pc2){	
	return (strcmp( ((prgcourse *) (pc1))->acronym,((prgcourse *) (pc2))->acronym)); 
}

prgcourse** pc_loadFrom(prgcourse** courses, String filename){
	dldr * loader = DataLoader_ctor();
	loader->vptr->newArray = &pc_newArray;
	loader->vptr->newInstance = &pc_newInstance;
	
	courses = (prgcourse**) loader->vptr->loadFrom(loader, filename);
	printf("size of courses: %i\n",sizeof(**courses));
	
	qsort(courses, sizeof(courses)/sizeof(courses[0]), sizeof(courses[0]), pc_comparator);
	return courses;
}

int pc_indexOf(String acr, prgcourse** courses){
	prgcourse* res;
	prgcourse* key = ProgramCourse_ctor(acr, '\0', -1);
	res= bsearch(key, courses, sizeof(courses)/sizeof(courses[0]), sizeof(courses[0]), pc_comparator);

	if (res==NULL)
		return -1;
	return (res - (prgcourse*) courses);
}

 
