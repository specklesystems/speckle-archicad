#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"


std::vector<ArchicadObject> HostToSpeckleConverter::GetElementChildren(const std::string& elemId)
{
	auto elementType = GetElementType(elemId);
	std::vector<ArchicadObject> children;
    auto apiElem = ConverterUtils::GetElement(elemId);
    auto apiElemMemo = ConverterUtils::GetElementMemo(elemId);
	SendConversionResult segmentConversionResult{};

    if (elementType == "Beam")
    {
        for (UInt32 i = 0; i < apiElem.beam.nSegments; i++)
        {
            auto segment = (apiElemMemo.beamSegments)[i];
            auto segmentId = APIGuidToString(segment.head.guid).ToCStr().Get();
            children.push_back(GetArchicadObject(segmentId, segmentConversionResult));
        }
    }
    else if (elementType == "Column")
    {
        for (UInt32 i = 0; i < apiElem.column.nSegments; i++)
        {
            auto segment = (apiElemMemo.columnSegments)[i];
            auto segmentId = APIGuidToString(segment.head.guid).ToCStr().Get();
            children.push_back(GetArchicadObject(segmentId, segmentConversionResult));
        }
    }

    return children;
}
