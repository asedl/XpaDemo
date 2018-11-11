/**
 * 
 */
package com.magic.examples;

import java.io.IOException;

import javax.xml.transform.TransformerException;

import com.magic.examples.xml.XMLProcessor;

/**
 * @author Andreas
 *
 */
public class XPATest {
	
	public static int transformXml(String xmlfile, String xslfile, String outputfile) throws TransformerException, IOException {
		return XMLProcessor.transformWithXSL(xmlfile, xslfile, outputfile);
		
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
