// Contact person : NN

#ifndef DASHEDLINEPATTERN_HPP
#define DASHEDLINEPATTERN_HPP

#pragma once

// from GSRoot
#include "Array.hpp"
#include "Pair.hpp"

// from Pattern
#include "IDashedLinePattern.hpp"


namespace GX {
namespace Pattern {


class PATTERN_DLL_EXPORT DashedLinePattern : public IDashedLinePattern
{
public:
	DashedLinePattern ();
	DashedLinePattern (GS::Array<IDashedLinePattern::DashItem>& dashItems, 
					   bool										scaledWithPlan);

	virtual ~DashedLinePattern ();

	virtual bool							ScaledWithPlan			() const override;
	virtual	UInt32							GetDashNum				() const override;
	virtual IDashedLinePattern::DashItem	GetDashItem				(UIndex idx) const override;
	virtual double							GetCenterPosition		(double lineLength) const override;
	virtual double							GetMinimalDashLength	() const override;

private:
			void							CalculateCenterPosition ();
			void							CalculateMinimalDashLength ();

	GS::ArrayFB<IDashedLinePattern::DashItem, 6>	dashItems;
	bool											scaledWithPlan;
	GS::Array<GS::Pair<double, double>>				centerPositionStore;
	double											minimalDashLength;
};


}
}

#endif
