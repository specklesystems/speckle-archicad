#ifndef GSPROGRESSFEEDBACK_HPP
#define GSPROGRESSFEEDBACK_HPP

#pragma once

#include "ThreadingDebug.hpp"
#include "Channel.hpp"
#include "UniString.hpp"
#include "GSRootExport.hpp"


class GSROOT_DLL_EXPORT DummyReportChannel: public GS::OChannel {
public:
	DummyReportChannel ();

	virtual GSErrCode	WriteBin (const char* source, USize nOfCharToWrite, USize* written = nullptr) override;
	virtual	GSErrCode	DirectOutputAccess (UIndex startPosition, char** output, USize* accessibleDataSize) override;
	virtual GSErrCode   GetOutputPosition (UInt64* pos) const override;

	virtual	void		SetDefaultOutputProtocol (void) override;

	virtual GSErrCode	PushMark	(void) override;
	virtual GSErrCode	PopMark		(void) override;
	virtual USize		GetOffset	(void) const override;
	virtual void		ResetOffset	(void) override;

	virtual GSErrCode	GetOutputStatus	  (void) const override;
	virtual void		ResetOutputStatus (void) override;
};


class GSROOT_DLL_EXPORT ProgressFeedback
{
private:
	DummyReportChannel dummyReportChannel;

public:
	virtual ~ProgressFeedback ();

	virtual void	InitProcessWindowNext (short procResID, const bool showImmediately = false);
	virtual void	BeginNextProcessPhase (short phaseResID);

	virtual GS::OChannel&	GetReportChannel (void);

	class Phase
	{
		ProgressFeedback& progressFeedback;
		const bool		set;
	public:
		Phase (ProgressFeedback& progressFeedback, short phaseResID, bool set = true):
		  progressFeedback (progressFeedback),
			  set (set)
		  {
			  if (set) {
				  progressFeedback.BeginNextProcessPhase (phaseResID);
			  }
		  }
	};

	virtual void	SetProcessPhaseString (const GS::UniString& phaseString);
	virtual void	SetProcessPhaseNum (Int32 phaseNum);
	virtual void	SetProcessName (const GS::UniString& processName);
	virtual void	SetProcessPhaseValue (Int32 value);
	virtual bool	ProcessWindowOn (void);
	virtual void	CloseProcessWindow (void);

protected:
	enum CheckMode {
		Check,
		RegisterOnly,
		SkipEntirely
	};

	ProgressFeedback ();
};


#endif