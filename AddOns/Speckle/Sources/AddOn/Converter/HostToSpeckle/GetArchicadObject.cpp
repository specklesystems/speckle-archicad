#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"


ArchicadObject HostToSpeckleConverter::GetArchicadObject(const std::string& elemId, SendConversionResult& conversionResult)
{
	ArchicadObject archicadObject{};
    
    archicadObject.applicationId = elemId;
    archicadObject.name = GetElementName(elemId);
    archicadObject.type = GetElementType(elemId);
    archicadObject.level = GetElementLevel(elemId);
    conversionResult.sourceType = archicadObject.type;
    conversionResult.sourceId = elemId;

    archicadObject.elements = GetElementChildren(elemId);
    if (archicadObject.elements.empty())
    {
        archicadObject.displayValue = GetElementBody(elemId);
    }
    archicadObject.properties = GetElementProperties(elemId);

    conversionResult.resultId = "";
    conversionResult.resultType = "ArchicadObject";

	return archicadObject;
}
