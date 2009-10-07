#include <stdio.h>
#include <String.h>

int slen(char * s){
	int len;
		for(len=0; s[len]!=0; ++len);
	return len;
}

void scpy (char * dst, char * src){
	int i;
		for(i=0;src[i]!=0;++i){
			dst[i]=src[i];
		}
	dst[i]=0;
}

void scat(char * s1, char * s2){
	int i,j;
	/*	for(i=0; s1[i]!=0; ++i);*/
		i=slen(s1);
		for(j=0; s2[j]!=0; ++j){
			s1[i++]=s2[j];
		}
		s1[i]=0;
}

int main(){
	char somespace[16];
	printf("%d \n",slen("LI31N"));
	scpy(somespace, "LI31N");
	puts(somespace);
	scat(somespace, " - PSC");
	puts(somespace);

	printf("%d \n",strlen("LI31N"));
	strcpy(somespace, "LI31N");
	puts(somespace);
	strcat(somespace, " - PSC");
	puts(somespace);
	
	return 0;	
}
