#ifndef ICOACHMARKCONTROLLER_HPP
#define ICOACHMARKCONTROLLER_HPP
#pragma once

#include "DGDefs.h"
#include "DGUtility.hpp"

namespace LearningContent {

enum class CoachmarkSource {
	Tooltip,
	LearningCenter,
	SampleFile
};

class DG_DLL_EXPORT ICoachmarkController {
public:
	virtual ~ICoachmarkController ();

	virtual void ShowCoachmark (const GS::UniString& id, CoachmarkSource source) = 0;
	virtual void ShowCoachmark (const GS::UniString& id, short leftPos, short topPos, CoachmarkSource source) = 0;
};

}	// namespace LearningContent

#endif
