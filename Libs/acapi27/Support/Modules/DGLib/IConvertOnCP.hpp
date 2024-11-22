
// *****************************************************************************
// Class IConvertOnCopy, IConvertOnPaste
//
// Module:			DGLib
// Namespace:		DG
// Contact person:	SA
//
// SG compatible
//
// *****************************************************************************


#if !defined ICONVERTONCP_HPP
#define ICONVERTONCP_HPP

// --------------------------------- Includes ----------------------------------
#include "DG.h"
#include "Color.hpp"

namespace TE {
	class IFont;
}

namespace GS {
	class UniString;
}

namespace DG {

// ====================== Class IConvertOnCopyPaste ============================

class DG_DLL_EXPORT IConvertOnCopyPaste {
public:
	virtual ~IConvertOnCopyPaste ();

	// output: typographic size in pixels
	virtual double			GetSizeOnCopy (double size) = 0;
	// output: color without pen index
	virtual Gfx::Color		GetPenColorOnCopy (const Gfx::Color& color) = 0;

	// output: scaled typographic size in pixels
	virtual double			GetSizeOnPaste (double size) = 0;
	// output: color with encoded pen index
	virtual Gfx::Color		GetPenColorOnPaste (const Gfx::Color& color) = 0;

	// output: font to replace a bitmap font
	virtual TE::IFont&		GetBitmapFontReplacementOnPaste (void) = 0;

	// output: new autotext entry ptr
	virtual GS::UniString*	GetGroupIDOnPaste (GS::UniString*) = 0;

	virtual bool			OnCutCopy () = 0;
	virtual bool			OnPaste () = 0;
};

// ______________________ Class IConvertOnCopyPaste ____________________________

}	// namespace DG

#endif	// ICONVERTONCP_HPP
