#ifndef STDIO_DEF
#define STDIO_DEF
#include <stdio.h>
#endif	
#include "z-Library.h"
#include <stdlib.h>
#define DEFAULT_EXT_NAME ".z"
enum CMD_ERRORS{CMD_INVALID_EXT,CMD_INVALID_OPTION,CMD_INVALID_FILES};

int my_compress(FILE *source, FILE *dest, int level)
{
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, level);
    if (ret != Z_OK)
        return ret;

    /* compress until end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)deflateEnd(&strm);
            return Z_ERRNO;
        }
        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)deflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */

    /* clean up and return */
    (void)deflateEnd(&strm);
    return Z_OK;
}


int my_decompress(FILE *source, FILE *dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}
/* report a zlib or i/o error */
void my_errors(int ret)
{
    fputs("zpipe: ", stderr);
    switch (ret) {
    case Z_ERRNO:
        if (ferror(stdin))
            fputs("error reading stdin\n", stderr);
        if (ferror(stdout))
            fputs("error writing stdout\n", stderr);
        break;
    case Z_STREAM_ERROR:
        fputs("invalid compression level\n", stderr);
        break;
    case Z_DATA_ERROR:
        fputs("invalid or incomplete deflate data\n", stderr);
        break;
    case Z_MEM_ERROR:
        fputs("out of memory\n", stderr);
        break;
    case Z_VERSION_ERROR:
        fputs("zlib version mismatch!\n", stderr);
    }
}

void my_cmdErrors(int ret){
	fputs("Comand Line Errors: ", stderr);
	switch(ret){
		 case CMD_INVALID_EXT:
			fputs("Not Know Extention\n", stderr);
		 case CMD_INVALID_FILES:
			fputs("Invalid source/destination files\n", stderr);
			break;
		 case CMD_INVALID_OPTION:
			fputs("Invalid Option\n", stderr);
			break;
	}
}
void progUsage(char *program){
	puts("--------------------------------------------------------------------------------");
	printf("Usage: \n%s -[c,d] -[l] [0-9] -[f] [0-5] source [dest]\n",program);
	puts("--------------------------------------------------------------------------------");
	puts("-c : compress");
	puts("-d : decompress");
	puts("-l : compress level");
	puts("\t[0-9] : 0- arquive, 9- maximum compress.");
	puts("-f : Filter type");
	puts("\t[0-9] : 0- None, 1- Sub, 2- Up, 3- Average, 4- Paeth, 5-Best.");
	puts("source: source file");
	puts("destination: destination file. It's optional. Case ignored destination file:");
	puts("\twhile compress: end with the extention source.z");
	puts("\twhile decompress: end with the extention source.dz");
	puts("--------------------------------------------------------------------------------");
}

void init_Args(struct cmdLnArgs *ma){
	/*Setting defaults values*/
	ma->action = compress_action;
	ma->compressLevel = Z_DEFAULT_COMPRESSION;
	ma->filter = 0;
	ma->destParsed = false;
}

int parseArgs(struct cmdLnArgs *ma, int argc, char **argv){
	int idx=1;
    while (idx < argc){
		
		if ((char)argv[idx][0] == '-'){
			switch ((char)argv[idx][1]){
				case 'c':
					ma->action=compress_action;
					break;
				case 'd':
					ma->action=decompress_action;
					break;
				case 'l':
					idx++;
					ma->compressLevel=*argv[idx] - '0';
					break;
				case 'f':
					idx++;
					ma->filter=*argv[idx] - '0';
					break;
				default:
					printf("%s \n",argv[idx]);
					my_cmdErrors(CMD_INVALID_OPTION);
					progUsage(argv[0]);
					return false;
					break;
			}
		}else{
			switch (((int)(argc -  idx))){
				case 1:
					ma->source=argv[idx];
					ma->destination=0;
					return true;
					break;
				case 2:
					ma->source=argv[idx++];
					ma->destination=argv[idx];
					return true;
					break;
				default:
					my_cmdErrors(CMD_INVALID_FILES);
					progUsage(argv[0]);
					return false;
					break;
			}
		}
		idx++;
	}
	return false;
	
}

