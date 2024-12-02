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
#include "UserInterfaceAPIExport.hpp"
#include "APIdefs_AttributeIndex.hpp"

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
class AttributeListCompositeItemObserver;
class AttributeListLineTypeItemObserver;
class AttributeListCheckItemObserver;
class AttributeListSelectionItemObserver;
class AttributeListRealItemObserver;
class AttributeListButtonItemObserver;
class AttributeListIconButtonItemObserver;
class AttributeListMaterialItemObserver;
class AttributeListBuildingMaterialItemObserver;
class AttributeListTextItemObserver;
class AttributeListDictionaryItemObserver;
}

namespace ACAPI {

constexpr short				APIInvalidPenIndex = -1223;

namespace UI {

class AttributeList;

class AttributeListGroupItem;

class AttributeListItemObserver;
class AttributeListPenItemObserver;
class AttributeListFillItemObserver;
class AttributeListCompositeItemObserver;
class AttributeListLineTypeItemObserver;
class AttributeListCheckItemObserver;
class AttributeListSelectionItemObserver;
class AttributeListRealItemObserver;
class AttributeListMaterialItemObserver;
class AttributeListBuildingMaterialItemObserver;
class AttributeListTextItemObserver;
class AttributeListDictionaryItemObserver;
class AttributeListButtonItemObserver;
class AttributeListIconButtonItemObserver;


// --- AttributeListItem -----------------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListItem
{
	friend class AttributeList;

protected:
	VBAL::AttributeListItem* vbAttributeListItem;

public:
	virtual ~AttributeListItem ();

	void Attach (AttributeListItemObserver& observer);
	void Detach (AttributeListItemObserver& observer);

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


// --- AttributeListItemObserver ---------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListItemObserver
{
	friend class AttributeListItem;

private:
	VBAL::AttributeListItemObserver* vbAttributeListItemObserver;

public:
	AttributeListItemObserver ();
	virtual ~AttributeListItemObserver ();

	virtual GS::UniString	AttributeListItemToolTipRequested (const AttributeListItem& source);
	virtual void			NameChanged (const AttributeListItem& source);
	virtual void			IconColumnClicked (const AttributeListItem& source);
};


// --- AttributeListSimpleItem -----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListSimpleItem : public AttributeListItem
{
	friend class AttributeListGroupItem;

protected:
	VBAL::AttributeListSimpleItem* GetVBAttrListSimpleItem () const;

public:
	virtual ~AttributeListSimpleItem ();

	void			SetBoldText (bool boldText = true);
	bool			HasBoldText (void) const;

	AttributeListGroupItem* GetGroup (void) const;
};


// --- AttributeListPenItem -----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListPenItem : public AttributeListSimpleItem
{
public:
	enum SubType {
		InvalidSubType,
		GMPen,
		GMPenWNull,
		OwnFilteredPen
	};

	AttributeListPenItem (const GS::UniString& name = GS::UniString (),
							 const DG::Icon& icon = DG::Icon (),
							 ADB::IAttributeSetProvider* attributeSetProvider = nullptr,
							 AttributeListPenItem::SubType subType = AttributeListPenItem::InvalidSubType,
							 short penValue = APIInvalidPenIndex,
							 bool status = true,
							 bool boldText = false);
	virtual ~AttributeListPenItem ();

	short	GetPen () const;
	void	SetPen (short newPen);

	void	Attach (AttributeListPenItemObserver& observer);
	void	Detach (AttributeListPenItemObserver& observer);

	void	SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);
	void	SetSubType (SubType subType);
	void	SetCustomCallBackAndUserData (const UC257CallBack callBack, const void* customUserData);

	virtual bool HasFocusedEditField (void) override;
};


// --- AttributeListPenItemObserver ---------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListPenItemObserver : public AttributeListItemObserver
{
	friend class AttributeListPenItem;

private:
	VBAL::AttributeListPenItemObserver* vbAttributeListPenItemObserver;

public:
	AttributeListPenItemObserver ();
	virtual ~AttributeListPenItemObserver ();

	virtual void PenChanged (const AttributeListPenItem& source);
};


// --- AttributeListFillItem ----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListFillItem : public AttributeListSimpleItem
{
public:
	enum SubType {
		InvalidSubType,
		ACPolyFill,
		ACWallFill,
		ACWallSoftInsulationFill,
		ACPolyWallFill,
		ACSurfaceFill,
		ACPolyFillWithGradient,
		OwnFilteredFill
	};

	AttributeListFillItem (const GS::UniString& name = GS::UniString (),
							  const DG::Icon& icon = DG::Icon (),
							  const DG::Icon& customIcon = DG::Icon (),
							  ADB::IAttributeSetProvider* attributeSetProvider = nullptr,
							  SubType subType = InvalidSubType,
							  API_AttributeIndex fillValue = APIInvalidAttributeIndex,
							  short fgPen = 0,
							  short bgPen = 0,
							  short contourPen = 0,
							  short innerPen = 0,
							  bool status = true,
							  bool boldText = false);
	virtual ~AttributeListFillItem ();

	API_AttributeIndex			GetFill (void) const;
	void						SetFill (const API_AttributeIndex& newFill);

	void	Attach (AttributeListFillItemObserver& observer);
	void	Detach (AttributeListFillItemObserver& observer);

	void	SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);
	void	SetSubType (SubType subType);

