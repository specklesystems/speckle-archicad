
// *****************************************************************************
//
// Declaration of ThreadManager class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADMANAGER_HPP
#define GS_THREADMANAGER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "FastLock.hpp"
#include "PagedArray.hpp"
#include "Singleton.hpp"
#include "ShutdownListener.hpp"
#include "StartupListener.hpp"
#include "ThreadListener.hpp"
#include "ThreadLocalKey.hpp"
#include "ThreadImpl.hpp"



// --- ThreadManager class -----------------------------------------------------

namespace GS {

class ThreadManager {

// Friend classes:
friend class LazyInstantiationPolicy;
friend class ThreadImpl;

// Type definitions:
private:
	typedef PagedArray<ThreadImpl*>	ThreadList;
	typedef PagedArray<ThreadListener*> ThreadListeners;
	typedef PagedArray<ShutdownListener*> ShutdownListeners;
	typedef PagedArray<StartupListener*> StartupListeners;
	typedef PagedArray<RunnableTask> ShutdownTasks;

// Static data members:
private:
	static GS::IntPtr		theMainThreadId;		// The thread identifier of the main thread
	static bool				initialized;			// theMainThreadId is initialized

// Data members:
private:
	ThreadImpl*				m_mainThread;			// The main thread

	ThreadList				m_runningThreads;		// The list of the running threads (threads started through threading package APIs)
	ThreadList				m_wrapperThreads;		// The list of the wrapped threads (threads not started through threading package APIs)

	ShutdownListeners		m_shutdownListeners;	// The list of shutdown listeners (shutdown listeners are notified during shutdown procedure, prior all threads to be shutdown)
	StartupListeners		m_startupListeners;		// The list of startup listeners (startup listeners are notified during startup procedure, during threading initialization)
	ShutdownTasks			m_shutdownTasks;		// The list of shutdown tasks (shutdown tasks are executed during the shutdown procedure, prior all threads to be shutdown)

	ThreadListeners			m_threadListeners;		// The list of thread life cycle listeners

	mutable FastLock		m_lock;					// Lock for serializing the access to the internal state
	ThreadImpl*				m_waiter;				// The thread waiting for the thread shutdown procedure completion

// Construction / destruction:
private:
	 ThreadManager ();
	 ThreadManager (const ThreadManager&); // Disabled
public:
	~ThreadManager ();

// Operator overloading:
private:
	const ThreadManager&	operator = (const ThreadManager&); // Disabled

// Operations:
public:
	ThreadImpl*				GetMainThread ();
	PagedArray<ThreadImpl*>	GetRunningThreads ();

	bool					IsValidThread (ThreadImpl* thread) const;

	void					AddRunningThread    (ThreadImpl* thread);
	void					RemoveRunningThread (ThreadImpl* thread);

	void					AddWrapperThread (ThreadImpl* thread);

	USize					GetAttachedShutdownListeners (PagedArray<ShutdownListener*>& shutdownListeners) const;
	bool					IsShutdownListenerAttached (ShutdownListener* shutdownListener) const;

	void					AttachShutdownListener (ShutdownListener* shutdownListener);
	bool					DetachShutdownListener (ShutdownListener* shutdownListener);

	void					DetachShutdownListeners ();

	USize					GetAttachedStartupListeners (PagedArray<StartupListener*>& startupListeners) const;
	bool					IsStartupListenerAttached (StartupListener* startupListener) const;
	
	void					AttachStartupListener (StartupListener* startupListener);
	bool					DetachStartupListener (StartupListener* startupListener);
	
	void					DetachStartupListeners ();

	USize					GetRegisteredShutdownTasks (PagedArray<RunnableTask>& shutdownTasks) const;
	bool					IsShutdownTaskRegistered (const RunnableTask& shutdownTask) const;

	void					RegisterShutdownTask (const RunnableTask& shutdownTask);
	bool					RevokeShutdownTask (const RunnableTask& shutdownTask);
	void					ClearShutdownTasks ();

	USize					GetAttachedThreadListeners (PagedArray<ThreadListener*>& threadListeners) const;
	bool					IsThreadListenerAttached (ThreadListener* threadListener) const;

	void					AttachThreadListener (ThreadListener* threadListener);
	bool					DetachThreadListener (ThreadListener* threadListener);

	void					DetachThreadListeners ();

	void					ClearThreadLocals (const ThreadLocalKey& threadLocalKey);

	void					Shutdown ();
	void					Startup ();

// Implementation:
private:
	void					FireThreadCreated (ThreadImpl* thread);
	void					FireThreadStarted (ThreadImpl* thread);
	void					FireThreadStopped (ThreadImpl* thread);
	void					FireThreadDeleted (ThreadImpl* thread);

	void					ThreadStarted (ThreadImpl* thread);
	void					ThreadStopped (ThreadImpl* thread);

	void					ReportStuckThreadsAtShutdown (UInt16 waitTime);

	USize					CopyRunningThreads (PagedArray<ThreadImpl*>& target) const;
	USize					CopyWrapperThreads (PagedArray<ThreadImpl*>& target) const;
	
	USize					CopyThreads (PagedArray<ThreadImpl*>& target) const;

// Static operations:
public:
	static GS::IntPtr		GetMainThreadId ();
	static void				SetMainThreadId (GS::IntPtr mainThreadId = 0);

	static bool				IsInitialized ();

	static ThreadManager&	GetInstance ();

};

////////////////////////////////////////////////////////////////////////////////
// ThreadManager inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetMainThreadId
// -----------------------------------------------------------------------------

inline GS::IntPtr		ThreadManager::GetMainThreadId ()
{
	return theMainThreadId;
}

// -----------------------------------------------------------------------------
// SetMainThreadId
// -----------------------------------------------------------------------------

inline void		ThreadManager::SetMainThreadId (GS::IntPtr mainThreadId)
{
	if (mainThreadId == 0) {
		mainThreadId = ThreadImpl::GetCurrentThreadId ();
	}
	
	theMainThreadId = mainThreadId;
	
	initialized = true;
}

// -----------------------------------------------------------------------------
// IsMainThreadIdSet
// -----------------------------------------------------------------------------

inline bool		ThreadManager::IsInitialized ()
{
	return initialized;
}

}

#endif // GS_THREADMANAGER_HPP
