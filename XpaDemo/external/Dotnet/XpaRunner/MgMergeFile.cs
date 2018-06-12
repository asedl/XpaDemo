using System;

/// <summary>
/// Summary description for Class1
/// </summary>
public class MgMergeFile
{
    private String Filename;

	public MgMergeFile(String Filename1)
	{
        Filename = Filename1;
    }

    public ReadFile() {
        Cstring FilenameTemp = GetTempFileName();

        int nModifications = 0;
        // Read the file and display it line by line.  
        System.IO.StreamReader file =
            new System.IO.StreamReader(Filename);
        System.IO.StreamWriter fileOut =
            new System.IO.StreamWriter(FilenameTempp);

        while ((line = file.ReadLine()) != null)
        {
            String strExpanded = Environment.ExpandEnvironmentVariables(line);
            if (!strExpanded.Equals(line))
                ++nModifications;
            file.WriteLine(strExpanded);
        }

        file.Close();
        fileOut.Close();
    }
}
