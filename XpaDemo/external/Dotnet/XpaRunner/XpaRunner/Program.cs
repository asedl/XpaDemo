using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Collections.Generic;

using CommandLine;
using ParameterParser;

namespace XpaRunner
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

    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
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

            string appname = Path.GetFileNameWithoutExtension(AppDomain.CurrentDomain.FriendlyName);
            string appsettings = Directory.GetCurrentDirectory() + "\\" + appname + ".settings";
            // appsettings = "C:\\magic.xpa\\samples\\xpatest\\XpaRunner.settings";
            bool shadowCopyFiles = false;
            ReadSettings(options, appsettings, ref shadowCopyFiles);
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
                CreateProcess(shadowCopyFiles, options, ParametersOtherStuff);
            }
            catch (Exception ex)
            {
                using (var sw = new StringWriter())
                {
                    sw.WriteLine("Failed: " + ex.Message);
                    sw.WriteLine("ExeFile=" + options.exeFile);
                    sw.WriteLine("WorkingDirectory=" + options.workingDir);
                    sw.WriteLine("Shadow Copy Files=" + (shadowCopyFiles ? "Y" : "N"));
                }

            }
        }

        static int CreateProcess(bool shadowCopyFiles, Options options, List<string> newParameters)
        {
            if (newParameters == null)
            {
                throw new ArgumentNullException(nameof(newParameters));
            }

            String commandline = String.Join(" ", newParameters);
            var p = new System.Diagnostics.Process();

            if (shadowCopyFiles)
            {
                if (!string.IsNullOrEmpty(options.workingDir))
                {
                    Directory.SetCurrentDirectory(options.workingDir);
                }

                var setup = AppDomain.CurrentDomain.SetupInformation;
                setup.ShadowCopyFiles = "true";
                var appDomain = AppDomain.CreateDomain(options.exeFile, AppDomain.CurrentDomain.Evidence, setup);

                appDomain.ExecuteAssembly(options.exeFile, CommandLineToArgs(commandline));
            }
            else
            {
                p.StartInfo.Arguments = Environment.ExpandEnvironmentVariables(commandline);

                p.StartInfo.FileName = options.exeFile;
                p.StartInfo.WorkingDirectory = options.workingDir;
                p.Start();
            }

            return 0;
        }

        private static int ReadSettings(Options options, String appsettings, ref bool shadowCopyFiles)
        {

            shadowCopyFiles = false;
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

                                case "SHADOWCOPYFILES":
                                    shadowCopyFiles = value.Equals("Y", StringComparison.InvariantCultureIgnoreCase);
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
                    sw.WriteLine("Shadow Copy Files=" + (shadowCopyFiles ? "Y" : "N"));
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


