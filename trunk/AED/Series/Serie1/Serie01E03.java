
public class Serie01 {
	
/*
	3. Realize o metodo estatico
	public static boolean isMaximumSubArrayGivenIndex(int[] v, int l, int r, int i)
	que retorna true se e são se l <= i <= r e a soma dos elementos do subarray (v; l; r) tiver o maior valor possivel
	para a soma de qualquer subarray de v contendo o indice i.


	Pessoalmente não gosto desta implementação.
	*/

	//    public static int maxValueSubArray(int[]v, int l, int r, int i)
	    
	    
	    public static boolean isMaximumSubArrayGivenIndex(int[] v, int l, int r, int i){
	    		int r_tmp=i, l_tmp=i, idx;
	    		int sum=0;
	    		for(idx=i-1;idx >= l; --idx)
	    			if (v[idx] > 0 && ((sum+v[idx])>0)){
	    				l_tmp=idx;
	    				sum=0;
	    			}
	    			else
	    				sum+=v[idx];
	    		sum=0;
	    		for(idx=i+1;idx <= r; ++idx)
	    			if (v[idx] > 0 && ((sum+v[idx])>0)){
	    				r_tmp=idx;
	    				sum=0;
	    			}	
	    			else
	    				sum+=v[idx];
	    		
	    	
				return (l==l_tmp && r==r_tmp);
			}	    
	    
	    
	    public static void main(String args[]){
	    	int[] tmp = {12,-2,-24,26,-3,-17,-18,20,16,-10,12,-2,10,-19};
	    	
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 0, tmp.length-1, 3));
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 2, tmp.length-1, 3));	    	
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 3, tmp.length-1, 3));	    	
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 3, 8, 3));
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 3, 12, 3));
	
	    	
	    	
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 0, tmp.length-1, 7));
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 2, tmp.length-1, 7));	    	
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 3, tmp.length-1, 7));	    	
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 3, 8, 7));
	    	System.out.println(isMaximumSubArrayGivenIndex(tmp, 7, 12, 7));
	    }
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	/**
	    4. Realize o metodo estatico
	    public static IntTriple getMaximumSubArrayGivenIndex(int[] v, int i)
	    que retorna o triplo de inteiros (l; r; s) tal que o resultado da avaliaçao de isMaximumSubArrayGivenIndex(v,l,r,i)
	    seja true e s = sum(l,r,v[i]);
	    O custo assimptotico deve ser O(N), onde N é a dimensão do array.
	  */
	  
	  	public static IntTriple MaximumSubArrayGivenIndex(int[] v, int l, int r, int i){
			int count=0, maxValue=0,left=l,right=r;
			
			for (int idx=l;idx<=i;idx++){
				count=0;
				for (int jdx=idx;jdx<=r;jdx++){
					count+=v[jdx];
					if (jdx>=i && count > maxValue){
						maxValue=count;
						left=idx;
						right=jdx;
					}
				}
			}
			return new IntTriple(left,right,maxValue);
		}
	    
	    public static IntTriple getMaximumSubArrayGivenIndex(int[] v, int i){
			return MaximumSubArrayGivenIndex(v, 0, v.length-1, i);
		}
	    
	    
	    
	    
	class IntTriple{
		private int left;
		private int right;
		private int sum;
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
	}    
	            	
}
