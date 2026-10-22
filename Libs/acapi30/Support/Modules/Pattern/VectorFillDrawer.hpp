// Contact person : KiP

#ifndef VECTORFILLDRAWER_HPP
#define VECTORFILLDRAWER_HPP

#pragma once

// Geometry
#include "IrregularPolygon2DClassDefinition.hpp"

// Pattern
#include "PatternExport.h"
#include "PatternTypeDefinitions.hpp"



namespace GX 
{
namespace Pattern 
{

class HatchInfo;
class HatchTran;
class VectorFillPattern;
class FillPatternPrimitivesDrawer;

class PATTERN_DLL_EXPORT VectorFillDrawer
{
public:
	static GSErrCode Draw (const HatchInfo&						hatchInfo,
						   const Geometry::IrregularPolygon2D&	polygon, 
						   FillPatternPrimitivesDrawer*			drawHatch,
						   const HatchTran&						hatchTran);	// this signature fits to GX::Pattern::DrawHatch_VectorFill

	static GSErrCode Draw (const Geometry::IrregularPolygon2D&	polygon,
						   const HatchTran&						hatchTran,
						   double								scalingFactor,
						   double								scalePaperToModel,
						   const VectorFillPattern&				pattern,
						   FillPatternPrimitivesDrawer*			drawer);

	static GSErrCode GetHatchToModelTransformation (const HatchInfo&			hatchInfo,
													const HatchTran&			hatchTran,
													Geometry::Matrix33&			transformation);
	
};

}
}

#endif