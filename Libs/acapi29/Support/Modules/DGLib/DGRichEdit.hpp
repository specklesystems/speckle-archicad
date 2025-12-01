// *****************************************************************************
// File:			DGRichEdit.hpp
//
// Description:		RichEdit classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGRICHEDIT_HPP
#define DGRICHEDIT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGUtility.hpp"
#include "DGItemProperty.hpp"

#include "Color.hpp"

#include "DGItemEventArgs.hpp"
#include "DGEventNotifier.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class RichEdit;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- RichEditDragSourceEvent -------------------------------------------------

class DG_DLL_EXPORT RichEditDragSourceEvent: public ItemDragSourceEvent
{
friend class RichEditDragSourceObserver;	// To access protected constructor
friend class RichEditObserver;				// To access protected constructor

protected:
	explicit RichEditDragSourceEvent (const ItemDragSourceEvent& ev);
			~RichEditDragSourceEvent ();

public:
	RichEdit*	GetSource (void) const;
};


// --- RichEditDragSourceObserver ----------------------------------------------

class DG_DLL_EXPORT RichEditDragSourceObserver
{
protected:
			 RichEditDragSourceObserver ();
	virtual ~RichEditDragSourceObserver ();

public:
	virtual void	RichEditDragStarting (const RichEditDragSourceEvent& ev, bool* canStart);
	virtual void	RichEditDragStarted (const RichEditDragSourceEvent& ev, UShort* effect);
	virtual void	RichEditDragStarted (const RichEditDragSourceEvent& ev, UShort* effect, bool* rightDragMenu);
	virtual void	RichEditDragEnded (const RichEditDragSourceEvent& ev, DragDrop::Effect effect);
	virtual void	RichEditDragSetDelayedData (const RichEditDragSourceEvent& ev);
};


// --- RichEditDropTargetEvent -------------------------------------------------

class DG_DLL_EXPORT RichEditDropTargetEvent: public ItemDropTargetEvent
{
friend class RichEditObserver;				// To access protected constructor

private:
	ULong	caretPosition;

protected:
	explicit RichEditDropTargetEvent (const ItemDropTargetEvent& ev);
			~RichEditDropTargetEvent ();

public:
	RichEdit*	GetSource (void) const;

	ULong		GetCaretPosition (void) const;
};


// --- RichEditDropTargetObserver ----------------------------------------------

class DG_DLL_EXPORT RichEditDropTargetObserver
{
protected:
			 RichEditDropTargetObserver ();
	virtual ~RichEditDropTargetObserver ();

public:
	virtual void	RichEditDragEntered (const RichEditDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour);
	virtual void	RichEditDragEntered (const RichEditDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour,
										 bool* rightDragMenu);
	virtual void	RichEditDragMoved (const RichEditDropTargetEvent& ev, DragDrop::Effect* effect, DragDrop::Feedback* denyFeedback);
	virtual void	RichEditDragLeft (const RichEditDropTargetEvent& ev, DragDrop::Effect* effect);
	virtual void	RichEditDropped (const RichEditDropTargetEvent& ev, DragDrop::Effect* effect);
};


// --- RichEditContentEvent ----------------------------------------------------

class DG_DLL_EXPORT RichEditContentEvent: public ItemChangeEvent
{
friend class RichEditObserver;				// To access protected constructor

private:
	const DG::RichEditChangeEventArg*	changeData;

protected:
	explicit RichEditContentEvent (const ItemChangeEvent& ev);

public:
	~RichEditContentEvent ();

	RichEdit*	GetSource (void) const;

	CharRange	GetOldContentRange (void) const;
	CharRange	GetNewContentRange (void) const;
};


// --- RichEditSelectionEvent --------------------------------------------------

class DG_DLL_EXPORT RichEditSelectionEvent: public ItemChangeEvent
{
friend class RichEditObserver;				// To access protected constructor

private:
	const DG::RichEditChangeEventArg*	changeData;

protected:
	explicit RichEditSelectionEvent (const ItemChangeEvent& ev);

public:
	~RichEditSelectionEvent ();

	RichEdit*	GetSource (void) const;

	CharRange	GetOldSelection (void) const;
	CharRange	GetNewSelection (void) const;
};


