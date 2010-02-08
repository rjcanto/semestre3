#include "MandatorySameDayValidator.h"

static msdvMethods msdv_vtable={
	dtor,
	ruleName,
	setArgs,
	isValid
};

void* ctor(){
	msdv* m = malloc(sizeof(msdv));
	if (m==NULL){
		printf("MandatorySameDayValidator: malloc falhou.");
		exit(1);
	}
	m->vptr = &msdv_vtable;
	return (void*)(m);
}

void dtor(twoEV* this){
	if (this != NULL)
		free(this);
}

void setArgs(twoEV* this, String dest){
}

char* ruleName(){
	return "Duas UC obrigatorias do mesmo semestre ou consecutivos com exame no mesmo dia.";
}

int isValid(twoEV* this, exam* ex1, exam* ex2){
	if (!isSameOrConsecTerms(ex1, ex2))
		return 1;
	if (getType(getCourse(ex1)) == 'B' && getType(getCourse(ex2)))
		return (getDate1(ex1) != getDate1(ex2) && getDate2(ex1) != getDate2(ex2));
	return 1;
}

/*recebe dois exames e verifica se as UC respectivas funcionam no mesmo semestre ou em semestres consecutivos*/
int isSameOrConsecTerms(exam* ex1, exam* ex2){
	unsigned int terms1 = (unsigned int) getTerms(getCourse(ex1));
	unsigned int terms2 = (unsigned int) getTerms(getCourse(ex2));
	return (terms1 & terms2)? 1: (terms1 & (terms2>>1)) ? 1: (terms1 & (terms2<<1)) ? 1:0;
}

