/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aedserie4;

/**
 *
 * @author nac
 */
public class GreedyAlgorithm {

    /**
     * Algorimo 1
     * @param tarefas
     * @return
     */


    public static Tarefa[] getSequence1(Tarefa[] tarefas) {
        Tarefa[] result = new Tarefa[tarefas.length];
        int maxday = tarefas[0].deadLine - 1;
        int lastindex = tarefas.length;
        boolean isFull = false;
        int tmp;

        for (int i = 0; i < tarefas.length; i++) {
            tmp = tarefas[i].deadLine - 1;
            if (tmp > maxday || isFull) {
                result[--lastindex] = tarefas[i];
            } else {
                if (result[tmp] == null) {
                    result[tmp] = tarefas[i];
                } else {
                    tmp = findNext(result, tmp);
                    if (tmp > -1) {
                        result[tmp] = tarefas[i];
                    } else {
                        isFull = true;
                        result[--lastindex] = tarefas[i];
                    }
                }
            }


        }
        quicksort(result, 0, maxday);
        quicksort(result, maxday + 1, result.length - 1);
        return result;
    }

    private static int findNext(Tarefa[] tarefas, int start) {
        for (; start > -1; start--) {
            if (tarefas[start] == null) {
                return start;
            }
        }
        System.out.println("Isfull");
        return -1;
    }


    public static void quicksort(Tarefa[] t, int l, int r) {
        if (r > l) {
            int p = (l + r) / 2;
            int np = partition(t, l, r, p);
            quicksort(t, l, np - 1);
            quicksort(t, np + 1, r);
        }

    }

    private static int partition(Tarefa[] t, int l, int r, int p) {
        int pv = t[p].deadLine;
        swap(t, p, r);
        int si = l;
        for (int i = l; i < r; i++) {
            if (t[i].deadLine <= pv) {
                swap(t, i, si);
                si++;
            }
        }
        swap(t, si, r);
        return si;
    }

    private static void swap(Tarefa[] t, int p, int r) {
        Tarefa tmp = t[p];
        t[p] = t[r];
        t[r] = tmp;
    }



    /**
     * Algoritmo 2
     * @param tarefas
     */
    public static void getSequence2(Tarefa[] tarefas) {
        AEDSetNode[] set = new AEDSetNode[tarefas.length];
        Tarefa[] result = new Tarefa[tarefas.length];

        boolean isFull = false;
        int max = tarefas[0].deadLine;


        for (int i = 0; i < tarefas.length; ++i) {
            isFull = !MakeSet(set, tarefas[i].deadLine);

            //União à Direita
            Union(set, i, i + 1);

            //à esqueda
            Union(set, i - 1, i);
        }
    }

    public static boolean MakeSet(AEDSetNode[] set, int idx) {
        int max;
        if (set[idx] != null) {
            max = set[idx].getMaxIdx();
            idx = max - set[max].getSize();
        }
        if (idx < 0) {
            return false;
        }
        set[idx] = new AEDSetNode(1, idx);
        return true;
    }

    public static void Union(AEDSetNode[] set, int current, int next) {
        int max = set[next].getMaxIdx();
        int size = set[next].getSize() + set[current].getSize();

        set[current].setMaxIdx(max);
        set[max].setSize(size);
    }

    public static void FindSet(Tarefa t) {
    }

    public static void Size(Tarefa t) {
    }

    public static void Largest(Tarefa t) {
    }
    public static void main(String[] args) {
        Tarefa t1 = new Tarefa(1, 5, 100);
        Tarefa t2 = new Tarefa(2, 3, 90);
        Tarefa t3 = new Tarefa(3, 1, 80);
        Tarefa t4 = new Tarefa(4, 4, 70);
        Tarefa t5 = new Tarefa(5, 2, 60);
        Tarefa t6 = new Tarefa(6, 1, 50);
        Tarefa t7 = new Tarefa(7, 1, 40);
        Tarefa t8 = new Tarefa(8, 3, 30);
        Tarefa t9 = new Tarefa(9, 6, 20);
        Tarefa t10 = new Tarefa(10, 7, 10);

        Tarefa[] ts = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10};
        for (int i = 0; i < ts.length; i++) {
            ts[i].print();
        }
        Tarefa[] rs = getSequence1(ts);
        System.out.println("-------------------------------------------------");
        for (int i = 0; i < rs.length; i++) {
            rs[i].print();
        }
    }
}

class AEDSetNode {

    private int size;
    private int maxIdx;

    public AEDSetNode(int s, int m) {
        size = s;
        maxIdx = m;
    }

    public void setSize(int s) {
        size = s;
    }

    public void setMaxIdx(int m) {
        maxIdx = m;
    }

    public int getMaxIdx() {
        return maxIdx;
    }

    public int getSize() {
        return size;
    }
}
