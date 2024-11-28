// *****************************************************************************
// File:			DGUniRichEdit.hpp
//
// Description:		UniRichEdit classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	TCs, SA
//
// SG compatible
// *****************************************************************************

#ifndef DGUNIRICHEDIT_HPP
#define DGUNIRICHEDIT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGUtility.hpp"
#include "DGItemProperty.hpp"

#include "DGItemEventArgs.hpp"
#include "DGEventNotifier.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class UniRichEdit;
	class IConvertOnCopyPaste;
}

namespace Gfx {
	class Color;
}

namespace GS {
	template<class T> class Array;
	class UniString;
}

namespace IO {
	class Location;
}

namespace TE {
	class CharStyle;
	class Tab;
	class Paragraph;
}


// --- Class declarations ------------------------------------------------------

namespace DG {


// --- UniRichEditDragSourceEvent -----------------------------------------------

class DG_DLL_EXPORT UniRichEditDragSourceEvent: public ItemDragSourceEvent
{
friend class UniRichEditDragSourceObserver;	// To access protected constructor
friend class UniRichEditObserver;			// To access protected constructor

protected:
	explicit UniRichEditDragSourceEvent (const ItemDragSourceEvent& ev);
			~UniRichEditDragSourceEvent ();

public:
	UniRichEdit*	GetSource (void) const;
};


// --- UniRichEditDragSourceObserver --------------------------------------------

class DG_DLL_EXPORT UniRichEditDragSourceObserver
{
protected:
			 UniRichEditDragSourceObserver ();
	virtual ~UniRichEditDragSourceObserver ();

public:
	virtual void	UniRichEditDragStarting (const UniRichEditDragSourceEvent& ev, bool* canStart);
	virtual void	UniRichEditDragStarted (const UniRichEditDragSourceEvent& ev, UShort* effect);
	virtual void	UniRichEditDragStarted (const UniRichEditDragSourceEvent& ev, UShort* effect, bool* rightDragMenu);
	virtual void	UniRichEditDragEnded (const UniRichEditDragSourceEvent& ev, DragDrop::Effect effect);
	virtual void	UniRichEditDragSetDelayedData (const UniRichEditDragSourceEvent& ev);
};


// --- UniRichEditDropTargetEvent ----------------------------------------------

class DG_DLL_EXPORT UniRichEditDropTargetEvent: public ItemDropTargetEvent
{
friend class UniRichEditObserver;				// To access protected constructor

private:
	ULong	caretPosition;

protected:
	explicit UniRichEditDropTargetEvent (const ItemDropTargetEvent& ev);
			~UniRichEditDropTargetEvent ();

public:
	UniRichEdit*	GetSource (void) const;

	ULong			GetCaretPosition (void) const;
};


// --- UniRichEditDropTargetObserver -------------------------------------------

class DG_DLL_EXPORT UniRichEditDropTargetObserver
{
protected:
			 UniRichEditDropTargetObserver ();
	virtual ~UniRichEditDropTargetObserver ();

public:
	virtual void	UniRichEditDragEntered (const UniRichEditDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour);
	virtual void	UniRichEditDragEntered (const UniRichEditDropTargetEvent& ev, DragDrop::Effect* effect,
											bool* defBehaviour, bool* rightDragMenu);
	virtual void	UniRichEditDragMoved (const UniRichEditDropTargetEvent& ev, DragDrop::Effect* effect, DragDrop::Feedback* denyFeedback);
	virtual void	UniRichEditDragLeft (const UniRichEditDropTargetEvent& ev, DragDrop::Effect* effect);
	virtual void	UniRichEditDropped (const UniRichEditDropTargetEvent& ev, DragDrop::Effect* effect);
};


// --- UniRichEditContentEvent --------------------------------------------------

class DG_DLL_EXPORT UniRichEditContentEvent: public ItemChangeEvent
{
friend class UniRichEditObserver;				// To access protected constructor

private:
	const DG::UniRichEditChangeEventArg*	changeData;

protected:
	explicit UniRichEditContentEvent (const ItemChangeEvent& ev);

public:
	~UniRichEditContentEvent ();

