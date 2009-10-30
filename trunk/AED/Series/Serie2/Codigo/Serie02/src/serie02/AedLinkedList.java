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
 */
public class AedLinkedList<E> extends AbstractCollection<E> implements List<E>, Deque<E>, Cloneable {

    private Node<E> h = new Node<E>(null, null, null);
    private int size = 0;

    private class LstItr implements ListIterator<E> {

        private Node<E> previous = h;
        private Node<E> next;
        private int idx;

        /*done*/
        public LstItr(int index) {
            next = AedLinkedList.this.getNodeAtIndex(index);
        }
        /*done*/
        public boolean hasNext() {
            return idx != size;
        }
        /*done*/
        public E next() {
            if (idx == size) {
                throw new NoSuchElementException();
            }
            previous = next;
            next = next.next;
            idx++;
            return previous.element;
        }
        /*done*/
        public boolean hasPrevious() {
            return idx != 0;
        }
        /*done*/
        public E previous() {
            if (idx == 0) {
                throw new NoSuchElementException();
            }
            previous = next = next.previous;
            --idx;
            return previous.element;
        }
        /*done*/
        public int nextIndex() {
            return idx;
        }
        /*done*/
        public int previousIndex() {
            return idx - 1;
        }
        /*done*/
        public void set(E e) {
            if (previous == h) throw new IllegalStateException();
            previous.element=e;
        }
        /*done*/
        public void add(E e) {
            previous=h;
            addAtHead(next, e);
            ++idx;
        }
        /*done*/
        public void remove() {
            Node<E> tmp = previous.next;

            AedLinkedList.this.remove(previous);

            if (next == previous)
                next = tmp;
            else
                --idx;

            previous=h;
        }
    }
    /*done*/
    public List<E> subList(int fromIndex, int toIndex) {
        if (fromIndex<0 || toIndex>size) throw new IndexOutOfBoundsException();
        if (fromIndex>toIndex) throw  new IllegalArgumentException();
              
        AedLinkedList<E> tmp =new AedLinkedList();
        for (Node <E> start =getNodeAtIndex(fromIndex);fromIndex<= toIndex;start=start.next){
            tmp.add(start.element);
            ++fromIndex;
        }
       return tmp;
    }
    /*done*/
    private class DescendingIterator implements Iterator{
        final LstItr lstItr=new LstItr(size());
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
    /*done*/
    public Iterator<E> descendingIterator() {
        return new DescendingIterator();
    }
    /*done*/
    public int indexOf(Object e) {
       int index =0;
        if (e == null){
            for (Node<E> node = h.next;node!=h;node=node.next){
                if (node.element==null)
                    return index;
                index++;
            }
        }else{
            for (Node<E> node = h.next;node!=h;node=node.next){
                if (e.equals(node.element))
                    return index;
                index++;
            }
        }
       return -1;

    }
    /*done*/
    public int lastIndexOf(Object e) {
        int index =0;
        if (e == null){
            for (Node<E> node = h.previous;node!=h;node=node.previous){
                if (node.element==null)
                    return index;
                index++;
            }
        }else{
            for (Node<E> node = h.previous;node!=h;node=node.previous){
                if (e.equals(node.element))
                    return index;
                index++;
            }
        }
       return -1;
    }
    /*done*/
    public boolean removeLastOccurrence(Object e) {
        if (e == null){
            for (Node<E> node = h.previous;node!=h;node=node.previous){
                if (node.element==null){
                    remove(node);
                    return true;
                }
            }
        }else{
            for (Node<E> node = h.previous;node!=h;node=node.previous){
                if (e.equals(node.element)){
                    remove(node);
                    return true;
                }
            }
        }
        return false;
    }
    /*done*/
    private Node<E> addAtHead(Node<E> node, E e) {
        Node<E> tmp = new Node<E>(node, node.previous, e);
        tmp.next.previous = tmp;
        tmp.previous.next = tmp;
        size++;
        return tmp;
    }
    /*done*/
    public void addFirst(E e) {
        addAtHead(h.next, e);
    }
    /*done*/
    public void addLast(E e) {
        addAtHead(h, e);
    }
    /*done*/
    public boolean offerFirst(E e) {
        addFirst(e);
        return true;
    }
    /*done*/
    public boolean offerLast(E e) {
        addLast(e);
        return true;
    }
    /*done*/
    public E pollFirst() {
        return (size == 0) ? null : getFirst();
    }
    /*done*/
    public E pollLast() {
        return (size == 0) ? null : getLast();
    }
    /*done*/
    public E getFirst() {
        if (size == 0) {
            throw new NoSuchElementException();
        }
        return h.next.element;
    }
    /*done*/
    public E getLast() {
        if (size == 0) {
            throw new NoSuchElementException();
        }
        return h.previous.element;
    }
    /*done*/
    public E peekFirst() {
        return (size == 0) ? null : getFirst();
    }
    /*done*/
    public E peekLast() {
        return (size == 0) ? null : getLast();
    }
    /*done*/
    public boolean removeFirstOccurrence(Object o) {
        return remove((E)o);
    }
    /*done*/
    public boolean offer(E e) {
        return add(e);
    }
    /*done*/
    public E poll() {
        return (size == 0) ? null : getFirst();
    }
    /*done*/
    public E element() {
        return getFirst();
    }
    /*done*/
    public E peek() {
        return (size == 0) ? null : getFirst();
    }
    /*done*/
    public void push(E e) {
        addFirst(e);
    }
    /*done*/
    public E pop() {
        return removeFirst();
    }
    /*done*/
    public Iterator<E> iterator() {
        return new LstItr(0);
    }
    /*done*/
    public int size() {
        return size;
    }
    /*done*/
    private class Node<E> {

