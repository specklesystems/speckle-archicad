#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"
#include "ElementTypeToStringConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

std::vector<NavigatorView> HostToSpeckleConverter::GetNavigatorViews()
{
	std::vector<NavigatorView> navigatorViews;

	//API_NavigatorView   view;
	//API_NavigatorItem   parent;
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
		//err = ACAPI_Navigator_GetNavigatorView(&navItem, &view);
		//auto dbi = navItem.db;
		std::string name = GS::UniString(navItem.uName).ToCStr().Get();
		std::string guid = APIGuidToString(navItem.guid).ToCStr().Get();
		navigatorViews.push_back({ name, guid });
	}

	return navigatorViews;
}
