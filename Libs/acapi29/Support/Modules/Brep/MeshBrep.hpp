// *********************************************************************************************************************
// Description:		Mesh BREP data structure. Geometry and topology data for Body.
//
// Module:			Brep
// Namespace:		Brep
// Contact person:	BeA
// *********************************************************************************************************************

#if !defined (MESHBREP_HPP)
#define MESHBREP_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "Owner.hpp"

// form Geometry
#include "Vector3D.hpp"
#include "Box3DData.h"

// from Brep
#include "BrepExport.hpp"
#include "BrepExternalBufferArray.hpp"
#include "BrepInt32Array.hpp"

// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace Brep {

	// --- Constant definitions --------------------------------------------------------------------------------------------

	// --- Type definitions ------------------------------------------------------------------------------------------------

class BREP_DLL_EXPORT MeshBrep {
public:
	typedef Coord3D Vertex;

	struct Edge {
		static const char* XMLTag_Edge;
		static const Int32 InvalidPgonIdx = -1;

		Int32 vert1 = 0, vert2 = 0;
		Int32 pgon1 = 0, pgon2 = 0;

		Edge () = default;
		Edge (Int32 vert1, Int32 vert2, Int32 pgon1 = InvalidPgonIdx, Int32 pgon2 = InvalidPgonIdx) :
			vert1 (vert1),
			vert2 (vert2),
			pgon1 (pgon1),
			pgon2 (pgon2)
		{
		}

		Int32	GetAnotherVertex	(Int32 currentVertex)		const;
		Int32	GetAnotherPolygon	(Int32 currentPolygon)		const;
		UInt32	GetPolygonCount		()							const;
		void	WriteXML			(GS::XMLOChannel& outXML)	const;
		void	ReadXML				(GS::XMLIChannel& inXML);
		static const char* GetXMLTag()								 { return XMLTag_Edge; }
	};

	typedef Int32 PolyEdge;
	typedef Vector3D PolyNormal;

	struct Polygon {
		static const char* XMLTag_Polygon;
		Int32	ivect = 0;
		Int32	fpedg = 0;
		Int32	lpedg = 0;

		UInt32	GetEdgeCount () const
		{
			return lpedg - fpedg + 1;
		}
		void	WriteXML (GS::XMLOChannel& outXML)	const;
		void	ReadXML (GS::XMLIChannel& inXML);
		static const char* GetXMLTag () { return XMLTag_Polygon; }
	};

private:

	typedef ExternalBufferArray<Vertex>			VertexContainerT;
	typedef ExternalBufferArray<Edge>			EdgeContainerT;
	typedef Int32Array							PolygonEdgeContainerT;
	typedef ExternalBufferArray<PolyNormal>		PolygonNormalContainerT;
	typedef ExternalBufferArray<Polygon>		PolygonContainerT;

	GS::Owner<std::byte[]>			m_buffer;

	VertexContainerT				m_vertices;
	EdgeContainerT					m_edges;
	PolygonEdgeContainerT			m_polyEdges;
	PolygonNormalContainerT			m_polyNormals;
	PolygonContainerT				m_polygons;

	F_Box3D							m_bounds;

public:

	// empty MeshBrep, no buffer is allocated
	MeshBrep ();

	// allocate own, fitting buffer
	MeshBrep (const MeshBrep& src);
	MeshBrep (GS::XMLIChannel& inXML);

	// Move operations reuse independent buffers from src if data didn't fit into the buffer of src and it wouldn't fit into the buffer of this	
	// MeshBrep (const MeshBrep&& src); // would be same as copy, because own buffer fits the size of src

	// externalBuffer == nullptr : allocate own buffer with given capacity
	// externalBuffer != nullptr : use external buffer with given capacity. Use CalcBufferSize to calculate required buffer size
	MeshBrep (USize vertexCount, USize edgeCount, USize polyEdgeCount, 
			  USize polyNormalCount, USize polygonCount, std::byte* externalBuffer = nullptr);
	MeshBrep (const MeshBrep& src, USize vertexCount, USize edgeCount, USize polyEdgeCount,
			  USize polyNormalCount, USize polygonCount, std::byte* externalBuffer = nullptr);
	MeshBrep (MeshBrep&& src, USize vertexCount, USize edgeCount, USize polyEdgeCount,
			  USize polyNormalCount, USize polygonCount, std::byte* externalBuffer = nullptr);

	MeshBrep& operator= (const MeshBrep& src);
	MeshBrep& operator= (MeshBrep&& src);

