// *********************************************************************************************************************
// API AttributeListItems - Wrapper classes for AttributeListItems to make them useable from Add-Ons
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef APIATTRIBUTELISTITEMS_HPP
#define APIATTRIBUTELISTITEMS_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

#include <float.h>

// GSRoot
#include "EventSource.hpp"
#include "EventObserver.hpp"

// GSUtils
#include "GSUtilsDefs.h"

// DG
#include "DG.h"
#include "DGModule.hpp"

// UC
#include "UC.h"

// own
#include "VBAttributeListExport.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace ADB {
	class IAttributeSetProvider;
}

namespace VBAC {
	class ProfileControlData;
}

namespace VBAL {
	class AttributeListItem;
	class AttributeListSimpleItem;
	class AttributeListGroupItem;

	class AttributeListItemObserver;
	class AttributeListPenItemObserver;
	class AttributeListFillItemObserver;
	class AttributeListLineTypeItemObserver;
	class AttributeListCheckItemObserver;
	class AttributeListSelectionItemObserver;
	class AttributeListRealItemObserver;
	class AttributeListButtonItemObserver;
	class AttributeListIconButtonItemObserver;
	class AttributeListMaterialItemObserver;
	class AttributeListTextItemObserver;
	class AttributeListDictionaryItemObserver;

	class APIAttributeList;

	class APIAttributeListGroupItem;

	class APIAttributeListItemObserver;
	class APIAttributeListPenItemObserver;
	class APIAttributeListFillItemObserver;
	class APIAttributeListLineTypeItemObserver;
	class APIAttributeListCheckItemObserver;
	class APIAttributeListSelectionItemObserver;
	class APIAttributeListRealItemObserver;
	class APIAttributeListMaterialItemObserver;
	class APIAttributeListTextItemObserver;
	class APIAttributeListDictionaryItemObserver;
	class APIAttributeListButtonItemObserver;
	class APIAttributeListIconButtonItemObserver;


#ifndef API_AttributeIndex
typedef GSAttributeIndex API_AttributeIndex;
#endif

#ifndef APIInvalidAttributeIndex
constexpr API_AttributeIndex	APIInvalidAttributeIndex	= 0;
#endif

constexpr API_AttributeIndex	APIInvalidMaterialIdx		= -314;
constexpr short					APIInvalidPenIndex			= -1223;


// --- APIAttributeListItem -----------------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListItem
{
friend class APIAttributeList;

protected:
	VBAL::AttributeListItem*			vbAttributeListItem;

public:
	virtual ~APIAttributeListItem ();

			void Attach (APIAttributeListItemObserver& observer);
			void Detach (APIAttributeListItemObserver& observer);

	virtual void SetStatus (bool newStatus);
			bool GetStatus () const;

	virtual	void SetVisibility (bool newVisibility);
			bool IsVisible () const;

	virtual bool HasFocusedEditField (void);

			void Select (bool shouldFocused = false);
			bool IsSelected (void);

			void SetName (const GS::UniString& name);
			void SetIcon (const DG::Icon& icon);

			GS::UniString GetName () const;

			void SetFirstVisible (void);

			void SetUserData (Int32 data);
			Int32 GetUserData (void) const;

			void SetDefaultToolTip (const GS::UniString& defaultToolTip);

			void SetCustomBgColor (const Gfx::Color& customBgColor);
};


// --- APIAttributeListItemObserver ---------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListItemObserver
{
friend class APIAttributeListItem;

private:
	VBAL::AttributeListItemObserver*	vbAttributeListItemObserver;

public:
	APIAttributeListItemObserver ();
	virtual ~APIAttributeListItemObserver ();

	virtual GS::UniString	AttributeListItemToolTipRequested (const APIAttributeListItem& source);
	virtual void			NameChanged (const APIAttributeListItem& source);
	virtual void			IconColumnClicked (const APIAttributeListItem& source);
};


// --- APIAttributeListSimpleItem -----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListSimpleItem: public APIAttributeListItem
{
friend class APIAttributeListGroupItem;

protected:
	VBAL::AttributeListSimpleItem*	GetVBAttrListSimpleItem () const;

public:
	virtual ~APIAttributeListSimpleItem ();

	void			SetBoldText (bool boldText = true);
	bool			HasBoldText (void) const;

	APIAttributeListGroupItem* GetGroup (void) const;
};


// --- APIAttributeListPenItem -----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListPenItem: public APIAttributeListSimpleItem
{
public:
	enum SubType {
		InvalidSubType,
		GMPen,
		GMPenWNull,
		OwnFilteredPen
	};

	APIAttributeListPenItem (const GS::UniString& name							= GS::UniString (),
							 const DG::Icon& icon								= DG::Icon (),
							 ADB::IAttributeSetProvider* attributeSetProvider	= nullptr,
							 APIAttributeListPenItem::SubType subType			= APIAttributeListPenItem::InvalidSubType,
							 short penValue										= APIInvalidPenIndex,
							 bool status										= true,
							 bool boldText										= false);
	virtual ~APIAttributeListPenItem ();

	short	GetPen () const;
	void	SetPen (short newPen);

	void	Attach (APIAttributeListPenItemObserver& observer);
	void	Detach (APIAttributeListPenItemObserver& observer);

	void	SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);
	void	SetSubType (SubType subType);
	void	SetCustomCallBackAndUserData (const UC257CallBack callBack, const void* customUserData);

