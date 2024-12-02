// *********************************************************************************************************************
// Description:		Helper functions for the MeshBody
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (MESHBODYUTILS_HPP)
#define MESHBODYUTILS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

// from Geometry
#include	"Plane.hpp"

// from Model3D
#include	"Model3D/model.h"
#include	"Model3D/MeshBodyPtr.hpp"
#include	"Model3D/EdgeAttributes.hpp"
#include	"Model3D/PolygonAttributes.hpp"

// from GSModeler
#include	"Model3D/Model3DExport.h"
#include	"Model3D/TextureCoordSys.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PC {
	class Matrix;
}

namespace Geometry {
	template <USize rowCount, USize colCount, typename T>
	class Matrix;

	typedef Matrix<4, 4, double> Matrix44d;
}

namespace Modeler {
	class Elem;
	class MeshBody;
	class CandidateMeshBody;
	class Model3DViewer;

// --- Constant definitions	--------------------------------------------------------------------------------------------

#define	VECTEPS		10e-7

// --- Type definitions	------------------------------------------------------------------------------------------------

template <class MeshBodyType>
class MODEL3D_DLL_EXPORT CompactConstPolygon {
public:
	enum VertexOrdering {Oriented, AsItIsStored};
private:
	const MeshBodyType&		body;
	const UInt32			polygonIdx;
	const Modeler::PGON&	pgon;

	Int32					actualPolygonEdgeIdx;
	Int32					actualPolyEdge;
	const TRANMAT*			tran;
public:
	//------------------
	//		ctor(s)
	//------------------
	CompactConstPolygon (const MeshBodyType& body, UInt32 polygonIdx, const TRANMAT& tran = Geometry::IdentityTranMat);
	// Properties
	bool					IsValid ()				const;
	// Data Access
	const Modeler::PGON&	Get ()					const;
	const MeshBodyType&		GetMeshBody ()				const;
	UInt32					GetPolygonIdx ()		const;
	const TRANMAT*			GetTran ()				const;

