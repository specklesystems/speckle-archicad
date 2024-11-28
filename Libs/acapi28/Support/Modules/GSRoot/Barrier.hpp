
// *****************************************************************************
//
// Declaration of Barrier class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_BARRIER_HPP
#define GS_BARRIER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "Condition.hpp"
#include "ReentrantLock.hpp"
#include "RunnableTask.hpp"



// --- Barrier class -----------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Barrier : public Waitable {

// Data members:
private:
	mutable ReentrantLock	m_lock;				// Lock for serializing access to internal state
	Condition				m_trip;				// Condition to wait on until tripped. Signaled when all threads arrive (tripped).
	UInt32					m_parties;			// The number of parties
	UInt32					m_counter;			// The number of parties still waiting. Counts down from parties to 0.
	Int32					m_generation;		// The generation number. Incremented upon barrier trip. Retracted upon reset.
	bool					m_broken;			// The broken flag
	RunnableTask			m_task;				// The task to run when tripped.

// Construction / destruction:
public:
	explicit Barrier (UInt32 parties);
			 Barrier (UInt32 parties, const RunnableTask& task);
private:
			 Barrier (const Barrier&); // Disabled
public:
			~Barrier ();

// Operator overloading:
private:
	const Barrier&			operator = (const Barrier&); // Disabled

// Operations:
public:
	UInt32					GetParties () const;
	UInt32					GetNumberOfWaitingParties () const;

	bool					IsBroken () const;

	UInt32					Await (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr);
	UInt32					Await (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr);
	UInt32					Await (bool interruptible = true);

	void					Reset ();

// Waitable interface implementation:
public:
	virtual bool			Wait (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool			Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void			Wait (bool interruptible = true) override;

// Implementation:
private:
	bool					DoWait (UInt32 timeout, bool interruptible, UInt32* remaining, UInt32& index);
	void					DoWait (bool interruptible, UInt32& index);

	void					BreakBarrier ();

};

////////////////////////////////////////////////////////////////////////////////
// Barrier inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetParties
// -----------------------------------------------------------------------------

inline UInt32	Barrier::GetParties () const
{
	return m_parties;
}

}

#endif // GS_BARRIER_HPP
