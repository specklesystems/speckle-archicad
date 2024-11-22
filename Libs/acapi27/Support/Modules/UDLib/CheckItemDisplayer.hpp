#ifndef CHECKITEM_DISPLAYER_HPP
#define CHECKITEM_DISPLAYER_HPP

#include "Owner.hpp"
#include "Optional.hpp"
#include "HashTable.hpp"
#include "BoolDisplayer.hpp"
#include "DGUtility.hpp"

namespace DG {
	class CheckItem;
	class IconPushCheck;
}

namespace UD {

class UD_DLL_EXPORT CheckItemDisplayer : public BoolDisplayer
{
protected:
	CheckItemDisplayer (DG::CheckItem& checkItem);

public:
	virtual ~CheckItemDisplayer ();
	virtual void SetValue (bool newValue) override final;
	virtual void EnableDisplayer () override final;
	virtual void DisableDisplayer () override final;
private:
	virtual void SetValuePostProcess (bool newValue);

	DG::CheckItem& checkItem;
};

class UD_DLL_EXPORT IconPushCheckDisplayer : public CheckItemDisplayer
{
public:
	class UD_DLL_EXPORT InitData
	{
	public:
		InitData (const DG::Icon& fixIcon);
		InitData (const DG::Icon& checkedStateIcon, const DG::Icon& uncheckedStateIcon);

		bool HasFixIcon () const;
		GS::Optional<DG::Icon> GetFixIcon () const;
		DG::Icon GetCheckedStateIcon () const;
		DG::Icon GetUnCheckedStateIcon () const;

	private:
		bool hasFixIcon;
		DG::Icon checkedStateIcon; 
		DG::Icon uncheckedStateIcon;
	};

	IconPushCheckDisplayer (DG::IconPushCheck& iconPushCheck, const InitData& initData);
	virtual ~IconPushCheckDisplayer ();

private:
	virtual void SetValuePostProcess (bool newValue) override;

	DG::IconPushCheck& iconPushCheck;
	GS::HashTable<bool, DG::Icon> variousIcons;
};

}

#endif