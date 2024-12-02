// *********************************************************************************************************************
// File:			UDRollDwonInterfaces.hpp
//
// Description:		Interface classes of rolldown dialogs
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	BM
//
// SG compatible
// *********************************************************************************************************************

#ifndef	UDROLLDOWNINTERFACES_HPP
#define	UDROLLDOWNINTERFACES_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "RandomIterator.hpp"
#include "UDDefinitions.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace GS {
	class UniString;
}

namespace DG {
	class Icon;
	class SimpleTab;
	class Rect;
}

namespace UD {
	class RollPanelObserver;
}

namespace UD {

// === IPanel interface ================================================================================================

class UD_DLL_EXPORT IPanel
{
public:
	virtual							~IPanel ();

	virtual bool					IsValid (void) const = 0;

	virtual const DG::SimpleTab&	GetTabControl (void) const = 0;

	virtual void					Initialize (void) = 0;
};


// === IRollPanel interface ============================================================================================

class UD_DLL_EXPORT IRollPanel: public IPanel
{
public:
	enum GrowType {
		NoGrow	= 0,
		HGrow	= 1,
		VGrow	= 2,
		HVGrow	= 3
	};

	virtual void					SetIcon (const DG::Icon& icon) = 0;
	virtual DG::Icon				GetIcon (void) const = 0;

	virtual void					SetTitle (const GS::UniString& title) = 0;
	virtual GS::UniString			GetTitle (void) const = 0;

	virtual bool					Expand (bool expandEnabledIfSurfaceNotInitialized = true) = 0;
	virtual bool					Collapse (bool collapseEnabledIfSurfaceNotInitialized = true) = 0;
	virtual void					SetState (bool state) = 0;
	virtual bool					IsExpanded (void) const = 0;
	virtual bool					IsAnimated (void) const = 0;
	virtual bool					IsExpanding (void) const = 0;
	virtual bool					IsCollapsing (void) const = 0;

	virtual void					Redraw (void) const = 0;

	virtual void					Enable (void) = 0;
	virtual void					Disable (void) = 0;

	virtual void					SetStatus (bool status) = 0;
	virtual bool					IsEnabled (void) const = 0;

	virtual void					Show (bool fullyVisibleRequiredForDoNothing = false) = 0;
	virtual void					Hide (void) = 0;
	virtual void					SetVisibility (bool visibility) = 0;
	virtual bool					IsVisible (void) const = 0;

	virtual void					Activate (void) = 0;
	virtual void					Deactivate (void) = 0;
	virtual bool					IsActive (void) const = 0;

	virtual void					SetGrowType (GrowType growType) = 0;
	virtual GrowType				GetGrowType (void) const = 0;

	virtual void					SetRollControlSize (short size) = 0;
	virtual short					GetRollControlSize (void) const = 0;

	virtual void					SetUserMinHeight (short minHeight) = 0; // for panels that want to resize themself

	virtual void					SetMaxHeight (short maxHeight) = 0;
	virtual short					GetMaxHeight (void) const = 0;

 	virtual void					RegisterObserver (RollPanelObserver& observer) = 0;
	virtual void					UnregisterObserver (RollPanelObserver& observer) = 0;

	virtual void					EnableCollapse ()  = 0;
	virtual void					DisableCollapse () = 0;

   virtual ~IRollPanel ();
};


// === IRollDownPanel interface ========================================================================================

class UD_DLL_EXPORT IRollDownPanel : public IRollPanel
{
public:
	virtual void					SetGapBelowPanel (short gap) = 0;
	virtual short					GetGapBelowPanel (void) const = 0;

	virtual ~IRollDownPanel ();
};


// === IMiddlePanel interface ==========================================================================================

class UD_DLL_EXPORT IMiddlePanel: public IPanel
{
public:
	enum GrowType {
		NoGrow	= 0,
		HGrow	= 1
	};