	void	SetForegroundPen (short newPen);
	void	SetBackgroundPen (short newPen);
	void	SetContourPen (short newPen);

	void	SetCustomIcon (const DG::Icon& customIcon);
};


// --- AttributeListFillItemObserver --------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListFillItemObserver : public AttributeListItemObserver
{
	friend class AttributeListFillItem;

private:
	VBAL::AttributeListFillItemObserver* vbAttributeListFillItemObserver;

public:
	AttributeListFillItemObserver ();
	virtual ~AttributeListFillItemObserver ();

	virtual void FillChanged (const AttributeListFillItem& source);
};



// --- AttributeListCompositeItem ----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListCompositeItem : public AttributeListSimpleItem {
public:
	enum SubType {
		InvalidSubType,
		CompositeWalls,
		CompositeSlabs,
		CompositeShells,
		CompositeRoofs,
		AllComposites,
		OwnFilteredComposite
	};

	AttributeListCompositeItem (const GS::UniString& name = GS::UniString (),
								const DG::Icon& icon = DG::Icon (),
								const DG::Icon& customIcon = DG::Icon (),
								ADB::IAttributeSetProvider* attributeSetProvider = nullptr,
								SubType subType = InvalidSubType,
								API_AttributeIndex CompositeValue = APIInvalidAttributeIndex,
								short fgPen = 0,
								short bgPen = 0,
								short contourPen = 0,
								short innerPen = 0,
								bool status = true,
								bool boldText = false);
	virtual ~AttributeListCompositeItem ();

	API_AttributeIndex			GetComposite (void) const;
	void						SetComposite (const API_AttributeIndex& newComposite);

	void	Attach (AttributeListCompositeItemObserver& observer);
	void	Detach (AttributeListCompositeItemObserver& observer);

	void	SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);
	void	SetSubType (SubType subType);

	void	SetForegroundPen (short newPen);
	void	SetBackgroundPen (short newPen);
	void	SetContourPen (short newPen);
	void	SetSeparatorPen (short newPen);

	void	SetCustomIcon (const DG::Icon& customIcon);
};


// --- AttributeListCompositeItemObserver --------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListCompositeItemObserver : public AttributeListItemObserver {
	friend class AttributeListCompositeItem;

private:
	VBAL::AttributeListCompositeItemObserver* vbAttributeListCompositeItemObserver;

public:
	AttributeListCompositeItemObserver ();
	virtual ~AttributeListCompositeItemObserver ();

	virtual void CompositeChanged (const AttributeListCompositeItem& source);
};



// --- AttributeListLineTypeItem ------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListLineTypeItem : public AttributeListSimpleItem
{
public:
	enum SubType {
		InvalidSubType,
		ACSymbolLine,
		ACDashedLine,
		OwnFilteredLine
	};

	AttributeListLineTypeItem (const GS::UniString& name = GS::UniString (),
								  const DG::Icon& icon = DG::Icon (),
								  ADB::IAttributeSetProvider* attributeSetProvider = nullptr,
								  AttributeListLineTypeItem::SubType subType = AttributeListLineTypeItem::InvalidSubType,
								  API_AttributeIndex lineType = APIInvalidAttributeIndex,
								  bool status = true,
								  bool boldText = false);
	virtual ~AttributeListLineTypeItem ();

	API_AttributeIndex			GetLineType (void) const;
	void						SetLineType (const API_AttributeIndex& newLineType);

	void	Attach (AttributeListLineTypeItemObserver& observer);
	void	Detach (AttributeListLineTypeItemObserver& observer);

	void	SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);
	void	SetSubType (SubType subType);
};


