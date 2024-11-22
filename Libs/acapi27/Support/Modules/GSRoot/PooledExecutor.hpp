
// *****************************************************************************
//
// Declaration of PooledExecutor class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_POOLEDEXECUTOR_HPP
#define GS_POOLEDEXECUTOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Executor.hpp"
#include "UniString.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class PooledExecutorImpl;

}



// --- PooledExecutor class ----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT PooledExecutor : public Executor {

// Type definitions:
private:
	typedef CountedPtr<PooledExecutorImpl, AtomicCounter> PooledExecutorImplPtr;

// Static constants:
public:
	static const UInt32			DefaultKeepAliveTime = 300000;

// Data members:
private:
	PooledExecutorImplPtr		m_impl;			// The implementation of the pooled executor
	RunnableTask				m_shutdownTask;	// Shutdown task for the pooled executor

// Construction / destruction:
public:
			 PooledExecutor (UInt32 minPoolSize, UInt32 maxPoolSize, UInt32 keepAliveTime = DefaultKeepAliveTime, const UniString& threadNamePrefix = GS::EmptyUniString);
			 PooledExecutor (UInt32 minPoolSize, UInt32 maxPoolSize, const UniString& threadNamePrefix);
private:
			 PooledExecutor (const PooledExecutor&); // Disabled
public:
	virtual ~PooledExecutor ();

// Operator overloading:
private:
	const PooledExecutor&		operator = (const PooledExecutor&); // Disabled

// Operations:
public:
	UInt32						GetMinimumPoolSize () const;
	UInt32						GetMaximumPoolSize () const;

	UInt32						GetKeepAliveTime () const;

	bool						IsShutdown () const;
	void						Shutdown ();

	bool						IsTerminating () const;
	bool						IsTerminated () const;

	bool						WaitTermination (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr);
	bool						WaitTermination (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr);
	void						WaitTermination (bool interruptible = true);

	bool						Remove (const RunnableTask& runnable);
	bool						Remove (const CallableTask& callable);

	void						Clear ();

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

// Static operations:
public:
	static const RunnableTask&	GetTask ();
};

}

#endif // GS_POOLEDEXECUTOR_HPP
