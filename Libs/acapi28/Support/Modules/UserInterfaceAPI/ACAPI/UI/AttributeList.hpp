// *********************************************************************************************************************
// API AttributeList - Wrapper class for AttributeList to make it useable from Add-Ons
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef APIATTRIBUTELIST_HPP
#define APIATTRIBUTELIST_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

// DG
#include "DG.h"

// GSRoot
#include "HashTable.hpp"

// own
#include "ACAPI/UI/AttributeListItems.hpp"
#include "UserInterfaceAPIExport.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace VBAL {
	class AttributeList;
	class AttributeListItem;
}

namespace ACAPI {
namespace UI {


#ifndef APIColumnResizeRatioNotSet
#define APIColumnResizeRatioNotSet -1
#endif


// === AttributeList class ==========================================================================================

class USERINTERFACEAPI_DLL_EXPORT AttributeList
{
public:
	enum HeaderType {
		NoHeader = 0,
		AllHeadersSeparated = 1,
		CommonHeadersForFixSizedColumns = 2
	};

private:
	VBAL::AttributeList* vbAttributeList;

	GS::Array<AttributeListItem*>	mItems;

	static GS::HashTable<const VBAL::AttributeListItem*, AttributeListItem*>	attributeListItemMap;

	static AttributeListItem* GetAttributeListItemFromMap (const VBAL::AttributeListItem* key)
	{
		return AttributeList::attributeListItemMap.ContainsKey (key) ? AttributeList::attributeListItemMap.Get (key) : nullptr;
	}

public:
	AttributeList (const DG::Panel& panel,
					  short item,
					  DG::ListBox::ScrollType scroll = DG::ListBox::VScroll,
					  short textEditMaxlength = 64,
					  const GS::UniString& headerString1 = GS::UniString (),
					  const GS::UniString& headerString2 = GS::UniString (),
					  AttributeList::HeaderType headerType = AttributeList::AllHeadersSeparated,
					  bool hasIconColumn = true,
					  bool isVisible = true);

	AttributeList (const DG::Panel& panel,
					  short x,
					  short y,
					  short width,
					  short height,
					  DG::ListBox::ScrollType scroll = DG::ListBox::VScroll,
					  short textEditMaxlength = 64,
					  const GS::UniString& headerString1 = GS::UniString (),
					  const GS::UniString& headerString2 = GS::UniString (),
					  AttributeList::HeaderType headerType = AttributeList::AllHeadersSeparated,
					  bool hasIconColumn = true,
					  bool isVisible = true);

	~AttributeList ();

	void		AddListItem (AttributeListItem& item);
	void		RemoveListItem (AttributeListItem& item);

	void		Move (short hDisp, short vDisp);
	void		Resize (short hGrow, short vGrow);
	void		MoveAndResize (short hDisp, short vDisp, short hGrow, short vGrow);

	void		SetRect (const DG::Rect& rect);
	DG::Rect	GetRect (void) const;

	short		GetRequiredHeight (void) const;

	void		LayoutTabs (void);

	void		FullRefreshList (bool selectFirstAsDefault = true);
	void		DisableUpdate (void);
	void		EnableUpdate (void);
	bool		UpdateIsEnabled (void);

	void		ClearList (bool refreshList = true);

	AttributeListItem* GetSelectedItem (void);
	void 					SelectItem (AttributeListItem* attributeListItem, bool shouldFocused = false);

	AttributeListItem* GetFirstVisibleItem (void);
	void					SetFirstVisibleItem (AttributeListItem* attributeListItem);

	short		GetListBoxId (void) const;

	void		ExpandAllGroups (void);
	void		CollapseAllGroups (void);

	void		SetStatus (bool	newStatus);
	bool		IsEnabled (void) const;

	void		Show (void);
	void		Hide (void);
	bool		IsVisible (void);

	bool		IsEmpty (void);

	static const AttributeListItem* GetConstAttributeListItemFromMap (const VBAL::AttributeListItem* key)
	{
		return AttributeList::attributeListItemMap.ContainsKey (key) ? AttributeList::attributeListItemMap.Get (key) : nullptr;
	}
};

}	// namespace UI

}	// namespace ACAPI

#endif
