#ifndef GS_UD_FILTERABLETREEVIEWITEMDATA_HPP
#define GS_UD_FILTERABLETREEVIEWITEMDATA_HPP
#pragma once

#include "UDDefinitions.hpp"

#include "DGTreeView.hpp"

namespace UD {
class UD_DLL_EXPORT FilterableTreeViewItemData {
private:
	GS::UniString								text;
	GS::Optional<DG::Icon>						normalIcon;
	GS::Optional<DG::Icon>						stateIcon;
	GS::Optional<DG::Icon>						overlayIcon;
	DG::Font::Style								fontStyle = DG::Font::Style::Plain;
	GS::Optional<Gfx::Color>					color;
	DGUserData									userData = 0;
	GS::Ref<GS::Object>							objectData = nullptr;
	DG::TreeView::ItemStatus					status = DG::TreeView::Enabled;
	bool										isExpanded = false;

public:
	virtual ~FilterableTreeViewItemData ();

	const GS::UniString& GetText () const;
	void SetText (const GS::UniString& newText);

	bool HasNormalIcon () const;
	DG::Icon GetNormalIcon () const;
	void SetNormalIcon (const DG::Icon& newIcon);

	bool HasStateIcon () const;
	DG::Icon GetStateIcon () const;
	void SetStateIcon (const DG::Icon& newIcon);

	bool HasOverlayIcon () const;
	DG::Icon GetOverlayIcon () const;
	void SetOverlayIcon (const DG::Icon& newIcon);

	DG::Font::Style GetFontStyle () const;
	void SetFontStyle (const DG::Font::Style newStyle);

	bool HasColor () const;
	const Gfx::Color& GetColor () const;
	void SetColor (const Gfx::Color& newColor);
	void ClearColor ();

	DGUserData GetUserData () const;
	void SetUserData (const DGUserData newUserData);

	const GS::Ref<GS::Object>& GetObjectData () const;
	void SetObjectData (const GS::Ref<GS::Object>& newObjectData);

	DG::TreeView::ItemStatus GetStatus () const;
	void SetStatus (const DG::TreeView::ItemStatus newStatus);

	bool IsExpanded () const;
	void StoreExpandedness ();
	void ClearExpandedness ();

	void FillToDGTreeView (DG::TreeView& treeView, Int32 treeViewItemIndex) const;
};

}

#endif
