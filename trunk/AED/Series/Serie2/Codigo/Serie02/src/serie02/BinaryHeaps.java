package serie02;

import java.security.acl.LastOwnerException;
import java.util.PriorityQueue;

/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 */
public class BinaryHeaps {
    /**
     * Este método apresenta na consola os inteiros presentes no amontoado
     * binário representado pelos primeiros count inteiros do array v. Esta
     * apresentação deve ter a seguinteE organização:
     * • Apresentar na mesma linha da consola os elementos com a mesma
     * profundidade (distância à raiz).
     * • Apresentar primeiro a linha com a raíz e por último a linha com os
     * elementos de maior profundidade.
     * • Em cada linha, os elementos são apresentados da esquerda para a direita.
     * @param v
     * @param count
     */
    public static void printByDepth(int[] v, int count){
        int level=0;
        int len=(int)Math.pow(2, level);

        for (int i=0,j=0; i<count ;i++){
            System.out.printf("[ %5d ]\t",v[i]);
            ++j;
            if(j == len){
                System.out.printf("\n");
                level++;
                j=0;
                len=(int)Math.pow(2, level);
            }
        }

    }
    /**
     * Este método, dado o max-heap representado pelos primeiros count inteiros
     * do array v, retorna o número de ocorrências do maior elemento presente
     * nesse max-heap.
     * @param v
     * @param count
     * @return
     */
    public static int countMaxInMaxHeap(int[] v, int count){
        return countMaxinHeap(v, 0, count,v[0])+1;
    }

    public static int countMaxinHeap(int[] v, int i, int count ,int max){
        if (2*i+1>=count) return 0;
        if (2*i+2>=count) return 0;
        if (v[i] != max) return 0;
        int total =0;
        
        if(v[2*i+1] == max) total+=countMaxinHeap(v, 2*i+1, count,max)+1;
        if(v[2*i+2] == max) total+=countMaxinHeap(v, 2*i+2, count,max)+1;
        //System.out.println(i+"<->"+ (2*i+1) +"<->"+(2*i+2));
        return total;
    }
    /**
     * Este método retorna a dimensão do maior sub-array de v, com início no
     * ındice 0, que representa um max-heap.
     * @param v
     * @return
     */
    public static int largestSubArrayThatIsAMaxHeap(int[] v){
        return checkMaxHeap(v);
    }
    /**
     *
     * @param v
     * @return
     *
     * Esta função verifica se o array está em Max-Heap.
     * A ideia é fazer a verificação se é max-heap a partir do "parent". Caso o
     * "parent" não esteja em max-heap, por definição, todos os seus pais tambem
     * não estão.
     * É utilizado uma estrutura de dados em memória para auxiliar a verificação
     * dos "parents" que estão em Max-Heap. Esta estrutura será utilizada poste-
     * riormente para efectuar a contabilização do maior sub-array que está em
     * max-heap.
     */
    public static int checkMaxHeap(int[] v){
        int lastParent=((v.length)-1)/2;
        int[] parents=new int[lastParent+1];
       

        do {
            if (parents[lastParent] != -1){
                if(isMaxHeap(v, lastParent)){
                    parents[lastParent]=1;
                }else{
                    setIsNotMaxHeap(parents, lastParent);
                }
            }
            --lastParent;
        }while(lastParent>=0);

       return getMaxInMaxHeap(parents);
    }

    /**
     *
     * @param v
     * Método auxiliar que coloca no ecrã o conteudo do array de inteiros V.
     * Serve principalmente para um verificações rápidas.
     */
    public static void print(int [] v){
        System.out.println();
        for (int i=0;i<v.length;++i){
            System.out.println(v[i]);
        }
    }

    /**
     *
     * @param v
     * @return
     *
     * Contabiliza o numero de elementos que estão em max-heap, retornando o nu-
     * mero da maior subsequencia.
     */
    public static int getMaxInMaxHeap(int[] v){
        int max=0,tmp=0;

        for (int i=0;i<v.length;++i){
            if (v[i] == 1){
                tmp++;
            }else{
                max=(tmp>max)?tmp:max;
                tmp=0;
            }
        }
        return (tmp>max)?tmp:max;
    }
    /**
     *
     * @param v
     * @param idx
     * Define a partir de uma posição todos os "parents" como "parents" que não
     * estão em conformidade. No âmbito deste exercicio é em max-heap, mas é
     * funcional em modo min-heap.
     */
    public static void setIsNotMaxHeap(int v[], int idx){

        while (idx>0){
            v[idx]=-1;
            idx=(idx-1)/2;
        }
        v[idx]=-1;
    }
    /**
     *
     * @param v
     * @param idx
     * @return
     * Verifica se os elementos que descendem dele estão em max-heap em relação
     * a ele.
     * 
     */
    public static boolean isMaxHeap(int[] v,int idx){
        return (v[2*idx+1] <= v[idx]  && ( ((2*idx+2)< v.length) ? v[2*idx+2] <= v[idx]:true) );
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        int v[] ={16,14,10,2,7,9,3,11,4,5};
        /*
         teste 1
         */
        printByDepth(v, v.length);
    
        /*teste 2*/
       // System.out.println("\n"+countMaxInMaxHeap(v, v.length));
        System.out.println("\n>>>"+largestSubArrayThatIsAMaxHeap(v));
    }

}
