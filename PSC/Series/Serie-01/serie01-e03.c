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
	grp = getchar();
	
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

void listU(char * filter){
	int i;
	for (i=0; i<idxR; ++i){
		if (strcmp((*reservas[i].pTurma).unCurr,filter) == 0)
			printf("%d - %s\n", reservas[i].numAluno, (*reservas[i].pTurma).turma);
	}	
}

void listD(char * filter){
	int i;
	for (i=0; i<idxR; ++i){
		if (strcmp((*reservas[i].pTurma).docente,filter) == 0)
			printf("%d - %s\n", reservas[i].numAluno, (*reservas[i].pTurma).unCurr);
	}	
}

void listG(char * filter){
	int i;
	for (i=0; i<idxR; ++i){
		if ((*reservas[i].pTurma).grpt == (*filter))
			printf("%d - %s\n", reservas[i].numAluno, (*reservas[i].pTurma).unCurr);		
	}	
}

void processArgs(char * type, char * filter){

	switch (*type) {
		case 'U':		/*filtrar por unidade curricular*/
		case 'u':
			printf("Lista de alunos da Unidade Curricular: %s \n",filter); 
			listU(filter);
		break;
		case 'D':		/*filtrar por Docente*/
		case 'd':
			printf("Lista de alunos do Docente: %s \n",filter); 
			listD(filter);
		break;
		case 'G':		/*filtrar por grupo horario*/
		case 'g':
			printf("Lista de alunos das turmas do grupo: %s \n",filter); 
			listG(filter);
		break;
		default:
			printf("Argumento <%s> inválido. Usar H (ou h) para ajuda.\n",type);
	}	

}

void showHelp(){
	puts("Lista de argumentos:");
	puts("serie01-e03 <tipo_lista> [filtro] < <ficheiro_a_importar>");
	puts("<tipo_lista>:");	
	puts("	h ou H - mostra este ecrã");
	puts("	u ou U - lista de alunos por unidade curricular.");
	puts("	d ou D - lista de alunos por Docentes.");
	puts("	d ou D - lista de alunos de turmas que partilham o mesmo grupo horário.");
	puts("[filtro]:");
	puts("	unidade, docente ou grupo horário a filtrar ou vazio para listar todas as opções.");
	puts("<ficheiro_a_importar>:");
	puts("	nome do ficheiro com os dados a processar.");
}

int main(int argc, char *argv[]){
/*	int i;*/

	if (argc<2){
		puts("Need at least one argument to be searched!");
		puts("Use H or h as first argument for details.");
	} else {
		if (*argv[1] == 'h' || *argv[1] == 'H') {
			showHelp();
			return 0;
		}
		processFile();
		processArgs(argv[1], argv[2]);
	}
	
/*	for (i=0; i<idxT;++i)
		printf("%s - %s - %s - %c \n",turmas[i].docente,turmas[i].unCurr,turmas[i].turma,turmas[i].grpt);
	for (i=0; i<idxR;++i){
		printf("%d - %s  \n", reservas[i].numAluno,(*reservas[i].pTurma).turma);
	}*/
return 0;
}
