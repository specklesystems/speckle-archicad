using System.Collections;
using Speckle.InterfaceGenerator;
using Speckle.Objects.Geometry;
using Speckle.Sdk.Models;
using Speckle.Sdk.Models.GraphTraversal;
using Speckle.Sdk.Models.Extensions;
using System.Diagnostics;
using Speckle.Objects.Other;
using Speckle.Archicad.ReceiveService.Instances;
using Speckle.Archicad.ReceiveService.Operations.Receive;
using Speckle.Objects;
using Speckle.Sdk;
using Speckle.DoubleNumerics;
using System.Collections.Concurrent;

namespace Speckle.Archicad.ReceiveService;
[GenerateAutoInterface]
public sealed class HostObjectBuilder() : IHostObjectBuilder
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
          _elementMaterials.TryAdd(elem, proxyId);
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

    var rootObjectUnpacker = new RootObjectUnpacker(DefaultTraversal.CreateTraversalFunc());
    var localToGlobalUnpacker = new LocalToGlobalUnpacker();

    // 1 - Unpack objects and proxies from root commit object
    var unpackedRoot = rootObjectUnpacker.Unpack(rootObject);
    var localToGlobalMaps = localToGlobalUnpacker.Unpack(
      unpackedRoot.DefinitionProxies,
    unpackedRoot.ObjectsToConvert.ToList()
    );

