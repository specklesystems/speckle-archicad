
// *****************************************************************************
//
// Declaration of ThreadMonitor class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADMONITOR_HPP
#define GS_THREADMONITOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ThreadMonitorImpl.hpp"
#include "Timeout.hpp"



// --- ThreadMonitor class -----------------------------------------------------

namespace GS {

class ThreadMonitor {

// Data members:
private:
	ThreadMonitorImpl*		m_impl;		// The underlying implementation of the thread monitor

// Construction / destruction:
public:
	explicit ThreadMonitor (ThreadMonitorImpl* impl);
private:
			 ThreadMonitor (const ThreadMonitor&); // Disabled
public:
			~ThreadMonitor ();

// Operator overloading:
private:
	const ThreadMonitor&	operator = (const ThreadMonitor&); // Disabled

// Operations:
public:
	void					Acquire ();
	bool					TryAcquire ();
	void					Release ();

	ThreadMonitorState		Wait (UInt32 timeout, bool interruptible);
	ThreadMonitorState		Wait (bool interruptible);
	bool					Notify ();

	bool					IsInterrupted () const;
	bool					Interrupted ();
	void					Interrupt ();

	bool					IsCanceled () const;
	bool					Canceled ();
	void					Cancel ();

	void					BlockOn (Interruptible* blocker);

};

////////////////////////////////////////////////////////////////////////////////
// ThreadMonitor inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Acquire
// -----------------------------------------------------------------------------

inline void		ThreadMonitor::Acquire ()
{
	m_impl->Acquire ();
}

// -----------------------------------------------------------------------------
// TryAcquire
// -----------------------------------------------------------------------------

inline bool		ThreadMonitor::TryAcquire ()
{
	return m_impl->TryAcquire ();
}

// -----------------------------------------------------------------------------
// Release
// -----------------------------------------------------------------------------

inline void		ThreadMonitor::Release ()
{
	m_impl->Release ();
}

// -----------------------------------------------------------------------------
// Wait
// -----------------------------------------------------------------------------

inline ThreadMonitorState	ThreadMonitor::Wait (UInt32 timeout, bool interruptible)
{
	return m_impl->Wait (timeout, interruptible);
}

// -----------------------------------------------------------------------------
// Wait
// -----------------------------------------------------------------------------

inline ThreadMonitorState	ThreadMonitor::Wait (bool interruptible)
{
	return m_impl->Wait (interruptible);
}

// -----------------------------------------------------------------------------
// Notify
// -----------------------------------------------------------------------------

inline bool		ThreadMonitor::Notify ()
{
	return m_impl->Notify ();
}

// -----------------------------------------------------------------------------
// IsInterrupted
// -----------------------------------------------------------------------------

inline bool		ThreadMonitor::IsInterrupted () const
{
	return m_impl->IsInterrupted ();
}

// -----------------------------------------------------------------------------
// Interrupted
// -----------------------------------------------------------------------------

inline bool		ThreadMonitor::Interrupted ()
{
	return m_impl->Interrupted ();
}

// -----------------------------------------------------------------------------
// Interrupt
// -----------------------------------------------------------------------------

inline void		ThreadMonitor::Interrupt ()
{
	m_impl->Interrupt ();
}

// -----------------------------------------------------------------------------
// IsCanceled
// -----------------------------------------------------------------------------

inline bool		ThreadMonitor::IsCanceled () const
{
	return m_impl->IsCanceled ();
}

// -----------------------------------------------------------------------------
// Canceled
// -----------------------------------------------------------------------------

inline bool		ThreadMonitor::Canceled ()
{
	return m_impl->Canceled ();
}

// -----------------------------------------------------------------------------
// Cancel
// -----------------------------------------------------------------------------

inline void		ThreadMonitor::Cancel ()
{
	m_impl->Cancel ();
}

// -----------------------------------------------------------------------------
// BlockOn
// -----------------------------------------------------------------------------

inline void		ThreadMonitor::BlockOn (Interruptible* blocker)
{
	m_impl->BlockOn (blocker);
}

}

#endif // GS_THREADMONITOR_HPP
