#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtersPNG.h"

int filter_none(byte source[], byte dest[], int size){
	int i, sum=0;
	dest[0]='0';
	for(i=0; i< size; ++i){
		sum+=dest[i+1]=source[i];
	}
	return sum;
}

int unfilter_none(byte source[], byte dest[], int size){
	int i;
	for(i=0; i< size; ++i){
		dest[i]=source[i+1];
	}
	return SUCCESS;
}

int filter_sub(byte source[], byte dest[], int size, int bpp){
	int i, sum=0;
	dest[0]='1';
	for(i=0; i < bpp; ++i){
		sum+=dest[i+1]=source[i]; } /*(*dest[i+1]) because dest[0]=filterType*/
	for(; i < size; ++i){
		sum+=dest[i+1]=source[i]-source[i-bpp]; }
	return sum;
}

int unfilter_sub(byte source[], byte dest[], int size, int bpp){
	int i;
	for(i=0; i < bpp; ++i){
		dest[i]=source[i+1]; }	
	for(; i < size; ++i){
		dest[i]=source[i+1]+source[i-bpp+1]; }
	return SUCCESS;
}

int filter_up(byte source[], byte prev[], byte dest[], int size, int bpp){
	int i, sum=0;
	dest[0]='2';
	for(i=0; i < size; ++i){
		sum+=dest[i+1]=source[i]-prev[i]; }	
	return sum;
}

int unfilter_up(byte source[], byte prev[], byte dest[], int size, int bpp){
	int i;
	for(i=0; i < size; ++i){
		dest[i]=source[i+1]+prev[i]; }	
	return SUCCESS;
}

int filter_average(byte source[], byte prev[], byte dest[], int size, int bpp){
	int i, sum=0;
	dest[0]='3';
	for(i=0; i < bpp; ++i){
		sum+= dest[i+1]=source[i]-prev[i]; }
	for(; i < size; ++i){
		sum+=dest[i+1]=source[i]-((source[i-bpp]+prev[i])/2); }	
	return sum;
}

int unfilter_average(byte source[], byte prev[], byte dest[], int size, int bpp){
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

int filter_paeth(byte source[], byte prev[], byte dest[], int size, int bpp){
	int i, sum=0;
	dest[0]='4';
	for(i=0; i < bpp; ++i){
		sum+=dest[i+1]=source[i]-prev[i]; }
	for(; i < size; ++i){
		sum+=dest[i+1]=source[i]-paethPredictor(source[i-bpp], prev[i], prev[i-bpp]); }
	return sum;
}

int unfilter_paeth(byte source[], byte prev[], byte dest[], int size, int bpp){
	int i;
	for(i=0; i < bpp; ++i){
		dest[i]=source[i+1]-prev[i]; }
	for(; i < size; ++i){
		dest[i]=source[i+1]+paethPredictor(source[i-bpp+1], prev[i], prev[i-bpp]); }
	return SUCCESS;
}

int filter_best(byte source[], byte prev[], byte dest[], int size, int bpp){
	int best, sum;
	byte* aux_dest = (byte*) (malloc(size+1));
	
	best=filter_none(source, dest, size);
	memcpy(dest, aux_dest, size+1);
		
	sum=filter_sub(source, dest, size, bpp);
	if (sum < best){
		best=sum;
		memcpy(dest, aux_dest, size+1);
	}
	sum=filter_up(source, prev, dest, size, bpp);
	if (sum < best){
		best=sum;
		memcpy(dest, aux_dest, size+1);
	}
	sum=filter_average(source, prev, dest, size, bpp);
	if (sum < best){
		best=sum;
		memcpy(dest, aux_dest, size+1);
	}
	sum=filter_paeth(source, prev, dest, size, bpp);
	if (sum < best){
		best=sum;
		memcpy(dest, aux_dest, size+1);
	}
	memcpy(aux_dest, dest, size+1);
	free(aux_dest);
	return best;
}

int filterPNG(byte source[], byte prev[], byte dest[], int size, int bpp, int type){	
	
	switch (type){
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
		case BEST:
			filter_best(source, prev, dest, size, bpp);
		break;
		case NONE:
		default:
			filter_none(source, dest, size);
		break;
		} 
	return SUCCESS;
}

int unfilterPNG(byte source[], byte prev[], byte dest[], int size, int bpp){
	byte aux = source[0];

	switch (aux){
			case '0':
				unfilter_none(source, dest, size);
			break;		
			case '1':
				unfilter_sub(source, dest, size, bpp);
			break;
			case '2':
				unfilter_up(source, prev, dest, size, bpp);
			break;
			case '3':
				unfilter_average(source, prev, dest, size, bpp);
			break;
			case '4':			
				unfilter_paeth(source, prev, dest, size, bpp);
			break;
			default:
				return UNSUCCESS;
			break;
		} 
	return SUCCESS;
}
