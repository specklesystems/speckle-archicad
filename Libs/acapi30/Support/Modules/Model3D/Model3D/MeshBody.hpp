// *********************************************************************************************************************
// Description:		Spatial information of one or more volumes
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_MESHBODY_HPP)
#define GS_MODELER_MESHBODY_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"Array.hpp"
#include	"SharedObject.hpp"
#include	"Owner.hpp"
#include	"Md5.hpp"

// from Geometry
#include	"Box3DData.h"		// F_Box3D Box3D

// from Model3D
#include	"Model3D/model.h"		// VERT HOTS TEVE
#include	"Model3D/EdgeAttributes.hpp"
#include	"Model3D/PolygonAttributes.hpp"
#include	"Model3D/PolygonConvexDecomposition.hpp"
#include	"Model3D/ModelerAttributes.hpp"
#include	"Model3D/Model3DExport.h"
#include	"Model3D/Model3DPrivExp.h"
#include	"Model3D/VertexId.hpp"
#include	"Model3D/EdgeId.hpp"
#include	"Model3D/PolygonId.hpp"
#include	"Model3D/UserDataContainer.hpp"
#include	"Model3D/RoundBodyNormals.hpp"
#include	"Model3D/BodyMemberComparator.hpp"
#include	"Model3D/TextureCoordSys.hpp"
#include	"Model3D/BodyLevelAttrs.hpp"

// from GDL
#include	"GDLWrapping.hpp"

#include	<float.h>

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {
	class OChannel;
	class IChannel;
	class XMLOChannel;
	class XMLIChannel;
	class ProcessControl;
}
struct List3dRec;

// --- Constant definitions	--------------------------------------------------------------------------------------------

#define MESHBODY_WRITE_NUM_PREC int (DBL_DIG - 2)

// --- Type definitions	------------------------------------------------------------------------------------------------
namespace Modeler {

class ConstMeshBodyVertexIterator;
class ConstMeshBodyEdgeIterator;
class ConstMeshBodyPolygonIterator;
class ConstMeshBodyPolyEdgeIterator;


class CoordsPosition {
	public:
	enum Position { Different, Identical, Equal };
	CoordsPosition (const CoordsPosition& positionIn) : position (positionIn.position) {}
	CoordsPosition (Position positionIn) : position (positionIn) {}
	const CoordsPosition& operator= (const CoordsPosition& positionIn) { position = positionIn.position; return *this; }
	bool operator== (Position positionIn) const { return position == positionIn; }
	bool operator!= (Position positionIn) const { return position != positionIn; }

	private:
		Position position;
};

class MODEL3D_DLL_EXPORT MeshBody : public GS::SharedObject {
	static GS::ClassInfo classInfo;

public:
	struct VertexData {
		VertexId	vertexId;
		bool		vertexHardFlag;

		VertexData () : vertexHardFlag (false) {};
	};

	struct EdgeData {
		EdgeAttributes	edgeAttributes;
		EdgeId			edgeId;
	};

public:
	struct PolygonData {
		PolygonAttributes	polygonAttributes;
		PolygonId			polygonId;
	};

	class MODEL3D_DLL_EXPORT IWriteAttributesToGDL
	{
	public:
		virtual GS::UniString	Out_Mater (GSAttributeIndex	 i) = 0;
		virtual GS::UniString	Out_Pen (short i) = 0;

		virtual ~IWriteAttributesToGDL ();
	};

public:
	enum Status
	{
		NoStatus		= 0x00000000,	//
		ClosedBody		= 0x00000001,	// automatic
		CurvedBody		= 0x00000002,	// automatic
		SurfaceBody		= 0x00000004,	// user					// SURFACEBIT
		CutBody			= 0x00000008,	// automatic
		ShadowOn		= 0x00000020,	// user
		ShadowOff		= 0x00000040,	// user
		ShadowNot		= 0x00000080,	// user
		MulRtxt			= 0x00000100,	// deprecated			// MULRTXTBIT
		MulColor		= 0x00000200,	// deprecated			// MULCOLORBIT
		MulUmat			= 0x00000400,	// deprecated			// MULUMATBIT
		FTopo			= 0x00001000,	// deprecated			// FTOPOBIT
		Topo			= 0x00002000,	// deprecated			// TOPOBIT
		ShadowBody		= 0x00004000,	// deprecated			// SHADOW_MARK_BIT, equivalent to shape type B_SHADOW
		Deleted			= 0x00008000,	// deprecated			// DELBIT
		SharpEdgeBody	= 0x00040000,	// automatic

