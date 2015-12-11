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
import javax.ws.rs.POST;
import javax.ws.rs.Path;

/**
 *
 * @author rio
 */

@Stateless
@Path("/deletedevice")
public class deletedevice {
    
    @POST
    public String deletedevice(@FormParam("user") String user, @FormParam("name") String name, @FormParam("type") int type) {
        return Integer.toString($deletedevice(user,name,type));
    }
    
    int $deletedevice(String user, String name, int type) {
        int result = -1;
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
            ResultSet rs = statement.executeQuery("select id as userid from users where username = \""+ user +"\"");
            int userid = rs.getInt("userid");
            String update = "error";
            update = "DELETE FROM devices WHERE userid = \""+ userid +"\"" + " and description = \"" + name + "\"";
            System.out.println(update);
            statement.executeUpdate(update);
            connection.close();
            if (update.equals("error")) return 0;
            else return 1;
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
    
}
