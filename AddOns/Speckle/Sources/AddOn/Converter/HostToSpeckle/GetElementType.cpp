#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"
#include "ElementTypeToStringConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

std::string HostToSpeckleConverter::GetElementType(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	return ElementTypeToStringConverter::ElementTypeToString(apiElem.header.type.typeID);
}
