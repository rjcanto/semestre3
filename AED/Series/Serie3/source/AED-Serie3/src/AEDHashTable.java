/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 *
 * Exercicio 1:
 *
 */

import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class AEDHashTable<E> {

    private final double REASHFACTOR = 0.70;
    private final int INCFACTOR = 3;
    private int size = 97;
    private ExtNode[] hashTable;
    private Comparator howToCompare;

    /**
     *
     * @param cmp
     * A construção da tabela de dispersão requer um comparador, a forma de como
     * os elementos são comparaveis, para tornar mais efeciente
     */
    public AEDHashTable(Comparator cmp) {
        hashTable = new ExtNode[size];
        howToCompare = cmp;
    }

    /**
     *
     * @param e
     * Coloca um novo elemento na tabela.
     * Verifica se a tabela necessita de ser redimensionada.
     */
    public void put(E e) {
        Node<E> newNode = new Node(e);
        int index = getIndex(e);

        if ((hashTable[index] != null) && (hashTable[index].getNbrElements() / size >= REASHFACTOR)) {
            reash();
        }

        add(hashTable[index], newNode);
    }

    /**
     *Função que redimenciona a tabela de dispersão.
     *Copia os elementos para a sua nova posição.
     *Actualiza os novos valores.
     */
    private void reash() {
        int ns = size * INCFACTOR;
        ExtNode[] hashTable2;
        hashTable2 = new ExtNode[ns];
        int newidx;
        E tmp = null;

        while (size > 0) {
            --size;
            if (hashTable[size].getNbrElements() > 0) {
                Iterator itr = itera(hashTable[size]).iterator();
                while (itr.hasNext()) {
                    tmp = (E) itr.next();
                    Node<E> n = new Node<E>(tmp);
                    newidx = getIndex(tmp);
                    add(hashTable2[newidx], n);
                }
            }
        }
        size = ns;
        hashTable = hashTable2;
    }

    /**
     *
     * @param ex
     * @param n
     *
     * Faz inserção ordenada.
     * Tem um custo linear na inserção, mas torna as pesquisas e outros métodos
     * solicitados, mais rápidos.
     **/
    private void add(ExtNode<E> ex, Node<E> n) {
        Node<E> next = ex;
        while ((next = next.next) != ex) {
            if (howToCompare.compare(n.element, next.element) > -1) {
                addHere(next, n);
                ex.incNbrElements();
                return;
            }
        }
        addHere(next, n);
        ex.incNbrElements();
    }

    /**
     *
     * @param head
     * @param newNode
     * Adiciona o node newNode após o node head.
     */
    private void addHere(Node<E> head, Node<E> newNode) {
        newNode.next = head.next;
        newNode.previous = head;
        head.next.previous = newNode;
        head.next = newNode;
    }

    /**
     *
     * @param e
     * @return
     * obtem o indicie para a tabela de dispersão
     */
    private int getIndex(E e) {
        int index = e.hashCode() % size;
        return (index < 0) ? index + size : index;
    }


    /**
     *
     * @param e
     * @return
     * Retorna o teste à chamada de contain, que retorna null se forem iguais,
     * ou então o maior dos menores nó.
     */
    public boolean contains(E e){
        return (contain(e) == null);
    }
    /**
     *
     * @param e
     * @return
     * Verifica se o elemento existe na tabela.
     * Indexa rapidamente a posição da tabela e como está ordenado verifica se é
     * maior que o elemento constante (e não existe) ou se é igual (existe). Se
     * chegar ao fim da lista, todos os elementos são menores e o elemento não
     * está contido na lista.
     */
    private Node<E> contain(E e) {
        int newidx = getIndex(e);
        int res;
        Iterator itr = itera(hashTable[newidx]).iterator();
        Node<E> tmp=hashTable[newidx];
        while(tmp.next!= hashTable[newidx]){
            res=howToCompare.compare(tmp.element, e);

            if (res>0){
                return tmp.previous;
            }else if (res == 0){
                return null;
            }
            tmp=tmp.next;
        }

        return tmp.previous;
    }

    /**
     *Chama para todos os indicies o metodo para remover os duplicados.
     */
    public void removeAllDuplicates() {
        int i = 0;
        while (i < size) {
            removeDuplicates(hashTable[i++]);
        }
    }

    /**
     *
     * @param n
     * O primeiro elementos da lista indicia quantos elementos existem na lista.
     * Assim, se não houver elementos sai do metodo, caso contrario verifica se
     * ha iguais remove duplicados, utilizando o iterador.
     */
    private void removeDuplicates(ExtNode<E> n) {
        if (n.getNbrElements() == 0) {
            return;
        }
        Iterator itr = itera(n).iterator();
        E e = (E) itr.next();
        while (itr.hasNext()) {
            if (itr.next().equals(e)) {
                itr.remove();
                n.decNbrElements();
            }
        }
    }

    /**
     *
     * @param e
     * @return
     * Coloca o elemento caso seja unico e retorna null, ou não o coloca e
     * retorna o elemento.
     * Actualiza os valores do numero de elementos da lista.
     */
    public E putUnique(E e) {
        Node<E> tmp =contain(e);
        if (tmp != null){
            addHere(tmp.previous, tmp);
            hashTable[getIndex(e)].incNbrElements();
            return null;
        }
        return e;
    }
    /**
     *
     * @param <E>
     * @param n
     * @return
     * Retorna o iterado para uma lista
     */
    private <E> Iterable<E> itera(final ExtNode<E> n) {
        return new Iterable<E>() {

            public Iterator<E> iterator() {
                return new Iterator<E>() {

                    Node<E> tn = n;
                    E element = null;

                    public boolean hasNext() {
                        if (tn.next != n) {
                            element = n.element;
                            tn = tn.next;
                            return true;
                        }
                        return false;
                    }

                    public E next() {
                        if (element == null && !hasNext()) {
                            throw new NoSuchElementException();
                        }
                        E tmp = element;
                        element = null;
                        return tmp;
                    }

                    public void remove() {
                        if (element == null) {
                            throw new NoSuchElementException();
                        }
                        tn.next.previous = tn.previous;
                        tn.previous.next = tn.next;
                        element = null;
                        tn = tn.next;

                        throw new UnsupportedOperationException("Not supported yet.");
                    }
                };
            }
        };
    }

    /**
     *
     * @param <E>
     * Definição de No
     */
    class Node<E> {

        Node<E> previous;
        Node<E> next;
        E element;

        Node(E e) {
            element = e;
            next = previous = this;
        }
    }

    /**
     *
     * @param <E>
     *
     * Definição de Nó extendido.
     * Este nó vai definir os nós "dummies" no array, contendo o numero de
     * elementos da lista.
     */
    class ExtNode<E> extends Node<E> {

        private int nbrElements;

        public ExtNode(E e) {
            super(e);
            this.nbrElements = 0;
            previous = next = this;
        }

        public int getNbrElements() {
            return nbrElements;
        }

        public void incNbrElements() {
            nbrElements++;
        }

        public void decNbrElements() {
            if (nbrElements > 0) {
                nbrElements--;
            }
        }
    }

    /**
     * 
     * @param args
     */
    public static void main(String[] args) {
    }
}