	virtual bool HasFocusedEditField (void) override;
};


// --- APIAttributeListPenItemObserver ---------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListPenItemObserver:	public APIAttributeListItemObserver
{
friend class APIAttributeListPenItem;

private:
	VBAL::AttributeListPenItemObserver*	vbAttributeListPenItemObserver;

public:
	APIAttributeListPenItemObserver ();
	virtual ~APIAttributeListPenItemObserver ();

	virtual void PenChanged (const APIAttributeListPenItem& source);
};


// --- APIAttributeListFillItem ----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListFillItem: public APIAttributeListSimpleItem
{
public:
	enum SubType {
		InvalidSubType,
		ACPolyFill,
		ACWallFill,
		ACWallSoftInsulationFill,
		ACPolyWallFill,
		ACAllCompFill,
		ACWallSetsFill,
		ACSlabSetsFill,
		ACRoofSetsFill,
		ACShellSetsFill,
		ACOnlyCompFill,
		ACSurfaceFill,
		ACPolyFillWithGradient,
		OwnFilteredFill
	};

	APIAttributeListFillItem (const GS::UniString& name							= GS::UniString (),
							  const DG::Icon& icon								= DG::Icon (),
							  const DG::Icon& customIcon						= DG::Icon (),
							  ADB::IAttributeSetProvider* attributeSetProvider	= nullptr,
							  APIAttributeListFillItem::SubType subType			= APIAttributeListFillItem::InvalidSubType,
							  API_AttributeIndex fillValue						= APIInvalidAttributeIndex,
							  short fgPen										= 0,
							  short bgPen										= 0,
							  short contourPen									= 0,
							  short innerPen									= 0,
							  bool status										= true,
							  bool boldText										= false);
	virtual ~APIAttributeListFillItem ();

	API_AttributeIndex			GetFill (void) const;
	void						SetFill (const API_AttributeIndex& newFill);

	void	Attach (APIAttributeListFillItemObserver& observer);
	void	Detach (APIAttributeListFillItemObserver& observer);

	void	SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);
	void	SetSubType (SubType subType);
	void	SetCustomCallBackAndUserData (const UC257CallBack callBack, const void* customUserData);

	void	SetForePen (short newPen);
	void	SetBackPen (short newPen);
	void	SetContourPen (short newPen);
	void	SetInnerPen (short newPen);

	void	SetCustomIcon (const DG::Icon& customIcon);
};


