/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package zhongyixueapp;

import java.awt.Frame;
import java.sql.* ;
import java.util.Vector;
import javax.swing.JOptionPane;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author Canto
 */
public class ZhongyixueTableModel extends AbstractTableModel {

    Vector cache;
    int colCount;
    String[] headers;
    Statement statement;
    ResultSet rs;
    ZhongyixueDB db ;

    public ZhongyixueTableModel(ZhongyixueDB db) {
        cache = new Vector();
        this.db = db ;
    }

    public String getColumnName(int i) {
        return headers[i];
    }

    public int getColumnCount() {
        return colCount;
    }

    public int getRowCount() {
        return cache.size();
    }

    public Object getValueAt(int row, int col) {
        return ((String[]) cache.elementAt(row))[col];
    }

    public void cleanQuery() {
        try {
            if(rs != null)
                rs.close();
            if(statement != null)
                statement.close();
        } catch(SQLException e) {
            JOptionPane.showMessageDialog(new Frame(), "CleanQuery() error",
                        "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    public void setQuery(String q) throws SQLException {
        cache = new Vector();
    
        // Execute the query and store the result set and its metadata
        statement = db.createStatement() ;
        rs = statement.executeQuery(q);

        ResultSetMetaData meta = rs.getMetaData();
        colCount = meta.getColumnCount();

        // Now we must rebuild the headers array with the new column names
        headers = new String[colCount];
        for (int h = 1; h <= colCount; h++) {
            headers[h - 1] = meta.getColumnName(h);
        }
        while (rs.next()) {
            String[] record = new String[colCount];
            for (int i = 0; i < colCount; i++) {
                record[i] = rs.getString(i + 1);
            }
            cache.addElement(record);
        }
        fireTableChanged(null); // notify everyone that we have a new table.
        cleanQuery() ;
        
    }
}