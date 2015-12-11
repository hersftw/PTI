package SmartCoreWEB;

/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/


import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;
import java.util.Enumeration;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.RequestDispatcher;
import javax.servlet.http.HttpSession;

/**
 *
 * @author david.molins.goma
 */
@WebServlet(urlPatterns = {"/login"})
public class login extends HttpServlet {
    
    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     * @throws java.lang.ClassNotFoundException
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException, ClassNotFoundException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        /* TODO output your page here. You may use following sample code. */
        //out.println("<p>test</p>");
        String token = null;
        
        
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        
        try {
            Class.forName("org.sqlite.JDBC");
            //conn = DriverManager.getConnection("jdbc:sqlite:C:/Users/david/Desktop/pti.sqlite");
            conn = DriverManager.getConnection("jdbc:sqlite://home/pti/pti.sqlite");
            stmt = conn.createStatement();
            int contador = 0;
            //out.println("<p>aqui?</p>");
            rs = stmt.executeQuery("Select count (*) as contador from users where username =\""+request.getParameter("user")+"\" and password = \""+request.getParameter("password")+"\";");
            while(rs.next()){
                //Retrieve by column name
                contador = rs.getInt("contador");
                //out.println("<p>"+Integer.toString(contador)+"</p>");
            }
            token = Integer.toString(contador);
            if (contador > 0) {
                out.println("<p>ACCES PERMES</p>");
                HttpSession session = request.getSession(true);
                // Set some attribute values to the session
                // In this case user and password from the request and client
                session.setAttribute("username", request.getParameter("user"));
                session.setAttribute("password", request.getParameter("password"));
                RequestDispatcher rd = request.getRequestDispatcher("menu.jsp");
                rd.include(request, response);
                
                /*Enumeration names = session.getAttributeNames();
                while (names.hasMoreElements()) {
                    String name = (String) names.nextElement();
                    Object value = session.getAttribute(name);
                    out.println("<p>name=" + name + " value=" + value + "</p>");
                }*/
                
            }
            else{
                out.println("<p> usuari o password incorrectes </p>");
                RequestDispatcher rd = request.getRequestDispatcher("index.html");
                rd.include(request, response);
            }
            //token  = Integer.toString(rs.getInt("contador"));
            conn.close();
        } catch (SQLException ex) {
            Logger.getLogger(login.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(login.class.getName()).log(Level.SEVERE, null, ex);
        }finally {
            try {
                if(conn != null)
                    conn.close();
            }
            catch(SQLException e) {
                //Error en tancar la connexio
                System.err.println(e.getMessage());
            }
        }
        
        /*RequestDispatcher rd = request.getRequestDispatcher("index.html")
        Class.forName("org.sqlite.JDBC");
        out.println("<h1>TEST</h1>");
        
        WebTarget webTarget;
        Client client;
        String BASE_URI = "http://fiberparty.upc.es:8080/PTIRestBackend/webresources";
        client = javax.ws.rs.client.ClientBuilder.newClient();
        webTarget = client.target(BASE_URI).path("login");
        
        Form form = new Form();
        form.param("user", "foo");
        form.param("password", "bar");
        webTarget.request().post(Entity.entity(form, URLEncoder.encode("", "UTF-8")), String.class);
        
        out.println(webTarget);*/
        /*if("1".equals(Integer.parseInt(responseSB.toString()))) {      //Si les credencials introduides coincideixen
        out.println("<p><h3><font color=#347C2C> Hola! El teu login ha sigut un exit. </font></h3><p>");
        RequestDispatcher rd = request.getRequestDispatcher("menu.html");
        rd.include(request, response);
        }
        else {
        out.println("<p><h3><font color=#F70D1A> Usuari i/o password introduit/s incorrecte/s. Torni a intentar-ho. </font></h3><p><br>");
        RequestDispatcher rd = request.getRequestDispatcher("index.html");
        rd.include(request, response);
        }
        */
        
    }
    
    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            System.out.println("<p>get</p>");
            processRequest(request, response);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(login.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            System.out.println("<p>post</p>");
            processRequest(request, response);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(login.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>
    
    
    
}