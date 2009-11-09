package serie02;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 */
/**
 * StringTokenizer foi usado em vez do String.split uma vez que o String.split
 * demonstrou ser bastante mais lento que o tokenizer
 */
public class ShortestPath {

    private static final String PATH = "D:/ISEL/Trabalhos/AED/Series/Serie2/";
    //private static final String PATH = "/home/masterzdran/ISEL/semestre3/AED/Series/Serie2/";
    private static final String FILENAME = PATH + "USA-road-d.NY.gr";
    private final String MERGE_FILENAME = FILENAME + ".merged";
    private final String SORTED_FILENAME = FILENAME + ".sorted";
    private final int MAX_LINES = 100000;
    private File filename;
    private PathNode[] pna;
    private Comparator cmp;
    private int nbrFiles = 0;
    private int maxLines;

    public ShortestPath(File filename, Comparator cmp) {
        this.filename = filename;
        this.cmp = cmp;
        pna = null;
    }

    public void initValues() {
        pna = null;
        pna = new PathNode[maxLines];
    }

    public int separeChunks() {
        BufferedReader fr = null;
        StringTokenizer element = null;
        String type = null;
        String line = null;
        int rowNbr = 0;

        try {
            fr = new BufferedReader(new FileReader(filename));
            while ((line = fr.readLine()) != null) {
                element = new StringTokenizer(line, " ");
                type = (String) element.nextElement();

                if (type.equals("c")) {
                    continue;
                }
                if (type.equals("p")) {
                    for (int i = 1; i < 3; ++i) {
                        element.nextElement();
                    }
                    maxLines = Integer.parseInt((String) element.nextElement());
                    maxLines = (maxLines > MAX_LINES) ? MAX_LINES : maxLines;
                    pna = new PathNode[maxLines];
                } else if (type.equals("a") && (rowNbr < maxLines)) {
                    pna[rowNbr++] = setPathNode(element);
                } else if (rowNbr == maxLines) {
                    mySort(rowNbr - 1);
                    write(pna, rowNbr, filename + "." + nbrFiles++, false);
                    initValues();
                    rowNbr = 0;
                    pna[rowNbr++] = setPathNode(element);
                }
            }
            if (rowNbr > 0 && rowNbr < maxLines) {
                mySort(rowNbr - 1);
                write(pna, rowNbr, filename + "." + nbrFiles++, false);
                initValues();
                rowNbr = 0;
            }
        } catch (FileNotFoundException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                fr.close();
            } catch (IOException ex) {
                Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        return nbrFiles;
    }

    private PathNode setPathNode(StringTokenizer element) {
        int tail = Integer.parseInt((String) element.nextElement());
        int head = Integer.parseInt((String) element.nextElement());
        int weight = Integer.parseInt((String) element.nextElement());

        PathNode pn = new PathNode('a', tail, head, weight);
        return pn;
    }

    public void merge() {
        int files2Decrease = nbrFiles - 1;
        int idx = 0;
        while (files2Decrease > 0) {
            mergeTwoChunks(filename + "." + idx++, filename + "." + files2Decrease--);

            if (idx >= files2Decrease) {
                idx = 0;
            }
        }
        File f1 = new File(filename + "." + idx);
        File f2 = new File(SORTED_FILENAME);
        f1.renameTo(f2);
    }

    /**
     *
     * @param file1
     * @param file2
     *
     * O ficheiro agregado ordenado está no nome do primeiro argumento passado.
     */
    public void mergeTwoChunks(String file1, String file2) {
        File f1 = new File(file1);
        File f2 = new File(file2);
        BufferedReader fr1 = null;
        BufferedReader fr2 = null;

        try {
            fr1 = new BufferedReader(new FileReader(f1));
            fr2 = new BufferedReader(new FileReader(f2));
            Iterator fileLineIter = fileLineIterator(fr1, fr2, cmp);
            int idx = 0;
            initValues();
            while (fileLineIter.hasNext()) {
                if (idx < maxLines) {
                    pna[idx++] = (PathNode) fileLineIter.next();
                } else {
                    write(pna, idx, MERGE_FILENAME, true);
                    idx = 0;
                    initValues();
                    pna[idx++] = (PathNode) fileLineIter.next();
                }
            }
            write(pna, idx, MERGE_FILENAME, true);

        } catch (FileNotFoundException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);

        } finally {
            try {
                fr1.close();
                fr2.close();
                File f3 = new File(MERGE_FILENAME);
                f1.delete();
                f2.delete();
                f3.renameTo(f1);
            } catch (IOException ex) {
                Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public <PathNode> Iterator<PathNode> fileLineIterator(final BufferedReader br1, final BufferedReader br2, final Comparator cmp) {
        return new Iterator<PathNode>() {

            StringTokenizer element = null;
            String line = null;
            String type = null;
            PathNode node = null;
            PathNode tmpNode1 = null;
            PathNode tmpNode2 = null;
            boolean file1End = false;
            boolean file2End = false;
            boolean file1LineReturned = true;
            boolean file2LineReturned = true;

            public boolean hasNext() {
                //Se o ficheiro1 não chegou ao fim
                if (!file1End) {
                    //Se a ultima linha retornada foi do ficheiro1
                    if (file1LineReturned) {
                        try {
                            line = br1.readLine();
                            if (line != null) {
                                element = new StringTokenizer(line, " ");
                                type = (String) element.nextElement();
                                tmpNode1 = (PathNode) setPathNode(element);
                            } else {
                                file1End = true;
                            }
                        } catch (IOException ex) {
                            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                }
                //Se o ficheiro2 não chegou ao fim
                if (!file2End) {
                    //Se a ultima linha retornada foi do ficheiro2
                    if (file2LineReturned) {
                        try {
                            line = br2.readLine();
                            if (line != null) {
                                element = new StringTokenizer(line, " ");
                                type = (String) element.nextElement();
                                tmpNode2 = (PathNode) setPathNode(element);
                            } else {
                                file2End = true;
                            }
                        } catch (IOException ex) {
                            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
                        }

                    }
                }

                //Processa a comparação e retorno.
                if (!file1End) {
                    if (!file2End) {
                        if (cmp.compare(tmpNode1, tmpNode2) < 1) {
                            node = tmpNode1;
                            file1LineReturned = true;
                            file2LineReturned = false;
                        } else {
                            node = tmpNode2;
                            file2LineReturned = true;
                            file1LineReturned = false;
                        }
                    } else {
                        node = tmpNode1;
                        file1LineReturned = true;
                        file2LineReturned = false;
                    }
                } else {
                    if (!file2End) {
                        node = tmpNode2;
                        file2LineReturned = true;
                        file1LineReturned = false;
                    } else {
                        return false;
                    }
                }
                return true;
            }

            public PathNode next() {
                if (node == null) {
                    throw new NoSuchElementException("No more lines to be read.");
                }
                PathNode p = node;
                node = null;
                return p;
            }

            public void remove() {
                throw new UnsupportedOperationException("Not supported yet.");
            }
        };
    }

    private void write(PathNode[] pn, int len, String outputFile, boolean merge) throws IOException {
        int lnNbr = 0;

        BufferedWriter fw = new BufferedWriter(new FileWriter(outputFile, merge));

        while (lnNbr < len) {
            fw.write(pn[lnNbr++].toString() + "\n");
        }
        fw.close();
    }

    private void mySort(int len) {
        //Arrays.sort(pna, 0, len, cmp);
        quicksort(0, len);
    }

    private void quicksort(int left, int right) {
        if (right > left) {
            int idx = partition(left, right);
            quicksort(idx + 1, right);
            quicksort(left, idx - 1);

        }
    }

    private int median(int left, int right) {
        int mid = (right - left) / 2;
        int idx;
        if (cmp.compare(pna[left], pna[mid]) < 0) {
            if (cmp.compare(pna[mid], pna[right]) < 0) {
                idx = mid;
            } else {
                idx = right;
            }
        } else {
            if (cmp.compare(pna[left], pna[right]) < 0) {
                idx = left;
            } else {
                if (cmp.compare(pna[mid], pna[right]) < 0) {
                    idx = right;
                } else {
                    idx = mid;
                }
            }
        }
        return idx;
    }

    private int partition(int left, int right) {
        int i, j;//i da esquerda para a direita, j ao contrário
        int x = median(left, right);
        exch(x, right);

        PathNode v = pna[right];
        i = left - 1;
        j = right;
        while (j > i) {
            while (less(pna[++i], v) && i < right);

            while (less(v, pna[--j]) && j > left);
            if (j == left) {
                break;
            }

            if (i >= j) {
                break;
            }
            exch(i, j);
        }
        exch(i, right);
        return i;
    }

    private boolean less(PathNode pn1, PathNode pn2) {
        return cmp.compare(pn1, pn2) <= 0;
    }

    private void exch(int pn1, int pn2) {
        PathNode pn3 = pna[pn1];
        pna[pn1] = pna[pn2];
        pna[pn2] = pn3;
    }

    public static void main(String[] args) {
        ShortestPath sp = new ShortestPath(new File(FILENAME), new orderPathByWeight());
        sp.separeChunks();
        sp.merge();
    }

    private static class PathNode implements Comparable<PathNode> {

        private char arc;
        private int tail;
        private int head;
        private int weight;

        public PathNode(char a, int t, int h, int w) {
            arc = a;
            tail = t;
            head = h;
            weight = w;
        }

        public int getHead() {
            return head;
        }

        public int getTail() {
            return tail;
        }

        public int getWeight() {
            return weight;
        }

        @Override
        public String toString() {
            return arc + " " + tail + " " + head + " " + weight;
        }

        public int compareTo(PathNode o) {
            return this.weight - o.weight;
        }
    }

    private static class orderPathByTail implements Comparator<PathNode> {

        public int compare(PathNode o1, PathNode o2) {
            return o1.getTail() - o2.getTail();
        }
    }

    private static class orderPathByHead implements Comparator<PathNode> {

        public int compare(PathNode o1, PathNode o2) {
            return o1.getHead() - o2.getHead();
        }
    }

    private static class orderPathByWeight implements Comparator<PathNode> {

        public int compare(PathNode node1, PathNode node2) {
            return node1.getWeight() - node2.getWeight();
        }
    }
}

