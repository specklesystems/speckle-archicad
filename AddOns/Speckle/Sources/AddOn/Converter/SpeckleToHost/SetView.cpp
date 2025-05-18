#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

void SpeckleToHostConverter::SetView(const std::string& viewName)
{
	API_NavigatorView   view;
	API_NavigatorItem   item = {};
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
		CHECK_ERROR(ACAPI_Navigator_GetNavigatorView(&navItem, &view));
		std::string name = GS::UniString(navItem.uName).ToCStr().Get();
		if (name == viewName)
		{
			auto dbInfo = navItem.db;
			//CHECK_ERROR(ACAPI_Window_ChangeWindow(&dbInfo));
			err = ACAPI_View_GoToView(APIGuidToString(navItem.guid).ToCStr());

			if (err != NoError)
			{
				break;
			}

			break;
		}
	}
}
