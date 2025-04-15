using System.Diagnostics;

namespace Speckle.Archicad.ReceiveService;

public class FileWriter
{
  public string RootDir { get; set; }
  public string OutputFolderName { get; set; }
  public int FilesPerFolder { get; set; }
  public int FilesWritten { get; private set; }

  public FileWriter(string rootDir, string outputFolderName, int filesPerFolder)
  {
    RootDir = rootDir;
    OutputFolderName = outputFolderName;
    FilesPerFolder = filesPerFolder;
    FilesWritten = 0;
  }

  public void Write(ArchicadElement elem)
  {
    int folderNum = (FilesWritten / FilesPerFolder) + 1;
    string folderPath = Path.Combine(RootDir, $"{OutputFolderName}_{folderNum}");

    if (!Directory.Exists(folderPath))
    {
      Directory.CreateDirectory(folderPath);
    }

    string fileName = $"speckle_object_{FilesWritten + 1}.xml";
    string filePath = Path.Combine(folderPath, fileName);
    string content = elem.ToString();

    File.WriteAllText(filePath, content);
    FilesWritten++;

    /*if (FilesWritten % FilesPerFolder == 0) 
    {
      var outDir = @"C:\poc\out";
      RunXmlConverter(folderPath, outDir);
    }*/
  }

  private void RunXmlConverter(string inputDir, string outputDir)
  {
    var lpXmlConverterPath = @"C:\Program Files\Graphisoft\Archicad 27\LP_XMLConverter.exe";
    Directory.CreateDirectory(outputDir);

    var startInfo = new ProcessStartInfo
    {
      FileName = lpXmlConverterPath,
      Arguments = $"x2l \"{inputDir}\" \"{outputDir}\"",
      UseShellExecute = false,
      CreateNoWindow = true,
    };

    using var process = Process.Start(startInfo);
  }
}
