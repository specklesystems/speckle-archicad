// *********************************************************************************************************************
// Description:		Spatial information of one or more volumes
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_CANDIDATEMESHBODY_HPP)
#define GS_MODELER_CANDIDATEMESHBODY_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"Array.hpp"
#include	"SharedObject.hpp"

// from Geometry
#include	"Box3DData.h"		// F_Box3D Box3D
#include	"KDTreeTypes.hpp"
#include	"KDTreeKeys.hpp"

// from Model3D
#include	"Model3D/MeshBody.hpp"
#include	"Model3D/MeshBodyPtr.hpp"
#include	"Model3D/ModelerAttributes.hpp"
#include	"Model3D/Model3DExport.h"
#include	"Model3D/CheckTask.hpp"
#include	"Model3D/IConstMeshBody.hpp"
#include	"Model3D/BodyLevelAttrs.hpp"

#include	"OU.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

struct BODY_2000;
struct BodyInfo;

// --- Constant definitions	--------------------------------------------------------------------------------------------


// --- Type definitions	------------------------------------------------------------------------------------------------


namespace Modeler {

typedef Geometry::KDTree<Geometry::Vector3DKey, UInt32> NormalTree;

class CandidateMeshBody;

typedef GS::ConstSharedPtr<CandidateMeshBody>		ConstCandidateMeshBodyPtr;
typedef GS::SharedPtr<CandidateMeshBody>			CandidateMeshBodyPtr;

class MODEL3D_DLL_EXPORT CandidateMeshBody : public GS::SharedObject {

public:
	// for reading old formats
	struct OmittedBodyParts {
		Int32	fvert, lvert;
		Int32	fteve;
		Int32	fedge, ledge;
		Int32	fpedg, lpedg;
		Int32	fvect, lvect;
		Int32	fpgon, lpgon;
		Int32	itran;
		ULong	origGeomBodyIndex;
		Int32	coor[NCOOR];
		bool	ftopo	: 1;
		bool	topo	: 1;
		bool	deleted	: 1;
	};

private:

	STATL			m_status;
	MeshBodyLevelAttrs	m_attrs;

	static const USize TextureParamAllocCount = Brep::MeshBrepFB::VertexAllocCount * 3;
	typedef GS::ArrayFB<MeshBody::VertexData, Brep::MeshBrepFB::VertexAllocCount>				VertexDataContT;
	typedef GS::ArrayFB<MeshBody::EdgeData, Brep::MeshBrepFB::PolyEdgeAllocCount>				EdgeDataContT;
	typedef GS::ArrayFB<MeshBody::PolygonData, Brep::MeshBrepFB::PolygonAllocCount>				PolygonDataContT;
	typedef GS::ArrayFB<double, TextureParamAllocCount>										TextureParamsContT;

	Brep::MeshBrepFB				m_meshBrep;
	VertexDataContT					m_vertexData;
	EdgeDataContT					m_edgeData;
	PolygonDataContT				m_polygonData;
	TextureParamsContT				m_textureParams;

	mutable GS::Owner<NormalTree>					m_normalTree;

	bool	Compress (Brep::MeshBrep&				newMeshBrep,
					  GS::Array<MeshBody::VertexData>&	newVertexData,
					  GS::Array<MeshBody::EdgeData>&	newEdgeData,
					  GS::Array<MeshBody::PolygonData>&	newPolygonData,
					  GS::Array<double>&			newTextureParams) const;

	void	DeletePolygons ();	// for MakeWireOnly


	class EdgeIpedgMap;
	void		FixSurfaceOrientation	(EdgeIpedgMap& edgeIpedgMap);
	void		SplitSameDirectionEdges	(EdgeIpedgMap& edgeIpedgMap);
	CheckStatus	CheckSurfaceOrientation	(const EdgeIpedgMap& edgeIpedgMap, const Modeler::CheckReporter& checkReporter) const;

public:
	CandidateMeshBody (void);
	CandidateMeshBody (const Brep::MeshBrep& brep, const MeshBody::VertexData& defaultVertexData, const MeshBody::EdgeData& defaultEdgeData, const MeshBody::PolygonData& defaultPolygonData);
	CandidateMeshBody (const CandidateMeshBody& src);
	CandidateMeshBody (const MeshBody& src);
	CandidateMeshBody (const BODY_2000& srcBODY);

