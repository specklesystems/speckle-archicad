// *****************************************************************************
//
//						Public Generator functions in GSModeler Module
// (The prototypes are defined in GDLEnvir.h)
//
// Contact person:	BA
//
// *****************************************************************************

#ifndef	_GSMODELER_GENERATORS_H_
#define	_GSMODELER_GENERATORS_H_

#include	"GSModelerExport.h"

// from GDL
#include	"GDLProc.h"

namespace Modeler {
	class IAttributeReader;
}

// =============================================================================
//
//							Generators for 2D Primitives
//
// =============================================================================

GSMODELER_DLL_EXPORT	Hotspot2Proc			BPHotspot2;
GSMODELER_DLL_EXPORT	Line2Proc				BPLine2;
GSMODELER_DLL_EXPORT	HotLine2Proc			BPHotLine2;
GSMODELER_DLL_EXPORT	Arc2Proc				BPArc2;
GSMODELER_DLL_EXPORT	HotArc2Proc				BPHotArc2;
GSMODELER_DLL_EXPORT	Circle2Proc				BPCircle2;
GSMODELER_DLL_EXPORT	Rect2Proc				BPRect2;
GSMODELER_DLL_EXPORT	Poly2Proc				BPPoly2;
GSMODELER_DLL_EXPORT	Spline2Proc				BPSpline2;
GSMODELER_DLL_EXPORT	Text2Proc				BPText2;
GSMODELER_DLL_EXPORT	RichText2Proc			BPRichText2;
GSMODELER_DLL_EXPORT	Picture2Proc			BPPicture2;
GSMODELER_DLL_EXPORT	Poly2Proc				BPPoly2NoFills;

// =============================================================================
//
//							Generators for Attributes
//
// =============================================================================


GSMODELER_DLL_EXPORT	MaterGenProc			BQMaterGen_MaterAdd_Onlycheck;
GSMODELER_DLL_EXPORT	DerivedMaterGenProc		BQDerivedMaterGen_MaterAdd_Onlycheck;
GSMODELER_DLL_EXPORT	FillGenProc				BQFillGen_FillAdd_Onlycheck;
GSMODELER_DLL_EXPORT	LtypeGenProc			BQLtypeGen_LineAdd_Onlycheck;

GSMODELER_DLL_EXPORT	MaterGenProc			BQMaterGen_MaterAdd_ToModeler;
GSMODELER_DLL_EXPORT	DerivedMaterGenProc		BQDerivedMaterGen_MaterAdd_ToModeler;
GSMODELER_DLL_EXPORT	FillGenProc				BQFillGen_FillAdd_ToModeler;
GSMODELER_DLL_EXPORT	LtypeGenProc			BQLtypeGen_LineAdd_ToModeler;


// =============================================================================
//
//							Generators for 3D Primitives
//
//							http://wiki/w/3D_konverzi%C3%B3
// =============================================================================

GSMODELER_DLL_EXPORT	CloseBodyProc			BOCloseBody;
GSMODELER_DLL_EXPORT	BodyProc				BOBody;
GSMODELER_DLL_EXPORT	NurbsBodyProc			NurbsBodyGen;

GSMODELER_DLL_EXPORT	SetShadowProc			BOSetShadow;

GSMODELER_DLL_EXPORT	VertProc				BOVert;
GSMODELER_DLL_EXPORT	TeveProc				BOTeve;
GSMODELER_DLL_EXPORT	VectProc				BOVector;
GSMODELER_DLL_EXPORT	EdgeProc				BOEdge;
GSMODELER_DLL_EXPORT	PgonProc				BOPgonGV;
GSMODELER_DLL_EXPORT	HotsProc				BOHotspot;

GSMODELER_DLL_EXPORT	NurbsVertProc			NurbsVertGen;
GSMODELER_DLL_EXPORT	NurbsEdgeProc			NurbsEdgeGen;
GSMODELER_DLL_EXPORT	NurbsTrimProc			NurbsTrimGen;
GSMODELER_DLL_EXPORT	NurbsTrimSingularProc	NurbsTrimSingularGen;
GSMODELER_DLL_EXPORT	NurbsFaceProc			NurbsFaceGen;
GSMODELER_DLL_EXPORT	NurbsLumpProc			NurbsLumpGen;

GSMODELER_DLL_EXPORT	SegmentProc				BOSegment;
GSMODELER_DLL_EXPORT	PPrismProc				BOGenPPrism;
GSMODELER_DLL_EXPORT	SPrismProc				BOGenSPrism;
GSMODELER_DLL_EXPORT	BPrismProc				BOGenBPrism;
GSMODELER_DLL_EXPORT	CWallProc				BOcWall;
GSMODELER_DLL_EXPORT	BeamProc				BOBeam;

GSMODELER_DLL_EXPORT	MassProc				BOGenMass;

GSMODELER_DLL_EXPORT	SetBaseProc				BOSetBase;
GSMODELER_DLL_EXPORT	RtxtProc				BORtxt;
GSMODELER_DLL_EXPORT	CoorProc				BOCoor;
GSMODELER_DLL_EXPORT	CoorVertexBasedProc		BOCoorVertexBased;

