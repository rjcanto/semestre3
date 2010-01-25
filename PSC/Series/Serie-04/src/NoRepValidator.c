#include <stdio.h>
#include 'myLib.h'
#include 'NoRepValidator.h';


static nrvMethods nrv_vtable={
	dtor,
	setArgs,
	ruleName,
	isValid
};

nrv* nrv_ctor(){
	nrv* n = (nrv *)malloc(sizeof(nrv));
	n->vptr = &nrv_table;                     
	return n;
}

static void setArgs (nrv* this, String dest){
	this->minDist = parseInt(dest);
}

static String ruleName (nrv* this){
	return "Sobreposicoes nao se repetem nas duas epocas.";
}

static boolean isValid(nrv* this, Exam *exam1, Exam *exam2){
	return (exam1->vptr->date1() != exam2->vptr->date1() ||
			exam1->vptr->date2() != exam2->vptr->date2());
}

static void dtor(nrv *this){
	if (this != null)
		free(this);
}
