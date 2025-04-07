using Speckle.InterfaceGenerator;
using Speckle.Objects.Data;
using Speckle.Objects.Geometry;
using Speckle.Sdk.Models;
using Speckle.Sdk.Models.GraphTraversal;
using Speckle.Sdk.Models.Instances;

namespace Speckle.Archicad.ReceiveService;

[GenerateAutoInterface]
public class HostObjectBuilder : IHostObjectBuilder
{
  public void Build(
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
         MeshesToHost([m]);
         break;
       case InstanceProxy p:
         Console.WriteLine(p.id);
         break;
       case DataObject d:
         MeshesToHost(d.displayValue.OfType<Mesh>());
         break;
      }
    }
  }

  private void MeshesToHost(IEnumerable<Mesh> meshes)
  {
    foreach (var mesh in meshes)
    {
      Console.WriteLine(mesh.id);
    }
  }
}