// --- AttributeListLineTypeItemObserver ----------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListLineTypeItemObserver : public AttributeListItemObserver
{
	friend class AttributeListLineTypeItem;

private:
	VBAL::AttributeListLineTypeItemObserver* vbAttributeListLineTypeItemObserver;

public:
	AttributeListLineTypeItemObserver ();
	virtual ~AttributeListLineTypeItemObserver ();

	virtual void LineTypeChanged (const AttributeListLineTypeItem& source);
};


// --- AttributeListCheckItem ------------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListCheckItem : public AttributeListSimpleItem
{
public:
	AttributeListCheckItem (const GS::UniString& name = GS::UniString (),
							   const DG::Icon& icon = DG::Icon (),
							   bool isChecked = false,
							   const GS::UniString& checkName = GS::UniString (),
							   bool status = true,
							   bool boldText = false);
	virtual ~AttributeListCheckItem ();


	bool					IsChecked () const;
	void					SetChecked (bool checked);

	void					SetCheckName (const GS::UniString& name);
	GS::UniString			GetCheckName () const;

	void	Attach (AttributeListCheckItemObserver& observer);
	void	Detach (AttributeListCheckItemObserver& observer);
};


// --- AttributeListCheckItemObserver ----------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListCheckItemObserver : public AttributeListItemObserver
{
	friend class AttributeListCheckItem;

private:
	VBAL::AttributeListCheckItemObserver* vbAttributeListCheckItemObserver;

public:
	AttributeListCheckItemObserver ();
	virtual ~AttributeListCheckItemObserver ();

	virtual void CheckChanged (const AttributeListCheckItem& source);
};


// --- AttributeListSelectionItem --------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListSelectionItem : public AttributeListSimpleItem
{
protected:
	AttributeListSelectionItem (bool dummy);

public:
	struct Item {
		DG::Icon			icon;
		GS::UniString		text;
		bool				enabled;
		bool				isSeparator;
		GS::Ref<GS::Object>	userData;

		Item () : enabled (true), isSeparator (false) {}
	};

	AttributeListSelectionItem (const GS::UniString& name = GS::UniString (),
								   const DG::Icon& icon = DG::Icon (),
								   bool status = true,
								   bool boldText = false);
	virtual ~AttributeListSelectionItem ();

	virtual short AddItem (const Item& newItem);
	short	AddSeparator ();
	void	EnableItem (short index);		// 1 based index because of DG
	void	DisableItem (short index);		// 1 based index because of DG
	void	SetItemStatus (short index, bool enabled);		// 1 based index because of DG
	void	SetItemIcon (short index, const DG::Icon& icon);

	short	GetSelected () const;			// 1 based index because of DG
	void	SelectItem (short index);		// 1 based index because of DG
	USize	GetSelectableItemCount (void) const;
	GS::UniString GetSelectedString (void) const;

	GS::Ref<GS::Object>	GetItemData (short index) const;
	void				SetItemData (short index, GS::Ref<GS::Object> data);

	void	DeleteAllItems (void);

	void	Attach (AttributeListSelectionItemObserver& observer);
	void	Detach (AttributeListSelectionItemObserver& observer);
};


// --- AttributeListSelectionItemObserver ------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListSelectionItemObserver : public AttributeListItemObserver
{
	friend class AttributeListSelectionItem;

private:
	VBAL::AttributeListSelectionItemObserver* vbAttributeListSelectionItemObserver;

public:
	AttributeListSelectionItemObserver ();
	virtual ~AttributeListSelectionItemObserver ();

	virtual void SelectionChanged (const AttributeListSelectionItem& source);
};


// --- AttributeListRealItem -----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListRealItem : public AttributeListSelectionItem
{
protected:
	AttributeListRealItem (bool dummy);

public:
	AttributeListRealItem (const GS::UniString& name = GS::UniString (),
							  const DG::Icon& icon = DG::Icon (),
							  double minValue = -DBL_MAX,
							  double maxValue = DBL_MAX,
							  double value = 0.0,
							  bool editable = true,
							  bool status = true,
							  bool boldText = false,
							  const GS::UniString& tagText = GS::UniString ());
	virtual ~AttributeListRealItem ();

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

	void					Attach (AttributeListRealItemObserver& observer);
	void					Detach (AttributeListRealItemObserver& observer);

	virtual bool			HasFocusedEditField (void) override;
};


