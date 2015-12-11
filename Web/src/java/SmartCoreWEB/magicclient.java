/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package SmartCoreWEB;

import javax.ws.rs.ClientErrorException;
import javax.ws.rs.client.Client;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.Form;

/**
 * Jersey REST client generated for REST resource:we [devicesstate]<br>
 * USAGE:
 * <pre>
 *        magicclient client = new magicclient();
 *        Object response = client.XXX(...);
 *        // do whatever with response
 *        client.close();
 * </pre>
 *
 * @author DEFIB
 */
public class magicclient {

    private WebTarget webTarget;
    private Client client;
    private static final String BASE_URI = "http://fiberparty.upc.es:8080/PTIRestBackend/webresources/";

    public magicclient() {
        client = javax.ws.rs.client.ClientBuilder.newClient();
        webTarget = client.target(BASE_URI).path("devicesstate");
    }

    /**
     * @param responseType Class representing the response
     * @param user form parameter
     * @param password form parameter
     * @param deviceID form parameter
     * @param newstate form parameter
     * @return response object (instance of responseType class)
     */
    public <T> T setdevicestate(Class<T> responseType, String user, String password, String deviceID, String newstate) throws ClientErrorException {
        String[] formParamNames = new String[]{"user", "password", "deviceID", "newstate"};
        String[] formParamValues = new String[]{user, password, deviceID, newstate};
        return webTarget.request(javax.ws.rs.core.MediaType.APPLICATION_FORM_URLENCODED).post(javax.ws.rs.client.Entity.form(getQueryOrFormParams(formParamNames, formParamValues)), responseType);
    }

    /**
     * @param responseType Class representing the response
     * @param user query parameter
     * @param password query parameter
     * @param deviceID query parameter
     * @return response object (instance of responseType class)
     */
    public <T> T getdevicestate(Class<T> responseType, String user, String password, String deviceID) throws ClientErrorException {
        String[] queryParamNames = new String[]{"user", "password", "deviceID"};
        String[] queryParamValues = new String[]{user, password, deviceID};
        ;
        javax.ws.rs.core.Form form = getQueryOrFormParams(queryParamNames, queryParamValues);
        javax.ws.rs.core.MultivaluedMap<String, String> map = form.asMap();
        for (java.util.Map.Entry<String, java.util.List<String>> entry : map.entrySet()) {
            java.util.List<String> list = entry.getValue();
            String[] values = list.toArray(new String[list.size()]);
            webTarget = webTarget.queryParam(entry.getKey(), (Object[]) values);
        }
        return webTarget.request().get(responseType);
    }

    private Form getQueryOrFormParams(String[] paramNames, String[] paramValues) {
        Form form = new javax.ws.rs.core.Form();
        for (int i = 0; i < paramNames.length; i++) {
            if (paramValues[i] != null) {
                form = form.param(paramNames[i], paramValues[i]);
            }
        }
        return form;
    }

    public void close() {
        client.close();
    }
    
}
