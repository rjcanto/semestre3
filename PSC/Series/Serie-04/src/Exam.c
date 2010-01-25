#include "Exam.h"

static void 	Exam_dtor		(exam *this);
static void		Exam_cleanup	(exam **this);
static int		e_comparator	(exam *pc1, exam* pc2);
static exam**	e_loadFrom		(exam **this, String filename, prgcourse** courses);
static int 		e_indexOf		(String acr, exam** exams);
static exam**	e_newArray		(int numEntries);
static exam* 	e_newInstance	(String* elems);

static examMethods exam_vtable={
	Exam_dtor,
	Exam_cleanup,
	e_comparator,
	e_loadFrom,
	e_indexOf
};

static void Exam_dtor(exam *this){
	if (this!=NULL){
		this->course->vptr->dtor(this->course);
		this->loader->vptr->dtor(this->loader);
		free(this);
	}
}

static void Exam_cleanup(exam** this){
	int i, size = sizeof(this)/sizeof(this[0]);
	for (i=0; i<size; ++i)
		this[i]->vptr->dtor(this[i]);
}
	
static exam* Exam_ctor(prgcourse course, int date1, int date2){
	exam *e = (exam*) malloc(sizeof(exam));
	e->vptr = &exam_vtable;
	e->course = course;
	e->date1 = date1;
	e->date2 = date2;
	
	/*p->loader = DataLoader_ctor();
	p->loader->vptr->newArray = &pc_newArray;
	p->loader->vptr->newInstance = &pc_newInstance;*/
	
	return e;
}

static exam** e_newArray(int numEntries){
	exam** aux = (exam**) malloc(sizeof(exam*) * numEntries);
	return aux;
}
/* em falta */
static exam* e_newInstance(String* elems){
	char type;
	int trms;	
	if (elems[0] == NULL) 
		return NULL;
	type = ((strlen(elems[1])==1) ? (*elems[1]):'\0');
	if (strlen(elems[2])<10){
		TRY{
		trms=parseInt(jmp, elems[2]);
		} CATCH(INT_EXCEPTION){
			trms=-1;
		}
		}	/* END OF TRY BLOCK */
	}
	return Exam_ctor(elems[0], type, trms);
}

static int e_comparator(exam *e1, exam *e2){
	return (strcmp(e1->course->acronym, e2->course->acronym)); 
}

static exam** e_loadFrom(exam** this, String filename, prgcourse** courses){
	exam** exams = (exam**) loadFrom(loader, filename);
	qsort(this, sizeof(courses)/sizeof(courses[0]), sizeof(courses[0]), courses[0]->vptr->comparator);
	return exams;
}

static int indexOf(String acr, exam** exams){
	exam* res;
	exam* key = Exam_ctor(acr, '\0', -1);
	return ((res=bsearch(key, exams, sizeof(exams)/sizeof(exams[0]), sizeof(exams[0]), exams[0]->vptr->comparator))?(res-exams):-1);
}

