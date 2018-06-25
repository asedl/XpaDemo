using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XpaTHttpDNetTest
{
    class Program
    {
        static void Main(string[] args)
        {
            int nRet = XpaTHttpDNet.XpaTHttpDNet.Post(
                @"https://localhost:9001/SoapContext/SoapPort",
                "",
                "",
                @"C:\xpa\samples\XpaDemo\XpaDemo\Temp\soap_request_01.xml",
                @"C:\xpa\samples\XpaDemo\XpaDemo\Temp\soap_request_01.response.xml",
                @"C:\xpa\samples\XpaDemo\XpaDemo\Samplefiles\certificates\myclientkey.p12",
                "test"
                );
        }
    }
}
