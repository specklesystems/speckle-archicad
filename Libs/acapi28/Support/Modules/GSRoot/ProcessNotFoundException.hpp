
// *****************************************************************************
//
// Declaration of ProcessNotFoundException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESSNOTFOUNDEXCEPTION_HPP
#define GS_PROCESSNOTFOUNDEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ProcessException.hpp"



// --- ProcessNotFoundException class ------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (ProcessNotFoundException, ProcessException, GS::Error, GSROOT_DLL_EXPORT)

}

#endif // GS_PROCESSNOTFOUNDEXCEPTION_HPP
