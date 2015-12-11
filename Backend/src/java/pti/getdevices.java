/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pti;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import javax.ejb.Stateless;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.QueryParam;

/**
 *
 * @author rio
 */

@Stateless
@Path("/getdevices")
public class getdevices {
    
    @GET
    public String getdevices(@QueryParam("username") String username, @QueryParam("password") String password) {
        return $getdevices(username, password);
    }
    
    String $getdevices(String username, String password) {
        String result = "-1 -1 -1 -1 -1";
        try {
            Class.forName("org.sqlite.JDBC");
        }
        catch (ClassNotFoundException e){
            System.err.println(e.getMessage());
        }
        Connection connection = null;
        try {
            connection = DriverManager.getConnection("jdbc:sqlite://home/pti/pti.sqlite");
            Statement statement = connection.createStatement();
            ResultSet rs = statement.executeQuery("select id as id from  users where username = \""+ username +"\" and  password = \""+ password +"\"");
            int userid = rs.getInt("id");
            if (userid > 0) {      //Si les credencials introduides coincideixen
                rs = statement.executeQuery("select id,description,activated,state,type from devices where userid = " + userid);
                while (rs.next()) {
                    if (result.equals("-1 -1 -1 -1 -1")) result = rs.getString("id") + " " + rs.getString("description") + " " + rs.getString("activated") + " " + rs.getString("state") + " " + rs.getString("type") + "\n";
                    else result += (rs.getString("id") + " " + rs.getString("description") + " " + rs.getString("activated") + " " + rs.getString("state") + " " + rs.getString("type") + "\n");
                }
            }
            else result = "0 0 0 0 0";
            connection.close();
            
        }
        catch(SQLException e) {
            System.err.println(e.getMessage());
        }
        finally {
            try {
                if (connection != null)
                    connection.close();
            }
            catch (SQLException e) {
                //Error en tancar la connexio
                System.err.println(e.getMessage());
            }
        }
        return result;
    }
    
    @POST
    public String getdevicespost(@FormParam("username") String username, @FormParam("password") String password) {
        return $getdevices(username, password);
    }
    
}
