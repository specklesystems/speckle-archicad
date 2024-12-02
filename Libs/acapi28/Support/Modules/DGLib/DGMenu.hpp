// *****************************************************************************
// File:			DGMenu.hpp
//
// Description:		Menu related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA, BL, MD
//
// SG compatible
// *****************************************************************************

#ifndef DGMENU_HPP
#define DGMENU_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Object.hpp"
#include "Event.hpp"
#include "EventSource.hpp"
#include "Array.hpp"

#include "DGCommandDescriptor.hpp"
#include "DGMenuItem.hpp"

#include "DG.h"
#include "DGUtility.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace xercesc_3_0 {
	class DOMElement;
}
namespace xercesc = xercesc_3_0;

namespace DG {
	class Menu;
	class MenuImpl;
	class MenuItem;
	class ContextMenuImpl;
	class CommandLayoutSerializer;
	class CommandLayoutDeserializer;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- MenuEvent ---------------------------------------------------------------

class DG_DLL_EXPORT MenuEvent :		public GS::Event
{
protected:
	explicit MenuEvent (Menu* source);

public:
	virtual ~MenuEvent ();

	Menu*	GetSource (void) const;
};


// --- MenuDisplayedItemListEvent ----------------------------------------------

class DG_DLL_EXPORT MenuDisplayedItemListEvent :		public MenuEvent
{
	friend class Menu;			// To access protected constructor

	bool	empty;

protected:
	explicit MenuDisplayedItemListEvent (Menu* source, bool empty);

public:
	virtual ~MenuDisplayedItemListEvent ();

