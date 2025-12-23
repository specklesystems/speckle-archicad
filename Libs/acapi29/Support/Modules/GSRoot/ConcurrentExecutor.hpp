
// *****************************************************************************
//
// Declaration of ConcurrentExecutor class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_CONCURRENTEXECUTOR_HPP
#define GS_CONCURRENTEXECUTOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Executor.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class ConcurrentExecutorImpl;

}



// --- ConcurrentExecutor class ------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ConcurrentExecutor : public Executor {

// Type definitions:
private:
	typedef CountedPtr<ConcurrentExecutorImpl, AtomicCounter> ConcurrentExecutorImplPtr;

// Data members:
private:
	ConcurrentExecutorImplPtr	m_impl;

// Construction / destruction:
public:
			 ConcurrentExecutor ();
private:
			 ConcurrentExecutor (const ConcurrentExecutor&); // Disabled
public:
	virtual ~ConcurrentExecutor ();

// Operator overloading:
private:
	const ConcurrentExecutor&	operator = (const ConcurrentExecutor&); // Disabled

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

#endif // GS_CONCURRENTEXECUTOR_HPP
