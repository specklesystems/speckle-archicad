#ifndef UDIMPROVEDTOOLTIP_HPP
#define UDIMPROVEDTOOLTIP_HPP


#include "UDDefinitions.hpp"
#include "UDItemInfoTag.hpp"


namespace UD {


class UD_DLL_EXPORT ImprovedTooltip : public UD::ItemInfoTag::ItemDecorator
{
public:
	void AddRow (const GS::UniString& contentType, const GS::UniString& text);
	void ClearRowArray ();

private:
	virtual short GetItemFromPosition (const DG::Point& position) const override;
	virtual DG::Rect GetSubItemRect (short subItem) const override;
	virtual ItemInfoTag::InfoTagContentCreator::MenuItemRowArray CreateMenuItemRowArray (short listItem) const override;

	ItemInfoTag::InfoTagContentCreator::MenuItemRowArray rowArray;
};


} // namespace UD


#endif