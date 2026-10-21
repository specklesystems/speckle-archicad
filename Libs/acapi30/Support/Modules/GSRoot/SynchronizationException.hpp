
// *****************************************************************************
//
// Declaration of SynchronizationException
//
// Module:          GSRoot
// Namespace:       GS
// Contact person:  SN
//
// *****************************************************************************

#ifndef GS_SYNCHRONIZATIONEXCEPTION_HPP
#define GS_SYNCHRONIZATIONEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ThreadingException.hpp"



// --- SynchronizationException class ------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (SynchronizationException, ThreadingException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_SYNCHRONIZATIONEXCEPTION_HPP