	void			ClearAndSetupBuffers (USize vertexCount, USize edgeCount, USize polyEdgeCount, USize polyNormalCount, USize polygonCount, std::byte* buffer);
	void			Clear ();

	void			CalculateTransformedBounds (const TRANMAT& trafo, F_Box3D& outBounds, const GS::Array<ULong>& omittedVertices = GS::Array<UIndex> ()) const;
	void			CalculateBounds ();	
	const F_Box3D&	GetLocalBounds (void) const;

	// Polygon handling
	ULong				GetPolygonCount (void) const;
	const Polygon&		GetConstPolygon (ULong index) const;
	Polygon*			GetModifiablePolygon (ULong index);
	void				SetPolygon (ULong index, const Polygon& newPolygon);
	ULong				AddPolygon (const Polygon& polygon);				// returns stored index
	void				SetPolygonCapacity (ULong capacity);

	typedef PolygonContainerT::ConstFastIterator PolygonIteratorT;
	PolygonIteratorT	BeginPolygons () const;
	PolygonIteratorT	EndPolygons () const;

	// PolyNormal handling
	ULong				GetPolyNormalCount (void) const;
	const PolyNormal&	GetConstPolyNormal (ULong index) const;
	PolyNormal			GetDirectedPolyNormalVector (ULong polygonIndex) const;
	void				SetPolyNormal (ULong index, const PolyNormal& newPolyNormal);
	ULong				AddPolyNormal (const PolyNormal& polyNormal);		// returns stored index
	void				SetPolyNormalCapacity (ULong capacity);

	typedef PolygonNormalContainerT::ConstFastIterator PolygonNormalIteratorT;
	PolygonNormalIteratorT BeginPolyNormals () const;
	PolygonNormalIteratorT EndPolyNormals () const;

	// PolyEdge handling
	ULong				GetPolyEdgeCount (void) const;
	PolyEdge			GetConstPolyEdge (ULong index) const;
	void				SetPolyEdge (ULong index, const PolyEdge& newPolyEdge);
	ULong				AddPolyEdge (const PolyEdge& polyEdge);				// returns stored index
	ULong				AddNPolyEdge (const PolyEdge* polyEdgePtr, ULong count);
	void				SetPolyEdgeCapacity (ULong capacity);
	Int32				GetBeginVertexOfPolyEdge (PolyEdge polyEdge) const;

	typedef Int32Array::ConstIterator PolyEdgeIteratorT;
	PolyEdgeIteratorT	BeginPolyEdges () const;
	PolyEdgeIteratorT	EndPolyEdges () const;

	// Edge handling
	ULong				GetEdgeCount (void) const;
	const Edge&			GetConstEdge (ULong index) const;
	Edge*				GetModifiableEdge (ULong index);
	void				SetEdge (ULong index, const Edge& newEdge);
	ULong				AddEdge (const Edge& edge);				// returns stored index
	void				SetEdgeCapacity (ULong capacity);

	typedef EdgeContainerT::ConstFastIterator EdgeIteratorT;
	EdgeIteratorT		BeginEdges () const;
	EdgeIteratorT		EndEdges () const;

	// Vertex handling
	ULong				GetVertexCount (void) const;
	const Vertex&		GetConstVertex (ULong index) const;
	void				SetVertex (ULong index, const Vertex& newVertex);
	ULong				AddVertex (const Vertex& vertex);				// returns stored index
	void				SetVertexCapacity (ULong capacity);

	typedef VertexContainerT::ConstFastIterator VertexIteratorT;
	VertexIteratorT		BeginVertices () const;
	VertexIteratorT		EndVertices () const;

	void				DeletePolygons ();

	void				Transform (const TRANMAT& tran);	// ReorientPolygons included
	void				TransformTail_NoReorient (ULong firstVertex, ULong firstPolyNormal, const TRANMAT& tran);
	void				TransformPart_NoReorient (ULong firstVertex, ULong vertexCount, ULong firstPolyNormal, ULong polyNormalCount, const TRANMAT& tran);

	void				ReorientPolygons (UIndex fromPolygonIndex = 0);
	void				ReorientPolygon (UIndex polygonIndex);
	void				ReorientPolyEdges (UIndex polygonIndex);

	Int32				AttachPolygonToPolyEdges (Int32 ipgon, Int32 npedg, const Int32* const ipedg);
	

	USize				GetUsedBytes () const;
	USize				GetPolyEdgeUsedBytes () const;

