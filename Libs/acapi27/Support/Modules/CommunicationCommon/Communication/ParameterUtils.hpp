
// *****************************************************************************
//
// Declaration of Parameter related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_PARAMETERUTILS_HPP
#define COMMUNICATION_PARAMETERUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Parameter.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {

// -----------------------------------------------------------------------------
// CheckParameterName
// -----------------------------------------------------------------------------

inline void		CheckParameterName (const GS::UniString& parameterName, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (parameterName.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid parameter name: name is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckParameter
// -----------------------------------------------------------------------------

inline void		CheckParameter (const Parameter& parameter, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (parameter.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid parameter: parameter is not valid.", sourceFile, sourceLine);
	}
}

}

#endif // COMMUNICATION_PARAMETERUTILS_HPP