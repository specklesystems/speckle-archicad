// *****************************************************************************
// File:			DGUserControl.hpp
//
// Description:		UserControl classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGUSERCONTROL_HPP
#define DGUSERCONTROL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGItem.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class UserControl;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- UserControlChangeEvent --------------------------------------------------

class DG_DLL_EXPORT UserControlChangeEvent: public ItemChangeEvent
{
friend class UserControlObserver;			// To access protected constructor

private:
	Int32	previousValue;

protected:
	explicit UserControlChangeEvent (const ItemChangeEvent& ev);

public:
	~UserControlChangeEvent ();

	UserControl*	GetSource (void) const;

	Int32			GetPreviousValue (void) const;
};


// --- UserControlDoubleClickEvent ---------------------------------------------

class DG_DLL_EXPORT UserControlDoubleClickEvent: public ItemDoubleClickEvent
{
friend class UserControlObserver;			// To access protected constructor

protected:
	explicit UserControlDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~UserControlDoubleClickEvent ();

	UserControl*	GetSource (void) const;
};


// --- UserControlTrackEvent ---------------------------------------------------

class DG_DLL_EXPORT UserControlTrackEvent: public ItemTrackEvent
{
friend class UserControlObserver;			// To access protected constructor

protected:
	explicit UserControlTrackEvent (const ItemTrackEvent& ev);

public:
	~UserControlTrackEvent ();

	UserControl*	GetSource (void) const;
};


// --- UserControlObserver -----------------------------------------------------

class DG_DLL_EXPORT UserControlObserver: public ItemObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;
	virtual	short	SpecTrackEntered (const ItemTrackEvent& ev) override;
	virtual	short	SpecTracked (const ItemTrackEvent& ev) override;
	virtual	short	SpecTrackExited (const ItemTrackEvent& ev) override;

	virtual void	UserControlChanged (const UserControlChangeEvent& ev);
	virtual void	UserControlDoubleClicked (const UserControlDoubleClickEvent& ev);
	virtual void	UserControlTrackEntered (const UserControlTrackEvent& ev);
	virtual void	UserControlTracked (const UserControlTrackEvent& ev);
	virtual void	UserControlTrackExited (const UserControlTrackEvent& ev);

public:
	UserControlObserver ();
   ~UserControlObserver ();
};


// --- UserControl -------------------------------------------------------------

class DG_DLL_EXPORT UserControl: public Item,
								 public ItemTrackNotifier<UserControl>
{
public:
	enum ButtonForm {
		BevelEdge			= DG_BA_BEVEL,
		RoundedBevelEdge	= DG_BA_ROUNDEDBEVEL
	};

	enum FrameType {
		NoFrame = DG_BF_NOFRAME,
		Frame	= DG_BF_FRAME
	};

	UserControl (const Panel& panel, short item);
	UserControl (const Panel& panel, const Rect& rect, short procId, ButtonForm form = BevelEdge);
	~UserControl ();

protected:
	UserControl (const Panel& panel, const Rect& rect, short procId, FrameType frameType, ButtonForm form = BevelEdge);

public:
	void	Attach (UserControlObserver& observer);
	void	Detach (UserControlObserver& observer);

	void	SetMin (Int32 min);
	void	SetMax (Int32 max);
	void	SetValue (Int32 value);

	Int32	GetMin (void) const;
	Int32	GetMax (void) const;
	Int32	GetValue (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
