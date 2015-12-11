/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/
package SmartCoreWEB;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Enumeration;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 *
 * @author DEFIB
 */
@WebServlet(name = "menu", urlPatterns = {"/menu"})
public class menu extends HttpServlet {
    
    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            /* TODO output your page here. You may use following sample code. */
            /*out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet menu</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Servlet menu at " + request.getContextPath() + "</h1>");
            out.println("</body>");
            out.println("</html>");*/
            HttpSession session = request.getSession(false);
            String device = null;
            try {
                // If you are not in a session - you are not logged in
                if (session == null) {
                    out.println("<p>No s'ha trobat cap sessió</p>");
                    RequestDispatcher rd = request.getRequestDispatcher("index.html");
                    rd.include(request, response);
                } else {
                    //out.println("<p>PENIS</p>");
                    if(request.getParameter("1") != null) device = "1";
                    else if(request.getParameter("2") != null) device = "2";
                    else if(request.getParameter("3") != null) device = "3";
                    else if(request.getParameter("4") != null) device = "4";
                    else if(request.getParameter("5") != null) device = "5";
                    //out.println("<p>PENIS2</p>");
                    magicclient client = new magicclient();       
                    
                    response.sendRedirect("menu.jsp");
                    
                    client.setdevicestate(Integer.class, "pti", "pti", device, request.getParameter("newstate"));
                    //out.println("<p>"+Integer.toString(fuckU)+"</p>");
                    /*out.println("Thank you, you are already logged in");
                    out.println("Here is the data in your session");
                    Enumeration names = session.getAttributeNames();
                    while (names.hasMoreElements()) {
                    String name = (String) names.nextElement();
                    Object value = session.getAttribute(name);
                    out.println("<p>name=" + name + " value=" + value + "</p>");
                    }*/
                    
                    
                    
                    
                    /*RequestDispatcher rd = request.getRequestDispatcher("menu.jsp");
                    rd.include(request, response);*/
                }
                // Write html for a new login
                
                out.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
            
        }
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
        processRequest(request, response);
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
        processRequest(request, response);
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
