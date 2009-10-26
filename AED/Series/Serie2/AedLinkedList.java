/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package serie2;

import java.util.AbstractCollection;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 *
 * @author nac
 */
public class AedLinkedList<E> extends AbstractCollection<E>{
    private int size;
    private Node<E> h=new Node<E>(null,null,null);

    public AedLinkedList(){
        h.next=h.previous=h;
    }
    
    public E getFirst() {
        if (size == 0)
            throw new NoSuchElementException();
        return h.next.element;
    }
    public E getLast()  {
        if (size == 0)
            throw new NoSuchElementException();
        return h.previous.element;
    }
    public boolean remove(Object o) {
        if (o == null){
            for (Node<E> n=h.next;n!=h;n=n.next){
                if(n.element == null){
                    remove(n);
                    return true;
                }
            }
        }else{
            for (Node<E> n=h.next;n!=h;n=n.next){
                if(o.equals(n.element)){
                    remove(n);
                    return true;
                }
            }
        }
    return false;
    }
    public E removeFirst() {
        return remove(h.next);
    }
    public E removeLast() {
        return remove(h.previous);
    }

    /*
    public void addFirst(E e) {}
    public void addLast(E e) {}
    public boolean contains(Object o) {}
    public boolean add(E e) {}

    public boolean addAll(Collection<? extends E> c) {}
    public boolean addAll(int index, Collection<? extends E> c) {}
    public void clear() {}
    public E get(int index) {}
    public E set(int index, E element) {}
    public void add(int index, E element) {}
    public E remove(int index) {}
    public int indexOf(Object o) {}
    public int lastIndexOf(Object o) {}
    public E peek() {}
    public E element() {}
    public E poll() {}
    public E remove() {}
    public boolean offer(E e) {}
    public boolean offerFirst(E e) {}
    public boolean offerLast(E e) {}
    public E peekFirst() {}
    public E peekLast() {}
    public E pollFirst() {}
    public E pollLast() {}
    public void push(E e) {}
    public E pop() {}
    public boolean removeFirstOccurrence(Object o) {}
    public boolean removeLastOccurrence(Object o) {}
    public ListIterator<E> listIterator(int index) {}
    private Entry<E> addBefore(E e, Entry<E> entry) {}
    private E remove(Entry<E> e) {}
    public Iterator<E> descendingIterator() {}
    public Object[] toArray() {}
     */
    private class ListItr implements ListIterator<E> {
        private Node<E> previous=h;
        private Node<E> next;
        private int idx;

        ListItr (int index){
            if (index< 0 || index>size)
                throw new IndexOutOfBoundsException("Size:"+size+"\tIndex:"+index);

            /*
             * Verifica se o indicie está mais perto do meio ou do fim.
             * Para não percorrer todos os elementos.
             */
            if (index < (size/2)){
                next=h.next;
                for(idx=0;idx<index;idx++)
                    next=next.next;
            }else{
                next=h;
                for(idx=size;idx>size;idx--)
                    next=next.previous;
            }
        }

        public boolean hasNext() {
            return idx != size;
        }

        public E next() {
            if (idx == size)
                throw new NoSuchElementException("Não Existe Elemento");
            previous=next;
            next=next.next;
            idx++;
            return previous.element;
        }

        public boolean hasPrevious() {
            return idx != 0;
        }

        public E previous() {
            if (idx == 0)
                throw new NoSuchElementException("Não Existem Elementos!");
            previous=next=next.previous;
            idx--;
            return previous.element;
        }

        public int nextIndex() {
            return idx;
        }

        public int previousIndex() {
            return idx-1;
        }

        public void remove() {
            Node<E> tmp=previous.next;
            
            try{
                AedLinkedList.this.remove(previous);
            }catch (NoSuchElementException e){
                throw new IllegalStateException("Não é possivel remover esse elemento!");
            }
            if (next == previous)
                next = tmp;
            else
                idx--;
            previous=h;
        }

        public void set(E e) {
            if (previous == h)
                throw new IllegalStateException("Operação Ilegal!");
            previous.element=e;
        }

        public void add(E e) {
            previous=h;
            addBefore(e,next);
            idx++;
        }
    }


    private Node<E> addBefore(E e, Node<E> node) {
	Node<E> tmp = new Node<E>(e, node, node.previous);
	tmp.previous.next = tmp;
	tmp.next.previous = tmp;
	size++;
	return tmp;
    }

    private E remove(Node<E> e) {
	if (e == h)
	    throw new NoSuchElementException();

        E tmp = e.element;
	e.previous.next = e.next;
	e.next.previous = e.previous;
        e.next = e.previous = null;
        e.element = null;
	size--;
        return tmp;
    }

    @Override
    public Iterator<E> iterator() {
        return new MyIterator();
    }


    @Override
    public int size() {
        return size;
    }

    private class MyIterator implements Iterator{
        protected int cursor =0;
        protected int lastIdx=-1;

        public boolean hasNext() {
            return cursor<AedLinkedList.this.size;
        }

        public Object next() {
            throw new UnsupportedOperationException("Not supported yet.");
        }

        public void remove() {
            throw new UnsupportedOperationException("Not supported yet.");
        }


    }
    static private class Node<E>{
        E element;
        Node<E> next;
        Node<E> previous;

        Node(E element,Node<E> previous,Node<E> next){
            this.element=element;
            this.next=next;
            this.previous=previous;
        }
    }

    /**
     * @param args the command line arguments
     */

    public static void main(String[] args) {

        // TODO code application logic here
    }
}

