#include <stdio.h>
#include "myLib.h"
#include "NoRepValidator.h"


static nrvMethods nrv_vtable={
	dtor,
	ruleName,
	setArgs,
	isValid
};

void* ctor(){
	nrv* n = (nrv*)malloc(sizeof(nrv));
	n->vptr = &nrv_vtable;                     
	return (void*)(n);
}

void dtor(twoEV* this){
	if (this != NULL)
		free(this);
}

void setArgs (twoEV* this, String dest){
}

String ruleName (){
	return "Sobreposicoes nao se repetem nas duas epocas.";
}

int isValid(twoEV* this, exam *exam1, exam *exam2){
	return (getDate1(exam1) != getDate1(exam2) ||
			getDate2(exam1) != getDate2(exam2));
}





