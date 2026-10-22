
// *****************************************************************************
//
// Declaration of DirectExecutor class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_DIRECTEXECUTOR_HPP
#define GS_DIRECTEXECUTOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Executor.hpp"
#include "Lock.hpp"



// --- DirectExecutor class ----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT DirectExecutor : public Executor {

// Data members:
private:
	mutable Lock			m_lock;			// Lock for serializing access to the internal state
	bool					m_canceled;		// Canceled flag

// Construction / destruction:
public:
			 DirectExecutor ();
private:
			 DirectExecutor (const DirectExecutor&); // Disabled
public:
	virtual ~DirectExecutor ();

// Operator overloading:
private:
	const DirectExecutor&	operator = (const DirectExecutor&); // Disabled

// Executor interface implementation:
public:
	virtual void			Execute (const RunnableTask& runnable) override;
	virtual AsyncResultPtr	Execute (const CallableTask& callable) override;

// Cancelable interface implementation:
public:
	virtual bool			IsCanceled () const override;
	virtual void			Cancel () override;

// Waitable interface implementation:
public:
	virtual bool			Wait (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool			Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void			Wait (bool interruptible = true) override;

};

}

#endif // GS_DIRECTEXECUTOR_HPP
