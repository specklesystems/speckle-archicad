// *********************************************************************************************************************
// Description:		Boundary representation described with NURBS curves and surfaces
//					http://wiki/w/NURBS_Brep_topol%C3%B3gia
// *********************************************************************************************************************

#if !defined (NURBS_BREP_HPP)
#define NURBS_BREP_HPP

#pragma once

//from GSRoot
#include "ClassInfo.hpp"

#include	"BrepExport.hpp"

#include	"Definitions.hpp"
#include	"Array.hpp"

#include	"NurbsVertex.hpp"
#include	"NurbsEdge.hpp"
#include	"NurbsFace.hpp"
#include	"NurbsTrim.hpp"
#include	"NurbsLoop.hpp"
#include	"NurbsLump.hpp"
#include	"NurbsShell.hpp"
#include	"NurbsBrepCheck.hpp"

#include	"NurbsCurve2D.hpp"
#include	"NurbsCurve3D.hpp"
#include	"NurbsSurface.hpp"

// Types

namespace Brep {


////////////////////////////////////////////////////////////////////////////////
// NurbsBrep
////////////////////////////////////////////////////////////////////////////////

class BREP_DLL_EXPORT NurbsBrep {
	static	GS::ClassInfo	classInfo;
public:

	// ================================
	//    Public constants
	// ================================

	// counts in a cube x 1.5
	static const UInt32	NurbsVertexAllocCount = 12;
	static const UInt32	NurbsEdgeAllocCount = 18;
	static const UInt32 NurbsTrimAllocCount = 2 * NurbsEdgeAllocCount;
	static const UInt32	NurbsLoopAllocCount = 9;
	static const UInt32	NurbsFaceAllocCount = 9;
	static const UInt32	NurbsShellAllocCount = 1;
	static const UInt32	NurbsRegionAllocCount = 2;
	static const UInt32	NurbsCurve2DAllocCount = NurbsTrimAllocCount;
	static const UInt32	NurbsCurve3DAllocCount = NurbsEdgeAllocCount;
	static const UInt32	NurbsSurfaceAllocCount = NurbsFaceAllocCount;	

private:
	// ================================
	//   Private constants
	// ================================
	static const double DefaultTolerance;

	// ================================
	//    Types
	// ================================
	typedef GS::ArrayFB<NurbsVertex				, NurbsVertexAllocCount	>		NurbsVertexContainerT;
	typedef GS::ArrayFB<NurbsEdge				, NurbsEdgeAllocCount	>		NurbsEdgeContainerT;
	typedef GS::ArrayFB<NurbsTrim				, NurbsTrimAllocCount	>		NurbsTrimContainerT;
	typedef GS::ArrayFB<NurbsLoop				, NurbsLoopAllocCount	>		NurbsLoopContainerT;
	typedef GS::ArrayFB<NurbsFace				, NurbsFaceAllocCount	>		NurbsFaceContainerT;
	typedef GS::ArrayFB<NurbsShell				, NurbsShellAllocCount	>		NurbsShellContainerT;
	typedef GS::ArrayFB<NurbsLump				, NurbsRegionAllocCount	>		NurbsLumpContainerT;
	typedef GS::ArrayFB<Geometry::NurbsCurve2D	, NurbsCurve2DAllocCount>		NurbsCurve2DContainerT;
	typedef GS::ArrayFB<Geometry::NurbsCurve3D	, NurbsCurve3DAllocCount>		NurbsCurve3DContainerT;
	typedef GS::ArrayFB<Geometry::NurbsSurface	, NurbsSurfaceAllocCount>		NurbsSurfaceContainerT;

	typedef NurbsVertexContainerT::ConstIterator		ConstVertexIt;
	typedef NurbsEdgeContainerT::ConstIterator			ConstEdgeIt;
	typedef NurbsTrimContainerT::ConstIterator			ConstTrimIt;
	typedef NurbsLoopContainerT::ConstIterator			ConstLoopIt;
	typedef NurbsFaceContainerT::ConstIterator			ConstFaceIt;
	typedef NurbsShellContainerT::ConstIterator			ConstShellIt;
	typedef NurbsLumpContainerT::ConstIterator			ConstLumpIt;
	typedef NurbsCurve2DContainerT::ConstIterator		ConstCurve2DIt;
	typedef NurbsCurve3DContainerT::ConstIterator		ConstCurve3DIt;
	typedef NurbsSurfaceContainerT::ConstIterator		ConstSurfaceIt;

private:

