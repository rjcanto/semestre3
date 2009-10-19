package Serie1;
/**
 * Primeira série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 */
public 	class IntTriple{
		private int left;
		private int right;
		private int sum;
        public IntTriple(){
			left=0;
			right=0;
			sum=0;
		}
		public IntTriple(int l, int r, int s){
			left=l;
			right=r;
			sum=s;
		}
		public int getLeft(){
			return left;
		}
		public int getRight(){
			return right;
		}
		public int getSum(){
			return sum;
		}
        public void print(){
            System.out.print("("+left+","+right+","+sum+")");
        }
}
