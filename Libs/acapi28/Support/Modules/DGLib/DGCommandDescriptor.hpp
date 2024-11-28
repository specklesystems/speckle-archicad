// *****************************************************************************
// File:			DGCommandDescriptor.hpp
//
// Description:		CommmandDescriptor related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA, BL, MD
//
// SG compatible
// *****************************************************************************

#ifndef DGCOMMANDESCRIPTOR_HPP
#define DGCOMMANDESCRIPTOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGCommandEvent.hpp"
#include "Array.hpp"
#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"
#include "HashTable.hpp"

#include "DG.h"
#include "DGUtility.hpp"

#include "DGShortcutManager.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class CommandDescriptor;
	class MultiCommandDescriptor;
	class Shortcut;
	struct CmdDescInfo;
}

namespace GS {
	class ProcessControl;
}

namespace DG {

// --- Type definitions --------------------------------------------------------

typedef GS::HashTable<DG::Command, DG::CommandDescriptor*>	CommandTable;
typedef GS::Array<DG::CommandDescriptor*>					CommandArray;
typedef GS::HashTable<GS::UniString, Int32>					CommandCategoryTable;
typedef GS::HashTable<DG::Command, DG::CmdDescInfo>			CommandInfoTable;


// --- Resource functions ------------------------------------------------------

DG_DLL_EXPORT GSErrCode	ReadCommandResource (GSResModule commandResModule, GSResModule iconResModule, Int32 resID, CommandTable* commandTable, GS::UniString* category = nullptr, const CommandInfoTable* infoTable = nullptr, ULong devId = 0, ULong productId = 0);


// --- Class declarations ------------------------------------------------------

// --- CommandDescriptorEvent --------------------------------------------------

class DG_DLL_EXPORT CommandDescriptorEvent :		public GS::Event
{
protected:
	explicit CommandDescriptorEvent (CommandDescriptor* source);

public:
	virtual ~CommandDescriptorEvent ();

	CommandDescriptor*	GetSource (void) const;
};


// --- CommandDescriptorCheckEvent ---------------------------------------------

class DG_DLL_EXPORT CommandDescriptorCheckEvent :		public CommandDescriptorEvent
{
	friend class CommandDescriptor;			// To access protected constructor

protected:
	explicit CommandDescriptorCheckEvent (CommandDescriptor* source);

public:
	virtual ~CommandDescriptorCheckEvent ();
};


// --- CommandDescriptorEnableEvent --------------------------------------------

class DG_DLL_EXPORT CommandDescriptorEnableEvent :	public CommandDescriptorEvent
{
	friend class CommandDescriptor;			// To access protected constructor

protected:
	explicit CommandDescriptorEnableEvent (CommandDescriptor* source);

public:
	virtual ~CommandDescriptorEnableEvent ();
};


// --- CommandDescriptorShortcutEvent ------------------------------------------

class DG_DLL_EXPORT CommandDescriptorShortcutEvent :	public CommandDescriptorEvent
{
	friend class CommandDescriptor;			// To access protected constructor

	const Shortcut*		shortcut;
protected:
	explicit CommandDescriptorShortcutEvent (CommandDescriptor* source, const Shortcut* shortcut);

public:
	virtual ~CommandDescriptorShortcutEvent ();

	const Shortcut*		GetShortcut (void) const;
};


// --- CommandDescriptorTextEvent ----------------------------------------------

class DG_DLL_EXPORT CommandDescriptorTextEvent :		public CommandDescriptorEvent
{
	friend class CommandDescriptor;			// To access protected constructor

	GS::UniString		previousText;

protected:
	explicit CommandDescriptorTextEvent (CommandDescriptor* source, const GS::UniString& prevText);

public:
	virtual ~CommandDescriptorTextEvent ();

	const GS::UniString&	GetPreviousText (void) const;
};


// --- CommandDescriptorDescEvent ----------------------------------------------

class DG_DLL_EXPORT CommandDescriptorDescEvent :		public CommandDescriptorEvent
{
	friend class CommandDescriptor;			// To access protected constructor

	GS::UniString		previousDesc;

protected:
	explicit CommandDescriptorDescEvent (CommandDescriptor* source, const GS::UniString& prevDesc);

public:
	virtual ~CommandDescriptorDescEvent ();

