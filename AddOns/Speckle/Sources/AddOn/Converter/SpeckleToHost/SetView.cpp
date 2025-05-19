#include "SpeckleToHostConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"

void SpeckleToHostConverter::SetView(const std::string& viewName)
{
	API_NavigatorItem item = {};
	GS::Array<API_NavigatorItem> items;

	item.itemType = API_PerspectiveNavItem;
	item.mapId = API_PublicViewMap;
	GSErrCode err = ACAPI_Navigator_SearchNavigatorItem(&item, &items);

	if (err != NoError)
	{
		return;
	}

	for (API_NavigatorItem& navItem : items)
	{
		std::string name = GS::UniString(navItem.uName).ToCStr().Get();
		if (name == viewName)
		{
			ACAPI_View_GoToView(APIGuidToString(navItem.guid).ToCStr());
			break;
		}
	}
}
