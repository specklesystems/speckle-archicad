// *********************************************************************************************************************
// Module:			GDL
// Namespace:		GDL
// Contact person:	KV
// *********************************************************************************************************************

#ifndef GDLPARAMCONVERSION_HPP
#define GDLPARAMCONVERSION_HPP

#include "GDLExport.h"
#include "GDLParamInterface.hpp"

namespace VBElem {
	class GDLParamList;
	class AddParMemoRecord;
}

class GDLParametersLegacyConversion;
class SymbolParametersSectionLegacyConversion;
class AddParRegDataReader;

namespace GDL
{

class GDL_DLL_EXPORT ParametersConversion
{
public:
	static Parameters		CreateParametersFromHandle (GS::Friend<GDLParametersLegacyConversion>, GSConstHandle addParHdl);
	static Parameters		CreateParametersFromHandle (GS::Friend<VBElem::AddParMemoRecord>, GSConstHandle addParHdl);
	
	static GSConstHandle	GetHandleFromParameters (GS::Friend<GDLParametersLegacyConversion>, const Parameters& parameters);
	static GSConstHandle	GetHandleFromParameters (GS::Friend<VBElem::GDLParamList>, const Parameters& parameters);
	static GSConstHandle	GetHandleFromParameters (GS::Friend<AddParRegDataReader>, const Parameters& parameters);

	static GSErrCode		GetHandleCopyFromParameters (GS::Friend<SymbolParametersSectionLegacyConversion>, const Parameters& parameters, GSHandle* addParHdlOut);
};

}

#endif