		// shadow-related flags								// ShadowOn and ShadowOff are mutually exclusive
		ShadowStatusFlags		= ShadowOn					// the body always casts shadow
								| ShadowOff					// the body never casts shadow
															// if neither of ShadowOn and ShadowOff is set, shadow casting is decided automatically
															// if both ShadowOn and ShadowOff are set, ShadowOn wins (this case violates invariant)
								| ShadowNot,				// the body does not receive shadow from other bodies

		// automatically calculated flags, currently calculated CandidateMeshBody::UpdateBodyFlags, called by CandidateMeshBody::CheckAndFix
		AutomaticStatusFlags	= ClosedBody				// all edges of the body has two side polygons (no contour and standalone edges)
								| CurvedBody				// the body has at least one edge with VISIBLEIFCONTOURBIT or one polygon with CURVEDBIT set
								| SharpEdgeBody				// the body has a sharp edge (REND_SHARP_EDGE set)
								| CutBody,					// the body has edges or polygons created by a cut operation
															// (ON_CUT_BIT, ON_MODEL_CUT_BIT or ON_SECT_CUT_SPEC_BIT)

		// flags that set by the user of the body/candidate body
		// Surface is a flag that can be set by the user OR automatically (if the body is not closed and not wireframe)
		UserStatusFlags			= SurfaceBody				// the body defines a surface instead of a solid
															// (affects solid and cut operations and, I guess,
															//  used to set backface culling on/off while rendering)
								| ShadowStatusFlags,

		ValidStatusFlags		= AutomaticStatusFlags
								| UserStatusFlags,

		DeprecatedStatusFlags	= Deleted					// used only in FL.c for old binary I/O
								| FTopo						// used only in FL.c for old binary I/O
								| Topo						// used only in FL.c for old binary I/O
								| ShadowBody				// never used
								| MulColor					// never used
								| MulUmat					// never used
								| MulRtxt					// never used
	};

private:
	MeshBodyLevelAttrs	m_attrs;
	STATL				m_status;		// Deprecated flags: Deleted/DELBIT, Topo/TOPOBIT, FTopo/FTOPOBIT


	void ClearAndSetupBuffers (USize vertexCount, USize edgeCount, USize polyEdgeCount, USize polyNormalCount, USize polygonCount, USize textureParamCount,
					   USize vertexHardFlagCount, USize vertexIdCount, USize edgeIdCount, USize polygonIdCount);

	GS::Owner<std::byte[]>									m_buffer;
	Brep::MeshBrep											m_meshBrep;
	Brep::ExternalBufferArray<EdgeAttributes>				m_edgeAttributes;
	Brep::ExternalBufferArray<PolygonAttributes>			m_polygonAttributes;
	Brep::ExternalBufferArray<double>						m_textureParams;
	Brep::ExternalBufferArray<PolygonConvexDecomposition>	m_polygonConvexDecompositions;
	Brep::ExternalBufferArray<char>							m_vertexHardFlags;
	Brep::ExternalBufferArray<VertexId>						m_vertexIds;
	Brep::ExternalBufferArray<EdgeId>						m_edgeIds;
	Brep::ExternalBufferArray<PolygonId>					m_polygonIds;

	static const Int32 RVNotInited = 0;
	static const Int32 RVInitInProgress = 1;
	static const Int32 RVInited = 2;
	mutable	volatile Int32		m_roundVectorsInitialized = RVNotInited;
	mutable	GS::Array<Vector3D>	m_roundVectors;	// cache with lazy initialization

private:
	void	CalculateMpuids ();

