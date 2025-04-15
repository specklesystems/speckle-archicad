using System.Collections.Concurrent;
using System.Diagnostics;
using System.Text.Json;
using System.Threading.Channels;

namespace Speckle.Archicad.ReceiveService;

public class FileConverter
{
  private readonly string _converterPath = @"C:\Program Files\Graphisoft\Archicad 27\LP_XMLConverter.exe";
  private readonly string _outputBaseDir;
  private readonly int _maxFilesPerFolder = 200;
  private readonly int _maxParallelConversions = 4;

  public FileConverter(string outputBaseDir)
  {
    _outputBaseDir = outputBaseDir;
    Directory.CreateDirectory(outputBaseDir);
  }

  public async Task Convert(BlockingCollection<ArchicadElement> elements, CancellationToken cancellationToken = default)
  {
    var inputChannel = Channel.CreateUnbounded<string>();

    // Start Consumers
    var consumers = Enumerable.Range(0, _maxParallelConversions).Select(_ => Task.Run(async () =>
    {
      await foreach (var folder in inputChannel.Reader.ReadAllAsync(cancellationToken))
      {
        string outputDir = Path.Combine(_outputBaseDir, "_output", Path.GetFileName(folder));
        //string outputDir = Path.Combine(_outputBaseDir, "out");
        RunXmlConverter(folder, outputDir);
      }
    }, cancellationToken)).ToList();

    // Producer
    var producer = Task.Run(async () =>
    {
      int folderIndex = 1;
      int fileCount = 0;
      int filesWritten = 0;
      string currentFolder = CreateFolder(folderIndex);

      foreach (var element in elements.GetConsumingEnumerable(cancellationToken))
      {
        string fileName = $"speckle_object_{filesWritten + 1}.xml";
        string filePath = Path.Combine(currentFolder, fileName);
        string content = element.ToString();
        File.WriteAllText(filePath, content);
        fileCount++;
        filesWritten++;

        if (fileCount >= _maxFilesPerFolder)
        {
          //MarkFolderAsComplete(currentFolder, fileCount);
          await inputChannel.Writer.WriteAsync(currentFolder, cancellationToken);
          folderIndex++;
          currentFolder = CreateFolder(folderIndex);
          fileCount = 0;
        }
      }

      // Handle last folder if it has leftover files
      if (fileCount > 0)
      {
        //MarkFolderAsComplete(currentFolder, fileCount);
        await inputChannel.Writer.WriteAsync(currentFolder, cancellationToken);
      }

      inputChannel.Writer.Complete();
    }, cancellationToken);

    await producer;
    await Task.WhenAll(consumers);
  }

  private string CreateFolder(int index)
  {
    string folderName = $"Batch_{index:D3}";
    string path = Path.Combine(_outputBaseDir, folderName);
    Directory.CreateDirectory(path);
    return path;
  }

  private void RunXmlConverter(string inputDir, string outputDir)
  {
    Directory.CreateDirectory(outputDir);

    var startInfo = new ProcessStartInfo
    {
      FileName = _converterPath,
      Arguments = $"x2l \"{inputDir}\" \"{outputDir}\"",
      UseShellExecute = false,
      CreateNoWindow = true,
    };

    using var process = Process.Start(startInfo);
    process?.WaitForExit();

    var fileCount = Directory.GetFiles(outputDir).Length;
    MarkFolderAsComplete(outputDir, fileCount);
  }

  private void MarkFolderAsComplete(string folderPath, int fileCount)
  {
    var result = new
    {
      result = "success",
      fileCount = fileCount
    };

    string resultFilePath = Path.Combine(folderPath, "results.json");
#pragma warning disable CA1869 // Cache and reuse 'JsonSerializerOptions' instances
    string json = JsonSerializer.Serialize(result, new JsonSerializerOptions { WriteIndented = true });
#pragma warning restore CA1869 // Cache and reuse 'JsonSerializerOptions' instances
    File.WriteAllText(resultFilePath, json);
  }

}
