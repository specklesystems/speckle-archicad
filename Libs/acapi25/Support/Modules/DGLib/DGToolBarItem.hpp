// *****************************************************************************
// File:			DGToolBarItem.hpp
//
// Description:		ToolBar item related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA, BL, MD
//
// SG compatible
// *****************************************************************************

#ifndef DGTOOLBARITEM_HPP
#define DGTOOLBARITEM_HPP

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
	class ToolBar;
	class ToolBarItemImpl;
	class CommandLayoutSerializer;
	class CommandLayoutDeserializer;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- ToolBarItem -------------------------------------------------------------

class DG_DLL_EXPORT ToolBarItem : public GS::Object, public CommandTreeItem
{
	friend	ToolBarItemImpl* ToolBarItem_GetImpl (ToolBarItem&);
	friend class ToolBar;

private:
	// relations
	ToolBar*			parentToolBar;

	void				SetParentToolBar	(ToolBar* toolBar);

protected:
	// implementation
	ToolBarItemImpl*		impl;

	ToolBarItemImpl*		GetImpl			(void) { return impl; };

	// construction
	ToolBarItem ();
	ToolBarItem (const ToolBarItem& source);

public:
	using GS::Object::Write;

#if defined(__GNUC__)
	virtual				~ToolBarItem ();
#endif

	virtual ToolBarItem*	Clone			(void) const override = 0;

	// accessors
	virtual bool		IsEnabled			(void) const = 0;
	virtual bool		IsChecked			(void) const = 0;

	virtual GS::UniString	GetText				(void) const = 0;
	virtual DG::Icon	GetIcon				(void) const = 0;
	virtual DG::Picture	GetPicture			(void) const = 0;
	virtual ULong		GetOSCommandId		(void) const = 0;

			ToolBar*	GetParentToolBar	(void) const;

	virtual Menu* GetMenu () const = 0;

	// serialization
	virtual GSErrCode	XMLWrite			(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const = 0;
	virtual	GSErrCode	Write				(CommandLayoutSerializer* serializer, GS::OChannel& oc) const = 0;
};


// --- ToolBarButton -----------------------------------------------------------

class DG_DLL_EXPORT ToolBarButton :	public ToolBarItem,
									public CommandDescriptorObserver
{
	DECLARE_CLASS_INFO

public:
	enum Mode {
		SelectiveText,
		NotSelectiveText
	};

private:
	// attributes
	DG::Command					command;
	mutable CommandDescriptor*	cmdDescCache;
	Mode						mode;
	bool						hasDeletedCmdDesc;

	// constructors
	ToolBarButton ();

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
	static	GS::UniString	GetMetaName			(void);
	static	GS::UniString	GetDummyMetaName	(void);

	// constructors / destructors
				ToolBarButton (CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);
				ToolBarButton (CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
				ToolBarButton (const Command& cmd);
				ToolBarButton (const Command& cmd, Mode mode);
				ToolBarButton (const ToolBarButton& source);
	virtual	   ~ToolBarButton ();

	virtual	ToolBarButton*		Clone (void) const override;

	// accessors
	virtual bool		IsEnabled			(void) const override;
	virtual bool		IsChecked			(void) const override;

	virtual GS::UniString	GetText				(void) const override;
	virtual DG::Icon	GetIcon				(void) const override;
	virtual DG::Picture	GetPicture			(void) const override;
	virtual ULong		GetOSCommandId		(void) const override;

	Mode				GetMode				(void) const;
	void				SetMode				(Mode mode);

	bool				CanBeWithPopupItem	(void) const;

	virtual Menu*		GetMenu				() const override;

	virtual Command					GetCommand		() const override;
	virtual CommandDescriptor*		GetCmdDesc		() const override;
	virtual bool					IsSeparator		() const override;
	virtual bool					IsDynamic		() const override;
	virtual bool					CanHaveSubItems	() const override;
	virtual CommandTreeItemList*	GetSubItems		() override;

	// serialization
	virtual GSErrCode	XMLWrite			(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const override;
	virtual	GSErrCode	Write				(CommandLayoutSerializer* serializer, GS::OChannel& oc) const override;
};


// --- ToolBarPopupItem --------------------------------------------------------

class DG_DLL_EXPORT ToolBarPopupItem :	public ToolBarItem,
										public GS::EventObserver
{
	DECLARE_CLASS_INFO

private:
	// attributes
	Menu*			menu;
	bool			sticky;				// if true, it tries to build into the prev. button

	// constructor
//	ToolBarPopupItem ();

protected:
	virtual		void		SourceDestroyed (GS::EventSource* source) override;

public:
	// static methods
	static	GS::UniString	GetMetaName			(void);
	static	GS::UniString	GetDummyMetaName	(void);

	// constructors / destructors
				ToolBarPopupItem (CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);
				ToolBarPopupItem (CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
				ToolBarPopupItem (Menu* menu, bool sticky = false);
				ToolBarPopupItem (const ToolBarPopupItem& source);
	virtual	   ~ToolBarPopupItem ();

	virtual	ToolBarPopupItem*		Clone (void) const override;

	// accessors
	virtual bool		IsEnabled			(void) const override;
	virtual bool		IsChecked			(void) const override;

	virtual GS::UniString	GetText				(void) const override;
	virtual DG::Icon	GetIcon				(void) const override;
	virtual DG::Picture	GetPicture			(void) const override;
	virtual ULong		GetOSCommandId		(void) const override;

	bool				IsSticky			(void) const;

	bool				CanBeWithButton		(void) const;

	virtual Menu* GetMenu () const override;

	virtual Command					GetCommand		() const override;
	virtual CommandDescriptor*		GetCmdDesc		() const override;
	virtual bool					IsSeparator		() const override;
	virtual bool					IsDynamic		() const override;
	virtual bool					CanHaveSubItems	() const override;
	virtual CommandTreeItemList*	GetSubItems		() override;

	// serialization
	virtual GSErrCode	XMLWrite			(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const override;
	virtual	GSErrCode	Write				(CommandLayoutSerializer* serializer, GS::OChannel& oc) const override;
};


// --- ToolBarSeparatorItem ----------------------------------------------------

class DG_DLL_EXPORT ToolBarSeparatorItem :	public ToolBarItem
{
	DECLARE_CLASS_INFO

private:

public:
	// static methods
	static	GS::UniString	GetMetaName (void);

	// constructors / destructors
				ToolBarSeparatorItem (CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);
				ToolBarSeparatorItem (CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
				ToolBarSeparatorItem ();
				ToolBarSeparatorItem (const ToolBarSeparatorItem& source);
	virtual	   ~ToolBarSeparatorItem ();

	virtual	ToolBarSeparatorItem*		Clone (void) const override;

	// accessors
	virtual bool		IsEnabled			(void) const override;
	virtual bool		IsChecked			(void) const override;

	virtual GS::UniString	GetText				(void) const override;
	virtual DG::Icon	GetIcon				(void) const override;
	virtual DG::Picture	GetPicture			(void) const override;
	virtual ULong		GetOSCommandId		(void) const override;

	virtual Menu*	GetMenu				() const override;

	virtual Command					GetCommand		() const override;
	virtual CommandDescriptor*		GetCmdDesc		() const override;
	virtual bool					IsSeparator		() const override;
	virtual bool					IsDynamic		() const override;
	virtual bool					CanHaveSubItems	() const override;
	virtual CommandTreeItemList*	GetSubItems		() override;

	// serialization
	virtual GSErrCode	XMLWrite			(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const override;
	virtual	GSErrCode	Write				(CommandLayoutSerializer* serializer, GS::OChannel& oc) const override;
};

}	// namespace DG

#endif
