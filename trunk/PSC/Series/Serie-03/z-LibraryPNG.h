#ifndef ZLIBRARY_H
#define ZLIBRARY_H
/* *
 * Definição de Bibliotecas Necessárias
 * */
#ifndef STDIO_DEF
#define STDIO_DEF
#include <stdio.h>
#endif

#include <string.h>
#include <assert.h>
#include "mylib.h"
#include "zlib.h"
#include "imageFormat.h"

/* *
 * Definição de um Work-Around para os ambientes Windows
 * */

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

/* *
 * Definição do tamanho do CHUNK
 * */

#define KBYTES 1024
/*#define CHUNK 128*KBYTES*/

struct filterSettings;

int my_compress(FILE *source, FILE *dest, int level, struct filterSettings myfilter);

int my_decompress(FILE *source, FILE *dest, struct filterSettings myfilter);

void my_errors(int ret);

void progUsage(char *program);

typedef unsigned char boolean;

enum action {compress_action,decompress_action};

typedef struct cmdLnArgs{
		int action;
		char * source;
		char * destination;
		int compressLevel;
		int filter;
		boolean destParsed;
}myArgs;

typedef struct filterSettings{
		int type;
		boolean firstLine;
		int nbrChars;
		int lineSize;
		int bpp;
}myFilter;

#endif
