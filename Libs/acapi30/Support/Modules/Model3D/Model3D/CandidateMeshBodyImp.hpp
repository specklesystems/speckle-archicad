// *********************************************************************************************************************
// Description:		Implementation of inline functions of MeshBody.hpp
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_CANDIDATEMESHBODYIMP_HPP)
#define GS_MODELER_CANDIDATEMESHBODYIMP_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include <math.h>

// from GSRoot

// from Geometry
#include "RealNumber.h"

// from Modeler

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function definitions --------------------------------------------------------------------------------------------

// =====================================================================================================================
//
// MeshBody
//
// =====================================================================================================================

inline bool		Modeler::CandidateMeshBody::HasStatusMask (STATL flags) const
{
	/*DBASSERT (HAS_ONLY_FLAGS (m_status, Body::ValidStatusFlags));
	DBASSERT (HAS_ONLY_FLAGS (flags, Body::ValidStatusFlags));*/

	return HAS_ANY_FLAGS (m_status, flags);
}


inline void		Modeler::CandidateMeshBody::SetStatusMask (STATL flags)
{
	/*DBASSERT (HAS_ONLY_FLAGS (m_status, Body::ValidStatusFlags));
	DBASSERT (HAS_ONLY_FLAGS (flags, Body::ValidStatusFlags));*/

	SET_FLAGS (m_status, flags);
}


inline void		Modeler::CandidateMeshBody::ClrStatusMask (STATL flags)
{
	CLR_FLAGS (m_status, flags);
}


inline void		Modeler::CandidateMeshBody::SetOrClrStatusMask (STATL flags, bool set)
{
	if (set)
		SetStatusMask (flags);
	else
		ClrStatusMask (flags);
}


inline void		Modeler::CandidateMeshBody::SetStatus (STATL flags)
{
	/*DBASSERT (HAS_ONLY_FLAGS (flags, MeshBody::ValidStatusFlags));*/

	m_status = flags;
}

inline void		Modeler::CandidateMeshBody::SetShadowStatus	(STATL status)
{
	// better do nothing if non-shadow flags are tried to be set
	if (!DBVERIFY (HAS_ONLY_FLAGS (status, MeshBody::ShadowStatusFlags)))
		return;

	ClrStatusMask (MeshBody::ShadowStatusFlags);
	SetStatusMask (status);
}


inline void		Modeler::CandidateMeshBody::MergeDefShadowStatus (STATL defShadowStatus)
{
	STATL actShadowStatus = GetShadowStatus ();

	STATL receiveShadow = (defShadowStatus & MeshBody::ShadowNot) | (actShadowStatus & MeshBody::ShadowNot);
	STATL res = receiveShadow;

	if (defShadowStatus & MeshBody::ShadowOn)
		res |= MeshBody::ShadowOn;
	else if (defShadowStatus & MeshBody::ShadowOff)
		res |= MeshBody::ShadowOff;
	else
		res |= actShadowStatus;

	SetShadowStatus (res);
}


