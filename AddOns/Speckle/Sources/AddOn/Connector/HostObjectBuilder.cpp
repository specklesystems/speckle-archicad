#include "HostObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "RootObjectUnpacker.h"
#include "ReceiveConversionResult.h"
#include <string>
#include <format>
#include <iostream>
#include <set>


HostObjectBuilderResult HostObjectBuilder::Build(const nlohmann::json& rootObject, const std::string& projectName, const std::string& modelName)
{
	std::ostringstream oss;
	oss << "Project " << projectName << ": Model " << modelName;
	std::string baseGroupName = oss.str();

	auto bakedMaterials = BakeMaterials(rootObject, baseGroupName);

	auto buildResult = BakeObjects(rootObject, baseGroupName, bakedMaterials);
	GroupObjects(buildResult.bakedObjectIds);
	return buildResult;
}

std::map<std::string, int> HostObjectBuilder::BakeMaterials(const nlohmann::json& rootObject, const std::string& baseGroupName)
{
	std::map<std::string, int> materialTable;
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
			materialTable[elementId] = materialIndex;
		}
	}

	return materialTable;
}

HostObjectBuilderResult HostObjectBuilder::BakeObjects(const nlohmann::json& rootObject, const std::string& baseGroupName, const std::map<std::string, int>& materialTable)
{
	std::vector<ReceiveConversionResult> conversionResults;
	std::vector<std::string> bakedObjectIds;

	RootObjectUnpacker unpacker{};
	auto unpackedMeshes = unpacker.UnpackMeshes(rootObject);

	CONNECTOR.GetProcessWindow().Init("Converting elements", static_cast<int>(unpackedMeshes.size()));
	int elemCount = 0;

	for (const auto& mesh : unpackedMeshes)
	{
		elemCount++;
		CONNECTOR.GetProcessWindow().SetProcessValue(elemCount);
		ReceiveConversionResult conversionResult{};

		try
		{
			int materialIndex = materialTable.at(mesh.applicationId);
			auto objectId = CONNECTOR.GetSpeckleToHostConverter().CreateMorph(mesh, materialIndex, baseGroupName);
			bakedObjectIds.push_back(objectId);
		}
		catch (const ArchiCadApiException& ae)
		{
			conversionResult.status = ConversionResultStatus::CONVERSION_ERROR;
			conversionResult.error.message = ae.what();
		}
		catch (const SpeckleConversionException& se)
		{
			conversionResult.status = ConversionResultStatus::CONVERSION_ERROR;
			conversionResult.error.message = se.what();
		}

		conversionResults.push_back(conversionResult);

		if (CONNECTOR.GetProcessWindow().IsProcessCanceled())
		{
			CONNECTOR.GetProcessWindow().Close();
			throw UserCancelledException("The user cancelled the receive operation");
		}
	}

	return { bakedObjectIds, conversionResults };
}

void HostObjectBuilder::GroupObjects(const std::vector<std::string>& objectIds)
{
	CONNECTOR.GetSpeckleToHostConverter().CreateGroup(objectIds);
}
