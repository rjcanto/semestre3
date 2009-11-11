package serie02;

import java.util.AbstractCollection;
import java.util.Collection;
import java.util.Deque;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * @param <E>
 *
 * Muitos dos comentários dos métodos, é literalmente copy/paste do texto
 * contido na documentação do LinkedList, pois não nos faz muito sentido
 * traduzir uma classe que acabamos por implementar.
 * 
 */
public class AedLinkedList<E> extends AbstractCollection<E> implements List<E>, Deque<E>, Cloneable {

    private Node<E> h = new Node<E>(null, null, null);
    private int size = 0;

    /**
     * Classe que implemta o ListeIterator
     */
    private class LstItr implements ListIterator<E> {

        private Node<E> previous = h;
        private Node<E> next;
        private int idx;

        public LstItr(int index) {
            next = AedLinkedList.this.getNodeAtIndex(index);
        }

        public boolean hasNext() {
            return idx != size;
        }

        public E next() {
            if (idx == size) {
                throw new NoSuchElementException();
            }
            previous = next;
            next = next.next;
            idx++;
            return previous.element;
        }

        public boolean hasPrevious() {
            return idx != 0;
        }

        public E previous() {
            if (idx == 0) {
                throw new NoSuchElementException();
            }
            previous = next = next.previous;
            --idx;
            return previous.element;
        }

        public int nextIndex() {
            return idx;
        }

        public int previousIndex() {
            return idx - 1;
        }

        public void set(E e) {
            if (previous == h) {
                throw new IllegalStateException();
            }
            previous.element = e;
        }

        public void add(E e) {
            previous = h;
            addAtHead(next, e);
            ++idx;
        }

        public void remove() {
            Node<E> tmp = previous.next;

            AedLinkedList.this.remove(previous);

            if (next == previous) {
                next = tmp;
            } else {
                --idx;
            }

            previous = h;
        }
    }

    /**
     *
     * @param fromIndex - low endpoint (inclusive) of the subList
     * @param toIndex - high endpoint (exclusive) of the subList
     * @return - a view of the specified range within this list
     */
    public List<E> subList(int fromIndex, int toIndex) {
        if (fromIndex < 0 || toIndex > size) {
            throw new IndexOutOfBoundsException();
        }
        if (fromIndex > toIndex) {
            throw new IllegalArgumentException();
        }

        AedLinkedList<E> tmp = new AedLinkedList();
        for (Node<E> start = getNodeAtIndex(fromIndex); fromIndex <= toIndex; start = start.next) {
            tmp.add(start.element);
            ++fromIndex;
        }
        return tmp;
    }

    /**
     * Classe que implementa um iterador, de forma a ter um Iterador descendente
     */
    private class DescendingIterator implements Iterator {

        final LstItr lstItr = new LstItr(size());

        public DescendingIterator() {
        }

        public boolean hasNext() {
            return lstItr.hasNext();
        }

        public Object next() {
            return lstItr.next;
        }

        public void remove() {
            lstItr.remove();
        }
    }

    /**
     *  Returns an iterator over the elements in this deque in reverse sequential order.
     * @return
     */
    public Iterator<E> descendingIterator() {
        return new DescendingIterator();
    }

    /**
     * Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
     * @param e
     * @return
     */
    public int indexOf(Object e) {
        int index = 0;
        if (e == null) {
            for (Node<E> node = h.next; node != h; node = node.next) {
                if (node.element == null) {
                    return index;
                }
                index++;
            }
        } else {
            for (Node<E> node = h.next; node != h; node = node.next) {
                if (e.equals(node.element)) {
                    return index;
                }
                index++;
            }
        }
        return -1;

    }

    /**
     * Returns the index of the last occurrence of the specified element in this list, or -1 if this list does not contain the element.
     * @param e
     * @return
     */
    public int lastIndexOf(Object e) {
        int index = 0;
        if (e == null) {
            for (Node<E> node = h.previous; node != h; node = node.previous) {
                if (node.element == null) {
                    return index;
                }
                index++;
            }
        } else {
            for (Node<E> node = h.previous; node != h; node = node.previous) {
                if (e.equals(node.element)) {
                    return index;
                }
                index++;
            }
        }
        return -1;
    }

