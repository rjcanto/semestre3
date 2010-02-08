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
	if(d==NULL) mallocError("DataLoader");
	d->input = NULL;
	d->vptr = &dldr_vtable; 
	return d;
}

void DataLoader_dtor(dldr *this){
	if (this != NULL)
		free(this);
}

arrayItem* loadFrom(dldr* this, arrayItem* arr, String filename){
	FILE* xpto = fopen(filename, "r");
	if (!xpto){
		printf("Erro a ler o ficheiro: %s.\n\n",filename);
		exit(1);
	}
	this->input = xpto;
	this->vptr->build(this,arr,0);
	fclose(this->input);
	return arr;
}

arrayItem* build(dldr* this, arrayItem* arr, int n){
	int idx=0, i=0;
	ItemType* item=NULL;
	String line ;
	String* elems; 

	line = (String) malloc(sizeof(char)*MAX_LINE_SZ+1);
	if (line==NULL) mallocError("DataLoader");
	
	if ((fgets(line, MAX_LINE_SZ,this->input))==NULL){
		if (!feof(this->input)){
			free(line);
			return NULL;	/*THROW(IO_ERROR_EXCEPTION);*/
		}
		else{
			arr->size = n;
			arr->array=this->vptr->newArray(n);
			free(line);
			return arr;
		}
	}
	
	elems = (String*) malloc(sizeof(String)*MAX_ITEMS);
	if (elems==NULL) mallocError("DataLoader");
	
	/*contar o num de tokens e alocar espaco do elems*/
	/*assumimos que existem um maximo de MAX_ITEMS por linha*/
	while((elems[idx]=strtok(line,"\\|"))!=NULL){
		++idx;
		line=NULL;
	}
	free(line);
	
	if(idx>0 && strlen(elems[0])>0){
		for (i=0; i<idx; ++i){
			elems[i]=xstrtrim(elems[i]);
		}
		item = this->vptr->newInstance(elems, idx);
		free(elems);
	}
	
	if(item != NULL){
		arr = build(this,arr, n+1);
			/*printf("n: %i\n", n);	DEBUG*/
		arr->array[n] = item;
		return arr;
	}
	return this->vptr->build(this,arr, n);	
}




