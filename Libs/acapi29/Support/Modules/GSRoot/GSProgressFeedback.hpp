#ifndef GSPROGRESSFEEDBACK_HPP
#define GSPROGRESSFEEDBACK_HPP

#pragma once

#include "ThreadingDebug.hpp"
#include "Channel.hpp"
#include "UniString.hpp"
#include "GSRootExport.hpp"


class GSROOT_DLL_EXPORT ProgressFeedback
{
public:
	virtual ~ProgressFeedback ();

	virtual void	InitProcessWindowNext (short procResID, bool showImmediately = false);
	virtual void	BeginNextProcessPhase (short phaseResID);

	class Phase {
	public:
		Phase (ProgressFeedback& progressFeedback, short phaseResID, bool set = true)
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