	const GS::UniString&	GetPreviousDesc (void) const;
};


// --- CommandDescriptorIconEvent ----------------------------------------------

class DG_DLL_EXPORT CommandDescriptorIconEvent :		public CommandDescriptorEvent
{
	friend class CommandDescriptor;			// To access protected constructor

	DG::Icon		previousIcon;

protected:
	explicit CommandDescriptorIconEvent (CommandDescriptor* source, const DG::Icon& prevIcon);

public:
	virtual ~CommandDescriptorIconEvent ();

	const DG::Icon&	GetPreviousIcon (void) const;
};


// --- CommandDescriptorDeleteEvent --------------------------------------------

class DG_DLL_EXPORT CommandDescriptorDeleteEvent :		public CommandDescriptorEvent
{
	friend class CommandDescriptor;			// To access protected constructor

protected:
	explicit CommandDescriptorDeleteEvent (CommandDescriptor* source);

public:
	virtual ~CommandDescriptorDeleteEvent ();
};


// --- CommandDescriptorObserver -----------------------------------------------

class DG_DLL_EXPORT CommandDescriptorObserver :		public GS::EventObserver
{
	friend class CommandDescriptor;

protected:
	virtual	void	CheckChanged		(const CommandDescriptorCheckEvent& ev);
	virtual	void	EnableChanged		(const CommandDescriptorEnableEvent& ev);
	virtual	void	TextChanged			(const CommandDescriptorTextEvent& ev);
	virtual	void	DescChanged			(const CommandDescriptorDescEvent& ev);
	virtual	void	IconChanged			(const CommandDescriptorIconEvent& ev);
	virtual	void	ShortcutAdded		(const CommandDescriptorShortcutEvent& ev);
	virtual	void	ShortcutRemoving	(const CommandDescriptorShortcutEvent& ev);
	virtual	void	CmdDescDeleting		(const CommandDescriptorDeleteEvent& ev);

public:
	CommandDescriptorObserver ();
   ~CommandDescriptorObserver ();
};


// --- CommandDescriptor -------------------------------------------------------

struct DG_DLL_EXPORT CmdDescInfo {
	bool			skip;
	bool			multi;
	bool			visible;
	SystemCommand	systemCommand;
	Command			moreCommand;

	USize			displayCount;
	USize			maxItem;

	enum ExtraParam {
		SkipCmdDesc
	};

	CmdDescInfo () {
		this->skip	= false;
		this->multi = false;
		this->visible = false;
		this->systemCommand = Invalid;
		this->displayCount = 0;
		this->maxItem = 0;
	}

	explicit CmdDescInfo (ExtraParam extraParam) {
		this->skip	= (extraParam == SkipCmdDesc);
		this->multi = false;
		this->visible = false;
		this->systemCommand = Invalid;
		this->displayCount = 0;
		this->maxItem = 0;
	}

	explicit CmdDescInfo (bool visible) {
		this->skip	= false;
		this->multi = false;
		this->visible = visible;
		this->systemCommand = Invalid;
	}

	explicit CmdDescInfo (SystemCommand systemCommand) {
		this->skip	= false;
		this->multi = false;
		this->visible = true;
		this->systemCommand = systemCommand;
	}

	CmdDescInfo (bool visible, USize displayCount, USize maxItem = 0) {
		this->skip	= false;
		this->multi = true;
		this->visible = visible;
		this->systemCommand = Invalid;
		this->displayCount = displayCount;
		this->maxItem = maxItem;
	}

	CmdDescInfo (bool visible, USize displayCount, USize maxItem, const Command& moreCommand) {
		this->skip	= false;
		this->multi = true;
		this->visible = visible;
		this->systemCommand = Invalid;
		this->moreCommand = moreCommand;
		this->displayCount = displayCount;
		this->maxItem = maxItem;
	}
};


class DG_DLL_EXPORT CommandDescriptor :		public GS::EventSource
{
	friend class ShortcutManager;
	friend class ShortcutScheme;
	friend class ShortcutUsage;
	friend DG_DLL_EXPORT GSErrCode	ReadCommandResource (GSResModule commandresModule, GSResModule iconResModule, Int32, CommandTable*, GS::UniString*, const CommandInfoTable*, ULong, ULong);


public:
	enum	SpecialTextIndex {
		CurrentText	= 0xffff,
		LastText	= 0xfffe
	};

private:
	void		Init (const DG::Command& command, SystemCommand systemCommand);
	GSErrCode	RefreshAllShortcut	(void);

protected:
	// attributes
	DG::Command			command;
	ULong				osCommandId;		// redundant data -> for speed

