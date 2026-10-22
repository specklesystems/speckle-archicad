// *****************************************************************************
// File:			NativeImage.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef NATIVEIMAGE_HPP
#define NATIVEIMAGE_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"

#include "CountedPtr.hpp"
#include "Channel.hpp"
#include "RSTypes.hpp"

#ifdef WINDOWS
#include "Win32Interface.hpp"
#else
#include <ApplicationServices/ApplicationServices.h>
#endif


namespace NewDisplay {
	class NativeContext;
}


// --- Class declarations ------------------------------------------------------

class INativeImageImpl
{
public:
	virtual ~INativeImageImpl ();
};


namespace NewDisplay {

class GRAPHIX_DLL_EXPORT NativeImage
{
public:
	enum Encoding	{
		JPEG			=	0,
		PNG				=	1,

		Unknown
	};

	typedef GS::CountedPtr<INativeImageImpl, GS::AtomicCounter> ImplRef;

public:
	ImplRef impl;

public:
	NativeImage ();
	NativeImage	(UInt32 width, UInt32 height, const NativeImage& imageForColorData, double resolutionFactor = 1.0);
	NativeImage	(UInt32 width, UInt32 height, UInt32 bitDepth, const void* bits, bool perPixelAlpha = false, UInt32 bytesPerRow = 0, bool enableMemoryOptimization = true, double resolutionFactor = 1.0);

#ifdef macintosh
	explicit NativeImage (CGImageRef image, bool perPixelAlpha = false);
#else
	explicit NativeImage (HBITMAP bitmap, double resolutionFactor = 1.0);
	explicit NativeImage (HICON hIcon, double resolutionFactor);
	explicit NativeImage (HENHMETAFILE metaFile, UInt32 width, UInt32 height);
#endif

	explicit NativeImage (GSResModule module, GSResID resID, Encoding format);
	explicit NativeImage (const char* data, UInt32 size, Encoding format);
	explicit NativeImage (const std::byte* data, UInt32 size, Encoding format);

	virtual ~NativeImage ();

	// Operations against nullptr
	bool			operator== (std::nullptr_t) const;
	bool			operator!= (std::nullptr_t) const;
	void			operator=  (std::nullptr_t);

	// Attribute access
	UInt32			GetWidth () const;
	UInt32			GetHeight () const;
	double			GetResolutionFactor () const;

	bool			IsPerPixelAlpha () const;

	void			GetColorKey (unsigned char& red, unsigned char& green, unsigned char& blue) const;
	void			SetColorKey (unsigned char red, unsigned char green, unsigned char blue);

	// Context handling
	NativeContext	GetContext ();
	void			ReleaseContext (NativeContext&);

	// Serialization
	bool			Encode (GS::OChannel& outputChannel, Encoding format) const;

#ifdef WINDOWS
	void*			GetBitPtr ();
	void			ReleaseBitPtr (void* ptr);
#endif

	// Deep copy
	NativeImage		CreateCopy () const;

	NativeImage		Resize (UInt32 maxWidth, UInt32 maxHeight) const;
};

}

#endif
