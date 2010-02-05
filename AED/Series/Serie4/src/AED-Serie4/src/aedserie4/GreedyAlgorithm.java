/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aedserie4;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Comparator;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;

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
        return result;
    }

    /**
     * Procura a posição livre para atribuir à tarefa a realizar.
     * @param tarefas
     * @param start
     * @return
     */
    private static int findNext(Tarefa[] tarefas, int start) {
        for (; start > -1; --start) {
            if (tarefas[start] == null) {
                return start;
            }
        }
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
        int pv = t[p].penalty;
        swap(t, p, r);
        int si = l;
        for (int i = l; i < r; i++) {
            if (t[i].penalty >= pv) {
                swap(t, i, si);
                si++;
            }
        }
        swap(t, si, r);
        return si;
    }

        public static void quicksort(Tarefa[] t, int l, int r,Comparator<Tarefa> cmp) {
        if (r > l) {
            int p = (l + r) / 2;
            int np = partition(t, l, r, p,cmp);
            quicksort(t, l, np - 1,cmp);
            quicksort(t, np + 1, r,cmp);
        }

    }

    private static int partition(Tarefa[] t, int l, int r, int p, Comparator<Tarefa> cmp) {
        int pv = t[p].penalty;
        swap(t, p, r);
        int si = l;
        for (int i = l; i < r; i++) {
            if (cmp.compare(t[i], t[p]) > 0) {
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

    public static void printArr(Tarefa[] ts) {
        for (int i = 0; i < ts.length; i++) {
            ts[i].print();
        }
    }

    public static Tarefa[] dataLoader(String filename) {
        File file = new File(filename);
        BufferedReader br = null;
        String line;
        StringTokenizer element = null;
        int maxLines=0;
        Tarefa[] tarefas = null;
        boolean isFirstLine = true;
        int idx = 0;
        try {
            br = new BufferedReader(new FileReader(filename));
            while ((line = br.readLine()) != null) {
                element = new StringTokenizer(line, ";");
                //read first line
                if (isFirstLine) {
                    maxLines = Integer.parseInt((String) element.nextElement());
               
                    tarefas = new Tarefa[maxLines];
                    isFirstLine = false;
                    element=null;
                    continue;
                }
                if (element.countTokens() == 3)
                    tarefas[idx++] = createTarefa(element);
                element=null;
            }
        } catch (FileNotFoundException ex) {
            Logger.getLogger(GreedyAlgorithm.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(GreedyAlgorithm.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                br.close();
            } catch (IOException ex) {
                Logger.getLogger(GreedyAlgorithm.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        quicksort(tarefas, 0, maxLines-1);
        return tarefas;
    }

    private static Tarefa createTarefa(StringTokenizer element) {
        int id = Integer.parseInt((String) element.nextElement());
        int deadLine = Integer.parseInt((String) element.nextElement());
        int penalty = Integer.parseInt((String) element.nextElement());
        Tarefa t = new Tarefa(id, deadLine, penalty);
        return t;
    }

    /*
    ============================================================================
     */
    /**
     * Algoritmo 2
     * @param tarefas
     */
    public static void main(String[] args) {
        String linuxPath="/home/masterzdran/ISEL/semestre3/AED/Series/Serie4/src/AED-Serie4/src/aedserie4";
            Tarefa[] xs=dataLoader(linuxPath+"/tarefas.txt");
        System.out.println("-------------------------------------------------");
        System.out.println("Array Original");
        System.out.println("-------------------------------------------------");
            printArr(xs);
        System.out.println("-------------------------------------------------");
        System.out.println("GetSequece 1");
        System.out.println("-------------------------------------------------");
            Sequence2 x = new Sequence2(xs);
            Tarefa[] ss = getSequence1(xs);
            printArr(ss);
        System.out.println("-------------------------------------------------");
        System.out.println("GetSequence2");
        System.out.println("-------------------------------------------------");
            Tarefa[] rs = x.getSequence2();
            printArr(rs);
    }
}

class AEDSetNode {

    private int count;
    private int maxIdx;
    private Tarefa tarefa;

    public AEDSetNode(int s, int m, Tarefa t) {
        tarefa = t;
        count = s;
        maxIdx = m;
    }

    public void setSize(int s) {
        count = s;
    }

    public void setMaxIdx(int m) {
        maxIdx = m;
    }

    public int getMaxIdx() {
        return maxIdx;
    }

    public int getSize() {
        return count;
    }

    public Tarefa getTarefa() {
        return tarefa;
    }

    public String toString() {
        return "Size: " + getSize() + "\tMax: " + getMaxIdx();
    }
}

class Sequence2 {

    private AEDSetNode[] DS;
    private Tarefa[] S;
    private final Tarefa[] tarefas;
    private int size;
    private final int root;
    private final int INITIAL_SIZE = 1;
    private final int LASTPOSITION;

    public Sequence2(Tarefa[] tarefas) {
        this.size = tarefas.length;
        DS = new AEDSetNode[size];
        S = new Tarefa[size];
        this.tarefas = tarefas;
        LASTPOSITION = S.length - 1;
        root = tarefas[0].deadLine - 1;
    }

    public Tarefa[] getSequence2() {
        //2. Iniciar a estrutura de dados para conjuntos disjuntos DS, contendo um
        //conjunto por tarefa, ou seja, realizar makeSet(ti) para 1 <= i <=  n
        for (int i = 0; i < size; ++i) {
            MakeSet(i, tarefas[i]);
        }

        /* Para cada tarefa t em T,
        por ordem decrescente das penalizações p,
        onde d é o prazo de t
        Se S[d] estiver livre, realizar as afectações
        S[d]<-t
        pos<-d
        Caso contrário
        Afectar s com o conjunto em DS que contém a tarefa S[d]: s<-findSet(S[d])
        Afectar pos com a diferença entre o maior índice em S onde
        está inserido um elemento de (s) e o tamanho de s: pos<-largest(s)
        Se pos > 0, afectar S[pos] <-t
        Caso contrário, a tarefa (t) fica em atraso e é colocada na última
        posição ainda livre de S. Afectar pos com a posição em que ficou (t).

        Garantir que não existem dois conjuntos em DS cujas tarefas estejam
        contíguas em S:
        Se S[pos-1] não está livre, então union(findSet(S[pos]); findSet(S[pos -1]))
        Se S[pos + 1] não está livre, então union(findSet(S[pos]); findSet(S[pos + 1]))
        Retornar S
         */
        int d;

        AEDSetNode s;
        int pos = 0;
        int largest = -1;
        int sizeDS = -1;
        int lastidx = LASTPOSITION;
        for (int i = 0; i < size; ++i) {
            d = tarefas[i].deadLine - 1;
            if (S[d] == null) {
                S[d] = tarefas[i];
                pos = d;
            } else {
                s = FindSet(DS[d], i);
                largest = Largest(s);
                sizeDS = Size(s);
                pos = largest - sizeDS;
                if (pos >= 0 && pos < root) {
                    S[pos] = tarefas[i];
                } else {
                    pos = lastidx--;//pq cada nó tem tamanho 1
                    S[pos] = tarefas[i];
                }
            }
            if (pos > 0 && S[pos - 1] != null) {
                Union(FindSet(DS[pos - 1], pos - 1), FindSet(DS[pos], pos));
            }
            if (pos < size - 1 && S[pos + 1] != null) {
                Union(FindSet(DS[pos], pos), FindSet(DS[pos + 1], pos + 1));
            }
        }
        return S;

    }

    /**
     * A operção makeSet(x) cria e insere na colecção o conjunto constituído
     * apenas pelo elemento x;
     * @param set
     * @param idx
     * @return
     */
    public void MakeSet(int idx, Tarefa t) {
        DS[idx] = new AEDSetNode(INITIAL_SIZE, idx, t);
    }

    /**
     * A operação union(x; y) cria e insere na colecção o conjunto Tx union Ty,
     * onde Tx é o conjunto da colecção que con tem x e Ty é o conjunto que
     * contém y. Note-se que, porque a colecção é constituída por conjuntos
     * disjuntos, os conjuntos Tx e Ty são também removidos da colecção.
     *
     * @param set
     * @param current
     * @param next
     */
    public void Union(AEDSetNode DSPos1, AEDSetNode DSPos2) {
        int max = DSPos2.getMaxIdx();
        int s = DS[max].getSize() + DSPos1.getSize();
        //DS[max].setSize(s);
        int i = max;
        // System.out.println(">>>>"+s+"\t"+DSPos1.toString()+"\t"+DSPos2.toString());
        while (s > 0) {
            DS[i].setMaxIdx(max);
            DS[i].setSize(s);
            --s;
            --i;
        }
    }

    /**
     * A operação findSet(x) retorna o elemento representante do conjunto
     * presente na colecção e que contém o elemento x.
     *
     * @param t
     */
    public AEDSetNode FindSet(AEDSetNode t, int idx) {
        if (idx < 0) {
            return null;
        }

        if (DS[idx].equals(t)) {
            return DS[idx];
        } else {
            return FindSet(DS[idx], DS[idx].getMaxIdx());
        }

    }

    /**
     * size(x), que retorna o número de tarefas presentes no conjunto que
     * contém x;
     * @param t
     */
    public int Size(AEDSetNode t) {
        AEDSetNode tmp = FindSet(t, t.getMaxIdx());
        return tmp.getSize();
    }

    /**
     * que retorna o maior prazo associada a qualquer das tarefas presentes no
     * conjunto que contém x.
     * @param t
     */
    public int Largest(AEDSetNode t) {
        AEDSetNode tmp = FindSet(t, t.getMaxIdx());
        return tmp.getMaxIdx();
    }
}
class comparePenalties implements Comparator<Tarefa>{
    public int compare(Tarefa o1, Tarefa o2) {
        return o1.penalty - o2.penalty;
    }
}
class compareDeadlines implements Comparator<Tarefa>{
    public int compare(Tarefa o1, Tarefa o2) {
        return o1.deadLine - o2.deadLine;
    }
}
