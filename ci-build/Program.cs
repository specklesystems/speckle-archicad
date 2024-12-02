using System.IO.Compression;
using Build;
using GlobExpressions;
using static Bullseye.Targets;
using static SimpleExec.Command;

const string CLEAN = "clean";
const string BUILD = "build";
const string ZIP = "zip";
const string RESTORE_TOOLS = "restore-tools";
const string BUILD_SERVER_VERSION = "build-server-version";
const string RUN_CMAKE = "build-cmake";

Target(
  CLEAN,
  ForEach("**/output"),
  dir =>
  {
    IEnumerable<string> GetDirectories(string d)
    {
      return Glob.Directories(".", d);
    }

    void RemoveDirectory(string d)
    {
      if (Directory.Exists(d))
      {
        Console.WriteLine(d);
        Directory.Delete(d, true);
      }
    }

    foreach (var d in GetDirectories(dir))
    {
      RemoveDirectory(d);
    }
  }
);

Target(
  RESTORE_TOOLS,
  () =>
  {
    Run("dotnet", "tool restore");
  }
);

Target(
  BUILD_SERVER_VERSION,
  DependsOn(RESTORE_TOOLS),
  () =>
  {
    Run("dotnet", "tool run dotnet-gitversion /output json /output buildserver");
  }
);

Target(RUN_CMAKE, Consts.SupportedVersions, s =>
{
  Run("cmake", $"-G \"Visual Studio 17 2022\" -T v142 -A \"x64\" -DAC_ADDON_LANGUAGE=\"INT\" -DAC_API_DEVKIT_DIR=\"Libs\\acapi{s}\" -B build\\{s} -DCMAKE_BUILD_TYPE=Release");
});

Target(
  BUILD,
  DependsOn(RUN_CMAKE),
  Consts.SupportedVersions,
  s =>
  {
    var version = Environment.GetEnvironmentVariable("GitVersion_FullSemVer") ?? "3.0.0-localBuild";
    var fileVersion = Environment.GetEnvironmentVariable("GitVersion_AssemblySemFileVer") ?? "3.0.0.9999";
    Console.WriteLine($"Version: {version} & {fileVersion}");
    Run("msbuild", $"./build/{s}/archicad-speckle.sln /p:Configuration=Release /p:Version={version} /p:FileVersion={fileVersion}");
  }
);

Target(
  ZIP,
  DependsOn(BUILD),
  Consts.InstallerManifests,
  x =>
  {
    var outputDir = Path.Combine(".", "output");
    var slugDir = Path.Combine(outputDir, x.HostAppSlug);

    Directory.CreateDirectory(outputDir);
    Directory.CreateDirectory(slugDir);

    foreach (var asset in x.Projects)
    {
      var fullPath = Path.Combine(".", asset.OutputPath);
      if (!Directory.Exists(fullPath))
      {
        throw new InvalidOperationException("Could not find: " + fullPath);
      }

      var assetName = asset.ConnectorVersion;
      var connectorDir = Path.Combine(slugDir, assetName);
      Directory.CreateDirectory(connectorDir);
      foreach (var directory in Directory.EnumerateDirectories(fullPath, asset.GlobPattern, SearchOption.AllDirectories))
      {
        Directory.CreateDirectory(directory.Replace(fullPath, connectorDir));
      }

      foreach (var file in Directory.EnumerateFiles(fullPath, asset.GlobPattern, SearchOption.AllDirectories))
      {
        Console.WriteLine(file);
        var destFileName = file.Replace(fullPath, connectorDir);
        File.Copy(file, destFileName, true);
      }
    }

    var outputPath = Path.Combine(outputDir, $"{x.HostAppSlug}.zip");
    File.Delete(outputPath);
    Console.WriteLine($"Zipping: '{slugDir}' to '{outputPath}'");
    ZipFile.CreateFromDirectory(slugDir, outputPath);
    // Directory.Delete(slugDir, true);
  }
);

Target("default", DependsOn(ZIP), () => Console.WriteLine("Done!"));

await RunTargetsAndExitAsync(args).ConfigureAwait(true);
