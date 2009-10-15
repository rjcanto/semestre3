#include <stdio.h>
#include <string.h>

/**
   Exercicio 3:
	Considerando as estruturas apresentadas escreva um programa que leia, via standard input, a informação sobre as turmas e respectivas reservas para PSC, PICC e CPg, disponivel no ficheiro de texto anexo. Considere que não existem mais do que 10 turmas nem mais do que 250 alunos. O programa deverá, de seguida, apresentar um menu de opções que permita apresentar listagens de alunos de acordo com (pelo menos) os seguintes critérios:
	- todos os alunos de uma dada unidade curricular;
	- todos os alunos de um dado docente;
	- todos os alunos das turmas agrupadas na mesma sala e horario (campo grpt de InfoTurma).
*/

#define MAX_TURMAS 10
#define MAX_ALUNOS 250

#define MAX_AB_DOCENTE 4
#define MAX_AB_UNCURR 5
#define MAX_AB_TURMA 6

int idxT=0;
int idxR=0;

typedef struct info_turma {
	char docente[MAX_AB_DOCENTE];	/*Abreviatura: JHT, PAP, MCS, JPP, JMP */
	char  unCurr[MAX_AB_UNCURR];	/*Abreviatura: PSC, PICC, CPg */
	char   turma[MAX_AB_TURMA];	/*Sigla:: LI31D, LI31N, LT41N, LR31D, ... */
	unsigned char grpt; /*Grupo de turmas que partilham sala e horario */
} InfoTurma;

typedef struct reserva { 
	unsigned int numAluno;
	InfoTurma * pTurma;
} Reserva;

InfoTurma turmas[MAX_TURMAS];
Reserva reservas[MAX_ALUNOS];

void addDocente() {
	int i,c;

	for (i=0; (c=getchar())!=' '; ++i) {
		turmas[idxT].docente[i]=c;
	}
	turmas[idxT].docente[i]=0;

	while ((c=getchar()) != ' ');
	turmas[idxT].grpt=getchar();
	
	turmas[idxT].unCurr[0] ='0';
	turmas[idxT].turma[0]='0';
	idxT++;
}

void addTurma() {
	int i,c, j=0;
	char turmatmp[6], grp;
	
	for (i=0; (c=getchar())!=' '; ++i) {
		turmatmp[i]=c;
	}
	turmatmp[i]=0;	
	printf("%s \n", turmatmp);
	grp = getchar();
	printf("%c \n", grp);
	
	for (i=0; i<idxT; ++i){
		if (turmas[i].grpt==grp){
			if (turmas[i].unCurr[0] != '0'){
				strcpy(turmas[idxT].docente, turmas[i].docente);
				turmas[idxT].grpt = turmas[i].grpt;
				i=idxT++;
			}
			getchar();
			while ((c=getchar())!='\n' && c!='\r' && c!=EOF){
				turmas[i].unCurr[j++]=c;
			}
			turmas[i].unCurr[j]=0;
			strcpy(turmas[i].turma, turmatmp);			
			break;
		}
	}
}

InfoTurma * findTurma(char * str){
	int i;
	for(i=0; i<idxT;++i){
		
		if(strcmp(turmas[i].turma, str)==0)
			return (turmas + i);	
	}
	return NULL;
}

void addReserva(){
	int c,i;
	char turmatmp[6];
	unsigned int number=0;
	
	for (i=0; (c=getchar())!=' '; ++i) {
		turmatmp[i]=c;
	}
	turmatmp[i]=0;
	while ((c=getchar())>='0' && c <='9'){
		number=number*10 +(c-'0');
	}
	reservas[idxR].numAluno = number;
	reservas[idxR++].pTurma = findTurma(turmatmp);	/*validar no caso de nao encontrar a turma*/
}


void processFile(){
	int c;

	while((c=getchar()) !=  EOF){
		switch (c) {
			case 'G':
				getchar();
				addDocente();
			break;
			case 'T':
				getchar();
				addTurma();
			break;
			case 'R':
				getchar();			
				addReserva();
			break;
		}	
	}
}

