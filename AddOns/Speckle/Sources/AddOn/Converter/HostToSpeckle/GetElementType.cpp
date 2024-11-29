#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"
#include "ElementTypeToStringConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

std::string HostToSpeckleConverter::GetElementType(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);

#if defined(AC25)
	auto elemType = apiElem.header.typeID;
#else
	auto elemType = apiElem.header.type.typeID;
#endif

	return ElementTypeToStringConverter::ElementTypeToString(elemType);
}