#pragma warning disable CA2000

    // 2 - Processing Elements in a Loop
    //var resultsQueue = new BlockingCollection<ArchicadElement>();

    /*var rootFolder = @"C:\poc";
    var outFolder = @"out";
    int filesPerFolder = 100;
    var fileWriter = new FileWriter(rootFolder, outFolder, filesPerFolder);

    var consumerTask = Task.Run(() =>
    {
      foreach (var elem in resultsQueue.GetConsumingEnumerable())
      {
        fileWriter.Write(elem); // Your FileWriter class's write logic
      }
    }, cancellationToken);*/

    //var numConsumers = Environment.ProcessorCount;
    /*var numConsumers = 4;
    var tasks = new List<Task>();
    var rootFolder = @"C:\poc";
    var outFolder = @"out";
    int filesPerFolder = 100;

    for (int i = 0; i < numConsumers; i++)
    {
      int index = i;
      var writer = new FileWriter(rootFolder, $"{outFolder}_{index}", filesPerFolder);

      tasks.Add(Task.Run(() =>
      {
        foreach (var elem in resultsQueue.GetConsumingEnumerable())
        {
          writer.Write(elem);
        }
      }, cancellationToken));
    }*/

    /*foreach (LocalToGlobalMap localToGlobalMap in localToGlobalMaps)
    {
      cancellationToken.ThrowIfCancellationRequested();
      try
      {
        if (
          localToGlobalMap.AtomicObject is ITransformable transformable
          && localToGlobalMap.Matrix.Count > 0
          && localToGlobalMap.AtomicObject["units"] is string units
        )
        {
          var id = localToGlobalMap.AtomicObject.id;
          ITransformable? newTransformable = null;
          foreach (var mat in localToGlobalMap.Matrix)
          {
            transformable.TransformTo(new Transform() { matrix = mat, units = units }, out newTransformable);
            transformable = newTransformable;
          }

          localToGlobalMap.AtomicObject = (newTransformable as Base)!;
          localToGlobalMap.AtomicObject.id = id;
          localToGlobalMap.Matrix = new HashSet<Matrix4x4>();
        }

        var elem = ConvertToArchicadElement(localToGlobalMap.AtomicObject, localToGlobalMap.Matrix);
        if (!elem.Empty)
        {
          resultsQueue.Add(elem, cancellationToken); // Add to queue instead of results list
        }
      }
      catch (Exception ex) when (!ex.IsFatal())
      {
        // swallow or log
      }
    }*/

    /*resultsQueue.CompleteAdding();
    //await consumerTask;
    await Task.WhenAll(tasks);

    stopwatch.Stop();
    Console.WriteLine($"Elapsed time: {stopwatch.ElapsedMilliseconds} ms");
    return;*/

    var resultsQueue = new BlockingCollection<ArchicadElement>();

    Parallel.ForEach(localToGlobalMaps, new ParallelOptions { CancellationToken = cancellationToken }, localToGlobalMap =>
    {
      cancellationToken.ThrowIfCancellationRequested();
      try
      {
        if (
            localToGlobalMap.AtomicObject is ITransformable transformable
            && localToGlobalMap.Matrix.Count > 0
            && localToGlobalMap.AtomicObject["units"] is string units
        )
        {
          var id = localToGlobalMap.AtomicObject.id;
          ITransformable? newTransformable = null;
          foreach (var mat in localToGlobalMap.Matrix)
          {
            transformable.TransformTo(new Transform() { matrix = mat, units = units }, out newTransformable);
            transformable = newTransformable;
          }

          localToGlobalMap.AtomicObject = (newTransformable as Base)!;
          localToGlobalMap.AtomicObject.id = id;
          localToGlobalMap.Matrix = new HashSet<Matrix4x4>();
        }

        var elem = ConvertToArchicadElement(localToGlobalMap.AtomicObject, localToGlobalMap.Matrix);
        if (!elem.Empty)
        {
          resultsQueue.Add(elem, cancellationToken);
        }
      }
      catch (Exception ex) when (!ex.IsFatal())
      {
        // log or swallow
      }
    });

    // Mark the collection as complete once all work is done
    resultsQueue.CompleteAdding();

    Stopwatch stopwatch = new Stopwatch();
    stopwatch.Start();
    var rootFolder = @"C:\poc";
    var fc = new FileConverter(rootFolder);
    await fc.Convert(resultsQueue, cancellationToken);

    /*var numConsumers = 16;
    var tasks = new List<Task>();
    var rootFolder = @"C:\poc";
    var outFolder = @"out";
    int filesPerFolder = 100;

    for (int i = 0; i < numConsumers; i++)
    {
      int index = i;
      var writer = new FileWriter(rootFolder, $"{outFolder}_{index}", filesPerFolder);

      tasks.Add(Task.Run(() =>
      {
        foreach (var elem in resultsQueue.GetConsumingEnumerable())
        {
          writer.Write(elem);
        }
      }, cancellationToken));
    }*/

    //await Task.WhenAll(tasks);
    //await Task.WhenAny(tasks);
    stopwatch.Stop();
    Console.WriteLine($"Elapsed time: {stopwatch.ElapsedMilliseconds} ms");
    //await DummyAsyncFunction();
  }

  public IReadOnlyCollection<RenderMaterialProxy>? TryGetRenderMaterialProxies(Base root) =>
    TryGetProxies<RenderMaterialProxy>(root, "renderMaterialProxies");

  private IReadOnlyCollection<T>? TryGetProxies<T>(Base root, string key) =>
    (root[key] as List<object>)?.Cast<T>().ToList();

  private ArchicadMaterial? GetMaterialById(string appId)
  {
    if (_elementMaterials.TryGetValue(appId, out var materialId))
    {
      if (_materialTable.TryGetValue(materialId, out var material))
      {
        return material;
      }
    }
    return null;
  }

  private ArchicadElement ConvertToArchicadElement(Base target, IReadOnlyCollection<Matrix4x4> matrix)
  {
    var elem = new ArchicadElement();
    string elemId = target.applicationId ?? "0";
    string matName = "speckle_default_material";
    var addedMaterials = new HashSet<string>();

    var combinedTransform = Matrix4x4.Identity;

    // existence of units is must, to be able to scale the transform correctly
    /*if (target["units"] is string units)
    {
      
    }*/

    foreach (Matrix4x4 m in matrix)
    {
      combinedTransform *= m;
    }

    foreach (var mesh in GetMeshes(target))
    {
      string meshId = mesh.applicationId ?? "0";
      // TODO refactor
      var meshmat = GetMaterialById(meshId);
      if (meshmat != null) 
      {
        matName = meshmat.Name;
        if (addedMaterials.Add(meshmat.Name))
        {
          elem.AddMaterial(meshmat);
        }
      }
      else
      {
        var elemmat = GetMaterialById(elemId);
        if (elemmat != null)
        {
          matName = elemmat.Name;
          if (addedMaterials.Add(elemmat.Name))
          {
            elem.AddMaterial(elemmat);
          }
        }
      }

      var acMesh = new ArchicadMesh(mesh, matName);
      acMesh.ApplyTransform(combinedTransform);
      //acMesh.Scale(0.001);
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

  public async Task PrintElementsAsync2(IEnumerable<ArchicadElement> elements, int subDirNum)
  {
    var rootDir = @"C:\poc";
    Directory.CreateDirectory(rootDir);
    var subdir = Path.Combine(rootDir, $"f{subDirNum}");

    var writeTasks = new List<Task>();
    int count = 1;

    foreach (var elem in elements)
    {
      string fileName = $"speckle_object_{count}.xml";
      string filePath = Path.Combine(subdir, fileName);

      var content = elem.ToString(); // Cache value to avoid closures

      writeTasks.Add(File.WriteAllTextAsync(filePath, content));
      count++;
    }

    await Task.WhenAll(writeTasks);
  }

  public async Task PrintElementsAsync(IEnumerable<ArchicadElement> elements, int numSubdir)
  {
    var rootDir = @"C:\poc";
    Directory.CreateDirectory(rootDir);

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
}
