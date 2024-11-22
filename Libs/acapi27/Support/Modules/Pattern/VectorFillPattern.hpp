// Contact person : KiP

#ifndef VECTORFILLPATTERN_HPP
#define VECTORFILLPATTERN_HPP

#pragma once

// Geometry
#include "Point2D.hpp"

// Pattern
#include "PatternExport.h"


namespace GX 
{
namespace Pattern 
{

class PATTERN_DLL_EXPORT VectorFillPattern
{
public:
	class PATTERN_DLL_EXPORT LineGroup
	{
	public:
		virtual ~LineGroup ();

		virtual	const Coord		GetOffset () const = 0;
		virtual	double			GetAngle () const = 0;
		virtual	double			GetPerpendicularOffset () const = 0;
		virtual	double			GetDirectionalOffset () const = 0;
		virtual	bool			IsDashedLine () const = 0;
		virtual	double			GetPeriodLength () const = 0;
		virtual UInt32			GetLinePartLengthsNum () const = 0;
		virtual double			GetLinePartLength (UIndex linePartIdx) const = 0;
	};

	virtual ~VectorFillPattern ();

	virtual	double		GetXSpacingFactor () const = 0;
	virtual	double		GetYSpacingFactor () const = 0;
	virtual	double		GetAngle () const = 0;
	virtual void		EnumerteLineGroups (const std::function<void (const LineGroup& lineGroup)>& processor) const = 0;
	virtual	bool		ScaledWithPlan () const = 0;
};

}
}

#endif