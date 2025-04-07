using Speckle.Sdk.Api;
using Speckle.Sdk.Credentials;
using Version = Speckle.Sdk.Api.GraphQL.Models.Version;

namespace Speckle.Archicad.ReceiveService;

/// <summary>
/// This looks similar to the ReceiveOperation in connectors common
/// </summary>
/// <param name="clientFactory"></param>
/// <param name="accountManager"></param>
/// <param name="operations"></param>
public sealed class ReceiveOperation(IClientFactory clientFactory, IAccountManager accountManager, IOperations operations, IHostObjectBuilder hostObjectBuilder)
{
  public async Task Receive(string projectId, string versionId, string accountId, CancellationToken cancellationToken = default)
  {
    var account = accountManager.GetAccount(accountId);
    using var client = clientFactory.Create(account);

    Version version = await client.Version.Get(versionId, projectId, cancellationToken);


    var rootObject = await operations.Receive2(new(account.serverInfo.url), projectId, version.referencedObject, account.token, null, cancellationToken);

  
    hostObjectBuilder.Build(rootObject, cancellationToken);
  }
  
}
