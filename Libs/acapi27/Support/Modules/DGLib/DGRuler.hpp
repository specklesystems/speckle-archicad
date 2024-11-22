// *****************************************************************************
// File:			DGRuler.hpp
//
// Description:		Ruler classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BL, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGRULER_HPP
#define DGRULER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGItemEventArgs.hpp"
#include "DGEventNotifier.hpp"
#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Ruler;
	class EventDispatcher;
}

namespace GS {
	template<class T>
	class Array;
}

namespace TE {
	class Tab;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- RulerChangeEvent --------------------------------------------------------

class DG_DLL_EXPORT RulerChangeEvent: public ItemChangeEvent
{
friend class RulerObserver;					// To access protected constructor

private:
	const DG::RulerChangeEventArg*	changeData;

protected:
	explicit RulerChangeEvent (const ItemChangeEvent& ev);

public:
	enum PartType {
		FirstLineIndent		= DG_RUPT_FIRSTLINEINDENT,
		LeftIndent			= DG_RUPT_LEFTINDENT,
		RightIndent			= DG_RUPT_RIGHTINDENT,
		Tab					= DG_RUPT_TAB
	};

	~RulerChangeEvent ();

	Ruler*		GetSource (void) const;

	PartType	GetChangedPartType (void) const;

	double		GetNewIndentPosition (void) const;

	short		GetTabulatorCount (void) const;

	short		GetTabulators (GS::Array<TE::Tab>* tabulators) const;
};


// --- RulerDoubleClickEvent --------------------------------------------------------

class DG_DLL_EXPORT RulerDoubleClickEvent: public ItemDoubleClickEvent
{
friend class RulerObserver;					// To access protected constructor

private:
	const DG::RulerClickEventArg*	clickData;

protected:
	explicit RulerDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	enum PartType {
		FirstLineIndent		= DG_RUPT_FIRSTLINEINDENT,
		LeftIndent			= DG_RUPT_LEFTINDENT,
		RightIndent			= DG_RUPT_RIGHTINDENT,
		Tab					= DG_RUPT_TAB,
		NonSpecificPart		= DG_RUPT_NONSPECIFICPART
	};

	~RulerDoubleClickEvent ();

	Ruler*		GetSource (void) const;

	PartType	GetDoubleClickedPartType (void) const;

	double		GetPosition (void) const;

	short		GetTabulatorIndex (void) const;

};


// --- RulerObserver -----------------------------------------------------------

class DG_DLL_EXPORT RulerObserver: public ItemObserver
{
friend class EventDispatcher;

protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;

	virtual void	RulerChanged (const RulerChangeEvent& ev);
	virtual void	RulerDoubleClicked (const RulerDoubleClickEvent& ev);
	virtual bool	RulerDragStarted (const Ruler* source);

public:
	RulerObserver ();
   ~RulerObserver ();
};


// --- Ruler -------------------------------------------------------------------
// using logical units

class DG_DLL_EXPORT Ruler: public Item,
						   public RulerNotifyHandler
{
public:
	enum RulerType {
		Editor	= DG_RT_EDITOR,
		Window	= DG_RT_2DWINDOW,
		Table	= DG_RT_TABLE
	};

	enum DirectionType {
		Horizontal	= 0,
		Vertical	= DG_RT_VERTICAL
	};

private:
	void 	InitNotifiers ();

	virtual short	NotifyDoubleClickEvent (const RulerClickEventArg& eventArg) override;
	virtual short	NotifyChangeEvent (const RulerChangeEventArg& eventArg) override;

public:
	Ruler (const Panel& panel, short item);
	Ruler (const Panel& panel, const Rect& rect, short richEditTextInd, RulerType rulerType = Editor, DirectionType dirType = Horizontal);
   ~Ruler ();

	EventNotifier<Ruler, const RulerClickEventArg, short> onDoubleClicked;
	EventNotifier<Ruler, const RulerChangeEventArg, short> onChanged;

	void			Attach (RulerObserver& observer);
	void			Detach (RulerObserver& observer);

	void			SetUnitType (DG::Unit::Type unitType);
	DG::Unit::Type	GetUnitType (void) const;
	void			SetTenUnitInPixels (double tenUnitInPixels);
	double			GetTenUnitInPixels (void) const;

	void			SetSnapDistanceSI (double snapDistanceSI);
	double			GetSnapDistanceSI (void) const;
	void			SetSnapDistanceUS (double snapDistanceUS);
	double			GetSnapDistanceUS (void) const;
	void			SetDefaultTabDistance (double defTabDistance);
	double			GetDefaultTabDistance (void) const;

	void			SetFirstLineIndent (double firstLineIndent);
	double			GetFirstLineIndent (void) const;
	void			SetLeftIndent (double leftIndent);
	double			GetLeftIndent (void) const;
	void			SetRightIndent (double rightIndent);
	double			GetRightIndent (void) const;
	void			SetRightIndentDisabled ();
	void			SetRightIndentEnabled ();
	bool			IsRightIndentDisabled (void) const;

	void			SetTextBoxWidth (double textBoxWidth);
	double			GetTextBoxWidth (void) const;
	void			SetScrollPosition (double scrollPosition);
	double			GetScrollPosition (void) const;

	short			GetTabulatorCount (void) const;
	short			GetTabulators (GS::Array<TE::Tab>* tabulators) const;
	void			SetTabulators (const GS::Array<TE::Tab>& tabulators);

	void			DisableDraw (void) const;
	void			EnableDraw (void) const;
	void			SetRTLLayout (bool flag);

	void			DrawHairline (Int32 pos);

	GSErrCode		Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
