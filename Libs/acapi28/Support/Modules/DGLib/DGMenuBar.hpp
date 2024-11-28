// *****************************************************************************
// File:			DGMenuBar.hpp
//
// Description:		Menu bar related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA, BL, MD
//
// SG compatible
// *****************************************************************************

#ifndef DGMENUBAR_HPP
#define DGMENUBAR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Object.hpp"

#include "DG.h"
#include "Array.hpp"
#include "Event.hpp"
#include "EventObserver.hpp"

#include "DGMenu.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace xercesc_3_0 {
	class DOMElement;
}
namespace xercesc = xercesc_3_0;

namespace DG {
	class MenuBarImpl;
	class MenuImpl;
	class CommandLayoutSerializer;
	class CommandLayoutDeserializer;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- MenuBar -----------------------------------------------------------------

class DG_DLL_EXPORT MenuBar		:	public GS::Object,
									public DG::MenuObserver
{
	DECLARE_CLASS_INFO

	friend MenuBarImpl* MenuBar_GetImpl (MenuBar*);
	friend class MenuBarImpl;

private:
	GS::UniString			serializationId;

	//attributes
	GS::Guid				guid;
	GS::UniString			name;
	GS::UniString			description;

	//relations
	GS::Array<Menu*>		items;

	//implementation
	MenuBarImpl*			impl;
	GS::Array<Menu*>		displayedItems;

	void					Init	(void);
	MenuBarImpl*			GetImpl	(void);

	// menubar item utilities
	bool					IsVisibleItem	(UIndex index) const;

	UIndex					IndexToDisplayIndex		(UIndex index) const;
	UIndex					DisplayIndexToIndex		(UIndex displayIndex) const;

	UIndex					InsertDisplayedItem		(UIndex index);
	void					RemoveDisplayedItem		(UIndex displayIndex);

	GSErrCode				ItemInserted	(UIndex index);
	GSErrCode				ItemRemoved		(UIndex index);

	// private interface for the bridge
	Menu*					GetDisplayedItem		(UIndex displayIndex) const;
	USize					GetDisplayedItemCount	(void) const;

protected:
	virtual		void	MenuDisplayedListChanged	(const MenuDisplayedItemListEvent& ev) override;
	virtual		void	SourceDestroyed				(GS::EventSource* source) override;

private:
	using GS::Object::Read;
	using GS::Object::Write;

public:

	// inner class definitions

	// ConstIterator
	typedef GS::Array<Menu*>::ConstIterator		ConstIterator;

	// static methods
	static	GS::UniString	GetMetaName (void);

	// constructors / destructors
			 MenuBar	(const GS::Guid& guid);
			 MenuBar	(const GS::Guid& guid, const GS::UniString& name);
			 MenuBar	(const MenuBar& source);
	virtual ~MenuBar	();

	// accessors
	GS::Guid		GetGuid			(void) const;
	GS::UniString	GetName			(void) const;
	void			SetName			(const GS::UniString& name);
	GS::UniString	GetDescription	(void) const;
	void			SetDescription	(const GS::UniString& description);

	// item operations
	void			AddMenu			(Menu* menu);
	void			InsertMenu		(const ConstIterator& iterator, Menu* menu);
	void			ReplaceMenu		(const ConstIterator& iterator, Menu* menu);
	void			RemoveMenu		(const ConstIterator& iterator);

	ConstIterator	Enumerate		(const Menu* iterator = nullptr) const;
	ConstIterator	Begin			(void) const;
	ConstIterator	End				(void) const;

	void		GetRecursiveMenuList	(GS::Array<Menu*>*	menus);

	// serialization
	GSErrCode	XMLWrite		(CommandLayoutSerializer* serializer, xercesc::DOMElement* parent, int level) const;
	GSErrCode	XMLRead			(CommandLayoutDeserializer* deserializer, const xercesc::DOMElement* parent);

	GSErrCode	Write			(CommandLayoutSerializer* serializer, GS::OChannel& oc) const;
	GSErrCode	Read			(CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
	GSErrCode	ReadVersion1	(CommandLayoutDeserializer* deserializer, GS::IChannel& ic);
	GSErrCode	ReadVersion2	(CommandLayoutDeserializer* deserializer, GS::IChannel& ic, const GS::InputFrame& frame);
};

}	// namespace DG

#endif
