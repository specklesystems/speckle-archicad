// *****************************************************************************
//
// Declaration of Thread class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREAD_HPP
#define GS_THREAD_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Cancelable.hpp"
#include "Interruptible.hpp"
#include "RunnableTask.hpp"
#include "ThreadState.hpp"
#include "UniString.hpp"
#include "Waitable.hpp"
#include "ThreadPriority.hpp"
#include "PagedArray.hpp"

#ifdef Yield
#undef Yield
#endif




// --- Forward declarations ----------------------------------------------------

namespace GS {

class ThreadImpl;

}



// --- Thread class ------------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Thread : public Cancelable, public Waitable {

// Friend classes:
friend class ThreadImpl;

// Data members:
private:
	ThreadImpl*			m_impl;

// Construction / destruction:
private:
	explicit Thread (ThreadImpl* impl);
public:
			 Thread ();
			 Thread (const RunnableTask& task, const UniString& name);
			 Thread (const Thread& rhs);
	virtual ~Thread ();

// Operator overloading:
public:
	const Thread&		operator =  (const Thread& rhs);

	bool				operator == (const Thread& rhs) const;
	bool				operator != (const Thread& rhs) const;

// Operations:
public:
	const RunnableTask&	GetTask () const;
	const UniString&	GetName () const;
	GS::IntPtr			GetId () const;

	const ThreadPriority	GetPriority (void) const;
	void					SetPriority (const ThreadPriority& priority);

	const ThreadState&	GetState () const;

	void				Start ();

	bool				Join (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr);
	bool				Join (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr);
	void				Join (bool interruptible = true);

	bool				IsInterrupted () const;
	void				Interrupt ();

	void				BlockOn (Interruptible* blocker);

	void				Clear ();

// Cancelable interface implementation:
public:
	virtual bool		IsCanceled () const override;
	virtual void		Cancel () override;

// Waitable interface implementation:
public:
	virtual bool		Wait (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool		Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void		Wait (bool interruptible = true) override;

// Static operations:
public:
	static Thread		GetCurrent ();
	static Thread		GetMain ();
	static bool			IsMain ();

	static PagedArray<Thread>	GetThreads ();

	static GS::IntPtr	GetCurrentThreadId ();

	static bool			Interrupted ();
	static bool			Canceled ();

	static void			Sleep (const Timeout& timeout, bool interruptible = true);
	static void			Sleep (UInt32 timeout, bool interruptible = true);

	static void			Yield ();

// Implementation:
private:
	void				CheckState (const char* sourceFile, UInt32 sourceLine) const;

};

////////////////////////////////////////////////////////////////////////////////
// Thread inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Thread::Thread () :
	m_impl (nullptr)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		Thread::operator == (const Thread& rhs) const
{
	return (m_impl == rhs.m_impl);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		Thread::operator != (const Thread& rhs) const
{
	return (m_impl != rhs.m_impl);
}

}

#endif // GS_THREAD_HPP
