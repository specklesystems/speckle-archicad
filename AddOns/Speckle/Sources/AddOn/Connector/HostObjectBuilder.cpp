#include "HostObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "RootObjectUnpacker.h"
#include "ReceiveConversionResult.h"


void HostObjectBuilder::Build(const nlohmann::json& rootObject, const std::string& projectName, const std::string& modelName)
{
	std::cout << projectName;
	std::cout << modelName;

	BakeObjects(rootObject);
}

void HostObjectBuilder::BakeObjects(const nlohmann::json& rootObject)
{
	std::vector<ReceiveConversionResult> conversionResults;

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
			CONNECTOR.GetSpeckleToHostConverter().CreateMorph(mesh);
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
			throw UserCancelledException("The user cancelled the send operation");
		}
	}
}
