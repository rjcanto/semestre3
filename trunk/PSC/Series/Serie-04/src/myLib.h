#ifndef MYLIB_H
#define MYLIB_H

#include "Exception.h"
#define SUCCESS 0;
#define UNSUCCESS 1;
#define INT_EXCEPTION 0xFFFF

enum boolean {false,true};
typedef unsigned char byte;
typedef char* String;


int parseInt(const String string);




#endif