	Int32					GetActualPolyEdge ()	const;
	const EDGE&				GetActualEdge ()		const;
	void					GetActualEdgeVertices (Coord3D& v1, Coord3D& v2, VertexOrdering ordering = Oriented) const;
	Coord3D					GetActualVertex ()		const;
	// Iterators
	void					ResetIterator ();
	bool					IsEnd ()				const;
	bool					Next ();
	void					NextNonHole ();
};


MODEL3D_DLL_EXPORT
void EnumerateBodyPgonVertices (const Modeler::MeshBody& body, const TRANMAT* tran, Int32 pgonIndex, const std::function<bool (const Coord3D&)>& func);

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

/************************************************************************/
/*				Surface Volume related utilities						*/
/************************************************************************/

MODEL3D_DLL_EXPORT
double MODEL3D_CALL	PolygonPyramidSignedVolume (const Modeler::MeshBody& body,
												UIndex pgonIdx,
												const Coord3D& pyramidTop);


// -----------------------------
// CalcPolygonMidpointNormalArea
// -----------------------------
// Template declaration: No need for dll exportation since this is just a declaration, hence it could not be exported at all!
template <typename MeshBodyType>
MODEL3D_DLL_EXPORT
void MODEL3D_CALL CalcPolygonMidpointNormalArea (	CompactConstPolygon<MeshBodyType>& compactPoly,
													Coord3D&								midpoint,
													Vector3D&								normal);


// -----------------------------
// GetPgonSurface
// -----------------------------
// Template declaration: No need for dll exportation since this is just a declaration, hence it could not be exported at all!
template <typename MeshBodyType>
MODEL3D_DLL_EXPORT
double MODEL3D_CALL GetPgonSurface (const MeshBodyType& body, ULong polygonIndex, const TRANMAT* elemTran);


// -----------------------------
// CalcBodySurfaceVolume
// -----------------------------
// Template declaration: No need for dll exportation since this is just a declaration, hence it could not be exported at all!
template <typename MeshBodyType>
MODEL3D_DLL_EXPORT
	void MODEL3D_CALL CalcBodySurfaceVolume (const MeshBodyType& body, const TRANMAT& elemTran, double* const surface, double* const signedVolume);

// -----------------------------
// AddElemSurfaceVolume
// -----------------------------
// It is the caller responsibility to clear variables if it is desired!
MODEL3D_DLL_EXPORT
bool MODEL3D_CALL AddElemSurfaceVolume (const Modeler::Elem&	elem,
										double*					surface,
										double*					volume);

/************************************************************************/
/*                                                                      */
/************************************************************************/
MODEL3D_DLL_EXPORT
short	MODEL3D_CALL IsPgonApexConcave (const MeshBody& body, Int32 ivect, Int32 v1, Int32 v2, Int32 v3);

MODEL3D_DLL_EXPORT
Int32	MODEL3D_CALL SearchPgonNormal (const MeshBody& body, Int32 sfvect, Int32 slvect, // searches a range
								  double x, double y, double z);
MODEL3D_DLL_EXPORT
short	MODEL3D_CALL CheckPgonNormal (const MeshBody& body, Int32 rivect, Int32 npedg, Int32 *ipedg, bool holecheck, bool strong);

MODEL3D_DLL_EXPORT
Int32	MODEL3D_CALL GetTriangleVertexIndexFromCPols (Int32* inCPols, Int32 polygonIndex, Int32 vertexIndex);

typedef GS::Pair<ConstMeshBodyPtr, const TRANMAT*> BodyTranmatPair;

MODEL3D_DLL_EXPORT
ConstMeshBodyPtr	MODEL3D_CALL	UnifyBodies (const GS::Array<BodyTranmatPair>& bodies, const TRANMAT* resTran);

MODEL3D_DLL_EXPORT
bool	MODEL3D_CALL	IsValidWrappingOnBody (Wrapping wrap);

MODEL3D_DLL_EXPORT
bool	MODEL3D_CALL	IsBaseWrappingOnBody (Wrapping wrap);

MODEL3D_DLL_EXPORT
bool	MODEL3D_CALL	IsValidWrappingOnPolygon (Wrapping wrap);

MODEL3D_DLL_EXPORT
bool	MODEL3D_CALL	IsUVWrappingOnPolygon (Wrapping wrap);

MODEL3D_DLL_EXPORT
bool	MODEL3D_CALL	IsLocalCoordSysWrappingOnPolygon (Wrapping wrap);

MODEL3D_DLL_EXPORT
Wrapping	MODEL3D_CALL	CalculatePolygonWrappingFromBodyWrapping (const Modeler::MeshBody& constBody, Modeler::TextureCoordSys& lcoo);

MODEL3D_DLL_EXPORT
void	MODEL3D_CALL	ConvertTextureVerticesToPolygonTextureParamters (Modeler::CandidateMeshBody& body, const GS::Array<TEVE>& teves);

MODEL3D_DLL_EXPORT
void	MODEL3D_CALL	TextureCoordinateSystemToPolygonTextureParameters (const Modeler::TextureCoordSys& tcs, GS::Array<double>& doubles);

MODEL3D_DLL_EXPORT
Modeler::ConstMeshBodyPtr	MODEL3D_CALL	CreateBoundingBoxMeshBody (const Box3D& box);

MODEL3D_DLL_EXPORT
Modeler::TextureCoordSys	MODEL3D_CALL PolygonTextureParametersToTextureCoordinateSystem (const GS::Array<double>& coords);

MODEL3D_DLL_EXPORT
void	MODEL3D_CALL	DiagnoseBodyDiff (const Modeler::MeshBody& body1, const Modeler::MeshBody& body2);

MODEL3D_DLL_EXPORT
Modeler::EdgeAttributes MODEL3D_CALL CorrectSmoothEdgeFlagForMorph (const Modeler::EdgeAttributes& edgeAttibutes,
																	const Modeler::PolygonAttributes *pgon1 = nullptr,
																	const Modeler::PolygonAttributes *pgon2 = nullptr);

MODEL3D_DLL_EXPORT
Modeler::EdgeAttributes MODEL3D_CALL CorrectSmoothEdgeFlagForNurbs (const Modeler::EdgeAttributes& edgeAttibutes,
																	const Modeler::PolygonAttributes *pgon1 = nullptr,
																	const Modeler::PolygonAttributes *pgon2 = nullptr);

}	// namespace Modeler

#endif

