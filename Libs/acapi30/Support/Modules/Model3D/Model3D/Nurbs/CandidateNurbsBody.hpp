// *********************************************************************************************************************
// Description:		Boundary representation of a body, boundary is described with NURBS curves and surfaces
//					http://wiki/w/NURBS_Brep_topol%C3%B3gia
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	CsetA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (CANDIDATENURBSBODY_HPP)
#define CANDIDATENURBSBODY_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------


// from Modeler
#include	"Model3D/Nurbs/NurbsBodyPtr.hpp"
#include	"Model3D/Nurbs/NurbsBodyBase.hpp"


// from GSUtils
#include	"GSUtilsDefs.h"


// Predeclarations

namespace Modeler {
class CandidateNurbsBody;

typedef GS::ConstSharedPtr<CandidateNurbsBody>		ConstCandidateNurbsBodyPtr;
typedef GS::SharedPtr<CandidateNurbsBody>			CandidateNurbsBodyPtr;
}

// Types

namespace Modeler {

////////////////////////////////////////////////////////////////////////////////
// CandidateNurbsBody
////////////////////////////////////////////////////////////////////////////////

class MODEL3D_DLL_EXPORT CandidateNurbsBody : public NurbsBodyBase {

	// ================================
	//       Disabled methods
	// ================================
	bool operator== (const CandidateNurbsBody&);	// Not clear if it would mean geometrical or data-structural equality.
													// Use Equals or implement geometrical comparison instead 

	void*	operator new[] (size_t) = delete;
	void	operator delete[] (void*) = delete;

	// ================================
	//       Private methods
	// ================================
private:
	Brep::NurbsBrep& ModifyBrep ();

	void	SetTextureCoordSysForMinMaxWrapping ();
	

	// ================================
	//       Public methods
	// ================================
public:
	CandidateNurbsBody (void) = default;
	CandidateNurbsBody (BrepOperations::NurbsBrepWithLibData&&	brepWithLibData,
						NurbsVertexDataContainerT&&				vertexData,
						NurbsEdgeDataContainerT&&				edgeData,
						NurbsFaceDataContainerT&&				faceData,
						STATL									shadowStatus,
						const NurbsBodyLevelAttrs&				bodyLevelAttrs);
	CandidateNurbsBody (const CandidateNurbsBody& src) = default;
	CandidateNurbsBody (CandidateNurbsBody&& src) = default;
	virtual ~CandidateNurbsBody (void);

	CandidateNurbsBody& operator= (const CandidateNurbsBody&) = default;
	CandidateNurbsBody& operator= (CandidateNurbsBody&&)	  = default;

	CandidateNurbsBody (const NurbsBodyBase& src);

	void	Clear ();
	void	Transform (const TRANMAT& tran);
	
	// Set
	void	SetBodyLevelAttrs	(const Modeler::NurbsBodyLevelAttrs& attrs) { m_attrs = attrs; }
	void	SetShadowStatus		(STATL shadowstat);
	void	SetSmoothness		(double begin, double end);
	void	SetSmoothness		(const NurbsSmoothnessInterval& smoothness);
	void	SetEdgePenIdx		(short pen)				{ m_attrs.edgePenIdx = pen;			}
	void	SetMaterialIdx		(GSAttributeIndex mat)	{ m_attrs.materialIdx = mat;			}

	void	SetWrapping			(const Wrapping& wrapping)		{ m_attrs.wrap = wrapping;		}
	void	SetTextureCoordSys	(const TextureCoordSys& tcs);
	void	SetTextureCoordSys	(const Coord3D& origin, const Coord3D& endOfX, const Coord3D& endOfY, const Coord3D& endOfZ);

	void	SetBodyUserDataContainer (const UserDataContainer* bodyUserDataContainer);
	void	SetBodyUserData (const GS::Guid& guid, const BaseUserData* bodyUserData);
	void	SetLineEliminationBehaviour (LineEliminationBehaviour lineEliminationBehaviour)
	{
		m_attrs.lineEliminationBehaviour = lineEliminationBehaviour;
	}

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
	UInt32	StoreNurbsVertex (const Coord3D& position, NurbsVertexAttributes::Hardness hard, double tolerance);
	UInt32	StoreNurbsEdge (
		UInt32										begVert,
		UInt32										endVert,
		UInt32										curve,
		double										curveBeg,
		double										curveEnd,
		const Modeler::NurbsEdgeAttributes::Status&	stat,
		short										color,
		double										tol);
	UInt32	StoreNurbsRingEdge (
		UInt32								curveIdx,
		double								curveBegParam,
		double								curveEndParam,
		const Modeler::NurbsEdgeAttributes::Status&	stat,
		short								color,
		double								tol);
	UInt32	StoreNurbsTrim (UInt32 edgeIdx, Int32 curve2DIdx, double curveBegParam, double curveEndParam, double tol);
	UInt32	StoreNurbsSingularTrim (UInt32 vertexIdx, Int32 curve2DIdx, double curveBegParam, double curveEndParam, double tol);
	UInt32	StoreNurbsLoop (const GS::Array<Brep::DirectedTrimIndex>& trims);
	UInt32	StoreNurbsFace (const GS::Array<UInt32>&			loops,
							UInt32								surface,
							GSAttributeIndex					mat,
							short								segmentationPen,
							double								tol);
	UInt32	StoreNurbsFace (const GS::Array<UInt32>&			loops,
							UInt32								surface,
							GSAttributeIndex					mat,
							short								segmentationPen,
							const Wrapping&						wrap,
							const Modeler::TextureCoordSys&		textureCoordSys,
							double								tol);
	UInt32	StoreNurbsShell (const GS::Array<Brep::DirectedFaceIndex>& faces);
	UInt32	StoreNurbsLump (const GS::Array<UInt32>& shells);

	void	SetNurbsVertexId	(UIndex vertexIdx,	const NurbsVertexId& vertexId);
	void	SetNurbsEdgeId		(UIndex edgeIdx,	const NurbsEdgeId& edgeId);
	void	SetNurbsFaceId		(UIndex faceIdx,	const NurbsFaceId& faceId);

	void	SetVertexAttributes	(UIndex vertexIdx, const NurbsVertexAttributes& vertexAttributes);
	void	SetEdgeAttributes	(UIndex edgeIdx, const NurbsEdgeAttributes& edgeAttributes);
	void	SetFaceAttributes	(UIndex faceIdx, const NurbsFaceAttributes& faceAttributes);

	void	MakeWire ();
	void	MakeLamina ();

	void	SetAllEdgePenIdx (short pen);
	void	SetAllEdgeInvisible ();
	void	SetAllFaceMaterialAndSegmPenIdx (Int32 mat, short segmentationPen);
	void	SetAllFaceId (const NurbsFaceId& faceId);

	// throws NurbsBrepConsistencyException
	void SetBrepCheckControl (const Brep::NurbsBrepCheckControl& control);
	const Brep::NurbsBrepCheckControl& GetBrepCheckControl () const;	

	// Finalize
	void Compress ();
	void CreateMinMaxWrapping ();
	bool ComplexCheckCompress (const Modeler::CheckReporter* reporter, USize materialCount);

	ConstNurbsBodyPtr	MoveToNurbsBody (const Modeler::CheckReporter* reporter = nullptr, USize materialCount = 0);

	void*	operator new (size_t size);
	void	operator delete (void* pointer);
	void*	operator new (size_t size, void* pointer) noexcept;
	void	operator delete (void* pointer, void*) noexcept;

#ifdef CHECKED_VERSION
	void	DebugCheck () const;
#endif
};


}	// namespace Modeler

#endif
