#include "SpeckleToHostConverter.h"
#include "CheckError.h"
#include "ConverterUtils.h"

std::string SpeckleToHostConverter::CreateLibPart(const Mesh& /*mesh*/, const int /*materialIndex*/, const std::string& /*baseGroupName*/, int /*runningNumber*/)
{
	return "dummy";
}
