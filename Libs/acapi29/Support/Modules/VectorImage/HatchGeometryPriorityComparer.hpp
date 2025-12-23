#ifndef HATCH_GEOMETRY_PRIORITY_COMPARER_HPP
#define HATCH_GEOMETRY_PRIORITY_COMPARER_HPP

#pragma once

// from GSRoot
#include "Definitions.hpp"

// from VectorImage
#include "VectorImageExport.h"
#include "PriorityCompareResult.hpp"

namespace GS {
	class Guid;
}

class Sy_HatchType;
class HatchObject;
class ConstVIMGuidPolyPair;

namespace VI {
namespace HatchGeometryPriority {

class ComparerEnvironment
{
public:
	virtual ~ComparerEnvironment ();

	virtual const Sy_HatchType* GetOriginalSyHatch (const GS::Guid& actualPolyId) const = 0;
	virtual const HatchObject&	GetHatchObject (const Sy_HatchType& syHatch) const = 0;
	virtual UInt32				GetOriginalImageHatchDisplayOrderIndex (const GS::Guid& hatchId) const = 0;
};

class VI_DLL_CLASS_EXPORT HatchGeometryPriorityComparer
{
public:
	virtual ~HatchGeometryPriorityComparer ();

	virtual PriorityCompareResult Compare (const ComparerEnvironment& comparerEnvironment,
										   const ConstVIMGuidPolyPair& lhs, 
										   const ConstVIMGuidPolyPair& rhs) const = 0;
};

}
}

#endif
