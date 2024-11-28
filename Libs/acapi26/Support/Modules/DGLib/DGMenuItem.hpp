// *****************************************************************************
// File:			DGMenuItem.hpp
//
// Description:		Menu item related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA, BL, MD
//
// SG compatible
// *****************************************************************************

#ifndef DGMENUITEM_HPP
#define DGMENUITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Object.hpp"

#include "Event.hpp"
#include "EventObserver.hpp"

#include "DG.h"
#include "DGUtility.hpp"
#include "DGCommandDescriptor.hpp"
#include "DGCommandTree.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace xercesc_3_0 {
	class DOMElement;
}
namespace xercesc = xercesc_3_0;

namespace DG {
	class Menu;
	class MenuItemImpl;
	class ModifierKey;
	class CommandLayoutSerializer;
	class CommandLayoutDeserializer;
	class ToolBarItem;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- MenuItem ----------------------------------------------------------------

class DG_DLL_EXPORT MenuItem : public GS::Object, public CommandTreeItem
{
	friend	MenuItemImpl* MenuItem_GetImpl (MenuItem&);
	friend class Menu;

private:
	// relations
	Menu*				parentMenu;

	void				SetParentMenu	(Menu* menu);

protected:
	// implementation
	MenuItemImpl*		impl;

	MenuItemImpl*		GetImpl			(void) { return impl; };

	// constructors
	MenuItem ();
	MenuItem (const MenuItem& source);

public:
	using GS::Object::Write;

	virtual				~MenuItem ();

	virtual MenuItem*	Clone			(void) const override = 0;

	virtual	bool		IsBaseMenuItem	(void) const = 0;
	virtual	bool		IsAlternateItem	(void) const = 0;

	virtual bool		IsEnabled		(void) const = 0;
	virtual bool		IsChecked		(void) const = 0;

	virtual GS::UniString	GetText			(void) const = 0;
	virtual GS::UniString	GetDescription	(void) const = 0;
	virtual DG::Icon	GetIcon			(void) const = 0;
	virtual DG::Picture	GetPicture		(void) const = 0;
	virtual ULong		GetOSCommandId	(void) const = 0;
	virtual ULong		GetModifierFlag	(void) const = 0;

