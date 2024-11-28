
// *****************************************************************************
//
// Declaration of ReentrantTicketLock, ReentrantTicketLockGuard classes
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *****************************************************************************

#ifndef GS_REENTRANTTICKETLOCK_HPP
#define GS_REENTRANTTICKETLOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TicketLock.hpp"



// --- ReentrantTicketLock class -----------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ReentrantTicketLock {
private:
	TicketLock ticketLock;
	IntPtr	   ownerThread;
	UInt32	   ownerThreadLevel;

	ReentrantTicketLock (const ReentrantTicketLock&);				// disabled
	ReentrantTicketLock& operator= (const ReentrantTicketLock&);	// disabled

public:
	ReentrantTicketLock ();

	void	Acquire (void);
	void	Release (void);
};


// --- ReentrantTicketLockGuard class ---------------------------------------------------

class GSROOT_DLL_EXPORT ReentrantTicketLockGuard {
private:
	ReentrantTicketLock* reentrantTicketLock;

	ReentrantTicketLockGuard (const ReentrantTicketLockGuard&);				// disabled
	ReentrantTicketLockGuard& operator= (const ReentrantTicketLockGuard&);	// disabled

public:
	ReentrantTicketLockGuard (ReentrantTicketLock& lock): reentrantTicketLock (&lock) { reentrantTicketLock->Acquire (); }
	ReentrantTicketLockGuard (volatile ReentrantTicketLock& lock): reentrantTicketLock (sync_cast<ReentrantTicketLock*> (&lock)) { reentrantTicketLock->Acquire (); }

   ~ReentrantTicketLockGuard () { reentrantTicketLock->Release (); }
};

}


#endif // GS_REENTRANTTICKETLOCK_HPP
