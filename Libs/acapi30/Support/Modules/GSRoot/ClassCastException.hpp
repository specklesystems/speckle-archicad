
// *****************************************************************************
//
// Declaration of ClassCastException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_CLASSCASTEXCEPTION_HPP
#define GS_CLASSCASTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ThreadingException.hpp"



// --- ClassCastException class ------------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (ClassCastException, ThreadingException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_CLASSCASTEXCEPTION_HPP
