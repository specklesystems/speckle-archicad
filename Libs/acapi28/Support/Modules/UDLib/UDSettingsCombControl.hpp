#ifndef UDSETTINGSCOMBCONTROL_HPP
#define UDSETTINGSCOMBCONTROL_HPP

#pragma once

#include	"UniString.hpp"
#include	"Ref.hpp"
#include	"UDDefinitions.hpp"
#include	"DGItemProperty.hpp"

namespace UD {

class SettingsCombListTabPage;
class SettingsCombHeaderTabPage;
class ISettingsCombCurrTabPage;

class UD_DLL_EXPORT SettingsCombControl {

	friend class SettingsCombMainDialog;
	friend class SettingsCombListTabPage;
	friend class SettingsCombHeaderTabPage;
	friend class ISettingsCombCurrTabPage;

public:
	enum DeleteBehaviour {
		KeepAtLeastOneElement,
		AllowToDeleteAllElements
	};


	explicit SettingsCombControl (DeleteBehaviour deleteBehaviour = KeepAtLeastOneElement);

	virtual ~SettingsCombControl ();

	virtual GS::UniString	GetName (const GS::Ref<GS::Object>& obj)	const										= 0;
	virtual void			SetName (GS::Ref<GS::Object> obj, const GS::UniString& name)							= 0;
	virtual bool			GoodName (const GS::UniString& name, const GS::UniString& initialText)	const			= 0;
	virtual bool			UniqueGoodName (const GS::UniString& name, const GS::UniString& initialText)	const	= 0;
	virtual GS::UniString	GetHelpAnchor () const;

	virtual short			GetNameColumnId () const { return 1; };

	virtual void			SaveItemsToSelect (const GS::Array<GS::Ref<GS::Object>>& itemsToSelect) const			= 0;
	virtual GS::Array<GS::Ref<GS::Object>> GetSavedItemsToSelect () const											= 0;

	virtual void			CommitChange (const GS::Ref<GS::Object>& obj);

	virtual bool			IsObjectModifiableOrDeletable (const GS::Ref<GS::Object>& obj) const;

	virtual DG::Font::Style	GetItemFontStyle (const GS::Ref<GS::Object>& obj) const;

	virtual DG::Icon		GetHeaderIcon () const;

	virtual DG::Icon		GetItemIcon (const GS::Ref<GS::Object>& obj) const;

	virtual DG::Icon		GetHoverIcon () const;
	virtual float			GetHoverIconAlpha () const;
	
	virtual void			ListBoxSelectionChanged ();
	virtual void			ListBoxDoubleClicked (const GS::Ref<GS::Object>& /*obj*/);

	virtual void			SortListBoxObjects (GS::Array<GS::Ref<GS::Object>>& setsCombRefArr, bool ascending) const;

	virtual bool			IsExcludedFromFiltering (const GS::Ref<GS::Object>& obj) const;

	virtual GS::UniString	GetSearchHintText () const = 0;
	virtual GS::UniString	GetSearchToolTipText () const = 0;

	void NameChanged ();

	void SetRights (bool createRight, bool deleteModifyRight);

	bool HasCreateRight () const;

	bool HasDeleteModifyRight () const;

	UIndex GetItemIndex (const GS::Ref<GS::Object>& obj) const;

	virtual GS::Ref<GS::Object>				NewButtonClicked	(const GS::Ref<GS::Object>& objectToCopy);
	virtual bool							DeleteButtonClicked (GS::Array<GS::Ref<GS::Object>>& objectsToDelete);
	virtual void							ExportButtonClicked (const GS::Array<GS::Ref<GS::Object>>& objectsToExport);
	virtual bool							ImportButtonClicked (GS::Array<GS::Ref<GS::Object>>& importedObjects, GS::Array<GS::Ref<GS::Object>>& overridenObjects);

	DeleteBehaviour							GetDeleteBehaviour () const;

protected:
	void EnumerateListBoxElements (const std::function<void (const GS::Ref<GS::Object>&)>& fn) const;

	SettingsCombListTabPage*				listTabPage;
	SettingsCombHeaderTabPage*				headerTabPage;
	GS::Array<ISettingsCombCurrTabPage*>	curTabPageArray;

	bool						hasCreateRight;
	bool						hasDeleteModifyRight;

	DeleteBehaviour				deleteBehaviour;
};

} //namespace UD


#endif
