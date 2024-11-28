// *****************************************************************************
// File:			AngleTrackerItem.hpp
//
// Description:
//
// Project:			ARCHICAD
//
// Namespace:
//
// Contact person:	NZ, DG
//
// SG compatible
// *****************************************************************************

#ifndef ANGLETRACKERITEM_HPP
#define ANGLETRACKERITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DoubleTrackerItemBase.hpp"


namespace Tracking {

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT AngleTrackerItem: public DoubleTrackerItemBase
{
public:
	virtual void			DrawTypeSpecific (NewDisplay::NativeContext& context, const DG::Rect& rect, bool selected) const override;
	virtual short			MeasureTypeSpecific () const override;
	virtual DG::RealEdit*	CreateEditControlTypeSpecific (DG::Palette& palette, const DG::Rect& itemRect) const override;
};

}	//namespace Tracker

#endif
