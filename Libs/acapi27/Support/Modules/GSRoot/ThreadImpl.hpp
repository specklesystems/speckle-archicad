
// *****************************************************************************
//
// Declaration of ThreadImpl class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADIMPL_HPP
#define GS_THREADIMPL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "HashTable.hpp"
#include "PagedArray.hpp"
#include "RunnableTask.hpp"
#include "ThreadLocal.hpp"
#include "ThreadLocalValue.hpp"
#include "ThreadMonitor.hpp"
#include "ThreadPriority.hpp"
#include "ThreadState.hpp"
#include "Timeout.hpp"
#include "UniString.hpp"



// --- Forward declaration -----------------------------------------------------

namespace GS {

class Thread;
class ThreadLauncher;
class ThreadManager;

}



// --- ThreadImpl class --------------------------------------------------------

namespace GS {

class ThreadImpl {

// Friend classes:
friend class ThreadLauncher;
friend class ThreadManager;

// Type definitions:
private:
	typedef PagedArray<ThreadImpl*>	ThreadList;
public:
	typedef HashTable<ThreadLocalKey, ThreadLocalValueBase*> ThreadLocalMap;

// Data members:
protected:
	mutable ThreadMonitor			m_monitor;		// The monitor of the thread
	ThreadState						m_state;		// The state of the thread

	AtomicCounter					m_counter;		// Reference counter

	RunnableTask					m_task;			// The task executed by the thread
	UniString						m_name;			// The name of the thread

	ThreadList						m_joiners;		// The list of threads which are waiting for thread completion

	ThreadLocalMap					m_threadLocalMapR;
	ThreadLocalMap					m_threadLocalMapW;

// Construction / destruction:
protected:
			 ThreadImpl (ThreadMonitorImpl* monitor, const UniString& name);
			 ThreadImpl (ThreadMonitorImpl* monitor, const RunnableTask& task, const UniString& name);
private:
			 ThreadImpl (const ThreadImpl&); // Disabled
public:
	virtual ~ThreadImpl ();

// Operator overloading:
private:
	ThreadImpl&						operator = (const ThreadImpl&); // Disabled

// Operations:
public:
	ThreadMonitor&					GetMonitor ();
	const ThreadState&				GetState () const;

	void							AddRef ();
	void							Release ();

	const RunnableTask&				GetTask () const;
	RunnableTask&					GetTask ();
	void							ClearTask ();

	const UniString&				GetName () const;
	GS::IntPtr						GetId () const;

	const ThreadPriority			GetPriority (void) const;
	void							SetPriority (const ThreadPriority& priority);

	const ThreadLocalMap&			GetThreadLocalMap () const;

	void							PutThreadLocal    (const ThreadLocalKey& threadLocalKey, ThreadLocalValueBase* threadLocalValue);
	void							RemoveThreadLocal (const ThreadLocalKey& threadLocalKey);
	void							ClearThreadLocal  (const ThreadLocalKey& threadLocalKey);

	void							ClearThreadLocalMap ();

	void							Start ();

	bool							Join (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr);
	void							Join (bool interruptible = true);

	bool							IsInterrupted () const;
	bool							Interrupted ();
	void							Interrupt ();

	bool							IsCanceled () const;
	bool							Canceled ();
	void							Cancel ();

	void							BlockOn (Interruptible* interruptible);

// Implementation:
protected:
	virtual GS::IntPtr				GetThreadId () const = 0;

	virtual bool					Start (Runnable* runnable) = 0;

	virtual void					SetNativeThreadName (const GS::UniString& nativeThreadName) = 0;
	
	virtual void					SetThreadPriority (const ThreadPriority& priority) = 0;
	virtual const ThreadPriority	GetThreadPriority (void) const = 0;

	virtual void					Run ();

// Static operations:
public:
	static ThreadImpl*				Create (const RunnableTask& task, const UniString& name);

	static bool						IsValid (ThreadImpl* impl);

	static GS::IntPtr				GetCurrentThreadId ();

