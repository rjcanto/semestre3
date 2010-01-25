#ifndef DATALOADER_H
#define DATALOADER_H

#include <stdio.h>
#include "myLib.h"
#define IO_ERROR_EXCEPTION 0xFFFE
#define MAX_ITEMS 10

typedef struct DataLoader dldr;

typedef void* ItemType;

typedef struct DataLoader_vtable{
	void 		(*dtor) 		(dldr *this);
	ItemType*	(*newArray)		(int numEntries);
	ItemType	(*newInstance)	(String* elems);
	ItemType*	(*loadFrom)		(dldr *this, String filename);
	ItemType*	(*build)		(dldr *this, int n);
} dldrMethods;

struct DataLoader{
	dldrMethods *vptr;
	FILE* input;
};

dldr* DataLoader_ctor();
	
#endif
