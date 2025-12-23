
// *****************************************************************************
//
// Declaration of debug utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_DEBUG_HPP
#define COMMUNICATION_DEBUG_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "GSException.hpp"



// --- Debug functions ---------------------------------------------------------

namespace Communication {

void			COMMUNICATIONCOMMON_API DebugPrintEx (const GS::Exception& exception);

GS::UniString	COMMUNICATIONCOMMON_API ToString (const GS::Exception& exception);

}



// --- Macros ------------------------------------------------------------------

#define DBPRINTEX(ex)	Communication::DebugPrintEx (ex)


#endif // COMMUNICATION_DEBUG_HPP