	~CandidateMeshBody ();

	void		Clear (void);
	void		MakeEmpty (void);
	void		ClearGeometry (void);
	void		ClearTextureCoordSys (void);

	bool		IsEmpty (void) const;
	bool		HasSameWrappingAndLocalCoordSys (CandidateMeshBody& srcBody) const;

	const Brep::MeshBrep&	GetConstMeshBrep () const { return m_meshBrep; }
	void		CopyFromIBody (const Cut::IConstMeshBody& srcBody, const TRANMAT& srcTran);
	void		MergeGeometry (CandidateMeshBody& srcBody);
	void		MergeGeometry (const MeshBody& srcBody);

	void		MergeXBodyStatus (const Modeler::MeshBody& otherBody);

	void		AdjustEdgeNeighborPolygons (void);

	void		UpdateStatus ();
	bool		CalculateClosedBody (void) const;
	bool		CalculateSolidBody (void) const;

	CheckStatus	CheckAndFix (const CheckTask& checkTask,
							 const USize materialCount,
							 const Modeler::CheckReporter& checkReporter);

	void		Transform (const TRANMAT& tran);	// ReorientPolygons included
	void		TransformTail_NoReorient (Int32 firstVertex, Int32 firstPolygon, Int32 firstPolyNormal, const TRANMAT& tran);
	void		TransformPart_NoReorient (Int32 firstVertex, Int32 vertexCount, Int32 firstPolygon, Int32 polygonCount, Int32 firstPolyNormal, Int32 polyNormalCount, const TRANMAT& tran);
	
	void		ReorientPolygons	(UIndex fromPolygonIndex = 0);

	void		SetAllEdgePenIdx			(short pen);
	void		SetAllEdgeInvisible			();
	void		SetAllPolygonMaterialIdx	(Int32 mat);
	void		SetAllPolygonId				(const PolygonId& polygonId);
	

	bool		operator== (const Modeler::CandidateMeshBody& other) const;
	bool		operator!= (const Modeler::CandidateMeshBody& other) const { return !operator== (other); }

	Modeler::CandidateMeshBody&		operator= (const Modeler::CandidateMeshBody& src);

	void		CalculateBounds ();
	void		GetBounds (const TRANMAT& trafo, F_Box3D& outBounds) const;
	void		CreateMinMaxWrapping (const GS::Array<UIndex>& omittedVertices);

	// --- Global attributes -------------------------------------------------------------------------------------------

	const F_Box3D&	GetLocalBounds  (void) const;
	
	void				SetupFromBODY (const BODY_2000& srcBody);
	MeshBodyPtr			ToMeshBody	(MPUIDCalculation mpuidCalculation = PreserveMPUIDs) const;

	void		MakeWireOnly (void);

	// --- Polygon handling --------------------------------------------------------------------------------------------

	bool	HasPolygons (void) const;
	ULong	GetPolygonCount (void) const;

	const PGON&		GetConstPolygon (ULong index) const;		// RECOMMENDED: Body-relative, starts from 0
	PGON*			GetPolygon (ULong index);					// RECOMMENDED: Body-relative, starts from 0
	void	SetPolygon (ULong index, const PGON& newPolygon);	// RECOMMENDED: Body-relative, starts from 0
	void	SetPolygonCapacity (ULong capacity);

	const PolygonAttributes& GetConstPolygonAttributes (ULong index) const;
	void SetPolygonAttributes (ULong index, const PolygonAttributes& polygonAttributes);

	const PolygonId&	GetPolygonId (ULong index) const;
	void				SetPolygonId (ULong index, const PolygonId& polygonId);	

	ULong	AddPolygonRec (const PGON& polyRec, const PolygonAttributes& polygonAttributes);					// returns stored index
	void	ReadPolygon (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong count, Int32 modelVersion);

