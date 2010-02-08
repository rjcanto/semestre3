#include "MinDistDependentValidator.h"

static mddvMethods mddv_vtable={
	dtor,
	ruleName,
	setArgs,
	isValid
};

void* ctor(){
	mddv* m = malloc(sizeof(mddv));
	if (m==NULL){
		printf("MinDistDependentValidator: malloc falhou.");
		exit(1);
	}
	m->vptr = &mddv_vtable;                     
	m->mi=0;
	m->md=0;
	return (void*)(m);
}

void dtor(twoEV* this){
	if (this != NULL)
		free(this);
}
/* Em dest recebe os argumentos para mi e md separados por ;*/ 
void setArgs(twoEV* this, String dest){
	String mistr=dest;
	String mdstr=dest-1;
	while((++mdstr)!=0){
		if ((*mdstr)==';'){
			(*mdstr++)=0;
			break;
		}
	}
	((mddv*)(this))->mi = mdv_parseInt(mistr);
	if ((((mddv*)(this))->md = mdv_parseInt(mdstr)) > getMdi(this))
		((mddv*)(this))->md = getMdi(this);
}

char* ruleName(){
	return "Distancia minima entre exames de UCs de semestres consecutivos.";
}

int isValid(twoEV* this, exam* ex1, exam* ex2){
	if (!isConsecTerms(ex1,ex2))
		return 1;
	if (isSDep(ex1,ex2))
		return ((abs(getDate1(ex1) - getDate1(ex2))) >= ((mddv*)(this))->md && (abs(getDate2(ex1) - getDate2(ex2))) >= ((mddv*)(this))->md);
	return ((abs(getDate1(ex1) - getDate1(ex2))) >= ((mddv*)(this))->mi && (abs(getDate2(ex1) - getDate2(ex2))) >= ((mddv*)(this))->mi);
}
/*recebe dois exames e verifica se as UC são dependencias fortes uma da outra*/
int isSDep(exam* ex1, exam* ex2){
	int i=0;
	while(getSDep(getCourse(ex1))[i]){
		if(!strcmp(getSDep(getCourse(ex1))[i++], getAcronym(getCourse(ex2))))
			return 1;
	}
	i=0;
	while(getSDep(getCourse(ex2))[i]){
		if(!strcmp((getSDep(getCourse(ex2))[i++]), getAcronym(getCourse(ex1))))
			return 1;
	}
	return 0;
}

/*recebe dois exames e verifica se as UC respectivas funcionam em semestres consecutivos*/
int isConsecTerms(exam* ex1, exam* ex2){
	unsigned int terms1 = (unsigned int) getTerms(getCourse(ex1));
	unsigned int terms2 = (unsigned int) getTerms(getCourse(ex2));
	return (terms1 & (terms2>>1)) ? 1: (terms1 & (terms2<<1)) ? 1:0;
}


int mdv_parseInt(const String string){
	int number=0;
	String i = string;
	while (*i!=0 && *i>='0' && *i <='9'){
		number=number*10 +(*i-'0');
		++i;
	}    
    return number;
}


