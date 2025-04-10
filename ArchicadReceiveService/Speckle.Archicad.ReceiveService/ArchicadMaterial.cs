using System.Globalization;
using Speckle.Objects.Other;

namespace Speckle.Archicad.ReceiveService;

public class ArchicadMaterial
{
  // RGB color components
  public double R { get; set; }
  public double G { get; set; }
  public double B { get; set; }

  // Material properties
  public double Ambient { get; set; } = 1.0;
  public double Diffuse { get; set; } = 1.0;
  public double Specular { get; set; }
  public double Transparent { get; set; }

  public int Shining { get; set; }
  public int TransparencyAttenuation { get; set; }

  public string Name { get; set; }

  public ArchicadMaterial(string name, RenderMaterial renderMaterial)
  {
    Name = name;
    UnpackARGB(renderMaterial.diffuse, out _, out double r, out double g, out double b);
    R = r;
    G = g; 
    B = b;

    Transparent = 1.0 - renderMaterial.opacity;
    Shining = (int)((1.0 - renderMaterial.roughness) * 100);
  }

  public override string ToString()
  {
    // Ensure decimal point is always a dot, regardless of culture
    var format = CultureInfo.InvariantCulture;

    return $"DEFINE MATERIAL \"{Name}\" 1,\n" +
           $"        {R.ToString("0.####", format)}, {G.ToString("0.####", format)}, {B.ToString("0.####", format)},! surface RGB [0.0..1.0]\n" +
           $"        {Ambient.ToString("0.####", format)}, {Diffuse.ToString("0.####", format)}, {Specular.ToString("0.####", format)}, {Transparent.ToString("0.####", format)}, ! ambient, diffuse, specular, transparent [0..1]\n" +
           $"        {Shining}, ! shining [0..100]\n" +
           $"        {TransparencyAttenuation} ! transparency attenuation [0..4]\n\n";
  }

  private static void UnpackARGB(int argb, out double a, out double r, out double g, out double b)
  {
    a = ((argb >> 24) & 0xFF) / 255.0;
    r = ((argb >> 16) & 0xFF) / 255.0;
    g = ((argb >> 8) & 0xFF) / 255.0;
    b = (argb & 0xFF) / 255.0;
  }
}