	UniRichEdit*	GetSource (void) const;

	CharRange		GetOldContentRange (void) const;
	CharRange		GetNewContentRange (void) const;
};


// --- UniRichEditSelectionEvent --------------------------------------------------

class DG_DLL_EXPORT UniRichEditSelectionEvent: public ItemChangeEvent
{
friend class UniRichEditObserver;				// To access protected constructor

private:
	const DG::UniRichEditChangeEventArg*	changeData;

protected:
	explicit UniRichEditSelectionEvent (const ItemChangeEvent& ev);

public:
	~UniRichEditSelectionEvent ();

	UniRichEdit*	GetSource (void) const;

	CharRange		GetOldSelection (void) const;
	CharRange		GetNewSelection (void) const;
};


// --- UniRichEditResizeEvent --------------------------------------------------

class DG_DLL_EXPORT UniRichEditResizeEvent: public ItemChangeEvent
{
friend class UniRichEditObserver;				// To access protected constructor

private:
	const DG::UniRichEditChangeEventArg*	resizeData;

protected:
	explicit UniRichEditResizeEvent (const ItemChangeEvent& ev);

public:
	~UniRichEditResizeEvent ();

	UniRichEdit*	GetSource (void) const;

	short			GetRequestedWidth (void) const;
	short			GetRequestedHeight (void) const;
	DG::NativeUnit	GetRequestedWidthInNativeUnits (void) const;
	DG::NativeUnit	GetRequestedHeightInNativeUnits (void) const;
};


// --- UniRichEditScrollBarChangeEvent -----------------------------------------

class DG_DLL_EXPORT UniRichEditScrollBarChangeEvent: public ItemChangeEvent
{
friend class UniRichEditObserver;				// To access protected constructor

private:
	const DG::UniRichEditChangeEventArg*	resizeData;

protected:
	explicit UniRichEditScrollBarChangeEvent (const ItemChangeEvent& ev);

public:
	~UniRichEditScrollBarChangeEvent ();

	UniRichEdit*	GetSource (void) const;

	Int32			GetOldHPosition (void) const;
	Int32			GetNewHPosition (void) const;

	Int32			GetOldVPosition (void) const;
	Int32			GetNewVPosition (void) const;
};


// --- UniRichEditObserver -----------------------------------------------------

class DG_DLL_EXPORT UniRichEditObserver: public ItemObserver,
										 public UniRichEditDragSourceObserver,
										 public UniRichEditDropTargetObserver
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

	virtual short	UniRichEditContentChanged (const UniRichEditContentEvent& ev);
	virtual short	UniRichEditSelectionChanged (const UniRichEditSelectionEvent& ev);
	virtual short	UniRichEditResizeRequested (const UniRichEditResizeEvent& ev);
	virtual short	UniRichEditScrollBarPositionChanged (const UniRichEditScrollBarChangeEvent& ev);

public:
	UniRichEditObserver ();
   ~UniRichEditObserver ();
};

// --- UniRichEdit -------------------------------------------------------------

