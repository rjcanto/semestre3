/**
 *
 * @author nac
 */
/**
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

    public static <E> int copyToArrayAux(Node<E> root, E[] v,int idx) {
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
     * Ex:
     * (Indicies)
     * Level 0:
     * nEle=7
     * mid=(nEle+1)/2=(7+1)/2=4
     * ===========================
     * Level 1 (Left):
     * nEle=nEle - mid= 7 - 4 = 3
     * mid=(nEle+1)/2=(3+1)/2=2
     * Level 2 (Left):
     * nEle=nEle - mid= 3 - 2 = 1
     * mid=(nEle+1)/2=(1+1)/2=1
     * Level 2 (Right):
     * nEle=nEle + mid= 3 + 2 = 5
     * mid=(nEle+1)/2=(5+1)/2=3
     * ===========================
     * Level 1 (Right):
     * nEle=nEle + mid= 7 + 4 = 11
     * mid=(nEle+1)/2=(11+1)/2=6
     *
     * Level 2 (Left):
     * nEle=nEle - mid= 11 - 6 = 5
     * mid=(nEle+1)/2=(5+1)/2=3
     * Level 2 (Right):
     * nEle=nEle + mid= 11 + 6 = 17
     * mid=(nEle+1)/2=(17+1)/2=9
     *
     * neste exercicio:
     * nElement=d
     *
     * (Value)
     * u(n)=u(1)+(n-1).r
     * neste exercicio
     * u(n) = u(1)+(n-1).d
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

    public static Node<Integer> BSTFAP(int a, int r, int n, int nEle) {
        if(r<=0 || nEle < 1|| n < 0  ) {
            System.out.println("=>null");
            return null;
        }
        //Novo Nó
        int mid=(n+n%2)/2 ;
        int value=elementFromArithProg(a, mid, r);

        Node<Integer> nN=new Node<Integer>(value);
        System.out.println("nElem :"+nEle+" n : "+n+" node : "+mid);
        int next=(n%2 == 0)?n-(nEle)/2 -1:n-(nEle +1 )/2;
        nN.left =BSTFAP(a, r,next , (nEle - (n+1)%2)/2 );
        nN.right=BSTFAP(a, r, n+(nEle + (n)%2 )/2 , nEle/2 );
        return nN;
    }


    private static int elementFromArithProg(int u1, int n, int r){
        return u1+(n-1)*r;
    }

    public static <E extends Comparable<E>> int rangeCount(Node<E> root, E l, E r) {
        return 0;
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
       Node<Integer> n= createBSTFromArithmeticProgression(1, 1, 23);
    }
}
