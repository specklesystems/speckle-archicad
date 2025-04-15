using System.Collections.Concurrent;
using System.Diagnostics;

namespace Speckle.Archicad.ReceiveService;

#pragma warning disable CA1001
public class FolderProcessor
{
  private readonly string _storePath = @"C:\poc";
  private readonly string _outputRoot = @"C:\poc\output";
  private readonly SemaphoreSlim _semaphore = new SemaphoreSlim(8); // max concurrent processes
  private readonly ConcurrentDictionary<string, bool> _processedFolders = new ConcurrentDictionary<string, bool>();
  private readonly TimeSpan _idleTimeout = TimeSpan.FromSeconds(1);
  private DateTime _lastFolderDetected = DateTime.Now;
  private bool _isWatching = true;

  public async Task StartAsync()
  {
    Console.WriteLine("Monitoring started...");
    _ = Task.Run(() => WatchForNewFolders());

    while (_isWatching)
    {
      var subfolders = Directory.GetDirectories(_storePath);
      foreach (var folder in subfolders)
      {
        if (!_processedFolders.ContainsKey(folder))
        {
          _processedFolders[folder] = true;
          _ = ProcessFolderAsync(folder);
        }
      }

      if ((DateTime.Now - _lastFolderDetected) > _idleTimeout)
      {
        _isWatching = false;
      }

      await Task.Delay(1000);
    }

    Console.WriteLine("No new folders detected. Waiting for running processes to finish...");
    while (_semaphore.CurrentCount < 8)
    {
      await Task.Delay(500);
    }
    Console.WriteLine("All processing complete.");
  }

  private void WatchForNewFolders()
  {
    using var watcher = new FileSystemWatcher(_storePath)
    {
      NotifyFilter = NotifyFilters.DirectoryName,
      EnableRaisingEvents = true,
    };

    watcher.Created += (s, e) =>
    {
      if (Directory.Exists(e.FullPath))
      {
        _lastFolderDetected = DateTime.Now;
      }
    };

    while (_isWatching)
    {
      Thread.Sleep(500);
    }
  }

  private async Task ProcessFolderAsync(string inputDir)
  {
    await _semaphore.WaitAsync();

    try
    {
      string folderName = Path.GetFileName(inputDir);
      string outputDir = Path.Combine(_outputRoot, folderName);

      Console.WriteLine($"Processing: {folderName}");
      RunXmlConverter(inputDir, outputDir);
    }
    finally
    {
      _semaphore.Release();
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

    using var process = Process.Start(startInfo);
    process?.WaitForExit();
  }
}
