using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace XpaDemoTests
{
    public class MgProcessHelpers
    {
        public string PrintPdf(string filenamePdfPriterExe, System.String commandArguments, int maxWaitTimeMs)
        {
            int exitCode = -1;
            Process p = null;
            string errormessage = "";

            try
            {
                // Start the process ...
                p = new Process();
                p.StartInfo.UseShellExecute = false;
                p.StartInfo.CreateNoWindow = true;
                p.StartInfo.FileName = filenamePdfPriterExe;
                p.StartInfo.Arguments = commandArguments;
                p.Start();

                // Now wait for the process tp terminate gracefully and kill it 
                // When MaxWaitTimeMs is exceeded
                int nMsWaited = 0;
                while (!p.WaitForExit(500))
                {
                    if (nMsWaited >= maxWaitTimeMs && p.MainWindowHandle != IntPtr.Zero) {
                        // It had some time. Now lets try to close it for a graceful exit ...
                        errormessage += ",closed main window";
                        p.CloseMainWindow();

                        Thread.Sleep(2000);

                        break;
                    }

                    nMsWaited += 500;

                };

                if (!p.HasExited) {
                    // We risk to loose unsaved data and corrupt stuff ....
                    errormessage += String.Format (",killing process with id {0}", p.Id);
                    p.Kill();
                }


                // Typically, by convention, Windows/DOS programs do return 0 if all went fine and an error code otherwise
                exitCode = p.ExitCode;

            }
            catch (Exception e)
            {

                // When .NET is not able to start the process we will get an exception from where we copy just the message at the moment			
                errormessage = e.Message;
            }
            finally
            {
                if (p != null) {
                    p.Dispose();
                }
            }

            String sRet = String.Format("{0}:{1}", exitCode, errormessage);
            return sRet;
        }
    }
}
