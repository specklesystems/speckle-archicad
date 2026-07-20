#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

namespace
{
	// Owns the memo handles for the duration of the segment walk (the recursive
	// GetArchicadObject calls below can throw).
	struct MemoGuard
	{
		API_ElementMemo memo{};
		~MemoGuard() { ACAPI_DisposeElemMemoHdls(&memo); }
	};
}

std::vector<ArchicadObject> HostToSpeckleConverter::GetElementChildren(const std::string& elemId, bool includeProperties)
{
	auto elementType = GetElementType(elemId);
	std::vector<ArchicadObject> children;

	const bool isBeam = (elementType == "Beam");
	const bool isColumn = (elementType == "Column");
	if (!isBeam && !isColumn)
		return children; // only beams/columns have hosted segments — skip the memo fetch

	auto apiElem = ConverterUtils::GetElement(elemId);
	MemoGuard guard;
	ACAPI_Element_GetMemo(
		apiElem.header.guid, &guard.memo, isBeam ? APIMemoMask_BeamSegment : APIMemoMask_ColumnSegment);
	SendConversionResult segmentConversionResult{};

	if (isBeam && guard.memo.beamSegments != nullptr)
	{
		for (UInt32 i = 0; i < apiElem.beam.nSegments; i++)
		{
			auto segment = (guard.memo.beamSegments)[i];
			auto segmentId = APIGuidToString(segment.head.guid).ToCStr().Get();
			children.push_back(GetArchicadObject(segmentId, segmentConversionResult, includeProperties));
		}
	}
	else if (isColumn && guard.memo.columnSegments != nullptr)
	{
		for (UInt32 i = 0; i < apiElem.column.nSegments; i++)
		{
			auto segment = (guard.memo.columnSegments)[i];
			auto segmentId = APIGuidToString(segment.head.guid).ToCStr().Get();
			children.push_back(GetArchicadObject(segmentId, segmentConversionResult, includeProperties));
		}
	}

	return children;
}
