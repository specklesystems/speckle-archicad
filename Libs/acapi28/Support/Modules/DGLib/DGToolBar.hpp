// *****************************************************************************
// File:			DGToolBar.hpp
//
// Description:		Toolbar related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA, BL, MD
//
// SG compatible
// *****************************************************************************

#ifndef DGTOOLBAR_HPP
#define DGTOOLBAR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Object.hpp"

#include "Array.hpp"
#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"

#include "DG.h"
#include "DGUtility.hpp"
#include "DGToolBarItem.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace xercesc_3_0 {
	class DOMElement;
}
namespace xercesc = xercesc_3_0;

namespace DG {
	class Menu;
	class ToolBar;
	class ToolBarImpl;
	class ToolBarItem;
	class CommandDescriptor;
	class CommandLayoutSerializer;
	class CommandLayoutDeserializer;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- ToolBarEvent ------------------------------------------------------------

class DG_DLL_EXPORT ToolBarEvent :	public GS::Event
{
protected:
	explicit ToolBarEvent (ToolBar* source);

public:
	virtual ~ToolBarEvent ();

	ToolBar*	GetSource (void) const;
};


// --- ToolBarCloseEvent -------------------------------------------------------

class DG_DLL_EXPORT ToolBarCloseEvent :		public ToolBarEvent
{
	friend class ToolBar;			// To access protected constructor

protected:
	explicit ToolBarCloseEvent (ToolBar* source);

public:
	virtual ~ToolBarCloseEvent ();
};


// --- ToolBarCloseRequestEvent ------------------------------------------------

class DG_DLL_EXPORT ToolBarCloseRequestEvent :		public ToolBarEvent
{
	friend class ToolBar;			// To access protected constructor

protected:
	explicit ToolBarCloseRequestEvent (ToolBar* source);

public:
	virtual ~ToolBarCloseRequestEvent ();
};


// --- ToolBarContextMenuEvent -------------------------------------------------

class DG_DLL_EXPORT ToolBarContextMenuEvent :		public ToolBarEvent
{
	friend class ToolBar;			// To access protected constructor

private:
	NativePoint			position;
	CommandDescriptor*	cmdDesc;

protected:
	ToolBarContextMenuEvent (ToolBar* source, NativePoint position, CommandDescriptor* cmdDesc);

public:
	virtual ~ToolBarContextMenuEvent ();

