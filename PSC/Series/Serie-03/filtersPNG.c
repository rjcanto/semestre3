#include <stdio.h>
#include "myLib.h"

enum filter {NONE, SUB, UP, AVERAGE, PAETH};


int filter_none(byte[]* source, byte[]* dest, int size){
	int i;
	dest[0]=NONE;
	for(i=0; i< size; ++i){
		dest[i+1]=source[i]
	}
	return SUCCESS;
}

int unfilter_none(byte[]* source, byte[]* dest, int size){
	int i;
	for(i=0; i< size; ++i){
		dest[i]=source[i+1]
	}
/*	fputs((char*)(source), dest);*/
	return SUCCESS;
}

int filter_sub(byte[]* source, byte[]* dest, int size, int bpp){
	int i, sum;
	dest[0]=SUB;
	for(i=0; i < bpp; ++i){
		sum+=dest[i+1]=source[i] } /*dest[i+1] because dest[0]=filterType*/
	for(i; i < size; ++i){
		sum+=dest[i+1]=source[i]-source[i-bpp] }
	/*
	while (!feof(source)){
		fputc(SUB,dest);
		fread(curr,1,buffer_sz,source);
		
	}*/
	return sum;
}

int unfilter_sub(byte[]* source, byte[]* dest, int size, int bpp){
	int i;
	for(i=0; i < bpp; ++i){
		dest[i]=source[i+1] }
	for(i; i < size; ++i){
		dest[i]=source[i+1]+source[i-bpp+1] }
	return SUCCESS;
}


int filter_up(byte[]* source, byte[]* prev, byte[]* dest, int size, int bpp){

	return SUCCESS;
}


int filter_average(FILE* source, FILE* dest, int buffer_sz){

	return SUCCESS;
}

int filter_paeth(FILE* source, FILE* dest, int buffer_sz){

	return SUCCESS;
}

int filterPNG(byte[]* source, byte[]* prev, byte[]* dest, int size, int bpp, int filterType){	
	switch (filterType){
		case SUB:
			filter_sub(source, dest, size, bpp);
		break;
		case UP:
			filter_up(source, prev, dest, size, bpp);
		break;
		case AVERAGE:
			filter_average(source, prev, dest, size, bpp);
		break;
		case PAETH:
			filter_paeth(source, prev, dest, size, bpp);
		break;
		case 128:
			filter_best(source, prev, dest, size, bpp);
		break;
		case NONE:
		default:
			filter_none(source, dest, size);
		break;
		}
	return SUCCESS;
}

int unFilter(byte[]* source, byte[]* prev, byte[]* dest, int size, int bpp){
	/*byte *aux;
	fr-ead(aux, sizeof(aux), 1, source);*/
	byte aux = source[0];
	switch (aux){
			case NONE:
				unfilter_none(source, dest, size);
			break;		
			case SUB:
				unfilter_sub(source, dest, size, bpp);
			break;
			case UP:
				unfilter_up(source, prev, dest, size, bpp);
			break;
			case AVERAGE:
				unfilter_average(source, prev, dest, size, bpp);
			break;
			case PAETH:			
				unfilter_paeth(source, prev, dest, size, bpp);
			break;
			default:
				return UNSUCCESS;
			break;
		}
	return SUCCESS;
}


int main(int argc, char *argv[]) {
    char *output_file;
    char *input_file;
	
	input_file=fopen("./images/boxes_1.ppm","r");
	output_file=fopen("boxes_1.ppm.test","w");
	sub(input_file,output_file, 63*3);
	
	fcloseall;
	
	return SUCCESS;
}
