// *********************************************************************************************************************
// Description:		PointCloud
//
// Module:			GSModeler
// Namespace:		ModelerAPI
// Contact person:	BoB
// *********************************************************************************************************************

#if !defined (MODELPOINTCLOUD_HPP)
#define MODELPOINTCLOUD_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "GSModelerExport.h"
#include "Box3DData.h"
#include "PCMatrix.hpp"
#include "SharedPtr.hpp"
#include "CoordinateSystem.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

class IPointCloudClip;

namespace ModelerAPI {
	class PointCloudRelay;
}

namespace ModelerAPI {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

class GSMODELER_DLL_EXPORT PointCloud {
	friend class PointCloudRelay;

private:
	GS::ConstSharedPtr<ModelerAPI::PointCloudRelay>	relay;

public:
	PointCloud ();
	PointCloud (const PointCloud& other);
	~PointCloud ();

	PointCloud& operator= (const PointCloud& other);
	
	IPointCloudClip*	GetClip () const;
	PC::Matrix			GetDataToTargetCoordSysTransformation (const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
	Box3D				GetBounds (const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------



}	// namespace TPL

#endif // MODELPOINTCLOUD_HPP
