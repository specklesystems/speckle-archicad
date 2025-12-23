#ifndef SETTINGSCOMBDIALOGSTATE_HPP
#define SETTINGSCOMBDIALOGSTATE_HPP

#pragma once

#include "DialogStateBase.hpp"


namespace UD {

class UD_DLL_EXPORT SettingsCombDialogState : public UD::DialogStateBase {
private:
	DG::NativePoint		position;
	short				listTabPageWidth;
	short				listTabPageHeight;
	bool				listTabPageState;
	short				headerTabPageWidth;
	short				headerTabPageHeight;
	GS::Array<short>	currTabPageWidthArray;
	GS::Array<short>	currTabPageHeightArray;
	GS::Array<bool>		currTabPageExpandedArray;

public:
	SettingsCombDialogState ();

	const DG::NativePoint&	GetPosition (void) const;
	void					SetPosition (const DG::NativePoint& inPosition);

	short	GetListTabPageWidth (void) const;
	void	SetListTabPageWidth (short width);

	short	GetListTabPageHeight (void) const;
	void	SetListTabPageHeight (short height);

	bool	GetListTabPageState (void) const;
	void	SetListTabPageState (bool state);

	short	GetHeaderTabPageWidth (void) const;
	void	SetHeaderTabPageWidth (short width);

	short	GetHeaderTabPageHeight (void) const;
	void	SetHeaderTabPageHeight (short height);

	GS::Array<short>	GetCurrTabPageWidthArray (void) const;
	void				SetCurrTabPageWidthArray (const GS::Array<short>& widthArray);

	GS::Array<short>	GetCurrTabPageHeightArray (void) const;
	void				SetCurrTabPageHeightArray (const GS::Array<short>& heightArray);

	GS::Array<bool>		GetCurrTabPageExpandedArray (void) const;
	void				SetCurrTabPageExpandedArray (const GS::Array<bool>& expandedArray);

	virtual void				Reset () override;

private:
	void						Init (void);

	virtual GS::ErrCode			Read (GS::IChannel& channel) override;
	virtual GS::ErrCode			Write (GS::OChannel& channel) const override;
};

}

#endif //SETTINGSCOMBDIALOGSTATE_HPP
