#ifndef GEOM_PPE_PROFILEMODELSETUPINTERFACE_HPP
#define GEOM_PPE_PROFILEMODELSETUPINTERFACE_HPP
#pragma once
#include "GeometricDefinitions.h"
#include "ModelIDs.hpp"
#include "OperationReturnStatus.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class EdgeTypeIndicator
{
	NothingSet = 0,
	ProfileGeometry = 1,
	Clone = 2,
	Auxiliary = 3,
	GCS = 4
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class VertexTypeIndicator
{
	NothingSet = 0,
	ProfileGeometry = 1,
	Clone = 2,
	Auxiliary = 3
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT ProfileModelSetupInterface
{
public:
	ProfileModelSetupInterface ();
	virtual ~ProfileModelSetupInterface ();

	virtual void AddNewVertex (const VertexIDType VertexIDType, const double x, const double y, const VertexTypeIndicator vType = VertexTypeIndicator::ProfileGeometry) = 0;
	virtual void AddNewEdge (const EdgeIDType edgeID, const VertexIDType begVertID, const VertexIDType endVertID, const EdgeTypeIndicator eType = EdgeTypeIndicator::NothingSet) = 0;
	virtual void SetEdgeArcData (const EdgeIDType edgeID, const double origX, const double origY, const bool clockwiseArc) = 0;
	virtual void SetZeroLenEdgeData (const EdgeIDType edgeID, const double tangX, const double tangY) = 0;

	virtual void AddNewAuxiliaryVertex (const double x, const double y, VertexIDType& vertID) = 0;
	virtual OperationReturnStatus CloneEdge (const EdgeIDType edgeID, EdgeIDType& newEdgeID, VertexIDType& newBegVertID, VertexIDType& newEndVertID) = 0;
};

#endif //GEOM_PPE_PROFILEMODELSETUPINTERFACE_HPP
