
// *****************************************************************************
//
// Declaration of MessageLoopExecutor class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_MESSAGELOOPEXECUTOR_HPP
#define GS_MESSAGELOOPEXECUTOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Executor.hpp"
#include "MessageTarget.hpp"



// --- MessageLoopExecutor class -----------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT MessageLoopExecutor : public Executor {

// Construction / destruction:
public:
	MessageLoopExecutor ();

// Operations:
public:
	bool						CanExecuteTask () const;

	void						Execute (const RunnableTask& runnable, Message::Priority priority);
	AsyncResultPtr				Execute (const CallableTask& callable, Message::Priority priority);

	void						ExecuteAndWait (const RunnableTask& runnable, Message::Priority priority = Message::Top);
	AsyncResultPtr				ExecuteAndWait (const CallableTask& callable, Message::Priority priority = Message::Top);

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

#endif // GS_MESSAGELOOPEXECUTOR_HPP