// --- AttributeListRealItemObserver ---------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListRealItemObserver : virtual public AttributeListSelectionItemObserver
{
	friend class AttributeListRealItem;

private:
	VBAL::AttributeListRealItemObserver* vbAttributeListRealItemObserver;

public:
	AttributeListRealItemObserver ();
	virtual ~AttributeListRealItemObserver ();

	virtual void ValueChanged (const AttributeListRealItem& source);
};


// --- AttributeListLengthItem -----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListLengthItem : public AttributeListRealItem
{
public:
	AttributeListLengthItem (const GS::UniString& name = GS::UniString (),
								const DG::Icon& icon = DG::Icon (),
								double minValue = -DBL_MAX,
								double maxValue = DBL_MAX,
								double value = 0.0,
								bool editable = true,
								bool status = true,
								bool boldText = false,
								const GS::UniString& tagText = GS::UniString ());
	virtual ~AttributeListLengthItem ();
};


// --- AttributeListAreaItem ----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListAreaItem : public AttributeListRealItem
{
public:
	AttributeListAreaItem (const GS::UniString& name = GS::UniString (),
							  const DG::Icon& icon = DG::Icon (),
							  double minValue = -DBL_MAX,
							  double maxValue = DBL_MAX,
							  double value = 0.0,
							  bool editable = true,
							  bool status = true,
							  bool boldText = false,
							  const GS::UniString& tagText = GS::UniString ());
	virtual ~AttributeListAreaItem ();
};


// --- AttributeListVolumeItem --------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListVolumeItem : public AttributeListRealItem
{
public:
	AttributeListVolumeItem (const GS::UniString& name = GS::UniString (),
								const DG::Icon& icon = DG::Icon (),
								double minValue = -DBL_MAX,
								double maxValue = DBL_MAX,
								double value = 0.0,
								bool editable = true,
								bool status = true,
								bool boldText = false,
								const GS::UniString& tagText = GS::UniString ());
	virtual ~AttributeListVolumeItem ();
};


// --- AttributeListAngleItem ------------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListAngleItem : public AttributeListRealItem
{
public:
	AttributeListAngleItem (const GS::UniString& name = GS::UniString (),
							   const DG::Icon& icon = DG::Icon (),
							   double minValue = -DBL_MAX,
							   double maxValue = DBL_MAX,
							   double value = 0.0,
							   bool editable = true,
							   bool status = true,
							   bool boldText = false,
							   const GS::UniString& tagText = GS::UniString ());
	virtual ~AttributeListAngleItem ();
};


// --- AttributeListIntItem -----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListIntItem : public AttributeListRealItem
{
public:
	AttributeListIntItem (const GS::UniString& name = GS::UniString (),
							 const DG::Icon& icon = DG::Icon (),
							 Int32 minValue = -GS::MaxInt32,
							 Int32 maxValue = GS::MaxInt32,
							 Int32 value = 0,
							 bool editable = true,
							 bool status = true,
							 bool boldText = false,
							 const GS::UniString& tagText = GS::UniString ());
	virtual ~AttributeListIntItem ();

	Int32 GetValue (void) const { return (Int32)AttributeListRealItem::GetValue (); }
	void SetValue (Int32 value) { AttributeListRealItem::SetValue ((double)value); }

	Int32 GetMinValue (void) const { return (Int32)AttributeListRealItem::GetMinValue (); }
	void SetMinValue (Int32 minValue) { AttributeListRealItem::SetMinValue (minValue); }

	Int32 GetMaxValue (void) const { return (Int32)AttributeListRealItem::GetMaxValue (); }
	void SetMaxValue (Int32 maxValue) { AttributeListRealItem::SetMaxValue (maxValue); }
};


// --- AttributeListMaterialItem -------------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListMaterialItem : public AttributeListSimpleItem
{
public:
	AttributeListMaterialItem (const GS::UniString& name = GS::UniString (),
								  const DG::Icon& icon = DG::Icon (),
								  ADB::IAttributeSetProvider* attributeSetProvider = nullptr,
								  API_AttributeIndex material = APIInvalidAttributeIndex,
								  bool status = true,
								  bool boldText = false);
	virtual ~AttributeListMaterialItem ();

	API_AttributeIndex			GetMaterial (void) const;
	void						SetMaterial (const API_AttributeIndex& newMat);

	void						SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);

	void						Attach (AttributeListMaterialItemObserver& observer);
	void						Detach (AttributeListMaterialItemObserver& observer);
};


