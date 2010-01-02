/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 *
 *
 * Realize a classe contendo os seguintes métodos estáticos para a manipulação
 * de ávores. Assuma que cada objecto do tipo Node<E> tem 3 campos:
 * - um value do tipo E
 * - left
 * - right
 * para os descendentes respectivos.
 *
 */
public class AEDTree<E> {

    /**
     * que copia para o array v os elementos da ávore binária de pesquisa
     * referenciada por root. Os elementos devem ficar organizados no array
     * por ordem decrescente, com o maior elemento na primeira posição.
     * Caso a dimensão da árvore exceda a dimensão do array, apenas são copiados
     * os ultimos v.length elementos.
     */

    public static <E> int copyToArray(Node<E> root, E[] v) {
        return copyToArrayAux(root, v, 0);
    }

    /**
     *
     * @param <E>
     * @param root
     * @param v
     * @param idx
     * @return
     *
     *
     * Método auxilizar para proceder a cópia.
     */
    private static <E> int copyToArrayAux(Node<E> root, E[] v,int idx) {
        if (idx >= v.length || root == null ) return 0;

        if (root.right != null)
            idx+=copyToArrayAux(root.right, v,idx);

        v[idx++]=root.value;
        if (root.left != null)
            idx+=copyToArrayAux(root.left, v,idx);

        return idx;
    }


    /**
     * que retorna a referência para o nó raíz duma árvore binária de pesquisa
     * contendo os inteiros da progress aritmética com inicío em a, dimensão n e
     * factor d (diferença entre dois elementos consecutivos d).
     * Assuma que o factor d é maior do que zero. A árvore resultante deve
     * estar balanceada.

     *
     *
     * @param a - inicio da Progressão Aritmetica
     * @param r - razão da Progressão Aritmetica
     * @param n - Numero de elementos
     * @return - Novo nó
     */
    public static Node<Integer> createBSTFromArithmeticProgression(int a, int r, int n) {
        return BSTFAP(a, r, n, n);
    }

    /**
     *
     * @param a
     * @param r
     * @param n
     * @param nEle
     * @return
     *
     * Método auxiliar para poder ser executada recurssivamente.
     */

    public static Node<Integer> BSTFAP(int a, int r, int n, int nEle) {
        if(r<=0 || nEle < 1|| n < 0  ) {
            return null;
        }
        //Novo Nó
        int mid=(n+n%2)/2 ;
        int value=elementFromArithProg(a, mid, r);

        Node<Integer> nN=new Node<Integer>(value);
        System.out.println("\t\t Node :"+mid+" Value : "+nN.value);

        int next=(n%2 == 0)?n-(nEle)/2 -1:n-(nEle +1 )/2;
        nN.left =BSTFAP(a, r,next , (nEle - (n+1)%2)/2 );
        nN.right=BSTFAP(a, r, n+(nEle + (n)%2 )/2 , nEle/2 );
        return nN;
    }

    /**
     *
     * @param u1
     * @param n
     * @param r
     * @return
     * Retorna o valor da progressão aritmética respeitando os valores do argumento
     */
    private static int elementFromArithProg(int u1, int n, int r){
        return u1+(n-1)*r;
    }

    /**
     *
     * @param <E>
     * @param root
     * @param l
     * @param r
     * @return
     * que retorna o número de elementos da árvore binária de pesquisa com raíz
     * root pertencentes ao intervalo [l; r].
     * Considere que o critério de organização da árvore binária de pesquisa é a
     * ordenação natural do tipo E.
     */
    public static <E extends Comparable<E>> int rangeCount(Node<E> root, E l, E r) {

        if (l == null || r == null || root == null) return 0;

        if (l.compareTo(root.value) >0){
            return rangeCount(root.right, l, r);
        }
        if (r.compareTo(root.value) < 0){
            return rangeCount(root.left, l, r);
        }
        return rangeCount(root.left, l, r) + rangeCount(root.right, l, r) +1;
    }


    static class Node<E> {

        Node<E> left;
        Node<E> right;
        E value;

        Node(E e) {
            value = e;
            left = right = this;
        }
    }

    /**
     *
     * @param args
     */
    public static void main(String[] args) {
    }
}
