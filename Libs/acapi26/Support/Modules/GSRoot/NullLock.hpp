
// *****************************************************************************
//
// Declaration and implementation of NullLock
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_NULLLOCK_HPP
#define GS_NULLLOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"



// --- NullLock class ----------------------------------------------------------

namespace GS {

class NullLock {

// Construction / destruction:
public:
	NullLock () {};
private:
	NullLock (const NullLock&); // Disabled

// Operator overloading:
private:
	const NullLock&		operator = (const NullLock&); // Disabled

// Operations:
public:
	void				Acquire () {};
	bool				TryAcquire () { return true; };
	void				Release () {};

};

}

#endif // GS_NULLLOCK_HPP
