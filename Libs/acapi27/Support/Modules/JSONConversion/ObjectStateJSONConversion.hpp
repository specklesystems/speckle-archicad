// *********************************************************************************************************************
// Description:		ObjectStateJSONConversion
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	MB, KKr
//
// *********************************************************************************************************************

#ifndef OBJECTSTATEJSONCONVERSION_HPP
#define OBJECTSTATEJSONCONVERSION_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "ObjectState.hpp"
#include "UniString.hpp"
#include "Channel.hpp"
#include "OBinaryChannel.hpp"
#include "IBinaryChannel.hpp"
#include "JSONConversionExport.hpp"

namespace JSON {

JSON_CONVERSION_API GSErrCode	CreateFromObjectState (const GS::ObjectState& objectState, GS::UniString&      destination, bool prettyPrint = false);
JSON_CONVERSION_API GSErrCode	CreateFromObjectState (const GS::ObjectState& objectState, GS::OBinaryChannel& destination, bool prettyPrint = false);
JSON_CONVERSION_API GSErrCode	CreateFromObjectState (const GS::ObjectState& objectState, GS::OChannel&       destination, bool prettyPrint = false);
				    
JSON_CONVERSION_API GSErrCode	ConvertToObjectState (const GS::UniString& source, GS::ObjectState& objectState);
JSON_CONVERSION_API GSErrCode	ConvertToObjectState (GS::IBinaryChannel&  source, GS::ObjectState& objectState);
JSON_CONVERSION_API GSErrCode	ConvertToObjectState (GS::IChannel&		   source, GS::ObjectState& objectState);

} // namespace JSON

#endif