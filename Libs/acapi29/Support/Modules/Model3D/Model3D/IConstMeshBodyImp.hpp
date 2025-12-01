// *********************************************************************************************************************
// Description:		IConstMeshBody Implementation (delegation)
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	RZ
//
// SG compatible
// *********************************************************************************************************************

#if !defined (ICONSTBODYIMP_HPP)
#define ICONSTBODYIMP_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
// from GSRoot
#include	"Definitions.hpp"

// from Model3D
#include	"Model3D/Model3DExport.h"

// from GSModeler
#include	"Model3D/IConstMeshBody.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace Modeler {
class MeshBody;

class	MODEL3D_DLL_EXPORT IConstMeshBodyImp : public virtual Cut::IConstMeshBody
{
protected:
	const MeshBody*		m_bodyPtr;
protected:
	IConstMeshBodyImp ();

public:

	virtual ULong	GetPolygonCount					() const override;
	virtual ULong	GetPolyNormalCount				() const override;
	virtual ULong	GetPolyEdgeCount				() const override;
	virtual ULong	GetEdgeCount					() const override;
	virtual ULong	GetVertexCount					() const override;
	virtual ULong	GetPolygonTextureParameterCount	() const override;
	virtual bool	IsEmpty							() const override;

	// relative indexing
	virtual	const Modeler::PGON& GetConstPolygon					(UIndex index) const override;
	virtual const Modeler::PolygonAttributes& GetConstPolygonAttributes (UIndex index) const override;
	virtual const Modeler::PolygonId& GetPolygonId					(UIndex index) const override;
	virtual Int32 GetConstPolyEdge									(UIndex index) const override;
	virtual const EDGE&	GetConstEdge								(UIndex index) const override;
	virtual const Modeler::EdgeAttributes& GetConstEdgeAttributes	(UIndex index) const override;
	virtual const Modeler::EdgeId& GetEdgeId						(UIndex index) const override;
	virtual const VERT&	GetConstVertex								(UIndex index) const override;
	virtual const Modeler::VertexId& GetVertexId					(UIndex index) const override;
	virtual bool GetVertexHardFlag									(UIndex index) const override;
	virtual const Vector3D&	GetConstPolyNormal						(UIndex index) const override;
	virtual double GetPolygonTextureParameter						(ULong index) const override;
	virtual void GetPolygonTextureParameters						(ULong index, GS::Array<double>* result) const override;

	IConstMeshBodyImp (const MeshBody* adaptee);

	virtual ~IConstMeshBodyImp ();

	// state related
	virtual const Modeler::MeshBodyLevelAttrs&	GetBodyLevelAttrs () const override;
	virtual ULong				GetStatus (void) const override;
	virtual ULong				GetShadowStatus (void) const override;
	virtual	GSAttributeIndex	GetMaterialIdx (void) const override;
	virtual	short				GetEdgePenIdx (void) const override;
	virtual	short				GetShapeType (void) const override;
	virtual UInt32				GetFatherBind (void) const override;
	
	virtual Wrapping						GetWrapping (void) const override;
	virtual const Modeler::TextureCoordSys&	GetTextureCoordSys () const override;
	virtual Modeler::TextureCoordSys		GetTextureCoordSys (const TRANMAT& tran) const override;

	virtual const Modeler::UserDataContainer*				GetBodyUserDataContainer () const override;

	virtual bool	IsWireBody () const override;
	virtual bool	IsSurfaceBody () const override;
	virtual bool	IsSolidBody () const override;
	virtual bool	IsClosedBody () const override;
	virtual bool	IsCurvedBody () const override;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Modeler

#endif
