#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"

// The element's layer, straight off the element header — no extra ACAPI round-trip for
// the index itself. Only the index -> name resolution costs a call, and that goes through
// ConverterUtils::GetAttributeName, which is cached by (attribute type, index) per send.
//
// NOT built on GetLayers(): that one brute-forces indices 1..32768 with an
// ACAPI_Attribute_Get each (it works around ACAPI_Attribute_GetNum under-reporting) and is
// sized for a one-shot filter populate, not a per-element lookup.
ArchicadLayer HostToSpeckleConverter::GetElementLayer(const std::string& elemId)
{
	ArchicadLayer layer;

	auto apiElem = ConverterUtils::GetElement(elemId);
	const API_AttributeIndex& layerIndex = apiElem.header.layer;

	// APIInvalidAttributeIndex == 0. Non-groupable / layerless elements land here and
	// simply get no IN_COLLECTION edge.
	if (!layerIndex.IsPositive())
		return layer;

	layer.id = layerIndex.ToUniString().ToCStr().Get();
	layer.name = ConverterUtils::GetAttributeName(layerIndex, API_LayerID);
	return layer;
}
