package com.magic.examples.net.http;

import static org.junit.Assert.*;

import java.io.IOException;

import org.apache.http.client.ClientProtocolException;
import org.junit.Test;

public class HttpRequestTest {

	@Test
	public void testTest() throws ClientProtocolException, IOException {
		HttpRequest httpRequest = new HttpRequest();		
		String response = httpRequest.Get("https://www.magicsoftware.com");
		System.out.println(response);
		
	}

}
