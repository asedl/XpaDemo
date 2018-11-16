using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XpaDemoTests
{
    public class MgProcessHelpers
    {
        public string PrintPdf(string filenamePdfPriterExe, System.String commandArguments, System.Double maxWaitTimeMs, System.Double exitCode)
        {
            Process p = null;
            string errormessage = "";

            try
            {
                // Start the process ...
                p = new Process();
                p.StartInfo.UseShellExecute = false;
                p.StartInfo.CreateNoWindow = false;
                p.StartInfo.FileName = filenamePdfPriterExe;
                p.StartInfo.Arguments = commandArguments;
                p.Start();

                // Now wait for the process tp terminate gracefully and kill it 
                // When MaxWaitTimeMs is exceeded
                int nMsWaited = 0;
                while (!p.WaitForExit(500))
                {
                    if (maxWaitTimeMs > 0)
                    {
                        nMsWaited *= 500;
                        if (nMsWaited >= maxWaitTimeMs)
                        {
                            p.Kill();
                        }
                    }
                };

                // Typically, by convention, Windows/DOS programs do return 0 if all went fine and an error code otherwise
                exitCode = p.ExitCode;
                p.Close();

            }
            catch (Exception e)
            {

                // When .NET is not able to start the process we will get an exception from where we copy just the message at the moment			
                errormessage = e.Message;
            }
            finally
            {
                exitCode = p.ExitCode;
                if (p != null)
                    p.Close();
            }

            // will be different from empty string if an exception did occur ...
            return errormessage;
        }

    }
}
