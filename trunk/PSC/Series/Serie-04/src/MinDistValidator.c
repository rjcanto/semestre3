#include "MinDistValidator.h"

static mdvMethods mdv_vtable={
	dtor,
	ruleName,
	setArgs,
	isValid
};

void* ctor(){
	mdv* m = malloc(sizeof(mdv));
	m->vptr = &mdv_vtable;                     
	m->minDist=13;
	return (void*)(m);
}

void dtor(oneEV* this){
	if (this != NULL)
		free(this);
}

void setArgs(oneEV* this, String dest){
	((mdv*)(this))->minDist = mdv_parseInt(dest);
}

char* ruleName(){
	return "Distancia minima entre exames da mesma UC.";
}

int isValid(oneEV* this, exam* ex){
	return (getDate2(ex) - getDate1(ex) >= ((mdv*)(this))->minDist);
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


