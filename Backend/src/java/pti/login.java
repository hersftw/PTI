package pti;

/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.ejb.Stateless;
import javax.ws.rs.*;
/**
 *
 * @author david
 */

@Stateless
@Path("/login")
public class login {
    
    
    @GET
    public String login(@QueryParam("user") String user, @QueryParam("password") String password) {
        return $login(user, password);
    }
    
    String $login(String user, String password) {
        String token = null;
        
        
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        
        try {
            Class.forName("org.sqlite.JDBC");
            conn = DriverManager.getConnection("jdbc:sqlite://home/pti/pti.sqlite"); 
            stmt = conn.createStatement();
            int contador = 0;
            rs = stmt.executeQuery("Select count (*) as contador from users where username =\""+user+"\" and password = \""+password+"\";");
            while(rs.next()){
                //Retrieve by column name
                contador = rs.getInt("contador");
            }
                token = Integer.toString(contador);
                if (contador > 0) token = "ACCES PERMES";
                //token  = Integer.toString(rs.getInt("contador"));
            
        } catch (SQLException ex) {
            Logger.getLogger(login.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(login.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        // GENERATE NEW TOKEN WITH NEW VALIDITY
        
        return token;
    }
    
    @POST
    public String loginpost(@FormParam("user") String user, @FormParam("password") String password) {
        return $login(user, password);
    }
    
    
}