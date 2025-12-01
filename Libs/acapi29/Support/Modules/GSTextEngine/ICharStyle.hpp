
// *****************************************************************************
//
//                                Interface ICharStyle
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined ICHARSTYLE_HPP
#define ICHARSTYLE_HPP


// --------------------------------- Includes ----------------------------------

#include "Color.hpp"
#include "IFont.hpp"

// ============================== Interface ICharStyle ==============================

namespace TE {


class TE_DLL_EXPORT ICharStyle {
public:
	enum StyleEffect {strikeout =  0x100, superscript = 0x200, subscript = 0x400, fractional = 0x1000, protect = 0x2000};

	virtual ~ICharStyle (void);

	virtual	Int32				GetEffects (void) const = 0;
	virtual	Gfx::Color*			GetColor (void) = 0;
	virtual	const Gfx::Color*	GetColor (void) const = 0;
	virtual	IFont*				GetFont (void) = 0;
	virtual	const IFont*		GetFont (void) const = 0;
	virtual	void*				GetUserData (void) const = 0;
};

}	// namespace TE
// ______________________________ Interface ICharStyle ______________________________

#endif