	NativePoint					GetPosition (void) const;
	const CommandDescriptor*	GetCmdDescriptor (void) const;
};


// --- ToolBarObserver ---------------------------------------------------------

class DG_DLL_EXPORT ToolBarObserver :	public GS::EventObserver
{
	friend class ToolBar;

protected:
	virtual void	ToolBarClosed			(const ToolBarCloseEvent& ev);
	virtual	void	ToolBarCloseRequested	(const ToolBarCloseRequestEvent& ev, bool* accepted);
	virtual	void	ContextMenuRequested	(const ToolBarContextMenuEvent& ev);

public:
	ToolBarObserver ();
   ~ToolBarObserver ();
};


// --- ToolBar -----------------------------------------------------------------

class DG_DLL_EXPORT ToolBar :	public GS::Object,
								public GS::EventSource,
								public GS::EventObserver,
								public CommandTreeItemList
{
	DECLARE_CLASS_INFO

	friend	ToolBarImpl*	ToolBar_GetImpl (ToolBar*);
	friend	short			ToolBar_CloseRequest (ToolBar*);
	friend	short			ToolBar_Close (ToolBar*);
	friend	void			ToolBar_ContextMenuRequested (ToolBar*, NativePoint, CommandDescriptor* cmdDesc);

	friend	class ToolBarImpl;

public:
	// enumerations
	enum Mode {
		ShowText,
		ShowIcon,
		ShowIconAndText,
		SelectiveText
	};

	enum Layout {
		Vertical,
		Horizontal
	};

private:
	virtual ToolBar*	Clone			(void) const  override { DBBREAK (); return nullptr; }

	GS::UniString					serializationId;

	// attributes
	static bool						shortcutInToolTip;
	GS::Guid						guid;
	GS::UniString					title;
	GS::UniString					description;
	Mode							mode;
	bool							visible;

	// relations
	GS::Array<ToolBarItem*>			items;

	// implementation
	ToolBarImpl*					impl;
	GS::Array<ToolBarItem*>			internalItems;
	GS::Array<ToolBarItem*>			displayedItems;

	void			Init					(void);
	ToolBarImpl*	GetImpl					(void);

	// observer notifications
	short			ProcessCloseEvent			(void);
	short			ProcessCloseRequestEvent	(void);
	void			ProcessContextMenuEvent		(NativePoint position, CommandDescriptor* cmdDesc);

	// disable copy
					ToolBar					(const ToolBar& source);

	//toolbar item utilities
	inline static MultiCommandDescriptor*
							GetMultiCmdDesc			(const ToolBarItem& toolBarItem);
	bool					IsVisibleItem			(UIndex internalIndex) const;

	UIndex					InternalIndexToIndex	(UIndex internalIndex) const;
	UIndex					IndexToInternalIndex	(UIndex index) const;
	UIndex					InternalToDisplayIndex	(UIndex internalIndex) const;
	UIndex					DisplayToInternalIndex	(UIndex displayIndex) const;

	UIndex					InsertDisplayedItem		(UIndex internalIndex);
	void					RemoveDisplayedItem		(UIndex displayIndex);
	void					UpdateItemsVisibility	(UIndex internalIndex = MaxUIndex);

	GSErrCode				BeforeToolBarItemInsert	(UIndex internalIndex);
	GSErrCode				AfterToolBarItemInsert	(UIndex internalIndex);
	GSErrCode				BeforeToolBarItemRemove	(UIndex internalIndex);
	GSErrCode				AfterToolBarItemRemove	(UIndex internalIndex);

	GSErrCode				ToolBarItemInserted		(UIndex internalIndex);
	GSErrCode				ToolBarItemRemoved		(UIndex internalIndex);

	GSErrCode				InsertInternalItem		(UIndex internalIndex, const ToolBarItem& toolBarItem);
	GSErrCode				RemoveInternalItem		(UIndex internalIndex);

	// private interface for the bridge
	ToolBarItem&	GetDisplayedItem			(UIndex index) const;
	UIndex			GetDisplayedItem			(const ToolBarItem& toolBarItem) const;
	USize			GetDisplayedItemCount		(void) const;

protected:
	// from EventObserver
	virtual	void	SourceDestroyed (GS::EventSource* source) override;

private:
	using GS::Object::Read;
	using GS::Object::Write;

public:

	// inner class definitions

	// ConstIterator
	typedef GS::Array<ToolBarItem*>::ConstIterator	ConstIterator;

	// CommandDescriptorIterator
	class DG_DLL_EXPORT CommandDescriptorIterator {
		friend class ToolBar;
	private:
		const CommandDescriptor*	commandDescriptor;
		ConstIterator*				iterator;

		inline 			CommandDescriptorIterator (const ToolBar* toolBar, const CommandDescriptor* commandDescriptor);
		inline void		MoveNext				(void);
		inline void		SetToolBarIterator		(const ToolBar* toolBar);
		inline void		DeleteToolBarIterator	(void);

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
	static bool		ShortcutInTooltip		(void);
	static void		SetShortcutInTooltip	(bool show);

	static GS::UniString	GetMetaName	(void);

	// constructors / destructors
				ToolBar	(const GS::Guid& guid);
				ToolBar	(const GS::Guid& guid, const GS::UniString& title);
				ToolBar	(const GS::Guid& guid, const GS::UniString& title, Mode mode);
	virtual	   ~ToolBar ();

	void		Attach (ToolBarObserver& observer);
	void		Detach (ToolBarObserver& observer);

	GSErrCode		Show					(void);
	GSErrCode		Hide					(void);
	GSErrCode		SetVisibility			(bool visible);
	bool			IsVisible				(void) const;

	// accessors
	const GS::Guid&	GetGuid					(void) const;
	GS::UniString	GetId					(void) const;
	GS::UniString	GetTitle				(void) const;
	void			SetTitle				(const GS::UniString& title);
	GS::UniString	GetDescription			(void) const;
	void			SetDescription			(const GS::UniString& description);
	Mode			GetMode					(void) const;
	void			SetMode					(Mode mode);
	void			SetLayout				(Layout layout);
	NativeRect		GetRectangle			(void) const;
	NativePoint		GetPosition				(void) const;
	void			SetPosition				(const NativePoint& point);
	void			GetSize					(NativeUnit& width, NativeUnit& height) const;
	void			SetSize					(const NativeUnit& width, const NativeUnit& height);

	Int32			GetDeveloperId			(void) const;
	Int32			GetLocalId				(void) const;

	// item operations
	void			AddToolBarItem			(const ToolBarItem& toolBarItem);
	void			InsertToolBarItem		(const ConstIterator& iterator, const ToolBarItem& toolBarItem);
	void			ReplaceToolBarItem		(const ConstIterator& iterator, const ToolBarItem& toolBarItem);
	void			RemoveToolBarItem		(const ConstIterator& iterator);

	ConstIterator	Enumerate				(const ToolBarItem* item = nullptr) const;
	ConstIterator	Begin					(void) const;
	ConstIterator	End						(void) const;

	virtual UIndex					GetSize		() const override;
	virtual CommandTreeItem&		operator[]	(UIndex index) override;
	virtual const CommandTreeItem&	operator[]	(UIndex index) const override;
	virtual void					RemoveItem	(UIndex index) override;
	virtual void					UnwrapItem	(UIndex index) override;

	void			GetRecursiveMenuList	(GS::Array<Menu*>*	menus);

	CommandDescriptorIterator
					GetCommandDescriptorIterator	(CommandDescriptor* commandDescriptor) const;

	// serialization
	GSErrCode		XMLWrite				(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const;
	GSErrCode		XMLRead					(CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);

	GSErrCode		Write					(CommandLayoutSerializer* serializer, GS::OChannel& oc) const;
	GSErrCode		Read					(CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
	GSErrCode		ReadVersion1			(CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
	GSErrCode		ReadVersion2			(CommandLayoutDeserializer* deserializer, GS::IChannel& ic, const GS::InputFrame& frame);
};

// --- Class definitions -------------------------------------------------------

// --- ToolBar::CommandDescriptorIterator --------------------------------------

inline ToolBar::CommandDescriptorIterator::CommandDescriptorIterator (const ToolBar* toolBar, const CommandDescriptor* commandDescriptor)
{
	iterator = nullptr;
	this->commandDescriptor = commandDescriptor;

	SetToolBarIterator (toolBar);
	MoveNext ();
}


inline void	ToolBar::CommandDescriptorIterator::MoveNext (void)
{
	ToolBar::ConstIterator& toolBarItemIterator = *iterator;
	while (toolBarItemIterator != nullptr) {
		ToolBarButton* button = dynamic_cast<ToolBarButton*> (*toolBarItemIterator);
		if (button != nullptr && button->GetCmdDesc () == commandDescriptor) {
			// found!
			return;
		}
		++toolBarItemIterator;
	}
	DeleteToolBarIterator ();
}


inline void	ToolBar::CommandDescriptorIterator::SetToolBarIterator (const ToolBar* toolBar)
{
	DeleteToolBarIterator ();
	try {
		iterator = new ConstIterator (toolBar->Begin ());
	} catch (...) {
		delete iterator;
		throw;
	}
}


inline void	ToolBar::CommandDescriptorIterator::DeleteToolBarIterator (void)
{
	delete iterator;
	iterator = nullptr;
}


inline ToolBar::CommandDescriptorIterator::CommandDescriptorIterator (const CommandDescriptorIterator& source)
{
	iterator = new ConstIterator (*source.iterator);
	commandDescriptor = source.commandDescriptor;
}


inline ToolBar::CommandDescriptorIterator::~CommandDescriptorIterator ()
{
	delete iterator;
}


inline ToolBar::ConstIterator&	ToolBar::CommandDescriptorIterator::operator* (void) const
{
	if (operator== (nullptr))
		throw GS::IllegalArgumentException ("Error: ToolBar::CommandDescriptorIterator illegal reference", __FILE__, __LINE__);

	return *iterator;
}


inline ToolBar::CommandDescriptorIterator&	ToolBar::CommandDescriptorIterator::operator++ (void)
{
	if (operator== (nullptr))
		throw GS::IllegalArgumentException ("Error: ToolBar::CommandDescriptorIterator illegal increment", __FILE__, __LINE__);

	++(*iterator);
	MoveNext ();

	return *this;
}


inline bool	ToolBar::CommandDescriptorIterator::operator!=	(const X*) const
{
	return (iterator != nullptr);
}


inline bool	ToolBar::CommandDescriptorIterator::operator==	(const X*) const
{
	return (iterator == nullptr);
}

}	// namespace DG

#endif