class DG_DLL_EXPORT UniRichEdit: public Item,
								 public FocusableProperty,
								 public UniRichEditNotifyHandler,
								 public ItemDragDropNotifier<UniRichEdit>,
								 public ItemWheelNotifier<UniRichEdit>,
								 public ItemFocusNotifier<UniRichEdit>,
								 public FilterCharNotifier<UniRichEdit>
{
public:
	enum ScrollType {
		NoScroll	= DG_ET_NOSCROLL,
		HScroll		= DG_ET_HSCROLL,
		VScroll		= DG_ET_VSCROLL,
		HVScroll	= DG_ET_HSCROLL | DG_ET_VSCROLL,
		HAutoScroll = DG_ET_HAUTOSCROLL
	};

	enum FrameType {
		Frame		= DG_ET_FRAME,
		NoFrame		= DG_ET_NOFRAME
	};

	enum ReadOnlyType {
		Editable	= DG_ET_EDITABLE,
		ReadOnly	= DG_ET_READONLY
	};

	enum CharPos {
		TextBegin	= DG_REP_TEXTBEGIN,
		TextEnd		= DG_REP_TEXTEND
	};

	enum ResizeType {
		AutoResize	 = 0,
		NoAutoResize = DG_ET_NOAUTORESIZE
	};

	enum WrapType {
		EOFWrap		= 0,
		WordWrap	= DG_ET_WORDWRAP
	};

	// Character style flags
	enum CharStyleFlagType {
		ColorFlag		= DG_STY_COLOR,
		FontSizeFlag	= DG_STY_SIZE,
		FontFlag		= DG_STY_FONT,

		VShiftEffectFlag			= DG_STY_VSHIFT_EFFECT,
		StrikeThroughEffectFlag		= DG_STY_STRIKE_EFFECT,
		ProtectedFlag				= DG_STY_PROTECTED_EFFECT,
		EffectFlag		= DG_STY_ALLEFFECT,

		NormalStyleFlag				= DG_STY_NORMAL_STYLE,
		BoldStyleFlag				= DG_STY_BOLD_STYLE,
		ItalicStyleFlag				= DG_STY_ITALIC_STYLE,
		UnderlineStyleFlag			= DG_STY_UNDERLINE_STYLE,
		StyleFlag		= DG_STY_ALLSTYLE,

		AllCharFlags	= DG_STY_ALL
	};

	// Character Effect Types
	enum CharEffectType {
		StrikeOutEffect		= DG_FX_STRIKEOUT,
		SuperScriptEffect	= DG_FX_SUPERSCRIPT,
		SubScriptEffect		= DG_FX_SUBSCRIPT
	};

	enum StrikeOutType {
		NoStrikeOut			= 0,
		StrikeOut			= DG_FX_STRIKEOUT
	};

	enum SuperScriptType {
		NoSuperScript		= 0,
		SuperScript			= DG_FX_SUPERSCRIPT
	};

	enum SubScriptType {
		NoSubScript			= 0,
		SubScript			= DG_FX_SUBSCRIPT
	};

	// Font Style Types
	enum FontStyleType {
		BoldFontStyle		= DG_CHSTY_BOLD,
		ItalicFontStyle		= DG_CHSTY_ITALIC,
		UnderlineFontStyle	= DG_CHSTY_UNDERLINE
	};

	enum BoldType {
		NoBoldStyle			= 0,
		BoldStyle			= DG_CHSTY_BOLD
	};

	enum ItalicType {
		NoItalicStyle		= 0,
		ItalicStyle			= DG_CHSTY_ITALIC
	};

	enum UnderlineType {
		NoUnderlineStyle	= 0,
		UnderlineStyle		= DG_CHSTY_UNDERLINE
	};

	// Paragraph style flags
	enum ParaStyleFlagType {
		JustFlag		= DG_PARA_JUSTIFICATION,
		FirstIndentFlag	= DG_PARA_FIRSTINDENT,
		LeftIndentFlag	= DG_PARA_LEFTINDENT,
		RightIndentFlag	= DG_PARA_RIGHTINDENT,
		TabFlag			= DG_PARA_TABULATORS,
		LeadingFlag		= DG_PARA_LEADING,
		AllParaFlags	= DG_PARA_ALL
	};

	enum JustType {
		LeftJustify		= DG_JSTY_LEFT,
		CenterJustify	= DG_JSTY_CENTER,
		RightJustify	= DG_JSTY_RIGHT,
		FullJustify		= DG_JSTY_FULL
	};

//	enum TabAlignment {
//		LeftAlign		= DG_TAB_LEFT,
//		CenterAlign		= DG_TAB_CENTER,
//		RightAlign		= DG_TAB_RIGHT,
//		DecimalAlign	= DG_TAB_DECIMAL
//	};

private:
	void InitNotifiers ();

	virtual void	NotifyChangeEvent (const UniRichEditChangeEventArg& eventArg);

public:
	UniRichEdit (const Panel& panel, short item, IConvertOnCopyPaste* convert = nullptr);
	UniRichEdit (const Panel& panel, const Rect& rect, ScrollType scroll = NoScroll, FrameType frame = Frame,
				 ReadOnlyType readOnly = Editable, ResizeType resize = AutoResize, WrapType wrap = EOFWrap,
				 IConvertOnCopyPaste* convert = nullptr);
   ~UniRichEdit ();

	EventNotifier<UniRichEdit, const UniRichEditChangeEventArg> onContentChanged;
	EventNotifier<UniRichEdit, const UniRichEditChangeEventArg> onSelectionChanged;
	EventNotifier<UniRichEdit, const UniRichEditChangeEventArg> onResizeRequested;
	EventNotifier<UniRichEdit, const UniRichEditChangeEventArg> onScrollBarChanged;

	void			Attach (UniRichEditObserver& observer);
	void			Detach (UniRichEditObserver& observer);

	void			CatText (const GS::UniString& text);
	void			SetText (const GS::UniString& text);
	void			SetTextRange (const CharRange& charRange, const GS::UniString& text);

	GS::UniString	GetText (EOL::Type eolType = EOL::Default) const;
	GS::UniString	GetTextRange (const CharRange& charRange, EOL::Type eolType = EOL::Default) const;

	Int32			GetTextLength (EOL::Type eolType = EOL::Default) const;
	Int32			GetTextRangeLength (const CharRange& charRange, EOL::Type eolType = EOL::Default) const;

	void			SetDefaultTabSize (double tabSize);
	double			GetDefaultTabSize (void) const;

	void			SetTextBoxWidth (double boxWidth);
	double			GetTextBoxWidth (void) const;

	Int32			GetLineCount (void) const;
	Int32			GetLineFromPosition (Int32 charPosition) const;
	Int32			GetLineLength (Int32 lineIndex) const;
	Int32			GetLinePosition (Int32 lineIndex) const;
	bool			HasText () const;

	void			SetSelection (const CharRange& selRange);
	CharRange		GetSelection (void) const;

	bool			FindString (CharRange* charRange, const GS::UniString& text,
								Search::Dir dir = Search::Down,
								Search::Case sens = Search::InSensitive,
								Search::Word match = Search::NoMatchWord) const;

	void			SetDefaultCharcode (GSCharCode charcode);
	void			SetCharStyle (const DG::CharRange& charRange, const TE::CharStyle& charStyle,
								  CharStyleFlagType styleFlag = AllCharFlags);
	void			GetCharStyle (const DG::CharRange& charRange, TE::CharStyle* charStyle) const;

	void			SetCharColor (const DG::CharRange& charRange, const Gfx::Color& charColor);
	Gfx::Color		GetCharColor (const DG::CharRange& charRange) const;

	void			SetCharEffects (const DG::CharRange& charRange, StrikeOutType strikeOut,
									SuperScriptType superScript, SubScriptType subScript);
	void			GetCharEffects (const DG::CharRange& charRange, StrikeOutType* strikeOut,
									SuperScriptType* superScript, SubScriptType* subScript) const;
	void			ToggleCharEffect (const DG::CharRange& charRange, CharEffectType effectType);
	void			SetCharEffect (const DG::CharRange& charRange, CharEffectType effectType, bool state);
	bool			GetCharEffect (const DG::CharRange& charRange, CharEffectType effectType) const;

	void			SetFontSize (const DG::CharRange& charRange, double fontSize);
	double			GetFontSize (const DG::CharRange& charRange) const;
	void			SetFontStyles (const DG::CharRange& charRange, BoldType boldStyle,
								   ItalicType italicStyle, UnderlineType underlineStyle);
	void			GetFontStyles (const DG::CharRange& charRange, BoldType* boldStyle, ItalicType* italicStyle,
								   UnderlineType* underlineStyle) const;
	void			ToggleFontStyle (const DG::CharRange& charRange, FontStyleType styleType);
	void			SetFontStyle (const DG::CharRange& charRange, FontStyleType styleType, bool state);
	bool			GetFontStyle (const DG::CharRange& charRange, FontStyleType styleType) const;

	void			SetFontName (const DG::CharRange& charRange, const GS::UniString& fontName);
	GS::UniString	GetFontName (const DG::CharRange& charRange) const;

	void			SetParagraph (const DG::CharRange& charRange, const TE::Paragraph& paragraphData,
								  ParaStyleFlagType styleFlag);
	void			GetParagraph (const DG::CharRange& charRange, TE::Paragraph* paragraphData) const;

	void			SetJustification (const DG::CharRange& charRange, JustType justification);
	JustType		GetJustification (const DG::CharRange& charRange) const;
	void			SetFirstIndent (const DG::CharRange& charRange, double firstIndent);
	double			GetFirstIndent (const DG::CharRange& charRange) const;
	void			SetLeftIndent (const DG::CharRange& charRange, double leftIndent);
	double			GetLeftIndent (const DG::CharRange& charRange) const;
	void			SetRightIndent (const DG::CharRange& charRange, double rightIndent);
	double			GetRightIndent (const DG::CharRange& charRange) const;
	void			SetLeading (const DG::CharRange& charRange, double leading);
	double			GetLeading (const DG::CharRange& charRange) const;

	void			SetTabs (const DG::CharRange& charRange, const GS::Array<TE::Tab>& tabParameters);
	void			SetTab (const DG::CharRange& charRange, Int32 tabIndex, const TE::Tab& tabParameter);
	Int32			GetTabNum (const DG::CharRange& charRange) const;
	void			GetTabs (const DG::CharRange& charRange, GS::Array<TE::Tab>* tabParameters) const;
	TE::Tab			GetTab (const DG::CharRange& charRange, Int32 tabIndex) const;

	void			GetRuns (const DG::CharRange& charRange, GS::Array<DG::CharRange>* bounds) const;
	void			GetParagraphBounds (const DG::CharRange& charRange, GS::Array<DG::CharRange>* bounds) const;

	Int32			GetOffsetFromPoint (const DG::Point& pt, bool pointIsRelativeToControl = false) const;

	void			PasteFromScrap ();
	GSErrCode		Dropped (UInt32 flavorType, void* dropData, Int32 dataSize, IO::Location* droppedFile);

	void			ClearUndo (void);
	void			BeginUndoAction (void);
	void			EndUndoAction (void);

	void			RunCharSelector (void);

	void			SetBackground (const Gfx::Color& bkgndColor);

	void			SetupPhase (bool start);

	void			ToggleCheckSpellingAsYouType ();
	bool			IsCheckSpellingAsYouType () const;
	void			ShowSpellingPanel ();

	Rect			GetCharRect (UIndex charPosition) const;

	void			SetCopyPasteConverter (IConvertOnCopyPaste* convert);

	virtual GSErrCode	Store (GS::ObjectState& os) const;

	class DG_DLL_EXPORT SetupPhaseGuard
	{
	private:
		DG::UniRichEdit& uniRichEdit;
	public:
		SetupPhaseGuard (DG::UniRichEdit& edit) : uniRichEdit (edit)
		{
			uniRichEdit.SetupPhase (true);
		}
		~SetupPhaseGuard ()
		{
			uniRichEdit.SetupPhase (false);
		}
	};
};

}	// namespace DG

#endif