	bool	SelfCompress ();

private:
	void	ReadPolygon110 (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong polyCount);
	void	ReadPolygon51  (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong polyCount);
	void	ReadPolygon41  (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong polyCount);

	// --- Polygon normalvector handling -------------------------------------------------------------------------------
public:
	bool	HasPolyNormals (void) const;
	ULong	GetPolyNormalCount (void) const;

	const Vector3D&	GetConstPolyNormal (ULong index) const;			// RECOMMENDED: Body-relative, starts from 0

	ULong	AddPolyNormalRec (const Vector3D& polyRec);				// returns stored index
	void	SetPolyNormalCapacity (ULong capacity);
	void	ReadPolyNormal (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong count, Int32 modelVersion);

private:
	void	ReadPolyNormal110 (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong polyNormalCount);
	void	ReadPolyNormal455 (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong polyNormalCount);
	void	ReadPolyNormal41  (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong polyNormalCount);

	// --- Polygon edge handling ---------------------------------------------------------------------------------------
public:
	bool	HasPolyEdges (void) const;
	ULong	GetPolyEdgeCount (void) const;

	Int32	GetConstPolyEdge (ULong index) const;			// RECOMMENDED: Body-relative, starts from 0
	void	SetPolyEdge (ULong index, Int32 newPolyEdge);	// RECOMMENDED: Body-relative, starts from 0

	ULong	AddPolyEdgeRec (Int32 polyRec);						// returns stored index
	ULong	AddNPolyEdgeRec (const Int32* polyRecPtr, ULong count);
	void	SetPolyEdgeCapacity (ULong capacity);
	void	ReadPolyEdge (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong polyEdgeCount, Int32 modelVersion);
	Int32	GetBodyVertIdxFromPolyEdgeIdx (Int32 pedgIdx) const;


	// --- Edge handling -----------------------------------------------------------------------------------------------
public:
	bool	HasEdges (void) const;
	ULong	GetEdgeCount (void) const;

	const EDGE&	GetConstEdge (ULong index) const;			// RECOMMENDED: Body-relative, starts from 0
	const EdgeAttributes& GetConstEdgeAttributes (ULong index) const;
	void	SetEdgeAttributes (ULong index, const EdgeAttributes& edgeAttributes);
	EDGE*	GetEdge (ULong index);							// RECOMMENDED: Body-relative, starts from 0
	void	SetEdge (ULong index, const EDGE& newEdge);			// RECOMMENDED: Body-relative, starts from 0

	ULong	AddEdgeRec (const EDGE& edgeRec, const EdgeAttributes& edgeAttributes);				// returns stored index
	void	SetEdgeCapacity (ULong capacity);
	void	ReadEdge (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong count, Int32 modelVersion);

	const EdgeId&		GetEdgeId (ULong index) const;
	void				SetEdgeId (ULong index, const EdgeId& edgeId);

	// --- Vertex handling ---------------------------------------------------------------------------------------------
public:
	bool	HasVertices (void) const;
	ULong	GetVertexCount (void) const;

	const VERT&	GetConstVertex (ULong index) const;			// RECOMMENDED: Body-relative, starts from 0
	Coord3D GetVertexPoint (ULong index, const TRANMAT& trafo = Geometry::IdentityTranMat) const;	// RECOMMENDED: Body-relative, starts from 0
	void	GetVertexCoords (ULong index, const TRANMAT& trafo, double* x, double* y, double* z) const;	// RECOMMENDED: Body-relative, starts from 0
	void	SetVertex (ULong index, const VERT& newVertex);		// RECOMMENDED: Body-relative, starts from 0

	CoordsPosition GetVerticesPosition (Int32 v1, Int32 v2) const;

	ULong	AddVertexRec (const VERT& vertexRec);				// returns stored index
	void	SetVertexCapacity (ULong capacity);
	void	ReadVertex (GS::IChannel& iChannel, GS::PlatformSign inplatform, ULong count, Int32 modelVersion);

