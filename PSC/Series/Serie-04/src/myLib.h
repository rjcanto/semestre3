#ifndef MYLIB_H
#define MYLIB_H

#include <stdlib.h>
#include <stdio.h>
#include "Exception.h"
#include <string.h>
#define SUCCESS 0;
#define UNSUCCESS 1;
#define INT_EXCEPTION 0xFFFF

typedef unsigned char byte;
typedef char* String;
enum boolean {false,true};


int parseInt(jmp_buf jmp, const String string);

String 	xstrtrim	(String string);
void 	mallocError	(String str);

#endif
