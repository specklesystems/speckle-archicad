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


HostObjectBuilderResult HostObjectBuilder::Build(const nlohmann::json& rootObject, const std::string& projectName, const std::string& modelName)
{
	std::ostringstream oss;
	oss << "Project " << projectName << ": Model " << modelName;
	std::string baseGroupName = oss.str();

	// TODO Bake Materials here

	auto buildResult = BakeObjects(rootObject, baseGroupName);
	GroupObjects(buildResult.bakedObjectIds);
	return buildResult;
}

HostObjectBuilderResult HostObjectBuilder::BakeObjects(const nlohmann::json& rootObject, const std::string& baseGroupName)
{
	// TODO Remove static material
	Material mat;
	int matind = CONNECTOR.GetSpeckleToHostConverter().CreateMaterial("speckle", mat);

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
			auto objectId = CONNECTOR.GetSpeckleToHostConverter().CreateMorph(mesh, matind, baseGroupName);
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
