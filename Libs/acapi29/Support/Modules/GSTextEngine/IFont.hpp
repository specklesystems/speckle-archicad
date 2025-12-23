
// *****************************************************************************
//
//                                Interface IFont
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined IFONT_HPP
#define IFONT_HPP


// --------------------------------- Includes ----------------------------------

#include "FontFamily.hpp"

// ============================== Interface IFont ==============================

namespace TE {

class TE_DLL_EXPORT IFont {
public:
	enum FontStyle { normal = 0, bold = 1, italic = 2, underline = 4 };

	virtual ~IFont (void);

	// Font size in point (on Windows must call it with minus sign at creating the font)
	virtual	double	GetSize (void) const = 0;
	virtual	Int32	GetStyle (void) const = 0;
	virtual	FontFamily*	GetFontFamily (void) = 0;
	virtual	const FontFamily*	GetFontFamily (void) const = 0;
};

}	// namespace TE
// ______________________________ Interface IFont ______________________________

#endif
