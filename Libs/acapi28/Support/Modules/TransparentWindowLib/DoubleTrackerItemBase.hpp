// *****************************************************************************
// File:			DoubleTrackerItemBase.hpp
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

#ifndef DOUBLETRACKERITEMBASE_HPP
#define DOUBLETRACKERITEMBASE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "TrackerItemBase.hpp"
#include "IDoubleProperty.hpp"
#include "DGEditControl.hpp"
#include "DGModule.hpp"


namespace Tracking {

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT DoubleTrackerItemBase:	public TrackerItemBase,
												public DG::RealEditObserver
{
friend class Tracker;

private:
	IDoubleProperty*		doubleProperty;
	mutable	double			propertyValue;
	double					setPropertyValue;
	DG::RealEdit*			realEdit;

private:
	void					ReleaseEditControls ();

protected:
	// Functions called from derived classes to access private data
	double					GetActualValue () const;

protected:
	// Functions called from Tracker and derived classes
	virtual void			Draw (NewDisplay::NativeContext& context, const DG::Rect& itemRect, bool selected, short itemWidth[4]) override;
	virtual void			Synchronize () const override;
	virtual DG::Item*		ActivateEditMode (DG::Palette& palette, short itemWidth[4]) override;
	virtual void			DeactivateEditMode () override;
	virtual short			GetColumnWidth (short (&itemWidth)[4]) const override;
	virtual short			GetHeight () const override;
	virtual void			FocusDefaultItem () override;

	// Template methods
	virtual void 			DrawTypeSpecific (NewDisplay::NativeContext& context, const DG::Rect& rect, bool selected) const = 0;
	virtual DG::RealEdit*	CreateEditControlTypeSpecific (DG::Palette& palette, const DG::Rect& itemRect) const = 0;
	virtual short			MeasureTypeSpecific () const = 0;

	// Event handlers
	virtual void			RealEditChanged (const DG::RealEditChangeEvent& ev) override;

public:
	DoubleTrackerItemBase ();
	virtual ~DoubleTrackerItemBase ();

	void					SetValue (double value);	// only works in edit mode

	void					SetProperty (IDoubleProperty& doubleProperty);
	IDoubleProperty*		GetProperty () const;

	virtual bool			IsInInput () const override;

	virtual DoubleTrackerItemBase* Clone () const;
};

}	//namespace Tracker

#endif
