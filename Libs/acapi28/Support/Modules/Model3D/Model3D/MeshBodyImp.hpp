// *********************************************************************************************************************
// Description:		Implementation of inline functions of Body.hpp
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_MESHBODYIMP_HPP)
#define GS_MODELER_MESHBODYIMP_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include <math.h>

// from GSRoot

// from Geometry
#include "RealNumber.h"

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

inline bool		Modeler::MeshBody::IsWireBody (void) const
{
	return HasEdges () && !HasPolygons ();	// emtpy body is not wireframe
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline bool		Modeler::MeshBody::IsSurfaceBody (void) const
{
	return HAS_ANY_FLAGS (m_status, MeshBody::SurfaceBody);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline bool		Modeler::MeshBody::IsSolidBody (void) const
{
	return !IsWireBody () && !IsSurfaceBody ();		// If solid, it is assumed to be closed also
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

// If all edges have two polygons attached
inline bool		Modeler::MeshBody::IsClosedBody (void) const
{
	return HAS_ANY_FLAGS (m_status, MeshBody::ClosedBody);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline bool		Modeler::MeshBody::IsCurvedBody (void) const
{
	return HAS_ANY_FLAGS (m_status, MeshBody::CurvedBody);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline bool		Modeler::MeshBody::IsCutBody (void) const
{
	return HAS_ANY_FLAGS (m_status, MeshBody::CutBody);
}


// -----------------------------------------------------------------------------
// 
// -----------------------------------------------------------------------------

inline bool		Modeler::MeshBody::HasSharpEdge (void) const
{
	return HAS_ANY_FLAGS (m_status, MeshBody::SharpEdgeBody);
}

inline bool		Modeler::MeshBody::AlwaysCastsShadow (void) const			// pcs 2003.02.24 TT#22361
{
	return HAS_ANY_FLAGS (m_status, MeshBody::ShadowOn);
}

inline bool		Modeler::MeshBody::NeverCastsShadow (void) const
{
	return HAS_ANY_FLAGS (m_status, MeshBody::ShadowOff) && !HAS_ANY_FLAGS (m_status, MeshBody::ShadowOn);
}

inline bool		Modeler::MeshBody::AutoCastsShadow (void) const
{
	return !HAS_ANY_FLAGS (m_status, MeshBody::ShadowOff) && !HAS_ANY_FLAGS (m_status, MeshBody::ShadowOn);
}

inline bool		Modeler::MeshBody::DoesNotReceiveShadow (void) const
{
	return HAS_ANY_FLAGS (m_status, MeshBody::ShadowNot);
}

// Warning! O(n) method
inline bool		Modeler::MeshBody::HasMultipleColors (void) const
{
	if (!HasEdges ())
		return false;

	short refEdgePen = (GetEdgePenIdx () > 0) ? GetEdgePenIdx () : GetConstEdgeAttributes (0).GetColor ();

	for (UIndex edgeIdx = 0; edgeIdx < GetEdgeCount (); ++edgeIdx)
		if (GetConstEdgeAttributes (edgeIdx).GetColor () != refEdgePen)
			return false;

	return true;
}


// Warning! O(n) method
inline bool		Modeler::MeshBody::HasMultipleMaterials (void) const
{
	if (!HasPolygons ())
		return false;

	GSAttributeIndex refMaterial = (GetMaterialIdx () > 0) ? GetMaterialIdx () : GetConstPolygonAttributes (0).GetMaterialIndex ();

	for (UIndex polyIdx = 0; polyIdx < GetPolygonCount (); ++polyIdx)
		if (GetConstPolygonAttributes (polyIdx).GetMaterialIndex () != refMaterial)
			return false;

	return true;
}


// Warning! O(n) method
inline bool		Modeler::MeshBody::HasMultipleTextures (void) const
{
	if (!HasPolygons ())
		return false;

	Int32 refTexture = GetConstPolygonAttributes (0).GetTextureIndex ();

	for (UIndex polyIdx = 0; polyIdx < GetPolygonCount (); ++polyIdx)
		if (GetConstPolygonAttributes (polyIdx).GetTextureIndex () != refTexture)
			return false;

	return true;
}



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void		Modeler::MeshBody::SetTextureCoordSys (const Modeler::TextureCoordSys& tcs)
{
	m_attrs.textureCoordSys = tcs;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline const Modeler::TextureCoordSys& Modeler::MeshBody::GetTextureCoordSys () const
{
	return m_attrs.textureCoordSys;
}


//inline bool Modeler::MeshBody::OnlyRefersToGeometry (void) const
//{
//	bool isRepeatedTopo = (m_status & TOPOBIT) > 0;  // if TOPO set, it is a reference, not a real ownership
//	bool isFirstTopo = (m_status & FTOPOBIT) > 0;
//	bool onlyRefersToGeometry = isRepeatedTopo && !isFirstTopo;
//
//	return onlyRefersToGeometry;
//}

inline bool Modeler::MeshBody::HasPolygons () const
{
	return m_meshBrep.GetPolygonCount () > 0;
}


inline ULong Modeler::MeshBody::GetPolygonCount () const
{
	return m_meshBrep.GetPolygonCount ();
}

inline bool Modeler::MeshBody::HasPolyNormals () const
{
	return m_meshBrep.GetPolyNormalCount () > 0;
}


inline ULong Modeler::MeshBody::GetPolyNormalCount () const
{
	return m_meshBrep.GetPolyNormalCount ();
}

inline bool Modeler::MeshBody::HasPolyEdges () const
{
	return m_meshBrep.GetPolyEdgeCount () > 0;
}

inline ULong Modeler::MeshBody::GetPolyEdgeCount () const
{
	return m_meshBrep.GetPolyEdgeCount ();
}

inline ULong Modeler::MeshBody::GetPolyEdgeUsedBytes () const
{
	return m_meshBrep.GetPolyEdgeUsedBytes ();
}

inline bool Modeler::MeshBody::HasEdges () const
{
	return m_meshBrep.GetEdgeCount () > 0;
}

inline ULong Modeler::MeshBody::GetEdgeCount () const
{
	return m_meshBrep.GetEdgeCount ();
}

inline const Modeler::EdgeAttributes& Modeler::MeshBody::GetConstEdgeAttributes (ULong index) const
{
	return m_edgeAttributes[index];
}

inline bool Modeler::MeshBody::HasVertices () const
{
	return m_meshBrep.GetVertexCount () > 0;
}

inline ULong Modeler::MeshBody::GetVertexCount () const
{
	return m_meshBrep.GetVertexCount ();
}

inline Wrapping Modeler::MeshBody::GetPolygonTextureWrapping (Int32 ipgon) const
{
	const PolygonAttributes& polygonAttributes = GetConstPolygonAttributes (ipgon);
	
	return (polygonAttributes.HasTextureUVs () || polygonAttributes.HasTextureCoordinateSystem ())
		? polygonAttributes.GetWrapping ()	// return own wrapping of polygon
		: GetWrapping ();					// fallback to wrapping from body
}

inline UV Modeler::MeshBody::GetPolygonTextureVertex (Int32 polygonIndex, Int32 vertexIndex) const
{
	UV result;
	result.u = 0.0;
	result.v = 0.0;

	DBASSERT (vertexIndex >= 0 && USize(vertexIndex) < GetVertexCount ());
	
	const PGON& apgon = GetConstPolygon (polygonIndex);
	const PolygonAttributes& polygonAttributes = GetConstPolygonAttributes (polygonIndex);

	USize holeCount = 0;
	for (Int32 ipedg = apgon.fpedg; ipedg <= apgon.lpedg; ipedg++) {
		Int32 ivert = GetBodyVertIdxFromPolyEdgeIdx (ipedg);
		
		if (ivert == -1) {
			++holeCount;
		} else if (ivert == vertexIndex) {
			result.u = GetPolygonTextureParameter (polygonAttributes.GetFirstTextureParameterIndex () + 2 * (ipedg - apgon.fpedg - holeCount));
			result.v = GetPolygonTextureParameter (polygonAttributes.GetFirstTextureParameterIndex () + 2 * (ipedg - apgon.fpedg - holeCount) + 1);
			return result;
		}
	}

	DBBREAK_STR ("Polygon has no vertex with this vertex index.");
	return result;
}

inline bool Modeler::MeshBody::HasPolygonTextureParameters (void) const
{
	return m_textureParams.GetSize () > 0;
}

inline ULong Modeler::MeshBody::GetPolygonTextureParameterCount () const
{
	return m_textureParams.GetSize ();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline const F_Box3D&	Modeler::MeshBody::GetLocalBounds (void) const
{
	return m_meshBrep.GetLocalBounds ();
}

inline Modeler::ConstMeshBodyVertexIterator Modeler::MeshBody::BeginVertices () const
{
	return ConstMeshBodyVertexIterator (*this, 0);
}


inline Modeler::ConstMeshBodyVertexIterator Modeler::MeshBody::EndVertices () const
{
	return ConstMeshBodyVertexIterator (*this, GetVertexCount ());
}


inline Modeler::ConstMeshBodyEdgeIterator Modeler::MeshBody::BeginEdges () const
{
	return ConstMeshBodyEdgeIterator (*this, 0);
}


inline Modeler::ConstMeshBodyEdgeIterator Modeler::MeshBody::EndEdges () const
{
	return ConstMeshBodyEdgeIterator (*this, GetEdgeCount ());
}


inline Modeler::ConstMeshBodyPolygonIterator Modeler::MeshBody::BeginPolygons () const
{
	return ConstMeshBodyPolygonIterator (*this, 0);
}


inline Modeler::ConstMeshBodyPolygonIterator Modeler::MeshBody::EndPolygons () const
{
	return ConstMeshBodyPolygonIterator (*this, GetPolygonCount ());
}


inline Modeler::ConstMeshBodyPolyEdgeIterator Modeler::MeshBody::BeginPolyEdges (const PGON& parentPoly) const
{
	return ConstMeshBodyPolyEdgeIterator (*this, parentPoly.fpedg);
}


inline Modeler::ConstMeshBodyPolyEdgeIterator Modeler::MeshBody::EndPolyEdges (const PGON& parentPoly) const
{
	return ConstMeshBodyPolyEdgeIterator (*this, parentPoly.lpedg + 1);
}


GS_FORCE_INLINE	const Modeler::PolygonId& Modeler::MeshBody::GetPolygonId (ULong index) const
{
	if (index < m_polygonIds.GetSize ())
		return m_polygonIds [index];

	return PolygonId::Invalid;
}


GS_FORCE_INLINE	const Modeler::EdgeId& Modeler::MeshBody::GetEdgeId (ULong index) const
{
	if (index < m_edgeIds.GetSize ())
		return m_edgeIds [index];

	return EdgeId::Invalid;
}


GS_FORCE_INLINE	const Modeler::VertexId& Modeler::MeshBody::GetVertexId (ULong index) const
{
	if (index < m_vertexIds.GetSize ())
		return m_vertexIds [index];

	return VertexId::Invalid;
}


GS_FORCE_INLINE	bool Modeler::MeshBody::GetVertexHardFlag (ULong index) const
{
	if ((index >> 3) < m_vertexHardFlags.GetSize ())
		return (m_vertexHardFlags[index >> 3] & (1 << (index & 7))) != 0;
		
	return false;
}


// =====================================================================================================================
//
// ConstMeshBodyVertexIterator
//
// =====================================================================================================================

inline Modeler::ConstMeshBodyVertexIterator::ConstMeshBodyVertexIterator (const Modeler::MeshBody& parentBodyIn, Int32 startIdx)
	: parentBody (parentBodyIn), vertIdx (startIdx)
{
}


inline const VERT& Modeler::ConstMeshBodyVertexIterator::operator* () const
{
	return parentBody.GetConstVertex (vertIdx);
}


inline const VERT* Modeler::ConstMeshBodyVertexIterator::operator-> () const
{
   return &parentBody.GetConstVertex (vertIdx);
}


inline Modeler::ConstMeshBodyVertexIterator& Modeler::ConstMeshBodyVertexIterator::operator++ ()
{
	++vertIdx;
	return *this;
}


inline Modeler::ConstMeshBodyVertexIterator Modeler::ConstMeshBodyVertexIterator::operator++ (int)
{
	ConstMeshBodyVertexIterator result = *this;
	++vertIdx;
	return result;
}


inline Modeler::ConstMeshBodyVertexIterator& Modeler::ConstMeshBodyVertexIterator::operator-- ()
{
	--vertIdx;
	return *this;
}


inline Modeler::ConstMeshBodyVertexIterator Modeler::ConstMeshBodyVertexIterator::operator-- (int)
{
	ConstMeshBodyVertexIterator result = *this;
	--vertIdx;
	return result;
}


inline bool	Modeler::ConstMeshBodyVertexIterator::operator== (const Modeler::ConstMeshBodyVertexIterator& rightOp) const
{
	return &parentBody == &rightOp.parentBody && vertIdx == rightOp.vertIdx;
}


inline bool	Modeler::ConstMeshBodyVertexIterator::operator!= (const Modeler::ConstMeshBodyVertexIterator& rightOp) const
{
	return !operator== (rightOp);
}


inline const VERT&	Modeler::ConstMeshBodyVertexIterator::operator[] (GS::Offset offset) const
{
	return parentBody.GetConstVertex (offset);
}


inline Modeler::ConstMeshBodyVertexIterator	Modeler::ConstMeshBodyVertexIterator::operator+  (GS::Offset offset) const
{
	ConstMeshBodyVertexIterator result = *this;
	return result += offset;
}


inline Modeler::ConstMeshBodyVertexIterator	Modeler::ConstMeshBodyVertexIterator::operator-  (GS::Offset offset) const
{
	ConstMeshBodyVertexIterator result = *this;
	return result -= offset;
}


inline GS::Offset			Modeler::ConstMeshBodyVertexIterator::operator-  (const Modeler::ConstMeshBodyVertexIterator& rightOp) const
{
	return vertIdx - rightOp.vertIdx;
}


inline Modeler::ConstMeshBodyVertexIterator&	Modeler::ConstMeshBodyVertexIterator::operator+= (GS::Offset offset)
{
	vertIdx += offset;
	return *this;
}


inline Modeler::ConstMeshBodyVertexIterator&	Modeler::ConstMeshBodyVertexIterator::operator-= (GS::Offset offset)
{
	vertIdx -= offset;
	return *this;
}


inline bool Modeler::ConstMeshBodyVertexIterator::operator<  (const Modeler::ConstMeshBodyVertexIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return vertIdx < rightOp.vertIdx;
}


inline bool Modeler::ConstMeshBodyVertexIterator::operator<= (const Modeler::ConstMeshBodyVertexIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return vertIdx <= rightOp.vertIdx;
}


inline bool Modeler::ConstMeshBodyVertexIterator::operator>  (const Modeler::ConstMeshBodyVertexIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return vertIdx > rightOp.vertIdx;
}


inline bool Modeler::ConstMeshBodyVertexIterator::operator>= (const Modeler::ConstMeshBodyVertexIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return vertIdx >= rightOp.vertIdx;
}


// =====================================================================================================================
//
// ConstMeshBodyEdgeIterator
//
// =====================================================================================================================

inline Modeler::ConstMeshBodyEdgeIterator::ConstMeshBodyEdgeIterator (const Modeler::MeshBody& parentBodyIn, Int32 startIdx)
	: parentBody (parentBodyIn), edgeIdx (startIdx)
{
}


inline const EDGE& Modeler::ConstMeshBodyEdgeIterator::operator* () const
{
	return parentBody.GetConstEdge (edgeIdx);
}


inline const EDGE* Modeler::ConstMeshBodyEdgeIterator::operator-> () const
{
   return &parentBody.GetConstEdge (edgeIdx);
}


inline Modeler::ConstMeshBodyEdgeIterator& Modeler::ConstMeshBodyEdgeIterator::operator++ ()
{
	++edgeIdx;
	return *this;
}


inline Modeler::ConstMeshBodyEdgeIterator Modeler::ConstMeshBodyEdgeIterator::operator++ (int)
{
	ConstMeshBodyEdgeIterator result = *this;
	++edgeIdx;
	return result;
}


inline Modeler::ConstMeshBodyEdgeIterator& Modeler::ConstMeshBodyEdgeIterator::operator-- ()
{
	--edgeIdx;
	return *this;
}


inline Modeler::ConstMeshBodyEdgeIterator Modeler::ConstMeshBodyEdgeIterator::operator-- (int)
{
	ConstMeshBodyEdgeIterator result = *this;
	--edgeIdx;
	return result;
}


inline bool	Modeler::ConstMeshBodyEdgeIterator::operator== (const Modeler::ConstMeshBodyEdgeIterator& rightOp) const
{
	return &parentBody == &rightOp.parentBody && edgeIdx == rightOp.edgeIdx;
}


inline bool	Modeler::ConstMeshBodyEdgeIterator::operator!= (const Modeler::ConstMeshBodyEdgeIterator& rightOp) const
{
	return !operator== (rightOp);
}


inline const EDGE&	Modeler::ConstMeshBodyEdgeIterator::operator[] (GS::Offset offset) const
{
	return parentBody.GetConstEdge (offset);
}


inline Modeler::ConstMeshBodyEdgeIterator	Modeler::ConstMeshBodyEdgeIterator::operator+  (GS::Offset offset) const
{
	ConstMeshBodyEdgeIterator result = *this;
	return result += offset;
}


inline Modeler::ConstMeshBodyEdgeIterator	Modeler::ConstMeshBodyEdgeIterator::operator-  (GS::Offset offset) const
{
	ConstMeshBodyEdgeIterator result = *this;
	return result -= offset;
}


inline GS::Offset			Modeler::ConstMeshBodyEdgeIterator::operator-  (const Modeler::ConstMeshBodyEdgeIterator& rightOp) const
{
	return edgeIdx - rightOp.edgeIdx;
}


inline Modeler::ConstMeshBodyEdgeIterator&	Modeler::ConstMeshBodyEdgeIterator::operator+= (GS::Offset offset)
{
	edgeIdx += offset;
	return *this;
}


inline Modeler::ConstMeshBodyEdgeIterator&	Modeler::ConstMeshBodyEdgeIterator::operator-= (GS::Offset offset)
{
	edgeIdx -= offset;
	return *this;
}


inline bool Modeler::ConstMeshBodyEdgeIterator::operator<  (const Modeler::ConstMeshBodyEdgeIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return edgeIdx < rightOp.edgeIdx;
}


inline bool Modeler::ConstMeshBodyEdgeIterator::operator<= (const Modeler::ConstMeshBodyEdgeIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return edgeIdx <= rightOp.edgeIdx;
}


inline bool Modeler::ConstMeshBodyEdgeIterator::operator>  (const Modeler::ConstMeshBodyEdgeIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return edgeIdx > rightOp.edgeIdx;
}


inline bool Modeler::ConstMeshBodyEdgeIterator::operator>= (const Modeler::ConstMeshBodyEdgeIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return edgeIdx >= rightOp.edgeIdx;
}

// =====================================================================================================================
//
// ConstMeshBodyPolygonIterator
//
// =====================================================================================================================

inline Modeler::ConstMeshBodyPolygonIterator::ConstMeshBodyPolygonIterator (const Modeler::MeshBody& parentBodyIn, Int32 startIdx)
	: parentBody (parentBodyIn), polyIdx (startIdx)
{
}


inline const Modeler::PGON& Modeler::ConstMeshBodyPolygonIterator::operator* () const
{
	return parentBody.GetConstPolygon (polyIdx);
}


inline const Modeler::PGON* Modeler::ConstMeshBodyPolygonIterator::operator-> () const
{
   return &parentBody.GetConstPolygon (polyIdx);
}


inline Modeler::ConstMeshBodyPolygonIterator& Modeler::ConstMeshBodyPolygonIterator::operator++ ()
{
	++polyIdx;
	return *this;
}


inline Modeler::ConstMeshBodyPolygonIterator Modeler::ConstMeshBodyPolygonIterator::operator++ (int)
{
	ConstMeshBodyPolygonIterator result = *this;
	++polyIdx;
	return result;
}


inline Modeler::ConstMeshBodyPolygonIterator& Modeler::ConstMeshBodyPolygonIterator::operator-- ()
{
	--polyIdx;
	return *this;
}


inline Modeler::ConstMeshBodyPolygonIterator Modeler::ConstMeshBodyPolygonIterator::operator-- (int)
{
	ConstMeshBodyPolygonIterator result = *this;
	--polyIdx;
	return result;
}


inline bool	Modeler::ConstMeshBodyPolygonIterator::operator== (const Modeler::ConstMeshBodyPolygonIterator& rightOp) const
{
	return &parentBody == &rightOp.parentBody && polyIdx == rightOp.polyIdx;
}


inline bool	Modeler::ConstMeshBodyPolygonIterator::operator!= (const Modeler::ConstMeshBodyPolygonIterator& rightOp) const
{
	return !operator== (rightOp);
}


inline const Modeler::PGON&	Modeler::ConstMeshBodyPolygonIterator::operator[] (GS::Offset offset) const
{
	return parentBody.GetConstPolygon (offset);
}


inline Modeler::ConstMeshBodyPolygonIterator	Modeler::ConstMeshBodyPolygonIterator::operator+  (GS::Offset offset) const
{
	ConstMeshBodyPolygonIterator result = *this;
	return result += offset;
}


inline Modeler::ConstMeshBodyPolygonIterator	Modeler::ConstMeshBodyPolygonIterator::operator-  (GS::Offset offset) const
{
	ConstMeshBodyPolygonIterator result = *this;
	return result -= offset;
}


inline GS::Offset			Modeler::ConstMeshBodyPolygonIterator::operator-  (const Modeler::ConstMeshBodyPolygonIterator& rightOp) const
{
	return polyIdx - rightOp.polyIdx;
}


inline Modeler::ConstMeshBodyPolygonIterator&	Modeler::ConstMeshBodyPolygonIterator::operator+= (GS::Offset offset)
{
	polyIdx += offset;
	return *this;
}


inline Modeler::ConstMeshBodyPolygonIterator&	Modeler::ConstMeshBodyPolygonIterator::operator-= (GS::Offset offset)
{
	polyIdx -= offset;
	return *this;
}


inline bool Modeler::ConstMeshBodyPolygonIterator::operator<  (const Modeler::ConstMeshBodyPolygonIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return polyIdx < rightOp.polyIdx;
}


inline bool Modeler::ConstMeshBodyPolygonIterator::operator<= (const Modeler::ConstMeshBodyPolygonIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return polyIdx <= rightOp.polyIdx;
}


inline bool Modeler::ConstMeshBodyPolygonIterator::operator>  (const Modeler::ConstMeshBodyPolygonIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return polyIdx > rightOp.polyIdx;
}


inline bool Modeler::ConstMeshBodyPolygonIterator::operator>= (const Modeler::ConstMeshBodyPolygonIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return polyIdx >= rightOp.polyIdx;
}


// =====================================================================================================================
//
// ConstMeshBodyPolyEdgeIterator
//
// =====================================================================================================================

#if 0 // FGy
// return value CAN be nullptr
static const EDGE* ResolvePedgToEDGEPtr (const Modeler::MeshBody& parentBody, Int32 pedgIdx)
{
	Int32 pedg = parentBody.GetConstPolyEdge (pedgIdx);
	const EDGE* edgePtr;
	if (pedg == 0) {
		edgePtr = nullptr;
	} else {
		Int32 edgeIdx;
		if (pedg > 0)
			edgeIdx =   pedg - 1;
		else
			edgeIdx = - pedg - 1;
		edgePtr = parentBody.GetConstEdge (edgeIdx);
	}
	return edgePtr;
}
#endif

inline Modeler::ConstMeshBodyPolyEdgeIterator::ConstMeshBodyPolyEdgeIterator (const Modeler::MeshBody& parentBodyIn, Int32 startIdx)
	: parentBody (parentBodyIn), pedgIdx (startIdx)
{
}


inline Int32 Modeler::ConstMeshBodyPolyEdgeIterator::operator* () const
{
	return parentBody.GetConstPolyEdge (pedgIdx);
}


inline Modeler::ConstMeshBodyPolyEdgeIterator& Modeler::ConstMeshBodyPolyEdgeIterator::operator++ ()
{
	++pedgIdx;
	return *this;
}


inline Modeler::ConstMeshBodyPolyEdgeIterator Modeler::ConstMeshBodyPolyEdgeIterator::operator++ (int)
{
	ConstMeshBodyPolyEdgeIterator result = *this;
	++pedgIdx;
	return result;
}


inline Modeler::ConstMeshBodyPolyEdgeIterator& Modeler::ConstMeshBodyPolyEdgeIterator::operator-- ()
{
	--pedgIdx;
	return *this;
}


inline Modeler::ConstMeshBodyPolyEdgeIterator Modeler::ConstMeshBodyPolyEdgeIterator::operator-- (int)
{
	ConstMeshBodyPolyEdgeIterator result = *this;
	--pedgIdx;
	return result;
}


inline bool	Modeler::ConstMeshBodyPolyEdgeIterator::operator== (const Modeler::ConstMeshBodyPolyEdgeIterator& rightOp) const
{
	return &parentBody == &rightOp.parentBody && pedgIdx == rightOp.pedgIdx;
}


inline bool	Modeler::ConstMeshBodyPolyEdgeIterator::operator!= (const Modeler::ConstMeshBodyPolyEdgeIterator& rightOp) const
{
	return !operator== (rightOp);
}


inline Int32	Modeler::ConstMeshBodyPolyEdgeIterator::operator[] (GS::Offset offset) const
{
	return parentBody.GetConstPolyEdge (offset);
}


inline Modeler::ConstMeshBodyPolyEdgeIterator	Modeler::ConstMeshBodyPolyEdgeIterator::operator+  (GS::Offset offset) const
{
	ConstMeshBodyPolyEdgeIterator result = *this;
	return result += offset;
}


inline Modeler::ConstMeshBodyPolyEdgeIterator	Modeler::ConstMeshBodyPolyEdgeIterator::operator-  (GS::Offset offset) const
{
	ConstMeshBodyPolyEdgeIterator result = *this;
	return result -= offset;
}


inline GS::Offset			Modeler::ConstMeshBodyPolyEdgeIterator::operator-  (const Modeler::ConstMeshBodyPolyEdgeIterator& rightOp) const
{
	return pedgIdx - rightOp.pedgIdx;
}


inline Modeler::ConstMeshBodyPolyEdgeIterator&	Modeler::ConstMeshBodyPolyEdgeIterator::operator+= (GS::Offset offset)
{
	pedgIdx += offset;
	return *this;
}


inline Modeler::ConstMeshBodyPolyEdgeIterator&	Modeler::ConstMeshBodyPolyEdgeIterator::operator-= (GS::Offset offset)
{
	pedgIdx -= offset;
	return *this;
}


inline bool Modeler::ConstMeshBodyPolyEdgeIterator::operator<  (const Modeler::ConstMeshBodyPolyEdgeIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return pedgIdx < rightOp.pedgIdx;
}


inline bool Modeler::ConstMeshBodyPolyEdgeIterator::operator<= (const Modeler::ConstMeshBodyPolyEdgeIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return pedgIdx <= rightOp.pedgIdx;
}


inline bool Modeler::ConstMeshBodyPolyEdgeIterator::operator>  (const Modeler::ConstMeshBodyPolyEdgeIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return pedgIdx > rightOp.pedgIdx;
}


inline bool Modeler::ConstMeshBodyPolyEdgeIterator::operator>= (const Modeler::ConstMeshBodyPolyEdgeIterator& rightOp) const
{
	DBASSERT (&parentBody == &rightOp.parentBody);
	return pedgIdx >= rightOp.pedgIdx;
}


#endif
