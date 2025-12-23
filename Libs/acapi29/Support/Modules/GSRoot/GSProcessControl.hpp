#ifndef GSPROCESSCONTROL_HPP
#define GSPROCESSCONTROL_HPP

#pragma once

#include "GSRootExport.hpp"
#include "GSAbort.hpp"
#include "GSProgressFeedback.hpp"
#include "Lock.hpp"

namespace GS {

class GSROOT_DLL_EXPORT ProcessControl: public AbortInterfaceBase,
										public ProgressFeedback
{
public:
	virtual ~ProcessControl ();

	virtual bool	TestBreak () = 0;
	virtual bool	WasBreak () const = 0;

private:
	bool registered;

protected:
	ProcessControl (CheckMode check, ProcessControl* parentProcess);
};

//the ProcessControlInterruptDelegate disregards any feedback, only handles interrupt, usefull when starting a sub - process, which should not update the phase, or handle any feedback.
class GSROOT_DLL_EXPORT ProcessControlInterruptDelegate : public ProcessControl
{
public: 
	ProcessControlInterruptDelegate (ProcessControl* toDelegateToInit = nullptr);
	virtual ~ProcessControlInterruptDelegate ();

	//delegating interrupts:
	void			EnableInterrupts ();
	void			DisableInterrupts ();

	virtual bool	ShouldAbort () noexcept override;

	virtual bool	TestBreak () override;
	virtual bool	WasBreak () const override;

	//disregarding all feedbacks:
	virtual void	InitProcessWindowNext (short /*procResID*/, bool /*showImmediately*/ = false) override {}
	virtual void	BeginNextProcessPhase (short /*phaseResID*/) override {}


	virtual void	SetProcessPhaseString (const GS::UniString& /*phaseString*/) override {}
	virtual void	SetProcessPhaseNum (Int32 /*phaseNum*/) override {}

	virtual bool	ProcessWindowOn (void) override { return false; }
	virtual void	CloseProcessWindow (void) override {}

private:
	ProcessControl*		toDelegateTo;
	mutable GS::Lock	interruptsEnabledLock; 
	bool				interruptsEnabled; 
};
	
class GSROOT_DLL_EXPORT NonInterruptibleProcessControl: public ProcessControl,
														public NonThreadSafeClass
{
public:
	explicit NonInterruptibleProcessControl (bool check = true);
	virtual ~NonInterruptibleProcessControl ();

	virtual bool	TestBreak () override;
	virtual bool	WasBreak () const override;
	virtual bool	ShouldAbort () noexcept override;
};


class GSROOT_DLL_EXPORT SimpleInterruptibleProcessControl:	public ProcessControl,
															public NonThreadSafeClass
{
private:
	bool wasBreak;

public:
	explicit SimpleInterruptibleProcessControl (bool check = true);
	virtual ~SimpleInterruptibleProcessControl ();

	virtual bool	TestBreak () override;
	virtual bool	WasBreak () const override;
	virtual bool	ShouldAbort () noexcept override;

	virtual bool	TestBreakToOverride () = 0;
};


class GSROOT_DLL_EXPORT ProcessControlDelegate: public ProcessControl
{
public:
	virtual ~ProcessControlDelegate ();

	virtual bool	ShouldAbort () noexcept override;

	virtual bool	TestBreak () override;
	virtual bool	WasBreak () const override;

	virtual void	InitProcessWindowNext (short procResID, const bool showImmediately = false) override;
	virtual void	BeginNextProcessPhase (short phaseResID) override;

	virtual void	SetProcessPhaseString (const GS::UniString& phaseString) override;
	virtual void	SetProcessPhaseNum (Int32 phaseNum) override;

	virtual bool	ProcessWindowOn (void) override;
	virtual void	CloseProcessWindow (void) override;

protected:
	ProcessControlDelegate (ProcessControl& toDelegateTo);

private:
	ProcessControl& toDelegateTo;
};


class GSROOT_DLL_EXPORT SafeProcessControl
{
	ProcessControl* processControl;
	bool			ownProcessControl;

public:
	SafeProcessControl ();
	SafeProcessControl (ProcessControl& processControl);
	~SafeProcessControl ();

	ProcessControl& GetProcessControl ();
	void SetProcessControl (ProcessControl& processControl);

};

}	// namespace GS

#endif
