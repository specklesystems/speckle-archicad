// *********************************************************************************************************************
// Description:		MeshBody Interface
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	RZ
//
// SG compatible
// *********************************************************************************************************************

#if !defined (IMESHBODY_HPP)
#define IMESHBODY_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
// from GSRoot
#include	"Definitions.hpp"

// from Model3D
#include	"Model3D/Model3DExport.h"
#include	"Model3D/model.h"		// EDGE PGON VERT HOTS TEVE

// from Modeler
#include	"Model3D/IConstMeshBody.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

//namespace Modeler {
//	class MeshBody;
//	class PGON;
//}

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace Modeler {
	class UserDataContainer;
}
namespace Cut {

class MODEL3D_CPP_DLL_EXPORT IMeshBody : public virtual IConstMeshBody {

public:
	// relative indexing
	virtual	Modeler::PGON*	GetPolygon	(UIndex index) = 0;
	virtual	EDGE*	GetEdge				(UIndex index) = 0;

	virtual void	SetVertex			(UIndex index, const VERT& newVertex) = 0;
	virtual void	SetVertexId			(UIndex index, const Modeler::VertexId vertexId) = 0;
	virtual void	SetVertexHardFlag	(UIndex index, bool vertexHardFlag) = 0;
	virtual void	SetPolyEdge			(UIndex index, Int32 newPolyEdge) = 0;
	virtual void	SetEdge				(UIndex index, const EDGE& newEdge) = 0;
	virtual void	SetEdgeAttributes	(ULong index,  const Modeler::EdgeAttributes& edgeAttributes) = 0;
	virtual void	SetEdgeId			(UIndex index, const Modeler::EdgeId edgeId) = 0;
	virtual void	SetPolygon			(UIndex index, const Modeler::PGON& newPolygon) = 0;
	virtual void	SetPolygonAttributes (UIndex index, const Modeler::PolygonAttributes& polygonAttributes) = 0;
	virtual void	SetPolygonId		(UIndex index, const Modeler::PolygonId& polygonId) = 0;

	virtual ULong	AddPolygonRec (const Modeler::PGON& pgon, const Modeler::PolygonAttributes& polygonAttributes) = 0;
	virtual ULong	AddPolyEdgeRec (Int32 pedg) = 0;
	virtual ULong	AddEdgeRec (const EDGE& edge, const Modeler::EdgeAttributes& edgeAttributes) = 0;
	virtual ULong	AddVertexRec (const VERT& vert) = 0;
	virtual ULong	AddPolyNormalRec (const Vector3D& vect) = 0;


	virtual Int32	StorePolygon (Int32 iumat, Wrapping tproj, Int32 irtxt, Int32 mpuid, Int32 ivect, Int32 npedg, Int32 *ipedg, const GS::Array<double>* tParams, STATL status) = 0;
	virtual Int32	StorePolyNormal (double x, double y, double z) = 0;
	virtual Int32	StoreEdge (short color, Int32 vert1, Int32 vert2, Int32 pgon1, Int32 pgon2, STATL status, short gmode) = 0;
	virtual Int32	StoreVertex (double x, double y, double z) = 0;

//	virtual	void	SetBounds (const Box3D& newBounds) = 0;
//	virtual	void	SetBounds (const F_Box3D& newBounds) = 0;

	virtual void	Clear () = 0;

	virtual ~IMeshBody ();

	// state related
	virtual void	SetBodyLevelAttrs (const Modeler::MeshBodyLevelAttrs& attrs) = 0;
	virtual	void	SetStatus (ULong status) = 0;
	virtual void	SetSurfaceBody (bool mark = true) = 0;
	virtual	void	SetMaterialIdx (GSAttributeIndex materialIdx) = 0;
	virtual	void	SetEdgePenIdx (short penIdx) = 0;
	virtual void	MergeColor (short penIdx) = 0;
	virtual void	MergeMaterial (Int32 materialIdx) = 0;
	virtual	void	SetShapeType (short shapeType) = 0;
	virtual	void	SetFatherBind (UInt32 bind) = 0;
	virtual void	SetWrapping (Wrapping wrap) = 0;
	virtual void	SetTextureCoordSys (const Modeler::TextureCoordSys& lcs) = 0;
	virtual void	SetBodyUserDataContainer (const Modeler::UserDataContainer* bodyUserDataContainer) = 0;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Cut

#endif
