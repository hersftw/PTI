/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.netbeans.rest.application.config;

import java.util.Set;
import javax.ws.rs.core.Application;

/**
 *
 * @author riogemm.panopio
 */
@javax.ws.rs.ApplicationPath("webresources")
public class ApplicationConfig extends Application {

    @Override
    public Set<Class<?>> getClasses() {
        Set<Class<?>> resources = new java.util.HashSet<>();
        addRestResourceClasses(resources);
        return resources;
    }

    /**
     * Do not modify addRestResourceClasses() method.
     * It is automatically populated with
     * all resources defined in the project.
     * If required, comment out calling this method in getClasses().
     */
    private void addRestResourceClasses(Set<Class<?>> resources) {
        resources.add(pti.DBtest.class);
        resources.add(pti.adddevices.class);
        resources.add(pti.deletedevice.class);
        resources.add(pti.devices.class);
        resources.add(pti.devicesstate.class);
        resources.add(pti.devicesstatepi.class);
        resources.add(pti.getdevices.class);
        resources.add(pti.login.class);
        resources.add(pti.test.class);
    }
    
}
