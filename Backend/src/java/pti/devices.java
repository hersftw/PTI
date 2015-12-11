package pti;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.ejb.Stateless;
import javax.ws.rs.*;
/**
 *
 * @author david
 */

@Stateless
@Path("/devices")
public class devices {
    
    
    @GET
    public int[] getdevicesbyuser(@QueryParam("user") String user, @QueryParam("token") String token) {
        return $getdevicesbyuser(user, token);
    }

    int[] $getdevicesbyuser(String user, String token) {
       int[] returnable = {1,2,3};
        //Conect to DB
        /*DBConection db = null;
        ResultSet rs = db.conectexecute("Select count (*) as contador from users where username = "+user+" and token = "+token+";"); // Verificar la validesa del token
        try{
        while(rs.next()){
                //Retrieve by column name
                int result  = rs.getInt("contador");
            }
        } catch (SQLException ex) {
            Logger.getLogger(login.class.getName()).log(Level.SEVERE, null, ex);
        }*/
        return returnable;
    }
    
    
    @PUT
    public Integer setdevicestate(@FormParam("user") String user, @FormParam("token") String token, @FormParam("deviceID") Integer deviceID, @FormParam("state") Integer state) {
        return $setdevicestate(user, token, deviceID, state);
    }

    Integer $setdevicestate(String user, String token, Integer deviceID, Integer state) {
        
        //Conect to DB
         DBConection db = null;
        ResultSet rs = db.conectexecute("UPDATE devices d, users u SET d.state = "+state+" WHERE u.username = "+user+" and u.token = "+token+" and u.id = d.userid and d.id = "+deviceID+";"); // Verificar la validesa del token
        try{
        while(rs.next()){
                //Retrieve by column name
                int result  = rs.getInt("contador");
            }
        } catch (SQLException ex) {
            Logger.getLogger(login.class.getName()).log(Level.SEVERE, null, ex);
        }
        //Send to the raspberry the new state
        
        
        return state;
    }
    
}

/*CREATE TABLE users (
    id int NOT NULL PRIMARY KEY,
    username varchar(50) UNIQUE NOT NULL,
    password varchar(50) NOT NULL,
    token varchar(50),
    token_since timestamp,
    token_until timestamp,
    
)

CREATE TABLE devices(
    id int NOT NULL,
    userid int NOT NULL,
    description tinytext or text,
    activated bool,
    state int
)
*/