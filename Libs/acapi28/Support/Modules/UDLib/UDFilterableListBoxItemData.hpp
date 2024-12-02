#ifndef GS_UD_FILTERABLELISTBOXITEMDATA_HPP
#define GS_UD_FILTERABLELISTBOXITEMDATA_HPP
#pragma once

#include <vector>

#include "UDDefinitions.hpp"

#include "DGListBox.hpp"

namespace UD {
class UD_DLL_EXPORT FilterableListBoxItemData {
public:
	enum class Type {
		Normal,
		Separator
	};

	class UD_DLL_EXPORT TabItemData final {
	private:
		GS::UniString							text;
		GS::Optional<DG::Icon>					icon;
		DG::Font::Style							fontStyle = DG::Font::Style::Plain;
		GS::Optional<Gfx::Color>				color;
		GS::Optional<Gfx::Color>				backgroundColor;
		GS::UniString							description;

	public:
		~TabItemData ();

		const GS::UniString&	GetText () const;
		void					SetText (const GS::UniString& newText);

		bool					HasIcon () const;
		DG::Icon				GetIcon () const;
		void					SetIcon (const DG::Icon& newIcon);

		DG::Font::Style			GetFontStyle () const;
		void					SetFontStyle (const DG::Font::Style newStyle);

		bool					HasColor () const;
		Gfx::Color				GetColor () const;
		void					SetColor (Gfx::Color newColor);

		bool					HasBackgroundColor () const;
		Gfx::Color				GetBackgroundColor () const;
		void					SetBackgroundColor (Gfx::Color newColor);

		const GS::UniString&	GetDescription () const;
		void					SetDescription (const GS::UniString& newDescription);
	};

private:
	Type						type = Type::Normal;
	DG::Font::Style				fontStyle = DG::Font::Style::Plain;
	GS::Optional<Gfx::Color>	color;
	GS::Optional<Gfx::Color>	backgroundColor;
	DGUserData					userData = 0;
	GS::Ref<GS::Object>			objectData = nullptr;
	DG::ListBox::ItemStatus		status = DG::ListBox::Enabled;
	bool						ownerDrawFlag = false;
	std::vector<TabItemData>	tabItemDataContainer;

public:
	explicit FilterableListBoxItemData ();
	virtual ~FilterableListBoxItemData ();

	void	SetToSeparator ();
	bool	IsSeparator () const;

	DG::Font::Style		GetFontStyle () const;
	void				SetFontStyle (DG::Font::Style newStyle);

	bool				HasColor () const;
	Gfx::Color			GetColor () const;
	void				SetColor (Gfx::Color newColor);
	void				ClearColor ();

	bool				HasBackgroundColor () const;
	Gfx::Color			GetBackgroundColor () const;
	void				SetBackgroundColor (Gfx::Color newBackgroundColor);
	void				ClearBackgroundColor ();

	DGUserData			GetUserData () const;
	void				SetUserData (DGUserData newUserData);

	const GS::Ref<GS::Object>&	GetObjectData () const;
	void						SetObjectData (GS::Ref<GS::Object> newObjectData);

	DG::ListBox::ItemStatus		GetStatus () const;
	void						SetStatus (DG::ListBox::ItemStatus newStatus);

	bool				GetOwnerDrawFlag () const;
	void				SetOwnerDrawFlag (bool newOwnerDrawFlag);

	void				AllocateTabItems (USize tabItemCount);

	TabItemData&		AccessTabItemValue (UIndex tabItemIndex);
	const TabItemData&	AccessTabItemValue (UIndex tabItemIndex) const;

	void				FillToDGListBox (DG::ListBox& listBox, short listBoxItemIndex) const;

	const std::vector<TabItemData>&	GetAllTabItemData () const;
};

}

#endif
