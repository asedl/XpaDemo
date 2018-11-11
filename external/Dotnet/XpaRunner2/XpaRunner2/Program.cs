using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Diagnostics;

using CommandLine;
using ParameterParser;

namespace XpaRunner2
{

    public enum YesNo
    {
        Y, N
    }


    class Options
    {
        [Option("xparun_exe", Required = true)]
        public String exeFile { get; set; }

        [Option("xparun_workingdir", Required = false)]
        public String workingDir { get; set; }

        [Option("xparun_parameters", Required = false)]
        public String parameters { get; set; }

        [Option("xparun_envexpand", Required = false)]
        public YesNo envExpand { get; set; }

        [Option("xparun_inidir", Required = false)]
        public String iniDir { get; set; }

        [Option("xparun_wait", Required = false)]
        public YesNo wait { get; set; }

        [Value(0)]
        public IList<string> OtherStuff { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            // Read .settings before evaluating command line parametrs which have precedence
            Options options = new Options();
            // Parse the commandline into Dictionary Options ...
            var parser = new Parser(with => with.EnableDashDash = true);
            var results = CommandLine.Parser.Default.ParseArguments<Options>(args);
            CommandLine.Parser.Default.ParseArguments<Options>(args)
                  .WithParsed(r => { options = r; });
            List<string> ParametersOtherStuff = new List<string>();
            if (options.OtherStuff != null)
            {
                // Check if there is a @INI Merge file on command line
                // If yes, and if it contains system environment variables we will expand those
                // and replace that parameter by a (temp) file we generated
                ParametersOtherStuff = readParameter(options);
            }

            string exefilename = System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName;
            string directoryName = Path.GetDirectoryName(exefilename);
            string fileNameWoExtension = Path.GetFileNameWithoutExtension(exefilename);
            string settingsFilename = directoryName + Path.DirectorySeparatorChar + fileNameWoExtension + ".settings";
            Console.WriteLine("Read settings from: {0}", settingsFilename);

            ReadSettings(options, settingsFilename);
            if (!String.IsNullOrEmpty(options.parameters))
            {
                ParametersParser Parameters = new ParametersParser(options.parameters);
                foreach (var parameter in Parameters)
                {
                    if (parameter.Bruto.Length > 0 && parameter.Bruto[0] == '@')
                    {
                        MgMergeFile mgMergeFile = new MgMergeFile();
                        int nModifications = mgMergeFile.ReadFile(parameter.Bruto.Substring(1));
                        if (nModifications > 0)
                        {
                            // Our (generated) copy differs from the original file. Effectively this means
                            // that it did contain system environment variables which we did expand
                            // We change the commandline parameter to our version 
                            ParametersOtherStuff.Add('@' + mgMergeFile.GetFilenameTemp());
                        }
                        else
                        {
                            ParametersOtherStuff.Add(parameter.Bruto);
                        }
                    }
                    else
                    {
                        ParametersOtherStuff.Add(parameter.Bruto);
                    }
                }
            }

            try
            {
                CreateProcess(options, ParametersOtherStuff);
            }
            catch (Exception ex)
            {
                using (var sw = new StringWriter())
                {
                    sw.WriteLine("Failed: " + ex.Message);
                    sw.WriteLine("ExeFile=" + options.exeFile);
                    sw.WriteLine("WorkingDirectory=" + options.workingDir);
                }

            }

        }

        static int CreateProcess(Options options, List<string> newParameters)
        {
            if (newParameters == null)
            {
                throw new ArgumentNullException(nameof(newParameters));
            }

            String commandline = String.Join(" ", newParameters);

            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = options.exeFile;
            startInfo.Arguments = Environment.ExpandEnvironmentVariables(commandline);
            startInfo.WorkingDirectory = options.workingDir;

            Process p = null;

            try
            {
                p = Process.Start(startInfo);

                do {
                    if (!p.HasExited) {
                        Console.WriteLine("  physical memory usage: {0}", p.WorkingSet64);
                        Console.WriteLine("  user processor time: {0}", p.UserProcessorTime);

                        if (p.Responding)
                        {
                            Console.WriteLine("Status = Running");
                        }
                        else
                        {
                            Console.WriteLine("Status = Not Responding");
                        }
                    }
                }
                while (!p.WaitForExit(1000));

                Console.WriteLine();
                Console.WriteLine("Process exit code: {0}", p.ExitCode);
            }
            finally
            {
                if (p != null)
                {
                    p.Close();
                }
            }


            return 0;
        }

