#include "HostObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "RootObjectUnpacker.h"
#include "ReceiveConversionResult.h"
#include "LibpartBuilder.h"
#include "Matrix_44.h"
#include "Units.h"
#include "ARGBColorConverter.h"
#include "RootObjectUnpacker.h"

#include "StopWatch.h"
#include "JsonFileWriter.h"

static std::string RemoveInvalidChars(const std::string& input)
{
	std::string output;
	const std::string invalidChars = "<>:\"/\\|?*";

	for (char c : input)
	{
		output += (invalidChars.find(c) == std::string::npos) ? c : '-';
	}

	return output;
}

// TODO
// this class is silly now
// should move functionality from RootObjectBuilder to here

HostObjectBuilderResult HostObjectBuilder::Build(const nlohmann::json& rootObject, const std::string& projectName, const std::string& modelName)
{
	HostObjectBuilderResult hostObjectBuilderResult;

	try
	{
		std::ostringstream oss;
		oss << "Project " << projectName << " - Model " << modelName;
		std::string baseGroupName = oss.str();
		baseGroupName = RemoveInvalidChars(baseGroupName);

		RootObjectUnpacker rootObjectUnpacker(std::make_shared<Node>(rootObject, nullptr), baseGroupName);
		rootObjectUnpacker.Unpack();
		hostObjectBuilderResult = rootObjectUnpacker.GetHostObjectBuilderResult();
	}
	catch (const std::exception& ex)
	{
		// TODO handle exception
		auto what = ex.what();
		std::cout << what;
	}

	// TODO return the real result
	return hostObjectBuilderResult;
}