	const VertexId&		GetVertexId (ULong index) const;
	void				SetVertexId (ULong index, const VertexId& vertexId);

	bool				GetVertexHardFlag (ULong index) const;
	void				SetVertexHardFlag (ULong index, bool vertexHardFlag);

	// --- Texture Vertex handling -------------------------------------------------------------------------------------
public:
	bool	HasPolygonTextureParameters (void) const;
	ULong	GetPolygonTextureParameterCount (void) const;

	double			GetPolygonTextureParameter (ULong index) const;		// RECOMMENDED: Body-relative, starts from 0
	void			GetPolygonTextureParameters (ULong index, GS::Array<double>* result) const;

	TextureCoordSys	GetPolygonTextureCoordinateSystem (UIndex index) const;
	GS::Array<UV>	GetPolygonTextureUVs (UIndex index) const;

	ULong	AddPolygonTextureParameterRec (double parameter);
	ULong	AddNPolygonTextureParameterRec (const double* parameters, ULong count);
	void	SetPolygonTextureParameterCapacity (ULong capacity);
	void	ClearPolygonTextureParameters (void);

	void	ConvertBodyWrappingToTextureParams (void);
	void	SetSameTextureParamsToBodyWrapping (void);

private:
	void	ReorientPolygonTextureParameters (UIndex fromPolygonIndex = 0);

	// --- Status related ----------------------------------------------------------------------------------------------
private:

	bool		HasStatusMask			(STATL flags) const;
	void		SetStatusMask			(STATL flags);
	void		ClrStatusMask			(STATL flags);
	void		SetOrClrStatusMask		(STATL flags, bool set);

	void		SetClosedBody			(void);
	void		SetOpenBody				(void);			// clear ClosedBody, set SurfaceBody
	void		SetCurvedBody			(void);
	void		SetSharpEdgeBody		(void);
	void		SetCutBody				(void);

public:

	STATL		GetStatus				(void) const	{ return m_status; }
	void		ClearStatus				(void)			{ m_status = MeshBody::NoStatus; }
	void		SetStatus				(STATL status);

	STATL		GetShadowStatus			(void) const	{ return (m_status & MeshBody::ShadowStatusFlags); }
	void		ClearShadowStatus		(void)			{ ClrStatusMask (MeshBody::ShadowStatusFlags); }
	void		SetShadowStatus			(STATL status);
	void		MergeDefShadowStatus	(STATL defShadowStatus);

	bool		IsWireBody				(void) const;
	bool		IsSolidBody				(void) const;
	
	bool		IsCurvedBody			(void) const;
	bool		IsClosedBody			(void) const;
	bool		HasSharpEdge			(void) const;

	bool		HasMultipleColors		(void) const;
	bool		HasMultipleMaterials	(void) const;
	bool		HasMultipleTextures		(void) const;

	bool		IsCutBody				(void) const;
	bool		IsSurfaceBody			(void) const;
	bool		IsShadowBody			(void) const;

	bool		DoesNotReceiveShadow	(void) const;
	bool		AlwaysCastsShadow		(void) const;
	bool		NeverCastsShadow		(void) const;
	bool		AutoCastsShadow			(void) const;

	// can be defined by user
	void		SetSurfaceBody			(bool mark = true);
	void		SetShadowBody			(bool mark = true);

	void		SetReceivesShadow		(void);
	void		SetDoesNotReceiveShadow	(void);
	void		SetAlwaysCastsShadow	(void);
	void		SetNeverCastsShadow		(void);
	void		SetAutoCastsShadow		(void);

