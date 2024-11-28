// *****************************************************************************
// File:			RenderingEffects.hpp
//
// Description:		Rendering effects for pointcloud renderers
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	RENDERINGEFFECTS_HPP
#define	RENDERINGEFFECTS_HPP

// --- Includes ----------------------------------------------------------------

#include "PointCloudDefinitions.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace	NewDisplay {
	class	BlitEffect;
};


namespace	PC	{

// --- Base rendering effect class ---------------------------------------------

class	POINTCLOUD_DLL_EXPORT	IRenderingEffect
{
public:
	IRenderingEffect ();
	virtual	~IRenderingEffect ();
};


// --- Falsecolor rendering effect ---------------------------------------------

class	POINTCLOUD_DLL_EXPORT	FalseColorRenderingEffect: public IRenderingEffect
{
public:
	float blackColorRed, blackColorGreen, blackColorBlue;
	float whiteColorRed, whiteColorGreen, whiteColorBlue;

public:
	FalseColorRenderingEffect (float blackColorRed, float blackColorGreen, float blackColorBlue,
								float whiteColorRed, float whiteColorGreen, float whiteColorBlue);
	
	virtual	~FalseColorRenderingEffect ();
};


// --- Rendering effect created on top of a Graphix bliteffect -----------------

class	POINTCLOUD_DLL_EXPORT	GraphixBlitEffect: public IRenderingEffect
{
public:
	NewDisplay::BlitEffect*	blitEffect;
	
public:
	GraphixBlitEffect (NewDisplay::BlitEffect* blitEffect);		// Empty effect if blitEffect is nullptr
	virtual ~GraphixBlitEffect ();
};

} // namespace PC


#endif	// RENDERINGEFFECTS_HPP