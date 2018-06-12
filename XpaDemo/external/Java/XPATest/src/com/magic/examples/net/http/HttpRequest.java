package com.magic.examples.net.http;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;


public class HttpRequest {
	public String Get (String url) throws ClientProtocolException, IOException {
		String retstring = null;

		CloseableHttpClient httpclient = HttpClients.createDefault();
		HttpGet httpGet = new HttpGet(url);
		
		CloseableHttpResponse response = httpclient.execute(httpGet);

		// The underlying HTTP connection is still held by the response object
		// to allow the response content to be streamed directly from the network socket.
		// In order to ensure correct deallocation of system resources
		// the user MUST call CloseableHttpResponse#close() from a finally clause.
		// Please note that if response content is not fully consumed the underlying
		// connection cannot be safely re-used and will be shut down and discarded
		// by the connection manager. 
		try {
		    System.out.println(response.getStatusLine());
		    HttpEntity entity = response.getEntity();
		    // do something useful with the response body
		    // and ensure it is fully consumed

		    retstring = EntityUtils.toString(entity);		    
		    EntityUtils.consume(entity);
		    
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
		    try {
				response.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		return retstring;
    }		
	
	public String Post (String url, String body) throws ClientProtocolException, IOException {
		String respbody = null;

		CloseableHttpClient httpclient = HttpClients.createDefault();
		HttpPost httpPost = new HttpPost(url);

		List <NameValuePair> nvps = new ArrayList <NameValuePair>();
		nvps.add(new BasicNameValuePair("username", "vip"));
		nvps.add(new BasicNameValuePair("password", "secret"));
		httpPost.setEntity(new UrlEncodedFormEntity(nvps));
		
		CloseableHttpResponse response = httpclient.execute(httpPost);

		try {
		    System.out.println(response.getStatusLine());
		    HttpEntity entity = response.getEntity();
		    // do something useful with the response body
		    // and ensure it is fully consumed
		    
		    respbody = EntityUtils.toString(entity);		    
		    EntityUtils.consume(entity);
		} finally {
		    response.close();
		}		
		
		return respbody;		
	}
}
