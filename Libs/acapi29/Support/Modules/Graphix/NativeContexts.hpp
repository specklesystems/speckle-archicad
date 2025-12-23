// *****************************************************************************
// File:			NativeContexts.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef NATIVECONTEXTS_HPP
#define NATIVECONTEXTS_HPP

// --- Includes ----------------------------------------------------------------

#include "NativeContext.hpp"

namespace DG {
	class UserItemUpdateEvent;
	class ListBoxTabItemUpdateEvent;
	class ListViewUpdateEvent;
}

namespace NewDisplay {

#ifdef WINDOWS

class GRAPHIX_DLL_EXPORT HDCContext: public NativeContext
{
public:
	HDCContext (void* hdc, double resolutionFactor);
};

class GRAPHIX_DLL_EXPORT GdiplusGraphicsContext: public NativeContext
{
public:
	GdiplusGraphicsContext (void* graphics, double resolutionFactor);
};

#endif

#ifdef macintosh

class GRAPHIX_DLL_EXPORT CGContextContext: public NativeContext
{
public:
	CGContextContext (void* cgContext);

    virtual ~CGContextContext ();
	CGContextContext (void* cgContext, double resolutionFactor);
};

#endif

}

#endif