// --- APIAttributeListFillItemObserver --------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListFillItemObserver:	public APIAttributeListItemObserver
{
friend class APIAttributeListFillItem;

private:
	VBAL::AttributeListFillItemObserver*	vbAttributeListFillItemObserver;

public:
	APIAttributeListFillItemObserver ();
	virtual ~APIAttributeListFillItemObserver ();

	virtual void FillChanged (const APIAttributeListFillItem& source);
};


// --- APIAttributeListLineTypeItem ------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListLineTypeItem: public APIAttributeListSimpleItem
{
public:
	enum SubType {
		InvalidSubType,
		ACSymbolLine,
		ACDashedLine,
		OwnFilteredLine
	};

	APIAttributeListLineTypeItem (const GS::UniString& name							= GS::UniString (),
								  const DG::Icon& icon								= DG::Icon (),
								  ADB::IAttributeSetProvider* attributeSetProvider	= nullptr,
								  APIAttributeListLineTypeItem::SubType subType		= APIAttributeListLineTypeItem::InvalidSubType,
								  API_AttributeIndex lineType						= APIInvalidAttributeIndex,
								  bool status										= true,
								  bool boldText										= false);
	virtual ~APIAttributeListLineTypeItem ();

	API_AttributeIndex			GetLineType (void) const;
	void						SetLineType (const API_AttributeIndex& newLineType);

	void	Attach (APIAttributeListLineTypeItemObserver& observer);
	void	Detach (APIAttributeListLineTypeItemObserver& observer);

	void	SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);
	void	SetSubType (SubType subType);
	void	SetCustomCallBackAndUserData (const UC261CallBack callBack, const void* customUserData);
};


// --- APIAttributeListLineTypeItemObserver ----------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListLineTypeItemObserver:	public APIAttributeListItemObserver
{
friend class APIAttributeListLineTypeItem;

private:
	VBAL::AttributeListLineTypeItemObserver*	vbAttributeListLineTypeItemObserver;

public:
	APIAttributeListLineTypeItemObserver ();
	virtual ~APIAttributeListLineTypeItemObserver ();

	virtual void LineTypeChanged (const APIAttributeListLineTypeItem& source);
};


// --- APIAttributeListCheckItem ------------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListCheckItem:	public APIAttributeListSimpleItem
{
public:
	APIAttributeListCheckItem (const GS::UniString& name = GS::UniString (),
							const DG::Icon& icon = DG::Icon (),
							bool isChecked = false,
							const GS::UniString& checkName = GS::UniString (),
							bool status = true,
							bool boldText = false);
	virtual ~APIAttributeListCheckItem ();


	bool					IsChecked () const;
	void					SetChecked (bool checked);

	void					SetCheckName (const GS::UniString& name);
	GS::UniString			GetCheckName () const;

	void	Attach (APIAttributeListCheckItemObserver& observer);
	void	Detach (APIAttributeListCheckItemObserver& observer);
};


// --- APIAttributeListCheckItemObserver ----------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListCheckItemObserver:	public APIAttributeListItemObserver
{
friend class APIAttributeListCheckItem;

private:
	VBAL::AttributeListCheckItemObserver*	vbAttributeListCheckItemObserver;

public:
	APIAttributeListCheckItemObserver ();
	virtual ~APIAttributeListCheckItemObserver ();

	virtual void CheckChanged (const APIAttributeListCheckItem& source);
};