	void	SetupFromElemArrays (
		const GS::PagedArray<VERT>& vertices_in,
		const GS::PagedArray<VertexId>& vertexIds_in,
		const GS::PagedArray<bool>& vertexHardFlags_in,
		const GS::PagedArray<double>& textureParams_in,
		const GS::PagedArray<EDGE>& edges_in,
		const GS::PagedArray<EdgeAttributes>& edgeAttributes_in,
		const GS::PagedArray<EdgeId>& edgeIds_in,
		const GS::PagedArray<Int32>& polyEdges_in,
		const GS::PagedArray<Vector3D>& polyNormals_in,
		const GS::PagedArray<PGON>& polygons_in,
		const GS::PagedArray<PolygonAttributes>& polygonAttributes_in,
		const GS::PagedArray<PolygonId>& polygonIds_in
	);

	Modeler::MeshBody&		operator= (const Modeler::MeshBody& src); // disable

	void	Init (void);

	void	InitRoundNormVectors (void) const;

	void	Transform (const TRANMAT& tran);

	void	CalculateBounds ();

	void	SetTextureCoordSys (const TextureCoordSys& tcs);

	PGON*	GetPolygon	(ULong index);
	void	SetPolyEdge	(ULong index, Int32 polyEdgeIn);

public:
				MeshBody (
					STATL status_in,
					const MeshBodyLevelAttrs& bodyLevelAttrs,
					const Brep::MeshBrep& meshBrep,
					const GS::Array<VertexData>& vertexData_in,
					const GS::Array<double>& textureParams_in,
					const GS::Array<EdgeData>& edgeData_in,
					const GS::Array<PolygonData>& polygons_in,
					MPUIDCalculation mpuidCalculation = PreserveMPUIDs
					);

				MeshBody (
					STATL status_in,
					const MeshBodyLevelAttrs& bodyLevelAttrs,
					const GS::PagedArray<VERT>& vertices_in,
					const GS::PagedArray<VertexId>& vertexIds_in,
					const GS::PagedArray<bool>& vertexHardFlags_in,
					const GS::PagedArray<double>& textureParams_in,
					const GS::PagedArray<EDGE>& edges_in,
					const GS::PagedArray<EdgeAttributes>& edgeAttributes_in,
					const GS::PagedArray<EdgeId>& edgeIds_in,
					const GS::PagedArray<Int32>& polyEdges_in,
					const GS::PagedArray<Vector3D>& polyNormals_in,
					const GS::PagedArray<PGON>& polygons_in,
					const GS::PagedArray<PolygonAttributes>& polygonAttributes_in,
					const GS::PagedArray<PolygonId>& polygonIds_in,
					MPUIDCalculation mpuidCalculation = PreserveMPUIDs
				);

				// Create empty body
				MeshBody (const UserDataContainer* userDataContainer_in);
				MeshBody (const MeshBody& src, const TRANMAT* trafo = nullptr); // full copy + optional trafo

				// MeshBody channel input constructors
				MeshBody (GS::IChannel& ic);
				MeshBody (GS::IChannel& ic, GS::Array<UIndex>& unusedCoorVertices);
				MeshBody (GS::XMLIChannel& inXML);

			   ~MeshBody ();


	bool											Equals (const Modeler::MeshBody& other) const;
	Modeler::BodyMemberSorter::CompareResult		CompareGeometry (const Modeler::MeshBody& other) const;

	enum MPUIDCheck { CheckMPUID, ByPassMPUID };
	bool		EqualShapeAndAttributesWithShuffle (const Modeler::MeshBody& other, MPUIDCheck mpuidCheck = CheckMPUID) const;

	void		QuickWriteCore (GS::OChannel& oc, ModelOLookup& lookup, const Modeler::Attributes::Viewer* attrViewer) const;	// no versioning, no checking
	void		QuickReadCore (GS::IChannel& ic, ModelILookup& lookup, Modeler::Attributes::Modifier* attrModifier, const Modeler::IAttributeReader* attReader);  // no versioning, no checking

