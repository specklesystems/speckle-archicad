#ifndef ILEARNINGTOOLTIPCONTROLLER_HPP
#define ILEARNINGTOOLTIPCONTROLLER_HPP
#pragma once

#include "DGDefs.h"
#include "DGUtility.hpp"
#include "Optional.hpp"

namespace LearningContent {

struct TooltipParameters {
	DG::NativeRect				refRect;
	DG::NativeRect				refParentRect;
	GS::UniString				defaultTooltip;
	GS::UniString				helpAnchor;
	GS::Optional<GS::UniString> hotkey;
	GS::Optional<short>			dialId;
	GS::Optional<short>			itemId;
};


class DG_DLL_EXPORT ITooltipController {
public:
	virtual ~ITooltipController ();

	virtual void RequestTooltip (const TooltipParameters& parameters) = 0;
	virtual void HideTooltip (bool forceHide = false) = 0;
	virtual void RefreshStatus () = 0;
};

DG_DLL_EXPORT void SetEnableTooltips (bool enabled);
DG_DLL_EXPORT bool IsTooltipEnabled ();
DG_DLL_EXPORT bool InitTooltips (bool defaultValue);

}	// namespace LearningContent


#endif