// --- APIAttributeListSelectionItem --------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListSelectionItem:	public APIAttributeListSimpleItem
{
protected:
	APIAttributeListSelectionItem (bool dummy);

public:
	struct Item {
		DG::Icon			icon;
		GS::UniString		text;
		bool				enabled;
		bool				isSeparator;
		GS::Ref<GS::Object>	userData;

		Item () : enabled (true), isSeparator (false) {}
	};

	APIAttributeListSelectionItem ( const GS::UniString& name = GS::UniString (),
									const DG::Icon& icon = DG::Icon (),
									bool status = true,
									bool boldText = false);
	virtual ~APIAttributeListSelectionItem ();

	virtual short AddItem (const Item& newItem);
	short	AddSeparator ();
	void	EnableItem (short index);		// 1 based index because of DG
	void	DisableItem (short index);		// 1 based index because of DG
	void	SetItemStatus (short index, bool enabled);		// 1 based index because of DG
	void	SetItemIcon (short index, const DG::Icon& icon);

	short	GetSelected () const;			// 1 based index because of DG
	void	SelectItem (short index);		// 1 based index because of DG
	USize	GetSelectableItemCount  (void) const;
	GS::UniString GetSelectedString (void) const;

	GS::Ref<GS::Object>	GetItemData (short index) const;
	void				SetItemData (short index, GS::Ref<GS::Object> data);

	void	DeleteAllItems (void);

	void	Attach (APIAttributeListSelectionItemObserver& observer);
	void	Detach (APIAttributeListSelectionItemObserver& observer);
};


// --- APIAttributeListSelectionItemObserver ------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListSelectionItemObserver:	public APIAttributeListItemObserver
{
friend class APIAttributeListSelectionItem;

private:
	VBAL::AttributeListSelectionItemObserver*	vbAttributeListSelectionItemObserver;

public:
	APIAttributeListSelectionItemObserver ();
	virtual ~APIAttributeListSelectionItemObserver ();

	virtual void SelectionChanged (const APIAttributeListSelectionItem& source);
};


// --- APIAttributeListRealItem -----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListRealItem:	public APIAttributeListSelectionItem
{
protected:
	APIAttributeListRealItem (bool dummy);

public:
	APIAttributeListRealItem (const GS::UniString& name = GS::UniString (),
							const DG::Icon& icon = DG::Icon (),
							double minValue = -DBL_MAX,
							double maxValue = DBL_MAX,
							double value = 0.0,
							bool editable = true,
							bool status = true,
							bool boldText = false,
							const GS::UniString& tagText = GS::UniString ());
	virtual ~APIAttributeListRealItem ();

	void					AddStringItem (const GS::UniString& newString);

	double					GetValue () const;
	void					SetValue (double value);

	double					GetMinValue () const;
	virtual void			SetMinValue (double minValue);

	double					GetMaxValue () const;
	virtual void			SetMaxValue (double maxValue);

	bool					IsEditable (void) const;
	void					SetEditable (bool editable);

	GS::UniString			GetTagText (void) const;
	void					SetTagText (const GS::UniString& tagText);

	void					Attach (APIAttributeListRealItemObserver& observer);
	void					Detach (APIAttributeListRealItemObserver& observer);

	virtual bool			HasFocusedEditField (void) override;
};


// --- APIAttributeListRealItemObserver ---------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListRealItemObserver:	virtual public APIAttributeListSelectionItemObserver
{
friend class APIAttributeListRealItem;

private:
	VBAL::AttributeListRealItemObserver*	vbAttributeListRealItemObserver;

public:
	APIAttributeListRealItemObserver ();
	virtual ~APIAttributeListRealItemObserver ();

	virtual void ValueChanged (const APIAttributeListRealItem& source);
};


// --- APIAttributeListLengthItem -----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListLengthItem:	public APIAttributeListRealItem
{
public:
	APIAttributeListLengthItem (const GS::UniString& name = GS::UniString (),
								const DG::Icon& icon = DG::Icon (),
								double minValue = -DBL_MAX,
								double maxValue = DBL_MAX,
								double value = 0.0,
								bool editable = true,
								bool status = true,
								bool boldText = false,
								const GS::UniString& tagText = GS::UniString ());
	virtual ~APIAttributeListLengthItem ();
};


// --- APIAttributeListAreaItem ----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListAreaItem : public APIAttributeListRealItem
{
public:
	APIAttributeListAreaItem (const GS::UniString& name = GS::UniString (),
							  const DG::Icon& icon = DG::Icon (),
							  double minValue = -DBL_MAX,
							  double maxValue = DBL_MAX,
							  double value = 0.0,
							  bool editable = true,
							  bool status = true,
							  bool boldText = false,
							  const GS::UniString& tagText = GS::UniString ());
	virtual ~APIAttributeListAreaItem ();
};


