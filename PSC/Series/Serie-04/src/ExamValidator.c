#include "ExamValidator.h"


static ValidatorLoaderMethods valLoader_vtable={
	valLdr_dtor,
};
static arrayMethods evArray_vtable={
	evArray_dtor
};

void oneEV_dtor(oneEV* this){
	if (this!=NULL)
		free(this);
}
void twoEV_dtor(twoEV* this){
	if (this!=NULL)
		free(this);
}
void valLdr_dtor(valLdr* this){
	if (this!=NULL)
		this->loader->vptr->dtor(this->loader);
	free(this);
}

void evArray_dtor(evArray* this){
	int i;
	if (this!=NULL){
		for(i=0; i<length(this); ++i)
			getArrayPosOneE(this,i)->vptr->dtor(getArrayPosOneE(this,i));
		free(getArrayOneE(this));
		free(this);
	}
}

evArray* evArray_ctor(){
	evArray* arr = (evArray*) (malloc(sizeof(evArray)));
	if (arr==NULL) mallocError("ExamValidator");
	arr->vptr = &evArray_vtable;
	arr->size=0;
	return arr;
}

valLdr* valLdr_ctor(){
	valLdr* aux = (valLdr*) malloc(sizeof(valLdr));
	if (aux==NULL) mallocError("ExamValidator");
	aux->vptr = &valLoader_vtable;
	aux->loader = DataLoader_ctor(); 
	aux->loader->vptr->newArray = &ev_newArray;
	aux->loader->vptr->newInstance = &ev_newInstance;
	return aux;
}

void** ev_newArray(int numEntries){
	evArray* aux = (evArray*)malloc(sizeof(oneEV*) * numEntries);
	if (aux==NULL) mallocError("ExamValidator");
	aux->size=0;
	return (void**)(aux);
}

evArray* ev_loadFrom(String filename){
	evArray* evarray = evArray_ctor();
	valLdr* evLoader = valLdr_ctor();	
	evarray = evLoader->loader->vptr->loadFrom(evLoader->loader, evarray, filename);
	evLoader->vptr->dtor(evLoader);
	return evarray;
}

void* ev_newInstance(String* elems, int nbr){
	void* res;
	void* extMod;
	void* (*ctor) ();
	String extLib;

	extLib=getModuleFileName(elems[0]);
	
	/*aceder aos modulos externos*/
	extMod = dlopen(extLib, RTLD_NOW);
	
	if (extMod==NULL){
		printf("Validador %s",elems[0]);
		if (elems[1]!=NULL)
			printf("(\"%s\")", elems[1]);
		printf(" nao encontrado.\n");
		/*printf("Erro: %s\n", dlerror());*/
		return NULL;
	}
	*(void**)(&ctor) = dlsym(extMod,"ctor");
	res= ctor();
	if (res == NULL){
		printf("Erro: %s\n", dlerror());
		return NULL;
	}
	if(nbr>1)
		((baseEV*) (res))->vptr->setArgs(res, elems[1]);
	return res;
}

int validate(ExamArray* exams, evArray* val1, evArray* val2){
	int idxe1,idxe2,idxv;
	int result = true;
	/* Validacoes singulares. */
	for(idxe1=0; idxe1<length(exams) ; ++idxe1){
		for(idxv=0; idxv<length(val1) ; ++idxv){
			if (!getArrayPosOneE(val1,idxv)->vptr->isValid(getArrayPosOneE(val1,idxv),getArrayPosE(exams,idxe1))){
				printf("%s falha na regra \"%s\"\n",getAcronym(getCourse(getArrayPosE(exams,idxe1))),getRuleName(getArrayPosOneE(val1,idxv)));
				result = false;
			}
		}
	}
	/* Validacoes duplas. */
	for(idxe1=0; idxe1<length(exams) ;++idxe1){
		for(idxe2=idxe1+1; idxe2<length(exams) ;++idxe2){
			for(idxv=0; idxv<length(val2); ++idxv){
				if (!getArrayPosTwoE(val2,idxv)->vptr->isValid(getArrayPosTwoE(val2,idxv),getArrayPosE(exams,idxe1),getArrayPosE(exams,idxe2))){
					printf("%s e %s falham na regra \"%s\"\n",getAcronym(getCourse(getArrayPosE(exams,idxe1))),getAcronym(getCourse(getArrayPosE(exams,idxe2))),getRuleName(getArrayPosOneE(val2,idxv)));
				result = false;
				}
			}
		}
	}
	return result;	
}

/* 
 * Constroi o nome do modulo a carregar.
 * tamanho da string igual ao tamanho do nome passado mais 2 caracteres para o prefixo "./"
 * mais 3 para a extensão ".so" e mais um para o terminador "\0"
 * calloc aloca memoria limpa, ou seja a string aux inicialmente esta vazia
 * */
String getModuleFileName(String name){
	String aux = (String) calloc((6+strlen(name)),sizeof(char));
	strcat(aux, "./");
	strcat(aux, name);
	strcat(aux, ".so");
	return aux;
}

int main(int argc, char** argv){
	int res;
	PrgCourseArray* courses;
	ExamArray* exams;
	oneEVArray* val1;
	twoEVArray* val2;
	
	if (argc != 3){
		puts("use: ExamValidator SomeProgram.txt Exams.txt");
		exit(1);
	}
	
	courses = pc_loadFrom(argv[1]);
	printf("#ProgramCourse = %i\n", courses->size);
	puts("---------------------");

	exams = e_loadFrom(argv[2],courses);
	printf("#Exams = %i\n", exams->size);
	puts("---------------------");

	val1 = ev_loadFrom("./DataFile/Validators1.txt");
	val2 = ev_loadFrom("./DataFile/Validators2.txt");
	
	res = validate(exams, val1, val2);
	
	printf("O mapa de exames e' %svalido.\n", res ? "" : "in");
	
	
	exams->vptr->dtor(exams);
	courses->vptr->dtor(courses);
	val1->vptr->dtor(val1);
	val2->vptr->dtor(val2);

	return 0;	
}