        private static int ReadSettings(Options options, String appsettings)
        {

            try
            {
                using (var sr = new StreamReader(appsettings))
                {
                    string line;
                    while ((line = sr.ReadLine()) != null)
                    {
                        var eq = line.IndexOf('=');
                        if (eq > 0)
                        {
                            var name = line.Remove(eq).Trim().ToUpper();
                            var value = line.Substring(eq + 1).Trim();
                            if (name.StartsWith(";"))
                                continue;
                            switch (name)
                            {
                                case "XPARUN_EXE":
                                    if (String.IsNullOrEmpty(options.exeFile))
                                    {
                                        options.exeFile = value;
                                    }

                                    break;
                                case "XPARUN_EXEDIR":
                                    if (String.IsNullOrEmpty(options.workingDir))
                                        options.workingDir = value;
                                    break;
                                case "XPARUN_PARAMETERS":
                                    if (String.IsNullOrEmpty(options.parameters))
                                        options.parameters = value;
                                    break;
                                case "XPARUN_ENVEXPAND":
                                    if (options.wait != YesNo.Y && options.wait != YesNo.N)
                                        options.wait = (YesNo)Enum.Parse(typeof(YesNo), value);
                                    break;

                                default:
                                    break;
                            }
                        }
                    }
                }

            }
            catch (Exception ex)
            {
                using (var sw = new StringWriter())
                {
                    sw.WriteLine("Failed: " + ex.Message);
                    sw.WriteLine("ExeFile=" + options.exeFile);
                    sw.WriteLine("WorkingDirectory=" + options.workingDir);
                }

            }

            return 0;
        }

        [DllImport("shell32.dll", SetLastError = true)]
        static extern IntPtr CommandLineToArgvW([MarshalAs(UnmanagedType.LPWStr)] string lpCmdLine, out int pNumArgs);

        public static string[] CommandLineToArgs(string commandLine)
        {
            int argc;
            var argv = CommandLineToArgvW(commandLine, out argc);
            if (argv == IntPtr.Zero)
                throw new System.ComponentModel.Win32Exception();
            try
            {
                var args = new string[argc];
                for (var i = 0; i < args.Length; i++)
                {
                    var p = Marshal.ReadIntPtr(argv, i * IntPtr.Size);
                    args[i] = Marshal.PtrToStringUni(p);
                }

                return args;
            }
            finally
            {
                Marshal.FreeHGlobal(argv);
            }
        }

        private static List<string> readParameter(Options o)
        {
            // Check if there is a @INI Merge file on command line
            // If yes, and if it contains system environment variables we will expand those
            // and replace that parameter by a (temp) file we generated
            List<string> newParameters = new List<string>();
            foreach (String p in o.OtherStuff)
            {
                if (p[0] == '@')
                {
                    MgMergeFile mgMergeFile = new MgMergeFile();
                    int nModifications = mgMergeFile.ReadFile(p.Substring(1));
                    if (nModifications > 0)
                    {
                        // Our (generated) copy differs from the original file. Effectively this means
                        // that it did contain system environment variables which we did expand
                        // We change the commandline parameter to our version 
                        newParameters.Add('@' + mgMergeFile.GetFilenameTemp());
                    }
                    else
                    {
                        newParameters.Add(p);
                    }
                }
                else
                {
                    // Neither @INIs nor parameter (Otions) for XpaRunner. We just forward these
                    newParameters.Add(p);
                }
            }

            return newParameters;
        }

    }
}
