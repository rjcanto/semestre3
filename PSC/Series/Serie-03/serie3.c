#include <stdio.h>
#define LINE_MAX 1024;
#define SUCCESS 0;
#define UNSUCCESS 1;
enum boolean {false,true};
/*private char string[LINE_MAX];*/
struct FileHeader{
	int magicValue;
	int imageWidth;
	int imageHeight;
	int maxGrey;
	int isFilled;
};
void initFileHeader(struct FileHeader *fh){
	fh->magicValue=0;
	fh->imageWidth=0;
	fh->imageHeight=0;
	fh->maxGrey=0;
	fh->isFilled=0;
}
void listfileHeader(char* filename,struct FileHeader *fh){
	puts("---------------------------------------");
	printf("File: %s \nHeader File Information\n",filename);	
	puts("---------------------------------------");
	printf("File magicValue: P%i\n",fh->magicValue);
	printf("Image Width: %i\n",fh->imageWidth);
	printf("Image Height: %i\n",fh->imageHeight);
	if (fh->magicValue > 1){
		printf("Max Gray: %i\n",fh->maxGrey);
	}
	puts("---------------------------------------");
}
void fillHeader(struct FileHeader *fh, int value){
	if (fh->magicValue == 0){
		fh->magicValue = value;
	}else if(fh->imageWidth == 0){
		fh->imageWidth = value;
	}else if(fh->imageHeight == 0){
		fh->imageHeight = value;
		fh->isFilled = (fh->magicValue == 1)?1:0;
	}else if(fh->maxGrey == 0){
		fh->maxGrey = value;	
		fh->isFilled = (fh->magicValue > 1)?1:0;
	}
}


int processFile(char *filename, struct FileHeader *fhp) {
	int chars=0;
	int ignore=false;
	int parsedInt=0;
	int c=0;
	FILE *fp=fopen(filename,"r");
	initFileHeader(fhp);
	while((fhp->isFilled == 0) && (c=fgetc(fp))!= EOF){
		switch(c){
			case '#':
				ignore = true;
				if (parsedInt > 0){
					fillHeader(fhp,parsedInt);
					parsedInt=0;
				}
				break;
			case '\t':
			case ' ' :
				if ((ignore == false) && parsedInt > 0){
					fillHeader(fhp,parsedInt);
					parsedInt=0;
				}
				break;
			case '\r':			
			case '\n':
				if ((ignore == false) && parsedInt > 0){
					fillHeader(fhp,parsedInt);
				}
				parsedInt=0;
				ignore = false;
				break;
			default:
				if ((ignore == false) && c > 47 && c < 58){
					parsedInt = parsedInt*10+(c-48);
				}
			break;
		}
		chars++;
	}
	fclose(fp);

 return chars;
}



int main(int argc, char *argv[]) {
    struct FileHeader fhp;
    if (argc == 1) {
        puts("Need at least one argument to be processed!");
        return UNSUCCESS;
    }
    while ((argc-1) > 0) {
        argc--;
	processFile(argv[argc],&fhp);
	listfileHeader(argv[argc],&fhp);	

    }

return SUCCESS;
}