// --- APIAttributeListVolumeItem --------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListVolumeItem : public APIAttributeListRealItem
{
public:
	APIAttributeListVolumeItem (const GS::UniString& name = GS::UniString (),
								const DG::Icon& icon = DG::Icon (),
								double minValue = -DBL_MAX,
								double maxValue = DBL_MAX,
								double value = 0.0,
								bool editable = true,
								bool status = true,
								bool boldText = false,
								const GS::UniString& tagText = GS::UniString ());
	virtual ~APIAttributeListVolumeItem ();
};


// --- APIAttributeListAngleItem ------------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListAngleItem:	public APIAttributeListRealItem
{
public:
	APIAttributeListAngleItem (const GS::UniString& name = GS::UniString (),
							const DG::Icon& icon = DG::Icon (),
							double minValue = -DBL_MAX,
							double maxValue = DBL_MAX,
							double value = 0.0,
							bool editable = true,
							bool status = true,
							bool boldText = false,
							const GS::UniString& tagText = GS::UniString ());
	virtual ~APIAttributeListAngleItem ();
};


// --- APIAttributeListIntItem -----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListIntItem:	public APIAttributeListRealItem
{
public:
	APIAttributeListIntItem	(const GS::UniString& name = GS::UniString (),
								const DG::Icon& icon = DG::Icon (),
								Int32 minValue = -GS::MaxInt32,
								Int32 maxValue = GS::MaxInt32,
								Int32 value = 0,
								bool editable = true,
								bool status = true,
								bool boldText = false,
								const GS::UniString& tagText = GS::UniString ());
	virtual ~APIAttributeListIntItem ();

	Int32 GetValue			(void) const { return (Int32) APIAttributeListRealItem::GetValue ();}
	void SetValue			(Int32 value) { APIAttributeListRealItem::SetValue ((double) value); }

	Int32 GetMinValue		(void) const { return (Int32) APIAttributeListRealItem::GetMinValue (); }
	void SetMinValue		(Int32 minValue) { APIAttributeListRealItem::SetMinValue (minValue); }

	Int32 GetMaxValue		(void) const { return (Int32) APIAttributeListRealItem::GetMaxValue (); }
	void SetMaxValue		(Int32 maxValue) { APIAttributeListRealItem::SetMaxValue (maxValue); }
};


// --- APIAttributeListMaterialItem -------------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListMaterialItem:	public APIAttributeListSimpleItem
{
public:
	enum SubType {
		InvalidSubType,
		ACMaterial,
		ACBuildingMaterial,
		OwnFilteredMaterial,
		OwnFilteredBuildingMaterial
	};

	APIAttributeListMaterialItem (const GS::UniString& name							= GS::UniString (),
								  const DG::Icon& icon								= DG::Icon (),
								  ADB::IAttributeSetProvider* attributeSetProvider	= nullptr,
								  APIAttributeListMaterialItem::SubType subType		= APIAttributeListMaterialItem::ACMaterial,
								  API_AttributeIndex material						= APIInvalidMaterialIdx,
								  bool status										= true,
								  bool boldText										= false);
	virtual ~APIAttributeListMaterialItem ();

	API_AttributeIndex			GetMaterial (void) const;
	void						SetMaterial (const API_AttributeIndex& newMat);

	void						SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);

	SubType						GetSubType (void) const;
	void						SetSubType (SubType subType);

	void						SetCustomCallBackAndUserData (const UC257CallBack callBack, const void* customUserData);

	void						Attach (APIAttributeListMaterialItemObserver& observer);
	void						Detach (APIAttributeListMaterialItemObserver& observer);
};


