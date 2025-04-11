using Speckle.Objects.Other;
using Speckle.Sdk.Models.GraphTraversal;
using Speckle.Sdk.Models.Instances;
using Speckle.Sdk.Models.Proxies;

namespace Speckle.Archicad.ReceiveService.Operations.Receive;

public record RootObjectUnpackerResult(
  IReadOnlyCollection<TraversalContext> ObjectsToConvert,
  IReadOnlyCollection<InstanceDefinitionProxy>? DefinitionProxies,
  IReadOnlyCollection<GroupProxy>? GroupProxies,
  IReadOnlyCollection<RenderMaterialProxy>? RenderMaterialProxies,
  IReadOnlyCollection<ColorProxy>? ColorProxies
);
