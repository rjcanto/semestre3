/**
 * Terceira série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 */
#include <stdio.h>
#define LINE_MAX 1024;
#define SUCCESS 0;
#define UNSUCCESS 1;
enum boolean {false,true};
struct FileHeader{
	int magicValue;
	int imageWidth;
	int imageHeight;
	int maxGrey;
	int isFilled;
};

/*
 * void initFileHeader(struct FileHeader *fh);
 * Função que vai inicializar os valores do objecto FileHeader
 */
void initFileHeader(struct FileHeader *fh){
	fh->magicValue=0;
	fh->imageWidth=0;
	fh->imageHeight=0;
	fh->maxGrey=0;
	fh->isFilled=false;
}

/*
 * void listfileHeader(char* filename,struct FileHeader *fh,int nbrChars)
 * Lista os conteudos do FileHeader.
 */
void listfileHeader(char* filename,struct FileHeader *fh,int nbrChars){
	puts("---------------------------------------");
	printf("File: %s \nHeader File Information\n",filename);	
	puts("---------------------------------------");
	printf("File magicValue: P%i\n",fh->magicValue);
	printf("Image Width: %i\n",fh->imageWidth);
	printf("Image Height: %i\n",fh->imageHeight);
	if (fh->magicValue > 1){
		printf("Max Gray: %i\n",fh->maxGrey);
	}
	printf("Nbr of chars read: %i\n",nbrChars);	
	puts("---------------------------------------");
}

/*
 * void fillHeader(struct FileHeader *fh, int value)
 * Função que preenche o header.
 * Dadas as caracteristicas do ficheiro, os dados vão ser preenchidos
 * pela ordem de chegada.
 * Existe uma atenção especial ao MagicValue para o preenchimento do valor
 * do MaxGray.
 */ 
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

/*
 * int processFileHeader(char *filename, struct FileHeader *fhp) 
 * Processa a informação constante no bloco de dados referente à descri-
 * ção do ficheiro preenchendo a estrutura do Header do Ficheiro.
 * Retorna o numero de caracteres lidos, até chegar ao bloco do Bitmap.
 */
int processFileHeader(char *filename, struct FileHeader *fhp) {
	int chars=0;
	int ignore=false;
	int parsedInt=0;
	int isHeaderBlockFinished=false;
	int c=0;
	FILE *fp=fopen(filename,"r");
	initFileHeader(fhp);
	while((isHeaderBlockFinished==false) && (c=fgetc(fp))!= EOF  ){
		switch(c){
			case '#':
			case '\t':
			case ' ' :
			case '\r':			
			case '\n':
				if ((ignore == false) && parsedInt > 0){fillHeader(fhp,parsedInt);}
	 			ignore = (c == '\n' || c == '\t')?false:(c == '#')?true:ignore;
				parsedInt=0;
				break;
			default:
				if ((ignore == false)){
					if (fhp->isFilled == true) {
						isHeaderBlockFinished=true;
						chars--;
						break;
					}
					if( c > 47 && c < 58){parsedInt = parsedInt*10+(c-48);}
				}
			break;
		}
		chars++;
	}
	fclose(fp);
 return chars;
}


/*
 * Processa multiplos ficheiros de entrada. Necessita de pelo menos 1.
 * */
int main(int argc, char *argv[]) {
    struct FileHeader fhp;
    int nbrChars=0;
    if (argc == 1) {
        puts("Need at least one argument to be processed!");
        return UNSUCCESS;
    }
    while ((argc-1) > 0) {
        argc--;
	nbrChars=processFileHeader(argv[argc],&fhp);
	listfileHeader(argv[argc],&fhp,nbrChars);	

    }

return SUCCESS;
}
