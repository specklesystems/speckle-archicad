
// *****************************************************************************
//
// Declaration of ThreadedExecutor class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADEDEXECUTOR_HPP
#define GS_THREADEDEXECUTOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Executor.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class ThreadedExecutorImpl;

}



// --- ThreadedExecutor class --------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ThreadedExecutor : public Executor {

// Type definitions:
private:
	typedef CountedPtr<ThreadedExecutorImpl, AtomicCounter> ThreadedExecutorImplPtr;

// Data members:
private:
	ThreadedExecutorImplPtr		m_impl;

// Construction / destruction:
public:
			 ThreadedExecutor ();
private:
			 ThreadedExecutor (const ThreadedExecutor&); // Disabled
public:
	virtual ~ThreadedExecutor ();

// Operator overloading:
private:
	const ThreadedExecutor&		operator = (const ThreadedExecutor&); // Disabled

// Executor interface implementation:
public:
	virtual void				Execute (const RunnableTask& runnable) override;
	virtual AsyncResultPtr		Execute (const CallableTask& callable) override;

// Cancelable interface implementation:
public:
	virtual bool				IsCanceled () const override;
	virtual void				Cancel () override;

// Waitable interface implementation:
public:
	virtual bool				Wait (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool				Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void				Wait (bool interruptible = true) override;

};

}

#endif // GS_THREADEDEXECUTOR_HPP
