using System.Collections;
using Speckle.InterfaceGenerator;
using Speckle.Objects.Geometry;
using Speckle.Sdk.Models;
using Speckle.Sdk.Models.GraphTraversal;
//using Speckle.Sdk.Models.Collections;
using Speckle.Sdk.Models.Extensions;
//using System.Collections.Concurrent;
using System.Diagnostics;
using Speckle.Objects.Other;
using Speckle.Archicad.ReceiveService.Instances;
using Speckle.Archicad.ReceiveService.Operations.Receive;
using Speckle.Objects;
using Speckle.Sdk;
using Speckle.DoubleNumerics;


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

    var rootObjectUnpacker = new RootObjectUnpacker(DefaultTraversal.CreateTraversalFunc());
    var localToGlobalUnpacker = new LocalToGlobalUnpacker();

    // 1 - Unpack objects and proxies from root commit object
    var unpackedRoot = rootObjectUnpacker.Unpack(rootObject);
    var localToGlobalMaps = localToGlobalUnpacker.Unpack(
      unpackedRoot.DefinitionProxies,
      unpackedRoot.ObjectsToConvert.ToList()
    );

    //**********************************************************************************

    var results = new List<ArchicadElement>();

    foreach (LocalToGlobalMap localToGlobalMap in localToGlobalMaps)
    {
      cancellationToken.ThrowIfCancellationRequested();
      try
      {
        // POC hack of the ages: try to pre transform curves, points and meshes before baking
        // we need to bypass the local to global converter as there we don't have access to what we want. that service will/should stop existing.
        if (
          localToGlobalMap.AtomicObject is ITransformable transformable // and ICurve
          && localToGlobalMap.Matrix.Count > 0
          && localToGlobalMap.AtomicObject["units"] is string units
        )
        {
          //TODO TransformTo will be deprecated as it's dangerous and requires ID transposing which is wrong!
          //ID needs to be copied to the new instance
          var id = localToGlobalMap.AtomicObject.id;
          ITransformable? newTransformable = null;
          foreach (var mat in localToGlobalMap.Matrix)
          {
            transformable.TransformTo(new Transform() { matrix = mat, units = units }, out newTransformable);
            transformable = newTransformable; // we need to keep the reference to the new object, as we're going to use it in the cache
          }

          localToGlobalMap.AtomicObject = (newTransformable as Base)!;
          localToGlobalMap.AtomicObject.id = id; // restore the id, as it's used in the cache
          localToGlobalMap.Matrix = new HashSet<Matrix4x4>(); // flush out the list, as we've applied the transforms already
        }

        // actual conversion happens here!

        var elem = ConvertToArchicadElement(localToGlobalMap.AtomicObject, localToGlobalMap.Matrix);
        if (!elem.Empty)
        {
          results.Add(elem);
        }

        /*var result = converter.Convert(localToGlobalMap.AtomicObject);
        if (result is DirectShapeDefinitionWrapper)
        {
          // direct shape creation happens here
          DirectShape directShapes = localToGlobalDirectShapeConverter.Convert(
            (localToGlobalMap.AtomicObject, localToGlobalMap.Matrix)
          );

          if (localToGlobalMap.AtomicObject is IRawEncodedObject and Base myBase)
          {
            postBakePaintTargets.Add((directShapes, myBase.applicationId ?? myBase.id.NotNull()));
          }
        }
        else
        {
          throw new ConversionException($"Failed to cast {result.GetType()} to direct shape definition wrapper.");
        }*/
      }
      catch (Exception ex) when (!ex.IsFatal())
      {
        // TODO
      }
    }

    //**********************************************************************************


    /*List<TraversalContext> objectsToConvertTc = DefaultTraversal.CreateTraversalFunc()
        .Traverse(rootObject)
        .Where(ctx => ctx.Current is not Collection)
        .ToList();

    var batchSize = 1; // Adjust based on performance testing
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

    /*var results = new List<ArchicadElement>();
    foreach (var context in objectsToConvertTc)
    {
      cancellationToken.ThrowIfCancellationRequested();
      var elem = ConvertToArchicadElement(context.Current);
      if (!elem.Empty)
      {
        results.Add(elem);
      }
    }*/

    await PrintElementsAsync(results.ToList());

    var rootDir = @"C:\poc";
    var outDir = @"C:\poc\out";
    await RunXmlConvertersAsync(rootDir, outDir);
  }

  public IReadOnlyCollection<RenderMaterialProxy>? TryGetRenderMaterialProxies(Base root) =>
    TryGetProxies<RenderMaterialProxy>(root, "renderMaterialProxies");

  private IReadOnlyCollection<T>? TryGetProxies<T>(Base root, string key) =>
    (root[key] as List<object>)?.Cast<T>().ToList();

  private ArchicadMaterial? GetMaterialById(string appId)
  {
    //string matName = "speckle_default_material";
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
      /*if (_elementMaterials.TryGetValue(meshId, out var materialId))
      {
        if (_materialTable.TryGetValue(materialId, out var material)) 
        {
          matName = material.Name;
          if (addedMaterials.Add(matName))
          {
            elem.AddMaterial(material);
          }
        }
      }*/

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
