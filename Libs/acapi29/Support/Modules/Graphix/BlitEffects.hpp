// *****************************************************************************
// File:			BlitEffects.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef BLITEFFECTS_HPP
#define BLITEFFECTS_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"					// GRAPHIX_DLL_EXPORT
#include "Color.hpp"


// --- Class declarations ------------------------------------------------------

namespace NewDisplay {

class GRAPHIX_DLL_EXPORT BlitEffect
{
protected:
	BlitEffect () = default;

public:
	virtual ~BlitEffect ();

	virtual BlitEffect* Clone	() const = 0;
	virtual bool		IsEqual	(const BlitEffect& other) const = 0;
};


class GRAPHIX_DLL_EXPORT FalseColorBlitEffect: public BlitEffect
{
public:
	const Gfx::Color blackColor;
	const Gfx::Color whiteColor;

public:
	FalseColorBlitEffect (const Gfx::Color blackColor, const Gfx::Color whiteColor);
	virtual ~FalseColorBlitEffect ();

	virtual BlitEffect* Clone () const override { return new FalseColorBlitEffect (blackColor, whiteColor);  }

	virtual bool IsEqual (const BlitEffect& other) const override;
};

}

#endif
