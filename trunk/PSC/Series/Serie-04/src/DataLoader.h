#ifndef DATALOADER_H
#define DATALOADER_H

#include <stdio.h>
#include "myLib.h"
#define IO_ERROR_EXCEPTION 0xFFFE
#define MAX_ITEMS 10
#define MAX_LINE_SZ 30

typedef struct DataLoader dldr;
typedef void* ItemType;
typedef struct ItemTypeArray arrayItem;

dldr* 		DataLoader_ctor		();
void 		DataLoader_dtor		(dldr * this);
arrayItem* 	loadFrom			(dldr *this, arrayItem* arr, String filename);
arrayItem*	build				(dldr *this, arrayItem* arr, int n);

typedef struct DataLoader_vtable{
	void 		(*dtor) 		(dldr *this);
	ItemType*	(*newArray)		(int numEntries);
	ItemType	(*newInstance)	(String* elems, int nbr);
	arrayItem*	(*loadFrom)		(dldr *this, arrayItem* arr, String filename);
	arrayItem*	(*build)		(dldr *this, arrayItem* arr, int n);
} dldrMethods;

typedef struct ItemTypeArray_vtable{
	void		(*dtor)			(arrayItem* this);
} arrayMethods;

struct DataLoader{
	dldrMethods *vptr;
	FILE* input;
};

struct ItemTypeArray{
	arrayMethods *vptr;
	ItemType* array;
	int size;
};

#define length(this)		(((const arrayItem * const)(this))->size)
#define getArray(this)		(this->array)
#define getArrayPos(var,i)	(var->array[i])


#endif
