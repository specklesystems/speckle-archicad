/*
Public model binary conversion routines
*/

#ifndef	MODELBINARYCONVERSION_HPP
#define	MODELBINARYCONVERSION_HPP

#pragma once

#include	"Model3D/Model3DExport.h"
#include	"Model3D/Model3DPrivExp.h"

#include	"BMX.hpp"


MODEL3D_DLL_EXPORT
GSErr MODEL3D_CALL SwapLP_CalledMacroSection (GS::PlatformSign inplatform, GSHandle syCalledMacroHdl, short syVersion, GS::PlatformSign toplatform);

MODEL3D_DLL_EXPORT
GSErr MODEL3D_CALL FCSwap_BINARYPart (GS::PlatformSign inplatform, GSHandle syBin3DHdl, GS::PlatformSign toplatform);


#endif // MODELBINARYCONVERSION_HPP
