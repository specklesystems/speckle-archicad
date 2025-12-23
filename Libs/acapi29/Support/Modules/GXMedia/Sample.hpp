// *********************************************************************************************************************
// Description:		Abstract Media Types
//
// Module:
// Namespace:
// Contact person:
//
// *********************************************************************************************************************


#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#pragma once

#include "GXMediaExport.hpp"
#include "GSPix.h"
#include "UniString.hpp"
//#include "GXImageBase.h"

//#include "Ref.hpp"
//#include "GSPix.h"

namespace GX {
	
//typedef GS::Ref<Media> MediaRef;


// --- Includes	--------------------------------------------------------------------------------------------------------

class GXMEDIA_DLL_EXPORT	Sample
{
protected:
	UInt64		duration;

public:
	Sample (UInt64 duration);
	virtual ~Sample ();

	virtual		UInt64	GetDuration () const;
};


class GXMEDIA_DLL_EXPORT	ImageSample: public Sample
{
protected:
	GSPixMapHandle	picHandle;

public:
	ImageSample ();
	explicit ImageSample (const GSPixMapHandle picHandle, UInt64 duration);
	/*explicit ImageSample (const NewDisplay::NativeImage& nativeImage);
	explicit ImageSample (GSHandle sourceImage, const FTM::TypeID& fileFormat);
	explicit ImageSample (IO::Location fileLoc);*/
	virtual ~ImageSample ();

	GSPixMapHandle		GetPixMap () const;
};


class GXMEDIA_DLL_EXPORT	SubtitleSample: public Sample
{
protected:
	GS::UniString	subtitle;

public:
	SubtitleSample (const GS::UniString& subtitle, UInt64 duration);
	virtual ~SubtitleSample ();

	GS::UniString		GetText () const;
};

}

#endif