GSMODELER_DLL_EXPORT	PointCloudProc			BOPointCloud;

GSMODELER_DLL_EXPORT	LineProc				BOLine;
GSMODELER_DLL_EXPORT	TriProc					BOTri;
GSMODELER_DLL_EXPORT	PgonProc				BOPgonSV;

GSMODELER_DLL_EXPORT	ArcProc					BOArc;
GSMODELER_DLL_EXPORT	CircleProc				BOCircle;
GSMODELER_DLL_EXPORT	RectProc				BORect;

GSMODELER_DLL_EXPORT	BrickProc				BOBrick;
GSMODELER_DLL_EXPORT	CylindProc				BOCylind;
GSMODELER_DLL_EXPORT	GenCylProc				BOGenCyl;
GSMODELER_DLL_EXPORT	SphereProc				BOSphere;
GSMODELER_DLL_EXPORT	EllipsProc				BOEllips;
GSMODELER_DLL_EXPORT	ConeProc				BOCone;
GSMODELER_DLL_EXPORT	ElbowProc				BOElbow;
GSMODELER_DLL_EXPORT	NurbsCurve2DProc		NurbsCurve2DGen;
GSMODELER_DLL_EXPORT	NurbsCurve3DProc		NurbsCurve3DGen;
GSMODELER_DLL_EXPORT	NurbsSurfaceProc		NurbsSurfaceGen;

GSMODELER_DLL_EXPORT	FPrismProc				BOGenFPrism;
GSMODELER_DLL_EXPORT	PyramidProc				BOPyramid;
GSMODELER_DLL_EXPORT	RevolveProc				BORevolve;
GSMODELER_DLL_EXPORT	SweepProc				BOSweep;
GSMODELER_DLL_EXPORT	TubeProc				BOTube;
GSMODELER_DLL_EXPORT	PlanarPathTubeProc		BOPlanarPathTube;
GSMODELER_DLL_EXPORT	RuledProc				BORuled;
GSMODELER_DLL_EXPORT	RuledSegmentedProc		BORuledSegmented;
GSMODELER_DLL_EXPORT	GDLMeshProc				BOGDLMesh;
GSMODELER_DLL_EXPORT	CoonsProc				BOCoons;
GSMODELER_DLL_EXPORT	Text3Proc				BTText3;
GSMODELER_DLL_EXPORT	RichText3Proc			BTRichText3;

GSMODELER_DLL_EXPORT	LightProc				BOLight;
GSMODELER_DLL_EXPORT	GDLPictProc				BOPicture;

GSMODELER_DLL_EXPORT	WallProc				BOWall;

GSMODELER_DLL_EXPORT	PolyRoofProc			BOPolyRoof;
GSMODELER_DLL_EXPORT	ExtrudedShellProc		BOExtrudedShell;
GSMODELER_DLL_EXPORT	RevolvedShellProc		BORevolvedShell;
GSMODELER_DLL_EXPORT	RuledShellProc			BORuledShell;

GSMODELER_DLL_EXPORT	GDLBeginGroupProc		CDBeginGroup;
GSMODELER_DLL_EXPORT	GDLEndGroupProc			CDEndGroup;
GSMODELER_DLL_EXPORT	GDLClearGroupProc		CDClearGroup;
GSMODELER_DLL_EXPORT	GDLClearGroupsByMainGroupIdProc CDClearGroupsByMainGroupId;
GSMODELER_DLL_EXPORT	GDLOperationGroupsProc	CDOperationGroups;
GSMODELER_DLL_EXPORT	GDLPlaceGroupProc		CDPlaceGroup;
GSMODELER_DLL_EXPORT	GDLSweepGroupProc		CDSweepGroup;
GSMODELER_DLL_EXPORT	GDLCreateGroupWithMaterialProc		CDCreateGroupWithMaterial;

GSMODELER_DLL_EXPORT	BinaryProc				B3Binary;

GSMODELER_DLL_EXPORT	SetModelProc				BOSetCandElemSolidState;
GSMODELER_DLL_EXPORT	ForceBodyInfoClosingProc	BOForceBodyClosing;

GSMODELER_DLL_EXPORT	PlaceCutplaneProc			BOPlaceCutplane;
GSMODELER_DLL_EXPORT	RemoveLastCutplaneProc		BORemoveLastCutplane;
GSMODELER_DLL_EXPORT	RemoveAllCutplanesProc		BORemoveAllCutplanes;

GSMODELER_DLL_EXPORT	PushBodyInfoStateProc		BOPushCandElemState;
GSMODELER_DLL_EXPORT	PopBodyInfoStateProc		BOPopCandElemState;

GSMODELER_DLL_EXPORT	CutPolyProc					BOCutPoly;

GSMODELER_DLL_EXPORT	GSErr	CPCheckInput (	double pa, double pb, double pc, double pd,
												Int32 nc, const GS::Array<Coord3D>& corners, COORD3 *dir,
												short *ccerr);

#endif
