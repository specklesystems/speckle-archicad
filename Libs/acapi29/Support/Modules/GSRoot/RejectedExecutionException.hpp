
// *****************************************************************************
//
// Declaration of RejectedExecutionException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_REJECTEDEXECUTIONEXCEPTION_HPP
#define GS_REJECTEDEXECUTIONEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ThreadingException.hpp"



// --- RejectedExecutionException class ----------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (RejectedExecutionException, ThreadingException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_REJECTEDEXECUTIONEXCEPTION_HPP
