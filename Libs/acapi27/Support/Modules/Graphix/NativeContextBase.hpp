// *****************************************************************************
// File:			NativeContextBase.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef NATIVECONTEXTBASE_HPP
#define NATIVECONTEXTBASE_HPP

// --- Includes ----------------------------------------------------------------

#ifdef	WINDOWS
#include <Win32Interface.hpp>
#endif

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT
#include "Pattern.hpp"					// Gfx::Pattern
#include "CountedPtr.hpp"
#include "Rect.hpp"

#define	ARGB(a, r, g, b)	((((UInt32) (a)) << 24) | (((UInt32) (r)) << 16) | (((UInt32) (g)) << 8) | (((UInt32) (b)) << 0))

namespace Graphix {

class	LowLevelContext;

}

namespace NewDisplay {

class NativeImage;

// --- Constants ---------------------------------------------------------------

// Context capabilities bits

const Int32 TargetIsTransparent	= 1 << 0;
const Int32 Target2DIsSupported	= 1 << 1;
const Int32 Target3DIsSupported	= 1 << 2;
const Int32 Is2DAccurate		= 1 << 3;


enum Filtering {
	NearestPixel	=	0,
	Bilinear		=	1,
	HighQuality		=	2,

	DefaultFilter	=	Bilinear
};

// --- Interfaces --------------------------------------------------------------

class GRAPHIX_DLL_EXPORT INativeContextImpl
{
public:
	virtual ~INativeContextImpl ();

	virtual void		Flush () = 0;
	virtual	void		InvalidateCaches () = 0;
	virtual	void		Release () = 0;
};


GRAPHIX_DLL_EXPORT	INativeContextImpl*		CreateCompoundNativeContextImpl ();
GRAPHIX_DLL_EXPORT	bool					IsCompoundImpl (INativeContextImpl*);
GRAPHIX_DLL_EXPORT	void					AddImplToCompoundNativeContextImpl (INativeContextImpl* compoundImpl, INativeContextImpl* impl);
GRAPHIX_DLL_EXPORT	INativeContextImpl*		GetImplFromCompoundNativeContextImpl (INativeContextImpl*, UInt32 implIndex);


#ifdef	WINDOWS

struct	AdditionalInfo
{
	void*		lpStencilBuffer;
	RECT		stencilDirtyRect;
	DWORD		maxStencilValue;
	UInt32		additionalMemory;

	bool		contextInitSuccess;
	bool		notEnoughMemForStencil;
};

	GS::Rect<float>		GRAPHIX_DLL_EXPORT	GetContextUpdateRect (INativeContextImpl*);
	GS::Rect<float>		GRAPHIX_DLL_EXPORT	GetContextDirtyRect (INativeContextImpl*);
	HRGN				GRAPHIX_DLL_EXPORT	GetContextDirtyRegion (INativeContextImpl*);
	AdditionalInfo		GRAPHIX_DLL_EXPORT	GetContextAdditionalInfo (INativeContextImpl*);

#endif

// --- Class declarations ------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	NativeContextBase
{
public:
	typedef GS::CountedPtr<INativeContextImpl, GS::AtomicCounter> ImplRef;

protected:
	ImplRef impl;

// Operations against nullptr
public:
	bool	operator== (std::nullptr_t) const;
	bool	operator!= (std::nullptr_t) const;
	void	operator= (std::nullptr_t);

protected:
	explicit NativeContextBase (ImplRef impl = ImplRef ());
	explicit NativeContextBase (const NativeContextBase&);

public:
	virtual ~NativeContextBase ();

	bool							IsAntialiasEnabled () const;
	void							SetAntialiasEnabled (bool enabled);

	void							Flush ();

	Int32							GetCaps () const;
	double							GetResolutionFactor () const;
	void							InvalidateCaches ();

	NativeImage						GetDashImage (const GS::Array<float>& dash, float scale = 1.0f, UInt32 maxImageWidth = 4096, UInt32 dashColorArgb = 0xFFFFFFFF, UInt32 spaceColorArgb = 0x0);
	NativeImage						GetPatternImage (Gfx::Pattern pattern, float scale = 1.0f, UInt32 foreColorArgb = 0xFFFFFFFF, UInt32 backColorArgb = 0x0);

	Graphix::LowLevelContext*		CreateLowLevelContext (bool depthStencilBufferNeeded);
};

};

#endif