	// ================================
	//     Topological subelements
	// ================================
	NurbsVertexContainerT	m_vertices;
	NurbsEdgeContainerT		m_edges;
	NurbsTrimContainerT		m_trims;
	NurbsLoopContainerT		m_loops;
	NurbsFaceContainerT		m_faces;
	NurbsShellContainerT	m_shells;
	NurbsLumpContainerT		m_lumps;
	
	// ================================
	//     Geometrical subelements
	// ================================
	NurbsCurve2DContainerT	m_curves2D;
	NurbsCurve3DContainerT	m_curves3D;
	NurbsSurfaceContainerT	m_surfaces;

	// ================================
	//        Other body data
	// ================================	
	GS::ThreadSafeLazyData<Box3D> m_bounds;
	NurbsBrepCheckControl		  m_checkControl;


	// ================================
	//       Disabled methods
	// ================================
	bool operator== (const NurbsBrep&);	// Not clear if it would mean geometrical or data-structural equality.
													// Use Equals or implement geometrical comparison instead 

	// ================================
	//       Private methods
	// ================================
private:
	
	// Subtasks of @Check. They throw the appropriate @NurbsBrepConsistencyException on error.
	template <typename CurveT, typename ConstCurveIteratorT>
	void CheckCurve			(const NurbsBrepCheckControl& control, const ConstCurveIteratorT& curveIt) const;
	void CheckCurve2D		(const NurbsBrepCheckControl& control, const ConstCurve2DIt& curveIt) const;
	void CheckCurve3D		(const NurbsBrepCheckControl& control, const ConstCurve3DIt& curveIt) const;
	void CheckSurface		(const NurbsBrepCheckControl& control, const ConstSurfaceIt& surfaceIt) const;
	void CheckVertex		(const NurbsBrepCheckControl& control, const ConstVertexIt& vertexIt) const;
	void CheckEdge			(const NurbsBrepCheckControl& control, const ConstEdgeIt& edgeIt) const;
	void CheckTrim			(const NurbsBrepCheckControl& control, const ConstTrimIt& trimIt) const;
	void CheckLoop			(const NurbsBrepCheckControl& control, const ConstLoopIt& loopIt) const;
	void CheckFace			(const NurbsBrepCheckControl& control, const ConstFaceIt& faceIt) const;
	void CheckShell			(const NurbsBrepCheckControl& control, const ConstShellIt& shellIt) const;
	void CheckLump			(const NurbsBrepCheckControl& control, const ConstLumpIt& lumpIt) const;

	void CheckEdgeGeometry				(const ConstEdgeIt& edgeIt) const;
	void CheckLoopTopologicalContinuity	(const ConstLoopIt& loopIt) const;
	void CheckLoopGeometricalContinuity	(const NurbsBrepCheckControl& control, const ConstLoopIt& loopIt) const;
	void CheckFaceGeometry				(const NurbsBrepCheckControl& control, const ConstFaceIt& faceIt) const;
	void CheckShellIsClosed				(const ConstShellIt& shellIt) const;
	void CheckShellIsConnected			(const ConstShellIt& shellIt) const;

	void DoCheck (const NurbsBrepCheckControl& control) const;

	void	ReadVersion1								(GS::IChannel& ic);
	void	WriteVersion1								(GS::OChannel& oc) const;
	void	QuickReadCoreData (GS::IChannel& ic);				// no version, no check
	void	QuickWriteCoreData (GS::OChannel& oc) const;		// no version, no check
	// ================================
	//       Public methods
	// ================================
public:
	NurbsBrep (void);
	NurbsBrep (GS::XMLIChannel& inXML);

	bool Equals (const NurbsBrep& other, double eps = SmallEps) const;

	void	Clear ();
	void	Transform (const TRANMAT& tran);
	void	CalculateBounds (Box3D* bounds, const TRANMAT& tran = Geometry::IdentityTranMat) const;
	Box3D	GetBounds (const TRANMAT& tran = Geometry::IdentityTranMat) const;
	void	GetBounds (Box3D* bounds, const TRANMAT& tran = Geometry::IdentityTranMat) const;
	
	// Get
	bool							IsEmpty			()				const { return (m_faces.IsEmpty () && m_edges.IsEmpty ()); }
	
