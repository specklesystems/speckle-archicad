
// *****************************************************************************
//
// Declaration of BackoffBase abstract class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_BACKOFFBASE_HPP
#define GS_BACKOFFBASE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"



// --- BackoffBase class -------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT BackoffBase {

// Static implementation:
protected:
	static UInt32		GetSalt ();
	static UInt32		Rand ();

};

}

#endif // GS_BACKOFFBASE_HPP