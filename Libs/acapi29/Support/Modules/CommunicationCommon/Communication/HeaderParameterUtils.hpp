
// *****************************************************************************
//
// Declaration of HeaderParameter related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERPARAMETERUTILS_HPP
#define COMMUNICATION_HEADERPARAMETERUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderParameter.hpp"

	// from GSRoot
#include "PagedArray.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {

// -----------------------------------------------------------------------------
// CheckHeaderParameterName
// -----------------------------------------------------------------------------

inline void		CheckHeaderParameterName (const GS::UniString& headerParameterName, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (headerParameterName.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid header parameter name: name is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckHeaderParameters
// -----------------------------------------------------------------------------

inline void		CheckHeaderParameters (const GS::PagedArray<HeaderParameter>& headerParameters, const char* sourceFile, GS::UInt32 sourceLine)
{
	for (const HeaderParameter& headerParameter : headerParameters) {
		if (DBERROR (headerParameter.IsValid () == false)) {
			throw GS::IllegalArgumentException ("Invalid header parameter list: list contains invalid header parameter.", sourceFile, sourceLine);
		}
	}
}

// -----------------------------------------------------------------------------
// CheckHeaderParameter
// -----------------------------------------------------------------------------

inline void		CheckHeaderParameter (const HeaderParameter& headerParameter, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (headerParameter.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid header parameter: parameter is not valid.", sourceFile, sourceLine);
	}
}

}

#endif // COMMUNICATION_HEADERPARAMETERUTILS_HPP