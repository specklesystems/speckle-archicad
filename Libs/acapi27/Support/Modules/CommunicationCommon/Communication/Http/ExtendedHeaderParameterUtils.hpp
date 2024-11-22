
// *****************************************************************************
//
// Declaration of ExtendedHeaderParameter related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_EXTENDEDHEADERPARAMETERUTILS_HPP
#define COMMUNICATION_HTTP_EXTENDEDHEADERPARAMETERUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ExtendedHeaderParameter.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckExtendedHeaderParameterLanguage
// -----------------------------------------------------------------------------

inline void		CheckExtendedHeaderParameterLanguage (const GS::UniString& language, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (language.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid extended header parameter language: language is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckExtendedHeaderParameterCharset
// -----------------------------------------------------------------------------

inline void		CheckExtendedHeaderParameterCharset (const GS::UniString& charset, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (charset.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid extended header parameter charset: charset is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckExtendedHeaderParameter
// -----------------------------------------------------------------------------

inline void		CheckExtendedHeaderParameter (const ExtendedHeaderParameter& extendedHeaderParameter, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (extendedHeaderParameter.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid extended header parameter: parameter is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_EXTENDEDHEADERPARAMETERUTILS_HPP