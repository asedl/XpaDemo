using System;
using System.IO;
using System.Net;
using System.Net.Http;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

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

    // Class that contains the data for
    // the alarm event. Derives from System.EventArgs.
    //
    public class AlarmEventArgs : EventArgs
    {
        private bool snoozePressed;
        private int nrings;

        //Constructor.
        //
        public AlarmEventArgs(bool snoozePressed, int nrings)
        {
            this.snoozePressed = snoozePressed;
            this.nrings = nrings;
        }

        // The NumRings property returns the number of rings
        // that the alarm clock has sounded when the alarm event
        // is generated.
        //
        public int NumRings
        {
            get { return nrings; }
        }

        // The SnoozePressed property indicates whether the snooze
        // button is pressed on the alarm when the alarm event is generated.
        //
        public bool SnoozePressed
        {
            get { return snoozePressed; }
        }

        // The AlarmText property that contains the wake-up message.
        //
        public string AlarmText
        {
            get
            {
                if (snoozePressed)
                {
                    return ("Wake Up!!! Snooze time is over.");
                }
                else
                {
                    return ("Wake Up!");
                }
            }
        }
    }

    // Delegate declaration.
    //
    public delegate void AlarmEventHandler(object sender, AlarmEventArgs e);

    // The Alarm class that raises the alarm event.
    //
    public class AlarmClock
    {
        private bool snoozePressed = false;
        private int nrings = 0;
        private bool stop = false;

        // The Stop property indicates whether the
        // alarm should be turned off.
        //
        public bool Stop
        {
            get { return stop; }
            set { stop = value; }
        }

        // The SnoozePressed property indicates whether the snooze
        // button is pressed on the alarm when the alarm event is generated.
        //
        public bool SnoozePressed
        {
            get { return snoozePressed; }
            set { snoozePressed = value; }
        }

        public int Nrings { get => nrings; set => nrings = value; }

        // The event member that is of type AlarmEventHandler.
        //
        public event AlarmEventHandler Alarm;

        // The protected OnAlarm method raises the event by invoking
        // the delegates. The sender is always this, the current instance
        // of the class.
        //
        protected virtual void OnAlarm(AlarmEventArgs e)
        {
            AlarmEventHandler handler = Alarm;
            if (handler != null)
            {
                // Invokes the delegates.
                handler(this, e);
            }
        }

        // This alarm clock does not have
        // a user interface.
        // To simulate the alarm mechanism it has a loop
        // that raises the alarm event at every iteration
        // with a time delay of 300 milliseconds,
        // if snooze is not pressed. If snooze is pressed,
        // the time delay is 1000 milliseconds.
        //
        public void Start()
        {
            for (; ; )
            {
                nrings++;
                if (stop)
                {
                    break;
                }
                else
                {
                    if (snoozePressed)
                    {
                        System.Threading.Thread.Sleep(1000);
                    }
                    else
                    {
                        System.Threading.Thread.Sleep(300);
                    }
                    AlarmEventArgs e = new AlarmEventArgs(snoozePressed, nrings);
                    OnAlarm(e);
                }
            }
        }

        public void ManualEvent() {
            AlarmEventArgs e = new AlarmEventArgs(snoozePressed, nrings);
            OnAlarm(e);
        }
    }
}