// --- APIAttributeListMaterialItemObserver -----------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListMaterialItemObserver:	public APIAttributeListItemObserver
{
friend class APIAttributeListMaterialItem;

private:
	VBAL::AttributeListMaterialItemObserver*	vbAttributeListMaterialItemObserver;

public:
	APIAttributeListMaterialItemObserver ();
	virtual ~APIAttributeListMaterialItemObserver ();

	virtual void MaterialChanged (const APIAttributeListMaterialItem& source);
};


// --- APIAttributeListTextItem -----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListTextItem: public APIAttributeListSelectionItem
{
protected:
	APIAttributeListTextItem (bool dummy);

public:
	APIAttributeListTextItem (const GS::UniString& name = GS::UniString (),
							const DG::Icon& icon = DG::Icon (),
							const GS::UniString& text = GS::UniString (),
							bool autoCustomHandling = true,
							bool editable = true,
							bool valueListEnabled = true,
							bool status = true,
							bool boldText = false);
	virtual ~APIAttributeListTextItem ();

	void	AddStringItem (const GS::UniString& newString);

	GS::UniString GetCustomText (void) const;
	void	SetCustomText (const GS::UniString& newCustomText);

	GS::UniString GetText (void) const;
	void	SetText (const GS::UniString& text, bool selectInPopup = true);

	bool	IsEditable (void) const;
	void	SetEditable (bool editable);

	bool	IsValueListEnabled (void) const;
	void	EnableValueList (void);
	void	DisableValueList (void);

	void	Attach (APIAttributeListTextItemObserver& observer);
	void	Detach (APIAttributeListTextItemObserver& observer);

	virtual bool HasFocusedEditField (void) override;
};


// --- APIAttributeListTextItemObserver ---------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListTextItemObserver:	virtual public APIAttributeListSelectionItemObserver
{
friend class APIAttributeListTextItem;

private:
	VBAL::AttributeListTextItemObserver*	vbAttributeListTextItemObserver;

public:
	APIAttributeListTextItemObserver ();
	virtual ~APIAttributeListTextItemObserver ();

	virtual void TextChanged (const APIAttributeListTextItem& source);
};


// --- APIAttributeListDictionaryItem -----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListDictionaryItem : public APIAttributeListSelectionItem
{
protected:
	APIAttributeListDictionaryItem (bool dummy);

public:
	APIAttributeListDictionaryItem (const GS::UniString& name = GS::UniString (),
									const DG::Icon& icon = DG::Icon (),
									const GS::UniString& text = GS::UniString (),
									bool status = true,
									bool boldText = false);
	virtual ~APIAttributeListDictionaryItem ();

	GS::UniString GetText (void) const;
	void	SetText (const GS::UniString& text);

	void	Attach (APIAttributeListDictionaryItemObserver& observer);
	void	Detach (APIAttributeListDictionaryItemObserver& observer);

	virtual bool HasFocusedEditField (void) override;
};


// --- APIAttributeListDictionaryItemObserver ---------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListDictionaryItemObserver :	virtual public APIAttributeListSelectionItemObserver
{
friend class APIAttributeListDictionaryItem;

private:
	VBAL::AttributeListDictionaryItemObserver*	vbAttributeListDictionaryItemObserver;

public:
	APIAttributeListDictionaryItemObserver ();
	virtual ~APIAttributeListDictionaryItemObserver ();

	virtual void TextChanged (const APIAttributeListDictionaryItem& source);
};


// --- APIAttributeListTaggedTextItem ----------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListTaggedTextItem: public APIAttributeListTextItem
{
public:
	APIAttributeListTaggedTextItem (const GS::UniString& name = GS::UniString (),
									const DG::Icon& icon = DG::Icon (),
									const GS::UniString& text = GS::UniString (),
									bool autoCustomHandling = true,
									bool editable = true,
									bool valueListEnabled = true,
									bool status = true,
									bool boldText = false,
									const GS::UniString& tagText = GS::UniString ());
	virtual ~APIAttributeListTaggedTextItem ();

	GS::UniString			GetTagText (void) const;
	void					SetTagText (const GS::UniString& tagText);
};


