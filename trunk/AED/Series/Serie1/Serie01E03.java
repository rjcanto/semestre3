package Serie1;
/**
 * Primeira s�rie de exerc�cios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 */

public class Serie01E03 {
	
/*
	3. Realize o metodo estatico
	public static boolean isMaximumSubArrayGivenIndex(int[] v, int l, int r, int i)
	que retorna true se e s�o se l <= i <= r e a soma dos elementos do subarray (v; l; r) tiver o maior valor possivel
	para a soma de qualquer subarray de v contendo o indice i.
*/	    
	public static boolean isMaximumSubArrayGivenIndexLeft(int[] v, int l, int i) {
		int l_tmp = i;

		for (int idx = i - 1, sum = 0; idx >= l; --idx) {
			if (v[idx] > 0 && ((sum + v[idx]) > 0)) {
				l_tmp = idx;
				sum = 0;
			} else {
				sum += v[idx];
			}
		}
		return (l == l_tmp);

	}
	public static boolean isMaximumSubArrayGivenIndexRight(int[] v, int r, int i) {
		int r_tmp = i;
		for (int idx = i + 1, sum = 0; idx <= r; ++idx) {
			if (v[idx] > 0 && ((sum + v[idx]) > 0)) {
	 			r_tmp = idx;
				sum = 0;
			} else {
				sum += v[idx];
			}
		}
		return r == r_tmp;
	}

	public static IntTriple MaximumSubArrayIndexLeft(int[] v, int l, int i) {
		int l_tmp = i,total =0;

		for (int idx = i - 1,sum=0; idx >= l; --idx) {
			if (v[idx] > 0 && ((sum + v[idx]) > 0)) {
				l_tmp = idx;
				total += sum + v[idx];
				sum = 0;
			} else {
				sum += v[idx];
			}
		}
		return (new IntTriple(l_tmp,0,total));	
	}

	public static IntTriple MaximumSubArrayIndexRight(int[] v, int r, int i) {
		int r_tmp = i,total=0;

		for (int idx = i + 1,sum=0; idx <= r; ++idx) {
			if (v[idx] > 0 && ((sum + v[idx]) > 0)) {
				r_tmp = idx;
				total += sum + v[idx];
				sum = 0;
			} else {
				sum += v[idx];
			}
			
		}
		return (new IntTriple(0,r_tmp,total));
	}

	public static boolean isMaximumSubArrayGivenIndexA2(int[] v, int l, int r,int i) {
		/*
		 *Objectos criados somente para tornar mais leg�vel o c�digo 
		 */
		IntTriple ll=MaximumSubArrayIndexLeft(v, l, i);
		IntTriple rr=MaximumSubArrayIndexRight(v, r, i);
		
		return (ll.getLeft()==l && rr.getRight()==r);
	}

	public static boolean isMaximumSubArrayGivenIndexA1(int[] v, int l, int r,int i) {
		return (isMaximumSubArrayGivenIndexLeft(v, l, i) && 	isMaximumSubArrayGivenIndexRight(v, r, i));
	}
	public static void main (String args[]) {		
		
	}    
}
