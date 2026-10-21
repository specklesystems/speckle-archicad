// *****************************************************************************
//
//                                Class IPlainTextBuilder
//
// Module:			TextEngine
// Namespace:		TE
// Platform:		common
// Contact person:	KM FG
//
// SG compatible
//
// *****************************************************************************

// --- Defines -----------------------------------------------------------------

#if !defined IPLAINTEXTBUILDER_HPP
#define IPLAINTEXTBUILDER_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "TEBase.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace GS {
	class UniString;
}

namespace TE {
	class ICharStyle;
}

// === Class IPlainTextBuilder ===================================================

namespace TE {

class TE_DLL_EXPORT IPlainTextBuilder
{

public:
	virtual  ~IPlainTextBuilder ();
	// types

	// methods
	virtual Int32	BeginText (double angle) = 0;
//	virtual long	BeginParagraph (void) = 0;
//	virtual long	BeginLine (void) = 0;
	virtual Int32	BeginRun (const ICharStyle* iCharStyle) = 0;
	virtual Int32	OneRun (const GS::UniString& uString, double baseLineX, double baseLineY, double runWidth) = 0;
//	virtual long	EndRun (void) = 0;
//	virtual long	EndLine (void) = 0;
//	virtual long	EndParagraph (void) = 0;
	virtual Int32	EndText (void);

};	// class IPlainTextBuilder

}	// namespace TE

#endif	// #if !defined IPLAINTEXTBUILDER_HPP
