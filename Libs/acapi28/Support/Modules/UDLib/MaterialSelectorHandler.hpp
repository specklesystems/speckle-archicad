#pragma once

#include "UCModule.hpp"
#include "MaterialChangeObserver.hpp"
#include "UserControlDisplayer.hpp"
#include "DisplayerRefresherOwner.hpp"

namespace UD {

class UD_DLL_EXPORT MaterialSelectorHandler
{
public:
	MaterialSelectorHandler (
		const DG::Panel& panel,
		short itemId,
		GS::Owner<DisplayerRefresher<UserControlDisplayer>> changeObserver,
		GS::Owner<MaterialValueApplier> editApplier,
		std::function<void(UserControlDisplayer& displayer)> displayInitializer
	);
	virtual ~MaterialSelectorHandler ();

	void SetUserData (const void* userData);
	void SetCallBack (const UC257CallBack callBack);
	void Resize (short hGrow, short vGrow);
	short GetWidth () const;

private:
	GS::Owner<UC::UC257>							materialSelector;
	GS::OnHeap<MaterialChangeObserver>				materialChangeObserver;
	DisplayerRefresherOwner<UserControlDisplayer>	displayerRefresherOwner;
};


} // namespace UD
