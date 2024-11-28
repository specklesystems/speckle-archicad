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
#include "VBAttributeListExport.hpp"
#include "APIAttributeListItems.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace VBAL {
	class AttributeList;
	class AttributeListItem;


#ifndef APIColumnResizeRatioNotSet
	#define APIColumnResizeRatioNotSet -1
#endif


// === APIAttributeList class ==========================================================================================

class VBATTRIBUTELIST_DLL_EXPORT	APIAttributeList
{
public:
	enum HeaderType {
		NoHeader						= 0,
		AllHeadersSeparated				= 1,
		CommonHeadersForFixSizedColumns	= 2
	};

private:
	VBAL::AttributeList*				vbAttributeList;

	GS::Array<APIAttributeListItem*>	mItems;

	static GS::HashTable<const VBAL::AttributeListItem*, APIAttributeListItem*>	attributeListItemMap;

	static APIAttributeListItem*	GetAPIAttributeListItemFromMap (const VBAL::AttributeListItem* key)
	{
		return APIAttributeList::attributeListItemMap.ContainsKey (key) ? APIAttributeList::attributeListItemMap.Get (key) : nullptr;
	}

public:
	APIAttributeList (	const DG::Panel& panel,
						short item,
						DG::ListBox::ScrollType scroll = DG::ListBox::VScroll,
						short textEditMaxlength = 64,
						const GS::UniString& headerString1 = GS::UniString (),
						const GS::UniString& headerString2 = GS::UniString (),
						APIAttributeList::HeaderType headerType = APIAttributeList::AllHeadersSeparated,
						bool hasIconColumn = true,
						bool isVisible = true);

	APIAttributeList (	const DG::Panel& panel,
						short x,
						short y,
						short width,
						short height,
						DG::ListBox::ScrollType scroll = DG::ListBox::VScroll,
						short textEditMaxlength = 64,
						const GS::UniString& headerString1 = GS::UniString (),
						const GS::UniString& headerString2 = GS::UniString (),
						APIAttributeList::HeaderType headerType = APIAttributeList::AllHeadersSeparated,
						bool hasIconColumn = true,
						bool isVisible = true);

   ~APIAttributeList ();

	void		AddListItem (APIAttributeListItem& item);
	void		RemoveListItem (APIAttributeListItem& item);

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

	APIAttributeListItem*	GetSelectedItem (void);
	void 					SelectItem (APIAttributeListItem* attributeListItem, bool shouldFocused = false);

	APIAttributeListItem*	GetFirstVisibleItem (void);
	void					SetFirstVisibleItem (APIAttributeListItem* attributeListItem);

	short		GetListBoxId (void) const;

	void		ExpandAllGroups		(void);
	void		CollapseAllGroups	(void);

	void		SetStatus (bool	newStatus);
	bool		IsEnabled (void) const;

	void		Show (void);
	void		Hide (void);
	bool		IsVisible (void);

	bool		IsEmpty (void);

	static const APIAttributeListItem*	GetConstAPIAttributeListItemFromMap (const VBAL::AttributeListItem* key)
	{
		return APIAttributeList::attributeListItemMap.ContainsKey (key) ? APIAttributeList::attributeListItemMap.Get (key) : nullptr;
	}
};

}	// namespace VBAL

#endif