        Node<E> next;
        Node<E> previous;
        E element;

        public Node(Node next, Node previous, E element) {
            this.next = next;
            this.previous = previous;
            this.element = element;
        }
    }
    /*done*/
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
    /*done*/
    public boolean addAll(int index, Collection<? extends E> c) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException();
        }

        Object[] tmpO= c.toArray();
        int newElmCnt=tmpO.length;
        if (newElmCnt == 0) return false;
        Node<E> next =(size == 0)?h:getNodeAtIndex(index);
        Node<E> previous=next.previous;

        for (int i = 0;i<newElmCnt;++i){
            Node<E> tmp = new Node<E>(next,previous,(E)tmpO[i]);
            next.next=tmp;
            next=tmp;
        }
        next.previous=previous;
        size+=newElmCnt;
        return true;
    }
    /*done*/
    public E get(int index) {
        return getNodeAtIndex(index).element;
    }
    /*done*/
    public E set(int index, E element) {
        Node<E> tmp = getNodeAtIndex(index);
        E retE=tmp.element;
        tmp.element=element;
        return retE;
    }
    /*done*/
    public void add(int index, E element) {
        Node<E> tmp=getNodeAtIndex(index);
        addAtHead( (size == 0)?h:tmp , element);
    }
    /*done*/
    public E remove(int index) {
        return remove(getNodeAtIndex(index));
    }
    /*done*/
    private E remove(Node<E> node){
        if (node == h) throw new NoSuchElementException();
        E e = node.element;
        node.previous.next=node.next;
        node.next.previous=node.previous;
        node.next=node.previous=null;
        node.element=null;
        --size;
        return e;
    }
    /*done*/
    public E remove() {
        return removeFirst();
    }
    /*Done*/
    public E removeFirst() {
        return remove(h.next);
    }
    /*Done*/
    public E removeLast() {
        return remove(h.previous);
    }
    /*done*/
    public ListIterator<E> listIterator(int index) {
        return new LstItr(index);
    }
    /*Node*/
    public ListIterator<E> listIterator() {
        return new LstItr(0);
    }
}
