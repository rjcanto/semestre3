#include <stdio.h>
#include <stdlib.h>
#include "myLib.h"

enum filter {NONE, SUB, UP, AVERAGE, PAETH};


int filter_none(byte* source, byte* dest, int size){
	int i, sum=0;
	dest[0]=NONE;
	for(i=0; i< size; ++i){
		sum+=dest[i+1]=source[i];
	}
	return sum;
}

int unfilter_none(byte* source, byte* dest, int size){
	int i;
	for(i=0; i< size; ++i){
		dest[i]=source[i+1];
	}
/*	fputs((char*)(source), dest);*/
	return SUCCESS;
}

int filter_sub(byte* source, byte* dest, int size, int bpp){
	int i, sum=0;
	dest[0]=SUB;
	for(i=0; i < bpp; ++i){
		sum+=dest[i+1]=source[i]; } /*dest[i+1] because dest[0]=filterType*/
	for(; i < size; ++i){
		sum+=dest[i+1]=source[i]-source[i-bpp]; }
	/*
	while (!feof(source)){
		fputc(SUB,dest);
		fread(curr,1,buffer_sz,source);
		
	}*/
	return sum;
}

int unfilter_sub(byte* source, byte* dest, int size, int bpp){
	int i;
	for(i=0; i < size; ++i){
		dest[i]=source[i+1]+source[i-bpp+1]; }
	return SUCCESS;
}

int filter_up(byte* source, byte* prev, byte* dest, int size, int bpp){
	int i, sum=0;
	dest[0]=UP;
	for(i=0; i < size; ++i){
		sum+=dest[i+1]=source[i]-prev[i]; }	
	return sum;
}

int unfilter_up(byte* source, byte* prev, byte* dest, int size, int bpp){
	int i;
	for(i=0; i < size; ++i){
		dest[i]=source[i+1]+prev[i]; }	
	return SUCCESS;
}

int filter_average(byte* source, byte* prev, byte* dest, int size, int bpp){
	int i, sum=0;
	dest[0]=AVERAGE;
	for(i=0; i < bpp; ++i){
		sum+=dest[i+1]=source[i]-prev[i]; }
	for(; i < size; ++i){
		sum+=dest[i+1]=source[i]-((source[i-bpp]+prev[i])/2); }	
	return sum;
}

int unfilter_average(byte* source, byte* prev, byte* dest, int size, int bpp){
	int i;
	for(i=0; i < bpp; ++i){
		dest[i]=source[i+1]-prev[i]; }
	for(; i < size; ++i){
		dest[i]=source[i+1]+((source[i-bpp+1]+prev[i])/2); }	
	return SUCCESS;
}

byte paethPredictor(byte left, byte upper, byte upper_left){
	byte p;
	int dist_l, dist_u, dist_ul;
	
	p=left+upper-upper_left;
	dist_l=abs(p-left);
	dist_u=abs(p-upper);
	dist_ul=abs(p-upper_left);
	
	if(dist_l <= dist_u && dist_l <= dist_ul)
		return left;
	else if(dist_u <= dist_ul)
		return upper;
	else
		return upper_left;
}

int filter_paeth(byte* source, byte* prev, byte* dest, int size, int bpp){
	int i, sum=0;
	dest[0]=PAETH;
	for(i=0; i < bpp; ++i){
		sum+=dest[i+1]=source[i]-prev[i]; }
	for(; i < size; ++i){
		sum+=dest[i+1]=source[i]-paethPredictor(source[i-bpp], prev[i], prev[i-bpp]); }
	return sum;
}

int unfilter_paeth(byte* source, byte* prev, byte* dest, int size, int bpp){
	int i;
	for(i=0; i < bpp; ++i){
		dest[i]=source[i+1]-prev[i]; }
	for(; i < size; ++i){
		dest[i]=source[i+1]+paethPredictor(source[i-bpp+1], prev[i], prev[i-bpp]); }
	return SUCCESS;
}

int filter_best(byte* source, byte* prev, byte* dest, int size, int bpp){
	int i, best, sum;
	byte aux_dest[size+1]; 
	
	best=filter_none(source, dest, size);
	strcpy(aux_dest, dest);
	
	sum=filter_sub(source, dest, size, bpp);
	if (sum < best){
		best=sum;
		strcpy(aux_dest, dest);
	}
	sum=filter_up(source, prev, dest, size, bpp);
	if (sum < best){
		best=sum;
		strcpy(aux_dest, dest);
	}
	sum=filter_average(source, prev, dest, size, bpp);
	if (sum < best){
		best=sum;
		strcpy(aux_dest, dest);
	}
	sum=filter_paeth(source, prev, dest, size, bpp);
	if (sum < best){
		best=sum;
		strcpy(aux_dest, dest);
	}
	strcpy(dest, aux_dest);
	return best;
}

int filterPNG(byte* source, byte* prev, byte* dest, int size, int bpp, int filterType){	
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

int unFilter(byte* source, byte* prev, byte* dest, int size, int bpp){
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
    byte* output[100];
	byte* previous[100];
    byte* input[100];
	
/*	input_file=fopen("./images/boxes_1.ppm","r");
	output_file=fopen("boxes_1.ppm.test","w");
	sub(input_file,output_file, 63*3);
	
	fcloseall;*/
	
	return SUCCESS;
}
