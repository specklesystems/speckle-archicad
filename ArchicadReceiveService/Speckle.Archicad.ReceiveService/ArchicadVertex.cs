namespace Speckle.Archicad.ReceiveService;

public class ArchicadVertex
{
  public double X { get; set; }
  public double Y { get; set; }
  public double Z { get; set; }

  public ArchicadVertex(double x, double y, double z)
  {
    X = x;
    Y = y;
    Z = z;
  }

  public override string ToString()
  {
    return $"VERT {X:F6}, {Y:F6}, {Z:F6}";
  }
}