	bool	IsEmptyDisplayedItemList (void) const;
};


// --- MenuObserver ------------------------------------------------------------

class DG_DLL_EXPORT MenuObserver :		public GS::EventObserver
{
	friend class Menu;

protected:
	virtual	void	MenuDisplayedListChanged	(const MenuDisplayedItemListEvent& ev);
	virtual void	MenuTrackEntered			();
	virtual void	MenuTrackExited				();

public:
	MenuObserver ();
   ~MenuObserver ();
};


// --- Menu --------------------------------------------------------------------

class DG_DLL_EXPORT Menu :	public GS::Object,
							public GS::EventSource,
							public MultiCommandDescriptorObserver,
							public CommandTreeItemList
{
	DECLARE_CLASS_INFO

	friend MenuImpl* Menu_GetImpl (Menu*);
	friend class MenuImpl;
	friend class CommandLayoutSerializer;

private:
	bool					onlyInternalUse;
	GS::UniString			serializationId;
	// attributes
	GS::UniString			title;
	GS::UniString			description;
	DG::Icon				icon;
	DG::Picture				picture;

	// relations
	GS::Array<MenuItem*>	items;

	// implementation
	MenuImpl*				impl;
	GS::Array<MenuItem*>	internalItems;
	GS::Array<MenuItem*>	displayedItems;

	void					Init	(void);
	MenuImpl*				GetImpl	(void);

	// disable copy
							Menu (const Menu& source);

	// menu item utilities
	inline static MultiCommandDescriptor*
							GetMultiCmdDesc			(const MenuItem& menuItem);
	bool					IsVisibleItem			(UIndex internalIndex) const;

	UIndex					InternalIndexToIndex	(UIndex internalIndex) const;
	UIndex					IndexToInternalIndex	(UIndex index) const;
	UIndex					InternalToDisplayIndex	(UIndex internalIndex) const;
	UIndex					DisplayToInternalIndex	(UIndex displayIndex) const;

	UIndex					InsertDisplayedItem		(UIndex internalIndex);
	void					RemoveDisplayedItem		(UIndex displayIndex);
	void					UpdateItemsVisibility	(UIndex internalIndex = MaxUIndex);

	GSErrCode				MenuItemInserted		(UIndex internalIndex);
	GSErrCode				MenuItemRemoved			(UIndex internalIndex);

	GSErrCode				InsertInternalItem		(UIndex internalIndex, const MenuItem& menuItem);
	GSErrCode				InsertInternalItem		(UIndex internalIndex, CommandDescriptor* cmdDesc);
	GSErrCode				RemoveInternalItem		(UIndex internalIndex);

	void					CheckMenuDisplayListChanged	(USize oldDisplayedListSize);

	// private interface for the bridge
	MenuItem&				GetDisplayedItem		(UIndex displayIndex) const;
	UIndex					GetDisplayedItem		(const MenuItem& menuItem) const;
	USize					GetDisplayedItemCount	(void) const;

protected:
	void			ProcessMenuDisplayedItemListChangedEvent	(const MenuDisplayedItemListEvent& ev);
	// from MultiCommandDescriptorObserver
	virtual	void	ClearItems		(const MultiCommandDescriptorClearEvent& ev) override;
	virtual	void	BuildItems		(const MultiCommandDescriptorBuildEvent& ev) override;

	// from EventObserver
	virtual	void	SourceDestroyed (GS::EventSource* source) override;

private:
	using GS::Object::Read;
	using GS::Object::Write;

public:

	// inner class definitions

	// ConstIterator
	typedef GS::Array<MenuItem*>::ConstIterator		ConstIterator;

	// CommandDescriptorIterator
	class DG_DLL_EXPORT CommandDescriptorIterator {
		friend class Menu;
	private:
		const CommandDescriptor*	commandDescriptor;
		ConstIterator*				iterator;

		inline 			CommandDescriptorIterator (const Menu* menu, const CommandDescriptor* commandDescriptor);
		inline void		MoveNext	(void);
		inline void		SetMenuIterator		(const Menu* menu);
		inline void		DeleteMenuIterator	(void);

		class DG_DLL_EXPORT X {};

	public:
		inline 			CommandDescriptorIterator (const CommandDescriptorIterator& source);
		inline 		   ~CommandDescriptorIterator ();

		inline ConstIterator&				operator*	(void) const;
		inline CommandDescriptorIterator&	operator++	(void);	// prefix
		inline bool							operator!=	(const X*) const;
		inline bool							operator==	(const X*) const;
	} ;

	// static methods
	static	Menu*		GetDummyMenu (void);

	static	GS::UniString	GetMetaName (void);

	// constructors / destructors
			 Menu (const GS::UniString& title);
			 Menu (const GS::UniString& title, const DG::Icon& icon);
			 Menu (const GS::UniString& title, const DG::Picture& picture);
	virtual ~Menu ();

	Menu*			RecursiveCopy		(void);
	Menu*			RecursiveCopyFilter	(const CommandTable& enabledCommands, bool isSticky = false, bool copyEmptySubMenus = true);
	bool			HasEnabledCommands	(const CommandTable& enabledCommands, bool isSticky = false);

	void			Attach				(GS::EventObserver& observer);
	void			Detach				(GS::EventObserver& observer);

	// accessors
	GS::UniString	GetTitle			(void) const;
	GSErrCode		SetTitle			(const GS::UniString& newTitle);
	GS::UniString	GetDescription		(void) const;
	GSErrCode		SetDescription		(const GS::UniString& newDescription);
	DG::Icon		GetIcon				(void) const;
	DG::Picture		GetPicture			(void) const;

	bool			IsEnabled			(void) const;

	bool			HasDisplayedItems	(void) const;

	// item operations
	void			AddMenuItem			(const MenuItem& menuItem);
	void			InsertMenuItem		(const ConstIterator& iterator, const MenuItem& menuItem);
	void			ReplaceMenuItem		(const ConstIterator& iterator, const MenuItem& menuItem);
	void			RemoveMenuItem		(const ConstIterator& iterator);

	virtual UIndex					GetSize		() const override;
	virtual CommandTreeItem&		operator[]	(UIndex index) override;
	virtual const CommandTreeItem&	operator[]	(UIndex index) const override;
	virtual void					RemoveItem	(UIndex index) override;
	virtual void					UnwrapItem	(UIndex index) override;

	ConstIterator	Enumerate			(const MenuItem* iterator = nullptr) const;
	ConstIterator	Begin				(void) const;
	ConstIterator	End					(void) const;

	void			GetRecursiveMenuList	(GS::Array<Menu*>*	menus);

	CommandDescriptorIterator
					GetCommandDescriptorIterator	(CommandDescriptor* commandDescriptor) const;

	void			MenuTrackEntered			();
	void			MenuTrackExited				();

	// serialization
	GSErrCode		XMLWrite			(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const;
	GSErrCode		XMLRead				(CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);

	GSErrCode		Write				(CommandLayoutSerializer* serializer, GS::OChannel& oc) const;
	GSErrCode		Read				(CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
	GSErrCode		ReadVersion1		(CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
	GSErrCode		ReadVersion2		(CommandLayoutDeserializer* deserializer, GS::IChannel& ic, const GS::InputFrame& frame);

};


// --- Class definitions -------------------------------------------------------

// --- Menu::CommandDescriptorIterator -----------------------------------------

inline Menu::CommandDescriptorIterator::CommandDescriptorIterator (const Menu* menu, const CommandDescriptor* commandDescriptor)
{
	iterator = nullptr;
	this->commandDescriptor = commandDescriptor;

	SetMenuIterator (menu);
	MoveNext ();
}


inline void	Menu::CommandDescriptorIterator::MoveNext (void)
{
	Menu::ConstIterator& menuItemIterator = *iterator;
	while (menuItemIterator != nullptr) {
		MenuSimpleItem* simpleItem = dynamic_cast<MenuSimpleItem*> (*menuItemIterator);
		if (simpleItem != nullptr && simpleItem->GetCmdDesc () == commandDescriptor) {
			// found!
			return;
		}
		++menuItemIterator;
	}
	DeleteMenuIterator ();
}


inline void	Menu::CommandDescriptorIterator::SetMenuIterator (const Menu* menu)
{
	DeleteMenuIterator ();
	try {
		iterator = new ConstIterator (menu->Begin ());
	} catch (...) {
		delete iterator;
		throw;
	}
}


inline void	Menu::CommandDescriptorIterator::DeleteMenuIterator (void)
{
	delete iterator;
	iterator = nullptr;
}


inline Menu::CommandDescriptorIterator::CommandDescriptorIterator (const CommandDescriptorIterator& source)
{
	iterator = new ConstIterator (*source.iterator);
	commandDescriptor = source.commandDescriptor;
}


inline Menu::CommandDescriptorIterator::~CommandDescriptorIterator ()
{
	delete iterator;
}


inline Menu::ConstIterator&	Menu::CommandDescriptorIterator::operator* (void) const
{
	if (operator== (nullptr))
		throw GS::IllegalArgumentException ("Error: Menu::CommandDescriptorIterator illegal reference", __FILE__, __LINE__);

	return *iterator;
}


inline Menu::CommandDescriptorIterator&	Menu::CommandDescriptorIterator::operator++ (void)
{
	if (operator== (nullptr))
		throw GS::IllegalArgumentException ("Error: Menu::CommandDescriptorIterator illegal increment", __FILE__, __LINE__);

	++(*iterator);
	MoveNext ();

	return *this;
}


inline bool	Menu::CommandDescriptorIterator::operator!=	(const X*) const
{
	return (iterator != nullptr);
}


inline bool	Menu::CommandDescriptorIterator::operator==	(const X*) const
{
	return (iterator == nullptr);
}

}	// namespace DG


namespace DG {

// --- ContextMenu -------------------------------------------------------------

class DG_DLL_EXPORT ContextMenu		:	public GS::Object,
										public GS::EventObserver
{
	DECLARE_CLASS_INFO

private:
	// attributes
	Menu*				menu;
	GS::UniString		id;
	GS::UniString		name;
	GS::UniString		description;
	DG::CommandTable	enabledCommands;

	// implementation
	ContextMenuImpl*	impl;

	void				Init	(void);

	ContextMenu (const ContextMenu& source);	//disabled

protected:
	virtual		void	SourceDestroyed (GS::EventSource* source) override;

private:
	using GS::Object::Read;
	using GS::Object::Write;

public:

	// static methods
	static		GS::UniString	GetMetaName (void);

	// constructors / destructors
	ContextMenu (const GS::UniString& id);
	ContextMenu (const GS::UniString& id, const GS::UniString& name);
	ContextMenu (const GS::UniString& id, Menu* menu);
	ContextMenu (const GS::UniString& id, const GS::UniString& name, Menu* menu);
   ~ContextMenu ();

	// accessors
	GS::UniString	GetId			(void) const;
	GS::UniString	GetName			(void) const;
	void			SetName			(const GS::UniString& name);
	GS::UniString	GetDescription	(void) const;
	void			SetDescription	(const GS::UniString& description);
	Menu*			GetMenu			(void);

	const DG::CommandTable&		GetEnabledCommands (void) const;
	void						SetEnabledCommands (const DG::CommandTable& enabledCommands);

	// display
	DG::CommandEvent*			Display	(const DG::NativePoint& position, bool isSticky = false);
	void                        FillContextMenuTable (Menu* copiedMenu, Int8* allItemNumber, short* entryCount, Int8* outBuf, short itemCount, short itemLevel);

	// item operators
	void						GetRecursiveMenuList	(GS::Array<Menu*>*	menus);

	// serialization
	GSErrCode		XMLWrite	(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const;
	GSErrCode		XMLRead		(CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);

	GSErrCode		Write		(CommandLayoutSerializer* serializer, GS::OChannel& oc) const;
	GSErrCode		Read		(CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
	GSErrCode		ReadVersion1(CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
	GSErrCode		ReadVersion2(CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
};

}	// namespace DG

#endif