// --- AttributeListMaterialItemObserver -----------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListMaterialItemObserver : public AttributeListItemObserver
{
	friend class AttributeListMaterialItem;

private:
	VBAL::AttributeListMaterialItemObserver* vbAttributeListMaterialItemObserver;

public:
	AttributeListMaterialItemObserver ();
	virtual ~AttributeListMaterialItemObserver ();

	virtual void MaterialChanged (const AttributeListMaterialItem& source);
};


// --- AttributeListBuildingMaterialItem -------------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListBuildingMaterialItem : public AttributeListSimpleItem {
public:
	AttributeListBuildingMaterialItem (const GS::UniString& name = GS::UniString (),
									   const DG::Icon& icon = DG::Icon (),
									   ADB::IAttributeSetProvider* attributeSetProvider = nullptr,
									   API_AttributeIndex material = APIInvalidAttributeIndex,
									   bool status = true,
									   bool boldText = false);
	virtual ~AttributeListBuildingMaterialItem ();

	API_AttributeIndex			GetBuildingMaterial (void) const;
	void						SetBuildingMaterial (const API_AttributeIndex& newMat);

	void						SetAttributeSetProvider (ADB::IAttributeSetProvider* attributeSetProvider);

	void						Attach (AttributeListBuildingMaterialItemObserver& observer);
	void						Detach (AttributeListBuildingMaterialItemObserver& observer);
};

// --- AttributeListBuildingMaterialItemObserver -----------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListBuildingMaterialItemObserver : public AttributeListItemObserver
{
	friend class AttributeListBuildingMaterialItem;

private:
	VBAL::AttributeListBuildingMaterialItemObserver* vbAttributeListBuildingMaterialItemObserver;

public:
	AttributeListBuildingMaterialItemObserver ();
	virtual ~AttributeListBuildingMaterialItemObserver ();

	virtual void BuildingMaterialChanged (const AttributeListBuildingMaterialItem& source);
};

// --- AttributeListTextItem -----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListTextItem : public AttributeListSelectionItem
{
protected:
	AttributeListTextItem (bool dummy);

public:
	AttributeListTextItem (const GS::UniString& name = GS::UniString (),
							  const DG::Icon& icon = DG::Icon (),
							  const GS::UniString& text = GS::UniString (),
							  bool autoCustomHandling = true,
							  bool editable = true,
							  bool valueListEnabled = true,
							  bool status = true,
							  bool boldText = false);
	virtual ~AttributeListTextItem ();

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

	void	Attach (AttributeListTextItemObserver& observer);
	void	Detach (AttributeListTextItemObserver& observer);

	virtual bool HasFocusedEditField (void) override;
};


// --- AttributeListTextItemObserver ---------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListTextItemObserver : virtual public AttributeListSelectionItemObserver
{
	friend class AttributeListTextItem;

private:
	VBAL::AttributeListTextItemObserver* vbAttributeListTextItemObserver;

public:
	AttributeListTextItemObserver ();
	virtual ~AttributeListTextItemObserver ();

	virtual void TextChanged (const AttributeListTextItem& source);
};


// --- AttributeListDictionaryItem -----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListDictionaryItem : public AttributeListSelectionItem
{
protected:
	AttributeListDictionaryItem (bool dummy);

public:
	AttributeListDictionaryItem (const GS::UniString& name = GS::UniString (),
									const DG::Icon& icon = DG::Icon (),
									const GS::UniString& text = GS::UniString (),
									bool status = true,
									bool boldText = false);
	virtual ~AttributeListDictionaryItem ();

	GS::UniString GetText (void) const;
	void	SetText (const GS::UniString& text);

	void	Attach (AttributeListDictionaryItemObserver& observer);
	void	Detach (AttributeListDictionaryItemObserver& observer);

	virtual bool HasFocusedEditField (void) override;
};


// --- AttributeListDictionaryItemObserver ---------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListDictionaryItemObserver : virtual public AttributeListSelectionItemObserver
{
	friend class AttributeListDictionaryItem;

private:
	VBAL::AttributeListDictionaryItemObserver* vbAttributeListDictionaryItemObserver;

public:
	AttributeListDictionaryItemObserver ();
	virtual ~AttributeListDictionaryItemObserver ();

	virtual void TextChanged (const AttributeListDictionaryItem& source);
};


