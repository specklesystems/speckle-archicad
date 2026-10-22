// *****************************************************************************
// File:			StringTrackerItem.hpp
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

#ifndef STRINGTRACKERITEM_HPP
#define STRINGTRACKERITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "TrackerItemBase.hpp"
#include "IStringProperty.hpp"
#include "DGEditControl.hpp"
#include "DGModule.hpp"


namespace Tracking {

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT StringTrackerItem:	public TrackerItemBase,
											public DG::TextEditBaseObserver
{
friend class Tracker;

private:
	IStringProperty*		stringProperty;
	GS::UniString			setPropertyValue;
	DG::TextEdit*			stringEdit;

protected:
	mutable	GS::UniString	propertyValue;
	short					m_IconLeftGap;

private:
	void					ReleaseEditControls ();

protected:
	// Functions called from Tracker and derived classes
	virtual void			Draw (NewDisplay::NativeContext& context, const DG::Rect& itemRect, bool selected, short itemWidth[4]) override;
	virtual void			Synchronize () const override;
	virtual DG::Item*		ActivateEditMode (DG::Palette& palette, short itemWidth[4]) override;
	virtual void			DeactivateEditMode () override;
	virtual short			GetColumnWidth (short (&itemWidth)[4]) const override;
	virtual short			GetHeight () const override;
	virtual void			FocusDefaultItem () override;

	// Overridable methods
	virtual void 			DrawTypeSpecific (NewDisplay::NativeContext& context, const DG::Rect& rect, bool selected) const;
	virtual DG::TextEdit*	CreateEditControlTypeSpecific (DG::Palette& palette, const DG::Rect& itemRect) const;
	virtual short			MeasureTypeSpecific () const;

	// Event handlers
	virtual void			TextEditChanged (const DG::TextEditChangeEvent& ev) override;

public:
	explicit StringTrackerItem (short _iconLeftGap = IconLeftGap);
	virtual ~StringTrackerItem ();

	void					SetProperty (IStringProperty& stringProperty);
	IStringProperty*		GetProperty () const;

	virtual bool			IsInInput () const override;
};

}	//namespace Tracker

#endif
