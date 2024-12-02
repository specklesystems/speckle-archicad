#ifndef ICOACHMARKCONTROLLER_HPP
#define ICOACHMARKCONTROLLER_HPP
#pragma once

#include "DGDefs.h"
#include "DGUtility.hpp"

namespace LearningContent {

enum class CoachmarkLocation {
	Center,
	TopLeft,
	TopRight,
	BottomRight,
	BottomLeft
};

class DG_DLL_EXPORT ICoachmarkController {
public:
	virtual ~ICoachmarkController ();

	virtual void ShowCoachmark (const GS::UniString& id, CoachmarkLocation location) = 0;
	virtual void ShowCoachmark (const GS::UniString& id, short leftPos, short topPos) = 0;
};

}	// namespace LearningContent

#endif