	static std::size_t	CalcBufferSize (USize vertexCount, USize edgeCount, USize polyEdgeCount, USize polyNormalCount, USize polygonCount);

	void				WriteXML (GS::XMLOChannel& outXML) const;
	void				ReadXML (GS::XMLIChannel& inXML, std::byte* buffer = nullptr);
};


class BREP_DLL_EXPORT MeshBrepFB : public MeshBrep {
	static constexpr USize BufferSize = 7604;
	union AlignedBuffer {
		std::byte buffer[BufferSize];
		void* dummy;
	} alignedBuffer;
	static_assert (alignof (AlignedBuffer) == alignof (void*), "AlignedBuffer should be aligned as void*!");
	static_assert (offsetof (AlignedBuffer, buffer) == 0, "buffer should be at the beginning of AlignedBuffer!");

public:
	static constexpr UInt32 VertexAllocCount = 127;
	static constexpr UInt32 EdgeAllocCount = 127;
	static constexpr UInt32 PolyEdgeAllocCount = 2 * EdgeAllocCount;
	static constexpr UInt32 PolyNormalAllocCount = 63;
	static constexpr UInt32 PolygonAllocCount = 63;

	MeshBrepFB ();
	MeshBrepFB (const MeshBrepFB& src);
	MeshBrepFB (MeshBrepFB&& src);

	MeshBrepFB (const MeshBrep& src);
	MeshBrepFB (MeshBrep&& src);

	MeshBrepFB& operator= (const MeshBrep& src);
	MeshBrepFB& operator= (const MeshBrepFB& src);

	MeshBrepFB& operator= (MeshBrep&& src);
	MeshBrepFB& operator= (MeshBrepFB&& src);

	~MeshBrepFB ();
};


	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------

	// -- Inline function definitions --------------------------------------------------------------------------------------


inline Int32 MeshBrep::Edge::GetAnotherVertex (Int32 currentVertex) const
{
	if (vert1 == currentVertex) {
		return vert2;
	} else if (vert2 == currentVertex) {
		return vert1;
	}

	return -1;
}


inline Int32 MeshBrep::Edge::GetAnotherPolygon (Int32 currentPolygon) const
{
	if (pgon1 == currentPolygon) {
		return pgon2;
	} else if (pgon2 == currentPolygon) {
		return pgon1;
	}

	return -1;
}


inline UInt32	MeshBrep::Edge::GetPolygonCount () const
{
	Int32 result = 0;
	if (pgon1 >= 0) {
		result++;
	}
	if (pgon2 >= 0) {
		result++;
	}
	return result;
}


inline const F_Box3D& MeshBrep::GetLocalBounds (void) const
{
	return m_bounds;
}


inline ULong MeshBrep::GetPolygonCount (void) const
{
	return m_polygons.GetSize ();
}


inline const MeshBrep::Polygon& MeshBrep::GetConstPolygon (ULong index) const
{
	return m_polygons[index];
}


inline MeshBrep::Polygon* MeshBrep::GetModifiablePolygon (ULong index)
{
	return &m_polygons[index];
}


inline void MeshBrep::SetPolygon (ULong index, const MeshBrep::Polygon& newPolygon)
{
	m_polygons[index] = newPolygon;
}


inline ULong MeshBrep::AddPolygon (const MeshBrep::Polygon& polygon)
{
	m_polygons.Push (polygon);
	return m_polygons.GetSize () - 1;
}


inline void MeshBrep::SetPolygonCapacity (ULong capacity)
{
	m_polygons.SetCapacity (capacity);
}


inline MeshBrep::PolygonIteratorT	MeshBrep::BeginPolygons () const
{
	return m_polygons.BeginFast ();
}


inline MeshBrep::PolygonIteratorT	MeshBrep::EndPolygons () const
{
	return m_polygons.EndFast ();
}


inline ULong MeshBrep::GetPolyNormalCount (void) const
{
	return m_polyNormals.GetSize ();
}


inline const MeshBrep::PolyNormal& MeshBrep::GetConstPolyNormal (ULong index) const
{
	return m_polyNormals[index];
}


inline MeshBrep::PolyNormal	MeshBrep::GetDirectedPolyNormalVector (ULong polygonIndex) const
{
	Int32 ivect = GetConstPolygon (polygonIndex).ivect;
	PolyNormal polyNormal = GetConstPolyNormal (GS::Abs (ivect) - 1);
	if (ivect < 0) {
		polyNormal *= -1.0;
	}
	return polyNormal;
}


