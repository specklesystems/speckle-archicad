#include "HostObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "RootObjectUnpacker.h"
#include "ReceiveConversionResult.h"
#include "UnpackedElement.h"
#include <string>
#include <format>
#include <iostream>
#include <set>

#include "LibpartBuilder.h"
#include "JsonFileWriter.h"
#include <StopWatch.h>


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

HostObjectBuilderResult HostObjectBuilder::BakeObjects(const nlohmann::json& rootObject, const std::string& /*baseGroupName*/, const std::map<std::string, std::string>& materialTable)
{
	std::vector<ReceiveConversionResult> conversionResults;
	std::vector<std::string> bakedObjectIds;

	RootObjectUnpacker unpacker{};
	auto unpackedElements = unpacker.UnpackElements(rootObject, materialTable);
	LibpartBuilder libpartBuilder{};

	//CONNECTOR.GetProcessWindow().Init("Converting elements", static_cast<int>(unpackedDisplayValues.size()));
	

	/*for (auto& displayValue : unpackedDisplayValues)
	{
		for (auto& unpackedMesh : displayValue)
		{
			try
			{
				std::string materialName = materialTable.at(unpackedMesh.mesh.applicationId);
				unpackedMesh.materialName = materialName;
			}
			catch (const std::exception& ex)
			{
				std::string msg = ex.what();
				std::cout << msg;
			}
			
		}
	}*/
	
	/*for (const auto& dv : unpackedDisplayValues)
	{
		elemCount++;

		CONNECTOR.GetProcessWindow().SetProcessValue(elemCount);
		ReceiveConversionResult conversionResult{};

		try
		{	
			auto objectId = libpartBuilder.CreateLibPart(dv, baseGroupName, elemCount);
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
		}*
	}*/

	libpartBuilder.CreateLibParts(unpackedElements);
	libpartBuilder.PlaceLibparts();

	return { bakedObjectIds, conversionResults };
}

void HostObjectBuilder::GroupObjects(const std::vector<std::string>& objectIds)
{
	CONNECTOR.GetSpeckleToHostConverter().CreateGroup(objectIds);
}
