#include "Exam.h"

examldr* eldr;

static examMethods exam_vtable={
	Exam_dtor,
	e_comparator,
	e_loadFrom,
	e_indexOf
};

static arrayMethods examArray_vtable={
	ExamArray_dtor
};

static examLoaderMethods examLoader_vtable={
	ExamLoader_dtor,
};

void Exam_dtor(exam *this){
	if (this!=NULL){
		/*this->course->vptr->dtor(this->course);*/ /*destrutor de exam não pode apagar dados do array prgcourses recebidoS*/
		free(this);
	}
}

void ExamArray_dtor(ExamArray* this){
	int i;
	for (i=0; i<this->size; ++i)
		getArrayPosE(this,i)->vptr->dtor(getArrayPosE(this,i));
	free(getArrayE(this));
	free(this);
}

void ExamLoader_dtor(examldr* this){
	if (this!=NULL){
		this->loader->vptr->dtor(this->loader);
		free(this);
	}
}

exam* Exam_ctor(prgcourse* course, int date1, int date2){
	exam *e = (exam*) malloc(sizeof(exam));
	e->vptr = &exam_vtable;
	e->course = course;
	e->date1 = date1;
	e->date2 = date2;
	return e;
}

ExamArray* ExamArray_ctor(){
	ExamArray* arr = (ExamArray*) (malloc(sizeof(ExamArray)));
	arr->vptr = &examArray_vtable;
	arr->size=0;
	return arr;
}

examldr* ExamLoader_ctor(ExamArray* courses){
	eldr = malloc(sizeof(examldr));
	eldr->vptr = &examLoader_vtable;
	eldr->loader = DataLoader_ctor(); 
	eldr->loader->vptr->newArray = &e_newArray;
	eldr->loader->vptr->newInstance = &e_newInstance;
	eldr->coursesArray = courses;
	return eldr;
}

void** e_newArray(int numEntries){
	void** aux = malloc(sizeof(exam*) * numEntries);
	return aux;
}

void* e_newInstance(String* elems, int nbr){
	int index;
	int num1=INT_MIN_VALUE, num2=INT_MIN_VALUE;
	index = pc_indexOf(elems[0], eldr->coursesArray);
	if (index<0) return NULL;
	if (strlen(elems[1])<4){
		TRY{
		num1=parseInt(jmp, elems[1]);
		} CATCH(INT_EXCEPTION){
			num1=INT_MIN_VALUE;
		}
		}	/* END OF TRY BLOCK */
	}
	if (nbr>1){
		TRY{
		num2=parseInt(jmp, elems[2]);
		} CATCH(INT_EXCEPTION){
			num2=INT_MIN_VALUE;
		}
		}	/* END OF TRY BLOCK */		
	}
	return (void*) Exam_ctor(getArrayPosPC(eldr->coursesArray,index),num1, num2); 
}

int e_comparator(const void* e1, const void* e2){
	return (strcmp(getAcronym(getCourse(e1)), getAcronym(getCourse(e2)))); 
}

ExamArray* e_loadFrom(String filename, ExamArray* courses){
	ExamArray* examArr = ExamArray_ctor();
	eldr = ExamLoader_ctor(courses);
	examArr = eldr->loader->vptr->loadFrom(eldr->loader, examArr, filename);
	/*qsort((exam**)(examArr->array),length(examArr), sizeof(exam), e_comparator);*/
	eldr->vptr->dtor(eldr);
	return examArr;
}

int e_indexOf(String acr, ExamArray* examsArr){
	int idx;
	exam* key = Exam_ctor(ProgramCourse_ctor(acr,0,-1,'\0','\0'), '\0', -1);
	for(idx=0; idx<length(examsArr);++idx)
		if(e_comparator(getArrayPosE(examsArr,idx),key) == 0){
			key->vptr->dtor(key);
			return idx;
		}
	return -1;
}
