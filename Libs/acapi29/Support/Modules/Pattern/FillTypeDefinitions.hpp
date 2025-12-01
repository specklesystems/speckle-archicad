// Contact person : KiP

#ifndef FILL_TYPE_DEFINITIONS_HPP
#define FILL_TYPE_DEFINITIONS_HPP

#pragma once

namespace GX 
{
namespace Pattern 
{

const short	MaxFillNumber	= 8191;		// max. number of fills

enum FillTypes 
{
	VectorFill			= 0,
	SymbolFill			= 1,
	SolidFill			= 2,
	EmptyFill_Deleted	= 3,
	LinearGradientFill	= 4,
	RadialGradientFill	= 5,
	ImageFill			= 6
};

enum FillTypeBits 
{
	ScaledBit	= 0,	
	SectionBit	= 1,	
	DrawingBit	= 2,	
	SurfaceBit	= 3		
};

#define	ScaledFill		(1<<GX::Pattern::ScaledBit)
#define	SectionFill		(1<<GX::Pattern::SectionBit)
#define	DrawingFill		(1<<GX::Pattern::DrawingBit)
#define	SurfaceFill		(1<<GX::Pattern::SurfaceBit)

}
}

#endif
