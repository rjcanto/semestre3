#include "Exam.h"



static examMethods exam_vtable={
	Exam_dtor,
	Exam_cleanup,
	e_comparator,
	e_loadfrom,
	e_indexOf
};

static void Exam_dtor(exam *this){
	if (this!=NULL){
		if (this->acronym)
			free(this->acronym);
		this->loader->vptr->dtor(this->loader);
		free(this);
	}
}

static void Exam_cleanup(exam[] *this){
	int i=0, size = sizeof(this)/sizeof(this[0]);
	for (i, i<size,++i)
		this[i]->vptr->dtor(this[i]);
}
	
static exam* Exam_ctor(prgcourse course, int date1, int date2){
	exam *e = (exam *)malloc(sizeof(exam));
	e->vptr = &exam_vtable;
	e->course = course;
	e->date1 = date1;
	e->date2 = date2;
	
	/*p->loader = DataLoader_ctor();
	p->loader->vptr->newArray = &pc_newArray;
	p->loader->vptr->newInstance = &pc_newInstance;*/
	
	return p;
}

static prgcourse[] pc_newArray(int numEntries){
	prgcourse[] aux = (prgcourse[]) malloc(sizeof(prgcourse*) * numEntries);
	return aux;
}

static prgcourse* pc_newInstance(String[] elems){
	char type;
	int trms, i=0;	
	if (elems[0] == NULL) 
		return NULL;
	type = (strlen(elems[1])==1) ? (*elems[1]):'\0');
	if (srtlen(elems[2])<10){
		TRY{
		trms=parseInt(elems[2]);
		} CATCH(INT_EXCEPTION){
			trms=-1;
		}
		}	/* END OF TRY BLOCK */
	}
	return ProgramCourse_ctor(elems[0], type, trms);
}

static int e_comparator(exam *e1, exam e2){
	return (strcmp(e1->course->acronym, e2->course->acronym)); 
}

static prgcourse[]* e_loadFrom(prgcourse[]* courses, String filename){
	courses = (prgcourse[]) loadFrom(loader, filename);
	qsort(this, sizeof(courses)/sizeof(courses[0]), sizeof(courses[0]), courses[0]->vptr->comparator);
	return courses;
}

static int indexOf(String acr, exam[] exams){
	int res;
	exam* key = ProgramCourse_ctor(acr, '\0', -1);
	return (res=bsearch(key, courses, sizeof(courses)/sizeof(courses[0]), sizeof(courses[0]), courses[0]->vptr->comparator))?(res-courses):-1;
}
	
	
} 
