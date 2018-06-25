using System;
using System.IO;
using System.Net;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace XpaTHttpDNet
{
    public class XpaTHttpDNet
    {
        public static int Post(string endpoint, string soapaction, string headers, string reqfile, string responsefile, string certfile, string certpasswd) {

            ServicePointManager.Expect100Continue = true;
            ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;

            String strSOAPRequest = "";
            if (File.Exists(reqfile)) {
                strSOAPRequest = File.ReadAllText(reqfile, Encoding.UTF8);
            }

            HttpWebRequest objRequest = (HttpWebRequest) WebRequest.Create(endpoint);
            objRequest.Method = "POST";
            objRequest.ContentLength = strSOAPRequest.Length;
            objRequest.ContentType = "text/xml;charset=UTF-8";
            if (!String.IsNullOrEmpty(soapaction)) {
                objRequest.Headers.Add(soapaction);
            }
            X509Certificate2 cert = new X509Certificate2 (certfile, certpasswd);
            objRequest.ClientCertificates.Add(cert);

            // TODO: When called from Magic the server certificate is not accepted
            // It's installed and works fine when testing from outside Magic (unit tests or command line test program)
            // Probably has to do with .NET framework version. For now we ALWWAYS accept the server's certificate
            objRequest.ServerCertificateValidationCallback +=
                new RemoteCertificateValidationCallback((sender, certificate, chain, policyErrors) => {
                    return true; });

            StreamWriter myWriter = null;
            try
            {
                myWriter = new StreamWriter(objRequest.GetRequestStream());
                myWriter.Write(strSOAPRequest);
            }
            catch (WebException we) {
                throw we;
            }
            catch (Exception e)
            {
            }
            finally
            {
                if (myWriter != null)
                    myWriter.Close();
            }

            HttpWebResponse objResponse = (HttpWebResponse) objRequest.GetResponse();
            using (StreamReader sr = new StreamReader(objResponse.GetResponseStream())) {
                using (System.IO.FileStream fs = new System.IO.FileStream(responsefile, FileMode.Create)) {
                    using (StreamWriter sw = new StreamWriter(fs, Encoding.UTF8)) {
                        sw.Write(sr.ReadToEnd());
                        sw.Close();
                    }
                    fs.Close();
                }
                sr.Close();
            }
            return 0;
        }

        private static X509Certificate2 GetCertificateFromStore(string certName)
        {

            X509Store store = new X509Store("MY", StoreLocation.CurrentUser);

            try
            {
                store.Open(OpenFlags.ReadOnly | OpenFlags.OpenExistingOnly);

                // Place all certificates in an X509Certificate2Collection object.
                X509Certificate2Collection collection = (X509Certificate2Collection) store.Certificates;

                // If using a certificate with a trusted root you do not need to FindByTimeValid, instead:
                // currentCerts.Find(X509FindType.FindBySubjectDistinguishedName, certName, true);
                X509Certificate2Collection fcollection = 
                    (X509Certificate2Collection) collection.Find(X509FindType.FindBySubjectDistinguishedName, certName, false);
                if (fcollection.Count == 0)
                    return null;
                // Return the first certificate in the collection, has the right name and is current.
                return fcollection[0];
            }
            finally
            {
                store.Close();
            }

        }
    }
}
