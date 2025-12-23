// *********************************************************************************************************************
// Description:		Abstract Media Types
//
// Module:
// Namespace:
// Contact person:
//
// *********************************************************************************************************************


#ifndef MEDIA_HPP
#define MEDIA_HPP

#pragma once

//#include "GXImageBase.h"
#include "GXMediaExport.hpp"
//#include "FileTypeManager.hpp"
#include "CountedPtr.hpp"
#include "UniString.hpp"
#include "Location.hpp"
//#include "GSPix.h"

namespace GX {

class	Sample;
class	ImageSample;
class	SubtitleSample;


// --- Base Media Class ------------------------------------------------------------------------------------------------

class IMediaImpl
{
public:
	virtual ~IMediaImpl ();
};


class GXMEDIA_DLL_EXPORT	Media
{
public:

	// ------------- Basic Media types ---------------------

	enum Type
	{
		Video	=	0
		//, Audio
	};

	// ------------- Container types -----------------------

	enum	ContainerTypeId
	{
		MP4		=	0,

#ifdef	WINDOWS
		WMV,
#endif

#ifdef	macintosh
		MOV,
#endif

		NumberOfContainerTypes,
		Unknown = NumberOfContainerTypes
	};

	struct	ContainerTypeDesc {
		GS::UniString	name;
		GS::UniString	description;
		//extension, mime type
	};

	typedef GS::CountedPtr<IMediaImpl, GS::AtomicCounter> ImplRef;

protected:
	ImplRef impl;

// Operations against nullptr
public:
	bool	operator== (std::nullptr_t) const;
	bool	operator!= (std::nullptr_t) const;
	void	operator= (std::nullptr_t);

protected:
	explicit Media (ImplRef impl = ImplRef ());
	explicit Media (const Media&);

public:
	virtual ~Media ();

	static	ContainerTypeId		MimeToContainerType (const char* mimeStr);
	static	const char*			ContainerTypeToMime (ContainerTypeId type);

	Type	GetType () const;
};


// --- WriteableMedia Class -------------------------------------------------------------------------------------------

class GXMEDIA_DLL_EXPORT	WriteableMedia: public Media
{
public:

	// ------------- Encoder types --------------------------

	enum	EncoderId
	{
		DefaultEncoder	=	0,

		H264,

#ifdef	WINDOWS
		WMV3,
#endif

		NumberOfEncoders
	};

	struct EncoderDesc {
		GS::UniString	name;
		GS::UniString	description;
	};

	/*static	UInt32				GetNumberOfAdditionalContainerTypes ();
	static	UInt32				GetAdditionalContainerTypeId (UInt32 idx);
	static	ContainerTypeDesc	GetContainerTypeDesc (UInt32 typeId);

	static	UInt32				GetNumberOfAdditionalEncoders ();
	static	UInt32				GetAdditionalencoderId (UInt32 idx);
	static	ContainerTypeDesc	GetEncoderDesc (UInt32 typeId);*/

	// ------------- Writeable Media Functionality ------------

public:
	explicit WriteableMedia (const IO::Location& fileLoc, Media::ContainerTypeId containerTypeId);
	explicit WriteableMedia (ImplRef impl = ImplRef ());
	virtual ~WriteableMedia ();

	static	UInt64	FpsToFrameDuration (UInt32 fps);

	Int32	CreateVideoStream (EncoderId encoderTypeId, UInt32 width, UInt32 height, UInt32 fps, UInt32 bitRate = 0);
	Int32	CreateSubtitleStream ();

	bool	AddMetadata (const GS::UniString& description, const GS::UniString& performer, const GS::UniString& copyRight);

	bool	BeginWriting ();
	bool	WriteSample (UInt32 streamIdx, const Sample& sample, UInt64 timeStamp);
	void	EndWriting ();
};


}

#endif
