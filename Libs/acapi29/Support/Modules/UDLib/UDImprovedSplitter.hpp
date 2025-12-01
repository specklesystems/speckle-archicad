#ifndef UDIMPROVEDSPLITTER_HPP
#define UDIMPROVEDSPLITTER_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "DGSplitter.hpp"


namespace UD
{

class UD_DLL_EXPORT ImprovedSplitter : public DG::Splitter {
protected:
	DG::Item&					hideableItem;
	GS::Array<DG::Item*>		moveableItems;
	GS::Array<DG::Item*>		moveAndResizeableItems;
	short						splitterDistance;

private:

	bool						hidingIsActive;
public:
	ImprovedSplitter (const DG::Panel& panel, short item, DG::Item& hideableItem);

	virtual ~ImprovedSplitter ();

	void AddMoveableItem (DG::Item& item);

	void AddMoveAndResizeableItem (DG::Item& item);

	void HandleResizeBySplitter (short movement);

	void HandleShowHideBySplitter ();

	bool HidingIsActive () const;

	virtual void SetSplitterDistance () = 0;

	void AdjustSplitterDistance (short adjustment);

	short GetSplitterDistance () const;

private:
	virtual void HideBySplitter () = 0;

	virtual void UnHideBySplitter () = 0;

	virtual void ResizeBySplitter (short movement) = 0;
};


class UD_DLL_EXPORT ImprovedHorizontalSplitter : public ImprovedSplitter {
public:
	ImprovedHorizontalSplitter (const DG::Panel& panel, short item, DG::Item& hideableItem);

	virtual void SetSplitterDistance () override;

private:

	virtual void HideBySplitter () override;

	virtual void UnHideBySplitter () override;

	virtual void ResizeBySplitter (short movement) override;
};

class UD_DLL_EXPORT ImprovedVerticalSplitter : public ImprovedSplitter {
public:
	ImprovedVerticalSplitter (const DG::Panel& panel, short item, DG::Item& hideableItem);

	virtual void SetSplitterDistance () override;

private:

	virtual void HideBySplitter () override;

	virtual void UnHideBySplitter () override;

	virtual void ResizeBySplitter (short movement) override;
};

}


#endif //UDIMPROVEDSPLITTER_HPP