// --- RichEditObserver --------------------------------------------------------

class DG_DLL_EXPORT RichEditObserver: public ItemObserver,
									  public RichEditDragSourceObserver,
									  public RichEditDropTargetObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual short	SpecDragStarting (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragStarted (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEnded (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragSetDelayedData (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEntered (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragMoved (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragLeft (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDropped (const ItemDropTargetEvent& ev) override;

	virtual void	RichEditContentChanged (const RichEditContentEvent& ev);
	virtual void	RichEditSelectionChanged (const RichEditSelectionEvent& ev);

public:
	RichEditObserver ();
   ~RichEditObserver ();
};


// --- RichEdit ----------------------------------------------------------------

class DG_DLL_EXPORT RichEdit: public Item,
							  public FocusableProperty,
							  public RichEditNotifyHandler,
							  public ItemDragDropNotifier<RichEdit>,
							  public ItemWheelNotifier<RichEdit>,
							  public ItemFocusNotifier<RichEdit>,
							  public FilterCharNotifier<RichEdit>
{
public:
	enum ScrollType {
		NoScroll	= DG_ET_NOSCROLL,
		HScroll		= DG_ET_HSCROLL,
		VScroll		= DG_ET_VSCROLL,
		HVScroll	= DG_ET_HSCROLL | DG_ET_VSCROLL
	};

	enum ReadOnlyType {
		Editable	= DG_ET_EDITABLE,
		ReadOnly	= DG_ET_READONLY
	};

	enum FrameType {
		Frame		= DG_ET_FRAME,
		NoFrame		= DG_ET_NOFRAME
	};

	enum EOLType {
		Default		= DG_EOL_DEFAULT,
		CR			= DG_EOL_CR,
		CRLF		= DG_EOL_CRLF
	};

	enum CharPos {
		TextBegin	= DG_REP_TEXTBEGIN,
		TextEnd		= DG_REP_TEXTEND
	};

private:
	void	InitNotifiers ();

	virtual void	NotifyChangeEvent (const RichEditChangeEventArg& eventArg);

public:
	RichEdit (const Panel& panel, short item);
	RichEdit (const Panel& panel, const Rect& rect, ScrollType scroll = NoScroll,
			  ReadOnlyType readOnly = Editable, FrameType frame = Frame);
   ~RichEdit ();

	EventNotifier<RichEdit, const RichEditChangeEventArg> onContentChanged;
	EventNotifier<RichEdit, const RichEditChangeEventArg> onSelectionChanged;

	void	Attach (RichEditObserver& observer);
	void	Detach (RichEditObserver& observer);

	void	CatText (const GS::UniString& text);
	void	SetText (const GS::UniString& text);
	void	SetTextRange (const CharRange& charRange, const GS::UniString& text);

	GS::UniString	GetText (EOLType eolType = Default) const;
	GS::UniString	GetTextRange (const CharRange& charRange, EOLType eolType = Default) const;

	void	SetFont (Font::Size size, Font::Style style);
	void	SetFont (const DGTEFontData* fontData);
	bool	GetFont (DGTEFontData* fontData) const;

	void		SetCharCode (GSCharCode charCode);
	GSCharCode	GetCharCode (void) const;

	void	SetTabSize (short tabSize);
	short	GetTabSize (void) const;

	Int32	GetLength () const;
	Int32	GetLineCount (void) const;
	Int32	GetLineFromPosition (Int32 charPosition) const;
	Int32	GetLineLength (Int32 lineIndex) const;
	void	SetLineMaxLength (short lineLength) const;
	Int32	GetLinePosition (Int32 lineIndex) const;

	void		SetSelection (const CharRange& selRange);
	CharRange	GetSelection (void) const;

	void	EnableDraw (void);
	void	DisableDraw (void);

	bool	FindString (CharRange* charRange, GS::UniString *text, Search::Dir dir = Search::Down,
						Search::Case sens = Search::InSensitive, Search::Word match = Search::NoMatchWord) const;

	void 	SetWordWrap (bool wordWrap);
	bool 	GetWordWrap (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const;
};

}	// namespace DG

#endif
