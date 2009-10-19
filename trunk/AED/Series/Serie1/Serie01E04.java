package Serie1;
/**
 * Primeira s�rie de exerc�cios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 */ 
public class Serie01E04 {

	/**
	 * 4. Realize o metodo estatico public static IntTriple
	 * getMaximumSubArrayGivenIndex(int[] v, int i) que retorna o triplo de
	 * inteiros (l; r; s) tal que o resultado da avalia�ao de
	 * isMaximumSubArrayGivenIndex(v,l,r,i) seja true e s = sum(l,r,v[i]); O
	 * custo assimptotico deve ser O(N), onde N � a dimens�o do array.
	 */
	

	public static IntTriple MaximunSubArrayIndexLeft(int[] v, int l, int i) {
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
		return (new IntTriple(l_tmp,i-1,total));
	}

	public static IntTriple MaximunSubArrayIndexRight(int[] v, int r, int i) {
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
		return (new IntTriple(i+1,r_tmp,total));
	}

	public static IntTriple MaximumSubArrayGivenIndex(int[] v, int l, int r, int i) {
		IntTriple left=MaximunSubArrayIndexLeft(v, l, i);
		IntTriple right=MaximunSubArrayIndexRight(v, r, i);
		return (new IntTriple(left.getLeft(), right.getRight(), left.getSum()+right.getSum() + v[i]) );
	}

	public static IntTriple getMaximumSubArrayGivenIndex(int[] v, int i) {
		IntTriple result=MaximumSubArrayGivenIndex(v, 0, v.length - 1, i);
		return result;
	}
	public static void main (String args[]) {		
		
	}
	}
