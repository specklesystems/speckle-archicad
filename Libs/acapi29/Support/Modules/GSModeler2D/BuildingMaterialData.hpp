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

// from CADInfrastructure
#include "ADBAttributeIndex.hpp"

namespace Modeler {
	class BuildingMaterialData 
	{
	public: 
		BuildingMaterialData ()
		{
			fillIndex = ADB::InvalidAttributeIndex;
			fillPen = Pen_First;
			fillbkgPen = Pen_Transparent;
		}

		BuildingMaterialData (
			const ADB::AttributeIndex& fillIndex,
			short fillPen,
			short fillbkgPen
		) :
			fillIndex (fillIndex),
			fillPen (fillPen),
			fillbkgPen (fillbkgPen)
		{
		}

		ADB::AttributeIndex fillIndex;
		short fillPen;
		short fillbkgPen;
	};

} //Modeler
#endif
