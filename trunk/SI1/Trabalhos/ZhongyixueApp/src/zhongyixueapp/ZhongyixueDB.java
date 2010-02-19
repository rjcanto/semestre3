/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package zhongyixueapp;

import java.awt.Frame;
import java.sql.*;
import java.util.Vector;
import javax.swing.JOptionPane; //For the error messages JOptionPane.

/**
 *
 * @author Canto
 */
public class ZhongyixueDB {

    private final String SQL_DRIVER = "sun.jdbc.odbc.JdbcOdbcDriver";
    private final String ODBC_SOURCE = "jdbc:odbc:Zhongyixue";

    private Connection con ;
    private Statement stmt = null;
    private ResultSet rs = null;
    private Vector cache = null ;
    int colCount;
    String[] headers;

    public ZhongyixueDB() {
        loadDatabase() ;
//      findPatient();
    }

    private void loadDatabase() {
        try {
            Class.forName(SQL_DRIVER);
            String url = ODBC_SOURCE ;
            
            con = DriverManager.getConnection(url);
            System.out.println("Connection Established Successfully");
        } catch (ClassNotFoundException e) {
            Frame errorFrame = new Frame();
            JOptionPane.showMessageDialog(errorFrame, "SQL Driver not found",
                    "Error", JOptionPane.ERROR_MESSAGE);
            System.exit(0);
       
        } catch (SQLException e) {
            Frame errorFrame = new Frame();
            JOptionPane.showMessageDialog(errorFrame, "ODBC Source not found",
                    "Error", JOptionPane.ERROR_MESSAGE);
            System.exit(0);
        }
    }

