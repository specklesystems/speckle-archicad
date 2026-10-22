// *********************************************************************************************************************
// Description:		ConstMeshBody Interface
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	RZ
//
// SG compatible
// *********************************************************************************************************************

#if !defined (ICONSTMESHBODY_HPP)
#define ICONSTMESHBODY_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
// from GSRoot
#include	"Definitions.hpp"
#include	"Array.hpp"

// from Geometry
#include	"TM.h"

#include	"Model3D/Model3DExport.h"

#include	"Model3D/model.h"		// VERT HOTS TEVE
#include	"Model3D/EdgeAttributes.hpp"
#include	"Model3D/PolygonAttributes.hpp"
#include	"Model3D/VertexId.hpp"
#include	"Model3D/EdgeId.hpp"
#include	"Model3D/PolygonId.hpp"
#include	"Model3D/PolygonConvexDecomposition.hpp"
#include	"Model3D/TextureCoordSys.hpp"
#include	"Model3D/BodyLevelAttrs.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace Modeler {
	class UserDataContainer;
}

namespace Cut {

class MODEL3D_CPP_DLL_EXPORT IConstMeshBody {

public:

	bool HasVertices (void) const;
	bool HasEdges (void) const;
	bool HasPolygons (void) const;
	bool HasPolygonTextureParameters (void) const;

	virtual ~IConstMeshBody ();
	
	virtual bool	IsEmpty							() const = 0;

	virtual ULong	GetVertexCount					() const = 0;
	virtual ULong	GetEdgeCount					() const = 0;
	virtual ULong	GetPolygonCount					() const = 0;
	virtual ULong	GetPolygonTextureParameterCount	() const = 0;
	virtual ULong	GetPolyNormalCount				() const = 0;
	virtual ULong	GetPolyEdgeCount				() const = 0;
	
	
	virtual Coord3D GetVertexPoint (ULong index, const TRANMAT& trafo = Geometry::IdentityTranMat) const;
	void	GetVertexCoords (ULong index, const TRANMAT& trafo, double* x, double* y, double* z) const;
	
	// relative indexing
	virtual	const Modeler::PGON&				GetConstPolygon				(UIndex index) const = 0;
	virtual const Modeler::PolygonAttributes&	GetConstPolygonAttributes	(UIndex index) const = 0;
	virtual const Modeler::PolygonId&			GetPolygonId				(UIndex index) const = 0;
	virtual Int32								GetConstPolyEdge			(UIndex index) const = 0;
	virtual const EDGE&							GetConstEdge				(UIndex index) const = 0;
	virtual const Modeler::EdgeAttributes&		GetConstEdgeAttributes		(UIndex index) const = 0;
	virtual const Modeler::EdgeId&				GetEdgeId					(UIndex index) const = 0;
	virtual const VERT&							GetConstVertex				(UIndex index) const = 0;
	virtual const Modeler::VertexId&			GetVertexId					(UIndex index) const = 0;
	virtual bool								GetVertexHardFlag			(UIndex index) const = 0;
	virtual const Vector3D&						GetConstPolyNormal			(UIndex index) const = 0;
	virtual double								GetPolygonTextureParameter	(ULong index) const = 0;
	virtual void								GetPolygonTextureParameters	(ULong index, GS::Array<double>* result) const = 0;
	
	// state related
	virtual const Modeler::MeshBodyLevelAttrs&	GetBodyLevelAttrs () const = 0;
	virtual ULong				GetStatus (void) const = 0;
	virtual ULong				GetShadowStatus (void) const = 0;
	virtual	GSAttributeIndex	GetMaterialIdx (void) const = 0;
	virtual	short				GetEdgePenIdx (void) const = 0;
	virtual	short				GetShapeType (void) const = 0;
	virtual	UInt32				GetFatherBind (void) const = 0;

	virtual Wrapping						GetWrapping (void) const = 0;
	virtual const Modeler::TextureCoordSys&	GetTextureCoordSys () const = 0;
	virtual Modeler::TextureCoordSys		GetTextureCoordSys (const TRANMAT& tran) const = 0;

	virtual const Modeler::UserDataContainer*				GetBodyUserDataContainer () const = 0;
	
	virtual bool	IsWireBody () const = 0;
	virtual bool	IsSurfaceBody () const = 0;
	virtual bool	IsSolidBody () const = 0;
	virtual bool	IsClosedBody () const = 0;
	virtual bool	IsCurvedBody () const = 0;

#if defined(DEBUVERS)
	virtual void	Dump (bool noGeom = false, GS::OChannel& channel = dbChannel) const;
#endif
};

inline	bool IConstMeshBody::HasVertices (void) const
{
	return GetVertexCount () != 0;
}


inline	bool IConstMeshBody::HasEdges (void) const
{
	return GetEdgeCount () != 0;
}


inline	bool IConstMeshBody::HasPolygons (void) const
{
	return GetPolygonCount () != 0;
}


inline	bool IConstMeshBody::HasPolygonTextureParameters (void) const
{
	return GetPolygonTextureParameterCount () != 0;
}

}	// namespace Cut

#endif