    /**
     * Removes the last occurrence of the specified element in this list (when traversing the list from head to tail).
     * @param e
     * @return
     */
    public boolean removeLastOccurrence(Object e) {
        if (e == null) {
            for (Node<E> node = h.previous; node != h; node = node.previous) {
                if (node.element == null) {
                    remove(node);
                    return true;
                }
            }
        } else {
            for (Node<E> node = h.previous; node != h; node = node.previous) {
                if (e.equals(node.element)) {
                    remove(node);
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Método que nos permite (mais facilmente) implementar a adição de elementos
     * à cabeça da lista.
     * A necessidade surgiu quando notamos que teriamos que repetir o código em
     * mais do que um método.
     * @param node
     * @param e
     * @return
     */
    private Node<E> addAtHead(Node<E> node, E e) {
        Node<E> tmp = new Node<E>(node, node.previous, e);
        tmp.next.previous = tmp;
        tmp.previous.next = tmp;
        size++;
        return tmp;
    }

    /**
     * Inserts the specified element at the beginning of this list.
     * @param e
     */
    public void addFirst(E e) {
        addAtHead(h.next, e);
    }

    /**
     * Appends the specified element to the end of this list.
     * @param e
     */
    public void addLast(E e) {
        addAtHead(h, e);
    }

    /**
     * Inserts the specified element at the front of this list.
     * @param e
     * @return
     */
    public boolean offerFirst(E e) {
        addFirst(e);
        return true;
    }

    /**
     * Inserts the specified element at the end of this list.
     * @param e
     * @return
     */
    public boolean offerLast(E e) {
        addLast(e);
        return true;
    }

    /**
     * Retrieves and removes the first element of this list, or returns null if this list is empty.
     * @return
     */
    public E pollFirst() {
        return (size == 0) ? null : getFirst();
    }

    /**
     * Retrieves and removes the last element of this list, or returns null if this list is empty.
     * @return
     */
    public E pollLast() {
        return (size == 0) ? null : getLast();
    }

    /**
     * Returns the first element in this list.
     * @return
     */
    public E getFirst() {
        if (size == 0) {
            throw new NoSuchElementException();
        }
        return h.next.element;
    }

    /**
     * Returns the last element in this list.
     * @return
     */
    public E getLast() {
        if (size == 0) {
            throw new NoSuchElementException();
        }
        return h.previous.element;
    }

    /**
     * Retrieves, but does not remove, the first element of this list, or returns null if this list is empty.
     * @return
     */
    public E peekFirst() {
        return (size == 0) ? null : getFirst();
    }

    /**
     * Retrieves, but does not remove, the last element of this list, or returns null if this list is empty.
     * @return
     */
    public E peekLast() {
        return (size == 0) ? null : getLast();
    }

    /**
     * Removes the first occurrence of the specified element in this list (when traversing the list from head to tail).
     * @param o
     * @return
     */
    public boolean removeFirstOccurrence(Object o) {
        return remove((E) o);
    }

    /**
     * Adds the specified element as the tail (last element) of this list.
     * @param e
     * @return
     */
    public boolean offer(E e) {
        return add(e);
    }

    /**
     * Retrieves and removes the head (first element) of this list
     * @return
     */
    public E poll() {
        return (size == 0) ? null : getFirst();
    }

    /**
     * Retrieves, but does not remove, the head (first element) of this list.
     * @return
     */
    public E element() {
        return getFirst();
    }

    /**
     * Retrieves, but does not remove, the head (first element) of this list.
     * @return
     */
    public E peek() {
        return (size == 0) ? null : getFirst();
    }

    /**
     * Pushes an element onto the stack represented by this list.
     * @param e
     */
    public void push(E e) {
        addFirst(e);
    }

    /**
     * Pops an element from the stack represented by this list.
     * @return
     */
    public E pop() {
        return removeFirst();
    }

    /**
     * Returns an iterator over the elements in this list (in proper sequence).
     * @return
     */
    public Iterator<E> iterator() {
        return new LstItr(0);
    }

    /**
     * Returns the number of elements in this list.
     * @return
     */
    public int size() {
        return size;
    }

    /**
     * Classe com a definição do Node que vai ser utilizado na utilização da Lista.
     * @param <E>
     */
    private class Node<E> {

        Node<E> next;
        Node<E> previous;
        E element;

        public Node(Node<E> next, Node<E> previous, E element) {
            this.next = next;
            this.previous = previous;
            this.element = element;
        }
    }

    /**
     * Método que nos permite (mais facilmente) implementar a obtenção de elementos
     * da lista.
     * A necessidade surgiu quando notamos que teriamos que repetir o código em
     * mais do que um método.
     *
     * @param index
     * @return
     */
    private Node<E> getNodeAtIndex(int index) {
        Node<E> next;
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException("Size:" + size + "\tindex:" + index);
        }

        if (index > size / 2) {
            next = h;
            for (int i = size; i > index; --i) {
                next = next.previous;
            }
        } else {
            next = h.next;
            for (int i = 0; i < index; ++i) {
                next = next.next;
            }
        }
        return next;
    }

    /**
     * Appends all of the elements in the specified collection to the end of this list, in the order that they are returned by the specified collection's iterator.
     * @param index
     * @param c
     * @return
     */
    public boolean addAll(int index, Collection<? extends E> c) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException();
        }

        Object[] tmpO = c.toArray();
        int newElmCnt = tmpO.length;
        if (newElmCnt == 0) {
            return false;
        }
        Node<E> next = (size == 0) ? h : getNodeAtIndex(index);
        Node<E> previous = next.previous;

        for (int i = 0; i < newElmCnt; ++i) {
            Node<E> tmp = new Node<E>(next, previous, (E) tmpO[i]);
            next.next = tmp;
            next = tmp;
        }
        next.previous = previous;
        size += newElmCnt;
        return true;
    }

    /**
     * Returns the element at the specified position in this list.
     * @param index
     * @return
     */
    public E get(int index) {
        return getNodeAtIndex(index).element;
    }

    /**
     * Replaces the element at the specified position in this list with the specified element.
     * @param index
     * @param element
     * @return
     */
    public E set(int index, E element) {
        Node<E> tmp = getNodeAtIndex(index);
        E retE = tmp.element;
        tmp.element = element;
        return retE;
    }

    /**
     * Inserts the specified element at the specified position in this list.
     * @param index
     * @param element
     */
    public void add(int index, E element) {
        Node<E> tmp = getNodeAtIndex(index);
        addAtHead((size == 0) ? h : tmp, element);
    }

    /**
     * Removes the element at the specified position in this list.
     * @param index
     * @return
     */
    public E remove(int index) {
        return remove(getNodeAtIndex(index));
    }

    /**
     * Removes the first occurrence of the specified element from this list, if it is present.
     * @param node
     * @return
     */
    private E remove(Node<E> node) {
        if (node == h) {
            throw new NoSuchElementException();
        }
        E e = node.element;
        node.previous.next = node.next;
        node.next.previous = node.previous;
        node.next = node.previous = null;
        node.element = null;
        --size;
        return e;
    }

    /**
     * Retrieves and removes the head (first element) of this list.
     * @return
     */
    public E remove() {
        return removeFirst();
    }

    /**
     * Removes and returns the first element from this list.
     * @return
     */
    public E removeFirst() {
        return remove(h.next);
    }

    /**
     * Removes and returns the last element from this list.
     * @return
     */
    public E removeLast() {
        return remove(h.previous);
    }

    /**
     * Returns a list-iterator of the elements in this list (in proper sequence), starting at the specified position in the list.
     * @param index
     * @return
     */
    public ListIterator<E> listIterator(int index) {
        return new LstItr(index);
    }

    /**
     * Returns a list iterator over the elements in this list (in proper sequence). 
     * @return
     */
    public ListIterator<E> listIterator() {
        return new LstItr(0);
    }
}