// --- AttributeListTaggedTextItem ----------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListTaggedTextItem : public AttributeListTextItem
{
public:
	AttributeListTaggedTextItem (const GS::UniString& name = GS::UniString (),
									const DG::Icon& icon = DG::Icon (),
									const GS::UniString& text = GS::UniString (),
									bool autoCustomHandling = true,
									bool editable = true,
									bool valueListEnabled = true,
									bool status = true,
									bool boldText = false,
									const GS::UniString& tagText = GS::UniString ());
	virtual ~AttributeListTaggedTextItem ();

	GS::UniString			GetTagText (void) const;
	void					SetTagText (const GS::UniString& tagText);
};


// --- AttributeListSeparatorItem ---------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListSeparatorItem : public AttributeListSimpleItem
{
public:
	AttributeListSeparatorItem ();
	virtual ~AttributeListSeparatorItem ();
};


// --- AttributeListButtonItem -----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListButtonItem : public AttributeListSimpleItem
{
public:
	AttributeListButtonItem (const GS::UniString& name = GS::UniString (),
								const DG::Icon& icon = DG::Icon (),
								const GS::UniString& buttonIcon = GS::UniString (),
								bool status = true,
								bool boldText = false);
	virtual ~AttributeListButtonItem ();

	void	SetButtonText (const GS::UniString& buttonText);
	const	GS::UniString	GetButtonText (void) const;

	void	Attach (AttributeListButtonItemObserver& observer);
	void	Detach (AttributeListButtonItemObserver& observer);
};


// --- AttributeListButtonItemObserver ---------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListButtonItemObserver : public AttributeListItemObserver
{
	friend class AttributeListButtonItem;

private:
	VBAL::AttributeListButtonItemObserver* vbAttributeListButtonItemObserver;

public:
	AttributeListButtonItemObserver ();
	virtual ~AttributeListButtonItemObserver ();

	virtual void ButtonClicked (const AttributeListButtonItem& source);
};


// --- AttributeListIconButtonItem -----------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListIconButtonItem : public AttributeListSimpleItem
{
public:
	AttributeListIconButtonItem (const GS::UniString& name = GS::UniString (),
									const DG::Icon& icon = DG::Icon (),
									const GS::UniString& text = GS::UniString (),
									const GS::UniString& tagText = GS::UniString (),
									const DG::Icon& buttonIcon = DG::Icon (),
									bool status = true,
									bool boldText = false);
	virtual ~AttributeListIconButtonItem ();

	void					SetText (const GS::UniString& text);
	GS::UniString			GetText (void) const;

	void					SetTagText (const GS::UniString& tagText);
	GS::UniString			GetTagText (void) const;

	void					SetButtonIcon (const DG::Icon& buttonIcon);
	DG::Icon				GetButtonIcon (void) const;

	void					SetButtonVisibility (bool visibility);

	void	Attach (AttributeListIconButtonItemObserver& observer);
	void	Detach (AttributeListIconButtonItemObserver& observer);
};


// --- AttributeListIconButtonItemObserver ---------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListIconButtonItemObserver : public AttributeListItemObserver
{
	friend class AttributeListIconButtonItem;

private:
	VBAL::AttributeListIconButtonItemObserver* vbAttributeListIconButtonItemObserver;

public:
	AttributeListIconButtonItemObserver ();
	virtual ~AttributeListIconButtonItemObserver ();

	virtual void ButtonClicked (const AttributeListIconButtonItem& source);
};


// --- AttributeListGroupItem ------------------------------------------------------------------------------------------

class USERINTERFACEAPI_DLL_EXPORT AttributeListGroupItem : public AttributeListItem
{
	friend class AttributeList;
	friend class AttributeListSimpleItem;

private:
	static GS::HashTable<VBAL::AttributeListGroupItem*, AttributeListGroupItem*>	attributeListGroupItemMap;
	GS::Array<AttributeListSimpleItem*>	mItems;

public:
	AttributeListGroupItem ();
	virtual ~AttributeListGroupItem ();

	void AddItem (AttributeListSimpleItem& item);
	void RemoveItem (AttributeListSimpleItem& item);

	void AddMasterItem (AttributeListSimpleItem& item);
	void RemoveMasterItem (void);

	void	Expand ();
	void	Collapse ();

	bool	IsExpanded () const;
	USize	GetSize () const;

	void	ClearGroup (void);
	virtual bool HasFocusedEditField (void) override;
};

}	// namespace UI

}	// namespace ACAPI

#endif
