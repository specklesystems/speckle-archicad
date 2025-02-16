#include "HostObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "RootObjectUnpacker.h"


void HostObjectBuilder::Build(const nlohmann::json& rootObject)
{
	RootObjectUnpacker unpacker{};
	auto unpackedMeshes = unpacker.UnpackMeshes(rootObject);

	for (const auto& mesh : unpackedMeshes)
	{
		CONNECTOR.GetSpeckleToHostConverter().CreateMorph(mesh);
	}
}
