
// *****************************************************************************
//
// Declaration of ProcessException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESSEXCEPTION_HPP
#define GS_PROCESSEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSException.hpp"



// --- ProcessException class --------------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (ProcessException, GeneralException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_PROCESSEXCEPTION_HPP