	// --- Attributes --------------------------------------------------------------------------------------------------
	void	SetBodyLevelAttrs (const Modeler::MeshBodyLevelAttrs& attrs) { m_attrs = attrs; }
	void	SetMaterialIdx	(GSAttributeIndex materialIdx)	{ m_attrs.materialIdx = materialIdx; }
	void	SetEdgePenIdx	(short edgePenIdx)	{ m_attrs.edgePenIdx = edgePenIdx; }
	void	MergeMaterial	(Int32 materialIdx);
	void	MergeColor		(short penIdx);
	void	SetShapeType	(short shapeType)		{ m_attrs.btype = shapeType; }
	void	SetFatherBind (UInt32 bind)			{ m_attrs.fatherBind = bind; }
	void	SetWrapping (Wrapping wrapping)		{ m_attrs.wrap = wrapping; }
	void	SetLineEliminationBehaviour (LineEliminationBehaviour lineEliminationBehaviour)
	{
		m_attrs.lineEliminationBehaviour = lineEliminationBehaviour;
	}

	void	SetTextureCoordSys (const TextureCoordSys& tcs);
	void	SetTextureCoordSys (const Coord3D& origin, const Coord3D& endOfX, const Coord3D& endOfY, const Coord3D& endOfZ);

	void	OverwriteMaterials (const GS::Array<Int32>* iumatPerPoly, Int32 defaultIumat);
	void	OverwriteEdgeColors (const GS::Array<short>* colorPerEdge, short defaultColor);
	void	OverwriteEdgeStatuses (const GS::Array<Int32>* statusPerEdge, Int32 defaultEdgeStatus);

	void	SetBodyUserDataContainer (const UserDataContainer* bodyUserDataContainer)
	{
		m_attrs.bodyUserDataContainer = GS::ToOptionalOnHeap (bodyUserDataContainer);
	}

	void	SetBodyUserData (const GS::Guid& guid, const BaseUserData* bodyUserData)	{ 
		if (m_attrs.bodyUserDataContainer.IsEmpty () && bodyUserData != nullptr) {
			m_attrs.bodyUserDataContainer = UserDataContainer ();
		}
		if (m_attrs.bodyUserDataContainer.HasValue ()) {
			m_attrs.bodyUserDataContainer->SetUserData (guid, bodyUserData);
			if (m_attrs.bodyUserDataContainer->GetSize () == 0) {
				m_attrs.bodyUserDataContainer.Clear ();
			}
		}
	}

	void	ClearAllUserData ()
	{
		m_attrs.bodyUserDataContainer.Clear ();
	}

	const MeshBodyLevelAttrs&	GetBodyLevelAttrs () const { return m_attrs; }
	Int32	GetMaterialIdx (void) const		{ return m_attrs.materialIdx; }
	short	GetEdgePenIdx (void) const		{ return m_attrs.edgePenIdx; }
	short	GetShapeType (void) const		{ return m_attrs.btype; }
	UInt32	GetFatherBind (void) const		{ return m_attrs.fatherBind; }
	Wrapping GetWrapping (void) const		{ return m_attrs.wrap; }
	LineEliminationBehaviour	GetLineEliminationBehaviour () const { return m_attrs.lineEliminationBehaviour; }

	const UserDataContainer* GetBodyUserDataContainer (void) const { return m_attrs.bodyUserDataContainer.GetPtr (); }

	const BaseUserData*	GetBodyUserData (const GS::Guid& guid) const	{ 
		return m_attrs.bodyUserDataContainer.HasValue () ? m_attrs.bodyUserDataContainer->GetUserData (guid): nullptr;
	}

	const TextureCoordSys&	GetTextureCoordSys () const;
	TextureCoordSys			GetTextureCoordSys (const TRANMAT& tran) const;
	bool					HasSameTextureCoordinateSystem (const MeshBody& body) const;
	bool					HasSameTextureCoordinateSystem (const CandidateMeshBody& body) const;