	virtual GSErrCode	XMLWrite		(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const = 0;
	virtual	GSErrCode	Write			(CommandLayoutSerializer* serializer, GS::OChannel& oc) const = 0;

			Menu*		GetParentMenu	(void) const;

	virtual Menu*		GetMenu () const = 0;
	
	virtual GS::Owner<ToolBarItem>	ToToolBarItem () const = 0;
};


// --- MenuSimpleItem ----------------------------------------------------------

class DG_DLL_EXPORT MenuSimpleItem :	public MenuItem,
										public CommandDescriptorObserver
{
	DECLARE_CLASS_INFO

private:
	// attributes
	DG::Command					command;
	mutable CommandDescriptor*	cmdDescCache;
	bool						dynamic;

	// construction
	MenuSimpleItem ();

	// utility functions
	MenuSimpleItem*	CanBeAlternateOfPrevious (void) const;

protected:
	// CommandDescriptorObserver methods
	virtual	void	CheckChanged		(const CommandDescriptorCheckEvent& ev) override;
	virtual	void	EnableChanged		(const CommandDescriptorEnableEvent& ev) override;
	virtual	void	TextChanged			(const CommandDescriptorTextEvent& ev) override;
	virtual	void	DescChanged			(const CommandDescriptorDescEvent& ev) override;
	virtual	void	IconChanged			(const CommandDescriptorIconEvent& ev) override;
	virtual	void	ShortcutAdded		(const CommandDescriptorShortcutEvent& ev) override;
	virtual	void	ShortcutRemoving	(const CommandDescriptorShortcutEvent& ev) override;
	virtual	void	CmdDescDeleting		(const CommandDescriptorDeleteEvent& ev) override;

public:
	// static methods
	static		GS::UniString	GetMetaName			(void);
	static		GS::UniString	GetDummyMetaName	(void);

	// constructors / destructors
				MenuSimpleItem (CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);
				MenuSimpleItem (CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
				MenuSimpleItem (const Command& cmd);
				MenuSimpleItem (const Command& cmd, bool dynamic);
				MenuSimpleItem (CommandDescriptor* cmdDesc);
				MenuSimpleItem (const MenuSimpleItem& source);
	virtual	   ~MenuSimpleItem ();

	virtual	MenuSimpleItem*		Clone (void) const override;

	// accessors
	virtual Command		GetCommand		() const override;

	virtual	bool		IsBaseMenuItem	(void) const override;
	virtual	bool		IsAlternateItem	(void) const override;
	virtual bool		IsEnabled		(void) const override;
	virtual bool		IsChecked		(void) const override;
	virtual GS::UniString	GetText			(void) const override;
	virtual GS::UniString	GetDescription	(void) const override;
	virtual DG::Icon	GetIcon			(void) const override;
	virtual DG::Picture	GetPicture		(void) const override;
	virtual ULong		GetOSCommandId	(void) const override;
	virtual ULong		GetModifierFlag	(void) const override;

	virtual Menu* GetMenu () const override;

	virtual CommandDescriptor*		GetCmdDesc		() const override;
	virtual bool					IsSeparator		() const override;
	virtual bool					IsDynamic		() const override;
	virtual bool					CanHaveSubItems	() const override;
	virtual CommandTreeItemList*	GetSubItems		() override;

	virtual GS::Owner<ToolBarItem>	ToToolBarItem () const override;

	ULong				GetFirstShortcutModifiers	(void) const;
	Key::Code			GetFirstShortcutKey			(void) const;
	GS::UniString			GetFirstShortcutDisplayText	(void) const;

	// serialization
	virtual GSErrCode	XMLWrite		(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const override;
	virtual	GSErrCode	Write			(CommandLayoutSerializer* serializer, GS::OChannel& oc) const override;
};


// --- MenuPopupItem ----------------------------------------------------------

class DG_DLL_EXPORT MenuPopupItem	:	public MenuItem,
										public GS::EventObserver
{
	DECLARE_CLASS_INFO

private:
	// attributes
	Menu*		menu;

protected:
	virtual		void	SourceDestroyed (GS::EventSource* source) override;

public:
	// static methods
	static		GS::UniString	GetMetaName			(void);
	static		GS::UniString	GetDummyMetaName	(void);

	// constructors / destructors
				MenuPopupItem (CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);
				MenuPopupItem (CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
				MenuPopupItem (Menu* menu);
				MenuPopupItem (const MenuPopupItem& source);
	virtual    ~MenuPopupItem ();


	virtual	MenuPopupItem*		Clone (void) const override;

	// accessors
	virtual	bool		IsBaseMenuItem	(void) const override;
	virtual	bool		IsAlternateItem	(void) const override;
	virtual bool		IsEnabled		(void) const override;
	virtual bool		IsChecked		(void) const override;
	virtual GS::UniString	GetText			(void) const override;
	virtual GS::UniString	GetDescription	(void) const override;
	virtual DG::Icon	GetIcon			(void) const override;
	virtual DG::Picture	GetPicture		(void) const override;
	virtual ULong		GetOSCommandId	(void) const override;
	virtual ULong		GetModifierFlag	(void) const override;

	virtual Menu* GetMenu () const override;

	virtual Command					GetCommand		() const override;
	virtual CommandDescriptor*		GetCmdDesc		() const override;
	virtual bool					IsSeparator		() const override;
	virtual bool					IsDynamic		() const override;
	virtual bool					CanHaveSubItems	() const override;
	virtual CommandTreeItemList*	GetSubItems		() override;

	virtual GS::Owner<ToolBarItem>	ToToolBarItem () const override;

	// serialization
	virtual GSErrCode	XMLWrite		(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const override;
	virtual	GSErrCode	Write			(CommandLayoutSerializer* serializer, GS::OChannel& oc) const override;
};


// --- MenuSeparatorItem -------------------------------------------------------

class DG_DLL_EXPORT MenuSeparatorItem : public MenuItem
{
	DECLARE_CLASS_INFO

public:
	// static methods
	static		GS::UniString	GetMetaName (void);

	// constructors / destructors
				MenuSeparatorItem (CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);
				MenuSeparatorItem (CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
				MenuSeparatorItem ();
				MenuSeparatorItem (const MenuSeparatorItem& source);
	virtual	   ~MenuSeparatorItem ();

	virtual	MenuSeparatorItem*		Clone (void) const override;

	// accessors
	virtual	bool		IsBaseMenuItem	(void) const override;
	virtual	bool		IsAlternateItem	(void) const override;
	virtual bool		IsEnabled		(void) const override;
	virtual bool		IsChecked		(void) const override;
	virtual GS::UniString	GetText			(void) const override;
	virtual GS::UniString	GetDescription	(void) const override;
	virtual DG::Icon	GetIcon			(void) const override;
	virtual DG::Picture	GetPicture		(void) const override;
	virtual ULong		GetOSCommandId	(void) const override;
	virtual ULong		GetModifierFlag	(void) const override;

	virtual Menu* GetMenu () const override;

	virtual Command					GetCommand		() const override;
	virtual CommandDescriptor*		GetCmdDesc		() const override;
	virtual bool					IsSeparator		() const override;
	virtual bool					IsDynamic		() const override;
	virtual bool					CanHaveSubItems	() const override;
	virtual CommandTreeItemList*	GetSubItems		() override;

	virtual GS::Owner<ToolBarItem>	ToToolBarItem	() const override;

	// serialization
	virtual GSErrCode	XMLWrite		(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const override;
	virtual	GSErrCode	Write			(CommandLayoutSerializer* serializer, GS::OChannel& oc) const override;
};

}	// namespace DG

#endif
