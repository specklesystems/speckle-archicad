// *****************************************************************************
// File:			DGCommandLayoutSerializer.hpp
//
// Description:		Command layout helper class
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA
//
// SG compatible
// *****************************************************************************

#ifndef DGCOMMANDLAYOUTSERIALIZER_HPP
#define DGCOMMANDLAYOUTSERIALIZER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSGuid.hpp"
#include "UniString.hpp"

#include "DG.h"
#include "DGCommandDescriptor.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace xercesc_3_0 {
	class DOMDocument;
	class DOMElement;
}
namespace xercesc = xercesc_3_0;

namespace DG {

class MenuBar;
class Menu;
class ContextMenu;
class ToolBar;
class CommandDescriptor;
class CommandLayout;

// --- Class declarations ------------------------------------------------------

// --- CommandLayoutSerializer -------------------------------------------------

class DG_DLL_EXPORT CommandLayoutSerializer
{
	friend class Menu;
	friend class MenuSimpleItem;
	friend class MenuPopupItem;
	friend class MenuSeparatorItem;
	friend class MenuBar;
	friend class ContextMenu;
	friend class ToolBar;
	friend class ToolBarButton;
	friend class ToolBarPopupItem;
	friend class ToolBarSeparatorItem;
	friend class CommandLayout;

private:
	// inner class definitions

	// SerializeItem
	class SerializeItem {
	public:
		const void*	ptr;
		GS::UniString	id;

		SerializeItem () { this->ptr = nullptr; };
		SerializeItem (const void* ptr, const GS::UniString& id) { this->ptr = ptr; this->id = id; };
	};

	GS::HashTable<GS::UniString, Int32>			generatedIDs;
	GS::HashSet<GS::UniString>					alreadyUsedIDs;
	GS::HashTable<const void*, SerializeItem>	serializeItems;

	// utility
	void					SetId			(GS::OChannel& oc, const GS::UniString& id);
	void					SetIdRef		(GS::OChannel& oc, const GS::UniString& id);

	void					SetId			(xercesc::DOMElement* elem, const GS::UniString& id);
	void					SetIdRef		(xercesc::DOMElement* elem, const GS::UniString& id);

	// serialization
	GSErrCode				InitSerialize		(const CommandLayout* commandLayout);
	void					Serialize			(xercesc::DOMDocument* doc, const CommandLayout& commandLayout);
	void					Serialize			(xercesc::DOMDocument* doc, const ShortcutScheme& shortcutScheme, const GS::UniString& xslPath = GS::UniString());
	void					SerializeCommands	(xercesc::DOMDocument* doc);
	void					SerializeContexts	(xercesc::DOMDocument* doc, const ShortcutScheme& shortcutScheme, const GS::HashTable<GS::Guid, GS::UniString>& contextNames);
	void					ExitSerialize		(void);

	// utility functions
	bool					AddSerializeItem	(const void* ptr, GS::UniString* id, const GS::UniString& serializationId);

public:

	// constructors
	CommandLayoutSerializer ();
	CommandLayoutSerializer (const CommandLayout& commandLayout);
	~CommandLayoutSerializer ();

	// serialization
	GSErrCode	XMLSerialize	(GS::OChannel& oChannel, const CommandLayout& commandLayout);
	GSErrCode	XMLSerialize	(xercesc::DOMDocument* doc, const CommandLayout& commandLayout);

	GSErrCode	XMLSerialize	(GS::OChannel& oChannel,
								 const ShortcutScheme& shortcutScheme,
								 const GS::HashTable<GS::Guid, GS::UniString>& contextNames,
								 const GS::UniString& xslPath = GS::UniString());
};

}	// namespace DG

namespace DG {

// --- CommandLayoutDeserializer -----------------------------------------------

class DG_DLL_EXPORT CommandLayoutDeserializer
{
	friend class Menu;
	friend class MenuSimpleItem;
	friend class MenuPopupItem;
	friend class MenuSeparatorItem;
	friend class MenuBar;
	friend class ContextMenu;
	friend class ToolBar;
	friend class ToolBarButton;
	friend class ToolBarPopupItem;
	friend class ToolBarSeparatorItem;
	friend class CommandLayout;

private:
	// inner class definitions

	// DeserializeItem
	class DeserializeItem {
	public:
		void*		ptr;
		GS::UniString	id;

		DeserializeItem () { this->ptr = nullptr; };
		DeserializeItem (void* ptr) { this->ptr = ptr; };
		DeserializeItem (void* ptr, const GS::UniString& id) { this->ptr = ptr; this->id = id; };
	};

	GS::HashTable<GS::UniString, DeserializeItem>	deserializeItems;

	// deserialization
	GSErrCode				InitDeserialize	(void);
	GSErrCode				Deserialize		(xercesc::DOMDocument* doc, CommandLayout* commandLayout);
	void					ExitDeserialize	(void);

	// utility functions
	void					AddDeserializeItem			(void* ptr, const GS::UniString& id);

	void					GetIds						(xercesc::DOMElement* elem, GS::UniString* id, GS::UniString* refId);
	GSErrCode				GetPtrFromElement			(xercesc::DOMElement* elem, void** ptr, GS::UniString* pId);
	Menu*					CreateMenu					(xercesc::DOMElement* elem, void* ptr, const GS::UniString& id);
	ContextMenu*			CreateContextMenu			(xercesc::DOMElement* elem, void* ptr, const GS::UniString& id);
	MenuBar*				CreateMenuBar				(xercesc::DOMElement* elem, void* ptr, const GS::UniString& id);
	ToolBar*				CreateToolBar				(xercesc::DOMElement* elem, void* ptr, const GS::UniString& id);

	void					GetIds						(GS::IChannel& ic, GS::UniString* id, GS::UniString* refId);
	GSErrCode				GetPtrFromElement_OLD		(GS::IChannel& ic, void** ptr, GS::UniString* pId);
	GSErrCode				GetPtrFromElement_D_079		(GS::IChannel& ic, void** ptr, GS::UniString* pId);
	GSErrCode				GetPtrFromElement			(GS::IChannel& ic, void** ptr, GS::UniString* pId);
	Menu*					CreateMenu					(GS::IChannel& ic, void* ptr, const GS::UniString& id);
	ContextMenu*			CreateContextMenu			(GS::IChannel& ic, void* ptr, const GS::UniString& id);
	MenuBar*				CreateMenuBar				(GS::IChannel& ic, void* ptr, const GS::UniString& id);
	ToolBar*				CreateToolBar				(GS::IChannel& ic, void* ptr, const GS::UniString& id);

public:
	// constructors
				CommandLayoutDeserializer	();

	// deserialization
	GSErrCode	XMLDeserialize	(GS::IChannel& iChannel, CommandLayout* commandLayout);
	GSErrCode	XMLDeserialize	(xercesc::DOMDocument* doc, CommandLayout* commandLayout);

	static GSErrCode		GetUniString_D_079			(GS::IChannel& ic, GS::UniString* uStr);
};

}	// namespace DG

#endif
