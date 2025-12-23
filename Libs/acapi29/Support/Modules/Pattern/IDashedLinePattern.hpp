// Contact person : NN

#ifndef I_DASHEDLINEPATTERN_HPP
#define I_DASHEDLINEPATTERN_HPP

#pragma once

// from Pattern
#include "PatternExport.h"


namespace GX {
namespace Pattern {

class PATTERN_DLL_EXPORT IDashedLinePattern
{
public:
	class PATTERN_DLL_EXPORT DashItem
	{
	public:
		DashItem (double dashLength, double gapLength);
		~DashItem ();

		double GetDashLength		() const;
		double GetGapLength			() const;
		double GetTotalItemLength	() const;

	private:
		const double dashLength;
		const double gapLength;
	};

	virtual ~IDashedLinePattern ();

	virtual bool		ScaledWithPlan			()					const = 0;
	virtual	UInt32		GetDashNum				()					const = 0;
	virtual DashItem	GetDashItem				(UIndex idx)		const = 0;
	virtual double		GetCenterPosition		(double lineLength)	const = 0;
	virtual double		GetMinimalDashLength	()					const = 0;
};

}
}

#endif
