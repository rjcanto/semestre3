/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 *
*/

import java.util.Iterator;
import java.util.NoSuchElementException;
/**
 * A melhor solução para este problema seria manter o "histórico" de elementos
 * retornados em forma de árvore binária ou mesmo utilizando a estrutura criada
 * no primeiro exercicio.
 * Por conhecer as soluções, melhores é que não alteramos a estrutura já 
 * implementada.
 * 
 */
public class Iterables {

    public static <E> Iterable<E> distinct(final Iterable<E> iter) {
        return new Iterable<E>() {

            public Iterator<E> iterator() {
                return new Iterator<E>() {

                    class Node<E> {

                        Node<E> previous;
                        Node<E> next;
                        E element;

                        Node(E e) {
                            element = e;
                            next = previous = null;
                        }
                    }
                    Node<E> node = null;
                    E element = null;
                    Iterator<E> itr = iter.iterator();

                    public boolean hasNext() {
                        if (!itr.hasNext()) {
                            element = null;
                            return false;
                        }
                        element = itr.next();
                        Node tmpNode = node;
                        while (tmpNode.next != null) {
                            if (tmpNode.element.equals(element)) {
                                if (!itr.hasNext()) {
                                    element = null;
                                    return false;
                                }
                                element = itr.next();
                                tmpNode = node;
                            }
                            tmpNode = tmpNode.next;
                        }
                        Node newNode = new Node(element);

                        newNode.next = node.next;
                        newNode.previous = node;
                        node.next.previous = newNode;
                        node.next = newNode;

                        return true;
                    }

                    public E next() {
                        if (element == null && !hasNext()) {
                            throw new NoSuchElementException();
                        }

                        E e = element;
                        element = null;
                        return e;
                    }

                    public void remove() {
                        throw new UnsupportedOperationException("Not supported yet.");
                    }
                };
            }
        };

    }
}
