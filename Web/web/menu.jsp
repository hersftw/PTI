<%-- 
    Document   : menu
    Created on : 29-nov-2015, 22:25:00
    Author     : david
--%>

<%@page import="javax.servlet.http.HttpSession"%>
<%@page import="javax.servlet.http.*"%>
<%@page import="java.sql.*"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>

<%
    Class.forName("org.sqlite.JDBC");
    Connection connection = null;
    try {
        Thread.sleep(3000);                 //1000 milliseconds is one second.
    } catch(InterruptedException ex) {
        Thread.currentThread().interrupt();
    }
    //connection = DriverManager.getConnection("jdbc:sqlite:C:/Users/DEFIB/Desktop/pti.sqlite");
    connection = DriverManager.getConnection("jdbc:sqlite://home/pti/pti.sqlite");
    //connection = DriverManager.getConnection("jdbc:sqlite:C:/Users/david/Desktop/pti.sqlite");
    Statement statement = connection.createStatement();
        
    %>



<html>
    <head>
        <title>Administració de dispositius</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" type="text/css" href="magiccss.css">
    </head>
    <body>
        <div class="supermagicbox">
            <h1>Smart Core</h1>
            <hr>       
            <form action="menu" method="post">
                <label id="text">Bombeta menjador:</label><%
                     ResultSet rs = statement.executeQuery("select state from devices where userid = 1 and id = 3;");
                     int state = -3;
                    while(rs.next()){
                        state = rs.getInt("state");
                    }
                    if (state == 0) out.print("<label id=\"off\">OFF</label>");
                    else if (state == 1) out.print("<label id=\"on\">ON</label>");
                    else if (state == 2) out.print("<label id=\"auto\">Auto</label>");
             %>
                <select name=newstate>
                            <option selected VALUE=0> Off</option>
                            <option selected VALUE=1> On</option>
                            <option selected VALUE=2> Auto</option>
                  
                <input name="3" type="submit" value="Canviar estat">
            </form>
        
      
            <form action="menu" method="post">
                <label id="text">Bombeta terrassa:</label><%
                     rs = statement.executeQuery("select state from devices where userid = 1 and id = 4;");
                     state = -3;
                    while(rs.next()){
                        state = rs.getInt("state");
                    }
                    if (state == 0) out.print("<label id=\"off\">OFF</label>");
                    else if (state == 1) out.print("<label id=\"on\">ON</label>");
                    else if (state == 2) out.print("<label id=\"auto\">Auto</label>");
             %>
                <select name=newstate>
                            <option selected VALUE=0> Off</option>
                            <option selected VALUE=1> On</option>
                            <option selected VALUE=2> Auto</option>
                
                <input name="4" type="submit" value="Canviar estat">
            </form>
       
            <form action="menu" method="post">
                <label id="text">Alarma:</label><%
                     rs = statement.executeQuery("select state from devices where userid = 1 and id = 5;");
                     state = -3;
                    while(rs.next()){
                        state = rs.getInt("state");
                    }
                    if (state == 0) out.print("<label id=\"off\">OFF</label>");
                    else if (state == 1) out.print("<label id=\"on\">ON</label>");
             %>
             <select name=newstate>
                            <option selected VALUE=0> Off</option>
                            <option selected VALUE=1> On</option>
                <input name="5" type="submit" value="Canviar estat">
            </form>
            <form action="menu" method="post">
                <label id="text">Temperatura:</label><%
                     rs = statement.executeQuery("select state from devices where userid = 1 and id = 2;");
                     state = -3;
                    while(rs.next()){
                        out.print(Integer.toString(rs.getInt("state"))+"ºC");
                    }
             %>
            </form>
            <br>
            <br>
<form action="logout" method="post">
    <center><input name="logout" type="submit" value="Desconecta't"></center>
</div>
</form>
</body>
</html>