	void		GetBounds (const TRANMAT& trafo, F_Box3D& outBounds) const;
	void		Print (GS::ProcessControl& processControl, GS::OChannel& oc, short replevel, const List3dRec *list3d, const TRANMAT* atran, Int32 gpgon) const;
	void		PrintAsTestCase (GS::OChannel& oc) const;
	void		PrintAsTestCaseToDBChannel () const;

	void		WriteXML (GS::XMLOChannel& outXML) const;
	void		WriteXMLToDBChannel () const;


	// --- Status related ----------------------------------------------------------------------------------------------

	STATL		GetStatus				(void) const	{ return m_status; }
	STATL		GetShadowStatus			(void) const	{ return m_status & ShadowStatusFlags; }

	bool		IsWireBody				(void) const;	// not a status flag but related
	bool		IsSolidBody				(void) const;	// not a status flag but related

	bool		IsClosedBody			(void) const;
	bool		IsCurvedBody			(void) const;
	bool		HasSharpEdge			(void) const;

	bool		IsSurfaceBody			(void) const;
	bool		IsCutBody				(void) const;

	bool		DoesNotReceiveShadow	(void) const;
	bool		AlwaysCastsShadow		(void) const;
	bool		NeverCastsShadow		(void) const;
	bool		AutoCastsShadow			(void) const;

	// --- O(n) methods ------------------------------------------------------------------------------------------------
	bool		HasMultipleColors		(void) const;
	bool		HasMultipleMaterials	(void) const;
	bool		HasMultipleTextures		(void) const;

public:

	// --- Global attributes -------------------------------------------------------------------------------------------

	const MeshBodyLevelAttrs&	GetBodyLevelAttrs () const { return m_attrs; }
	Int32				GetMaterialIdx (void) const		{ return m_attrs.materialIdx; }
	short				GetEdgePenIdx (void) const		{ return m_attrs.edgePenIdx; }
	short				GetShapeType (void) const		{ return m_attrs.btype; }
	UInt32				GetFatherBind (void) const		{ return m_attrs.fatherBind; }
	Wrapping			GetWrapping (void) const		{ return m_attrs.wrap; }
	LineEliminationBehaviour	GetLineEliminationBehaviour () const { return m_attrs.lineEliminationBehaviour; }

	const Brep::MeshBrep&		GetConstMeshBrep () const { return m_meshBrep;  }

	const UserDataContainer*	GetBodyUserDataContainer (void) const		{ return m_attrs.bodyUserDataContainer.GetPtr (); }

	const BaseUserData*	GetBodyUserData (const GS::Guid& guid) const		{ return m_attrs.bodyUserDataContainer.HasValue () ? m_attrs.bodyUserDataContainer->GetUserData (guid) : nullptr; }

	const TextureCoordSys&	GetTextureCoordSys () const;
	TextureCoordSys			GetTextureCoordSys (const TRANMAT& tran) const;
	bool					HasSameTextureCoordinateSystem (const MeshBody& body) const;
	
	bool		IsInvisible (void) const	{ return GetShapeType () == B_SHADOW; }

	const F_Box3D&	GetLocalBounds  (void) const;

	ULong		GetUsedBytes (void) const;

	bool		IsEmpty () const;
	bool		HasVisibleParts () const;

	// --- Polygon handling --------------------------------------------------------------------------------------------

	bool	HasPolygons (void) const;
	ULong	GetPolygonCount (void) const;

					const PGON&			GetConstPolygon (ULong index) const;
					const PolygonAttributes& GetConstPolygonAttributes (ULong index) const;
	GS_FORCE_INLINE	const PolygonId&	GetPolygonId	(ULong index) const;

	// --- Polygon normalvector handling -------------------------------------------------------------------------------
public:
	bool	HasPolyNormals (void) const;
	ULong	GetPolyNormalCount (void) const;