	static ThreadImpl*				GetCurrentIfExists ();
	static ThreadImpl*				GetCurrent ();
	static ThreadImpl*				GetMain ();

	static ThreadImpl*				GetImpl (const Thread& thread);
	
	static Thread					GetThread (ThreadImpl* impl);

	static PagedArray<ThreadImpl*>	GetRunningThreads ();

	static void						Sleep (UInt32 timeout, bool interruptible = true);
	static void						Yield ();

// Static implementation:
private:
	static ThreadImpl*				Create (GS::IntPtr tid, const UniString& name = "");
	static void						Launch (ThreadImpl* parent, ThreadImpl* thread);

};

////////////////////////////////////////////////////////////////////////////////
// ThreadImpl inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetMonitor
// -----------------------------------------------------------------------------

inline ThreadMonitor&	ThreadImpl::GetMonitor ()
{
	return m_monitor;
}

// -----------------------------------------------------------------------------
// AddRef
// -----------------------------------------------------------------------------

inline void		ThreadImpl::AddRef ()
{
	++ m_counter;
}

// -----------------------------------------------------------------------------
// Release
// -----------------------------------------------------------------------------

inline void		ThreadImpl::Release ()
{
	if (-- m_counter == 0) {
		delete this;
	}
}

// -----------------------------------------------------------------------------
// GetName
// -----------------------------------------------------------------------------

inline const UniString&		ThreadImpl::GetName () const
{
	return m_name;
}

// -----------------------------------------------------------------------------
// GetId
// -----------------------------------------------------------------------------

inline GS::IntPtr	ThreadImpl::GetId () const
{
	return GetThreadId ();
}

// -----------------------------------------------------------------------------
// GetPriority
// -----------------------------------------------------------------------------

inline const ThreadPriority		ThreadImpl::GetPriority (void) const
{
	return GetThreadPriority ();
}

// -----------------------------------------------------------------------------
// SetPriority
// -----------------------------------------------------------------------------

inline void		ThreadImpl::SetPriority (const ThreadPriority& priority)
{
	SetThreadPriority (priority);
}

// -----------------------------------------------------------------------------
// GetThreadLocalMap
// -----------------------------------------------------------------------------

inline const ThreadImpl::ThreadLocalMap&	ThreadImpl::GetThreadLocalMap () const
{
	return m_threadLocalMapR;
}

// -----------------------------------------------------------------------------
// Join
// -----------------------------------------------------------------------------

inline void		ThreadImpl::Join (bool interruptible)
{
	Join (Timeout::Infinite, interruptible, nullptr);
}

// -----------------------------------------------------------------------------
// IsInterrupted
// -----------------------------------------------------------------------------

inline bool		ThreadImpl::IsInterrupted () const
{
	return m_monitor.IsInterrupted ();
}

// -----------------------------------------------------------------------------
// Interrupted
// -----------------------------------------------------------------------------

inline bool		ThreadImpl::Interrupted ()
{
	return m_monitor.Interrupted ();
}

// -----------------------------------------------------------------------------
// Interrupt
// -----------------------------------------------------------------------------

inline void		ThreadImpl::Interrupt ()
{
	m_monitor.Interrupt ();
}

// -----------------------------------------------------------------------------
// IsCanceled
// -----------------------------------------------------------------------------

inline bool		ThreadImpl::IsCanceled () const
{
	return m_monitor.IsCanceled ();
}

// -----------------------------------------------------------------------------
// Canceled
// -----------------------------------------------------------------------------

inline bool		ThreadImpl::Canceled ()
{
	return m_monitor.Canceled ();
}

// -----------------------------------------------------------------------------
// Cancel
// -----------------------------------------------------------------------------

inline void		ThreadImpl::Cancel ()
{
	m_monitor.Cancel ();
}

// -----------------------------------------------------------------------------
// BlockOn
// -----------------------------------------------------------------------------

inline void		ThreadImpl::BlockOn (Interruptible* blocker)
{
	m_monitor.BlockOn (blocker);
}

}

#endif // GS_THREADIMPL_HPP