	bool	IsInvisible (void) const {
		DBASSERT (HAS_ONLY_FLAGS (m_status, MeshBody::ValidStatusFlags));			// Note. MeshBody::Deleted is deprecated
		return HAS_ANY_FLAGS (m_status, MeshBody::Deleted) || IsShadowBody ();
	}

public:
	ULong	StoreVertex (double x, double y, double z);
	void	StoreTextureParametersAndSetPolygonAttributes (UIndex polygonIndex, const PolygonAttributes& polygonAttributes, const GS::Array<double>* tParams);
	void	TransformPolygonTextureParameters (Int32 ipgon, const TRANMAT* tran);
	Int32	StoreEdge (short color, Int32 vert1, Int32 vert2, Int32 pgon1, Int32 pgon2, STATL status, short gmode);
	Int32	StorePolyNormal (double x, double y, double z);
	Int32	StorePolygon (Int32 iumat, Wrapping tproj, Int32 irtxt, Int32 mpuid, Int32 ivect, Int32 npedg, Int32 *ipedg, const GS::Array<double>* tParams, STATL status);
	ULong	StoreAndCheckCompletePolygon (Int32 iumat, Wrapping tproj, Int32 itxtu, Int32 npedg, Int32* ipedg, const GS::Array<double>* tParams, STATL pstat, bool ncheck);
	ULong	StorePolygonWithPolyEdges (Int32 iumat, Wrapping tproj, Int32 irtxt, Int32 ivect, Int32 npedg, Int32* ipedg, const GS::Array<double>* tParams, STATL pstat);
	Int32	StoreUnitPolyNormal (double x, double y, double z);
	void	CalculateLoopNormal (Int32 npedg, const Int32* ipedg, double* nx, double* ny, double* nz, const Vector3D* referenceNormal = nullptr) const;
	bool	CalcUnitNormalFrom3Verts (Int32 v1, Int32 v2, Int32 v3, double* nx, double* ny, double* nz) const;
	STATL	CalcLoopConcaveAndHoleStatus (Int32 npedg, const Int32 *ipedg) const;
	STATL	CalcLoopConcaveAndHoleStatusOfStoredPgon (Int32 ipgon) const;
	Int32	AttachPolygonToPolyEdges (Int32 ipgon, Int32 npedg, const Int32* const ipedg);
	
	Int32	GetPolyEdgeStartVertex (Int32 pedg) const;
	Int32	GetPolyEdgeEndVertex (Int32 pedg) const;

	void	InvalidateEdge (Int32 iedge);
	bool	IsEdgeInvalidated (Int32 iedge) const;

	void	InvalidatePolygon (Int32 ipgon);
	bool	IsPolygonInvalidated (Int32 ipgon) const;

	//BodyUtils
	short	IsPgonApexConcave (Int32 ivect, Int32 v1, Int32 v2, Int32 v3) const;
	short	CheckPolygonNormal (Int32 rivect,
						   Int32 npedg, Int32 *ipedg,
						   bool holecheck, bool strong) const;
	short	CheckPolygonNormal (Int32 ipgon,
						   bool holecheck, bool strong) const;
	Int32	SearchPgonNormal (Int32 sfvect, Int32 slvect,
								 double x, double y, double z) const;

	void	GetPVert3 (Int32 a1, Int32 a2,
					  Int32 *v1, Int32 *v2, Int32 *v3) const;	// throws exception


public:
	GSErrCode	Read (GS::IChannel& ic);

	void		DumpGDL (GS::OChannel& oc, bool minimalDump = false) const;
	void		DumpGDLToDBChannel () const;
	void		DumpMinimalGDLToDBChannel () const;

	void*	operator new (size_t size);
	void	operator delete (void* pointer);
	void*	operator new (size_t size, void* pointer) noexcept;
	void	operator delete (void* pointer, void*) noexcept;
private:
	struct	NormalClassification {
		bool		invalid;
		ULong		index;

		NormalClassification () : invalid (false), index (0) {}

		bool	IsInvalid (void) const	{ return invalid; }
		void	SetInvalid (ULong i)	{ invalid = true; index = i; }
		bool	IsOK (void) const		{ return !invalid; }
		void	SetOK (void)			{ invalid = false; }
	};

	NormalClassification	CorrectNormals (const CheckTask& checkTask);
	CheckStatus				ClassifyDoubles (void) const;

	void*	operator new[] (size_t) = delete;
	void	operator delete[] (void*) = delete;
};



}	// namespace Modeler

#include "Model3D/CandidateMeshBodyImp.hpp"

#endif

