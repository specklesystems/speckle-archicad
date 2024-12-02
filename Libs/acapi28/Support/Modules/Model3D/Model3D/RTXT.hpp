// *********************************************************************************************************************
// Description:		RTXT - Texture Attributes
//
// Module:			GSModeler
// Namespace:		
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (RTXT_HPP)
#define RTXT_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"uchar_t.hpp"
#include	"UniString.hpp"
#include	"ClassInfo.hpp"

// from GSUtils
#include	"GSUtilsDefs.h"

// from Model3D
#include	"Model3D/Model3DExport.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

struct RTXT_180;

namespace GDL
{
	class IFileRef;
	class IFileServices;
}

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


class MODEL3D_CPP_DLL_EXPORT RTXT {
	static GS::ClassInfo classInfo;

private:
	STATW					status;
	short					psize;
	float					xsize, ysize;
	Int32					pictIndex;
	GS::UniString			imageName;
	mutable Int32 volatile	initStatus;
	mutable	short			hsize, vsize;
	mutable GDL::IFileRef* 	fileRef;
	GSHandle				tpixs;

public:
	RTXT ();
	RTXT (const RTXT_180& src);
	RTXT (const RTXT& src);
	RTXT (RTXT&& src);

	RTXT& operator= (RTXT&& src);

	~RTXT ();

	bool					MissingTextureImage (GDL::IFileServices* fileServices) const;
	bool					IsValidTpixs () const;

	STATW					GetStatus () const		{ return status;	}
	short					GetPsize () const		{ return psize;		}
	float					GetXsize () const		{ return xsize;		}
	float					GetYsize () const		{ return ysize;		}
	Int32					GetPictIndex () const	{ return pictIndex;	}
	GS::UniString			GetImageName () const	{ return imageName;	}

	short					GetHsize (GDL::IFileServices* fileServices) const;
	short					GetVsize (GDL::IFileServices* fileServices) const;
	const GDL::IFileRef*	GetFileRef (GDL::IFileServices* fileServices) const;			

	void					SetStatus (STATW p)						{ status = p;	}
	void					SetPsize (short p)						{ psize = p;	}
	void					SetXsize (float p)						{ xsize = p;	}
	void					SetYsize (float p)						{ ysize = p;	}
	void					SetPictIndex (Int32 p)					{ pictIndex = p;}
	void					SetImageName (const GS::UniString& p)	{ imageName = p;}
	void					SetHsize (short p) const				{ hsize = p;	}
	void					SetVsize (short p) const				{ vsize = p;	}
	void					ResetTpixs (GSHandle p = nullptr);

	void				SetupRTXT (	float xsiz, float ysiz, Int32 hsiz, Int32 vsiz,
									const GS::UniString& imageName, short pictIndex, 
									STATW status, GSHandle tpixs);

	GSPtr			GetTpixsPtr			() const;
	GSHandle		GetTpixsCopy		() const;
	GSSize			GetTpixsSize		() const;
	void			SetTpixsSize		(UInt32 newTpixsSize);
	void			ClearTpixs			();

	void			FreeDynamicData		();

	GSErrCode		Read (GS::IChannel& ic); // binary storage with version
	GSErrCode		Write (GS::OChannel& oc) const;

	void			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	void			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

	GSErrCode		QuickRead (GS::IChannel& ic); // binary storage without version
	GSErrCode		QuickWrite (GS::OChannel& oc) const;

	void			WriteXML (GS::XMLOChannel& outXML) const;
	void			ReadXML	(GS::XMLIChannel& inXML);

private:
	void			InitLibraryConnection (GDL::IFileServices* fileServices) const;
	void			LazyInitLibraryConnection(GDL::IFileServices* fileServices) const;

	void			CopyRTXT (const RTXT& src);

	RTXT& operator= (const RTXT& source); //disabled

};

// for reading old files
struct RTXT_130 {
	STATW		status;
	short		psize;
	float		xsize, ysize;
	short		filler0;			/* for word alignment */
	short		filler1;
	Int32		filler2;
	GS::uchar_t	imageName [256];		/* MAXLONGNAME == 256 */
	short		hsize, vsize;
	UInt32		tpixs;
};			/* 2 + 2 + 2*4 + 520 + 2*2 + 4 = 540 */

struct RTXT_160 {
	STATW		status;
	short		psize;
	float		xsize, ysize;
	short		filler0;
	short		filler1;
	Int32		filler2;
	GS::uchar_t	imageName [256];
	short		hsize, vsize;
	GSHandle	tpixs;
};

struct RTXT_180 {
	static const Int32		RTXT18NameBuffSize = 256;
	STATW					status;
	short					psize;
	float					xsize, ysize;
	short					filler0;					/* for word alignment */
	short					filler1;
	Int32					pictIndex;
	GS::uchar_t				imageName [RTXT18NameBuffSize];	/* MAXLONGNAME == 256 */
	short					hsize, vsize;
	GSPtr					filler3; // fileRef
	GSHandle				tpixs;

	RTXT_180 () : status (0),
		psize (0),
		xsize (0),
		ysize (0),
		pictIndex (0),
		hsize (0),
		vsize (0),
		tpixs (0) 
	{}

};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------



#endif	// RTXT_HPP
