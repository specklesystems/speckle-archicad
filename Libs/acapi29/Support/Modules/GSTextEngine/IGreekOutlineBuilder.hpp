// *****************************************************************************
//
//                                Class IGreekOutlineBuilder
//
// Module:			TextEngine
// Namespace:		TE
// Platform:		common
// Contact person:	KM FG
//
// SG compatible
//
// *****************************************************************************

// --------------------------------- Defines -----------------------------------

#if !defined IGREEKOUTLINEBUILDER_HPP
#define IGREEKOUTLINEBUILDER_HPP

// --------------------------------- Includes ----------------------------------

#include "ICharStyle.hpp"

// =========================== Class IGreekOutlineBuilder ======================

namespace TE {

class TE_DLL_EXPORT IGreekOutlineBuilder
{

public:
	virtual ~IGreekOutlineBuilder ();

	// methods
	virtual Int32	BeginGreekOutline () = 0;
	virtual Int32	LineColor (const Gfx::Color& color) = 0;
	virtual Int32	LineRect (double x, double y, double w, double h, double angle) = 0;
	virtual Int32	EndGreekOutline () = 0;


};	// class IGreekOutlineBuilder

}	// namespace TE

#endif	// #if !defined IGREEKOUTLINEBUILDER_HPP
