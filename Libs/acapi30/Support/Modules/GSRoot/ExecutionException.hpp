
// *****************************************************************************
//
// Declaration of ExecutionException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_EXECUTIONEXCEPTION_HPP
#define GS_EXECUTIONEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ThreadingException.hpp"



// --- ExecutionException class ------------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (ExecutionException, ThreadingException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_EXECUTIONEXCEPTION_HPP
