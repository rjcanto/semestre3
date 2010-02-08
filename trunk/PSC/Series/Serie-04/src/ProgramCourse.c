#include "ProgramCourse.h"

static prgcourseMethods prgcourse_vtable={
	ProgramCourse_dtor,
	pc_comparator,
	pc_loadFrom,
	pc_indexOf
};

static arrayMethods prgcourseArray_vtable={
	ProgramCourseArray_dtor
};

void ProgramCourse_dtor(prgcourse * this){
	if (this!=NULL){
		if (this->acronym)
			free(this->acronym);
		if (this->sdep)
			free(this->sdep);
		if (this->wdep)
			free(this->wdep);
		free(this);
	}
}

void ProgramCourseArray_dtor(PrgCourseArray* this){
	int i=0;
	for (i=0; i<length(this); ++i)
		getArrayPosPC(this,i)->vptr->dtor(getArrayPosPC(this,i));
	free(this->array);
	free(this);
}

String* processDependents(String str){
	int i, idx=0;
	String* depUC = (String*) malloc(sizeof(String)*(MAX_DEP_UC+1));
		
	while((depUC[idx]=strtok(str,";"))!=NULL){
		++idx;
		str=NULL;
	}
	if(idx>0 && strlen(depUC[0])>0)
		for (i=0; i<idx; ++i)
			depUC[i]=xstrtrim(depUC[i]);
	return depUC;
}

prgcourse* ProgramCourse_ctor(String acronym, char type, int terms, String sdep, String wdep){
	prgcourse *p = (prgcourse *)malloc(sizeof(prgcourse));
	if (acronym){
		p->acronym = (String) malloc(strlen(acronym)+1*sizeof(char));
		strcpy(p->acronym,acronym);
	}
	p->sdep = processDependents(sdep);
	p->wdep = processDependents(wdep);
	p->type = type;
	p->terms = terms;
	p->vptr = &prgcourse_vtable;
	return p;
}

PrgCourseArray* ProgramCourseArray_ctor(){
	PrgCourseArray* aux= (PrgCourseArray*) (malloc(sizeof(PrgCourseArray)));
	aux->vptr = &prgcourseArray_vtable;
	aux->size=0;
	return aux;
}

void** pc_newArray(int numEntries){
	void** aux =  malloc(sizeof(prgcourse*) * numEntries);
	return aux;
}

void* pc_newInstance(String* elems, int nbr){
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
	return ProgramCourse_ctor(elems[0], type, trms, elems[3], elems[4]);
}

int pc_comparator(const void *pc1, const void *pc2){	
	return (strcmp( getAcronym(pc1),getAcronym(pc2))); 
}

PrgCourseArray* pc_loadFrom(String filename){
	dldr* loader = DataLoader_ctor();
	PrgCourseArray* coursesArray = ProgramCourseArray_ctor();
	loader->vptr->newArray = &pc_newArray;
	loader->vptr->newInstance = &pc_newInstance;
	coursesArray = loader->vptr->loadFrom(loader,coursesArray, filename);
/*	qsort((prgcourse**) (coursesArray->array),length(coursesArray), sizeof(courses), pc_comparator);*/
	loader->vptr->dtor(loader);
	return coursesArray;
}

int pc_indexOf(String acr, PrgCourseArray* courses){
	/*prgcourse* res;*/
	prgcourse* key = ProgramCourse_ctor(acr, '\0', -1, '\0', '\0');
	int idx;
	for(idx=0; idx<length(courses); ++idx)
		if (pc_comparator(getArrayPosPC(courses,idx), key) ==0){
			key->vptr->dtor(key);
			return idx;
	}	
	key->vptr->dtor(key);
	return -1;
}


