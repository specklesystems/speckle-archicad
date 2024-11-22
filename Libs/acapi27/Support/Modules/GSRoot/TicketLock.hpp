
// *****************************************************************************
//
// Declaration of TicketLock, TicketLockGuard classes
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *****************************************************************************

#ifndef GS_TICKETLOCK_HPP
#define GS_TICKETLOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "Atomic.hpp"
#include "MemoryBarrier.hpp"

#ifdef Yield
#undef Yield
#endif



// --- TicketLock class --------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT TicketLock {
private:
	volatile Int32 current;
	Int32		   ticket;

	TicketLock (const TicketLock&);				// disabled
	TicketLock& operator= (const TicketLock&);	// disabled

	void	Yield (void);

public:
	inline TicketLock ();

	GS_FORCE_INLINE void	Acquire	  (void);	// waits with Yield
	GS_FORCE_INLINE void	Release	  (void);
};


// --- TicketLockGuard class ---------------------------------------------------

class GSROOT_DLL_EXPORT TicketLockGuard {
private:
	TicketLock* ticketLock;

	TicketLockGuard (const TicketLockGuard&);				// disabled
	TicketLockGuard& operator= (const TicketLockGuard&);	// disabled

public:
	TicketLockGuard (TicketLock& lock): ticketLock (&lock) { ticketLock->Acquire (); }
	TicketLockGuard (volatile TicketLock& lock): ticketLock (sync_cast<TicketLock*> (&lock)) { ticketLock->Acquire (); }

   ~TicketLockGuard () { ticketLock->Release (); }
};


////////////////////////////////////////////////////////////////////////////////
// TicketLock inlines

inline TicketLock::TicketLock ():
	current (0),
	ticket (0)
{
}


GS_FORCE_INLINE void	TicketLock::Acquire (void)
{
	Int32 myTicket = AtomicIncrement (&ticket);

	while (current != myTicket - 1)
		Yield ();
}


GS_FORCE_INLINE void	TicketLock::Release (void)
{
	GS::MemoryBarrierForVolatile ();
	current++;
}

}


#endif // GS_TICKETLOCK_HPP