void printArgs(struct cmdLnArgs *arg){
		puts("--------------------------------------------------------------------------------");
		printf("[Action]:%i\n",arg->action);
		printf("[Filter]:%i\n",arg->filter);
		printf("[Compress Level]:%i\n",arg->compressLevel);
		printf("[Source]:%s\n",arg->source);
		printf("[Destination]:%s\n",arg->destination);
		printf("[DestParsed]:%i\n",arg->destParsed);
		puts("--------------------------------------------------------------------------------");
}
void cleanNewFileName(char * destination){
		free(destination);
}
/**
 * Na ausência do ficheiro de destino, gera o seu nome como:
 * :: Na realização da compressão
 * ficheiro_origem.DEFAULT_EXT_NAME (.z)
 * :: Na realização da descompressão
 * ficheiro_origem.SEM DEFAULT_EXT_NAME (sem .z)
 * 
 * No Caso da extensão não ser conhecida não realiza a operação.
 * */
unsigned int  newOutputFile(struct cmdLnArgs *myargs, char *outputfile){
	int sizeOfExt=0;
	int equal=0; 
		sizeOfExt=(myargs->action == compress_action)?strlen(myargs->source)+strlen(DEFAULT_EXT_NAME):strlen(myargs->source)-strlen(DEFAULT_EXT_NAME);
		
		outputfile=(char *)malloc(sizeof(char)*(sizeOfExt));
		if (outputfile == NULL){
			my_errors(Z_MEM_ERROR);
			return false;
		}	
		if (myargs->action == compress_action){
			myargs->destination=strcpy(outputfile,myargs->source);
			myargs->destination=strcat(outputfile,DEFAULT_EXT_NAME);
		}else{
			equal=strcmp(&(myargs->source[sizeOfExt]),DEFAULT_EXT_NAME);
			if(equal){
					my_cmdErrors(CMD_INVALID_EXT);
					return false;
			}
			
			myargs->destination=strncpy(outputfile,myargs->source,sizeOfExt);
		}	
		return true;
}

int main(int argc, char **argv)
{
    int ret=0;
    myArgs myargs;
    char * outputfile=0;
    FILE *sourceFile;
    FILE *destinationFile;
    
    
    if(argc == 1){
		progUsage(argv[0]);
		return UNSUCCESS;
	}

	init_Args(&myargs);
	ret=parseArgs(&myargs,argc,argv);
    if (ret == false) {
		progUsage(argv[0]);
		return UNSUCCESS;
	}
    
	
	if (myargs.destination == NULL){
		ret=newOutputFile(&myargs,outputfile);
		if (ret == false){
			return UNSUCCESS;
		}
		myargs.destParsed=true;
	}

 

	/**
	 * Processamento do ficheiro
	 **/
	sourceFile=fopen(myargs.source,"rb");
	destinationFile=fopen(myargs.destination,"wr");
	SET_BINARY_MODE(sourceFile);
	SET_BINARY_MODE(destinationFile);


	printf("Processing file: %s into %s ...", myargs.source,myargs.destination);
	if (myargs.action == compress_action){
		ret = my_compress(sourceFile,destinationFile, myargs.compressLevel);
	}else{
		ret = my_decompress(sourceFile, destinationFile);
	}
	if (ret != Z_OK){
			printf("--- :::  ERROR. File not processed!\n");
			my_errors(ret);
			if(myargs.destParsed){
				cleanNewFileName(outputfile);
			}
			
			return UNSUCCESS;
	}
	printf(" ::: DONE File successufly processed!\n");


	if(myargs.destParsed){
		cleanNewFileName(outputfile);
	}
	return ret;
}
