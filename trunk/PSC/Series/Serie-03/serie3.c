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

void processLine() {

}

void initFileHeader(struct FileHeader fh){
	fh.magicValue=0;
	fh.imageWidth=0;
	fh.imageHeight=0;
	fh.maxGrey=0;
	fh.isFilled=0;
}
void listfileHeader(struct FileHeader fh){
	puts("---------------------------------------\n");
	printf("File magicValue: P%i\nImage Width: %i\nImage Height: %i\nMax Gray: %i\n",fh.magicValue,fh.imageWidth,fh.imageHeight,fh.maxGrey);
	puts("---------------------------------------\n");
}
void fillHeader(struct FileHeader fh, int value){

	if (fh.magicValue == 0){
		fh.magicValue = value;
			printf("\n\t>>>> [MV][%i] <<<<\n",value);
	}else if(fh.imageWidth == 0){
		fh.imageWidth = value;
				printf("\n\t>>>> [IW][%i] <<<<\n",value);
	}else if(fh.imageHeight == 0){
		fh.imageHeight = value;
		fh.isFilled = (fh.magicValue == 1)?1:0;
				printf("\n\t>>>> [IH][%i] <<<<\n",value);
	}else if(fh.maxGrey == 0){
		fh.maxGrey = value;	
		fh.isFilled = (fh.magicValue > 1)?1:0;
				printf("\n\t>>>> [MF][%i] <<<<\n",value);
	}
}


int processFile(char *filename, struct FileHeader fhp) {
	int chars=0;
	int ignore=false;
	int parsedInt=0;
	int c=0;
	FILE *fp=fopen(filename,"r");
	initFileHeader(fhp);
	while((fhp.isFilled == 0) && (c=fgetc(fp))!= EOF){
		putchar(c);
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
				ignore = false;
				break;
			case 'P':
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
    struct FileHeader fhd = { 0 , 0 , 0 , 0};
    if (argc == 1) {
        puts("Need at least one argument to be processed!");
        return UNSUCCESS;
    }
    while ((argc-1) > 0) {
        argc--;
	printf("%s\n",argv[argc]);
	processFile(argv[argc],fhd);
	listfileHeader(fhd);
    }

return SUCCESS;
}
