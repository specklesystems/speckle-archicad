#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"


ArchicadObject HostToSpeckleConverter::GetArchicadObject(const std::string& elemId, SendConversionResult& conversionResult, bool includeProperties)
{
	ArchicadObject archicadObject{};
    
    archicadObject.applicationId = elemId;
    archicadObject.name = GetElementName(elemId);
    archicadObject.type = GetElementType(elemId);
    archicadObject.level = GetElementLevel(elemId);
    conversionResult.sourceType = archicadObject.type;
    conversionResult.sourceId = elemId;

    archicadObject.elements = GetElementChildren(elemId, includeProperties);
    if (archicadObject.elements.empty())
    {
        archicadObject.displayValue = GetElementBody(elemId);
    }

    archicadObject.properties = includeProperties ? GetElementProperties(elemId) : nlohmann::json::object();

    conversionResult.resultId = "";
    conversionResult.resultType = "ArchicadObject";

	return archicadObject;
}
