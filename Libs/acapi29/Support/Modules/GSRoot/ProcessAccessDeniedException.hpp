
// *****************************************************************************
//
// Declaration of ProcessAccessDeniedException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESSACCESSDENIEDEXCEPTION_HPP
#define GS_PROCESSACCESSDENIEDEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ProcessException.hpp"



// --- ProcessAccessDeniedException class --------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (ProcessAccessDeniedException, ProcessException, GS::Error, GSROOT_DLL_EXPORT)

}

#endif // GS_PROCESSACCESSDENIEDEXCEPTION_HPP
