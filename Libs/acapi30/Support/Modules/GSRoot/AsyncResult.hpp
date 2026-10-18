
// *****************************************************************************
//
// Declaration of AsyncResult interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_ASYNCRESULT_HPP
#define GS_ASYNCRESULT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Cancelable.hpp"
#include "Object.hpp"
#include "Waitable.hpp"


// --- AsyncResult interface ---------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT AsyncResult : public Cancelable, public Waitable {

// Construction / destruction:
protected:
			 AsyncResult () = default;
			 AsyncResult (const AsyncResult&) = default;
public:
	virtual ~AsyncResult ();

// Operator overloading:
protected:
	AsyncResult&		operator = (const AsyncResult&) = default;

// Interface methods:
public:
	virtual Object*		Get (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr);
	virtual Object*		Get (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) = 0;
	virtual	Object*		Get (bool interruptible = true) = 0;

	virtual bool		IsCompletedWithException () const = 0;
	virtual bool		IsCompletedWithResult () const = 0;
	virtual bool		IsCompleted () const = 0;

};

}

#endif // GS_ASYNCRESULT_HPP
