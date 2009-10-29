package serie02;

/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 */
public class Iterables {

    public static <E> Iterable<E> concat(Iterable<E> iter1, Iterable<E> iter2) {
        return null;
    }

    public static <E> Iterable<E> takeWhile(Iterable<E> iter, Predicate<E> pred) {
        return null;
    }

    public interface Predicate<E> {

        boolean eval(E e);
    }
}
