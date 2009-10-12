package serie1;
/**
 * @author Nuno Cancelo
 * 
 */
public class Serie01E02 {

	/*
	 * 2. Realize o metodo estatico public int countEqualTo(int[] v, int l, int
	 * r, int a) que retorna o numero de ocorrencias do inteiro a no subarray(v;
	 * l; r), que esta ordenado de forma crescente. O custo assimptotico deve
	 * ser O(logN), onde N e a dimensão do subarray. Tenha em consideração que o
	 * numero de ocorrencias pertence a O(N).
	 */

	/**
	 * Solução 1:
	 * 
	 */

	/**
	 * Método auxiliar que retorna o indicie da primeira ocorrência de 'a', ou
	 * -1 caso não haja nenhuma ocorrencia.
	 */
	public static int getFirstOccurrence(int[] v, int l, int r, int a) {
		if (l>r) return -1;
		int mid=(l + r) / 2;
		int val;
		if (v[mid] < a)
			val=getFirstOccurrence(v, mid + 1, r, a);
		else 
			val=getFirstOccurrence(v,l, mid - 1, a);			
		if(val==-1 && v[mid] == a ) return mid;
	return val;
	}
	/**
	 * Método auxiliar que retorna o indicie da última ocorrência de 'a', ou
	 * -1 caso não haja nenhuma ocorrencia.
	 */
	public static int getLastOccurrence(int[] v, int l, int r, int a) {
		if (l>r) return -1;
		int mid=(l + r) / 2;
		int val;
		if (v[mid] > a)
			val=getLastOccurrence(v, l,mid - 1, a);
		else 
			val=getLastOccurrence(v, mid + 1,r, a);			
		if(val==-1 && v[mid] == a ) return mid;
	return val;
	}
	/**
	 * Método que retorna o numero de ocorrencias do valor 'a', caso haja.
	 * Utiliza o metodo auxiliar getFirstOccurrence(...) e getLastoccurrence(...).
	 */
	public static int countEqualTo(int[] v, int l, int r, int a) {
		int left=0,right=0;
		if ((left=getFirstOccurrence(v, l, r, a))!=-1){
			right=getLastOccurrence(v, l, r, a);
			return (right- left +1);
		}
		return -1;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] var={0,1,2,2,2,2,2,3,4,5,6,7,8,9};
		int x=getLastOccurrence(var, 0, 13, 9);
		System.out.println("var /> "+ x);

	}

}
