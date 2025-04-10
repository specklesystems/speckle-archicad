using System.Collections;
using Speckle.InterfaceGenerator;
using Speckle.Objects.Geometry;
using Speckle.Sdk.Models;
using Speckle.Sdk.Models.GraphTraversal;
using Speckle.Sdk.Models.Collections;
using Speckle.Sdk.Models.Extensions;
//using System.Collections.Concurrent;
using System.Diagnostics;
using Speckle.Objects.Other;

namespace Speckle.Archicad.ReceiveService;

[GenerateAutoInterface]
public sealed class HostObjectBuilder : IHostObjectBuilder
{
  private Dictionary<string, string> _elementMaterials;
  private Dictionary<string, ArchicadMaterial> _materialTable;

  public async Task Build(
    Base rootObject,
    CancellationToken cancellationToken
  )
  {
    var renderMaterialProxies = TryGetRenderMaterialProxies(rootObject);
    _elementMaterials = new Dictionary<string, string>();

    if (renderMaterialProxies != null)
    {
      foreach (var proxy in renderMaterialProxies)
      {
        var proxyId = proxy.GetId();
        foreach (var elem in proxy.objects)
        {
          _elementMaterials.Add(elem, proxyId);
        }
      }
    }

    _materialTable = new Dictionary<string, ArchicadMaterial>();
    if (renderMaterialProxies != null)
    {
      foreach (var proxy in renderMaterialProxies)
      {
        var renderMaterial = proxy.value;
        var materialName = renderMaterial.name;
        var proxyId = proxy.GetId();
        _materialTable.Add(proxyId, new ArchicadMaterial(materialName, renderMaterial));
      }
    }

    List<TraversalContext> objectsToConvertTc = DefaultTraversal.CreateTraversalFunc()
        .Traverse(rootObject)
        .Where(ctx => ctx.Current is not Collection)
        .ToList();

    /*var batchSize = 1; // Adjust based on performance testing
    var batches = objectsToConvertTc.Chunk(batchSize);

    var results = new ConcurrentBag<ArchicadElement>();

    var tasks = batches.Select(batch => Task.Run(() =>
    {
      foreach (var context in batch)
      {
        cancellationToken.ThrowIfCancellationRequested();

        var elem = ConvertToArchicadElement(context.Current);
        if (!elem.Empty)
        {
          results.Add(elem);
        }
      }
    }, cancellationToken)).ToArray();
    await Task.WhenAll(tasks);*/

    var results = new List<ArchicadElement>();
    foreach (var context in objectsToConvertTc)
    {
      cancellationToken.ThrowIfCancellationRequested();
      var elem = ConvertToArchicadElement(context.Current);
      if (!elem.Empty)
      {
        results.Add(elem);
      }
    }

    await PrintElementsAsync(results.ToList());

    var rootDir = @"C:\poc";
    var outDir = @"C:\poc\out";
    await RunXmlConvertersAsync(rootDir, outDir);
  }

  public IReadOnlyCollection<RenderMaterialProxy>? TryGetRenderMaterialProxies(Base root) =>
    TryGetProxies<RenderMaterialProxy>(root, "renderMaterialProxies");

  private IReadOnlyCollection<T>? TryGetProxies<T>(Base root, string key) =>
    (root[key] as List<object>)?.Cast<T>().ToList();

  private ArchicadElement ConvertToArchicadElement(Base target)
  {
    var elem = new ArchicadElement();
    string matName = "speckle_default_material";
    var addedMaterials = new HashSet<string>();

    foreach (var mesh in GetMeshes(target))
    {
      string meshId = mesh.applicationId ?? "0";
      if (_elementMaterials.TryGetValue(meshId, out var materialId))
      {
        if (_materialTable.TryGetValue(materialId, out var material)) 
        {
          matName = material.Name;
          if (addedMaterials.Add(matName))
          {
            elem.AddMaterial(material);
          }
        }
      }
      var acMesh = new ArchicadMesh(mesh, matName);
      acMesh.Scale(0.001);
      elem.AddMesh(acMesh);
    }

    return elem;
  }

  private List<Mesh> GetMeshes(Base target)
  {
    var meshes = new List<Mesh>();
    switch (target)
    {
      case Mesh mesh:
        meshes.Add(mesh);
        break;
      default:
        var displayValue = target.TryGetDisplayValue<Base>();
        if ((displayValue is IList && !displayValue.Any()) || displayValue is null)
        {
          //throw
        }
        if (displayValue != null)
        {
          foreach (var display in displayValue)
          {
            meshes.AddRange(GetMeshes(display));
          }
        }     
        break;
    }

    return meshes;
  }

  public async Task PrintElementsAsync(IEnumerable<ArchicadElement> elements)
  {
    var rootDir = @"C:\poc";
    Directory.CreateDirectory(rootDir);

    var numSubdir = 8;
    var subDirs = Enumerable.Range(1, numSubdir)
                            .Select(i => Path.Combine(rootDir, $"f{i}"))
                            .ToArray();

    foreach (var dir in subDirs)
    {
      Directory.CreateDirectory(dir);
    }

    var writeTasks = new List<Task>();
    int count = 1;

    foreach (var elem in elements)
    {
      int folderIndex = (count - 1) % numSubdir;
      string folderPath = subDirs[folderIndex];

      string fileName = $"speckle_object_{count}.xml";
      string filePath = Path.Combine(folderPath, fileName);

      var content = elem.ToString(); // Cache value to avoid closures

      writeTasks.Add(File.WriteAllTextAsync(filePath, content));
      count++;
    }

    await Task.WhenAll(writeTasks);
  }

  private async Task RunXmlConvertersAsync(string rootDir, string outputDir)
  {
    var lpXmlConverterPath = @"C:\Program Files\Graphisoft\Archicad 27\LP_XMLConverter.exe";

    var sourceDirs = Directory.GetDirectories(rootDir)
                              .Where(dir => Path.GetFileName(dir).StartsWith('f'))
                              .ToArray();

    Directory.CreateDirectory(outputDir);

    var conversionTasks = sourceDirs.Select(sourceDir =>
    {
      return Task.Run(() =>
      {
        var startInfo = new ProcessStartInfo
        {
          FileName = lpXmlConverterPath,
          Arguments = $"x2l \"{sourceDir}\" \"{outputDir}\"",
          UseShellExecute = false,
          CreateNoWindow = true,
        };

        using var process = Process.Start(startInfo);
        process?.WaitForExit();
      });
    });

    await Task.WhenAll(conversionTasks);
  }
}