    protected void closeDatabase() {
        try {
            if (con != null)
                con.close();
        } catch (SQLException ex) {
            JOptionPane.showMessageDialog(new Frame(), "Database Closing Error",
                        "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    protected void insertPatient() throws SQLException {
        con.setAutoCommit(false) ;
        String cmdInsPessoa = "insert into "+
                "dbo.PESSOA(BI,NIF,nomePessoa,morada,telefone,idade,dataNasc)" +
                " values (?,?,?,?,?,?,?) ;" ;
        String cmdInsPaciente = "insert into " +
                "dbo.PACIENTE(BI,profissao,estadoCivil,declRespon,email,dataRegisto) " +
                "values (?,?,?,null,?,?);" ;
        PreparedStatement pstmt = con.prepareStatement(cmdInsPessoa ) ;
        String biString = JOptionPane.showInputDialog(null, "Insira número BI (máx. 10 car.)");
        pstmt.setString(1, biString);
        pstmt.setString(2, JOptionPane.showInputDialog(null, "Insira NIF (máx. 10 car.)"));
        pstmt.setString(3, JOptionPane.showInputDialog(null, "Insira Nome Paciente (máx. 50 car.)"));
        pstmt.setString(4, JOptionPane.showInputDialog(null, "Insira Morada (máx. 30 car.)"));
        pstmt.setString(5, JOptionPane.showInputDialog(null, "Insira Telefone (máx. 15 car.)"));
        pstmt.setByte(6, Byte.valueOf(JOptionPane.showInputDialog(null, "Insira Idade"))) ;
        /* Trying to use setDate but this driver doesn't allow
        java.sql.Date date = new Date(0) ;
        java.util.Date date = new Date(1970,3,21);
        java.sql.Date birthDate = new java.sql.Date(date.getTime());
        pstmt.setDate(7, date.valueOf("1972-2-23")) ;
         */
        pstmt.setString(7,JOptionPane.showInputDialog(null, "Insira Data Nascimento (AAAA-MM-DD)")) ;
        pstmt.executeUpdate() ;

        pstmt = con.prepareStatement(cmdInsPaciente) ;
        pstmt.setString(1, biString);
        pstmt.setString(2, JOptionPane.showInputDialog(null, "Insira Profissão (máx. 20 car.)"));
        pstmt.setString(3, JOptionPane.showInputDialog(null, "Insira Estado Civil (máx. 15 car.)"));
        pstmt.setString(4, JOptionPane.showInputDialog(null, "Insira Email (máx. 20 car.)"));
        pstmt.setString(5,JOptionPane.showInputDialog(null, "Insira Data de Registo (AAAA-MM-DD)")) ;

        pstmt.executeUpdate() ;
        con.commit() ;
        con.setAutoCommit(true);
            
    }

    protected void insertDoctor() throws SQLException {
        con.setAutoCommit(false) ;
        String cmdInsPessoa = "insert into "+
                "dbo.PESSOA(BI,NIF,nomePessoa,morada,telefone,idade,dataNasc)" +
                " values (?,?,?,?,?,?,?) ;" ;
        String cmdInsTerapeuta = "insert into " +
                "dbo.TERAPEUTA(BI,dataConclusao,emFuncoes) " +
                "values (?,?,?);" ;
        PreparedStatement pstmt = con.prepareStatement(cmdInsPessoa ) ;
        String biString = JOptionPane.showInputDialog(null, "Insira número BI (máx. 10 car.)");
        pstmt.setString(1, biString);
        pstmt.setString(2, JOptionPane.showInputDialog(null, "Insira NIF (máx. 10 car.)"));
        pstmt.setString(3, JOptionPane.showInputDialog(null, "Insira Nome Terapeuta (máx. 50 car.)"));
        pstmt.setString(4, JOptionPane.showInputDialog(null, "Insira Morada (máx. 30 car.)"));
        pstmt.setString(5, JOptionPane.showInputDialog(null, "Insira Telefone (máx. 15 car.)"));
        pstmt.setByte(6, Byte.valueOf(JOptionPane.showInputDialog(null, "Insira Idade"))) ;
        pstmt.setString(7,JOptionPane.showInputDialog(null, "Insira Data Nascimento (AAAA-MM-DD)")) ;
        pstmt.executeUpdate() ;

        pstmt = con.prepareStatement(cmdInsTerapeuta) ;
        pstmt.setString(1, biString);
        pstmt.setString(2, JOptionPane.showInputDialog(null, "Insira Data Conclusão Especialização (AAAA-MM-DD)"));
        pstmt.setBoolean(3, Boolean.valueOf(JOptionPane.showInputDialog(null, "Está em funcões? 'true' ou 'false'",true)));
        pstmt.executeUpdate() ;

        con.commit() ;
        con.setAutoCommit(true);
    }

    protected void insertSchedule( String biPaciente, String biTerapeuta ) throws SQLException {
        con.setAutoCommit(false) ;
        String cmdInsSchedule = "insert into "+
                "dbo.CONSULTA(BIPaciente,BITerapeuta, numConsulta, dataConsulta, relatorio)" +
                " values (?,?,?,?,?) ;" ;
        PreparedStatement pstmt = con.prepareStatement(cmdInsSchedule) ;
        pstmt.setString(1, biPaciente);
        pstmt.setString(2, biTerapeuta);
        pstmt.setInt(3, (Integer.parseInt(JOptionPane.showInputDialog(null, "Insira Numero de Consulta"))));
        pstmt.setString(4, JOptionPane.showInputDialog(null, "Insira Data da Consulta (AAAA-MM-DD)"));
        pstmt.setString(5, JOptionPane.showInputDialog(null, "Insira relatorio (máx. 500 car.)"));
        pstmt.executeUpdate() ;

        con.commit() ;
        con.setAutoCommit(true);
    }

//
//    private void findSchedule(){}
//
//    private void findTreatment(){}
//
//    private void findPatientChart(){}
//
//    private void findSpecialization(){}

    //TODO
    /*Necessário garantir que elimina em todas as tabelas referenciadas*/
    protected void removePatient(String bi) throws SQLException {
        con.setAutoCommit(false) ;
        String cmdDelPessoa = "DELETE FROM dbo.PESSOA WHERE BI=?" ;
        String cmdDelPaciente = "DELETE FROM dbo.PACIENTE WHERE BI=?" ;

        PreparedStatement pstmt = con.prepareStatement(cmdDelPaciente ) ;
        pstmt.setString(1, bi);
        pstmt.executeUpdate() ;

        pstmt = con.prepareStatement(cmdDelPessoa) ;
        pstmt.setString(1, bi);
        pstmt.executeUpdate() ;
        con.commit() ;
        con.setAutoCommit(true);
    }

    protected void retireDoctor(String bi) throws SQLException {
        con.setAutoCommit(false) ;

        String cmdUpdtDoctor = "UPDATE dbo.TERAPEUTA " +
                            "SET emFuncoes = 0" +
                            "WHERE BI=?" ;
        PreparedStatement pstmt = con.prepareStatement(cmdUpdtDoctor) ;
        pstmt.setString(1, bi);
        pstmt.executeUpdate() ;

        con.commit() ;
        con.setAutoCommit(true);
    }


//
//    private void removeSchedule(){}
//
//    private void removeTreatment(){}
//
//    private void removePatientChart(){}
//
//    private void removeSpecialization(){}

    protected Statement createStatement() throws SQLException {
            return con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_READ_ONLY) ;
    }

//    public void setQuery(String q) {
//        cache = new Vector();
//        try {
//            // Execute the query and store the result set and its metadata
//              ResultSet rs = stmt.executeQuery(q);
//              ResultSetMetaData meta = rs.getMetaData();
//              colCount = meta.getColumnCount();
//
//              // Now we must rebuild the headers array with the new column names
//              headers = new String[colCount];
//              for (int h = 1; h <= colCount; h++) {
//                headers[h - 1] = meta.getColumnName(h);
//              }
//
//              // and file the cache with the records from our query. This would
//              // not be
//              // practical if we were expecting a few million records in response
//              // to our
//              // query, but we aren't, so we can do this.
//            while (rs.next()) {
//                String[] record = new String[colCount];
//                for (int i = 0; i < colCount; i++) {
//                    record[i] = rs.getString(i + 1);
//                }
//                cache.addElement(record);
//            }
//            //fireTableChanged(null); // notify everyone that we have a new table.
//            return
//        } catch (Exception e) {
//            cache = new Vector(); // blank it out and keep going.
//            e.printStackTrace();
//        }
//    }




}