	const Vector3D&	GetConstPolyNormal (ULong index) const;
	Vector3D GetNormalVectorByEdge (	UInt32								bodyEdgeIndex,
										EdgeVertexPolygonConfiguration		normalVectorIdentifier,
										const TRANMAT&						trafo = Geometry::IdentityTranMat) const;

	Vector3D GetPolygonNormalVectorByVertex (UIndex polygonIndex, UInt32 polyVertexIdx, const TRANMAT& trafo) const;

	// --- Polygon edge handling ---------------------------------------------------------------------------------------
public:
	bool	HasPolyEdges (void) const;
	ULong	GetPolyEdgeCount (void) const;

	Int32	GetConstPolyEdge (ULong index) const;

	USize	GetPolyEdgeUsedBytes (void) const;
	Int32	GetBodyVertIdxFromPolyEdgeIdx (Int32 pedgIdx) const;
	bool	GetBodyIndicesFromPolyEdge (Int32 polyEdgeIdx, Int32 *edgeIdx, Int32 *begVertIdx, Int32 *endVertIdx) const;
	void	GetBodyVertIndicesFromPolyEdges (Int32 firstEdgeIdxInPoly, bool* isInHole, Int32* v1, Int32* v2, Int32* v3) const;

	Int32	GetPolyEdgeStartVertex (Int32 pedg) const;
	Int32	GetPolyEdgeEndVertex (Int32 pedg) const;

		// --- Convex Polygon Decomposition handling ------------------------------------------------------------------------------
private:
	const Int32*	GetTriIpedgs (ULong pgonIndex) const;
public:
	bool	 IsDecomposedIntoTriangles		(ULong pgonIndex) const;
	Int32	 GetConvexPolygonCount			(ULong pgonIndex) const;
	Int32	 GetConvexPolygonVertexCount	(ULong pgonIndex, Int32 convPolyIdx) const;
	Int32	 GetConvexPolygonVertexIndex	(ULong pgonIndex, Int32 convPolyIdx, Int32 convPolyVertIdx) const;
	Int32	 GetConvexPolygonPolyEdgeIndex	(ULong pgonIndex, Int32 convPolyIdx, Int32 convPolyVertIdx) const;
	ULong	 GetConvexPolygonCacheSize		(ULong pgonIndex) const;
	Vector3D GetConvexPolygonNormalVectorByVertex (ULong			pgonIndex,
												   UInt32			convPolyIdx,
												   UInt32			convPolyVertIdx,
												   const TRANMAT&	trafo = Geometry::IdentityTranMat) const;

	const PolygonConvexDecomposition& GetConstPolygonConvexDecomposition (ULong pgonIndex) const;

	// --- Edge handling -----------------------------------------------------------------------------------------------
public:
	bool	HasEdges (void) const;
	ULong	GetEdgeCount (void) const;

	const EDGE&				GetConstEdge	(ULong index) const;
	const EdgeAttributes&	GetConstEdgeAttributes (ULong index) const;
	const EdgeId&			GetEdgeId		(ULong index) const;


	// --- Vertex handling ---------------------------------------------------------------------------------------------
public:
	bool	HasVertices (void) const;
	ULong	GetVertexCount (void) const;

	const VERT&	GetConstVertex (ULong index) const;
	Coord3D GetVertexPoint (ULong index, const TRANMAT& trafo = Geometry::IdentityTranMat) const;
	void	GetVertexCoords (ULong index, const TRANMAT& trafo, double* x, double* y, double* z) const;

	CoordsPosition GetVerticesPosition (Int32 v1, Int32 v2) const;

	GS_FORCE_INLINE	const VertexId&		GetVertexId (ULong index) const;
	GS_FORCE_INLINE bool GetVertexHardFlag (ULong index) const;

	void	GetPolygonVertices (ULong pgonIdx, GS::Array<ULong>& pgonVertIdxsInBody, GS::Array<ULong>* nextContourStartIdxs = nullptr) const;
	void	GetPolygonVertices (ULong pgonIdx, GS::Array<VERT>& pgonVertsAsVERT, GS::Array<ULong>* nextContourStartIdxs = nullptr) const;
	void	GetPolygonVertices (ULong pgonIdx, GS::PagedArray<Coord3D>& pgonVertsAsCoord3D, GS::Array<ULong>* nextContourStartIdxs = nullptr) const;


