/**
 * Primeira série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 * Exercicio 3:
 * São utilizadas quinze funções para dividir o problema e facilitar a leitura:
 * -> processInput(), processG(), processT(), processR()
 * 	  Funções que lêem o ficheiro e processam os 3 tipos de linhas existentes
 * 	  construindo os arrays com dados importados.
 * 	  As funções que processam os dados baseam-se no formato actual do ficheiro. Se
 *    este formato for alterado apenas é necessário actualizar os indices de início
 *    dos campos que queremos importar.
 * 	  Ao processar as reservas verifica se a reserva foi efectuada numa turma válida
 * 
 * -> processArgs(char * type, char * filter)
 *    Processa os argumentos passados ao programa. Se não tiver argumentos ou o 
 *    primeiro argumento for h (ou H) mostra a ajuda. Se o primeiro argumento for 
 *    U (Unidade Curricular), D (Docente) ou T(turma) chama a função apply_if definida
 *    em assembly enviando um ponteiro para a estrutura de dados, o filtro, 
 *    um ponteiro para a função de comparação e a função a aplicar caso o resultado da
 *    comparacao seja diferente de 0.
 * 
 * -> compareU(void * elem, void * filter), compareD(void * elem, void * filter), compareG(void * elem, void * filter)
 * 	  compara um campo da estrutura elem com o filtro.
 * 	  devolve 0 se forem iguais ou 1 se diferentes
 * 
 * -> findU(char * str, int max), findD(char * str, int max), findG(char * str, int max)	
 *    As funções find são utilizadas para não repetir dados quando se mostra ao utilizador
 * 	  as listagens de filtros disponíveis.
 * 
 * -> addAluno(void * elem)
 * 	  Recebe um ponteiro para um elemento da estrutura e adiciona esse aluno à listagem a apresentar 
 *    no final, por ordem alfabética, 
 * 
 * -> findTurma(char * str)
 *    Para processamento das Reservas procura a turma a que cada aluno se quer inscrever
 * 	  para adicionar o ponteiro para a turma correcta na estrutura de Reservas.
 * 
 * -> showList() e showHelp()
 * 	  Funções que mostram a ajuda para utilização do programa na linha de comandos e que 
 * 	  mostra a lista pedida após processamento.
 *  
 * Estratégia de resolução: 
 * -> Partiu-se o problema em duas partes.
 * -> Uma parte que gere o input recebido, e alimenta as estruturas definidas com os dados
 * -> Uma parte que processa os argumentos, constrói a listagem pedida e apresenta a listagem
 *    ao utilizador
 * -> Com a utilização do apply_if genérico diminui-se a quantidade de código a desenvolver do
 *    lado do C. Poderiamos também usar o aplly_if com uma alteração aos métodos findU, findD e findG
 *    para passar pelos elementos do array turmas mas teria de existir uma alteração da assinatura uma vez
 * 	  que o scope do find varia de elemento para elemento. A condição de paragem é variável.
 * 
 */ 


#include <stdio.h>
#include <string.h>

#define MAX_TURMAS 10
#define MAX_ALUNOS 250
#define MAX_AB_DOCENTE 4
#define MAX_AB_UNCURR 5
#define MAX_AB_TURMA 6

int idxT=0;
int idxR=0;
int idxA=0;

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
Reserva reservas[MAX_ALUNOS];
unsigned int listaAlunos[MAX_ALUNOS];

int apply_if(void * data, size_t dim, size_t len, void * filter, 
	int (* predicate) (void * elem, void * filter), void (* action)(void * elem));


void addAluno(void * elem){
	int i=0,j;
	unsigned int num = (*(Reserva *)elem).numAluno;
	while(i<idxA && num>listaAlunos[i])
		++i;
	for(j=++idxA; j>i; --j)
		listaAlunos[j]=listaAlunos[j-1];
	listaAlunos[i]=num;
}

InfoTurma * findTurma(char * str){
	int i;
	for(i=0; i<idxT;++i){
		if(strcmp(turmas[i].turma, str)==0)
			return (turmas + i);	
	}
	return NULL;
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
	InfoTurma * InfoTurmatmp;
	
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
	
	if ((InfoTurmatmp=findTurma(turmatmp))!=NULL){
		reservas[idxR].pTurma = InfoTurmatmp;	/*validar no caso de nao encontrar a turma*/
		reservas[idxR].numAluno = val;
		idxR++;
	}else
		printf("A reserva do aluno nº %d foi efectuada numa turma não válida (%s)\n",val,turmatmp);
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

int findU(char * str, int max){
	int i;
	for (i=0; i<max; ++i)
		if (strcmp(turmas[i].unCurr,str)==0)
			return -1;
	return 0;
}

int findD(char * str, int max){
	int i;
	for (i=0; i<max; ++i)
		if (strcmp(turmas[i].docente,str)==0)
			return i;
	return -1;
}

int findG(int grp, int max){
	int i;
	for (i=0; i<max; ++i)
		if (turmas[i].grpt==grp)
			return i;
	return -1;
}

void showList(){
	int i;
	if (idxA==0) puts("\n Não existem alunos para listar de acordo com as condições indicadas.\n");
	for(i=0; i<idxA;++i)
		printf("%d\n", listaAlunos[i]);
}


int compareU(void * elem, void * filter){
	return (strcmp((*(*(Reserva *)elem).pTurma).unCurr, (char*)filter)?0:1);
}


int compareD(void * elem, void * filter){
	return (strcmp((*(*(Reserva *)elem).pTurma).docente, (char*)filter)?0:1);
}

int compareG(void * elem, void * filter){
	return (((*(*(Reserva *)elem).pTurma).grpt == *(unsigned char*) filter));
}

void processArgs(char * type, char * filter){
	int i;
	switch (*type) {
		case 'U':		/*filtrar por unidade curricular*/
		case 'u':
			if (filter == NULL){
				for (i=0; i<idxT; ++i)
					if (findU(turmas[i].unCurr, i)==-1)
						printf("%s\n",turmas[i].unCurr);
				return;
			}else{
				printf("Lista de alunos da Unidade Curricular: %s \n",filter); 
				apply_if(&reservas, sizeof(reservas[0]), idxR, filter, &compareU, &addAluno);
			}
		break;
		case 'D':		/*filtrar por Docente*/
		case 'd':
			if (filter == NULL){
				for (i=0; i<idxT; ++i)
					if (findD(turmas[i].docente, i)==-1)
						printf("%s \n",turmas[i].docente);
				return;
			}else{
				printf("Lista de alunos do Docente: %s \n",filter);
				apply_if(&reservas, sizeof(reservas[0]), idxR, filter, &compareD, &addAluno);
			}
		break;
		case 'G':		/*filtrar por grupo horario*/
		case 'g':
			if (filter == NULL){
				for (i=0; i<idxT; ++i)
					if (findG(turmas[i].grpt, i)==-1)
						printf("%c - %s\n",turmas[i].grpt, turmas[i].docente);
				return;
			}else{
				printf("Lista de alunos das turmas do grupo: %s \n",filter);  
				apply_if(&reservas, sizeof(reservas[0]), idxR, filter, &compareG, &addAluno);
					
			}
		break;
		default:
			printf("Argumento <%s> inválido. Usar H (ou h) para ajuda.\n",type);
	}
	showList();
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

	if (argc<2){
		puts("\n***Need at least one argument to be searched!***\n");
		showHelp();
	} else {
		if (*argv[1] == 'h' || *argv[1] == 'H') {
			showHelp();
			return 0;
		}
		processInput();
		processArgs(argv[1], argv[2]);
	}
	
return 0;
}
