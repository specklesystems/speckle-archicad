using System.Text;

namespace Speckle.Archicad.ReceiveService;

public class ArchicadPolygon
{
  public List<int> EdgeIndices { get; }
  public int Size { get; }
  public string MaterialName { get; }

  public ArchicadPolygon(List<int> edgeIndices, string materialName)
  {
    MaterialName = materialName;
    Size = edgeIndices.Count;
    EdgeIndices = edgeIndices;
  }

  public override string ToString()
  {
    var sb = new StringBuilder();
    sb.AppendLine($"MATERIAL \"{MaterialName}\"");
    sb.Append($"PGON {Size}, 0, -1");

    foreach (var index in EdgeIndices)
    {
      //var i = index > 0 ? index + 1 : index - 1; 
      sb.Append($", {index}");
    }

    return sb.ToString();
  }
}
