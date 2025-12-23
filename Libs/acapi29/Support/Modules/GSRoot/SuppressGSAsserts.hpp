// *****************************************************************************
//
//				SuppressGSAsserts - Suppress assertion logs and messages
//
// Module:			CppUnit
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_SUPPRESSGSASSERTS_HPP
#define GS_SUPPRESSGSASSERTS_HPP

#include "AtomicCounter.hpp"
#include "GSDebug.hpp"
#include "Lock.hpp"

namespace GS
{

class GSROOT_DLL_EXPORT SuppressAssertLogs
{
	static GS::AtomicCounter counter;
	static GS::Lock			 lock;

	bool enableGuard;

public:
	 SuppressAssertLogs (bool enableGUard = true);
	~SuppressAssertLogs ();
};


class GSROOT_DLL_EXPORT SuppressAssertMessages
{
	static GS::AtomicCounter counter;
	static GS::Lock			 lock;

	bool enableGuard;

public:
	SuppressAssertMessages (bool enableGUard = true);
	~SuppressAssertMessages ();
};

}

#endif /* GS_SUPPRESSGSASSERTS_HPP */
