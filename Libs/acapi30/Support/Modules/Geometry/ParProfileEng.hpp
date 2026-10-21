#ifndef GEOM_PPE_PARPROFILEENG_HPP
#define GEOM_PPE_PARPROFILEENG_HPP
#pragma once
#include "ModelIDs.hpp"
#include "GeometricDefinitions.h"
#include "OperationReturnStatus.hpp"
#include "SolutionQuality.hpp"
#include <list>
#include <string>
#include <map>

class ParProfileEngSetupInterfaces; 
class ParProfileEngOptions;
class ComputationalModel;
class ActualStretchData;
class PointAnchor;

namespace Geometry
{
	class GenArc;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT ParProfileEng
{
public:
	ParProfileEng ();
	virtual ~ParProfileEng ();

	void					SetOptions (const ParProfileEngOptions& newOptions);
	void					GetSetupInterfaces (ParProfileEngSetupInterfaces& interfaces);

	SolutionQuality			Solve ();
	OperationReturnStatus	UpdateBoundingBox ();
	OperationReturnStatus	CalculateParameterValues (std::map<std::string, double>& valueMap) const;
	OperationReturnStatus	CalculateHorizontalSize (const PointAnchor& begAnchor, const PointAnchor& endAnchor, double& val) const;
	OperationReturnStatus	CalculateHorizontalPos (const PointAnchor& anchor, double& val) const;
	OperationReturnStatus	CalculateVerticalSize (const PointAnchor& begAnchor, const PointAnchor& endAnchor, double& val) const;
	OperationReturnStatus	CalculateVerticalPos (const PointAnchor& anchor, double& val) const;
	OperationReturnStatus	CheckPerturbations (std::list<std::string>& probParIDs);
	OperationReturnStatus	ReportResidualAccuracy (double tolerance);
	OperationReturnStatus	Sweep (const size_t nSolutions, const std::string& sweepName);
	OperationReturnStatus	DumpCurrentGeometry (const std::string& HTMLFileName);
	OperationReturnStatus	TextExportCurrentGeometry (const std::string& fileName);
	OperationReturnStatus	GetVertexCoords (const VertexIDType vertID, double& x, double& y) const;
	OperationReturnStatus	GetEdge (const EdgeIDType edgeID, double& xBeg, double& yBeg, double& xEnd, double& yEnd) const;
	OperationReturnStatus	GetGenArc (const EdgeIDType arcEdgeID, GS::Array<Geometry::GenArc>& edgeArcs, bool& isArc) const;
	OperationReturnStatus	GetActualStretchData (ActualStretchData& actStretch) const;
	OperationReturnStatus	ExportReferenceData (const std::string& fileName);

private: 
	void					SetupGCS ();
	void					SetupDomainCorners ();

	ComputationalModel*		cmpModel;

	int						nextFreeReservedID; 

	int						globalCoordSysOriginVertexID;
	int						globalCoordSysXAxisEdgeID;
	int						globalCoordSysYAxisEdgeID;
};

#endif //GEOM_PPE_PARPROFILEENG_HPP