	GS::UniString				category;

	GS::ArrayFB <GS::UniString, 2>	cleanText;
	GS::ArrayFB <GS::UniString, 2>	text;
	UIndex						textIndex;
	GS::UniString				description;
	DG::Icon					icon;
	DG::Picture					picture;
	bool						enabled;
	bool						checked;

	bool						visible;

	// stored data for disabling the "enable" notfications
	bool						statusNotificationDisabled;
	bool						oldEnableState;

	// observer notifications
	void		ProcessEnableEvent				(const CommandDescriptorEnableEvent& ev);
	void		ProcessCheckEvent				(const CommandDescriptorCheckEvent& ev);
	void		ProcessTextEvent				(const CommandDescriptorTextEvent& ev);
	void		ProcessDescEvent				(const CommandDescriptorDescEvent& ev);
	void		ProcessIconEvent				(const CommandDescriptorIconEvent& ev);
	void		ProcessShortcutAddEvent			(const Shortcut* shortcut);
	void		ProcessShortcutAddEvent			(const CommandDescriptorShortcutEvent& ev);
	void		ProcessShortcutRemovingEvent	(const Shortcut* shortcut);
	void		ProcessShortcutRemovingEvent	(const CommandDescriptorShortcutEvent& ev);
	void		ProcessDeleteEvent				(const CommandDescriptorDeleteEvent& ev);

	// constructor
				CommandDescriptor				(const CommandDescriptor& source);

public:
	// static methods
	static CommandDescriptor*			GetDummyDescriptor	(void);
	static CommandDescriptor*			GetVisibleDummyDescriptor (void);
	static const CommandTable&			GetCommandTable		(void);
	static const CommandCategoryTable&	GetCommandCategoryTable (void);
	static GS::UniString				GetCleanText		(const GS::UniString& text);
	static void							AddOldCommand (const DG::Command& command);
	static bool							IsOldCommand  (const DG::Command& command);

	// constructors / destructors
								CommandDescriptor	(const DG::Command& command,
													 const GS::UniString& text,
													 const GS::UniString& category = GS::UniString(),
													 bool visible = true,
													 SystemCommand systemCommand = Invalid);

								CommandDescriptor	(const DG::Command& command,
													 const GS::UniString& text,
													 const DG::Icon& icon,
													 const GS::UniString& category = GS::UniString(),
													 bool visible = true,
													 SystemCommand systemCommand = Invalid);

								CommandDescriptor	(const DG::Command& command,
													 const GS::UniString& text,
													 const DG::Picture& picture,
													 const GS::UniString& category = GS::UniString(),
													 bool visible = true,
													 SystemCommand systemCommand = Invalid);

	virtual					   ~CommandDescriptor ();

	void						Attach				(CommandDescriptorObserver& observer);
	void						Detach				(CommandDescriptorObserver& observer);

	void						DisableStatusNotification	(void);
	void						EnableStatusNotification	(void);

	// accessors
	ULong						GetOSCommandId		(void) const;
	const DG::Command&			GetCommand			(void) const;

	const GS::UniString&		GetCategory			(void) const;

	const GS::UniString&		GetText				(UIndex index = CurrentText) const;
	const GS::UniString&		GetCleanText		(UIndex index = CurrentText) const;
	const GS::UniString&		GetDescription		(void) const;
	DG::Icon					GetIcon				(void) const;
	DG::Picture					GetPicture			(void) const;
	bool						IsEnabled			(void) const;
	bool						IsChecked			(void) const;
	bool						IsVisible			(void) const;

	void						SetText				(const GS::UniString& newText, UIndex index = CurrentText);
	UIndex						SetCurrentText		(UIndex index);
	UIndex						GetCurrentTextIndex	(void);
	void						SetDescription		(const GS::UniString& newDescription);
	void						SetIcon				(const DG::Icon& newIcon);

	virtual void				Check				(void);
	virtual void				UnCheck				(void);
	void						SetState			(bool state);

	virtual	void				Enable				(void);
	virtual	void				Disable				(void);
	void						SetStatus			(bool status);


