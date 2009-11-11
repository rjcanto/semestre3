package serie02;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 *
 * Os comentários relevantes encontram-se no relatório.
 */
public class Iterables {
    /**
     *
     * @param <E>
     * @param iter1
     * @param iter2
     * @return
     * 3.1. public static <E> Iterable<E> concat(Iterable<E> iter1, Iterable<E> iter2)
     * que retorna um objecto com a interface Iterable<E>, representando a concatenação
     * das sequências iter1 e iter2. Não é necessário implementar o método remove,
     * pertencente à Interface genérica Iterator<E>.
     * A implementação deste método deve minimizar o espaço ocupado pelo iterador.
     *
     */
    public static <E> Iterable<E> concat(final Iterable<E> iter1, final Iterable<E> iter2) {
        return new Iterable<E>() {

            public Iterator<E> iterator() {
                return new Iterator<E>() {
                    private Iterator<E> i1 = iter1.iterator();
                    private Iterator<E> i2 = null;
                    E element =null;

                    public boolean hasNext() {
                        if (i1.hasNext()){
                            element=i1.next();
                            return true;
                        }else{
                            if(i2 == null)i2 = iter2.iterator();
                            if (i2.hasNext()){
                                element=i2.next();
                                return true;
                            }else{
                                element=null;
                                return false;
                            }
                        }
                    }

                    public E next() {
                        if (element == null && !hasNext()) {
                            throw new NoSuchElementException();
                        }
                        E e = element;
                        element=null;
                        return e;
                    }

                    public void remove() {
                        throw new UnsupportedOperationException("Not supported yet.");
                    }
                };
            }
        };
    }

    /**
     *
     * @param <E>
     * @param iter
     * @param pred
     * @return
     *
     * 3.2. public static <E> Iterable<E> takeWhile(Iterable<E> iter, Predicate<T> pred){
     * que retorna um objecto com a interface Iterable<E>, representando o maior
     * prefixo da sequêcia iter em que todos os elementos satisfazem o predicado
     * pred. Não é necessário implementar o método remove, pertencente à interface
     * genérica Iterator<E>. A implementação deste método deve minimizar o espaço
     * ocupado pelo iterador.
     * Use a seguinte definição da interface pred.
     * public interface Predicate<E> {
     * boolean eval(E e);
     * }
     * 
     */
    public static <E> Iterable<E> takeWhile(final Iterable<E> iter, final Predicate<E> pred) {
        return new Iterable<E>() {

            public Iterator<E> iterator() {
                return new Iterator<E>() {
                    private E element=null;
                    private Iterator<E> it=iter.iterator();
                    public boolean hasNext() {
                        while (it.hasNext()){
                            if (pred.eval(element=it.next())) {
                                return true;
                            }
                        }
                        element=null;
                        return false;
                    }

                    public E next() {
                        if (element==null && !hasNext()){
                            throw new NoSuchElementException();
                        }
                        E e=element;
                        element=null;
                        return e;
                    }

                    public void remove() {
                        throw new UnsupportedOperationException("Not supported yet.");
                    }
                };
            }
        };
    }

    public interface Predicate<E> {

        boolean eval(E e);
    }
}
