package serie02;

import java.util.AbstractCollection;
import java.util.Collection;
import java.util.Deque;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * @param <E>
 */
public class AedLinkedList<E> extends AbstractCollection<E>  implements List<E>, Deque<E>, Cloneable{

    private class Node<E>{
        Node next;
        Node previous;
        E element;
        public Node(Node next, Node previous, E element){
            this.next=next;
            this.previous=previous;
            this.element=element;
        }
    }

    private class ListItr implements ListIterator{

        public boolean hasNext() {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        public Object next() {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        public void remove() {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        public boolean hasPrevious() {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        public Object previous() {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        public int nextIndex() {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        public int previousIndex() {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        public void set(Object e) {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        public void add(Object e) {
            throw new UnsupportedOperationException("Not supported yet.");
        }

    }

    @Override
    public Iterator<E> iterator() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public int size() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean addAll(int index, Collection<? extends E> c) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E get(int index) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E set(int index, E element) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public void add(int index, E element) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E remove(int index) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public int indexOf(Object o) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public int lastIndexOf(Object o) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ListIterator<E> listIterator() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ListIterator<E> listIterator(int index) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public List<E> subList(int fromIndex, int toIndex) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public void addFirst(E e) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public void addLast(E e) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean offerFirst(E e) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean offerLast(E e) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E removeFirst() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E removeLast() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E pollFirst() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E pollLast() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E getFirst() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E getLast() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E peekFirst() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E peekLast() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean removeFirstOccurrence(Object o) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean removeLastOccurrence(Object o) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean offer(E e) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E remove() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E poll() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E element() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E peek() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public void push(E e) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public E pop() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public Iterator<E> descendingIterator() {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
