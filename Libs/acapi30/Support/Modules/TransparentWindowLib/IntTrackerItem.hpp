// *****************************************************************************
// File:			IntTrackerItem.hpp
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

#ifndef INTTRACKERITEM_HPP
#define INTTRACKERITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "TrackerItemBase.hpp"
#include "IIntProperty.hpp"
#include "DGEditControl.hpp"
#include "DGModule.hpp"


namespace Tracking {

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT IntTrackerItem:	public TrackerItemBase,
											public DG::IntEditObserver
{
friend class Tracker;

private:
	IIntProperty*			intProperty;
	mutable	int				propertyValue;
	int						setPropertyValue;
	DG::IntEdit*			intEdit;

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
	virtual DG::IntEdit*	CreateEditControlTypeSpecific (DG::Palette& palette, const DG::Rect& itemRect) const;
	virtual short			MeasureTypeSpecific () const;

	// Event handlers
	virtual void			IntEditChanged (const DG::IntEditChangeEvent& ev) override;

public:
	IntTrackerItem ();
	virtual ~IntTrackerItem ();

	void					SetProperty (IIntProperty& intProperty);
	IIntProperty*			GetProperty () const;

	virtual bool			IsInInput () const override;
};

}	//namespace Tracker

#endif
