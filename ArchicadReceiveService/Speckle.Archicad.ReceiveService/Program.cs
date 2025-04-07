using Speckle.Objects.Geometry;
using Speckle.Sdk;
using Speckle.Sdk.Host;
using Speckle.Sdk.Models;

namespace Speckle.Archicad.ReceiveService;

public static class Program
{

  public static async Task Main(string[] args)
  {
    string projectId = args[0];
    string versionId = args[1];
    string accountId = args[2];

    var serviceProvider = GetServiceProvider();
    var archicadReceiver = serviceProvider.GetRequiredService<ReceiveOperation>();

    await archicadReceiver.Receive(projectId, versionId, accountId);

  }
  
  private static ServiceProvider GetServiceProvider()
  {
    TypeLoader.Initialize(typeof(Base).Assembly, typeof(Point).Assembly);
    var serviceCollection = new ServiceCollection();
    serviceCollection.AddSingleton<ReceiveOperation>();
    serviceCollection.AddSingleton<IHostObjectBuilder, HostObjectBuilder>();
    serviceCollection.AddSpeckleSdk( HostApplications.Archicad, HostAppVersion.v3, "v3.0.0");
    return serviceCollection.BuildServiceProvider();
  }
  
}