	// shortcut methods
	GSErrCode					AddShortcut			(Key::Code key, ULong modifiers, const GS::Guid& contextGuid, bool fixedShortcut = false);
	GSErrCode					RemoveShortcut		(Shortcut* shortcut);
	GSErrCode					RemoveShortcut		(Shortcut* shortcut, const GS::Guid& contextGuid);
	GSErrCode					RemoveAllShortcut	(const GS::Guid& contextGuid);
	GSErrCode					RemoveAllShortcut	(void);

	ShortcutIterator			GetActiveShortcutIterator
													(void) const;
};


// --- MultiCommandDescriptorEvent ---------------------------------------------

class DG_DLL_EXPORT MultiCommandDescriptorEvent :		public GS::Event
{
protected:
	explicit MultiCommandDescriptorEvent (MultiCommandDescriptor* source);

public:
	virtual ~MultiCommandDescriptorEvent ();

	MultiCommandDescriptor*	GetSource (void) const;
};


// --- MultiCommandDescriptorClearEvent ----------------------------------------

class DG_DLL_EXPORT MultiCommandDescriptorClearEvent :		public MultiCommandDescriptorEvent
{
	friend class MultiCommandDescriptor;			// To access protected constructor

protected:
	explicit MultiCommandDescriptorClearEvent (MultiCommandDescriptor* source);

public:
	virtual ~MultiCommandDescriptorClearEvent ();
};


// --- MultiCommandDescriptorBuildEvent ----------------------------------------

class DG_DLL_EXPORT MultiCommandDescriptorBuildEvent :		public MultiCommandDescriptorEvent
{
	friend class MultiCommandDescriptor;			// To access protected constructor

protected:
	explicit MultiCommandDescriptorBuildEvent (MultiCommandDescriptor* source);

public:
	virtual ~MultiCommandDescriptorBuildEvent ();
};


// --- MultiCommandDescriptorObserver ------------------------------------------

class DG_DLL_EXPORT MultiCommandDescriptorObserver :	public CommandDescriptorObserver
{
	friend class MultiCommandDescriptor;

protected:
	virtual	void	ClearItems		(const MultiCommandDescriptorClearEvent& ev);
	virtual	void	BuildItems		(const MultiCommandDescriptorBuildEvent& ev);

public:
	MultiCommandDescriptorObserver ();
   ~MultiCommandDescriptorObserver ();
};


// --- MultiCommandDescriptor --------------------------------------------------

class DG_DLL_EXPORT MultiCommandDescriptor :	public CommandDescriptor
{
	friend DG_DLL_EXPORT GSErrCode	ReadCommandResource (GSResModule commandResModule, GSResModule iconResModule, Int32, CommandTable*, GS::UniString*, const CommandInfoTable*, ULong, ULong);

private:
	struct CommandItem {
		CommandDescriptor*		commandDescriptor;
		GS::Object*				data;

		inline	CommandItem () { commandDescriptor = nullptr; data = nullptr;}
		inline	CommandItem (CommandDescriptor* cmdDesc, GS::Object* d) { commandDescriptor = cmdDesc; data = d;}
	};

	// attributes
	CommandDescriptor*						moreItemsDescriptor;
	GS::Array<CommandItem>					commandItems;
	USize									maxDisplayedItemCount;
	USize									maxItemCount;
	GSIndex									radioChecked;
	Command									customMoreCommand;

	// observer notifications
	void		ProcessClearEvent			(const MultiCommandDescriptorClearEvent& ev);
	void		ProcessBuildEvent			(const MultiCommandDescriptorBuildEvent& ev);

	void		Init						(const DG::Command& command, const DG::Command* customMoreCommand = nullptr);

	// sort predicate
	static bool	SortByCommandTextAsc		(const CommandItem& item1, const CommandItem& item2);
	static bool	SortByCommandTextDesc		(const CommandItem& item1, const CommandItem& item2);

	// constructors
	MultiCommandDescriptor					(const MultiCommandDescriptor& source);

	MultiCommandDescriptor&	operator=		(const MultiCommandDescriptor& source);

public:
	// constructors / destructors
						MultiCommandDescriptor		(const DG::Command& command,
													 const GS::UniString& text,
													 const GS::UniString& category = GS::UniString(),
													 bool visible = true);

