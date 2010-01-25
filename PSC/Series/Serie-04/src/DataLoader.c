#include <stdio.h>
#include "myLib.h"
#include "DataLoader.h"

static dldrMethods dldr_vtable={
	DataLoader_dtor,
	NULL,
	NULL,
	loadFrom,
	build
};

dldr* DataLoader_ctor(){
	dldr* d = (dldr *)malloc(sizeof(dldr));
	d->vptr = &dldr_vtable; 
	return d;
}

void DataLoader_dtor(dldr *this){
	if (this != NULL)
		free(this);
}

ItemType* loadFrom(dldr *this, String filename){
	ItemType* res;
	this->input=fopen(filename, "r");
	puts(filename);
	res=this->vptr->build(this,0);
	fclose(this->input);
	puts("DataLoader.loadFrom");
	printf("size of array: %i\n", sizeof(res));
	printf("size of array[0]: %i\n", sizeof(res[0]));
	return res;
}

ItemType* build(dldr *this, int n){
	int idx=0, i=0;
	ItemType* item=NULL;
	ItemType* items=NULL;
	String line = (String) malloc(sizeof(String)*MAX_LINE_SZ);
	String* elems = (String*) malloc(sizeof(String)*MAX_ITEMS);

	if ((fgets(line, 30,this->input))==NULL){
		if (!feof(this->input))
			return NULL;	/*THROW(IO_ERROR_EXCEPTION);*/
		else
			return this->vptr->newArray(n);
	}
		
	/*contar o num de tokens e alocar espaco do elems*/
	/*assumimos que existem um maximo de MAX_ITEMS por linha*/
		
	while((elems[idx]=strtok(line,"\\|"))!=NULL){
		++idx;
		line=NULL;
	}
	
	if(idx>0 && strlen(elems[0])>0){
		for (i=0; i<idx; ++i){
			elems[i]=xstrtrim(elems[i]);
		}
		item = this->vptr->newInstance(elems);	
	}
	
	if(item != NULL){
		items = build(this, n+1);
			/*items = malloc(sizeof(ItemType)*n);*/
			printf("n: %i\n", n);
		items[n] = item;
		return items;
	}
	return this->vptr->build(this, n);	
}






