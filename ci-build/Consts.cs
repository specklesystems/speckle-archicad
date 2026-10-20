namespace Build;

public static class Consts
{
    public static readonly string[] SupportedVersions = new string[] { "27", "28", "29", "30" };
    public static readonly InstallerProject[] InstallerManifests =
    {
        new(
            "archicad",
            [
                new("archicad27", "build/27/INT/Release", "*.apx"),
                new("archicad28", "build/28/INT/Release", "*.apx"),
                new("archicad29", "build/29/INT/Release", "*.apx"),
                new("archicad30", "build/30/INT/Release", "*.apx"),
            ]
        ),
    };
}

public readonly record struct InstallerProject(
    string HostAppSlug,
    IReadOnlyList<InstallerAsset> Projects
)
{
    public override string ToString() => $"{HostAppSlug}";
}

public readonly record struct InstallerAsset(
    string ConnectorVersion,
    string OutputPath,
    string GlobPattern = "*"
);
