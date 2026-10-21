// *********************************************************************************************************************
// Description:		Texture Coordinate functions (taken from LC)
//
// Module:			Model3D
// Namespace:
// Contact person:	BA, PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (TEXTURECOORD_HPP)
#define TEXTURECOORD_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Geometry
#include "TMB.h"
#include "Box3DData.h"

// from GSModeler
#include "Model3D/Model3DPrivExp.h"

// from Model3D
#include "Model3D/model.h"
#include "Model3D/LocalCoordSys.hpp"
#include "Model3D/TextureCoordSys.hpp"

namespace Modeler {
	class Model3D;
	class Model3DViewer;
	class Model3DModifier;
	class MeshBody;
	class CandidateMeshBody;
}

namespace GS {
	template <class T>
	class Array;
}

struct UVCoord {
	double	u;
	double	v;
};


// Describes how to treat W_GLOBAL_COORDS flags when calculating a local coordinate system.
enum GlobalCoordsHandling
{
	ApplyGlobalCoords,			// default, treat W_GLOBAL_COORDS normally
	IgnoreAnyGlobalCoords,		// ignore W_GLOBAL_COORDS flags if any of them is set
	IgnoreAllGlobalCoords		// ignore W_GLOBAL_COORDS flags only if all of them are set
};

// --- Function declarations -------------------------------------------------------------------------------------------

class TexTranData {
public:
	BASTRAN		ttran, invttran;
	double		tradius;

	TexTranData () : tradius (0.0)
	{
		BNZeroMemory (&ttran, sizeof (ttran));
		BNZeroMemory (&invttran, sizeof (invttran));
	}
};

template<class MeshBodyType>
class TexCoordCalcDataTemplate {
public:
	void Setup (const MeshBodyType* body, const TRANMAT* tran) {
		this->body = body;
		this->tran = tran;
		this->initialized = false;
		this->lastpgonUV = -1;
		this->lastpgonQ = -1;
	}

	TexCoordCalcDataTemplate (const MeshBodyType* body, const TRANMAT* tran)
	{
		Setup (body, tran);
	}

	const MeshBodyType* body;
	const TRANMAT* tran;

	TexTranData td;

	//TCGetTextureCoord
	bool		initialized;
	WrapMethod	baseWrap;
	COORD3		e1, e2, e3, c0;

	//TCGetTextureCoordFromUV
	Int32	lastpgonUV;
	COORD3	p0, p1, p2;
	UV		uv0, uv1, uv2;

	//TCGetTextureQuadricFitUV
	Int32	lastpgonQ;
	BASTRAN	ptran;
	COORD3	refPoint;
	short	foundEqu;
	double	xc [6], yc [6];
};

typedef TexCoordCalcDataTemplate<Modeler::MeshBody>				TexCoordCalcData;
typedef TexCoordCalcDataTemplate<Modeler::CandidateMeshBody>		CBTexCoordCalcData;

MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	TCGet3DLocalCoords (
						const Wrapping& wrap,
						const Modeler::TextureCoordSys& coor,
						const F_Box3D& bounds,
						const TRANMAT& atran,
						COORD3*		c0,
						COORD3*		e1,
						COORD3*		e2,
						COORD3*		e3);

MODEL3D_PRIVATE_EXPORT
bool	MOD3D_PRIV	TCGetTextureCoord  (
						TexCoordCalcData& calcData,
						const F_Box3D* bounds,
						Int32		ipgon,
						COORD3*		pgonNormal,
						COORD3*		pCoor,
						double*		alfa,
						double*		beta,
						Int32*		selPlane,
						short		pixNum,
						double*		radius,
						bool		forcePlanarProjection = false);

MODEL3D_PRIVATE_EXPORT
bool		MOD3D_PRIV	TCGetPGONTextureCoordinate (
									TexCoordCalcData&		calcData,
									Int32					ipgon,
									const F_Box3D&			bodyBoundsInWorld,
									const Coord3D*			position,
									const Vector3D*			normalVector,
									UVCoord&				textureCoordinate);

MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	TCGetTextureYAxis (const TexCoordCalcData& calcData, WrapMethod wType, Int32 whichPlane, COORD3 *yaxis);

MODEL3D_PRIVATE_EXPORT
bool		MOD3D_PRIV	TCFGetUVCoord2 (TexCoordCalcData& calcData, const F_Box3D& bounds, Int32 ipgon,
										const Vector3D *normal, const Coord3D *point, UVCoord *uv, double* radius);

