package pti;




import java.sql.*;

/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/**
 *
 * @author david
 */
public class DBConection {
    //static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    //static final String DB_URL = "jdbc:mysql://mysqlfib.fib.upc.es";
    //static final String DB_URL = "jdbc:sqlite:C:\\Users\\Rio\\Dropbox\\UPC\\AD\\P2\\datasqlite3.db";
    
    //  Database credentials
//    static final String USER = "pti02";
//    static final String PASS = "BDpti02";
    //static final String USER = "pti";
    //static final String PASS = "ungaterasmus";
    
    public ResultSet conectexecute(String sqlquery){
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        try{
            //Register JDBC driver
            Class.forName("org.sqlite.JDBC");
            
            //Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection("jdbc:sqlite:C:\\Users\\david\\Desktop\\pti.sqlite");
            
            //Execute a query
            System.out.println("Creating statement...");
            stmt = conn.createStatement();
            rs = stmt.executeQuery(sqlquery);
                        
            //Clean-up environment
            rs.close();
            stmt.close();
            conn.close();
            
            return rs;
        }catch(SQLException se){
            //Handle errors for JDBC
            se.printStackTrace();
        }catch(Exception e){
            //Handle errors for Class.forName
            e.printStackTrace();
        }finally{
            //finally block used to close resources
            try{
                if(stmt!=null)
                    stmt.close();
            }catch(SQLException se2){
            }// nothing we can do
            try{
                if(conn!=null)
                    conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }//end finally try
        }//end try
        System.out.println("Conecció a DB tancada");
        return rs;
    }//end main
}