	// --- Normalvector for curved surfaces handling -------------------------------------------------------------------
public:
	ULong			GetRoundNormVectorCount () const;
 private:
	// Instead this function use the PGON functionality: GetNormalVectorByVertex or MeshBody::GetNormalVectorByEdge
	const Vector3D*	GetConstRoundNormVectorPtr (ULong index) const;
	Vector3D		GetRoundNormVector (UInt32 vectorIdx, const TRANMAT& trafo) const;
public:

	void		ClearRoundNormVectorCache (void);

	// --- Texture Vertex handling -------------------------------------------------------------------------------------
public:
	bool		HasPolygonTextureParameters (void) const;
	ULong		GetPolygonTextureParameterCount (void) const;
	Wrapping	GetPolygonTextureWrapping (Int32 ipgon) const;
	bool		GetPolygonLocalCoordinateSystem (Int32 ipgon, COORD3* c0, COORD3* e1, COORD3* e2, COORD3* e3, WrapMethod* method) const;
	UV			GetPolygonTextureVertex (Int32 polygonIndex, Int32 vertexIndex) const;
	double		GetPolygonTextureParameter (ULong index) const;
	void		GetPolygonTextureParameters (ULong index, GS::Array<double>* result) const;	
	
	TextureCoordSys	GetPolygonTextureCoordinateSystem (UIndex index) const;
	GS::Array<UV>	GetPolygonTextureUVs (UIndex index) const;


public:
	ConstMeshBodyVertexIterator BeginVertices () const;
	ConstMeshBodyVertexIterator EndVertices () const;
	ConstMeshBodyEdgeIterator BeginEdges () const;
	ConstMeshBodyEdgeIterator EndEdges () const;
	ConstMeshBodyPolygonIterator BeginPolygons () const;
	ConstMeshBodyPolygonIterator EndPolygons () const;
	ConstMeshBodyPolyEdgeIterator BeginPolyEdges (const PGON& parentPoly) const;
	ConstMeshBodyPolyEdgeIterator EndPolyEdges (const PGON& parentPoly) const;

public:
	MD5::FingerPrint GetShuffleInvariantCheckSum () const;

private:
	GSErrCode	Read		(GS::IChannel& ic, GS::Array<UIndex>& unusedCoorVertices);
	void		ReadXML		(GS::XMLIChannel& inXML);

public:
	GSErrCode	Write (GS::OChannel& oc) const;

	enum WriteAsGDLOption {Default = 0, CurvedPolygons, AllCurved, SimpleModelOutput, ShadowBodiesToo, ShadowBodiesOnly};
	enum WriteAsGDLLayout {WriteAsUStr = 0, WriteAsCStr = 1};
	typedef GSErrCode (*WriteAsGDLTextureGetter)(void *userData, ULong ipgon, Int32 irtxt, GS::UniString *name, double *width, double *height, bool *hasAlpha);

	GSErrCode	WriteAsGDL (
		GS::ProcessControl&			processControl,
		GS::OChannel&				oc,
		WriteAsGDLLayout			layout,
		const WriteAsGDLOption&		option,
		WriteAsGDLTextureGetter		GetTextureInfo,
		IWriteAttributesToGDL&		writeAttributeToGDL,
		void *						userData
	) const;

private:
	void		ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	void		ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame, GS::Array<UIndex>& unusedCoorVertices);
	void		ReadVersion3 (GS::IChannel& ic, const GS::InputFrame& frame, GS::Array<UIndex>& unusedCoorVertices);
	void		ReadVersion4 (GS::IChannel& ic, const GS::InputFrame& frame);
	void		ReadVersion5 (GS::IChannel& ic, const GS::InputFrame& frame);
	void		ReadVersion6 (GS::IChannel& ic, const GS::InputFrame& frame);
	void		ReadVersion7 (GS::IChannel& ic, const GS::InputFrame& frame);