// --- APIAttributeListSeparatorItem ---------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListSeparatorItem:	public APIAttributeListSimpleItem
{
public:
	APIAttributeListSeparatorItem ();
	virtual ~APIAttributeListSeparatorItem ();
};


// --- APIAttributeListButtonItem -----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListButtonItem:	public APIAttributeListSimpleItem
{
public:
	APIAttributeListButtonItem (const GS::UniString& name = GS::UniString (),
								 const DG::Icon& icon = DG::Icon (),
								 const GS::UniString& buttonIcon = GS::UniString (),
								 bool status = true,
								 bool boldText = false);
	virtual ~APIAttributeListButtonItem ();

	void	SetButtonText (const GS::UniString& buttonText);
	const	GS::UniString	GetButtonText (void) const;

	void	Attach (APIAttributeListButtonItemObserver& observer);
	void	Detach (APIAttributeListButtonItemObserver& observer);
};


// --- APIAttributeListButtonItemObserver ---------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListButtonItemObserver:	public APIAttributeListItemObserver
{
friend class APIAttributeListButtonItem;

private:
	VBAL::AttributeListButtonItemObserver*	vbAttributeListButtonItemObserver;

public:
	APIAttributeListButtonItemObserver ();
	virtual ~APIAttributeListButtonItemObserver ();

	virtual void ButtonClicked (const APIAttributeListButtonItem& source);
};


// --- APIAttributeListIconButtonItem -----------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListIconButtonItem:	public APIAttributeListSimpleItem
{
public:
	APIAttributeListIconButtonItem (const GS::UniString& name = GS::UniString (),
									const DG::Icon& icon = DG::Icon (),
									const GS::UniString& text = GS::UniString (),
		                         	const GS::UniString& tagText = GS::UniString (),
		                            const DG::Icon& buttonIcon = DG::Icon (),
		                            bool status = true,
		                            bool boldText = false);
	virtual ~APIAttributeListIconButtonItem ();

	void					SetText (const GS::UniString& text);
	GS::UniString			GetText (void) const;

	void					SetTagText (const GS::UniString& tagText);
	GS::UniString			GetTagText (void) const;

	void					SetButtonIcon (const DG::Icon& buttonIcon);
	DG::Icon				GetButtonIcon (void) const;

	void					SetButtonVisibility (bool visibility);

	void	Attach (APIAttributeListIconButtonItemObserver& observer);
	void	Detach (APIAttributeListIconButtonItemObserver& observer);
};


// --- APIAttributeListIconButtonItemObserver ---------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListIconButtonItemObserver:	public APIAttributeListItemObserver
{
friend class APIAttributeListIconButtonItem;

private:
	VBAL::AttributeListIconButtonItemObserver*	vbAttributeListIconButtonItemObserver;

public:
	APIAttributeListIconButtonItemObserver ();
	virtual ~APIAttributeListIconButtonItemObserver ();

	virtual void ButtonClicked (const APIAttributeListIconButtonItem& source);
};


// --- APIAttributeListGroupItem ------------------------------------------------------------------------------------------

class VBATTRIBUTELIST_DLL_EXPORT APIAttributeListGroupItem: public APIAttributeListItem
{
friend class APIAttributeList;
friend class APIAttributeListSimpleItem;

private:
	static GS::HashTable<VBAL::AttributeListGroupItem*, APIAttributeListGroupItem*>	attributeListGroupItemMap;
	GS::Array<APIAttributeListSimpleItem*>	mItems;

public:
	APIAttributeListGroupItem ();
	virtual ~APIAttributeListGroupItem ();

	void AddItem (APIAttributeListSimpleItem& item);
	void RemoveItem (APIAttributeListSimpleItem& item);

	void AddMasterItem (APIAttributeListSimpleItem& item);
	void RemoveMasterItem (void);

	void	Expand ();
	void	Collapse ();

	bool	IsExpanded () const;
	USize	GetSize () const;

	void	ClearGroup (void);
	virtual bool HasFocusedEditField (void) override;
};

}	// namespace VBAL

#endif
