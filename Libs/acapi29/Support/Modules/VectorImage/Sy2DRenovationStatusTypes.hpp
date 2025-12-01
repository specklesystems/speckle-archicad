#ifndef SY2DRENOVATIONSTATUSTYPES_HPP
#define SY2DRENOVATIONSTATUSTYPES_HPP

#pragma once

#include "VectorImageExport.h"

namespace VI {

enum Sy2dRenovationStatusTypes
{
	SyUndefinedRenovationStatus = 0,
	SyExistingRenovationStatus = 1,
	SyNewRenovationStatus = 2,
	SyDemolishedRenovationStatus = 3
};

VI_DLL_CLASS_EXPORT
char	ConvertRenovationStatus_Phasing_To_Sy2D (char phasingRenovationStatus);

VI_DLL_CLASS_EXPORT
char	ConvertRenovationStatus_Sy2D_To_Phasing (char sy2DRenovationStatus);

}

#endif