	void		WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	void		WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	void		WriteVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	void		WriteVersion4 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	void		WriteVersion5 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	void		WriteVersion6 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	void		WriteVersion7 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

public:
	void		DumpGDL (GS::OChannel& oc, bool minimalDump = false) const;
	void		DumpGDLToDBChannel () const;
	void		DumpMinimalGDLToDBChannel () const;
};


class ConstMeshBodyVertexIterator {
	private:
		const MeshBody& parentBody;
		Int32			vertIdx;

	public:
		ConstMeshBodyVertexIterator (const MeshBody& parentBodyIn, Int32 startIdx);
		ConstMeshBodyVertexIterator (const ConstMeshBodyVertexIterator&) = default;
		const ConstMeshBodyVertexIterator& operator= (const ConstMeshBodyVertexIterator&) = delete;

		const VERT& operator* () const;
		const VERT* operator-> () const;

		const VERT&	operator[] (GS::Offset offset) const;

		ConstMeshBodyVertexIterator& operator++ ();
		ConstMeshBodyVertexIterator operator++ (int);
		ConstMeshBodyVertexIterator& operator-- ();
		ConstMeshBodyVertexIterator operator-- (int);

		ConstMeshBodyVertexIterator	operator+  (GS::Offset offset) const;
		ConstMeshBodyVertexIterator	operator-  (GS::Offset offset) const;
		GS::Offset			operator-  (const ConstMeshBodyVertexIterator& rightOp) const;

		ConstMeshBodyVertexIterator&	operator+= (GS::Offset offset);
		ConstMeshBodyVertexIterator&	operator-= (GS::Offset offset);

		bool	operator== (const ConstMeshBodyVertexIterator& rightOp) const;
		bool	operator!= (const ConstMeshBodyVertexIterator& rightOp) const;

		bool	operator<  (const ConstMeshBodyVertexIterator& rightOp) const;
		bool	operator<= (const ConstMeshBodyVertexIterator& rightOp) const;
		bool	operator>  (const ConstMeshBodyVertexIterator& rightOp) const;
		bool	operator>= (const ConstMeshBodyVertexIterator& rightOp) const;

};


class ConstMeshBodyEdgeIterator {
	private:
		const MeshBody& parentBody;
		Int32			edgeIdx;

	public:
		ConstMeshBodyEdgeIterator (const MeshBody& parentBodyIn, Int32 startIdx);
		ConstMeshBodyEdgeIterator (const ConstMeshBodyEdgeIterator&) = default;
		const ConstMeshBodyEdgeIterator& operator= (const ConstMeshBodyEdgeIterator&) = delete;

		const EDGE& operator* () const;
		const EDGE* operator-> () const;

		const EDGE&	operator[] (GS::Offset offset) const;

		ConstMeshBodyEdgeIterator& operator++ ();
		ConstMeshBodyEdgeIterator operator++ (int);
		ConstMeshBodyEdgeIterator& operator-- ();
		ConstMeshBodyEdgeIterator operator-- (int);

		ConstMeshBodyEdgeIterator	operator+  (GS::Offset offset) const;
		ConstMeshBodyEdgeIterator	operator-  (GS::Offset offset) const;
		GS::Offset			operator-  (const ConstMeshBodyEdgeIterator& rightOp) const;

		ConstMeshBodyEdgeIterator&	operator+= (GS::Offset offset);
		ConstMeshBodyEdgeIterator&	operator-= (GS::Offset offset);

		bool	operator== (const ConstMeshBodyEdgeIterator& rightOp) const;
		bool	operator!= (const ConstMeshBodyEdgeIterator& rightOp) const;

		bool	operator<  (const ConstMeshBodyEdgeIterator& rightOp) const;
		bool	operator<= (const ConstMeshBodyEdgeIterator& rightOp) const;
		bool	operator>  (const ConstMeshBodyEdgeIterator& rightOp) const;
		bool	operator>= (const ConstMeshBodyEdgeIterator& rightOp) const;

};