						MultiCommandDescriptor		(const DG::Command& command,
													 const GS::UniString& text,
													 const DG::Icon& icon,
													 const GS::UniString& category = GS::UniString(),
													 bool visible = true);

						MultiCommandDescriptor		(const DG::Command& command,
													 const GS::UniString& text,
													 const DG::Picture& picture,
													 const GS::UniString& category = GS::UniString(),
													 bool visible = true);

						MultiCommandDescriptor		(const DG::Command& command,
													 const GS::UniString& text,
													 const GS::UniString& category,
													 bool visible,
													 const DG::Command& customCommand);

	virtual			   ~MultiCommandDescriptor		();

	void				Attach 						(MultiCommandDescriptorObserver& observer);
	void				Detach 						(MultiCommandDescriptorObserver& observer);

	// accessors
	virtual	void		Enable						(void) override;

	USize				GetDisplayedItemMaxCount	(void) const;
	void				SetDisplayedItemMaxCount	(USize maxDisplayedItemCount);

	USize				GetItemMaxCount				(void) const;
	void				SetItemMaxCount				(USize maxItemCount);

	GS::UniString		GetMoreItemsText			(void) const;
	GS::UniString		GetMoreItemsDescription		(void) const;
	void				SetMoreItemsText			(const GS::UniString& moreItemsText);
	void				SetMoreItemsDescription		(const GS::UniString& moreItemsDescription);

	const Command&		GetCustomMoreCommand		(void) const;

	// item methods
	USize				GetDisplayedItemCount		(void) const;
	CommandDescriptor*	GetDisplayedItem			(UIndex index);

	void				SortAscending				(void);
	void				SortDescending				(void);

	USize				GetItemCount				(void) const;
	GSIndex				GetItemIndex				(CommandDescriptor* commandDescriptor) const;
	CommandDescriptor*	GetItem						(UIndex index) const;
	GS::Object*			GetItemData					(UIndex index) const;
	GSErrCode			AddItem						(const GS::UniString& itemText, GS::Object* data = nullptr, const DG::Icon& icon = DG::Icon ());
	GSErrCode			AddItem						(const GS::UniString& itemText, const GS::UniString& longDescription, GS::Object* data = nullptr, const DG::Icon& icon = DG::Icon ());
	GSErrCode			AddSeparatorItem			(void);
	GSErrCode			InsertItem					(UIndex index, const GS::UniString& itemText, GS::Object* data = nullptr, const DG::Icon& icon = DG::Icon ());
	GSErrCode			InsertItem					(UIndex index, const GS::UniString& itemText, const GS::UniString& longDescription, GS::Object* data = nullptr, const DG::Icon& icon = DG::Icon ());
	GSErrCode			InsertSeparatorItem			(UIndex index);
	GSErrCode			RemoveItem					(UIndex index);
	GSErrCode			Clear						(void);

	void				SetRadioChecked				(UIndex index);
};


// --- MultiCommandEvent -------------------------------------------------------

class DG_DLL_EXPORT MultiCommandEvent : public CommandEvent
{
private:
	MultiCommandDescriptor*	multiCommandDescriptor;

public:
	inline		MultiCommandEvent (const Command& commandIdParam,
								   CommandDescriptor* commandDescriptorParam,
								   MultiCommandDescriptor* multiCommandDescriptorParam);
			   ~MultiCommandEvent ();

	virtual		MultiCommandEvent*		Clone	(void) const override;

	inline MultiCommandDescriptor*	GetMultiCommandDescriptor	(void) const;
};


inline MultiCommandEvent::MultiCommandEvent (const Command& commandIdParam,
											 CommandDescriptor* commandDescriptorParam,
											 MultiCommandDescriptor* multiCommandDescriptorParam)
	:	CommandEvent			(commandIdParam, commandDescriptorParam),
		multiCommandDescriptor	(multiCommandDescriptorParam)
{
}


inline MultiCommandEvent*	MultiCommandEvent::Clone (void) const
{
	try {
		return new MultiCommandEvent (*this);
	} catch (GS::OutOfMemoryException&) {
		return nullptr;
	}
}


inline MultiCommandDescriptor*	MultiCommandEvent::GetMultiCommandDescriptor (void) const
{
	return multiCommandDescriptor;
}

}	// namespace DG

#endif
