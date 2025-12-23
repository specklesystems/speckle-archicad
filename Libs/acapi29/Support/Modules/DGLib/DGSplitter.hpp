// *********************************************************************************************************************
// File:			DGSplitter.hpp
//
// Description:		Splitter Control Classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	VM
//
// SG compatible
// *********************************************************************************************************************

#ifndef DGSPLITTER_HPP
#define DGSPLITTER_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGDefs.h"
#include "DGItemEventArgs.hpp"
#include "DGEventNotifier.hpp"
#include "DGItemProperty.hpp"
#include "DGPanel.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class Splitter;
	class SplitterObserver;
}


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

// --- SplitterClickEvent ----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SplitterClickEvent: public ItemClickEvent
{
friend class SplitterObserver;			// To access protected constructor

protected:
	explicit SplitterClickEvent (const ItemClickEvent& ev);

public:
	~SplitterClickEvent ();

	Splitter*	GetSource (void) const;
};


// --- SplitterDoubleClickEvent ----------------------------------------------------------------------------------------

class DG_DLL_EXPORT SplitterDoubleClickEvent: public ItemDoubleClickEvent
{
friend class SplitterObserver;			// To access protected constructor

protected:
	explicit SplitterDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~SplitterDoubleClickEvent ();

	Splitter*	GetSource (void) const;
};


// --- SplitterDragEvent -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SplitterDragEvent: public ItemEvent
{
friend class Splitter;				// To access protected constructor
friend class SplitterObserver;

private:
	const DG::SplitterDragEventArg*	splitterMsgData;

protected:
	explicit SplitterDragEvent (Splitter* source, const DG::EventArg& msgData);

public:
	~SplitterDragEvent ();

	Splitter*	GetSource (void) const;

	short		GetPosition (void) const;
};


// --- SplitterObserver ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SplitterObserver: public ItemObserver
{
public:
	SplitterObserver ();
   ~SplitterObserver ();

	virtual	short	SpecClicked (const ItemClickEvent& ev) override;
	virtual void	SplitterClicked (const SplitterClickEvent& ev);

	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;
	virtual void	SplitterDoubleClicked (const SplitterDoubleClickEvent& ev);

	virtual void	SplitterDragStarted (const SplitterDragEvent& ev);
	virtual void	SplitterDragged (const SplitterDragEvent& ev);
	virtual void	SplitterDragExited (const SplitterDragEvent& ev);
};


// --- Splitter --------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT Splitter: public Item,
							  public SplitterNotifyHandler,
							  public ItemTrackNotifier<Splitter>
{
public:
	enum Orientation {
		Horizontal	= DG_SPLT_HORIZONTAL,
		Vertical	= DG_SPLT_VERTICAL
	};

	enum Type {
		Normal		= 0,
		Transparent	= DG_SPLT_TRANSPARENT
	};

private:
	void	ProcessSplitterDragEvent (const DG::EventArg& msgData);

	void 	InitNotifiers ();

	virtual void	NotifyDragStartEvent (const SplitterDragEventArg& eventArg) override;
	virtual void	NotifyDragEvent (const SplitterDragEventArg& eventArg) override;
	virtual void	NotifyDragExitEvent (const SplitterDragEventArg& eventArg) override;

public:
	Splitter (const Panel& panel, short item);
	Splitter (const Panel& panel, const Rect& rect, Orientation orientation, Type type = Normal);
   ~Splitter ();

	EventNotifier<Splitter, const SplitterDragEventArg> onDragStarted;
	EventNotifier<Splitter, const SplitterDragEventArg> onDragged;
	EventNotifier<Splitter, const SplitterDragEventArg> onDragExited;

	void		Attach (SplitterObserver& observer);
	void		Detach (SplitterObserver& observer);

	Orientation	GetOrientation (void) const;
	Type		GetType (void) const;

	void		EnableDrag (void);
	void		DisableDrag (void);
	void		SetDragStatus (bool isEnabled);
	bool		IsDragEnabled (void) const;

	GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
