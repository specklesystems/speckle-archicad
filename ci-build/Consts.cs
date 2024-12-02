namespace Build;

public static class Consts
{
  public static readonly string[] SupportedVersions = new string[] { "27", "28"};
  public static readonly string[] Solutions = ["build_27/speckle-archicad.sln", "build_28/speckle-archicad.sln"];

  public static readonly InstallerProject[] InstallerManifests =
  {
    new("archicad", [new("archicad27", "build/27/INT/Release", "*.apx"), new("archicad28", "build/28/INT/Release", "*.apx")])
  };
}

public readonly record struct InstallerProject(string HostAppSlug, IReadOnlyList<InstallerAsset> Projects)
{
  public override string ToString() => $"{HostAppSlug}";
}

public readonly record struct InstallerAsset(string ConnectorVersion, string OutputPath, string GlobPattern = "*");
