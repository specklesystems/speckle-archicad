
// *****************************************************************************
//
// Declaration of CancellationException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_CANCELLATIONEXCEPTION_HPP
#define GS_CANCELLATIONEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ThreadingException.hpp"



// --- CancellationException class ---------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (CancellationException, ThreadingException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_CANCELLATIONEXCEPTION_HPP
