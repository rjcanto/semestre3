#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtersPNG.h"


int filter_none(byte source[], byte dest[], int size){
	int i, sum=0;
	dest[0]=NONE;
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
	dest[0]=SUB;
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
	dest[0]=UP;
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
	dest[0]=AVERAGE;
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
	dest[0]=PAETH;
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

void copyByteArray(byte source[], byte dest[], int size){
	int i;
	for(i=0; i<size; ++i)
		dest[i]=source[i];
}

int filter_best(byte source[], byte prev[], byte dest[], int size, int bpp){
	int best, sum;
	byte* aux_dest = (byte*) (malloc(size+1));
	
	
	best=filter_none(source, dest, size);
	copyByteArray(dest, aux_dest, size+1);
	
	sum=filter_sub(source, dest, size, bpp);
	if (sum < best){
		best=sum;
		copyByteArray(dest, aux_dest, size+1);
	}
	sum=filter_up(source, prev, dest, size, bpp);
	if (sum < best){
		best=sum;
		copyByteArray(dest, aux_dest, size+1);
	}
	sum=filter_average(source, prev, dest, size, bpp);
	if (sum < best){
		best=sum;
		copyByteArray(dest, aux_dest, size+1);
	}
	sum=filter_paeth(source, prev, dest, size, bpp);
	if (sum < best){
		best=sum;
		copyByteArray(dest, aux_dest, size+1);
	}
	copyByteArray(aux_dest, dest, size+1);
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

/*
int main(int argc, char *argv[]) {
    
	header *fhp;
    int nbrChars=0;
	int chunk=63*3;
	FILE *sourceFile;
	FILE *destinationFile;
	FILE *finalFile;
	byte in[63*3+1];
	byte out[63*3+1];
	byte prev[63*3+1];
	byte aux[50];
	int i=0;
    if (argc == 1) {
        puts("Need at least one argument to be processed!");
        return UNSUCCESS;
    }
	
	fhp = (header*)(malloc(sizeof(header)));
	
	for(i=0;i<chunk+1;++i)
		prev[i]=0;
	
	i=0;
	
    while ((argc-1) > 0) {
        argc--;
		nbrChars=processFileHeader(argv[argc],fhp);
		printf("nbrChars %d \n",nbrChars);
		
		
		chunk=(fhp->imageWidth)*3;
		printf("chunk: %i\n",chunk);
		sourceFile=fopen("box.ppm","rb");
//		sourceFile=fopen("feep.ppm","rb");
		fread(aux,1,nbrChars,sourceFile);
//		fseek(sourceFile,nbrChars,SEEK_SET);
		destinationFile=fopen("box.ppm.temp","wb");
//		destinationFile=fopen("feep.ppm.temp","wb");
		fwrite(aux,1,nbrChars,destinationFile);
		
		while (!feof(sourceFile)){
			//puts("efectuar fread");
			fread(in,1,chunk,sourceFile);
			//printf("passagem: %i\n",++i);
			//puts("in");
			//puts((char*)(&in));
			//puts("chamar filter none");
			filter_best(in, prev, out, chunk, 3);
			//puts("out:");
			//puts((char*)(&out));
			fwrite(out,1,chunk+1,destinationFile);
			++i;
		}
		fclose(destinationFile);
		puts("pausa");
		printf("nº passagens: %i\n",i);
		i=0;
		destinationFile=fopen("box.ppm.temp","rb");
//		destinationFile=fopen("feep.ppm.temp","rb");
		fread(aux,1,nbrChars,destinationFile);
//		fseek(destinationFile,nbrChars,SEEK_SET);
		finalFile=fopen("box.pp1","wb");
//		finalFile=fopen("feep.pp1","wb");
		fwrite(aux,1,nbrChars,finalFile);
		
		while (!feof(destinationFile)){ 
			//puts("efectuar fread");
			fread(in,1,chunk+1,destinationFile);
//			printf("passagem: %i\n",++i);
			//puts("in");
			//puts((char*)(&out));
			//puts("chamar filter none");
			unFilter(in, prev, out, chunk, 3);
			//puts("out:");
			//puts((char*)(&in));
			fwrite(out, 1, chunk, finalFile);
			++i;
		}		
		
				printf("nº passagens: %i\n",i);

		
		puts("END!");
}
	
	free(fhp);
	
	return SUCCESS;
}
*/
