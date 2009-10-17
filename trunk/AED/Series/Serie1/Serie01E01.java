package serie1;
/**
 * Primeira série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 */

public class Serie01E01 {
/*
1. Realize o método estático
public static int removeOdd(int[] v, int count);
Este método retira os inteiros ímpares da sequência representada pelos primeiros count inteiros do array v. A
sequência resultante fica contida de forma contígua nas primeiras posições do array v. O valor retornado pelo
método é a dimensão da sequência resultante.
*/

  /**
   *Solução 1:
   *Remove os inteiros nos "count" primeiros termos e retorna o numero de elementos
   *que ficaram nos "dim" primeiras posições.
   * 
   *Trabalha no Dominío 0->count.   
   */ 

    	public static int removeOdd(int[] v, int count){
    		int dim=0;
    		for (int idx=0;idx<count;idx++)
    	        if (v[idx]%2 == 0) v[dim++]=v[idx];
    		return dim;
    	}

  /**
   *Solução 2:
   *Remove os inteiros nos "count" primeiros termos e retorna o numero de elementos
   *validos no vector "v".
   *Trabalha no Dominio 0->tamanho do array.
   *As chavetas no if (idx<count) são necessários para o segundo "if" não assumir
   *que o else lhe diz respeito.            
   */ 
	public static int removeOdd(int[] v, int count){
		int dim=0;
		for (int idx=0;idx<v.length;idx++){
			if (idx<count){
				if (v[idx]%2 == 0) v[dim++]=v[idx];
			}else{
				v[dim++]=v[idx];
			}
		}
		return dim;
	}
	public static void main (String args[]) {		
		
	}
}
