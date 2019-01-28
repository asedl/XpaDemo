using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XpaDemoTests
{
    public class MgFileHelpers
    {
        public FileSystemInfo[] FileListGet(String directory, String orderby) {
            List<FileSystemInfo> filesOrdered, files = new DirectoryInfo(directory).GetFileSystemInfos().ToList();

            switch (orderby) {
                case "CreationTime":
                    filesOrdered = files.OrderBy(f => f.CreationTime).ToList();
                    break;
                case "Extension":
                    filesOrdered = files.OrderBy(f => f.Extension).ToList();
                    break;
                case "FullName":
                    filesOrdered = files.OrderBy(f => f.FullName).ToList();
                    break;
                case "Name":
                default:
                    filesOrdered = files.OrderBy(f => f.Name).ToList();
                    break;
            }
            if (orderby == "CreationTime ")
                filesOrdered = files.OrderBy(f => f.CreationTime).ToList();
            return filesOrdered.ToArray();
        }
    }
}
