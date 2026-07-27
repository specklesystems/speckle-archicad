#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"

// The element this one is HOSTED ON: a door/window's container wall, a skylight's
// container roof or shell. Empty for everything else.
//
// The owner guid rides in the element struct we already fetched, so this costs no extra
// ACAPI round-trip. API_DoorType is a typedef of API_WindowType, so both read `.owner`
// off their respective union members.
//
// The caller turns this into a SUBELEMENT edge directed HOST -> HOSTED, matching the Revit
// connector. Archicad's API does distinguish hosting (this `owner` guid) from composition
// (ACAPI_HierarchicalEditing_GetHierarchicalElementOwner, used by FilterOutHierarchicalChildren),
// and the spec has a separate HOSTED_ON (22) for the former — but no connector emits it, so
// both collapse onto SUBELEMENT here. See EmitDeferredTopology for the reasoning.
std::string HostToSpeckleConverter::GetElementHost(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);

	API_Guid owner = APINULLGuid;
	switch (apiElem.header.type.typeID)
	{
	case API_WindowID:
		owner = apiElem.window.owner;
		break;
	case API_DoorID:
		owner = apiElem.door.owner;
		break;
	case API_SkylightID:
		owner = apiElem.skylight.owner;
		break;
	default:
		return "";
	}

	if (owner == APINULLGuid)
		return "";

	return APIGuidToString(owner).ToCStr().Get();
}
