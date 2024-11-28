// *********************************************************************************************************************
// Description:		BuildingMaterialData
//
// Module:			GSModeler2D
// Namespace:		Modeler
// Contact person:	AACS
//
// SG compatible
// *********************************************************************************************************************

#if !defined (BuildingMaterialData_HPP)
#define BuildingMaterialData_HPP

#pragma once

#include "GSUtilsDefs.h"

namespace Modeler {
	class BuildingMaterialData 
	{
	public: 
		BuildingMaterialData ()
		{
			fillIndex = Fill_Missing;
			fillPen = Pen_First;
			fillbkgPen = Pen_Transparent;
		}

		BuildingMaterialData (
			GSAttributeIndex fillIndex,
			short fillPen,
			short fillbkgPen
		) :
			fillIndex (fillIndex),
			fillPen (fillPen),
			fillbkgPen (fillbkgPen)
		{
		}

		GSAttributeIndex fillIndex;
		short fillPen;
		short fillbkgPen;
	};

} //Modeler
#endif
