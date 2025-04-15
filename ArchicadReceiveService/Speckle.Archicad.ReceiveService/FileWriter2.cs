using System.Collections.Concurrent;
using System.Diagnostics;

namespace Speckle.Archicad.ReceiveService;

#pragma warning disable CA1003
#pragma warning disable CA2000
#pragma warning disable CA2008
#pragma warning disable CA1063
#pragma warning disable CA1816
#pragma warning disable CS8600

public class FileWriter2 : IDisposable
{
  public string RootDir { get; set; }
  public string OutputFolderName { get; set; }
  public int FilesPerFolder { get; set; }
  public int MaxConverterProcesses { get; set; }
  public int FilesWritten { get; private set; }

  private readonly ConcurrentQueue<string> _folderQueue = new();
  private readonly SemaphoreSlim _converterSemaphore;
  private int _runningProcesses;

  private readonly string _outDir = @"C:\poc\out";


  //public event Action? AllConversionsCompleted;

  public FileWriter2(string rootDir, string outputFolderName, int filesPerFolder, int maxConverterProcesses)
  {
    RootDir = rootDir;
    OutputFolderName = outputFolderName;
    FilesPerFolder = filesPerFolder;
    MaxConverterProcesses = maxConverterProcesses;
    _converterSemaphore = new SemaphoreSlim(maxConverterProcesses);
    Directory.CreateDirectory(_outDir);
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

    if (FilesWritten % FilesPerFolder == 0)
    {
      _folderQueue.Enqueue(folderPath);
      TryStartConversion2();
    }
  }

  private void TryStartConversion2()
  {
    if (_runningProcesses < MaxConverterProcesses && _folderQueue.TryDequeue(out string folderPath))
    {
      Interlocked.Increment(ref _runningProcesses);
      RunXmlConverter(folderPath, _outDir);
    }
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

    var process = new Process
    {
      StartInfo = startInfo,
      EnableRaisingEvents = true
    };

    process.Exited += (sender, e) =>
    {
      Console.WriteLine("XML conversion process has exited.");
      Interlocked.Decrement(ref _runningProcesses);
      TryStartConversion2();
      process.Dispose();
    };

    process.Start();
  }
  
  public void Dispose()
  {
    _converterSemaphore.Dispose();
  }
}