void printTurmaDetails(InfoTurma * t){
	printf("[ %s - %s - %c - %s ] \n",t->docente,t->unCurr,t->grpt,t->turma);
	/*printf("%s \n", * t.turma);*/


}

void processG(){
	char c;
	int i=0,a=0;
	while((c=getchar()) != '\n'  && c != EOF && c!=0 && c!='\r'){
		
		if (i>0 && i<4){
			turmas[idxT].docente[a]=c;
			a++;
		}else if (i == 5){
			
		}else if (i == 7){
			turmas[idxT].grpt=c;
		}
		++i;
	}
	turmas[idxT].unCurr[0]=0;
	turmas[idxT].turma[0]=0;
	idxT++;
}

void processT(){
	char c;
	int i=0,a=0,b=0;
	char turmatmp[MAX_AB_TURMA], grp;
	char unCurrtmp[MAX_AB_UNCURR];
	
	while((c=getchar()) != '\n'  && c != EOF && c!=0 && c!='\r'){
		if (i>0 && i<6){
			turmatmp[a]=c;
			a++;
		}else if (i == 7){
			grp=c;
		}else if (i > 8){
			unCurrtmp[b]=c;
			b++;
		}
		++i;
	}
	
	turmatmp[a]=0;
	unCurrtmp[b]=0;

	
	
	for (i=0; i<idxT; ++i){
		if (turmas[i].grpt==grp){
			 if (turmas[i].unCurr[0] != 0){
				
				
				strcpy(turmas[idxT].docente, turmas[i].docente);
				turmas[idxT].grpt = turmas[i].grpt;
				i=idxT++;
			}
			
			strcpy(turmas[i].turma,turmatmp);	
			
			strcpy(turmas[i].unCurr,unCurrtmp);
			break;

		}
	}

}

void processR(){
	char c;
	int i=0,a=0;
	char turmatmp[MAX_AB_TURMA];
	unsigned int val=0;
	
	while((c=getchar()) != '\n'  && c != EOF && c!=0 && c!='\r'){
		
		if (i>0 && i<6){
			turmatmp[a]=c;
			a++;
		}else if (i > 6 && c >='0' && c <='9'){
			val=val*10 +(c-'0');
		}
		i++;
	}
	turmatmp[a] = 0;
	reservas[idxR].numAluno = val;
	reservas[idxR].pTurma = findTurma(turmatmp);	/*validar no caso de nao encontrar a turma*/
	
	idxR++;
	
}


void processInput(){
	/**
	 *  0 1 2 3 4 5 6 7 8
	 * |_|_|_|_|_|_|_|_|_|
	 *  G   P A P   D   1
	 * 
	 *  0 1 2 3 4 5 6 7 8 910111213
	 * |_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	 *  T   L I 3 1 D   1   P I C C
	 * 
	 *  0 1 2 3 4 5 6 7 8 910111213
	 * |_|_|_|_|_|_|_|_|_|_|_|_|_|
	 *  R   L I 3 1 D   3 1 4 0 1 
	 * */
	char c;
	
	do{
		c=getchar();
		switch(c){
				case 'G':
					processG();
					break;
				case 'T':
					processT();
					break;
				case 'R':
					processR();
					break;
		}
	}while(c!=EOF);

}

int main(int argc, char *argv[]){
	int i;

	if (argc>0)
		processInput();
		/*printList(argv[1], argv[2]);*/
	else
		puts("Need at least one argument to be searched!");
	/*
	 for (i=0; i<idxT;++i)
		printf("%s - %s - %c - %s \n",turmas[i].docente,turmas[i].unCurr,turmas[i].grpt,turmas[i].turma);
		
	*/
	for (i=0; i<idxR;++i){
	/*	printf("%d - %s \n", reservas[i].numAluno,reservas[i].pTurma->turma);*/
		
		printTurmaDetails(reservas[i].pTurma);
	}	
	

return 0;	 

}
