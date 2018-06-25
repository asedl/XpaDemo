
package org.apache.hello_world_soap_http.types;

import javax.xml.bind.annotation.XmlRegistry;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the org.apache.hello_world_soap_http.types package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {


    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: org.apache.hello_world_soap_http.types
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link GreetMe }
     * 
     */
    public GreetMe createGreetMe() {
        return new GreetMe();
    }

    /**
     * Create an instance of {@link GreetMeResponse }
     * 
     */
    public GreetMeResponse createGreetMeResponse() {
        return new GreetMeResponse();
    }

}
