package serie02;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
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
    private final String PATH="/home/masterzdran/Desktop/Link to ISEL/semestre3/AED/Series/Serie2/";
    private final String FILENAME=PATH+"USA-road-d.NY.gr";


    public void openFile(File filename){
        BufferedReader fr;
        BufferedWriter fw;

        try {
            fr = new BufferedReader(new FileReader(filename));
            String xpto=fr.readLine();
            StringTokenizer ups= new StringTokenizer(xpto, xpto)

            
        } catch (FileNotFoundException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(ShortestPath.class.getName()).log(Level.SEVERE, null, ex);
        }

        

    }

}
