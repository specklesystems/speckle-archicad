// ****************************************************************************
// File:			LowLevelObjectsG3x.hpp
//
// Description:		Common lowlevel object interfaces usable only with
//                  G3x GPU generation model
//
// Contact person:	DG
//
// SG compatible
// ****************************************************************************

#ifndef	LOWLEVELOBJECTSG3x_HPP
#define	LOWLEVELOBJECTSG3x_HPP

// --- Includes ----------------------------------------------------------------

#include	"LowLevelObjects.hpp"


namespace	Graphix	{

// --- Vertex input layout -----------------------------------------------------

enum	InputElementFormatG3x	{
	IEF_R32F_3x	=	0,
	IEF_RG32F_3x,
	IEF_RGB32F_3x,
	IEF_RGBA32F_3x,

	IEF_RGBA8UNORM_3x,

	IEF_R32UINT,
	IEF_RG32UINT,
	IEF_RGB32UINT,
	IEF_RGBA32UINT,

	IEF_R32SINT,
	IEF_RG32SINT,
	IEF_RGB32SINT,
	IEF_RGBA32SINT,

	NumOfInputElementFormatG3x
};


// --- Viewport ----------------------------------------------------------------

struct	ViewportG3x
{
	float			x;
	float			y;
	float			width;
	float			height;
	float			zMin;
	float			zMax;
};

// --- Blending state ----------------------------------------------------------

enum	BlendOp
{
	BO_Add		=	0,
	BO_Subtract,
	BO_RevSubtract,
	BO_Min,
	BO_Max
};


struct BlendG3x
{
	bool		blendEnable;
	BlendMode	srcBlend;
	BlendMode	dstBlend;
	BlendOp		blendOp;
	BlendMode	srcBlendAlpha;
	BlendMode	dstBlendAlpha;
	BlendOp		blendOpAlpha;
	UInt32		writeMask;
};

// --- Rasterizer state --------------------------------------------------------

struct RasterizerG3x
{
	LLCullMode	cullMode;						// Default: CM_None
	Int32		depthBias;						// Default: 0
	float		slopeScaleDepthBias;			// Default: 0.0f
	//bool		frontCounterClockwise;			// Default: false
	bool		scissorEnable;					// Default: false
	bool		depthClampEnable;				// Default: false
};


// --- Geometry shader ---------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	GeometryShader
{
public:
	virtual	~GeometryShader ();
};


// --- Uniform buffer ----------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	UniformBuffer
{
public:
	void*	buffer;
	UInt32	size;

public:
	UniformBuffer ();
	virtual	~UniformBuffer ();

	virtual	void	Update () = 0;
};

} // namespace Graphix

#endif	// LOWLEVELOBJECTSG3x_HPP
