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
    archicadObject.level = GetElementLevel(elemId);
    conversionResult.sourceType = archicadObject.type;
    conversionResult.sourceId = elemId;  

    auto apiElem = ConverterUtils::GetElement(elemId);
    auto apiElemMemo = ConverterUtils::GetElementMemo(elemId);

    SendConversionResult segmentConversionResult{};
    if (archicadObject.type == "Beam")
    {
        for (UInt32 i = 0; i < apiElem.beam.nSegments; i++)
        {
            auto segment = (apiElemMemo.beamSegments)[i];
            auto segmentId = APIGuidToString(segment.head.guid).ToCStr().Get();
            archicadObject.elements.push_back(GetArchicadObject(segmentId, segmentConversionResult));
        }
    }
    else if (archicadObject.type == "Column")
    {
        for (UInt32 i = 0; i < apiElem.column.nSegments; i++)
        {
            auto segment = (apiElemMemo.columnSegments)[i];
            auto segmentId = APIGuidToString(segment.head.guid).ToCStr().Get();
            archicadObject.elements.push_back(GetArchicadObject(segmentId, segmentConversionResult));
        }
    }
    else
    {
        archicadObject.displayValue = GetElementBody(elemId);
        archicadObject.properties = GetElementProperties(elemId);
    }

    conversionResult.resultId = "";
    conversionResult.resultType = "ArchicadObject";

	return archicadObject;
}
