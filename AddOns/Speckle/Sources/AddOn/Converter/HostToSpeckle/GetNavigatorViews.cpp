#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"

std::vector<NavigatorView> HostToSpeckleConverter::GetNavigatorViews()
{
	std::vector<NavigatorView> navigatorViews;
	API_NavigatorItem   item = {};
	GS::Array<API_NavigatorItem> items;

	item.itemType = API_PerspectiveNavItem;
	item.mapId = API_PublicViewMap;
	GSErrCode err = ACAPI_Navigator_SearchNavigatorItem(&item, &items);

	if (err != NoError)
	{
		return {};
	}

	for (API_NavigatorItem& navItem : items)
	{
		std::string name = GS::UniString(navItem.uName).ToCStr().Get();
		std::string guid = APIGuidToString(navItem.guid).ToCStr().Get();
		navigatorViews.push_back({ name, guid });
	}

	return navigatorViews;
}
