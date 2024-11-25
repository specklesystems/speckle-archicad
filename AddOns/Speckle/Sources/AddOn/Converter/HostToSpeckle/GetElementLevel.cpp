#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

std::string HostToSpeckleConverter::GetElementLevel(const std::string& elemId)
{
	auto apielem = ConverterUtils::GetElement(elemId);
	auto floorInd = apielem.header.floorInd;
	return "Level " + std::to_string(floorInd);
}