MODEL3D_PRIVATE_EXPORT
WrapMethod	MOD3D_PRIV	TCPreCalculateLCOO (const Wrapping&	wrap, const Modeler::TextureCoordSys& textureCoordSys, const F_Box3D& bounds, const TRANMAT& atran,
											COORD3 *c0, COORD3 *e1, COORD3 *e2, COORD3 *e3);


MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	TransformPrismRoofLcoo (Coord3D& c0, Coord3D& e1, Coord3D& e2, Coord3D& e3);


MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	TranslateLcooCenterToGlobalOrigo (Coord3D& center, const Coord3D& dir);


MODEL3D_PRIVATE_EXPORT
short		MOD3D_PRIV	TCInitBoxTran	(TexTranData& td, COORD3	*ex, COORD3	*ey, COORD3	*ez);

MODEL3D_PRIVATE_EXPORT
short		MOD3D_PRIV	TCInitSphereTran	(TexTranData& td,
											 COORD3	*e1,
											 COORD3	*e2,
											 COORD3	*e3);

MODEL3D_PRIVATE_EXPORT
short		MOD3D_PRIV	TCInitCylindTran	(TexTranData& td,
											 COORD3	*e1,
											 COORD3	*e2,
											 COORD3	*e3);

MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	TCWorldToCylind	(const TexTranData& td,
										 COORD3		*inWorld,
										 Int32		whichPlane,
										 double		*alfa,
										 double		*beta);

MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	TCWorldToSphere	(const TexTranData& td,
										 COORD3	*inWorld,
										 double	*alfa,
										 double	*beta);

MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	TCWorldToBox	(const TexTranData& td,
										 double	*alfa,
										 double	*beta,
										 COORD3	*inWorld,
										 Int32	whichPlane);

MODEL3D_PRIVATE_EXPORT
bool		MOD3D_PRIV	TCCylindToWorld	(const TexTranData& td,
										 const COORD3&	boxRefer,
										 const COORD3&	e1,
										 const COORD3&	e2,
										 const COORD3&	e3,
										 const COORD3&	pgonNormal,
										 const COORD3&	pgonRefer,
										 double	alfa,
										 double	beta,
										 COORD3& inWorld,
										 Int32	whichPlane);

MODEL3D_PRIVATE_EXPORT
bool		MOD3D_PRIV	TCSphereToWorld	(const TexTranData& td,
										 const COORD3&	boxRefer,
										 const COORD3&	pgonNormal,
										 const COORD3&	pgonRefer,
										 double	alfa,
										 double	beta,
										 COORD3& inWorld);

MODEL3D_PRIVATE_EXPORT
bool		MOD3D_PRIV	TCGetTextureQuadricFitUV (TexCoordCalcData& calcData, Int32 ipgon, COORD3 *pCoor,
												  double *alfa, double *beta, short pixNum = 1);

MODEL3D_PRIVATE_EXPORT
bool		MOD3D_PRIV	TCGetTextureDistanceUV (const Modeler::MeshBody* abody, const TRANMAT& atran,
												Int32 ipgon, COORD3 *pCoor,
												double *alfa, double *beta, short pixNum = 1);

MODEL3D_PRIVATE_EXPORT
bool		MOD3D_PRIV	TCGetTextureCoordFromUV (TexCoordCalcData& calcData,
												 Int32 ipgon, COORD3 *pCoor,
												 double *alfa, double *beta, short pixNum = 1);

MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	CreateCubicTextureParametersOnPoly (Modeler::CandidateMeshBody&	destCandBody,
															Int32					destPgonIndex);

MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	CreateTextureParametersOnPoly (const Modeler::MeshBody&			refBody,
													   Modeler::CandidateMeshBody&		destCandBody,
													   Int32						refPGONIdx,
													   Int32						destPGONIdx,
													   const TRANMAT&					tran);

MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	InheritTextureParametersOnPoly (const Modeler::MeshBody&		refBody,
														Modeler::CandidateMeshBody&		destCandBody,
														Int32						refPGONIdx,
														Int32						destPGONIdx,
														const TRANMAT&					tran);

MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	CreateLcsOnPoly					(Modeler::CandidateMeshBody&	destCandBody,
														 Int32						destPGONIdx,
														 const LocalCoordSys&		lcs);

MODEL3D_PRIVATE_EXPORT
void		MOD3D_PRIV	CreateTextureParametersOnPolyCB (const Modeler::CandidateMeshBody&	refBody,
														 Modeler::CandidateMeshBody&		destCandBody,
														 Int32							refPGONIdx,
														 Int32							destPGONIdx,
														 const TRANMAT&					tran);

MODEL3D_PRIVATE_EXPORT
bool		MOD3D_PRIV	IsTrafoDependent (const Wrapping& wrap);

#endif // TEXTURECOORD_HPP
