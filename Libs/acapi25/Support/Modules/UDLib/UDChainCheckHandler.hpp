// *****************************************************************************
// File:			UDChainCheckHandler.hpp
//
// Description:		Class implementation for handling two ore more chained Edit Controls behavior (especially resetting the previous values on unchaining)
//
// Project:			
//
// Namespace:		UD
//
// Contact person:	FEn
// *****************************************************************************

#pragma once

#ifndef UDCHAINCHECKHANDLER_HPP
#define UDCHAINCHECKHANDLER_HPP

#include "UDDefinitions.hpp"
//#include "DGModule.hpp"
#include "DGCheckItem.hpp"
#include "UDImprovedTooltip.hpp"

namespace UD {

class ChainCheckHandler;
class ChainCheckHandlerObserver;

class UD_DLL_EXPORT ChainCheckHandler:	public GS::EventSource,
										public DG::CheckItemObserver
{
friend class ChainCheckHandlerObserver;

protected:
	DG::IconPushCheck			chainCheck;
	DG::EditControl*			lastChainedEditControl;

	DG::Icon					chainedIcon;
	DG::Icon					unchainedIcon;

	short						diffBetweenEditAndChainCheckRight;

	short						chainedIconId;
	short						unchainedIconId;

	virtual void CheckItemChanged (const DG::CheckItemChangeEvent& ev) override;

public:
	ChainCheckHandler  (const DG::Panel& panel, short checkItemId, DG::Icon chainedIconIn, DG::Icon unchainedIconIn);
	~ChainCheckHandler ();

	virtual void	ResizeEditControlsIfNeeded		(bool /*resizeCondition*/, short /*resizeDirection = 1*/) { };

	bool			IsInRememberingState			(void)						{ return lastChainedEditControl != nullptr; }
	void			StopRememberLastValue			(void)						{ lastChainedEditControl = nullptr; }

	void			SetChainCheckState				(bool state);
	void			SetChainCheckStatus				(bool status)				{ chainCheck.SetStatus (status); }
	void			SetChainCheckVisibility			(bool visibility)			{ chainCheck.SetVisibility (visibility); }
	void			MoveChainCheck					(short hMove, short vMove)	{ chainCheck.Move (hMove, vMove); }
	bool			IsChainCheckOn					(void) const				{ return chainCheck.IsChecked (); }
};


class UD_DLL_EXPORT ChainCheckHandlerForLengthEdit :	public ChainCheckHandler,
														public DG::RealEditObserver
{
private:
	DG::LengthEdit	lengthEdit1;
	DG::LengthEdit	lengthEdit2;
	double			savedValue;

	virtual void	CheckItemChanged			(const DG::CheckItemChangeEvent& ev) override;
	virtual void	RealEditChanged				(const DG::RealEditChangeEvent& ev) override;
	virtual void	ItemToolTipRequested		(const DG::ItemHelpEvent& ev, GS::UniString* toolTipText) override;

public:
	ChainCheckHandlerForLengthEdit				(const DG::Panel& panel, short checkItemId, short lengthEdit1Id, short lengthEdit2Id, DG::Icon chainedIconIn, DG::Icon unchainedIconIn);
	~ChainCheckHandlerForLengthEdit				();

	void Attach (ChainCheckHandlerObserver& observer);
	void Detach (ChainCheckHandlerObserver& observer);

	void SetUpperLengthEditValue				(double value)		{ lengthEdit1.SetValue (value); }
	void SetLowerLengthEditValue				(double value)		{ lengthEdit2.SetValue (value); }

	bool IsUpperLengthEditVisible				(void)				{ return lengthEdit1.IsVisible (); }
	bool IsLowerLengthEditVisible				(void)				{ return lengthEdit2.IsVisible (); }
	void SetUpperLengthEditVisibility			(bool visibility)	{ lengthEdit1.SetVisibility (visibility); }
	void SetLowerLengthEditVisibility			(bool visibility)	{ lengthEdit2.SetVisibility (visibility); }

	void SetUpperLengthEditStatus				(bool status)		{ lengthEdit1.SetStatus (status); }
	void SetLowerLengthEditStatus				(bool status)		{ lengthEdit2.SetStatus (status); }

	virtual void	ResizeEditControlsIfNeeded	(bool resizeCondition, short resizeDirection = 1) override;
	void			ResizeEditControls			(short hResize);
	void			MoveAndResizeEditControls	(short hMove, short vMove, short hResize, short vResize);

	void ConnectToUpperLengthEditToolTip		(UD::ImprovedTooltip& toolTip);
	void ConnectToLowerLengthEditToolTip		(UD::ImprovedTooltip& toolTip);
};


class /*UD_DLL_EXPORT*/ ChainCheckHandlerObserver : public GS::EventObserver
{
friend class ChainCheckHandler;

private:
	virtual void ChainCheckChanged				(const ChainCheckHandler* /*source*/) { };
};


class UD_DLL_EXPORT ChainCheckHandlerForLengthEditObserver : public ChainCheckHandlerObserver
{
friend class ChainCheckHandlerForLengthEdit;

private:
	virtual void LengthEditChanged							(const ChainCheckHandlerForLengthEdit* /*source*/, short /*controlId*/, double /*value*/)								{ };
	virtual GS::UniString GetToolTipTextForUpperLengthEdit	(void)																													{ return GS::UniString (); }
	virtual GS::UniString GetToolTipTextForLowerLengthEdit	(void)																													{ return GS::UniString (); }
};

}

#endif