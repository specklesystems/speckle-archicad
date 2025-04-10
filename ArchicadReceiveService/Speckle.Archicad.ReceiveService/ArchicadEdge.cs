namespace Speckle.Archicad.ReceiveService;

public class ArchicadEdge
{
  public int Start { get; }
  public int End { get; }
  public int Count { get; set; }
  public bool Visible { get; set; }

  public ArchicadEdge(int start, int end)
  {
    Start = start;
    End = end;
    Count = 1;
  }

  public override string ToString()
  {
    int visibilityFlag = Visible ? 0 : 1;
    return $"EDGE {Start + 1}, {End + 1}, -1, -1, {visibilityFlag}";
  }
}
