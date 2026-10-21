#ifndef _UDDIALOGRESIZER_H_
#define _UDDIALOGRESIZER_H_

#pragma  once

#include "UDDefinitions.hpp"

namespace DG {
class TabPage;
}

namespace UD {

class UD_DLL_EXPORT DialogResizer {

public:

	DialogResizer ();
	~DialogResizer ();

	//-----
	// Setting functions, call usually in DG_MSG_INIT only at first start of dialog
	//-----

	// set the dialog id
	void	SetDialogId (short dialogId, bool resizeWithDialog = true);

	// add an item to adjust list and specify the growing and resizing quantities relative to change of dialog size
	void	AddAdjustableItem (short itemId, double moveXRratio, double moveYRratio, double sizeXRratio, double sizeYRratio);

	//-----
	// Adjusting function, call at start of processing DG_MSG_GROW and in DG_MSG_INIT after first start of dialog
	// if dxGrow, dyGrow set then don't compute the grow
	//-----
	void	AdjustItems (bool embedMove = false, short *dxGrow = nullptr, short *dyGrow = nullptr);

	// Refresh the size specified element
	void	RefreshAdjustableItem (short itemId, bool grow);

	// gets the dialogs grow from original
	void	GetGrow (short *dxGrow, short *dyGrow);

	DG::TabPage	*tabPage;
private:

	short	dialId;
	bool	resizeWithDialog;
	short	dialOrigXSize;
	short	dialOrigYSize;

	struct TItemAdjustSpec
	{
		short	itemId;
		short	origXPos;
		short	origYPos;
		short	origXSize;
		short	origYSize;
		short	curXPos;
		short	curYPos;
		short	curXSize;
		short	curYSize;
		double	moveXRratio;
		double	moveYRratio;
		double	sizeXRratio;
		double	sizeYRratio;
	};

	GS::HashTable<short, TItemAdjustSpec>	*adjustableItems;

};

}


#endif	// _UDDIALOGRESIZER_H_
