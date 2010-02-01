/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aedserie4;

/**
 *
 * @author nac
 */
public class Tarefa{
    final int id;
    final int deadLine;
    final int penalty;

    public Tarefa(int i, int d, int p){
        id=i;
        deadLine=d;
        penalty=p;
    }

    public void print(){
        System.out.print("ID: "+id+"\tDeadLine: "+deadLine+"\tPenalty: "+penalty+"\n");

    }

    public int compareTo(Tarefa t) {
        return penalty - t.penalty;
    }
}
