#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

ArchicadObject HostToSpeckleConverter::GetArchicadObject(const std::string& elemId, SendConversionResult& conversionResult)
{
	ArchicadObject archicadObject{};

    archicadObject.applicationId = elemId;
    archicadObject.name = GetElementName(elemId);
    archicadObject.type = GetElementType(elemId);
    conversionResult.sourceType = archicadObject.type;
    conversionResult.sourceId = elemId;
    archicadObject.displayValue = GetElementBody(elemId);
    conversionResult.resultId = "";
    conversionResult.resultType = "Mesh";
    archicadObject.level = GetElementLevel(elemId);
    archicadObject.properties = GetElementProperties(elemId);

	return archicadObject;
}