	virtual void					SetGrowType (GrowType growType) = 0;
	virtual GrowType				GetGrowType (void) const = 0;

	virtual void					SetSplitterSize (short size) = 0;
	virtual short					GetSplitterSize (void) const = 0;
	virtual void					SetSplitterStatus (void) = 0; // efary 2007.12.03 TT 69185:

    virtual ~IMiddlePanel ();
};


// === IPanelLayout interface ==========================================================================================

class UD_DLL_EXPORT IPanelLayout
{
public:
	virtual							~IPanelLayout ();

	virtual void					SetRect (const DG::Rect& rect) = 0;
	virtual DG::Rect				GetRect (void) const = 0;

	virtual short					GetWidth (void) const = 0;
	virtual short					GetMinWidth (void) const = 0;

	virtual short					GetHeight (void) const = 0;
	virtual short					GetMinHeight (void) const = 0;
};


// === IRollPanelLayout interface ======================================================================================

class UD_DLL_EXPORT IRollPanelLayout: public IPanelLayout
{
public:
	virtual short					GetExpandedHeight (void) const = 0;
	virtual short					GetExpandedMinHeight (void) const = 0;

	virtual short					GetCollapsedHeight (void) const = 0;

    virtual ~IRollPanelLayout ();
};


// === IRollDownPanelSet interface =====================================================================================

class UD_DLL_EXPORT IRollDownPanelSet
{
public:
	typedef GS::ConstRandomIterator<IRollDownPanel*>	ConstIterator;

	virtual						   ~IRollDownPanelSet ();

	virtual IRollDownPanel*			CreateRollDownPanel (const IRollDownPanel* panel = nullptr) = 0;
	virtual void					RemoveRollDownPanel (IRollDownPanel* panel) = 0;
	virtual ConstIterator			EnumerateRollDownPanels (void) const = 0;
};


// === IRollDownSurface interface ======================================================================================

class UD_DLL_EXPORT IRollDownSurface
{
public:
	enum LayoutMethod {
		FixSizeLayout	= 0,
		SizeableLayout	= 1
	};

	typedef GS::ConstForwardIterator<IRollDownPanelSet*>	ConstIterator;

	virtual						   ~IRollDownSurface ();

	virtual IRollDownPanelSet*		CreateRollDownPanelSet (void) = 0;
	virtual void					RemoveRollDownPanelSet (IRollDownPanelSet* panelSet) = 0;
	virtual ConstIterator			EnumerateRollDownPanelSets (void) const = 0;
	virtual IRollDownPanelSet*		GetRollDownPanelSet (short index) const = 0;

	virtual void					SetActiveRollDownPanelSet (const IRollDownPanelSet* panelSet) = 0;
	virtual IRollDownPanelSet*		GetActiveRollDownPanelSet (void) const = 0;

	virtual IRollPanel*				CreateRollLeftPanel (void) = 0;
	virtual void					RemoveRollLeftPanel (void) = 0;
	virtual IRollPanel*				GetRollLeftPanel (void) const = 0;

	virtual IPanel*					CreateHeaderPanel (void) = 0;
	virtual void					RemoveHeaderPanel (void) = 0;
	virtual IPanel*					GetHeaderPanel (void) const = 0;

	virtual IMiddlePanel*			CreateMiddlePanel (void) = 0;
	virtual void					RemoveMiddlePanel (void) = 0;
	virtual IMiddlePanel*			GetMiddlePanel (void) const = 0;

	virtual IPanel*					CreateBottomPanel (void) = 0;
	virtual void					RemoveBottomPanel (void) = 0;
	virtual IPanel*					GetBottomPanel (void) const = 0;

	virtual LayoutMethod			GetLayoutMethod (void) const = 0;
	virtual void					SetLayoutMethod (LayoutMethod layoutMethod) = 0;

	virtual void					BeginPanelLayout (void) = 0;
	virtual void					EndPanelLayout (void) = 0;
};

}	// namespace UD

#endif
