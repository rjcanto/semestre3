package Serie1;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

/**
 * Primeira série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 */
public class Serie01E05 {

    public static final int TEST_START      = 500000;
    public static final int TEST_END        = 10000000;
    public static final int TEST_STEP       = 500000;
    public static final String PATH         ="report.txt";
    
    /**
     * 5. Considere o metodo
     * public static IntTriple getMaximumSubArray(int[] v)
     * que retorna o triplo (l; r; s), tal que (v; l; r) seja um subarray de v com maior valor para a soma dos seus
     * elementos e s seja o valor dessa soma. Sendo N a dimens~ao do array,
     *
     * 5.1. Realize uma implementacao usando um algoritmo com custo assimptotico (N2).
     * Sugestao: pesquisa exaustiva utilizando o metodo getMaximumSubArrayGivenIndex.
     *
     * 5.2. Realize uma implementacao usando um algoritmo com custo assimptotico (N logN).
     * Sugestao: divisao do problema em dois subproblemas e utilizacao do metodo getMaximumSubArrayGivenIndex.
     *
     * 5.3. Realize uma implementacao usando um algoritmo com custo assimptotico (N).
     * Sugestao: percurso linear usando as seguintes observacoes:
     *      - O primeiro e ultimo elemento do subarray solucao sao nao negativos.
     *      - Se o subarray (v; l; r) tem soma negativa, entao o subarray (v; l; r0), para qualquer r0 > r0, nao e solucao.
     *
     * Avalie experimentalmente as implementacoes anteriores.
     */
    

    public static IntTriple getMaximumSubArrayN2(int [] v){
        IntTriple result = new IntTriple();
        for (int i=0; i<v.length; ++i){
            IntTriple aux = Serie01E04.getMaximumSubArrayGivenIndex(v,i);
            if (aux.getSum() > result.getSum())
                result=aux;
        }
        return result;
    }

    public static IntTriple MaximumSubArrayNlogN(int [] v, int l, int r){
        IntTriple result = new IntTriple();
        IntTriple aux = new IntTriple();
        while(l<r){
            aux = Serie01E04.MaximunSubArrayIndexRight(v, r, l);
            if (aux.getSum() > result.getSum())
                result = aux;
            l++;
        }
        return result;
    }


    public static IntTriple getMaximumSubArrayNlogN(int [] v){
        return MaximumSubArrayNlogN(v,0,v.length-1);
    }

        public static IntTriple getMaximumSubArrayN(int [] v){
        int sum=0,sum_aux=0, idxl=0, idxr=0, idx_aux=0;
        for (int i=0; i<v.length; ++i){
            sum_aux+=v[i];
            if (sum_aux>sum){
                sum=sum_aux;
                idxl=idx_aux;
                idxr=i;
            } else {
                if (sum_aux<0){
                    idx_aux=i+1;
                    sum_aux=0;
                }
            }
        }
        return new IntTriple(idxl,idxr,sum);
    }

     public static void outputToFile(String pathnameOut, int[][] v) throws FileNotFoundException, IOException{
     //ficheiro de saida
     FileOutputStream fs = new FileOutputStream(pathnameOut);
     PrintWriter pw = new PrintWriter (fs);

     String str = null;
     boolean numeroFlag =false;

     pw.println("Size (N);N^2;N*LOG(N);N;");
     for(int i=0; i<v.length; ++i){
         for(int j=0;j<v[0].length;++j)
            pw.print(v[i][j] + ";");
         pw.print("\n");
     }
     pw.flush();
     pw.close();
     fs.close();
     }

     public static void random(int[] v){
         Random generator = new Random();
         for (int i=0; i<v.length; ++i)
             v[i]= generator.nextInt(100)-50;
     }
     
     public static void teste(int min, int max, int step){
         int[][] testResults = new int[(max-min)/step+1][4];
         int i=0,j=0;
         double init=0;
         double end=0;


         for (int n=min; n<=max; n+=step,++i){
            int[] testArray = new int[n];
            IntTriple result = new IntTriple();

            System.out.print("N="+n+" - ");
            testResults[i][j++]=n;
            random(testArray);

            if(n<50000){
               init=System.currentTimeMillis();
                   result=getMaximumSubArrayN2(testArray);
               end=System.currentTimeMillis();
               testResults[i][j++]=(int)((end-init));
            }
            result.print();
            if(n<50000){
                init=System.currentTimeMillis();
                    result=getMaximumSubArrayNlogN(testArray);
                end=System.currentTimeMillis();
                testResults[i][j++]=(int)((end-init));
            }
            result.print();

            init=System.currentTimeMillis();
               result=getMaximumSubArrayN(testArray);
            end=System.currentTimeMillis();
            testResults[i][j++]=(int)((end-init));
            result.print();
            System.out.println();
            
            j=0;
         }

         try {
            outputToFile(PATH, testResults);
        } catch (FileNotFoundException ex) {
            System.out.println(ex);
        } catch (IOException ex) {
            System.out.println(ex);
        }




     }
     public static void main(String[] args) {
//
//         int[] vector = {12, -2, -24, 26, -3, -17, -18, 20, 16, -10, 12, -2, 10, -15};
//
//         IntTriple temp = getMaximumSubArrayN(vector);
//         System.out.println(temp.getLeft() + " - " + temp.getRight() + " - " + temp.getSum());

         teste(TEST_START,TEST_END,TEST_STEP);



        
    }
    
}
