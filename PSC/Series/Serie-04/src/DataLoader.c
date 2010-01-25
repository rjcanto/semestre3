#include <stdio.h>
#include "myLib.h"
#include "DataLoader.h"

static void 		DataLoader_dtor		(dldr * this);
static ItemType* 	loadFrom			(dldr *this, String filename);
static ItemType*	build				(dldr *this, int n);
static ItemType*	newArray			(int numEntries);
static ItemType 	newInstance			(String* elems);


static dldrMethods dldr_vtable={
	DataLoader_dtor,
	newArray,
	newInstance,
	loadFrom,
	build
};

dldr* DataLoader_ctor(){
	dldr* m = (dldr *)malloc(sizeof(dldr));
	m->vptr = &dldr_vtable; 
	return m;
}

static void DataLoader_dtor(dldr *this){
	if (this != NULL)
		free(this);
}

static ItemType* loadFrom(dldr *this, String filename){
	ItemType* res;
	this->input=fopen(filename, "r");
	res=this->vptr->build(this,0);
	fclose(this->input);
	return res;
}

static ItemType* build(dldr *this, int n){
	int idx=0, i=0;
	ItemType* item=NULL;
	ItemType* items=NULL;
	String line;
	String* elems;
	
	fgets(line, 20,this->input);
	
	if (line==NULL){
		if (!feof(this->input))
			return NULL;	/*THROW(IO_ERROR_EXCEPTION);*/
		else
			return this->vptr->newArray(n);
	}
		
	/*contar o num de tokens e alocar espaco do elems*/
	/*assumimos que existem um maximo de MAX_ITEMS por linha*/
	*elems = (String) malloc(sizeof(String)*MAX_ITEMS);
		
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
		items=this->vptr->build(this, n+1);
		if (items == NULL)
			items = malloc(sizeof(ItemType)*n);
		items[n] = item;
		return items;
	}
	return this->vptr->build(this, n);	
}