	UInt32							GetVertexCount	()				const { return m_vertices.GetSize ();	}
	const NurbsVertex&				GetConstVertex	(UInt32 index)	const { return m_vertices[index];		}
	UInt32							GetEdgeCount	()				const { return m_edges.GetSize ();		}
	const NurbsEdge&				GetConstEdge	(UInt32 index)	const { return m_edges[index];			}
	UInt32							GetTrimCount	()				const { return m_trims.GetSize ();		}
	const NurbsTrim&				GetConstTrim	(UInt32 index)	const { return m_trims[index];			}
	UInt32							GetLoopCount	()				const { return m_loops.GetSize ();		}
	const NurbsLoop&				GetConstLoop	(UInt32 index)	const { return m_loops[index];			}
	UInt32							GetFaceCount	()				const { return m_faces.GetSize ();		}
	const NurbsFace&				GetConstFace	(UInt32 index)	const { return m_faces[index];			}
	UInt32							GetShellCount	()				const { return m_shells.GetSize ();		}
	const NurbsShell&				GetConstShell	(UInt32 index)	const { return m_shells[index];			}
	UInt32							GetLumpCount	()				const { return m_lumps.GetSize ();		}
	const NurbsLump&				GetConstLump	(UInt32 index)	const { return m_lumps[index];			}
	UInt32							GetCurve2DCount	()				const { return m_curves2D.GetSize ();	}
	const Geometry::NurbsCurve2D&	GetConstCurve2D	(UInt32 index)	const { return m_curves2D[index];		}
	UInt32							GetCurve3DCount	()				const { return m_curves3D.GetSize ();	}
	const Geometry::NurbsCurve3D&	GetConstCurve3D	(UInt32 index)	const { return m_curves3D[index];		}
	UInt32							GetSurfaceCount	()				const { return m_surfaces.GetSize ();	}
	const Geometry::NurbsSurface&	GetConstSurface	(UInt32 index)	const { return m_surfaces[index];		}

	// Build
	UInt32	StoreNurbsCurve2D (const Geometry::NurbsCurve2D& curve);
	UInt32	StoreNurbsCurve2D (const GS::Array<double>&	knotVector, const GS::Array<Coord>& controlPoints, const GS::Array<double>& weights);
	UInt32	StoreNurbsCurve3D (const Geometry::NurbsCurve3D& curve);
	UInt32	StoreNurbsCurve3D (const GS::Array<double>&	knotVector, const GS::Array<Coord3D>& controlPoints, const GS::Array<double>& weights);
	UInt32	StoreNurbsSurface (const Geometry::NurbsSurface& surface);
	UInt32	StoreNurbsSurface (
				const GS::Array<double>&				knotVectorU,
				const GS::Array<double>&				knotVectorV,
				const GS::Array<GS::Array<Coord3D> >&	controlPoints,
				const GS::Array<GS::Array<double> >&	weights);
	UInt32	StoreNurbsVertex (const Coord3D& position, double tolerance);
	UInt32	StoreNurbsEdge (
		UInt32										begVert,
		UInt32										endVert,
		UInt32										curve,
		double										curveBeg,
		double										curveEnd,
		double										tol);
	UInt32	StoreNurbsRingEdge (
		UInt32								curveIdx,
		double								curveBegParam,
		double								curveEndParam,
		double								tol);
	UInt32	StoreNurbsTrim (UInt32 edgeIdx, Int32 curve2DIdx, double curveBegParam, double curveEndParam, double tol);
	UInt32	StoreNurbsSingularTrim (UInt32 vertexIdx, Int32 curve2DIdx, double curveBegParam, double curveEndParam, double tol);
	UInt32	StoreNurbsLoop (const GS::Array<DirectedTrimIndex>& trims);
	UInt32	StoreNurbsFace (const GS::Array<UInt32>&			loops,
							UInt32								surface,
							double								tol);
	UInt32	StoreNurbsShell (const GS::Array<DirectedFaceIndex>& faces);
	UInt32	StoreNurbsLump (const GS::Array<UInt32>& shells);
	
	// throws NurbsBrepConsistencyException
	void Check (const NurbsBrepCheckControl& control) const;

	// throws NurbsBrepConsistencyException
	void							SetCheckControl (const NurbsBrepCheckControl& control);
	const NurbsBrepCheckControl&	GetCheckControl () const;	

	void	MakeWire ();
	void	MakeLamina ();

	ULong GetUsedBytes () const;
	ULong GetHeapUsedBytes () const;

