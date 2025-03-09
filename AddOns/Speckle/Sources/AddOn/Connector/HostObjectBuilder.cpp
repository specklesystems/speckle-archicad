#include "HostObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "RootObjectUnpacker.h"
#include "ReceiveConversionResult.h"
#include "UnpackedElement.h"
#include "LibpartBuilder.h"
#include "JsonFileWriter.h"


HostObjectBuilderResult HostObjectBuilder::Build(const nlohmann::json& rootObject, const std::string& projectName, const std::string& modelName)
{
	std::ostringstream oss;
	oss << "Project " << projectName << ": Model " << modelName;
	std::string baseGroupName = oss.str();

	auto bakedMaterials = BakeMaterials(rootObject, baseGroupName);
	auto buildResult = BakeObjects(rootObject, baseGroupName, bakedMaterials);

	return buildResult;
}

std::map<std::string, std::string> HostObjectBuilder::BakeMaterials(const nlohmann::json& rootObject, const std::string& baseGroupName)
{
	std::map<std::string, std::string> materialTable;
	std::map<std::string, int> createdMaterials;

	RootObjectUnpacker unpacker{};
	auto unpackedMaterialProxies = unpacker.UnpackRenderMaterialProxies(rootObject);

	for (const auto& proxy : unpackedMaterialProxies)
	{
		std::ostringstream oss;
		oss << baseGroupName << "_" << std::to_string(proxy.value.diffuse);
		std::string materialName = oss.str();

		int materialIndex = 0;
		if (createdMaterials.find(materialName) != createdMaterials.end())
		{
			materialIndex = createdMaterials[materialName];
		}
		else
		{
			materialIndex = CONNECTOR.GetSpeckleToHostConverter().CreateMaterial(proxy.value, materialName);
			createdMaterials[materialName] = materialIndex;
		}

		for (const auto& elementId : proxy.objects)
		{
			materialTable[elementId] = materialName;
		}
	}

	return materialTable;
}

HostObjectBuilderResult HostObjectBuilder::BakeObjects(const nlohmann::json& rootObject, const std::string& baseGroupName, const std::map<std::string, std::string>& materialTable)
{
	RootObjectUnpacker unpacker{};
	auto unpackedElements = unpacker.UnpackElements(rootObject, materialTable);
	LibpartBuilder libpartBuilder(baseGroupName);

	libpartBuilder.CreateLibParts(unpackedElements);
	libpartBuilder.PlaceLibparts();

	return { libpartBuilder.bakedObjectIds, libpartBuilder.conversionResults };
}

void HostObjectBuilder::GroupObjects(const std::vector<std::string>& objectIds)
{
	CONNECTOR.GetSpeckleToHostConverter().CreateGroup(objectIds);
}
