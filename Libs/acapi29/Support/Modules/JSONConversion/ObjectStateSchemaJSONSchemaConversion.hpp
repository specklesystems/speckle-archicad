#ifndef OBJECTSTATESCHEMAJSONSCHEMACONVERSION_HPP
#define OBJECTSTATESCHEMAJSONSCHEMACONVERSION_HPP

#pragma once

#include "ObjectState.hpp"
#include "UniString.hpp"
#include "Channel.hpp"
#include "OBinaryChannel.hpp"
#include "IBinaryChannel.hpp"
#include "JSON/Value.hpp"
#include "JSONConversionExport.hpp"

namespace JSON {

JSON_CONVERSION_API GSErrCode	CreateJSONSchemaFromObjectStateSchema (const GS::ObjectState::Schema&	objectStateSchema,
																	   JSON::ValueRef					destination);
JSON_CONVERSION_API GSErrCode	CreateJSONSchemaFromObjectStateSchema (const GS::ObjectState::Schema&	objectStateSchema,
																	   GS::UniString&					destination,
																	   bool								prettyPrint = false);

JSON_CONVERSION_API GSErrCode	ConvertJSONSchemaToObjectStateSchema (JSON::ValueRef											source,
																	  const GS::UniString&										uri,
																	  GS::HashTable<GS::UniString, GS::ObjectState::Schema>&	uriToSchemaDictionary,
																	  GS::HashTable<GS::UniString, GS::ObjectState::Field>&		uriToFieldDictionary);
JSON_CONVERSION_API GSErrCode	ConvertJSONSchemaToObjectStateSchema (const GS::UniString&										source,
																	  const GS::UniString&										uri,
																	  GS::HashTable<GS::UniString, GS::ObjectState::Schema>&	uriToSchemaDictionary,
																	  GS::HashTable<GS::UniString, GS::ObjectState::Field>&		uriToFieldDictionary);

} // namespace JSON

#endif
