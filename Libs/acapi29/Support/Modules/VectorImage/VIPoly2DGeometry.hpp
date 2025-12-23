#ifndef	VIPOLY2DGEOMETRY_HPP
#define	VIPOLY2DGEOMETRY_HPP

#pragma once

//from GSRoot
#include "HashTable.hpp"

//from Geometry
#include "Poly2DTypes.hpp"

// from VectorImage
#include "VectorImageExport.h"
#include "GeomElemIDDescendencyMap.hpp"
#include "VI2DGeometryInterface.hpp"

class ReIDMapCollector;
class VectorImage;
class VIMultiPoly2D; 
typedef GS::HashTable<GS::Guid, VIMultiPoly2D*>			VIMultiPoly2DMap;

class VI_DLL_CLASS_EXPORT VIPoly2DGeometry : public VI2DGeometryInterface
{
public:
	VIPoly2DGeometry ();
	VIPoly2DGeometry (const VIPoly2DGeometry& source);
	virtual ~VIPoly2DGeometry ();

	//manage: 
	void											Initialize (const VectorImage* originalVectorImageInit);
	void											Clear ();

	//access geometry:
	const Sy_HatchType*								GetOriginalSy_HatchType (const GS::Guid& currentPolyId) const;

	//VI2DGeometryInterface:
	virtual void									AddNewPoly (GS::Friend<VectorImage>, const GS::Guid& polyGUID, VIMultiPoly2D* newPoly, const Sy_HatchType* hatchType) override; //ownership of newPoly is passed here! 
	virtual VI2DGeometryInterface::Iterator			Begin () override;
	virtual VI2DGeometryInterface::Iterator			End () override;
	virtual VI2DGeometryInterface::ConstIterator	BeginConst () const override;
	virtual VI2DGeometryInterface::ConstIterator	EndConst () const override;
	virtual IGeomElemIDResolverPtr					GetGeomElemIDResolver () override;
	virtual void									GetOriginalHatchObject (const GS::Guid& polyGuid, HatchObject& emptyHatchObj) const override;
	virtual const GeomElemIDDescendencyMap&			GetEdgeDescendants () const override { return edgeDescendants; }
	virtual const GeomElemIDDescendencyMap&			GetVertexDescendants () const override { return vertexDescendants; }

	void											AddEdgeMarker (const GeomElemID marker);
	void											GetRootEdgeMarker (const GeomElemID currentID, GeomElemID& rootMarker);
	virtual void									MakeAllMarkersUnique () override;	//Each edge or vertex gets a marker that is unique, therefore may be used as ID!
	virtual void									GetNewVectorImage (VectorImage& newVI, const VI::HatchGeometryPriority::HatchGeometryPriorityComparer& comparer) override;

	virtual GS::Array<VI2DGeometryInterface::Iterator>		GetPriorityOrderedPolys (const VI::HatchGeometryPriority::HatchGeometryPriorityComparer& comparer) override;
	virtual GS::Array<VI2DGeometryInterface::ConstIterator>	GetConstPriorityOrderedPolys (const VI::HatchGeometryPriority::HatchGeometryPriorityComparer& comparer) const override;
private:
	void											RenumberOnePoly (Geometry::IrregularPolygon2D& poly, const GS::Guid& oldPolyID, const GS::Guid& newPolyID, UInt32& currVertMarker, UInt32& currEdgeMarker, ReIDMapCollector& reID);
	void											SeparateMultiPolys ();

	class MyGeomElemIDResolver;																			 

	const VectorImage*								originalVectorImage;
	VIMultiPoly2DMap								hatchPolygons;

	GeomElemIDDescendencyMap						edgeDescendants;
	GeomElemIDDescendencyMap						vertexDescendants;
	GS::HashTable<GS::Guid, GS::Guid>				currentGUIDToRootGUID;
	GS::HashTable<GS::Guid, const Sy_HatchType*>	rootGUIDToSy_HatchType;
};


#endif //VIPOLY2DGEOMETRY_HPP
