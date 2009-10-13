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
	char docente[4];	/*Abreviatura: JHT, PAP, MCS, JPP, JMP */
	char  unCurr[5];	/*Abreviatura: PSC, PICC, CPg */
	char   turma[6];	/*Sigla:: LI31D, LI31N, LT41N, LR31D, ... */
	unsigned char grpt; /*Grupo de turmas que partilham sala e horario */
} InfoTurma;

typedef struct reserva { 
	unsigned int numAluno;
	InfoTurma * pTurma;
} Reserva;

InfoTurma turmas[MAX_TURMAS];
Reserva reservas[250];

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
	/*printf("%s - %c \n",turmas[idxT].docente,turmas[idxT].grpt);*/
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
	/*printf("%s \n", * t.turma);*/


}


int main(int argc, char *argv[]){
	int i;

	if (argc>0)
		processFile();
		/*printList(argv[1], argv[2]);*/
	else
		puts("Need at least one argument to be searched!");
		
	for (i=0; i<idxT;++i)
		printf("%s - %s - %s - %c \n",turmas[i].docente,turmas[i].unCurr,turmas[i].turma,turmas[i].grpt);
	for (i=0; i<idxR;++i){
		printf("%d - %d ", reservas[i].numAluno,reservas[i].pTurma);
		printTurmaDetails(reservas[i].pTurma);
	}
return 0;	 

}
