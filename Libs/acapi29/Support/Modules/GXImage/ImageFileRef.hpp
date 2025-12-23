// *********************************************************************************************************************
// Description:		Temporary image file
//
// Module:
// Namespace:
// Contact person:	BAt
//
// *********************************************************************************************************************


#ifndef IMAGEFILEREF_HPP
#define IMAGEFILEREF_HPP

#pragma once

#include "GXImageExport.hpp"
#include "Location.hpp"
#include "GXImageSaveOptions.hpp"
#include "FileTypeManager.hpp"

namespace GX {


// --- Includes	--------------------------------------------------------------------------------------------------------

class GXIMAGE_DLL_EXPORT ImageFileRef
{
private:
	IO::Location loc;
	ImageSaveOptions options;
	FTM::TypeID type;

public:
	ImageFileRef (const IO::Location& location, FTM::TypeID type, ImageSaveOptions options);
	~ImageFileRef ();
	
	IO::Location GetLocation (void) { return loc; }
	ImageSaveOptions GetOptions (void) {return options; }
	GS::UniString GetFormatMime (void) const;
};

}

#endif