class ConstMeshBodyPolygonIterator {
	private:
		const MeshBody& parentBody;
		Int32			polyIdx;

	public:
		ConstMeshBodyPolygonIterator (const MeshBody& parentBodyIn, Int32 startIdx);
		ConstMeshBodyPolygonIterator (const ConstMeshBodyPolygonIterator&) = default;
		const ConstMeshBodyPolygonIterator& operator= (const ConstMeshBodyPolygonIterator& src) = delete;

		const PGON& operator* () const;
		const PGON* operator-> () const;

		const PGON&	operator[] (GS::Offset offset) const;

		ConstMeshBodyPolygonIterator& operator++ ();
		ConstMeshBodyPolygonIterator operator++ (int);
		ConstMeshBodyPolygonIterator& operator-- ();
		ConstMeshBodyPolygonIterator operator-- (int);

		ConstMeshBodyPolygonIterator	operator+  (GS::Offset offset) const;
		ConstMeshBodyPolygonIterator	operator-  (GS::Offset offset) const;
		GS::Offset			operator-  (const ConstMeshBodyPolygonIterator& rightOp) const;

		ConstMeshBodyPolygonIterator&	operator+= (GS::Offset offset);
		ConstMeshBodyPolygonIterator&	operator-= (GS::Offset offset);

		bool	operator== (const ConstMeshBodyPolygonIterator& rightOp) const;
		bool	operator!= (const ConstMeshBodyPolygonIterator& rightOp) const;

		bool	operator<  (const ConstMeshBodyPolygonIterator& rightOp) const;
		bool	operator<= (const ConstMeshBodyPolygonIterator& rightOp) const;
		bool	operator>  (const ConstMeshBodyPolygonIterator& rightOp) const;
		bool	operator>= (const ConstMeshBodyPolygonIterator& rightOp) const;

};


class ConstMeshBodyPolyEdgeIterator {
	private:
		const MeshBody& parentBody;
		Int32			pedgIdx;

	public:
		ConstMeshBodyPolyEdgeIterator (const MeshBody& parentBodyIn, Int32 startIdx);
		ConstMeshBodyPolyEdgeIterator (const ConstMeshBodyPolyEdgeIterator&) = default;
		const ConstMeshBodyPolyEdgeIterator& operator= (const ConstMeshBodyPolyEdgeIterator&) = delete;

		Int32	operator* () const;

		Int32	operator[] (GS::Offset offset) const;

		ConstMeshBodyPolyEdgeIterator&	operator++ ();
		ConstMeshBodyPolyEdgeIterator	operator++ (int);
		ConstMeshBodyPolyEdgeIterator&	operator-- ();
		ConstMeshBodyPolyEdgeIterator	operator-- (int);

		ConstMeshBodyPolyEdgeIterator	operator+ (GS::Offset offset) const;
		ConstMeshBodyPolyEdgeIterator	operator- (GS::Offset offset) const;
		GS::Offset						operator- (const ConstMeshBodyPolyEdgeIterator& rightOp) const;

		ConstMeshBodyPolyEdgeIterator&	operator+= (GS::Offset offset);
		ConstMeshBodyPolyEdgeIterator&	operator-= (GS::Offset offset);

		bool	operator== (const ConstMeshBodyPolyEdgeIterator& rightOp) const;
		bool	operator!= (const ConstMeshBodyPolyEdgeIterator& rightOp) const;

		bool	operator<  (const ConstMeshBodyPolyEdgeIterator& rightOp) const;
		bool	operator<= (const ConstMeshBodyPolyEdgeIterator& rightOp) const;
		bool	operator>  (const ConstMeshBodyPolyEdgeIterator& rightOp) const;
		bool	operator>= (const ConstMeshBodyPolyEdgeIterator& rightOp) const;

};

}	// namespace Modeler


MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	DLModelPoint (const TRANMAT *tran, double *x, double *y, double *z);

MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	DLModelVector (const TRANMAT *tran, double *x, double *y, double *z);

#include "Model3D/MeshBodyImp.hpp"

#endif
