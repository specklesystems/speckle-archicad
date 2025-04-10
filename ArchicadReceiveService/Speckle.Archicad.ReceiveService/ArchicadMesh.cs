using System.Text;
using Speckle.Objects.Geometry;

namespace Speckle.Archicad.ReceiveService;

public class ArchicadMesh
{
  public List<ArchicadVertex> Vertices { get; }
  public List<ArchicadEdge> Edges { get; }
  public List<ArchicadPolygon> Polygons { get; }
  public string MaterialName { get; }

  public ArchicadMesh(Mesh mesh, string materialName = "speckle_default_material")
  {
    Vertices = new List<ArchicadVertex>();
    Edges = new List<ArchicadEdge>();
    Polygons = new List<ArchicadPolygon>();
    MaterialName = materialName;

    // Parse vertices
    for (int i = 0; i < mesh.vertices.Count; i += 3)
    {
      double x = mesh.vertices[i];
      double y = mesh.vertices[i + 1];
      double z = mesh.vertices[i + 2];
      Vertices.Add(new ArchicadVertex(x, y, z));
    }

    // Parse faces and generate edges
    for (int i = 0; i < mesh.faces.Count;)
    {
      var edgeIndeices = new List<int>();
      int faceSize = mesh.faces[i++];
      for (int j = 0; j < faceSize; j++)
      {
        int start = mesh.faces[i + j];
        int end = mesh.faces[i + ((j + 1) % faceSize)];
        var edgeIndex = AddEdge(start, end);
        edgeIndeices.Add(edgeIndex);
      }
      i += faceSize;
      Polygons.Add(new ArchicadPolygon(edgeIndeices, MaterialName));
    }
  }
  public int AddEdge(int start, int end)
  {
    for (int i = 0; i < Edges.Count; i++)
    {
      var edge = Edges[i];
      if (edge.Start == start && edge.End == end)
      {
        edge.Count++;
        return i + 1;
      }

      if (edge.Start == end && edge.End == start)
      {
        edge.Count++;
        return -(i + 1);
      }
    }

    Edges.Add(new ArchicadEdge(start, end));
    return Edges.Count;
  }

  public void Scale(double scaling)
  {
    foreach (var v in Vertices)
    {
      v.X *= scaling;
      v.Y *= scaling;
      v.Z *= scaling;
    }
  }

  public override string ToString()
  {
    var sb = new StringBuilder();

    // Vertices
    foreach (var vertex in Vertices)
    {
      sb.AppendLine(vertex.ToString());
    }
    sb.AppendLine();

    // Edges
    foreach (var edge in Edges)
    {
      sb.AppendLine(edge.ToString());
    }
    sb.AppendLine();

    // Polygons
    foreach (var polygon in Polygons)
    {
      sb.AppendLine(polygon.ToString());
    }

    // Final footer
    sb.AppendLine();
    sb.AppendLine("BODY 4");
    sb.Append("BASE");
    sb.AppendLine();

    return sb.ToString();
  }
}
