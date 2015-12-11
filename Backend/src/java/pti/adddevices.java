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
@Path("/adddevices")
public class adddevices {
    
    @POST
    public String adddevice(@FormParam("user") String user, @FormParam("name") String name, @FormParam("type") int type, @FormParam("state") int state) {
        return Integer.toString($adddevice(user,name,type,state));
    }
    
    int $adddevice(String user, String name, int type, int state) {
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
            ResultSet rs = statement.executeQuery("select id as newID from devices order by id desc limit 1");
            int id = rs.getInt("newID");
            rs = statement.executeQuery("select id as userid from users where username = \""+ user +"\"");
            int userid = rs.getInt("userid");
            String update = "error";
            boolean activated = true;
            update = "INSERT INTO devices VALUES ('" +
                                    (id+1) + "','" +
                                    userid + "','" +
                                    name + "','" +
                                    activated + "','" +
                                    state + "','" +
                                    type + "');";
            System.out.println(update);
            statement.executeUpdate(update);
            connection.close();
            if (update.equals("error")) return 0;
            else return id+1;
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
