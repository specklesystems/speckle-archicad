#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"

// The group this element belongs to, straight off the element header — no ACAPI
// round-trip. APINULLGuid means ungrouped (also the case for non-groupable element
// types), which is the signal to emit no IN_GROUP edge.
//
// This is the IMMEDIATE group, not the root of a nested group chain
// (ACAPI_Grouping_GetRootGroup would give that). The immediate group is the more specific
// answer and is what a flat IN_GROUP axis wants; nesting is a follow-up, see
// GetGroupDisplayName below.
std::string HostToSpeckleConverter::GetElementGroup(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);

	if (apiElem.header.groupGuid == APINULLGuid)
		return "";

	return APIGuidToString(apiElem.header.groupGuid).ToCStr().Get();
}

// Archicad groups are ANONYMOUS: API_GroupID exists as an element type id but there is no
// API_GroupType in the API_Element union and no name field anywhere — unlike Revit, where
// a group carries its GroupType name. So there is nothing to display and we synthesise a
// stable short label from the guid. An unlabelled node in a scene tree is worse than a
// synthetic one.
std::string HostToSpeckleConverter::GetGroupDisplayName(const std::string& groupId)
{
	if (groupId.empty())
		return "";

	// Guid strings are "BC1E7D39-C7F9-...."; the first block is short and unique enough
	// to tell two groups apart in a tree.
	const std::string shortId = groupId.substr(0, groupId.find('-'));
	return "Group " + shortId;
}
