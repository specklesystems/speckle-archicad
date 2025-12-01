
// *****************************************************************************
//
// Declaration of ThreadMonitorImpl abstract class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADMONITORIMPL_HPP
#define GS_THREADMONITORIMPL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Interruptible.hpp"
#include "ThreadMonitorState.hpp"



// --- ThreadMonitorImpl class -------------------------------------------------

namespace GS {

class ThreadMonitorImpl {

// Nested classes:
protected:
	class [[nodiscard]] ClearInterruptibleGuard {

	// Data members:
	private:
		ThreadMonitorImpl*				m_monitor;

	// Construction / destruction:
	public:
		explicit ClearInterruptibleGuard (ThreadMonitorImpl* monitor);
	private:
				 ClearInterruptibleGuard (const ClearInterruptibleGuard&); // Disabled
	public:
				~ClearInterruptibleGuard ();

	// Operator overloading:
	private:
		const ClearInterruptibleGuard&	operator = (const ClearInterruptibleGuard&); // Disabled

	};

	class [[nodiscard]] SetInterruptibleGuard {

	// Data members:
	private:
		ThreadMonitorImpl*				m_monitor;
		bool							m_commit;

	// Construction / destruction:
	public:
		 SetInterruptibleGuard (ThreadMonitorImpl* monitor, bool interruptible);
	private:
		 SetInterruptibleGuard (const SetInterruptibleGuard&); // Disabled
	public:
		~SetInterruptibleGuard ();

	// Operator overloading:
	private:
		const SetInterruptibleGuard&	operator = (const SetInterruptibleGuard&); // Disabled

	// Operations:
	public:
		void							Commit ();

	};

// Friend classes:
friend class ClearInterruptibleGuard;
friend class SetInterruptibleGuard;

// Data members:
protected:
	volatile bool				m_waiting;			// Waiting flag: indicates that the thread monitor is in waiting state
	volatile bool				m_signaled;			// Signaled flag: indicates that the thread monitor is waken up due to a signal
	volatile bool				m_interrupted;		// Interrupted flag: indicates that thread monitor is interrupted
	volatile bool				m_canceled;			// Canceled flag: indicates that the thread monitor is canceled
	volatile bool				m_deferred;			// Deferred interruption flag: indicates that the thread monitor is uninterruptible

// Construction / destruction:
protected:
			 ThreadMonitorImpl ();
private:
			 ThreadMonitorImpl (const ThreadMonitorImpl&); // Disabled
public:
	virtual ~ThreadMonitorImpl ();

// Operator overloading:
private:
	const ThreadMonitorImpl&	operator = (const ThreadMonitorImpl&); // Disabled

// Operations:
public:
	virtual	void				Acquire	() = 0;
	virtual bool				TryAcquire () = 0;
	virtual void				Release	() = 0;

	virtual ThreadMonitorState	Wait (UInt32 timeout, bool inerruptible) = 0;
	virtual ThreadMonitorState	Wait (bool interruptible) = 0;
	virtual bool				Notify () = 0;

	virtual bool				IsInterrupted () const = 0;
	virtual bool				Interrupted () = 0;
	virtual void				Interrupt () = 0;

	virtual bool				IsCanceled () const = 0;
	virtual bool				Canceled () = 0;
	virtual void				Cancel () = 0;

	virtual void				BlockOn (Interruptible* blocker) = 0;

// Implementation:
protected:
	void						SetInterruptDeferred (bool deferred);
	bool						IsInterruptDeferred () const;

};

////////////////////////////////////////////////////////////////////////////////
// ThreadMonitorImpl inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ThreadMonitorImpl::ThreadMonitorImpl () :
	m_waiting (false),
	m_signaled (false),
	m_interrupted (false),
	m_canceled (false),
	m_deferred (false)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetInterruptDeferred
// -----------------------------------------------------------------------------

inline void		ThreadMonitorImpl::SetInterruptDeferred (bool deferred)
{
	// Note: if the thread monitor is not in waiting state then interruption only
	// means setting the thread monitor's interrupt status flag, so interrupt may
	// impact later. Deferring the interruption means deferring the impact of the
	// interrupt status flag.

	m_deferred = deferred;
}

// -----------------------------------------------------------------------------
// IsInterruptDeferred
// -----------------------------------------------------------------------------

inline bool		ThreadMonitorImpl::IsInterruptDeferred () const
{
	return m_deferred;
}

}

#endif // GS_THREADMONITORIMPL_HPP
