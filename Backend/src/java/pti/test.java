/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/
package pti;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.ejb.Stateless;
import javax.net.ssl.HttpsURLConnection;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.QueryParam;

/**
 *
 * @author riogemm.panopio
 */
@Stateless
@Path("/test")
public class test {
    
    @GET
    public String hola (@QueryParam("user") String user) {
        String returnable="vacio";
        try {
            String res = "Hola " + user;
            
            
            
            
           
            String url = "http://hers.no-ip.org/cgi-bin/sendOrder.py?deviceID=3&newstate="+user;
		
		URL obj = new URL(url);
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();

		// optional default is GET
		con.setRequestMethod("GET");

		//add request header
		//con.setRequestProperty("deviceID", "");

		int responseCode = con.getResponseCode();
		System.out.println("\nSending 'GET' request to URL : " + url);
		System.out.println("Response Code : " + responseCode);

		BufferedReader in = new BufferedReader(
		        new InputStreamReader(con.getInputStream()));
		String inputLine;
		StringBuffer response = new StringBuffer();

		while ((inputLine = in.readLine()) != null) {
			response.append(inputLine);
		}
		in.close();

		//print result
		returnable = response.toString();
            
            
            
            //POST QUE NO FUNCA
            /*
            String url = "http://hers.no-ip.org/cgi-bin/sendOrder.py";
		URL obj = new URL(url);
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();

		//add reuqest header
		con.setRequestMethod("POST");
		con.setRequestProperty("Accept-Language", "en-US,en;q=0.5");

		//String urlParameters = "deviceID="++"&newstate="+user;
		String urlParameters = "newstate="+user;
		// Send post request
		con.setDoOutput(true);
		DataOutputStream wr = new DataOutputStream(con.getOutputStream());
		wr.writeBytes(urlParameters);
		wr.flush();
		wr.close();

		int responseCode = con.getResponseCode();
		System.out.println("\nSending 'POST' request to URL : " + url);
		System.out.println("Post parameters : " + urlParameters);
		System.out.println("Response Code : " + responseCode);

		BufferedReader in = new BufferedReader(
		        new InputStreamReader(con.getInputStream()));
		String inputLine;
		StringBuffer response = new StringBuffer();

		while ((inputLine = in.readLine()) != null) {
			response.append(inputLine);
		}
		in.close();
		
		//print result
		returnable = response.toString();*/

	} catch (MalformedURLException ex) {
            Logger.getLogger(test.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(test.class.getName()).log(Level.SEVERE, null, ex);
        }
            
            
           /* String encodedQuery = URLEncoder.encode("", "UTF-8");
            String postData = "newstate="+user+ encodedQuery;
            //String postData = "deviceID=3&newstate="+user;//+ encodedQuery;
            
            // Connect to google.com
            URL url = new URL("http://hers.no-ip.org/cgi-bin/sendOrder.py");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            //connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
            connection.setRequestProperty("Content-Length",  String.valueOf(postData.length()));
            connection.setDoOutput(true);
            
            // Write data
            //DataOutputStream wr = new DataOutputStream(con.getOutputStream());
            OutputStream os = connection.getOutputStream();
            os.write(postData.getBytes());
            
            // Read response
            StringBuilder responseSB = new StringBuilder();
            BufferedReader br = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            
            String line;
            while ( (line = br.readLine()) != null){
                responseSB.append(line);
            }
            returnable = responseSB.toString();
            
            // Close streams
            br.close();
            os.close();*/
            
            /*String url = "http://hers.no-ip.org/file_test.html";
            HttpClient httpClient = new HttpClient();
            PostMethod postMethod = new PostMethod(url);
            postMethod.addParameter("Email", email);
            postMethod.addParameter("fname", fname);
            try {
            httpClient.executeMethod(postMethod);
            } catch (HttpException e) {
            e.printStackTrace();
            } catch (IOException e) {
            e.printStackTrace();
            }
            */
            //return res;
       
        return returnable;
    }
}