#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

ArchicadLevel HostToSpeckleConverter::GetElementLevel(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	// Story table (settings fetch + name conversion) is cached per send.
	return ConverterUtils::GetStoryLevel(apiElem.header.floorInd);
}
