# OWCLN001_xpatest_uris

  Menu: Http/HttpGet(Examples)
  
  This is an online (line mode) browse program for sampledatabase table DatabaseComponent.xpatest_uris. xpatest_uris does contain some sample URLs / URIs which are persisted there because they are nice for testing.

  In the browse screen which gets opened when you start the program there's then (plenty) of buttons which allow to perform some actions on the URIs.  

  
## Buttons / Events
### Get(Magic)
Invokes program BWCLN001_HttpGet(Magic) to perform a Http GET operation on the currently selected URL by means of Magic's built-in HTTPCall() function. That in turn will produce two files which will be written to the applications temp directory:
* a file with the payload (body) of the HTTP server response
* a file with the headers from the message returned from the http server 

### Get(Apache)
Invokes program BWCLN002_HttpGet (Apache) with the currently selected URL as parameter. This program will perform a Http GET request by means of Apache HttpClient library which is wrapped in our Java class com.magic.examples.HttpRequest

  Currently this library does only return the http response body as a Blob. If an error occurs it will throw a Java exception - which is caught in BWCLN002_HttpGet, currently however not handled at all.

  The result (message body) of the Http request will be written to the applications temp directory

### Get(cURL)
Invokes program BWCLN001_HttpGet(cURL) with the currently selected URL as parameter. This program will perform a Http GET request on that URL by a CURL request from command line. BWCLN001_HttpGet(cURL) will produce three files in the applications temp directory:  
* a file with the payload (body) of the http server's response
* a file with the headers from the http server's response
* a file with the trace (console output) of the CURL command

See also docs of BWCLN001_HttpGet(cURL) and CURL for additional information like available configuration settings for CURL, ...

### Get(Magic/C#)
Invokes program BWCLN004_HttpGet(Magic .NET) with the currently selected URL as parameter. This program will perform a Http GET request on that URL by means of embedded (snippet) C# code and return the response as a Blob. Finally will produce:  
* a file with the payload (body) of the http server's response

### Get(Magic/C#/Async)
Invokes program BWCLN004_HttpGet(async) with the currently selected URL as parameter. This program will perform a Http GET request on that URL by means of embedded  asynchronous C# code. The program is started in a parallel context and control will return immediately to OWCLN001_xpatest_uris. BWCLN004_HttpGet(async) will raise a global event when it's done - which needs to be handled.

Note: That's basically "async(magic) + async(c#)" and overkill but it's just a sample. See doc of BWCLN004_HttpGet(async) for further details regarding asynchronouus http request and how its implemented there.

### Get(C# script)
Invokes program BWCLN210_ExeScript_csscript with the currently selected URL as a parameter. BWCLN210_ExeScript_csscript is part of the XPATEST scripting framework and it will load C# code from a template which gets compiled and executed in order to perform (finally) the Http request.

## Display of response
What we do get back from the http server (if anything) is displayed in the multiline text box on the right side of the URL table. Immediately after program OUTIL100_EmbeddedBrowser gets invoked which implements an embedded webbrowser in order to display the content of the response file (from disk). It response is anything it can render, it will display it nicely.
 
## Files
In this test program we write the results of the Http Requests to files in the applications temp directory %XPATEST_HOME%temp\ . Goal is to always have three files, which can be analyzed (or used) when the request is finished:
1. a file with the body (payload) of the http server's response
2. a file with the http headers of the http server's response
3. a file with log information (specific to chosen implementation) 

Currently not all of the methods we implemented for Http Requests do always produce the "full" set of these three files.

## Known issues
There's plenty of issues with this program resp. the implementations for Http GET which get called if you press one of the HttpGet buttons. Main issue is that the headers of the http server response do not get evaluated so the programs do actually neither check what the content-type of the response is, nor what the encoding is. This raises issues if the content-type is different from text/html and (Unicode issues) if the content encoding is different from UTF-8