	// Read - write
	void	Read	(GS::IChannel& ic);
	void	Write	(GS::OChannel& oc) const;

	void	QuickRead		(GS::IChannel& ic);				// no version, no check
	void	QuickWrite		(GS::OChannel& oc) const;		// no version, no check
	void	QuickReadCore	(GS::IChannel& ic);				// no version, no check
	void	QuickWriteCore	(GS::OChannel& oc) const;		// no version, no check

	void	ReadXML		(GS::XMLIChannel& inXML);
	void	WriteXML	(GS::XMLOChannel& outXML) const;
	void	WriteXMLToDBChannel	() const;


#ifdef CHECKED_VERSION
	void	DebugCheck () const;
#endif
};



////////////////////////////////////////////////////////////////////////////////
// Traverse on topological parts
////////////////////////////////////////////////////////////////////////////////

// For visiting all trims of a face
class BREP_DLL_EXPORT ConstNurbsTrimOfFaceIterator {
private:
	const NurbsBrep&			brep;
	const NurbsFace&			face;
	// Primary data: state of iterator
	UInt32						actLoopInFaceIdx;
	UInt32						actTrimInLoopIdx;
	// Derived data: filled by sync
	const NurbsLoop*			actLoop;
	const NurbsTrim*			actTrim;
	Int32						actTrimInBrepIdx;

	void	Init ();
	void	Sync ();
	bool	IsEnd ()		const;
public:
	ConstNurbsTrimOfFaceIterator (const NurbsBrep& b, const NurbsFace& f);
	ConstNurbsTrimOfFaceIterator (const NurbsBrep& b, UInt32 fIdx);
	void				operator++ ();
	const NurbsTrim&	operator* ()					const	{ return *actTrim; }
	bool				operator== (std::nullptr_t)		const	{ return IsEnd (); }
	bool				operator!= (std::nullptr_t)		const	{ return !IsEnd (); }
	Int32				GetActTrimIndex ()				const	{ return actTrimInBrepIdx; }
	bool				IsActTrimReversed ()			const;
};


// For visiting all non-singular edges of a face
class BREP_DLL_EXPORT ConstNurbsEdgeOfFaceIterator {
	const NurbsBrep&				brep;
	// Primary data: state of iterator
	ConstNurbsTrimOfFaceIterator	trimIterator;
	// Derived data: filled by sync
	const NurbsEdge*				actEdge;
	Int32							actEdgeIdx;

	void	Init ();
	void	Sync ();
	bool	IsValid ()		const;
	bool	IsEnd ()		const;
public:
	ConstNurbsEdgeOfFaceIterator (const NurbsBrep& b, const NurbsFace& f);
	ConstNurbsEdgeOfFaceIterator (const NurbsBrep& b, UInt32 fIdx);
	void				operator++ ();
	const NurbsEdge&	operator* ()					const	{ return *actEdge; }
	bool				operator== (std::nullptr_t)		const	{ return IsEnd (); }
	bool				operator!= (std::nullptr_t)		const	{ return !IsEnd (); }
	Int32				GetActEdgeIndex ()				const	{ return actEdgeIdx; }
	bool				IsActEdgeReversed ()			const;
};


// For visiting all faces of an edge
class BREP_DLL_EXPORT ConstNurbsFaceOfEdgeIterator {
	const NurbsBrep&			brep;
	const NurbsEdge&			edge;
	// Primary data: state of iterator
	UInt32						actTrimOnEdgeIdx;
	// Derived data: filled by sync
	const NurbsTrim*			actTrim;
	const NurbsLoop*			actLoop;
	const NurbsFace*			actFace;
	Int32						actFaceIdx;

	void	Init ();
	void	Sync ();
	bool	IsValid ()	const;
	bool	IsEnd ()	const;
public:
	ConstNurbsFaceOfEdgeIterator (const NurbsBrep& b, const NurbsEdge& e);
	ConstNurbsFaceOfEdgeIterator (const NurbsBrep& b, UInt32 eIdx);
	void				operator++ ();
	const NurbsFace&	operator* ()					const	{ return *actFace; }
	bool				operator== (std::nullptr_t)		const	{ return IsEnd (); }
	bool				operator!= (std::nullptr_t)		const	{ return !IsEnd (); }
	Int32				GetActFaceIndex ()				const	{ return actFaceIdx; }
	bool				IsActFaceReversed ()			const;	// expensive
};


}	// namespace Brep

#endif // NURBS_BREP_HPP