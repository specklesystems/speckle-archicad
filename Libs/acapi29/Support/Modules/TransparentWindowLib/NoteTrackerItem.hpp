// *****************************************************************************
// File:			NoteTrackerItem.hpp
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

#ifndef NOTETRACKERITEM_HPP
#define NOTETRACKERITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "TrackerItemBase.hpp"


namespace Tracking {

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT NoteTrackerItem:	public TrackerItemBase
{
friend class Tracker;

private:
	GS::UniString				note;

protected:
	// Functions called from Tracker and derived classes
	virtual void			Draw (NewDisplay::NativeContext& context, const DG::Rect& itemRect, bool selected, short itemWidth[4]) override;
	virtual void			Synchronize () const override;
	virtual DG::Item*		ActivateEditMode (DG::Palette& palette, short itemWidth[4]) override;
	virtual void			DeactivateEditMode () override;
	virtual short			GetColumnWidth (short (&itemWidth)[4]) const override;
	virtual short			GetHeight () const override;
	virtual bool			IsEnabled (void) const override;
	virtual void			FocusDefaultItem () override;
	virtual bool			IsInInput () const override;

public:
	NoteTrackerItem ();
	virtual ~NoteTrackerItem ();

	void	SetNote (const GS::UniString& note);
};

}	//namespace Tracker

#endif
