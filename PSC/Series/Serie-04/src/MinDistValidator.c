#include <stdio.h>
#include 'myLib.h'
#include 'MinDistValidator.h';


static mdvMethods mdv_vtable={
	dtor,
	setArgs,
	ruleName,
	isValid
};

mdv* mdv_ctor(){
	mdv* m = (mdv *)malloc(sizeof(mdv));
	m->vptr = &mdv_table;                     
	return m;
}

static void setArgs(mdv* this, String dest){
	this->minDist = parseInt(dest);
}

static String ruleName(mdv* this){
	return "Distancia minima entre exames da mesma UC.";
}

static boolean isValid(mdv* this, Exam *exam){
	return (exam->vptr->date2() - exam->vptr->date1() >= this->minDist);
}

static void dtor(mdv *this){
	if (this != null)
		free(this);
}



