#if !defined GS_COMMONUI_TREEDATA_HPP
#define	GS_COMMONUI_TREEDATA_HPP


#include "UDDefinitions.hpp"
#include "DGUtility.hpp"
#include "UniString.hpp"


namespace UD {


class UD_DLL_EXPORT TreeItemDisplayData {
private:
	GS::UniString	text;
	DG::Icon		icon;

public:
	TreeItemDisplayData ();
	virtual ~TreeItemDisplayData ();

	const GS::UniString&	GetText (void) const;
	void					SetText (const GS::UniString& inText);

	const DG::Icon&	GetIcon (void) const;
	void			SetIcon (const DG::Icon& inIcon);
};


class UD_DLL_EXPORT TreeItemData {
private:
	TreeItemDisplayData	displayData;
	UInt32				levelDirection;

public:
	TreeItemData ();
	virtual ~TreeItemData ();

	const TreeItemDisplayData&	GetDisplayData (void) const;
	void						SetDisplayData (const TreeItemDisplayData& inDisplayData);

	UInt32	GetLevelDirection (void) const;
	void	SetLevelDirection (UInt32 inLevelDirection);
};


class UD_DLL_EXPORT TreeData {
private:
	GS::Array<TreeItemData> treeItems;

public:
	static const UIndex NoParentIndex;

	TreeData ();
	virtual ~TreeData ();

	void AddTreeItem (const TreeItemData& treeItemData);

	const TreeItemDisplayData&	GetTreeItemDisplayData (UIndex treeItemIndex) const;
	UIndex						GetTreeItemParent (UIndex treeItemIndex) const;
	UInt32						GetTreeItemLevel (UIndex treeItemIndex) const;
	bool						IsTreeItemLeaf (UIndex treeItemIndex) const;

	USize GetTreeItemCount (void) const;
};


class UD_DLL_EXPORT TreeDataBuilder {
private:
	TreeData&	treeData;
	UInt32		actualLevel;

public:
	TreeDataBuilder (TreeData& treeData);
	virtual ~TreeDataBuilder ();

	void AddTreeItem (const TreeItemDisplayData& treeItemDisplayData);

	void IncrementActualLevel (void);
	void DecrementActualLevel (void);
	void SetActualLevelToFirst (void);
};


} // namespace UD


#endif