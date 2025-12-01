
// *****************************************************************************
//
// Declaration of BrokenBarrierException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_BROKENBARRIEREXCEPTION_HPP
#define GS_BROKENBARRIEREXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SynchronizationException.hpp"



// --- BrokenBarrierException class --------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (BrokenBarrierException, SynchronizationException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_BROKENBARRIEREXCEPTION_HPP
