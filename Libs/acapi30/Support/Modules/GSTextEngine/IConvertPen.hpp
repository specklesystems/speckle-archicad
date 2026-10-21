
// *****************************************************************************
//
//                                Class IConvertPen
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined VBUTILICONVERTPEN_HPP
#define VBUTILICONVERTPEN_HPP

// --------------------------------- Includes ----------------------------------
#include "TEBase.hpp"
#include "Color.hpp"

// ============================== Class IConvertPen ==============================

namespace VBUtil {


class TE_DLL_EXPORT IConvertPen {
public:
	virtual bool	GetPenColor (Int32	penID, Gfx::Color* color) = 0;

    virtual ~IConvertPen ();
};


}	// namespace VBUtil
// ______________________________ Class IConvertPen ______________________________

#endif
