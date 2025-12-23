#ifndef GSABORTCONDITIONS_HPP
#define GSABORTCONDITIONS_HPP

#pragma once

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "GSException.hpp"
#include "Ref.hpp"

#include "GSAbort.hpp"

#include "Array.hpp"
#include "GSTime.hpp"

namespace GS {


// Abort utility

GSROOT_DLL_EXPORT AbortInterfaceBaseRef	 GetNeverAbortBase ();
GSROOT_DLL_EXPORT AbortInterfaceRef		 GetNeverAbort ();


// EveryConditionMetAbort

class GSROOT_DLL_EXPORT EveryConditionMetAbort : public AbortInterfaceBase
{
public:
	void AddCondition (AbortInterfaceBaseRef abortCondition);

	virtual bool ShouldAbort () noexcept override;

private:
	GS::Array<AbortInterfaceBaseRef> conditions;
};


// AnyConditionMetAbort

class GSROOT_DLL_EXPORT AnyConditionMetAbort : public AbortInterfaceBase
{
public:
	void AddCondition (AbortInterfaceBaseRef abortCondition);

	virtual bool ShouldAbort () noexcept override;

private:
	GS::Array<AbortInterfaceBaseRef> conditions;
};


// ElapsedTimeExceededAbort

class GSROOT_DLL_EXPORT ElapsedTimeExceededAbort : public AbortInterfaceBase
{
public:
	ElapsedTimeExceededAbort (double timeLimitSec);

	virtual bool ShouldAbort () noexcept override;

private:
	GSFineTicks startTime;
	const double timeLimitSec;
};


} // namespace GS

#endif
