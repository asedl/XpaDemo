using System;
using System.IO;

/// <summary>
/// Summary description for Class1
/// </summary>
public class MgMergeFile
{
    private string filenameTemp;


    public MgMergeFile()
    {
    }

    public string GetFilenameTemp()
    {
        return filenameTemp;
    }

    public int ReadFile(String mergefilename)
    {
        filenameTemp = Path.GetTempFileName();

        int nModifications = 0;
        // Read the file and display it line by line.  
        System.IO.StreamReader file =
            new System.IO.StreamReader(mergefilename);
        System.IO.StreamWriter fileOut =
            new System.IO.StreamWriter(GetFilenameTemp());

        String line;
        while ((line = file.ReadLine()) != null)
        {
            String strExpanded = Environment.ExpandEnvironmentVariables(line);
            if (!strExpanded.Equals(line))
                ++nModifications;
            fileOut.WriteLine(strExpanded);
        }

        file.Close();
        fileOut.Close();

        return nModifications;
    }
}
