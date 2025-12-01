// *********************************************************************************************************************
// File:			DGCommonEventArgs.hpp
//
// Description:		Dialog manager event handling.
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	SZM
// *********************************************************************************************************************

#ifndef DG_COMMON_EVENTARGS_HPP
#define DG_COMMON_EVENTARGS_HPP

#include "DGEventArgs.hpp"
#include "DGNativeUnit.hpp"
#include "UniString.hpp"

typedef Int32 DGDragFormat;					// Drag drop data type identifier format

namespace DG {

// --- IntBasedEventArg ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT IntBasedEventArg: public EventArg
{
	Int64 intData = 0;

public:
	static IntBasedEventArg None;

	IntBasedEventArg () = default;
	IntBasedEventArg (Int64 data);
	virtual	~IntBasedEventArg ();

	virtual		operator Int64() const override;
	virtual		operator Int32() const override;
	virtual		operator short() const override;
	virtual		operator UShort() const override;
	virtual		operator ULong() const override;

	virtual bool	operator== (short data) const override;
	virtual bool	operator== (Int32 data) const override;
	virtual bool	operator== (Int64 data) const override;
	virtual bool	operator== (UInt64 data) const override;
			bool	operator== (const IntBasedEventArg& other) const;

			bool	operator!= (const IntBasedEventArg& other) const;

	virtual bool	operator< (short data) const override;
	virtual bool	operator< (Int32 data) const override;
	virtual bool	operator< (Int64 data) const override;
			bool	operator< (const IntBasedEventArg& other) const;

	virtual bool	operator> (short data) const override;
	virtual bool	operator> (Int32 data) const override;
	virtual bool	operator> (Int64 data) const override;
			bool	operator> (const IntBasedEventArg& other) const;
};


// --- DG::DragDropEventArg --------------------------------------------------------------------------------------------

class DG_DLL_EXPORT DragDropEventArg: public EventArg
{
public:
	UShort			subMessage;				// Sub message identifier
	UShort			effect;					// The effect allowed and resulted in a drag and drop operation
	UShort			denyFeedback;			// Denies some feedback functionality -> this is a return value
	short			xPos;					// Horizontal mouse position relative to the client rect
	short			yPos;					// Vertical mouse position relative to the client rect
	Int32			insertPos;				// Drag and drop item insertion position
	short			relativePos;			// Relative position to the insertion position (on, above, under)
	DGDragFormat	rqFormat;				// Requested format on a delayed drag and drop.
	const void*		sourceFeedback;			// Platform dependent native image. On Mac must be a CGImage or HBITMAP on Windows (defined for user items)
	short			feedbackLeft;			// Left of feedback image rect
	short			feedbackTop;			// Top of feedback image rect
	short			feedbackRight;			// Right of feedback image rect
	short			feedbackBottom;			// Bottom of feedback image rect
	bool			rightDragCtxMenu;		// Bring up the Copy/Move/Cancel right drag context menu
	const GS::uchar_t*	folderPath;			// The destination folder on a delayed 'FILE' drag and drop

	virtual ~DragDropEventArg ();
};


// --- DG::ContextMenuEventArg -----------------------------------------------------------------------------------------

class DG_DLL_EXPORT ContextMenuEventArg: public EventArg
{
public:
	short			panelId = 0;				// Id of the panel whose context help is requested
	short			itemId = 0;					// Id of the item above which the event occured
	DG::NativeUnit	xPos;						// Horizontal mouse position in screen coordinates
	DG::NativeUnit	yPos;						// Vertical mouse position in screen coordinates
	Int32			treeItem = 0;				// The TreeView item above which the event occured
	short			listItem = 0;				// The ListBox or ListView item above which the event occured
	short			listHeaderItem = 0;			// The ListBox Header item above which the event occured
	bool			inListHeaderButton = 0;		// Event occured above the listbox header button
	Int32			tabBarItemId = 0;			// Tabbar item identifier above the event occured
	bool			needHelp = false;			// If the first "What's this" context item is selected and the message is not handled (let DG launch the borwser with the help anchor)

	virtual ~ContextMenuEventArg ();
};


// --- DG::WheelEventArg -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT WheelEventArg: public EventArg
{
public:
	short			subMessage;					// DG_TSM_TRACKENTER, DG_TSM_TRACKING, DG_TSM_TRACKEXIT
	short			itemId;						// Id of the item above which the event occured
	short			xPos;						// Horizontal mouse position relative to the client rect
	short			yPos;						// Vertical mouse position relative to the client rect
	short			xTrackValue;				// Value of the mouse wheel rotation
	short			yTrackValue;				// Value of the mouse wheel rotation
	short			keyFlag;					// DG_MOD_COMMAND, DG_MOD_OPTION, DG_MOD_SHIFT
	short			processedKeyFlag;			// DG_MOD_COMMAND, DG_MOD_OPTION, DG_MOD_SHIFT
	bool			fromTouchCapableDevice;		// Trackpad, Magic Mouse on macOS

	WheelEventArg ();
	virtual	~WheelEventArg ();

	void	Init ();
};


// --- DG::HelpEventArg ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT HelpEventArg: public EventArg
{
public:
	short			subMessage;				// DG_HSM_TOOLTIP, DG_HSM_CONTEXTHELP
	short			itemId;					// Id of the item whose help is requested
	Int32			treeItem;				// The TreeView item above which the help is requested
	short			listItem;				// The ListBox or ListView item whose help is requested
	short			filler;					// filler
	Int32			tabBarItemId;			// The TabBar item identifier above the help is requested
	GS::UniString	toolTipText;			// the tooltip text
	GS::UniString	contextHelpAnchor;		// the help anchor text

	HelpEventArg ();
	virtual	~HelpEventArg ();

	void	Init ();
};


// --- DG::UserDefinedEventArg -----------------------------------------------------------------------------------------

typedef	EventArg	UserDefinedEventArg;

}

#endif // DG_COMMON_EVENTARGS_HPP
