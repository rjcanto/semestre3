/**
 * Terceira série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 */

#ifndef IMAGEFORMAT_H
#define IMAGEFORMAT_H

typedef struct FileHeader{
	int magicValue;
	int imageWidth;
	int imageHeight;
	int maxGrey;
	int isFilled;
} header;

void initFileHeader(struct FileHeader *fh);

void listfileHeader(char* filename,struct FileHeader *fh,int nbrChars);
 
void fillHeader(struct FileHeader *fh, int value);

int processFileHeader(char *filename, struct FileHeader *fhp);

int processFileHeader(char *filename, struct FileHeader *fhp);

#endif
