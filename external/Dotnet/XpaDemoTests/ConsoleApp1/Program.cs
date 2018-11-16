using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using XpaDemoTests;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            MgProcessHelpers mgph = new MgProcessHelpers();
            String sRetMessage = 
                mgph.PrintPdf(@"D:\Program Files (x86)\Foxit Software\Foxit Reader\FoxitReader.exe", @"/p C:\Users\sedlm\Documents\TestPdf.pdf", 5000);
            Console.WriteLine(sRetMessage);
            Console.ReadKey();
        }
    }
}
