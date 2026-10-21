
// *****************************************************************************
//
// Declaration SingletonLock class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SINGLETONLOCK_HPP
#define GS_SINGLETONLOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Lockable.hpp"



// --- SingletonLock class -----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT SingletonLock {

// Construction / destruction:
private:
	SingletonLock (); // Disabled
	SingletonLock (const SingletonLock&); // Disabled

// Operator overloading:
private:
	const SingletonLock&	operator = (const SingletonLock&);

// Static operations:
public:
	static Lockable&		GetLock ();

};

}

#endif // GS_SINGLETONLOCK_HPP
