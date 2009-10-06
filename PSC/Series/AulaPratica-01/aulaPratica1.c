#include <stdio.h>
#include <limits.h>
#include <float.h>


/**
   Exercicio 1:
   Escreva a função count_ones(v), que retorna o número de bits a 1 presentes no inteiro v. Escreva também o
   respectivo programa de teste, não se esquecendo de incluir valores de entrada negativos.
*/
int count_ones(int v){
	int mask=1;
	int count=0;

	while (mask != 0){
		if ((v & mask)) 
			count++;
		mask = mask<<1;
	}
	return count;
}

/**
   Exercicio 2:
   Escreva a função getlong(), que usa getchar para ler do standard input a representação decimal de um valor
   inteiro com sinal e retorna esse valor como long. Escreva também o respectivo programa de teste, que
   deverá consistir num ciclo, cujo corpo será printf(“%ld\n”, getlong()). Mais uma vez, não se esqueça dos
   valores negativos.
*/
long getlong(){
	
	int c=getchar();
	int signal=(c == '-')?-1:1;
	long number= (signal != -1)?c-'0':0;

	while ((c=getchar())>='0' && c <='9'){
		number=number*10 +(c-'0');
	}
	return signal*number;
}
/**
   Exercicio 3:
   SO C90 forbids mixed declarations and code
Escreva a função min_ssize(v), que retorna o número mínimo de bytes necessário para armazenar o valor
   presente em v, incluindo o bit de sinal. Escreva também o respectivo programa de teste, tirando partido da
   alínea anterior.
*/
int min_ssizeiOld(unsigned long v){
	int 		count   =0;
	unsigned char 		uc	=-1;
	unsigned short		us	=-1;
	unsigned int		ui	=-1;
	unsigned long		ul	=-1;
	if (v > ul)
		count=sizeof(ul);
	else 
		if (v>ui)
		count=sizeof(ul);
	else
		if (v>us)
		count=sizeof(ui);
	else
		if (v>uc)
		count=sizeof(us);
	else
		count=sizeof(uc);
return count;
}

int test_range(long min, long max, long value){
	return (value>=min && value<=max);
}

int min_ssize(long v){
	/*
	Esta ideia surgiu da leitura do capitulo "2.2 Data Types and Sizes" do livro do K&R, nomeadamente
	da página 36:
	"
	The standard headers <limits.h> and <float.h> contain symbolic constants for all of these
	sizes, along with other properties of the machine and compiler. These are discussed in
	Appendix B.
	"
	*/
	int bytes=0;
	/*==================================
	[1] = char
	==================================*/
	
	/*test char*/
	if (test_range(CHAR_MIN,CHAR_MAX,v))
		bytes=sizeof(char);
	/*test signed char*/
	else if (test_range(CHAR_MIN,UCHAR_MAX,v))
		bytes=sizeof(signed char);
	/*test unsigned char*/
	else if (test_range(SCHAR_MIN,SCHAR_MAX,v))
		bytes=sizeof(unsigned char);
	/*==================================
	[2] = short
	==================================*/
	/*test short int*/
	else if (test_range(SHRT_MIN,SHRT_MAX,v))
		bytes=sizeof(short);
	/*test unsigned short int */
	else if (test_range(0,USHRT_MAX,v))
		bytes=sizeof(unsigned short);
	/*==================================
	[3] = int
	==================================*/
	/*test int*/
	else if (test_range(INT_MIN,INT_MAX,v))
		bytes=sizeof(int);
	/*test unsigned int*/
	else if (test_range(0,UINT_MAX,v))
		bytes=sizeof(unsigned int);
	/*==================================
	[4] = long
	==================================*/
	/*test long*/
	else if (test_range(LONG_MIN,LONG_MAX,v))
		bytes=sizeof(long);
	/*test unsigned long*/
	else if (test_range(0,ULONG_MAX,v))
		bytes=sizeof(unsigned long);
	/*==================================
	[5] = float
	==================================*/
	/*test float*/
	/*
	if (test_range(CHAR_MIN,CHAR_MAX,v))
		bytes=sizeof(float);
	*/
	/*==================================
	[6] = double
	==================================*/
	/*test double */
	/*
	if (test_range(CHAR_MIN,CHAR_MAX,v))
		bytes=sizeof(double);
	*/
	/*test long double*/
	/*
	if (test_range(CHAR_MIN,CHAR_MAX,v))
		bytes=sizeof(long double);
	*/
return bytes;
}

int check_string(int *str_find, int *str_in, int str_len){
	int idx=0;
	int i;
	for (i=0;i<str_len;i++){
		if (*(str_in + i) == *(str_find + idx)){
			idx++;
			if (*(str_find + idx) == '\0')
				return 1;
		}else{
			idx=0;
		}
	}
	return 0;
}

int main(){
	/*Exercicio 1:*/
	/*
	int else value=-1;
	printf ("--> %d\n",count_ones(value));
	*/
/*------------------------------------------------*/
	/*
	Exercicio 2:
	*/
	/*
	while (1)
		printf("%ld\n", getlong());
	*/
/*------------------------------------------------*/
	/*
	Exercicio 3:
	*/
/*	long value=getlong();
	printf ("Valor: %ld byte: %d \n",value,min_ssize(value));
*/
/*------------------------------------------------*/
	/*
	Exercicio 4:
	*/

	char string[]="ISEL";
	char line[5000]="Nuno Cancelo";
	int c;
	int idx=0;
	int i;
	int i1=0;
        int i2;
	int found=0;
	while ((c=getchar())!='\n'){
		line[idx]=c;
		idx++;
	}

         for (i2=0;i2<idx;i2++){
                 if (*(line + i2) == *(string + i1)){
                        i1++;
                        if (*(string + i1) == '\0')
                                found= 1;
                 }else{
                         i1=0;
                 }
         }
	if(found){
		for (i=0;i<idx;i++){
			putchar(line[i]);
		}
	}
	printf("\n");

return 0;
}

