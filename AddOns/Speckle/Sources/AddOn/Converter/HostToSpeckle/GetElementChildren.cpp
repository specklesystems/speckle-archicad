#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

#include <unordered_set>

namespace
{
	// Owns the memo handles for the duration of the child walk (the recursive
	// GetArchicadObject calls below can throw).
	struct MemoGuard
	{
		API_ElementMemo memo{};
		~MemoGuard() { ACAPI_DisposeElemMemoHdls(&memo); }
	};

	// Appends the guids of one memo sub-part array. Sized from the handle rather than the
	// element's own count field, matching GetElementBody::GetPartIDs.
	template<typename T>
	void CollectGuids(T* parts, std::vector<std::string>& out)
	{
		if (parts == nullptr)
			return;

		const GSSize count = BMGetPtrSize(reinterpret_cast<GSPtr>(parts)) / sizeof(T);
		for (Int32 i = 0; i < count; ++i)
			out.push_back(APIGuidToString(parts[i].head.guid).ToCStr().Get());
	}

	// Memo mask covering exactly the sub-part arrays read below. 0 = the type has no
	// children and the memo fetch is skipped entirely.
	UInt64 ChildMemoMask(API_ElemTypeID typeID)
	{
		switch (typeID)
		{
		case API_BeamID:
			return APIMemoMask_BeamSegment;
		case API_ColumnID:
			return APIMemoMask_ColumnSegment;
		case API_CurtainWallID:
			return APIMemoMask_CWallFrames | APIMemoMask_CWallPanels |
				APIMemoMask_CWallJunctions | APIMemoMask_CWallAccessories;
		default:
			return 0;
		}
	}
}

// The element's own child elements, each converted into a full ArchicadObject (its own
// geometry + properties) and linked to the parent with a SUBELEMENT edge by the caller.
//
// NOTE the division of labour with GetElementBody: GetArchicadObject only extracts a body
// for an element with NO children, so a parent that reports children here contributes no
// geometry of its own — the children carry all of it. That is what turns a curtain wall
// from one merged per-material blob into a real parent/child hierarchy, and it is why this
// function and GetElementBody::CollectPartIDs must not both claim the same parts.
std::vector<ArchicadObject> HostToSpeckleConverter::GetElementChildren(const std::string& elemId, bool includeProperties)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	const API_ElemTypeID typeID = apiElem.header.type.typeID;

	const UInt64 memoMask = ChildMemoMask(typeID);
	if (memoMask == 0)
		return {};

	MemoGuard guard;
	ACAPI_Element_GetMemo(apiElem.header.guid, &guard.memo, memoMask);

	std::vector<std::string> childIds;
	switch (typeID)
	{
	case API_BeamID:
		CollectGuids(guard.memo.beamSegments, childIds);
		break;
	case API_ColumnID:
		CollectGuids(guard.memo.columnSegments, childIds);
		break;
	case API_CurtainWallID:
		// Frames, panels, junctions and accessories are the geometry carriers. SEGMENTS are
		// deliberately excluded: they are a logical subdivision with no body of their own,
		// and neither API_CWFrameType nor API_CWPanelType exposes a back-reference to its
		// segment — so a CW -> segment -> frame tier cannot be reconstructed from the child
		// side. The hierarchy is therefore flat: curtain wall -> parts.
		CollectGuids(guard.memo.cWallFrames, childIds);
		CollectGuids(guard.memo.cWallPanels, childIds);
		CollectGuids(guard.memo.cWallJunctions, childIds);
		CollectGuids(guard.memo.cWallAccessories, childIds);
		break;
	default:
		break;
	}

	std::vector<ArchicadObject> children;
	children.reserve(childIds.size());

	SendConversionResult childConversionResult{};
	for (const auto& childId : childIds)
		children.push_back(GetArchicadObject(childId, childConversionResult, includeProperties));

	return children;
}

// Drops elements whose hierarchical parent is ALSO in the list — they are emitted as
// SUBELEMENT children of that parent, so sending them again at top level would duplicate
// both their geometry and their properties.
//
// This is needed because GetElementList maps a single type filter onto the parent AND its
// sub-types (e.g. "CurtainWall" -> API_CurtainWallID plus Segment/Frame/Panel/Junction/
// Accessory ids; likewise "Stair" and "Railing"), so picking one type filter returns both
// tiers. The Revit connector solves the same problem with
// RemoveKnownChildElementsWhenParentPresent.
//
// The test is "the API reports an owner that is not the element itself, and that owner is
// in the selection". ACAPI_HierarchicalEditing_GetHierarchicalElementOwner returns the
// INPUT element as the owner when it is not a child, so comparing against self is the
// robust check — more so than trusting API_ChildElemInMultipleElem, which is documented
// only for curtain walls / stairs / railings and may not classify beam and column
// segments. A child whose parent is NOT in the selection is kept and sent standalone.
std::vector<std::string> HostToSpeckleConverter::FilterOutHierarchicalChildren(const std::vector<std::string>& elementIds)
{
	const std::unordered_set<std::string> present(elementIds.begin(), elementIds.end());

	std::vector<std::string> kept;
	kept.reserve(elementIds.size());

	for (const auto& elemId : elementIds)
	{
		API_Guid guid = APIGuidFromString(elemId.c_str());
		const API_HierarchicalOwnerType ownerType = API_RootHierarchicalOwner;
		API_HierarchicalElemType hierarchicalElemType = API_UnknownElemType;
		API_Guid ownerGuid = APINULLGuid;

		const GSErrCode err = ACAPI_HierarchicalEditing_GetHierarchicalElementOwner(
			&guid, &ownerType, &hierarchicalElemType, &ownerGuid);

		// Unknown ownership -> keep. Dropping an element we cannot classify would silently
		// lose it; a duplicate is the safer failure.
		if (err != NoError || ownerGuid == APINULLGuid || ownerGuid == guid)
		{
			kept.push_back(elemId);
			continue;
		}

		const std::string ownerId = APIGuidToString(ownerGuid).ToCStr().Get();
		if (present.find(ownerId) == present.end())
			kept.push_back(elemId);
	}

	return kept;
}
