using Speckle.InterfaceGenerator;
using Speckle.Objects.Data;
using Speckle.Objects.Geometry;
using Speckle.Sdk.Models;
using Speckle.Sdk.Models.GraphTraversal;
using Speckle.Sdk.Models.Instances;

namespace Speckle.Archicad.ReceiveService;

[GenerateAutoInterface]
public sealed class HostObjectBuilder : IHostObjectBuilder, IDisposable
{


  public async Task Build(
    Base rootObject,
    CancellationToken cancellationToken
  )
  {
    
    //Processing of the root object proxies (like the material proxies, and instance proxies)

    // var renderMaterialProxy = rootObject["renderMaterialProxies"] as RenderMaterialProxy;
    // var instanceProxies = rootObject["instanceDefinitionProxies"] as IReadOnlyCollection<InstanceDefinitionProxy> ?? [];
    
    var traversalFunc = DefaultTraversal.CreateTraversalFunc();

    foreach (var context in traversalFunc.Traverse(rootObject))
    {
      cancellationToken.ThrowIfCancellationRequested();
      
      var current = context.Current;

      
      //Take current object, write a gsm file
      switch (current)
      {
       case Mesh m:
         await MeshesToHost([m]);
         break;
       case InstanceProxy p:
         Console.WriteLine(p.id);
         break;
       case DataObject d:
         await MeshesToHost(d.displayValue.OfType<Mesh>());
         break;
      }
    }
  }

  private readonly HttpClient _client = new HttpClient();
  private static readonly Uri s_archicadService = new Uri("localhost:8080");
  
  private async Task MeshesToHost(IEnumerable<Mesh> meshes)
  {
    foreach (var mesh in meshes)
    {
      Console.WriteLine(mesh.id);
      //Example of making a HTTP request
      var res = await _client.GetAsync(s_archicadService);
      res.EnsureSuccessStatusCode();
      
    }
  }

  public void Dispose()
  {
    _client.Dispose();
  }
}
