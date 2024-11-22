#ifndef DGCLIPBOARD_HPP
#define DGCLIPBOARD_HPP
#pragma once

#include "DGDLLExport.h"
#include "UniString.hpp"
#include "Singleton.hpp"
#include "Ref.hpp"


namespace GX {
	class Image;
}


namespace DG {


class ClipboardImpl;


class DG_DLL_EXPORT Clipboard : public GS::Singleton<Clipboard> {
public:
	static	UInt32		textTypeId;			// ANSI text
	static	UInt32		uniTextTypeId;		// UniCode text
	static	UInt32		rtfTypeId;			// Rich text
	static	UInt32		prtfTypeId;			// packaged Rich text document
	static	UInt32		imageTypeId;		// Bitmap image
	static	UInt32		metaFileTypeId;		// MetaFile
	static  UInt32		pdfTypeId;			// Pdf
	static	UInt32		expressionTypeID;	// Expression type

public:
	Clipboard ();
	~Clipboard ();

	void			Init ();
	bool			Clear ();
	UInt32			RegisterDataType (const GS::UniString& typeName);

	bool			HasData (UInt32 typeId) const;
	GSHandle		GetData (UInt32 typeId) const;
	bool			SetData (UInt32 typeId, const void* data, GSSize len);
	
	bool			GetUniString (UInt32 typeId, GS::UniString& data) const;
	bool			SetUniString (UInt32 typeId, const GS::UniString& data);
	
	bool			GetImage (GX::Image& image) const;
	bool			SetImage (const GX::Image& image);

private:
	GS::Ref<ClipboardImpl> clipboardImpl;
};


}


#endif