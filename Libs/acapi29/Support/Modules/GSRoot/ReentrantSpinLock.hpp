
// *****************************************************************************
//
// Declaration of ReentrantSpinLock class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	IZO
//
// *****************************************************************************

#ifndef GS_REENTRANTSPINLOCK_HPP
#define GS_REENTRANTSPINLOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "Lockable.hpp"



// --- ReentrantSpinLock class ----------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ReentrantSpinLock : public Lockable {

// Data members:
private:
	volatile Int32 m_lock;
	UInt32 m_holdCount;
	volatile GS::IntPtr m_ownerThread;

// Construction / destruction:
public:
			 ReentrantSpinLock ();
private:
			 ReentrantSpinLock (const ReentrantSpinLock&); // Disabled
public:
	virtual ~ReentrantSpinLock ();

// Operator overloading:
private:
	const ReentrantSpinLock&		operator = (const ReentrantSpinLock&); // Disabled

// Lockable interface implementation:
public:
	virtual void		Acquire (bool interruptible = true) override;
	virtual bool		TryAcquire (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool		TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void		Release () override;

};

////////////////////////////////////////////////////////////////////////////////
// ReentrantSpinLock inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ReentrantSpinLock::ReentrantSpinLock () :
	m_lock (0),
	m_holdCount (0),
	m_ownerThread (0)
{
	// Empty constructor body
}

}

#endif // GS_REENTRANTSPINLOCK_HPP