inline void MeshBrep::SetPolyNormal (ULong index, const PolyNormal& newPolyNormal)
{
	m_polyNormals[index] = newPolyNormal;
}


inline ULong MeshBrep::AddPolyNormal (const MeshBrep::PolyNormal& polyNormal)
{
	m_polyNormals.Push (polyNormal);
	return m_polyNormals.GetSize () - 1;
}


inline void MeshBrep::SetPolyNormalCapacity (ULong capacity)
{
	m_polyNormals.SetCapacity (capacity);
}


inline MeshBrep::PolygonNormalIteratorT MeshBrep::BeginPolyNormals () const
{
	return m_polyNormals.BeginFast ();
}


inline MeshBrep::PolygonNormalIteratorT MeshBrep::EndPolyNormals () const
{
	return m_polyNormals.EndFast ();
}


inline ULong MeshBrep::GetPolyEdgeCount (void) const
{
	return m_polyEdges.GetSize ();
}


inline MeshBrep::PolyEdge MeshBrep::GetConstPolyEdge (ULong index) const
{
	return m_polyEdges.GetValue (index);
}


inline void MeshBrep::SetPolyEdge (ULong index, const MeshBrep::PolyEdge& newPolyEdge)
{
	m_polyEdges.SetValue (index, newPolyEdge);
}


inline ULong MeshBrep::AddPolyEdge (const MeshBrep::PolyEdge& polyEdge)
{
	return AddNPolyEdge (&polyEdge, 1);
}


inline void MeshBrep::SetPolyEdgeCapacity (ULong capacity)
{
	m_polyEdges.SetCapacity (capacity);
}


inline Int32 MeshBrep::GetBeginVertexOfPolyEdge (PolyEdge polyEdge) const
{
	DBASSERT (polyEdge != 0);
	const Edge& edge = GetConstEdge (GS::Abs (polyEdge) - 1);
	if (polyEdge > 0) {
		return edge.vert1;
	} else {
		return edge.vert2;
	}
}


inline MeshBrep::PolyEdgeIteratorT MeshBrep::BeginPolyEdges () const
{
	return m_polyEdges.Begin ();
}


inline MeshBrep::PolyEdgeIteratorT MeshBrep::EndPolyEdges () const
{
	return m_polyEdges.End ();
}


inline ULong MeshBrep::GetEdgeCount (void) const
{
	return m_edges.GetSize ();
}


inline const MeshBrep::Edge& MeshBrep::GetConstEdge (ULong index) const
{
	return m_edges[index];
}


inline MeshBrep::Edge* MeshBrep::GetModifiableEdge (ULong index)
{
	return &m_edges[index];
}


inline void MeshBrep::SetEdge (ULong index, const MeshBrep::Edge& newEdge)
{
	m_edges[index] = newEdge;
}


inline ULong MeshBrep::AddEdge (const MeshBrep::Edge& edge)
{
	m_edges.Push (edge);
	return m_edges.GetSize () - 1;
}


inline void MeshBrep::SetEdgeCapacity (ULong capacity)
{
	m_edges.SetCapacity (capacity);
}


inline MeshBrep::EdgeIteratorT	MeshBrep::BeginEdges () const
{
	return m_edges.BeginFast ();
}


inline MeshBrep::EdgeIteratorT	MeshBrep::EndEdges () const
{
	return m_edges.EndFast ();
}


inline ULong MeshBrep::GetVertexCount (void) const
{
	return m_vertices.GetSize ();
}


inline const MeshBrep::Vertex& MeshBrep::GetConstVertex (ULong index) const
{
	return m_vertices[index];
}


inline void MeshBrep::SetVertex (ULong index, const MeshBrep::Vertex& newVertex)
{
	m_vertices[index] = newVertex;
}


inline ULong MeshBrep::AddVertex (const MeshBrep::Vertex& vertex)
{
	m_vertices.Push (vertex);
	return m_vertices.GetSize () - 1;
}

inline void MeshBrep::SetVertexCapacity (ULong capacity)
{
	m_vertices.SetCapacity (capacity);
}

inline MeshBrep::VertexIteratorT	MeshBrep::BeginVertices () const
{
	return m_vertices.BeginFast ();
}

inline MeshBrep::VertexIteratorT	MeshBrep::EndVertices () const
{
	return m_vertices.EndFast ();
}

}	// namespace Brep

#endif // MESHBREP_HPP
