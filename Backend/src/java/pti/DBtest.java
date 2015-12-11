package pti;

import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.ejb.Stateless;
import javax.ws.rs.*;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author david
 */

@Stateless
@Path("/DBtest")
public class DBtest {
    @GET
    public String hola (@QueryParam("user") String user) throws ClassNotFoundException {
        String returnable = "out";
        try {
            /*String JDBC_DRIVER = "com.mysql.jdbc.Driver";
            String DB_URL = "jdbc:mysql://fiberparty.upc.es:3306/pti";
            String USER = "pti";
            String PASS = "";*/
            
            Connection conn = null;
            Statement stmt = null;
            ResultSet rs = null;
            
            //Class.forName("com.mysql.jdbc.Driver");
            Class.forName("org.sqlite.JDBC");
            
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection("jdbc:sqlite://home/pti/pti.sqlite");
            
            System.out.println("Creating statement...");
            stmt = conn.createStatement();
            rs = stmt.executeQuery("Select count (*) as contador from users");
            
            returnable = Integer.toString(rs.getInt("contador"));
            
            rs.close();
            stmt.close();
            conn.close();
            
        } catch (SQLException ex) {
            Logger.getLogger(DBtest.class.getName()).log(Level.SEVERE, null, ex);
        }
        return returnable;
    }
}
