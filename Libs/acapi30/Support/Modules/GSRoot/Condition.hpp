
// *****************************************************************************
//
// Declaration of Condition class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_CONDITION_HPP
#define GS_CONDITION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "Lockable.hpp"
#include "Waitable.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class FifoConditionImpl;

}



// --- Condition class ---------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Condition : public Waitable {

// Data members:
private:
	FifoConditionImpl*	m_impl;

// Construction / destruction:
public:
	explicit Condition (Lockable& lock);
private:
			 Condition (const Condition&); // Disabled
public:
	virtual ~Condition ();

// Operator overloading:
private:
	const Condition&	operator = (const Condition&); // Disabled

// Operations:
public:
	void				Notify ();
	void				NotifyAll ();

// Waitable interface implementation:
public:
	virtual bool		Wait (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool		Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void		Wait (bool interruptible = true) override;

};

}

#endif // GS_CONDITION_HPP
