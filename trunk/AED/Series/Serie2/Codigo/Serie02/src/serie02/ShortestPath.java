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
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.StringTokenizer;

/**
 * Grupo:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 */
public class ShortestPath {

    private static final String PATH = "D:/ISEL/Trabalhos/AED/Series/Serie2/";
    private static final String FILENAME = PATH + "USA-road-d.NY.gr";
    private final int MAX_LINES = 100000;
    private File filename;
    private PathNode[] pna;
    private int nbrFiles = 0;

    public ShortestPath(File filename) {
        this.filename = filename;
        initValues();
    }

    public void initValues() {
        pna = null;
        pna = new PathNode[MAX_LINES];
    }

    public int separeChunks() {
        BufferedReader fr = null;
        StringTokenizer element = null;
        String type = null;
        String line = null;
        int rowNbr = 0;
        pna = new PathNode[MAX_LINES];
        try {

            fr = new BufferedReader(new FileReader(filename));
            while ((line = fr.readLine()) != null) {
                element = new StringTokenizer(line, " ");
                type = (String) element.nextElement();

                if (type.equals("a") && (rowNbr < MAX_LINES)) {
                    pna[rowNbr++] = setPathNode(element);
                } else if (rowNbr == MAX_LINES) {
                    mySort(pna, rowNbr, new orderPathByWeight());
                    write(pna, rowNbr,filename + "." + nbrFiles++);
                    initValues();
                    rowNbr = 0;
                }
            }
            if (rowNbr > 0 && rowNbr < MAX_LINES) {
                mySort(pna, rowNbr, new orderPathByWeight());
                write(pna, rowNbr,filename + "." + nbrFiles++);
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

    public void mergeTwoChunks(String file1, String file2) {
        BufferedReader fr1 = null;
        BufferedReader fr2 = null;
        StringTokenizer element1 = null;
        StringTokenizer element2 = null;
        String type = null;
        String line1 = null;
        String line2 = null;

        try {
            fr1 = new BufferedReader(new FileReader(file1));
            fr2 = new BufferedReader(new FileReader(file2));
            int rowNbr = 0;
            boolean lf1 = false;
            boolean lf2 = false;
            boolean f1end=false;
            boolean f2end=false;
            PathNode pn1 = null;
            PathNode pn2 = null;
            initValues();
            while (!(f1end && f2end)) {
                if (!lf1) {
                    line1 = fr1.readLine();
                    if (line1 == null){
                        f1end=true;
                        //processa resto do outro ficheiro se o mesmo não tiver acabado
                    }
                    element1 = new StringTokenizer(line1, " ");
                    type = (String) element1.nextElement();
                    pn1 = setPathNode(element1);
                    lf1=true;
                }
                if (!lf2) {
                    line2 = fr2.readLine();
                    if (line2 == null){
                        f2end=true;
                        //processa resto do outro ficheirose o mesmo não tiver acabado
                    }
                    element2 = new StringTokenizer(line2, " ");
                    type = (String) element2.nextElement();
                    pn2 = setPathNode(element2);
                    lf2=true;
                }
                if (pn1.getWeight() <= pn2.getWeight()){
                    pna[rowNbr++]=pn1;
                    lf1=false;
                }else{
                    pna[rowNbr++]=pn2;
                    lf2=false;
                }
                if (rowNbr==MAX_LINES){
                    write(pna, rowNbr,filename + ".merged." + nbrFiles/2);
                    rowNbr=0;
                    
                }
            }
        } catch (FileNotFoundException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);

        } finally {
            try {
                fr1.close();
                fr2.close();
            } catch (IOException ex) {
                Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

    }

    private void processFile(BufferedReader bf){
        
    }

    private void read(BufferedReader fr) throws IOException {
    }

    private void write(PathNode[] pn, int len, String outputFile) throws IOException {
        int lnNbr = 0;

        BufferedWriter fw = new BufferedWriter(new FileWriter(outputFile));

        while (lnNbr < len) {
            fw.write(pn[lnNbr++].toString() + "\n");
        }
        fw.close();
    }

    private void mySort(PathNode[] p, int len, Comparator<PathNode> cmp) {
        Arrays.sort(p, 0, len, cmp);
    }

    public static void main(String[] args) {
        ShortestPath sp = new ShortestPath(new File(FILENAME));
        sp.separeChunks();
        sp.mergeTwoChunks(PATH + "USA-road-d.NY.gr.0", PATH + "USA-road-d.NY.gr.1");
    }
}

class PathNode implements Comparable<PathNode> {

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

class orderPathByTail implements Comparator<PathNode> {

    public int compare(PathNode o1, PathNode o2) {
        return o1.getTail() - o2.getTail();
    }
}

class orderPathByHead implements Comparator<PathNode> {

    public int compare(PathNode o1, PathNode o2) {
        return o1.getHead() - o2.getHead();
    }
}

class orderPathByWeight implements Comparator<PathNode> {

    public int compare(PathNode o1, PathNode o2) {
        return o1.getWeight() - o2.getWeight();
    }
}
