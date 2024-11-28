// *********************************************************************************************************************
// File:			UDRollDownDialogs.hpp
//
// Description:		Declaration of rolldown dialog classes
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	BM
//
// SG compatible
// *********************************************************************************************************************

#ifndef	UDROLLDOWNDIALOGS_HPP
#define	UDROLLDOWNDIALOGS_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "UniString.hpp"

#include "DGModule.hpp"

#include "UDDefinitions.hpp"

#include "UDRollDownInterfaces.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace UD {
	class RollDownSurface;
}


namespace UD {

UD_DLL_EXPORT GSResModule GetUDResourceModule (void);


// === Utility functions ===============================================================================================

namespace RollDownDialogs {

UD_DLL_EXPORT void		EnableAnimation (void);
UD_DLL_EXPORT void		DisableAnimation (void);
UD_DLL_EXPORT void		SetAnimationStatus (bool enable);
UD_DLL_EXPORT bool		IsAnimationEnabled (void);

UD_DLL_EXPORT void		EnableAutoPosition (void);
UD_DLL_EXPORT void		DisableAutoPosition (void);
UD_DLL_EXPORT void		SetAutoPositionStatus (bool enable);
UD_DLL_EXPORT bool		IsAutoPositionEnabled (void);

UD_DLL_EXPORT void		SetAnimationSpeed (ULong speed);
UD_DLL_EXPORT ULong		GetAnimationSpeed (void);

}	// namespace RollDownDialogs


// === RollDownModalDialog class =======================================================================================

// --- Declaration -----------------------------------------------------------------------------------------------------

class UD_DLL_EXPORT RollDownModalDialog: public  DG::ModalDialog,
										 public DG::ButtonItemObserver,
										 public DG::PanelObserver
{
private:
	static const short	buttonHeight;

private:
	RollDownSurface*	rollDownSurface;

protected:
	DG::Button*			okButton;
	DG::Button*			cancelButton;

	virtual void		ButtonClicked (const DG::ButtonClickEvent& ev) override;
	virtual	void		PanelChangeRegistrationRequested (const DG::Item* item, bool* allowRegistration) override;
	virtual void 		PanelScaleChanged (const DG::PanelScaleChangeEvent& ev) override;

public:
	RollDownModalDialog (const GS::Guid& guid, const DG::NativePoint* position = nullptr, CaptionType captionType = TopCaption,
						 FrameType frameType = NormalFrame);
	RollDownModalDialog (const GS::UniString& okText, short okWidth, const GS::UniString& cancelText, short cancelWidth, const GS::Guid& guid,
						 const DG::NativePoint* position = nullptr, CaptionType captionType = TopCaption,
						 FrameType frameType = NormalFrame);
   ~RollDownModalDialog ();

	IRollDownSurface*	GetRollDownSurface (void);

	const IRollDownSurface*	GetRollDownSurface (void) const;
};


// === RollDownModelessDialog class ====================================================================================

// --- Declaration -----------------------------------------------------------------------------------------------------

class UD_DLL_EXPORT RollDownModelessDialog: public DG::ModelessDialog
{
private:
	RollDownSurface*	rollDownSurface;

public:
	RollDownModelessDialog (const GS::Guid& guid, const DG::NativePoint* position = nullptr, CloseType closeType = NoClose,
							MinimizeType minimizeType = NoMinimize, MaximizeType maximizeType = NoMaximize,
							CaptionType captionType = TopCaption, FrameType frameType = NormalFrame);
   ~RollDownModelessDialog ();

	IRollDownSurface*	GetRollDownSurface (void);
};


// === RollDownPalette class ===========================================================================================

// --- Declaration -----------------------------------------------------------------------------------------------------

class UD_DLL_EXPORT RollDownPalette: public DG::Palette
{
private:
	RollDownSurface*	rollDownSurface;

public:
	RollDownPalette (const GS::Guid& guid, CloseType closeType = NoClose, CaptionType captionType = TopCaption, FrameType frameType = NormalFrame);
	RollDownPalette (const GS::Guid& guid, const DG::NativePoint* position = nullptr, CloseType closeType = NoClose, CaptionType captionType = TopCaption, FrameType frameType = NormalFrame);
   ~RollDownPalette ();

	IRollDownSurface*	GetRollDownSurface (void);
};

}	// namespace UD

#endif
