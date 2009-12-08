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
#define CHUNK 128*KBYTES

int my_compress(FILE *source, FILE *dest, int level);

int my_decompress(FILE *source, FILE *dest);

void my_errors(int ret);

void progUsage(char *program);

typedef unsigned char boolean;

enum action {compress_action,decompress_action};

typedef struct cmdLnArgs{
		int action;
		char * source;
		char * destination;
		int compressLevel;
		boolean destParsed;
}myArgs;
#endif