inline bool		Modeler::CandidateMeshBody::IsWireBody (void) const
{
	return HasEdges () && !HasPolygons ();		// empty body is not wireframe
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline bool		Modeler::CandidateMeshBody::IsSurfaceBody (void) const
{
	return !IsWireBody () && HasStatusMask (MeshBody::SurfaceBody);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline bool		Modeler::CandidateMeshBody::IsSolidBody (void) const
{
	return !IsWireBody () && !HasStatusMask (MeshBody::SurfaceBody);		// If solid, it is assumed to be closed also
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------


// If all edges have two polygons attached
inline bool		Modeler::CandidateMeshBody::IsClosedBody (void) const
{
	return HasStatusMask (MeshBody::ClosedBody);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline bool		Modeler::CandidateMeshBody::IsCurvedBody (void) const
{
	return HasStatusMask (MeshBody::CurvedBody);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline bool		Modeler::CandidateMeshBody::IsCutBody (void) const
{
	return HasStatusMask (MeshBody::CutBody);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline bool		Modeler::CandidateMeshBody::IsShadowBody (void) const
{
	return HasStatusMask (MeshBody::ShadowBody);
}


// -----------------------------------------------------------------------------
// 
// -----------------------------------------------------------------------------

inline bool		Modeler::CandidateMeshBody::HasSharpEdge (void) const
{
	return HasStatusMask (MeshBody::SharpEdgeBody);
}

inline bool		Modeler::CandidateMeshBody::AlwaysCastsShadow (void) const			// pcs 2003.02.24 TT#22361
{
	return HasStatusMask (MeshBody::ShadowOn);
}

inline bool		Modeler::CandidateMeshBody::NeverCastsShadow (void) const
{
	return HasStatusMask (MeshBody::ShadowOff) && !HasStatusMask (MeshBody::ShadowOn);
}

inline bool		Modeler::CandidateMeshBody::AutoCastsShadow (void) const
{
	return !HasStatusMask (MeshBody::ShadowOff) && !HasStatusMask (MeshBody::ShadowOn);
}

inline bool		Modeler::CandidateMeshBody::DoesNotReceiveShadow (void) const
{
	return HasStatusMask (MeshBody::ShadowNot);
}

// ---------------------------------------------------------------------------------------------------------------------
// Status setters
// ---------------------------------------------------------------------------------------------------------------------

inline void		Modeler::CandidateMeshBody::SetClosedBody (void)
{
	SetStatusMask (MeshBody::ClosedBody);
}

inline void		Modeler::CandidateMeshBody::SetOpenBody (void)
{
	ClrStatusMask (MeshBody::ClosedBody);
	SetStatusMask (MeshBody::SurfaceBody);	// consistency: if the body is not closed, Surface must always be set
}

inline void		Modeler::CandidateMeshBody::SetSurfaceBody (bool mark /* = true */)
{
	SetOrClrStatusMask (MeshBody::SurfaceBody, mark);
}

inline void		Modeler::CandidateMeshBody::SetCurvedBody (void)
{
	SetStatusMask (MeshBody::CurvedBody);
}

inline void		Modeler::CandidateMeshBody::SetSharpEdgeBody (void)
{
	SetStatusMask (MeshBody::SharpEdgeBody);
}

inline void		Modeler::CandidateMeshBody::SetCutBody (void)
{
	SetStatusMask (MeshBody::CutBody);
}

inline void		Modeler::CandidateMeshBody::SetShadowBody (bool mark /* = true */)
{
	SetOrClrStatusMask (MeshBody::ShadowBody, mark);
}

inline void		Modeler::CandidateMeshBody::SetReceivesShadow (void)
{
	ClrStatusMask (MeshBody::ShadowNot);
}

inline void		Modeler::CandidateMeshBody::SetDoesNotReceiveShadow (void)
{
	SetStatusMask (MeshBody::ShadowNot);
}

inline void		Modeler::CandidateMeshBody::SetAlwaysCastsShadow (void)
{
	SetStatusMask (MeshBody::ShadowOn);
	ClrStatusMask (MeshBody::ShadowOff);
}

inline void		Modeler::CandidateMeshBody::SetNeverCastsShadow (void)
{
	ClrStatusMask (MeshBody::ShadowOn);
	SetStatusMask (MeshBody::ShadowOff);
}

inline void		Modeler::CandidateMeshBody::SetAutoCastsShadow (void)
{
	ClrStatusMask (MeshBody::ShadowOn);
	ClrStatusMask (MeshBody::ShadowOff);
}


// ---------------------------------------------------------------------------------------------------------------------
// Set the body's material index to the given @materialIdx if no valid material index is currently set. Otherwise do nothing.
// ---------------------------------------------------------------------------------------------------------------------
inline void		Modeler::CandidateMeshBody::MergeMaterial (Int32 materialIdx)
{
	if (GetMaterialIdx () <= 0)
	{
		SetMaterialIdx (materialIdx);
	}
}


// ---------------------------------------------------------------------------------------------------------------------
// Set the body's edge pen index to the given @penIdx if no valid pen index is currently set. Otherwise do nothing.
// ---------------------------------------------------------------------------------------------------------------------
inline void		Modeler::CandidateMeshBody::MergeColor (short penIdx)
{
	if (GetEdgePenIdx() <= 0)
	{
		SetEdgePenIdx (penIdx);
	}
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void Modeler::CandidateMeshBody::SetTextureCoordSys (const Modeler::TextureCoordSys& tcs)
{
	m_attrs.textureCoordSys = tcs;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void Modeler::CandidateMeshBody::SetTextureCoordSys (const Coord3D& origin, const Coord3D& endOfX, const Coord3D& endOfY, const Coord3D& endOfZ)
{
	m_attrs.textureCoordSys.origin = origin;
	m_attrs.textureCoordSys.pointX = endOfX;
	m_attrs.textureCoordSys.pointY = endOfY;
	m_attrs.textureCoordSys.pointZ = endOfZ;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline const Modeler::TextureCoordSys& Modeler::CandidateMeshBody::GetTextureCoordSys () const
{
	return m_attrs.textureCoordSys;
}


//inline bool Modeler::CandidateMeshBody::OnlyRefersToGeometry (void) const
//{
//	bool isRepeatedTopo = (m_status & TOPOBIT) > 0;  // if TOPO set, it is a reference, not a real ownership
//	bool isFirstTopo = (m_status & FTOPOBIT) > 0;
//	bool onlyRefersToGeometry = isRepeatedTopo && !isFirstTopo;
//
//	return onlyRefersToGeometry;
//}

inline bool Modeler::CandidateMeshBody::HasPolygons () const
{
	return m_meshBrep.GetPolygonCount () > 0;
}


inline ULong Modeler::CandidateMeshBody::GetPolygonCount () const
{
	return m_meshBrep.GetPolygonCount ();
}

inline bool Modeler::CandidateMeshBody::HasPolyNormals () const
{
	return m_meshBrep.GetPolyNormalCount () > 0;
}


inline ULong Modeler::CandidateMeshBody::GetPolyNormalCount () const
{
	return m_meshBrep.GetPolyNormalCount ();
}

inline bool Modeler::CandidateMeshBody::HasPolyEdges () const
{
	return m_meshBrep.GetPolyEdgeCount () > 0;
}

inline ULong Modeler::CandidateMeshBody::GetPolyEdgeCount () const
{
	return m_meshBrep.GetPolyEdgeCount ();
}

inline bool Modeler::CandidateMeshBody::HasEdges () const
{
	return m_meshBrep.GetEdgeCount () > 0;
}


inline ULong Modeler::CandidateMeshBody::GetEdgeCount () const
{
	return m_meshBrep.GetEdgeCount ();
}

inline const Modeler::EdgeAttributes& Modeler::CandidateMeshBody::GetConstEdgeAttributes (ULong index) const
{
	return m_edgeData[index].edgeAttributes;
}

inline void Modeler::CandidateMeshBody::SetEdgeAttributes (ULong index, const EdgeAttributes& edgeAttributes)
{
	m_edgeData[index].edgeAttributes = edgeAttributes;
}

inline bool Modeler::CandidateMeshBody::HasVertices () const
{
	return m_meshBrep.GetVertexCount () > 0;
}

inline ULong Modeler::CandidateMeshBody::GetVertexCount () const
{
	return m_meshBrep.GetVertexCount ();
}

inline bool Modeler::CandidateMeshBody::HasPolygonTextureParameters () const
{
	return m_textureParams.GetSize () > 0;
}

inline ULong Modeler::CandidateMeshBody::GetPolygonTextureParameterCount () const
{
	return m_textureParams.GetSize ();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline const F_Box3D&	Modeler::CandidateMeshBody::GetLocalBounds (void) const 
{
	return m_meshBrep.GetLocalBounds ();
}

inline Modeler::CandidateMeshBody&		Modeler::CandidateMeshBody::operator= (const Modeler::CandidateMeshBody& src)
{
	if (this == &src) {
		return *this;
	}

	m_status	= src.m_status;
	m_attrs		= src.GetBodyLevelAttrs();
	
	m_meshBrep						= src.m_meshBrep;
	m_vertexData					= src.m_vertexData;
	m_edgeData						= src.m_edgeData;
	m_polygonData					= src.m_polygonData;
	m_textureParams					= src.m_textureParams;
	
	return *this;
}

#endif

