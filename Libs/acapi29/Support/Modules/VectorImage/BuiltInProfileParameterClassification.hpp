#ifndef BUILTIN_PROFILE_PARAMETER_CLASS_HPP
#define	BUILTIN_PROFILE_PARAMETER_CLASS_HPP

#pragma once

// from VectorImage
#include "VectorImageTypedefs.hpp"
#include "VectorImageExport.h"

namespace PVI {
	VI_DLL_EXPORT bool  VI_CALL DoesHorizontalControl (const ProfileBuiltInParameterId& BIParamID);
	VI_DLL_EXPORT bool  VI_CALL DoesVerticalControl (const ProfileBuiltInParameterId& BIParamID);
	VI_DLL_EXPORT bool  VI_CALL DoesSizeControl (const ProfileBuiltInParameterId& BIParamID);
	VI_DLL_EXPORT bool  VI_CALL DoesPositionControl (const ProfileBuiltInParameterId& BIParamID);
	VI_DLL_EXPORT bool  VI_CALL DoesTotalSizeControl (const ProfileBuiltInParameterId& BIParamID);
	VI_DLL_EXPORT bool  VI_CALL DoesNominalSizeControl (const ProfileBuiltInParameterId& BIParamID);
	VI_DLL_EXPORT bool  VI_CALL DoesStretchSizeControl (const ProfileBuiltInParameterId& BIParamID);
	VI_DLL_EXPORT bool  VI_CALL IsBuiltInProfileParameter (const ProfileParameterId& paramID);
}

#endif
