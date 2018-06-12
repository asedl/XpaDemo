using System.IO;
using System.Net;

String URI = Env.ScriptArgs[0];
String ResponseFile = Env.ScriptArgs[1];
String ResponseConsoleOutput = ResponseFile + ".console.out";

FileStream ostrmResponse;
FileStream ostrmConsole;
StreamWriter writerConsole;
StreamWriter writerResponse;
TextWriter oldOut = Console.Out;
try {
  ostrmConsole = new FileStream (ResponseConsoleOutput, FileMode.OpenOrCreate, FileAccess.Write);
  writerConsole = new StreamWriter (ostrmConsole);

  ostrmResponse = new FileStream (ResponseFile, FileMode.OpenOrCreate, FileAccess.Write);
  writerResponse = new StreamWriter (ostrmResponse);
}
catch (Exception e) {
  Console.WriteLine ("Cannot open file for writing: " + ResponseFile);
  Console.WriteLine (e.Message);
   throw new System.ArgumentException("invalid filename for response", "original");
 }

// Redirect Console output to a file
Console.SetOut(writerConsole);

Console.WriteLine ("Http Request");
Console.WriteLine ("Request (URI): " + URI);
Console.WriteLine ("Response (Body): " + ResponseFile);

// Fake IE ....
WebClient webClient = new WebClient();
webClient.Headers["User-Agent"] =
  "Mozilla/4.0 (Compatible; Windows NT 5.1; MSIE 6.0) " +
  "(compatible; MSIE 6.0; Windows NT 5.1; " +
  ".NET CLR 1.1.4322; .NET CLR 2.0.50727)";
try {
    // execute the GET request ....
    string ret = webClient.DownloadString(URI);
    // ret now contains the contents of the webpage
    Console.WriteLine("First 256 bytes of response: " + ret.Substring(0,265));

    writerResponse.Write(ret);
}
catch (WebException we) {
  // Log the status ...
  Console.WriteLine(we.Message + "\n" + we.Status.ToString());
}

catch (NotSupportedException ne) {
  // Log the exception message
  Console.WriteLine(ne.Message);
}

Console.SetOut (oldOut);
writerConsole.Close();
ostrmConsole.Close();
writerResponse.Close();
ostrmResponse.Close();
