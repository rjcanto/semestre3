package serie02;

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
     * @param v - representa o Heap
     * @param count - numero de elementos dos quais queremos imprimir.
     *
     * Implementação:
     * A análise do heap demonstra que o comprimento de cada nivel se obtem
     * através da formula 2^n, com n >= 0. Assim sendo temos uma váriavel que
     * controla o numero de vezes que os nós são escritos em cada nivel.
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
     * @param v - Array com o heap
     * @param count - Numero de elementos do heap.
     * @return
     */
    public static int countMaxInMaxHeap(int[] v, int count){
        return countMaxinHeap(v, 0, count,v[0]);
    }
    /**
     *
     * @param v - Array com o Heap
     * @param i - Indicie a partir do qual se começa a analisar
     * @param count - numero de elementos presentes no heap
     * @param max - valor máximo do heap encontrado
     * @return - retorna o numero de ocorrencias
     *
     * Implementação:
     * Metodo recursivo para obter o numero de vezes que o máximo ocorre.
     */
    public static int countMaxinHeap(int[] v, int i, int count ,int max){
        if (2*i+1>=count) return 0;
        if (2*i+2>=count) return 0;
        if (v[i] != max) return 0;
        int total =0;
        if(v[2*i+1] == max) total+=countMaxinHeap(v, 2*i+1, count,max);
        if(v[2*i+2] == max) total+=countMaxinHeap(v, 2*i+2, count,max);
        return total+1;
    }
    /**
     * Este método retorna a dimensão do maior sub-array de v, com início no
     * ındice 0, que representa um max-heap.
     * @param v - Array com o heap a ser analasizado
     * @return - retorna o numero elementos do maior max-heap do heap.
     */
    public static int largestSubArrayThatIsAMaxHeap(int[] v){
        return checkMaxHeap(v);
    }
    /**
     *
     * @param v - Array com o heap a ser analasizado
     * @return - retorna o numero elementos do maior max-heap do heap.
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
        int lastParent=((v.length-1)-1)/2;
        int[] parents=new int[v.length];
       

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
        print(parents);
       return getMaxInMaxHeap(parents, v.length);
    }

    /**
     *
     * @param v - Array com o heap a ser analasizado
     * Método auxiliar que coloca no ecrã o conteudo do array de inteiros V.
     * Serve principalmente para um verificações rápidas, sem recorrer ao debug
     * exaustivo.
     */
    public static void print(int [] v){
        System.out.println();
        for (int i=0;i<v.length;++i){
            System.out.println(v[i]);
        }
    }

    /**
     *
     * @param v - Array com o heap a ser analasizado
     * @return - retorna o numero elementos do maior max-heap do heap.
     *
     * Contabiliza o numero de elementos que estão em max-heap, retornando o nu-
     * mero da maior subsequencia.
     */
    public static int getMaxInMaxHeap(int[] v, int dim){
        int max=0;
        for (int i=0;i<dim;++i){
            if (v[i] == 1){
                return getLen(v, i, dim);
            }
        }
        return max;
    }

    /**
     *
     * @param v - Array que contem o heap
     * @param i - indicie a partir do qual começa
     * @param dim - tamanho heap
     * @return - retorna o numero de elementos.
     */
    private static int getLen(int[] v, int i,int dim){
        if (i>=dim) return 0;
        int total=0;
        total+= getLen(v, 2*i+1, dim);
        total+= getLen(v, 2*i+2, dim);
        return total+1;
    }

    /**
     *
     * @param v - array com o heap
     * @param idx - indicie a partir do qual marca o nó como não max-heap
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
     * @param v - array com o heap
     * @param idx - indicie do elemento que vais testar se está em max-heap
     * @return - retorna true se é max-heap, false caso contrário.
     * Verifica se os elementos que descendem dele estão em max-heap em relação
     * a ele.
     * 
     */
    public static boolean isMaxHeap(int[] v,int idx){
        return (v[2*idx+1] <= v[idx]  && ( ((2*idx+2)< v.length) ? v[2*idx+2] <= v[idx]:true) );
    }
}
