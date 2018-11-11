using System;
using System.Net;

class Program
{
    static void Main()
    {
        // Create web client simulating IE6.
        using (WebClient client = new WebClient())
        {
            Console.WriteLine("Requesting ....");

            client.Headers["User-Agent"] =
                "Mozilla/4.0 (Compatible; Windows NT 5.1; MSIE 6.0) " +
                "(compatible; MSIE 6.0; Windows NT 5.1; " +
                ".NET CLR 1.1.4322; .NET CLR 2.0.50727)";

            // Download data.
            byte[] arr = client.DownloadData("http://www.magicsoftware.com/");

            // Write values.
            Console.WriteLine("--- WebClient result ---");
            Console.WriteLine(arr.Length);

			string download = Encoding.ASCII.GetString(arr);
			Console.WriteLine(download);
			
        }
    }
}