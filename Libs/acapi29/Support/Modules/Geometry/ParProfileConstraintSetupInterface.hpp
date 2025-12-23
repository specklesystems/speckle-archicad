#ifndef GEOM_PPE_PARPROFILECONSTRAINTSETUPINTERFACE_HPP
#define GEOM_PPE_PARPROFILECONSTRAINTSETUPINTERFACE_HPP

#pragma once
#include "GeometricDefinitions.h"
#include "ModelIDs.hpp"
#include "EdgePosSideIndicatorType.hpp"
#include <vector>

class UserControlValue; 
enum class StretchZoneType;
class PointAnchor;
class GeneralAnchor;
class DimData;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT OneEdgeOffsetData
{
public:
	OneEdgeOffsetData () : edgePosSide (EdgePosSideIndicatorType::Undefined) {}
	OneEdgeOffsetData (EdgeIDType edgeIDInit, EdgePosSideIndicatorType edgePosSideInit) : edgeID (edgeIDInit), edgePosSide (edgePosSideInit) {}

	EdgeIDType					edgeID;
	EdgePosSideIndicatorType	edgePosSide;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::vector<OneEdgeOffsetData> MultiEdgeOffsetData;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT ParProfileConstraintSetupInterface
{
public:
	ParProfileConstraintSetupInterface ();
	virtual ~ParProfileConstraintSetupInterface ();


	virtual void SetVertexLockedToNothing (const VertexIDType vertID) = 0;											//vertex will move
	virtual void SetVertexLockedToGCS (const VertexIDType vertID) = 0;												//vertex will not move
	virtual void SetVertexLockedToStretchCanvas (const VertexIDType vertID) = 0;									//vertex will not move, but only due to stretch
	virtual void SetVertexLockedToVertex (const VertexIDType vertID, const VertexIDType hostVertID) = 0;			//vertex move with host vertex, if that moves
	virtual void SetVertexLockedToEdge (const VertexIDType vertID, const EdgeIDType hostEdgeID) = 0;				//vertex is on the line of edge
	virtual void SetVertexLockedToVertices (const VertexIDType vertID,
											const VertexIDType hostVertID1, const VertexIDType hostVertID2) = 0;	//vertex is half way between two other vertices

	virtual void SetEdgeDirectionLockedToGCS (const EdgeIDType edgeID) = 0;											//edge will not rotate
	virtual void SetEdgeDirectionLockedToStretchCanvas (const EdgeIDType edgeID) = 0;								//edge will not rotate, except due to stretch
	virtual void SetEdgeDirectionLockedToEdge (const EdgeIDType edgeID, const EdgeIDType hostEdgeID) = 0;			//angle locked between the edge and the host edge
	virtual void SetEdgeEdgeAngleLimit (const EdgeIDType edgeID1, const EdgeIDType edgeID2, const UserControlValue& ucv) = 0;
	virtual void UnlockEdgeLength (const EdgeIDType edgeID) = 0;
	virtual void LockEdgeLength (const EdgeIDType edgeID) = 0;
	virtual void LockEdgeEnds (const EdgeIDType edgeID) = 0;
	virtual void UnlockEdgeEnds (const EdgeIDType edgeID) = 0;

	virtual void SetDistanceGCSPointE (const double GCS_x, const double GCS_y, const EdgeIDType edgeID, const UserControlValue& ucv) = 0;
	virtual void SetDistanceVV (const VertexIDType vertID1, const VertexIDType vertID2, const UserControlValue& ucv) = 0;
	virtual void SetDistanceVE (const VertexIDType vertID, const EdgeIDType edgeID, const EdgePosSideIndicatorType edgePosSide, const UserControlValue& ucv) = 0;
	virtual void SetDistanceEV (const EdgeIDType edgeID, const VertexIDType vertID, const EdgePosSideIndicatorType edgePosSide, const UserControlValue& ucv) = 0;							//same as SetDistanceVE
	virtual void SetDistanceEE (const EdgeIDType posEdge, const EdgeIDType negEdge, const EdgePosSideIndicatorType edgePosSideForPosEdge, const UserControlValue& ucv) = 0;							//the two edge should be parallel and should remain so.
	virtual void SetStretchX (const double zone_ll, const double zone_ul, const StretchZoneType& stretchZoneType, const UserControlValue& ucv) = 0;
	virtual void SetStretchY (const double zone_ll, const double zone_ul, const StretchZoneType& stretchZoneType, const UserControlValue& ucv) = 0;
	
	//anchor based size constraints:
	virtual void SetHorizontalSizeConstraint (const UserControlValue& ucv, const PointAnchor& left, const PointAnchor& right) = 0;
	virtual void SetVerticalSizeConstraint (const UserControlValue& ucv, const PointAnchor& bottom, const PointAnchor& top) = 0;
	virtual void SetHorizontalAnchorConstraint (const UserControlValue& ucv, const PointAnchor& anchor) = 0;
	virtual void SetVerticalAnchorConstraint (const UserControlValue& ucv, const PointAnchor& anchor) = 0;

	virtual void SetStretchZoneTopConstraint (const UserControlValue& ucv) = 0;
	virtual void SetStretchZoneBottomConstraint (const UserControlValue& ucv) = 0;
	virtual void SetStretchZoneLeftConstraint (const UserControlValue& ucv) = 0;
	virtual void SetStretchZoneRightConstraint (const UserControlValue& ucv) = 0;

	//Higher level setup (translator)
	virtual void OffsetMultiEdges (
		const MultiEdgeOffsetData offsetData,
		const UserControlValue& offsetValue) = 0;

	virtual void DimControlTool (
		const GeneralAnchor&				anchor1,
		const GeneralAnchor&				anchor2,
		const DimData&						dim,
		const UserControlValue&				distance) = 0;
};

#endif //GEOM_PPE_PARPROFILECONSTRAINTSETUPINTERFACE_HPP
