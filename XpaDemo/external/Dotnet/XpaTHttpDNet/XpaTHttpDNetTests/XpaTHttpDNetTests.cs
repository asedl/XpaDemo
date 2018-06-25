using Microsoft.VisualStudio.TestTools.UnitTesting;
using XpaTHttpDNet;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XpaTHttpDNet.Tests
{
    [TestClass()]
    public class XpaTHttpDNetTests
    {
        [TestMethod()]
        public void PostTest()
        {

            int nRet = XpaTHttpDNet.Post(
                @"https://localhost:9001/SoapContext/SoapPort",
                "",
                "",
                @"C:\xpa\samples\XpaDemo\XpaDemo\Temp\soap_request_01.xml",
                @"C:\xpa\samples\XpaDemo\XpaDemo\Temp\soap_request_01.response.xml",
                @"C:\xpa\samples\XpaDemo\XpaDemo\Samplefiles\certificates\myclientkey.p12",
                "test"
                );

            Assert.Fail();
        }
    }
}