#ifndef HATCH_PRIORITY_COMPARER_HPP
#define HATCH_PRIORITY_COMPARER_HPP

#pragma once

// from GSRoot
#include "Definitions.hpp"

// from VectorImage
#include "VectorImageExport.h"
#include "PriorityCompareResult.hpp"

class VectorImage;
class Sy_HatchType;
class HatchObject;

namespace GS {
	class Guid;
}

namespace VI {
namespace HatchPriority {

class ComparerEnvironment
{
public:
	virtual ~ComparerEnvironment ();

	virtual const HatchObject&	GetHatchObject				(const Sy_HatchType& syHatch) const = 0;
	virtual UInt32				GetHatchDisplayOrderIndex	(const GS::Guid& hatchId) const = 0;
};

class VI_DLL_CLASS_EXPORT HatchPriorityComparer
{
public:
	virtual ~HatchPriorityComparer ();

	virtual PriorityCompareResult Compare (const ComparerEnvironment& comparerEnvironment,
										   const Sy_HatchType& lhs, 
										   const Sy_HatchType& rhs) const = 0;
};

}
}

#endif
