/**
 * 
 */
package com.magic.examples.xml;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.StringWriter;
import java.util.Arrays;

import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import joptsimple.OptionParser;
import joptsimple.OptionSet;
import net.sf.saxon.TransformerFactoryImpl;

/**
 * @author Andreas
 *
 */
public class XMLProcessor {
	
	private static final  Logger log = LogManager.getLogger(XMLProcessor.class.getName());
	
	final static OptionParser optionParser = new OptionParser();  
	final static String[] fileOptions = {"xml", "xmlfile"};  
	final static String[] xslOptions = {"xsl", "xslfile"};  
	final static String[] outfileOptions = {"o", "outfile"};  
	final static String[] verboseOptions = {"v", "verbose"};  
	final static String[] helpOptions = {"h", "help"};  
		
	public static int transformWithXSL (String xmlfile, String xslfile, String outputfile) throws TransformerException, IOException {
		
		log.debug (XMLProcessor.class.getName());
		log.debug("xmlfile: " + xmlfile );
		log.debug("xslfile: " + xslfile );
		log.debug("outputfile: " + outputfile );
		
		File xsltFile = new File(xslfile);
	    File inputXml = new File(xmlfile);

	    Source xmlSource = new javax.xml.transform.stream.StreamSource(inputXml);
	    Source xsltSource = new javax.xml.transform.stream.StreamSource(xsltFile);
	    StringWriter sw = new StringWriter();

	    Result result = new javax.xml.transform.stream.StreamResult(sw);

	    TransformerFactory transFact = new TransformerFactoryImpl();
	    Transformer trans = null;
		try {
			trans = transFact.newTransformer(xsltSource);
		    trans.transform(xmlSource, result);
		} catch (TransformerConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	    	    
	    File file = new File(outputfile);
	    new File(file.getParent()).mkdir();
	    FileWriter output = new FileWriter(file);
	    output.write(sw.toString());
	    output.close();
		
		return -1;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		optionParser.acceptsAll(Arrays.asList(fileOptions), "Path and name of xml file.").withRequiredArg().required();  	
		optionParser.acceptsAll(Arrays.asList(xslOptions), "Path and name of xsl file.").withRequiredArg().required();  	
		optionParser.acceptsAll(Arrays.asList(outfileOptions), "Path and name of outputfile.").withRequiredArg().required();  	
		optionParser.acceptsAll(Arrays.asList(verboseOptions), "Verbose logging.");  
		optionParser.acceptsAll(Arrays.asList(helpOptions), "Display help/usage information").forHelp();  
		final OptionSet options = optionParser.parse(args);
		
		try {
			int result =
					transformWithXSL (args[0], args[1], args[2]);
		} catch (TransformerException | IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
