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
    private final int MAX_LINES = 10000;
    private File filename;
    private PathNode[] pna = new PathNode[MAX_LINES];
    private int lineNbrAll = 0;

    public ShortestPath(File filename) {
        this.filename = filename;
    }

    public void openFile() {
        BufferedReader fr;
        BufferedWriter fw;

        try {
            fr = new BufferedReader(new FileReader(filename));
            fw = new BufferedWriter(new FileWriter(filename + ".new"));

            read(fr);

            //mySort(pna, new orderPathByWeight());

            //write(fw);

            fw.close();
            fr.close();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void read(BufferedReader fr) throws IOException {
        StringTokenizer ups;
        String type ;
        String line;
        PathNode pn;
        int rowNbr=0;
        while ((line = fr.readLine()) !=  null  && (rowNbr < MAX_LINES)){
                ups = new StringTokenizer(line, " ");
                type= (String) ups.nextElement();

                //if (type.equals("a")) {

//                    int tail = Integer.parseInt((String) ups.nextElement());
//                    int head = Integer.parseInt((String) ups.nextElement());
//                    int weight = Integer.parseInt((String) ups.nextElement());
//                    pn = new PathNode('a', tail, head, weight);
//                    //pna[lineNbr++] = pn;

        }
    }

    private void write(BufferedWriter fw) throws IOException {
        int lnNbr = 0;
        while (lnNbr < MAX_LINES) {
            fw.append(pna[lnNbr++].toString() + "\n");
        }
    }

    private void mySort(PathNode[] p, Comparator<PathNode> cmp) {
        Arrays.sort(p, cmp);
    }

    public static void main(String[] args) {
        ShortestPath sp = new ShortestPath(new File(FILENAME));
        sp.openFile();
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
