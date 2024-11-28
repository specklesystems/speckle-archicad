/*==========================================================================**
**								GDLProc.h									**
**																			**
**						GDL Callback function prototypes					**
**==========================================================================*/


#ifndef	_GDLProc_H_
#define _GDLProc_H_

#include	"GDLExport.h"

#include	"Array.hpp"
#include	"Pair.hpp"

#include	"UniCHar.hpp"
#include	"UniString.hpp"
#include	"PagedArray.hpp"		// GS::PagedArray
#include	"enProc.h"
#include	"comProc.h"
#include	"Point2D.hpp"
#include	"Vector3D.hpp"
#include	"TRANMAT.h"				// TRANMAT
#include	"TM.h"
#include	"SegmentationRule.hpp"
#include	"GSUtilsDefs.h"			// STATL
#include	"GDLExport.h"
#include	"GDLDefs.h"				// GdlErrDisplayData
#include	"ISymbol2D.hpp"
#include	"GDLParamTypes.hpp"
#include	"FileOperations.hpp"
#include	"ADBAttributeIndex.hpp"
#include	"Variant.hpp"
#include	"Result.hpp"

/*==========================================================================**
**								COMMON DATA TYPES 							**
**==========================================================================*/

#ifndef _model_I_H_

#include "VA.hpp"

#endif		/* _model_I_H_ */

class GdlDebugMemento;
struct GdlGenProcs;
class GSUserData;
class Wrapping;
class WordAnchor;
class IValueListComponent;

namespace Geometry {
	class GridMesh;
	class Surface3D;
}
namespace GS {
	class UnID;
	class ProcessControl;
	template<class T> class VAArray;
}

namespace GDL
{
	class IFileRef;
	class IFileServices;
}

namespace ADB {
	class IAttributeSetProvider;
}

enum InterpretationMode {
	FromMasterGdl = 1,
	FromObject
} ;

enum	MaterialEffect {
	VertexMaterial,
	EdgeMaterial
};

#define	GWRONGVERTIND		2001
#define	GWRONGEDGEIND		2002
#define	GWRONGVECTIND		2003

#define GWRONGNURBSGENCALL		2004

typedef	double	GDL_CALL	TextLenProc (GSUserData* userDataPtr, Int32 styleind, const GS::UniString& str);

typedef	double	GDL_CALL	GetNorthOfPlaceProc (GSUserData* userDataPtr);

typedef void	GDL_CALL	NumFormReqProc (short dimKind, short *norm, short *roundInch, short *lenDecimals,
											 bool *show0Whole, char *show0Inch, char *showSmall5, bool *hide0Dec);

typedef	void	GDL_CALL	StyleInfoProc (const GS::UniString& fontname, short familytype, double face, double slant, double size,
										   double *height, double *descent, double *leading);


struct GDL_DLL_EXPORT  GlimaIdx
{
	GS::Variant<ADB::AttributeIndex, Int32> index;


	GlimaIdx ();
	GlimaIdx (Int32 idx);
	GlimaIdx (const ADB::AttributeIndex& idx);

	bool operator==(const GlimaIdx& otherGlima) const;
	bool operator!=(const GlimaIdx& otherGlima) const;

	Int32		ToInt32 () const;
};


GDL_DLL_EXPORT
GlimaIdx	CreateGlimaIdx (Int32 idx);


// A modositasokat ezekben a tablazatokban is le kell kovetni.
// Uj request felvetelekor el kell donteni, hogy parameter szkriptbol kell-e mukodnie (alapesetben nem).
// http://wiki/w/GDL_Request
// http://wiki/w/GDL_Application_Query

class	GDL_DLL_EXPORT	IGDLRequests {
public:
	enum RequestValueMode
	{
		DefaultValues,
		NormalValues
	};

	enum class NumValDescriptionMode 
	{
		NoDescription,
		WithDescription
	};

	virtual				~IGDLRequests (void);

	virtual bool		NeedToStoreData (Int32 requestNumber) = 0;

	virtual	Int32		SizeReq (void) = 0;

	virtual	float		AttrReq (Int32 func, GS::UniString& str) = 0;

	virtual	void		PrograminfoReq (GS::UniString* name, UInt32* version, UInt32* keySerialNum, bool* isCommercial) = 0;

	virtual	void		DimformReq (	short dimKind, short *norm, short *roundInch, short *lenDecimals,
										bool *show0Whole, char *show0Inch, char *showSmall5, bool *hide0Dec) = 0;

	virtual	void		CatnamecodeReq (GS::UniString& name, GS::UniString& code) = 0;

	virtual	void		PlantitleReq (Int32 nrvals, GDLRequestResult& planTitleStrings) = 0;

	virtual	void		HomestoryReq (	short *index, GS::UniString& storyname,
										bool home_story_of_opening) = 0;

	virtual	void		StoryReq (short *index, GS::UniString& storyname) = 0;

	virtual	bool		CleanintersReq (void) = 0;

	virtual	GSErr		ZonedataReq (	GS::UniString& catname, GS::UniString& catcode,
										GS::UniString& number, GS::UniString& name,
										GS::UniString& catname2, GS::UniString& catcode2,
										GS::UniString& number2, GS::UniString& name2,
										bool fromOwner) = 0;

	virtual	GSErr		CustomautolabelReq (GS::UniString& name) = 0;

	virtual	GSErr		ZonecolusareaReq (double *area) = 0;

	virtual	short		WidoshowdimReq (void) = 0;

	virtual	short		WindowshowdimReq (void) = 0;

	virtual	short		DoorshowdimReq (void) = 0;

	virtual	void		NameOfListedReq (const GDL::ParameterGetter& globHdl, GS::UniString& name) = 0;

	virtual	GSErr		WidozonerelevReq (bool fromOwner, short* value) = 0;

	virtual	void		CalcformReq (	short dimKind, short *norm, short *roundInch, short *lenDecimals,
										bool *show0Whole, char *show0Inch, char *showSmall5, bool *hide0Dec) = 0;

	virtual	GSErr		MatchpropReq (	bool ownProp,
										Int32 nrvals, Int32 *retValue,
										GDLRequestResult& values) = 0;

	virtual	GSErr		AssoclpparvalueReq (	const char* parName, Int32 parIndex,
												char *name, Int32 *index,
												short *type, bool *isArray, unsigned char *flags, Int32 *dim1, Int32 *dim2,
												GdlValueRecord *numVal, GS::UniString& strVal,
												GDLRequestResult& arrayValues, NumValDescriptionMode numValDescriptions) = 0;

	virtual	GSErr		AssocelpropReq (	const GDL::ParameterGetter& globHdl,
											Int32 nrData, const char *order, Int32 nrVals, Int32 *retValue,
											GDLRequestResult& values) = 0;

	virtual	void		RefleveldataReq (Int32 nrvals, GDLRequestResult& values) = 0;

	virtual	void		AssoclpnameReq (GS::UniString& name) = 0;

	virtual	void		StoryinfoReq (	Int32 nrvals, bool allStories, Int32 index,
										Int32 *retValue, GDLRequestResult& values) = 0;

	virtual	void		AncestryinfoReq (	bool getReplacedInfo, Int32 nrvals,
											Int32 *retValue, GDLRequestResult& ancestryInfoResult) = 0;

	virtual	void		Styleinfo (	const GS::UniString& fontname, short familytype, double face, double slant, double size,
									double *height, double *descent, double *leading)	 = 0;

	virtual	Int32		ConstrfilldisplayReq (void) = 0;

	virtual	void		WorkingformReq (	short dimKind, short *norm, short *roundInch, short *lenDecimals,
											bool *show0Whole, char *show0Inch, char *showSmall5, bool *hide0Dec) = 0;

	virtual	void		TextsizeunitReq (	short workspaceKind,
											GS::UniString& unit) = 0;

	virtual	GSErr		MaterialinfoReq (	const GS::Variant< ADB::AttributeIndex, Int32>& materIndex,
											Int32 nData, double **data, GDL::Parameters* extraParameters,
											const char *reqStr, Int32 *retValue,
											GDLRequestResult& values,
											RequestValueMode requestValueMode) = 0;

	virtual	GSErr		TextblockinfoReq (	const GdlTextBlockData*					textBlockData,
											const GS::VAArray<GdlParagraphData>*	paragraphs,
											const GSHandle							tabsHdl,		// double
											const GS::VAArray<GdlStringData>*		stringsData,
											const GSHandle							stringsHdl,		// Layout
											double*									width,
											double*									height) = 0;

	virtual	void		FontnameslistReq (Int32 nrvals, GDLRequestResult& values) = 0;

	virtual	void		HomeDBinfoReq (	Int32			*parentDBIntId,
										GS::UniString&	parenDBUserId,
										GS::UniString&	parenDBName,
										short			*homeContext) = 0;

	virtual	Int32		FloorplanoptionReq (void) = 0;

	virtual	double		ViewAngleReq (void) = 0;

	virtual	void		ElemInfoReq (GS::UniString& name) = 0;

	virtual void		FullInfoReq (GDLRequestResult& idStrings) = 0;

	virtual GSErr		SumWithRoundingReq (const Int32 formatReqNr, const GS::Array<double>& numVals, double& result) = 0;

	virtual	GSErr		ApplicationQuery (	const GS::UniString&		identifierStr,
											const GS::UniString&		parameterStr,
											Int32						nrvals,
											bool*						storeData,
											Int32*						retValue,
											GDLRequestResult&			values,
											RequestValueMode			requestValueMode) = 0;

	virtual GSErr		PropertiesOfParent (Int32 reqIndex,
											Int32* retValue,
											GDLRequestResult& values) = 0;

	virtual GSErr		PropertyValueOfParent (	const GS::UniString& propertyId,
												Int32* retValue,
												GDLRequestResult& values) = 0;

	virtual GSErr		PropertyValuesOfParent (const GDL::Dictionary&		dictValue,
												Int32*						retValue,
												GDLRequestResult&			values) = 0;

	virtual GSErr		PropertyName		   (const GS::UniString& propertyId,
												Int32* retValue,
												GS::UniString& propertyType,
												GS::UniString& propertyGroupName,
												GS::UniString& propertyName) = 0;

	virtual	bool		AppQueryEnabledFromParameterScript (const GS::UniString& identifierStr) = 0;

	virtual	GSErr		LibraryGlobal	(	const GS::UnID&				unID,
											const GS::UniString&		identifierStr,
											const GS::UniString&		parameterStr,
											Int32*						retValue,
											GDLRequestResult&			values) = 0;

	virtual	GSErr		BuildMatInfo (	const GS::UniString*			buildMatName,
									    const ADB::AttributeIndex&		buildMatIndex,
								 		const char*						reqStr,
										Int32*							retValue,
										GDLRequestResult&				values,
										RequestValueMode				requestValueMode) = 0;

	virtual	GSErr		ComponentVolume (UInt32 componentIndex, double& volume) = 0;

	virtual	GSErr		ComponentProjectedArea (UInt32 componentIndex, double& projectedArea) = 0;

	virtual GSErr		AutoTextList (Int32* retValue,
									  GDLRequestResult& values) = 0;

	virtual	void		ConfigurationNumber (GS::UniString& configurationNumber) = 0;

	virtual GSErr		ProfileComponents (const GS::UniString* profileName, const ADB::AttributeIndex& profileIndex, GDLRequestResult& componentTypeCodeValues) = 0;
	virtual GSErr		ProfileBoundingBox (const GS::UniString* profileName, const ADB::AttributeIndex& profileIndex, double width, double height, double* xmin, double* ymin, double* xmax, double* ymax) = 0;
	virtual GSErr		ProfileGeometry (const GS::UniString* profileName, const ADB::AttributeIndex& profileIndex, double width, double height, GDLRequestResult& rawGeometryValues) = 0;
	virtual GSErr		ProfileComponentInfo (const GS::UniString*			profileName,
											  const ADB::AttributeIndex&	profileIndex,
											  Int32							componentIndex,
											  Int32							parameterIndex,
											  Int32*						retValue,
											  GDLRequestResult&				values,
											  RequestValueMode				requestValueMode) = 0;
											  
	virtual GSErr		ComponentIdsOfParent (const GDL::Dictionary& dictValue, Int32* retValue, GDLRequestResult& result) = 0;
	virtual GSErr		ComponentPropertyValuesOfParent (const GDL::Dictionary& dictValue, Int32* retValue, GDLRequestResult& result) = 0;
	virtual GSErr		ComponentPropertiesOfParent (Int32 reqIndex, Int32* retValue, GDLRequestResult& result) = 0;
	virtual GSErr		PropertyTreeOfParent (const GDL::Dictionary& dictValue, Int32* retValue, GDLRequestResult& result) = 0;
	virtual GSErr		ComponentPropertyTreeOfParent (const GDL::Dictionary& dictValue, Int32* retValue, GDLRequestResult& result) = 0;

	virtual	GSErr		MEPSystemAttributesReq (const ADB::AttributeIndex& index,
															 ADB::AttributeIndex* symbolFillType,
															 Int32* symbolFillPen,
															 Int32* symbolFillBGPen,
															 ADB::AttributeIndex* centerLineLineType,
															 Int32* centerLinePen,
															 Int32* penContour,
															 ADB::AttributeIndex* insulationSurface,
															 ADB::AttributeIndex* surface) = 0;

	virtual	void		PseudonymGSIDInfo (Int32 nrvals, Int32* retValue, GDLRequestResult& values) = 0;
};

/****************************************************************************/
/****************************************************************************/
/*																			*/
/*					ATTRIBUTUM HANDLING FUNCTION PROTOTYPES					*/
/*																			*/
/****************************************************************************/
/****************************************************************************/
struct GDLAttributeComponent {
	void*	data;
};

struct GDL3DComponent {
	void*	data;
};


namespace GDLGen {

class PropertyList;

enum PrismGenerationFlags {
	KeepAllPrismLines				= 0x00000000,
	EliminatePrismTopLines			= 0x00000001,
	EliminatePrismBottomLines		= 0x00000002,
	EliminatePrismSideLines			= 0x00000004,
	EliminateAllPrismLines			= EliminatePrismTopLines | EliminatePrismBottomLines | EliminatePrismSideLines,
	CurvedSegmentationNodes			= 0x00000008,
	PrismGenerationUsedBits			=	KeepAllPrismLines |
										EliminatePrismTopLines |
										EliminatePrismBottomLines |
										EliminatePrismSideLines |
										EliminateAllPrismLines |
										CurvedSegmentationNodes
};

enum PolyRoofGenerationFlags {
	KeepAllPolyRoofLines		= 0x00000000,
	EliminateAllPolyRoofLines	= 0x00000001,
	InvisibleAllPolyRoofLines	= 0x00000002,
	PolyRoofGenerationUsedBits	= KeepAllPolyRoofLines | EliminateAllPolyRoofLines | InvisibleAllPolyRoofLines
};

// Status flags for sweepgroup operation
enum SweepGroupOperationStatusFlags {
	SweepGroupOpNoStatus			= 0x00000000,
	SweepGroupOpNewEdgesInvisible	= 0x00000001,	// currently unused, analogous to GroupOpNewEdgesInvisible
	SweepGroupOpKeepTexture			= 0x00000002,	// keep per polygon texture parameters on result body the same as the source body

	SweepGroupStatusUsedBits		= SweepGroupOpNoStatus | SweepGroupOpKeepTexture
};

// Status flags for group operations ([add|sub|isect]group)
enum OperationGroupStatusFlags {
	GroupOpNoStatus					= 0x00000000,
	GroupOpNewEdgesInvisible		= 0x00000001,
	GroupOpInheritTextureFromTool	= 0x00000002,	// For polygons without specific texture wrapping or UVs,
													// inherit texture parameters from the tool body.
	GroupOpStatusUsedBits			= GroupOpNoStatus | GroupOpInheritTextureFromTool | GroupOpNewEdgesInvisible
};

// A clone of this type can be found in the following file:
// GSModeler/GSModelerDLL/Generator/RoofConstruct/RoofConstruct.hpp
// Do not modify it without updating that one as well!
enum RoofEdgeTrim {
	VerticalTrim,
	PerpendicularTrim,
	HorizontalTrim,
	CustomAngleToRoof,
	CustomAngleToHPlane,
	RETLastItem // Do not add new elements after this item!!! Add them before it.
};
enum RoofEdgeType { REUndefined, RERidge, REValley, REHip, REEaves, RERTDome, RERTHollow, RERTCoplanar };
// A clone of this type can be found in the following file:
// GSModeler/GSModelerDLL/Generator/RoofConstruct/RoofConstruct.hpp
// Do not modify it without updating that one as well!
enum RoofContourApplication {
	ApplyOnAll,
	DoNotApplyOnGables,
	RCALastItem // Do not add new elements after this item!!! Add them before it.
};

}


typedef	GS::Optional<GS::Variant<ADB::AttributeIndex, Int32>>  GDL_CALL	MaterGenProc (GDLAttributeComponent component, GSUserData* userDataPtr, const GS::UniString& name,
																			  short method, Int32 npar, const double *const* pars,
																			  const GS::UniString* textureName, Int32 tnpar, const double *const* tpars,
																			  const GDL::ParameterGetter& addExternalData,
																			  bool permanentAttribute, bool forceCheckingMode);
typedef	GS::Optional<GS::Variant<ADB::AttributeIndex, Int32>>  GDL_CALL	DerivedMaterGenProc (GDLAttributeComponent component, GSUserData* userDataPtr, const GS::UniString& name,
																					 const GS::UniString& basedOnName, const GDL::ParameterGetter& redefParData,
																					 const GS::UniString* textureName, Int32 tnpar, const double *const* tpars,
																					 const GDL::ParameterGetter& addExternalData,
																					 bool permanentAttribute, bool forceCheckingMode);

typedef	GS::Optional<GS::Variant<ADB::AttributeIndex, Int32>> GDL_CALL	FillGenProc (GDLAttributeComponent component, GSUserData* userDataPtr,
																		 const GS::UniString& name, short method,
																		 const GS::UniString& imageName,
																		 Int32 npar, const double *const* pars,
																		 ISymbol2D::ConstRef symbol2D, const GDL::ParameterGetter& addExternalData,
																		 bool permanentAttribute, bool forceCheckingMode);

typedef	GS::Result<ADB::AttributeIndex, GSErrCode> GDL_CALL	LtypeGenProc (GDLAttributeComponent component, GSUserData* userDataPtr, const GS::UniString& name,
																		  short method, Int32 npar, const double *const* pars,
																		  ISymbol2D::ConstRef symbol2D, const GDL::ParameterGetter& addExternalData,
																		  bool permanentAttribute, bool forceCheckingMode);


typedef short	GDL_CALL	StyleDefCheckProc (GSUserData* userDataPtr, Int32 version, Int32 npar, const double *const* pars, short familytype, const GS::UniString& fontname);
typedef Int32	GDL_CALL	StyleGenProc (GSUserData* userDataPtr, short familytype, const GS::UniString& fontname, unsigned char face, const WordAnchor& anchor, short just, double slant, double size);

typedef GSErr	GDL_CALL	SymbHdlGenProc (GDLAttributeComponent component, GSUserData* userDataPtr, GDL::IFileRef* fileRef, GDL::ParameterAccessor& globHdl, const GDL::ParameterGetter& addParHdl, ISymbol2D::ConstRef& symbol2D);

struct GDLAttributeGenerators {
	MaterGenProc		*materGen;
	DerivedMaterGenProc *derivedMaterGen;
	FillGenProc			*fillGen;
	LtypeGenProc		*ltypeGen;
	StyleDefCheckProc	*styleDefCheck;
	StyleGenProc		*styleGen;
	SymbHdlGenProc		*symbolHdl;

	GDLAttributeComponent	component;
};

class	GDL_DLL_EXPORT	IGDLGlobalAttrQueries {
public:
	virtual		~IGDLGlobalAttrQueries (void); 

	virtual	ADB::AttributeIndex	MaterInd (const GS::UniString& name) = 0;
	virtual	GSErr				MaterName (const ADB::AttributeIndex& index, GS::UniString& name) = 0;
	virtual	ADB::AttributeIndex	FillInd (const GS::UniString& name) = 0;
	virtual	GSErr				FillName (const ADB::AttributeIndex& index, GS::UniString& name) = 0;
	virtual	GSErr				FillClass (const ADB::AttributeIndex& index, short& iClass) = 0;
	virtual	ADB::AttributeIndex	LtypeInd (const GS::UniString& name) = 0;
	virtual	GSErr				LtypeName (const ADB::AttributeIndex& index, GS::UniString& name) = 0;
	virtual	ADB::AttributeIndex	BuildingMaterialInd (const GS::UniString& name) = 0;
	virtual	GSErr				BuildingMaterialName (const ADB::AttributeIndex& index, GS::UniString& name) = 0;
	virtual GSErr				BuildingMaterialAttributes (const ADB::AttributeIndex& index, ADB::AttributeIndex& cutMaterial, ADB::AttributeIndex& cutFill, PenType& cutFillPen, PenType& cutFillBGPen) = 0;
	virtual	ADB::AttributeIndex	ProfileInd (const GS::UniString& name) = 0;
	virtual	GSErr				ProfileName (const ADB::AttributeIndex& index, GS::UniString& name) = 0;
};


struct ShellSidesMaterial {
	enum Size {ArraySize = 4};
	typedef GlimaIdx Array [ArraySize];
};

struct ADBShellSidesMaterial {
	enum Size { ArraySize = 4 };
	typedef ADB::AttributeIndex Array[ArraySize];
};

typedef enum {
	SEM_NotExplode	= 0,
	SEM_Explode		= 1
} ShellExplosionMode;

typedef enum {				// Describes which part of a shell should be generated
	SGM_genNormal			= 0,
	SGM_genCutBody			= 1
} ShellGenerationMode;

typedef enum {				// Meaning of segmentation for BORevolve
	Tangential	= 1,		// segmentation number is ignored and a fix value is used instead, Segmentation is done via tangential segments
	ByCircle,				// segmentation number refers to whole circle
	ByArc					// segmentation number refers to arc
} RevolveCurvedSegType;

typedef enum {
	RevProfSmooth = 1,		//revolved copies of profile will be smooth
	RevProfSharp			//revolved copies of profile will be sharp
} RevolveProfileCopiesSmoothness;

enum class RuledTextureMode {
	UVPerPolygon = 0,
	CubicFromBody = 1,
	ValidStatuses = CubicFromBody
};

/****************************************************************************/
/****************************************************************************/
/*																			*/
/*							BODY GENERATOR FUNCTIONS						*/
/*																			*/
/****************************************************************************/
/****************************************************************************/
typedef	GSErr	GDL_CALL	CloseBodyProc (GDL3DComponent component,
										   bool forceBodyInfoClosing, bool setUnknownType, bool saveCandElem);
typedef	GSErr	GDL_CALL	BodyProc (GDL3DComponent component, Int32 statusIn, bool forceBodyInfoClosing);
typedef	GSErr	GDL_CALL	NurbsBodyProc (GDL3DComponent				component, 
										   GDL_NurbsBodyStatus			bodyStatus,
										   double						smoothnessMin, 
										   double						smoothnessMax, 
										   bool							forceBodyInfoClosing);

typedef	GSErr	GDL_CALL	SetModelProc (GDL3DComponent component, GSUserData* userDataPtr, short gMode);
typedef GSErr	GDL_CALL	SetShadowProc (GDL3DComponent component, STATL shadowStatus);
typedef GSErr	GDL_CALL	SetBodyAttributesProc (GDL3DComponent component, GSUserData* userDataPtr, const ADB::AttributeIndex& bMat,
												   const ADB::AttributeIndex& ifill, PenType sbkgc, PenType sconc, PenType sfilc, const ADB::AttributeIndex& sltype);

typedef GSErr	GDL_CALL	GDLBeginGroupProc (GDL3DComponent component,
											   const GS::Guid& mainGroupId, GS::Guid* actGroupId);
typedef GSErr	GDL_CALL	GDLEndGroupProc (GDL3DComponent component);
typedef GSErr	GDL_CALL	GDLClearGroupProc (GDL3DComponent component, GSUserData* userDataPtr, const GS::Guid& actGroupId);	//vc7.1
typedef GSErr	GDL_CALL	GDLClearGroupsByMainGroupIdProc (GDL3DComponent component, const GS::Guid& mainGroupId);	//vc7.1

typedef GSErr	GDL_CALL	GDLOperationGroupsProc (GDL3DComponent		component,
													GSUserData*			userDataPtr,
													Int32				operation,
													STATW				operationStatus,	// see @OperationGroupStatusFlags
													const GS::Guid&		groupId1,
													const GS::Guid&		groupId2,
													const GS::Guid&		mainGroupId,
													GS::Guid*			resGroupId,
													short				cutLineColor,
													const GlimaIdx&		cutSurfaceGlima,
													short				cutSurfaceGlimaColor);
typedef GSErr	GDL_CALL	GDLPlaceGroupProc (GDL3DComponent	component,
											   const GS::Guid&	groupId,
											   const TRANMAT	&tran);
typedef GSErr	GDL_CALL	GDLSweepGroupProc (GDL3DComponent	component,
											   GSUserData*		userDataPtr,
											   const GS::Guid&	groupId,
											   const GS::Guid&	mainGroupId,
											   GS::Guid*		resGroupId,
											   COORD3*			c,
											   short			newLineColor,
											   const GlimaIdx&	newSurfaceGlima,
											   short			newSurfaceGlimaColor,
											   const TRANMAT&	tran,
											   Int32			sweepAlgorithm,
											   STATW			operationStatus);		// see @OperationGroupStatusFlags
typedef GSErr	GDL_CALL	GDLCreateGroupWithMaterialProc (GDL3DComponent		component,
															GSUserData*			userDataPtr,
															const GS::Guid&		groupId,
															const GS::Guid&		mainGroupId,
															GS::Guid*			resGroupId,
															short				mask,
															PenType				pen,
															const GlimaIdx&		glima);
typedef	GSErr	GDL_CALL	SegmentProc (GDL3DComponent component,
										 PenType	pen,
										 const ADB::AttributeIndex& ltype,
										 double		x1, double y1, double z1,
										 double		x2, double y2, double z2,
										 const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	HotLineProc (GDL3DComponent component,
										 GSUserData* userDataPtr,
										 PenType	pen,
										 double		x1, double y1, double z1,
										 double		x2, double y2, double z2, UInt32 unID,
										 const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	ArcProc (GDL3DComponent component,
									PenType		pen, const GlimaIdx& glima,
									const ADB::AttributeIndex& ltype,
									const ADB::AttributeIndex& fillind,
									double		x0, double y0,
									double		r,
									double		alpha, double beta,
									Int32		ncs,
									const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	HotArcProc (GDL3DComponent component,
									GSUserData* userDataPtr,
									PenType		pen,
									double		x0, double y0,
									double		r,
									double		alpha, double beta, UInt32 unID,
									Int32		ncs,
									const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	CircleProc (GDL3DComponent component,
										PenType				pen,
										const GlimaIdx&		glima,
										const ADB::AttributeIndex& ltype,
										const ADB::AttributeIndex& fillind,
										double				r,
										Int32				ncs,
										const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	RectProc (GDL3DComponent component,
										PenType			pen,
										const GlimaIdx& glima,
										const ADB::AttributeIndex& ltype,
										double			a, double b,
										bool			undlin,
										double		e1, double e2,
										const TRANMAT		&tran);

typedef	void	GDL_CALL	ForceBodyInfoClosingProc (GDL3DComponent 	component,
													  bool				force);

typedef	GSErr	GDL_CALL	PlaceCutplaneProc (GDL3DComponent	component,
												  double pa, double pb, double pc, double pd, double dd,
												  short status, PenType pen, const GlimaIdx& glima, Int32 cutPolygonId,
												  Wrapping wrap,
												  const Coord3D& origin, const Vector3D& xaxis,
												  const Vector3D& yaxis, const Vector3D& zaxis,
												  const TRANMAT& tran);

typedef	GSErr	GDL_CALL	RemoveLastCutplaneProc (GDL3DComponent	component);
typedef	void	GDL_CALL	RemoveAllCutplanesProc (GDL3DComponent	component);

typedef	GSErr	GDL_CALL	PushBodyInfoStateProc (GDL3DComponent	component,
											   GSUserData*			userDataPtr);
typedef	void	GDL_CALL	PopBodyInfoStateProc (GDL3DComponent	component);


/****************************************************************************/
/****************************************************************************/
/*																			*/
/*					GENERAL THREE DIMENSIONAL ELEMENTS						*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

typedef	GSErr	GDL_CALL	BrickProc (
									GDL3DComponent component,
									PenType		pen, const GlimaIdx& glima,
									double		a, double b, double c,
									const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	CylindProc (
									GDL3DComponent component,
									PenType		pen, const GlimaIdx& glima,
									double		h, double r,
									Int32		ncs,
									const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	GenCylProc (
									GDL3DComponent component,
									PenType		pen, const GlimaIdx& glima,
									double		h,
									double		r1, double r2,
									double		phi1, double phi2,
									double		theta,
									short		btype,
									Int32		ncs,
									const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	SphereProc (
									GDL3DComponent component,
									PenType		pen, const GlimaIdx& glima,
									double		r,
									Int32		ncs,
									const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	EllipsProc (
									GDL3DComponent component,
									PenType		pen, const GlimaIdx& glima,
									double		h,
									double		r,
									Int32		ncs,
									const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	ConeProc (
									GDL3DComponent component,
									PenType		pen, const GlimaIdx& glima,
									double		h,
									double		r,
									Int32		ncs,
									const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	ElbowProc (
									GDL3DComponent component,
									PenType		pen, const GlimaIdx& glima,
									double		r1,
									double		alpha,
									double		r2,
									Int32		ncs1, Int32 ncs2,
									const TRANMAT		&tran);

typedef	GSErr	GDL_CALL	NurbsCurve2DProc (
									GDL3DComponent				component,
									const GS::Array<double>&	knots,
									const GS::Array<Coord>&		cPoints,
									const GS::Array<double>&	weights);

typedef	GSErr	GDL_CALL	NurbsCurve3DProc (
									GDL3DComponent				component,
									const GS::Array <double>&	knots,
									const GS::Array <Coord3D>&	cPoints,
									const GS::Array <double>&	weights,
									const TRANMAT				&tran);
typedef	GSErr	GDL_CALL	NurbsSurfaceProc (
									GDL3DComponent						component,
									const GS::Array <double>&			knotsU,
									const GS::Array <double>&			knotsV,
									Int32								nControlU,
									Int32								nControlV,
									const GS::Array <Coord3D>&			cPoints,
									const GS::Array <double>&			weights,
									const TRANMAT						&tran);

/****************************************************************************/
/****************************************************************************/
/*																			*/
/*			THREE DIMENSIONAL ELEMENTS BASED ON GENERATOR CURVES 			*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

typedef	GSErr	GDL_CALL	PPrismProc (
					GDL3DComponent 	component,
					GSUserData* 	userDataPtr,
					short			btype,
					Int32			status,
					PenType			pen,
					const GlimaIdx& topglima,
					const GlimaIdx& botglima,
					const GlimaIdx& sideglima,
					const ADB::AttributeIndex& ltype,
					const ADB::AttributeIndex& fillind,
					short fillframe,
					short fillcolor,
					short bkgcolor,
					Int32			ncur,
					const double	*curvx, const double *curvy, const double *curvz2, const double* ang,
					const double	*eAng,
					bool			closeIt,
					const short		*stat, const short *mask, const GlimaIdx *mats, short emask,
					MaterialEffect 	materialEffect,
					double			thickness,
					double			hx, double hy, double hz, double hh,
					double			bx, double by, double bz, double bh,
					const TRANMAT	&tran, const SegmentationRule& segmentation, short* errcode);
typedef	GSErr	GDL_CALL	SPrismProc (
					GDL3DComponent	component,
					short			btype, Int32 status,
					short			color, const GlimaIdx& topglima, const GlimaIdx& botglima, const GlimaIdx& sideglima,
					Int32			ncur, const double *curvx, const double *curvy, const double *ang,					
					bool			closeIt,
					const short		*stat, const short *mask, const GlimaIdx *mats, short emask,
					MaterialEffect	materialEffect,
					double			hx, double hy, double hz, double hh,
					double			bx, double by, double bz, double bh,
					const			TRANMAT &tran, const SegmentationRule& segmentation, short *errcode);
typedef	GSErr	GDL_CALL	BPrismProc (
					GDL3DComponent component,
					short			btype,
					PenType			pen, const GlimaIdx& topglima, const GlimaIdx& botglima, const GlimaIdx& sideglima,
					Int32			ncur,
					const double	*curvx, const double *curvy, const double *ang,
					const short		*mask, const GlimaIdx *mats,
					double			thickness, double radius, Int32 ncs,
					const TRANMAT	&tran, const SegmentationRule& segmentation, short* errcode);
typedef	GSErr	GDL_CALL	FPrismProc (
					GDL3DComponent	component,
					PenType			pen,
					const GlimaIdx& topglima, const GlimaIdx& botglima, const GlimaIdx& sideglima,
					const GlimaIdx& hillglima,
					Int32			ncur,
					const double	*curvx, const double *curvy, const double *ang,
					bool			closeIt,
					const short		*stat, const short *mask,
					double			thickness, double angle, double hill, Int32 status, Int32 ncs,
					const TRANMAT	&tran, const SegmentationRule& segmentation, short* errcode);
typedef	GSErr	GDL_CALL	MassProc (
					GDL3DComponent	component,
					PenType			pen,
					const GlimaIdx& topglima, const GlimaIdx& botglima, const GlimaIdx& sideglima,
					short			btype,
					STATL			status,
					Int32			ncur,
					const double	*curv1x, const double *curv1y, const double *curv1z, const double *ang1,
					const short		*mask,
					double			dz,
					Int32			m,
					const double	*curv2x, const double *curv2y, const double *curv2z, const double *ang2,
					const short		*stat,
					const TRANMAT	&tran,
					const SegmentationRule& segmentation,
					short			*ccerr);
typedef	GSErr	GDL_CALL	PyramidProc (
					GDL3DComponent 	component,
					PenType			pen, const GlimaIdx& glima,
					Int32			ncur,
					const double	*curvx, const double *curvy, const double *ang,
					const short		*stat,
					double			hx, double hy, double hz,
					short			mask,
					const TRANMAT	&tran,
					const SegmentationRule& segmentation,
					short			*ccerr);
typedef	GSErr	GDL_CALL	RevolveProc (
					GDL3DComponent 	component,
					GSUserData* 	userDataPtr,
					PenType			pen, const GlimaIdx& glima,
					Int32			ncur,
					const double	*curvx, const double *curvy, const double *ang,
					const short		*stat, const GlimaIdx *materials,
					double			alphaOffset,
					double			alpha,
					double			snapBetaOffset,
					double			snapBeta,
					short			mask,
					Int32			ncs,
					const TRANMAT	&tran,
					const SegmentationRule& segmentation,
					short			*out_err,
					bool			closeIt);
typedef	GSErr	GDL_CALL	SweepProc (
					GDL3DComponent 	component,
					PenType			pen, const GlimaIdx& glima,
					Int32			ngen,
					const double	*genx, const double *geny, const double *ang,
					const short		*genstat,
					Int32			ncur,
					const double	*curvx, const double *curvy, const double *curvz,
					double			dalpha,
					double			scale,
					short			mask,
					const TRANMAT	&tran,
					const SegmentationRule& segmentation,
					short			*ccerr);
typedef	GSErr	GDL_CALL	TubeProc (
					GDL3DComponent 	component,
					GSUserData* 	userDataPtr,
					short			btype,
					PenType			pen, const GlimaIdx& topglima, const GlimaIdx& botglima, const GlimaIdx& sideglima,
					Int32			ngen,
					const double	*genx, const double *geny, const double *gang,
					const short		*genstat,
					const GlimaIdx	*genmats,
					Int32			ncur, const Point3D* curv,
					const double*	ang,
					short			mask,
					bool			revol, bool closeIt,
					const TRANMAT	&tran,
					const SegmentationRule& segmentation,
					short			*ccerr);
typedef GSErr	GDL_CALL	PlanarPathTubeProc (
					GDL3DComponent 		component,
					GSUserData* 		userDataPtr,
					PenType				pen, 
					const GlimaIdx&		topglima, const GlimaIdx& botglima, const GlimaIdx& sideglima,
					Int32				ngen,
					const double		*genx, const double *geny, const double *gang,
					const short			*genstat, 
					const GlimaIdx		*genmats,
					Int32				ncur,
					const double 		*curvx, const double *curvy, const double *curvang, const short *curvstat,
					short				mask,
					const TRANMAT		*tran,
					const SegmentationRule& gensegmentation,
					const SegmentationRule& curvsegmentation,
					short				*ccerr);
typedef	GSErr	GDL_CALL	RuledProc (
					GDL3DComponent	component,
					PenType			pen, const GlimaIdx& glima,
					Int32			ncur, Int32 version,
					const double	*curv1x, const double	*curv1y, const short *stat1,
					const double	*curv2x, const double *curv2y, const double *curv2z,
					short			mask,
					const TRANMAT	&tran,
					short			*ccerr);
typedef	GSErr	GDL_CALL	RuledSegmentedProc (
					GDL3DComponent						component,
					GSUserData*							userDataPtr,
					PenType								pen,
					const GlimaIdx&						glimaTop,
					const GlimaIdx&						glimaBot,
					const GlimaIdx&						glimaSide,
					const GS::Array<GlimaIdx>*			glimas,
					const GS::Array<Coord3D>&			profile1,
					const GS::Array<Coord3D>&			profile2,
					const GS::Array<short>*				stat,
					short								mask,
					const TRANMAT&						tran,
					RuledTextureMode					ruledTextureMode);
typedef	GSErr	GDL_CALL	GDLMeshProc (
					GDL3DComponent 	component,
					PenType			pen, const GlimaIdx& glima,
					double			a, double b,
					Int32			m, Int32 n,
					const double 	*z,
					short			mask,
					const TRANMAT	&tran);
typedef	GSErr	GDL_CALL	CoonsProc (
					GDL3DComponent 	component,
					PenType			pen, const GlimaIdx& glima,
					Int32			m,
					Int32			n,
					const double	*curvUVxyz,
					short			mask,
					const TRANMAT	&tran);
typedef GSErr	GDL_CALL	CutPolyProc (GDL3DComponent component,
					GSUserData*				userDataPtr,
					Int32					ncorner,
					short					method,
					short					status,
					const Coord3D			*top,
					const Coord3D			*dir,
					double					dd,
					const short				*mask,
					const Coord3D			*corners,
					const double			*ang,
					const GlimaIdx			*mats,
					short					prim,
					const TRANMAT			&tran,
					const SegmentationRule& segmentation,
					PenType					pen,
					const GlimaIdx&			glima,
					short					*errcode);
typedef		CutPolyProc		WallHoleProc;


/****************************************************************************/
/****************************************************************************/
/*																			*/
/*						THREE DIMENSIONAL PRIMITIVES						*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

typedef	GSErr	GDL_CALL	SetBaseProc (GDL3DComponent component);
typedef	GSErr	GDL_CALL	VertProc (
									  GDL3DComponent component,
									  double		x, double y, double z,
									  GDL_VertexType	type, 
									  const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	TeveProc (
									  GDL3DComponent component,
									  double		x, double y, double z,
									  double		u, double v,
									  const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	VectProc (
									  GDL3DComponent component,
									  double		x, double y, double z,
									  const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	EdgeProc (
									  GDL3DComponent	component,
									  PenType			pen,
									  const ADB::AttributeIndex& ltype,
									  Int32		i1, Int32 i2,
									  Int32		p1, Int32 p2,
									  STATL		status);
typedef	GSErr	GDL_CALL	PgonProc (
									  GDL3DComponent	component,
									  PenType			pen, const GlimaIdx& glima,
									  Int32		irtxt,
									  Int32		npedg,
									  Int32*	ipedg,
									  Int32		ivect,
									  Int32		status,		/* -1 */
									  Wrapping	wrap,
									  const		GS::Array <Coord3D>& vertCoords,
									  const		GS::Array <Coord>&  pedg_uv,
									  const TRANMAT&	tran);

typedef GSErr	GDL_CALL	NurbsVertProc (
									  GDL3DComponent	component,
									  const Coord3D&	c,
									  GDL_VertexType	type, 
									  double			tolerance,
									  const TRANMAT&	tran);

typedef	GSErr	GDL_CALL	NurbsEdgeProc (
									  GDL3DComponent				component,
									  PenType						pen,
									  Int32							ivert1, 
									  Int32							ivert2,
									  Int32							icurve,
									  double						curveDomainBegin, 
									  double						curveDomainEnd,
									  GDL_NurbsEdgeStatus			flag,
									  double						tolerance,
									  const TRANMAT&				tran);

typedef	GSErr	GDL_CALL	NurbsTrimProc (
								      GDL3DComponent	component,
								      Int32				iedge,
								      Int32				icurve,
								      double			curveDomainBegin,
								      double			curveDomainEnd,
									  double			tolerance);

typedef	GSErr	GDL_CALL	NurbsTrimSingularProc (
								      GDL3DComponent	component,
								      Int32				ivert,
								      Int32				icurve,
								      double			curveDomainBegin,
								      double			curveDomainEnd,
									  double			tolerance);

typedef	GSErr	GDL_CALL	NurbsFaceProc (
	            					  GDL3DComponent			component,
								      PenType					pen, 
									  const GlimaIdx&			glima,
									  PenType					segmentationPen,
									  Wrapping					wrap,
									  const GS::Array<double>&	textureCoords, 
								      Int32						isurface,
									  const GS::Array <Int32>&	trims,
								      double					tolerance,
									  const TRANMAT&			tran);

typedef GSErr	GDL_CALL	NurbsLumpProc (
									  GDL3DComponent			component,
									  const GS::Array <Int32>&	faces);


typedef GSErr	GDL_CALL	PointCloudProc (
									  GDL3DComponent		component,
									  const GS::UniString&	pointCloudName,
									  const TRANMAT&		tran);
typedef	GSErr	GDL_CALL	HotsProc (
									  GDL3DComponent component,
									  GSUserData* userDataPtr,									  
									  double		x,
									  double		y,
									  double		z,
									  short			type,
									  short			subtype,
									  UInt32		unID,
									  Int32			paramIndex,
									  Int32			arrIndex1,
									  Int32			arrIndex2,
									  Int32			flag,
									  Int32			dispParamIndex,
									  Int32			dispArrIndex1,
									  Int32			dispArrIndex2,
									  GS::UniString* customDescription,
									  const TRANMAT& tran);
typedef	Int32	GDL_CALL	RtxtProc (
									  GDL3DComponent component,
									  const GS::UniString&		imageName,
									  short pictIndex,
									  double	a, double b, short mask);
typedef	GSErr	GDL_CALL	CoorProc (
									  GDL3DComponent component,
									  Wrapping	wrap,
									  const Coord3D& origin,
									  const Coord3D& endOfX,
									  const Coord3D& endOfY,
									  const Coord3D& endOfZ,
									  const TRANMAT& tran);
typedef	GSErr	GDL_CALL	CoorVertexBasedProc (
									  GDL3DComponent component,
									  Wrapping	wrap,
									  Int32		vert1, Int32 vert2, Int32 vert3, Int32 vert4);
typedef	GSErr	GDL_CALL	LineProc (
									  GDL3DComponent component,
									  PenType	pen,
									  Int32		vert1, Int32 vert2,
									  Int32		sflinc);
typedef	GSErr	GDL_CALL	TriProc (
									 GDL3DComponent component,
									 PenType	pen, const GlimaIdx& glima,
									 Int32		vert1, Int32 vert2, Int32 vert3);


/****************************************************************************/
/****************************************************************************/
/*																			*/
/*						SPECIAL THREE DIMENSIONAL ELEMENTS					*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

typedef	GSErr	GDL_CALL	WallProc (GDL3DComponent component,
									  PenType	pen,
									  const GlimaIdx& leftglima, const GlimaIdx& rightglima, const GlimaIdx& sideVglima, const GlimaIdx& sideHglima,
									  double	top,
									  double	x1, double x2, double x3, double x4,
									  double	y1, double y2, double y3, double y4,
									  double	thickness,
									  bool		gable,
									  bool		lowvis, bool upvis,
									  bool 		luvis, bool llvis, bool ruvis, bool rlvis,
									  double	begdist, double enddist,
									  double	begheight, double endheight,
									  short		nholes,
									  double	**holes,
									  bool		**frames4,
									  const TRANMAT	&tran);
typedef	GSErr	GDL_CALL	CWallProc (
					GDL3DComponent component,
					PenType			pen,
					const GlimaIdx& leftglima, const GlimaIdx& rightglima, const GlimaIdx& sideVglima, const GlimaIdx& sideHglima,
					double			top,
					double			x1, double x2, double x3, double x4,
					double			y1, double y2, double y3, double y4,
					double			thickness, double radius, Int32 ncs,
					double			beamthick, double beamoffset, short wallStatus,
					short			mask1, short mask2, short mask3, short mask4,
					short			nholes, double** holes, short** frames,
					short			nplanes, double** planes,
					const TRANMAT	&tran);

typedef	GSErr	GDL_CALL	BeamProc (
					GDL3DComponent component,
					PenType			pen,
					const GlimaIdx& leftglima, const GlimaIdx& rightglima, 
					const GlimaIdx& sideVglima, const GlimaIdx& topglima, 
					const GlimaIdx& botglima,
					double			top,
					double			x1, double x2, double x3, double x4,
					double			y1, double y2, double y3, double y4,
					double			thickness,
					short			mask1, short mask2, short mask3, short mask4,
					const TRANMAT	&tran);
typedef	GSErr	GDL_CALL	BinaryProc (
					GDL3DComponent component,
					PenType		pen, const GlimaIdx& glima,
					GDL::IFileRef*	fileRef,
					short		matmode, short subIdent, Int32 bind,
					short		actshadow,
					const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	BinaryBufProc (
										   GDL3DComponent component, GDLAttributeComponent attribcomp,
										   GSUserData* userDataPtr,
										   PenType		pen, const GlimaIdx& glima, short gmode,
										   GDL::IFileRef*		fileRef,
										   short		matmode, short subIdent, Int32 bind,
										   short		actshadow,
										   CloseBodyProc	*end,
										   VertProc			*vert, VectProc *vect, TeveProc *teve,
										   EdgeProc			*edge, PgonProc *pgon,
										   MaterGenProc		*matergen,
										   FillGenProc		*fillgen,
										   RtxtProc	*rtxt, CoorProc *coor,
										   const TRANMAT 	&tran);

typedef	GSErr	GDL_CALL	Text3Proc (
					GDL3DComponent component,
					PenType		pen, const GlimaIdx& glima,
					Int32		styleind,
					const GS::UniString&	string,
					double		thickness,
					double		hill,
					short		smoo,
					const TRANMAT		&tran);

typedef	GSErr	GDL_CALL	RichText3Proc (
					GDL3DComponent component,
					GdlTextBlockData*				textBlockData,
					GS::VAArray<GdlParagraphData>*	paragraphs,
					GSHandle						tabsHdl,		// double
					GS::VAArray<GdlStringData>*		stringsData,
					GSHandle						stringsHdl,		// Layout
					const TRANMAT&	tran);

enum PolyRoofOffsetTopMaterialMode {
	PROTMM_UseTopMaterial,
	PROTMM_UseCutMaterial
};
typedef	GSErr	GDL_CALL	PolyRoofProc (GDL3DComponent component,

										  // Line elimination control variables
										  short btype,
										  Int32 status,

										  // Pivot polygon
										  ULong pivotPolyNCoords,
										  const Coord* pivotPolyCoords,
										  const ULong* pivotPolyEdgeUIds,
										  ULong pivotPolyNContours,
										  const ULong* pivotPolyContourEnds,

										  // Z values for each level
										  ULong nZVals,
										  const double* zVals,

										  // Angles for each edge and each level
										  const double* roofAngleMatrix,

										  // Gable overhang for each edge and each level
										  const double *neighborOverHangMatrix,

										  double thickness, double totalThickness,

										  // Contour polygon
										  ULong contourPolyNCoords,
										  const Coord* contourPolyCoords,
										  const GDLGen::RoofEdgeTrim* contourPolyBottomEdgeTrim,
										  const double* contourPolyBottomEdgeAngles,
										  const ULong* contourPolyEdgeUIds,
										  ULong contourPolyNContours,
										  const ULong* contourPolyContourEnds,

										  const GDLGen::RoofContourApplication& contourApplication,

										  // Top and bottom materials for each pivot edge on each level
										  const GlimaIdx* topMats,
										  const GlimaIdx* bottomMats,
										  // Side material for each contour edge
										  const GlimaIdx* sideMats,
										  const GlimaIdx& defaultSideMat,
										  short color,

										  // Partial structure display
										  double psdEffectiveOffset,

										  PolyRoofOffsetTopMaterialMode offsetTopMaterialMode,

										  const TRANMAT& tran);

typedef	GSErr	GDL_CALL	ExtrudedShellProc (GDL3DComponent component, GSUserData* userDataPtr,
											   short color, const GlimaIdx& topglima, const GlimaIdx& botglima, const GlimaIdx& sideglima, Int32 status,
											   double fromThickness, double thickness, const ShellExplosionMode shellExplosionMode, bool isFlipped,
											   Int32 ncur, const double *curvx, const double *curvy, const double *ang, const short *mask,
											   double hx, double hy, double hz, double hh,
											   double bx, double by, double bz, double bh,
											   const GlimaIdx (&sideMaterials) [4],
											   const ShellGenerationMode shellGenMode,
											   const TRANMAT &tran, const TRANMAT &localTrafo,
											   bool draftModel,
											   short *out_err);

typedef	GSErr	GDL_CALL	RevolvedShellProc (GDL3DComponent component, GSUserData* userDataPtr,
											   short color, const GlimaIdx& topglima, const GlimaIdx& botglima, const GlimaIdx& sideglima, Int32 status,
											   double fromThickness, double thickness, const ShellExplosionMode shellExplosionMode, bool isFlippedv,
											   Int32 ncur, const double *curvx, const double *curvy, const double *ang, const short *stat,
											   double alphaOffset, double alpha,
											   Int32 nCurvedSeg, RevolveCurvedSegType curvedSegType, RevolveProfileCopiesSmoothness profSmoothness,
											   const GlimaIdx (&sideMaterials) [4],
											   const ShellGenerationMode shellGenMode,
											   const TRANMAT &tran, const TRANMAT &localTrafo,
											   bool draftModel,
											   short *out_err);

typedef	GSErr	GDL_CALL	RuledShellProc (GDL3DComponent component, GSUserData* userDataPtr,
											short color, const GlimaIdx& topglima, const GlimaIdx& botglima, const GlimaIdx& sideglima, Int32 status,
											double fromThickness, double thickness, const ShellExplosionMode shellExplosionMode, bool isFlipped,
											Int32 ncur1, const double *in_curv1x, const double *in_curv1y, const double* in_ang1, const short *in_stat1,
											Int32 ncur2, const double *in_curv2x, const double *in_curv2y, const double *in_ang2, const short *in_stat2, const TRANMAT& planeTrafo,
											const GS::Array<GS::Pair<Int32, Int32> >& definedGeneratrices,
											const GlimaIdx (&sideMaterials) [4],
											const ShellGenerationMode shellGenMode,
											const TRANMAT &tran, const TRANMAT &in_localTrafo,
											bool draftModel,
											short *out_err);


/****************************************************************************/
/****************************************************************************/
/*																			*/
/*							ELEMENTS FOR VISUALIZATION						*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

typedef	GSErr	GDL_CALL	LightProc (
					GDL3DComponent component,
					short color, const GlimaIdx& glima,
					double		rc, double gc, double bc,
					const Int32 lightType,
					double		radius,
					double		alpha, double beta,  double angfalloff,
					double		dist1, double dist2, double distfalloff,
					const		GDL::ParameterGetter& addExternalData,
					const TRANMAT		&tran);
typedef	GSErr	GDL_CALL	GDLPictProc (
					GDL3DComponent component,
					PenType		pen, short drwIndex, const GlimaIdx& glima,
					const GS::UniString& filename, short pictIndex, IMAGEREC *imageptr,
					double		a, double b,
					short		mask,
					const TRANMAT		&tran);


struct GDL3DGenerators {
	CloseBodyProc			*closeBody;
	SetModelProc			*setmodel;
	SetShadowProc			*setshadow;
	SetBodyAttributesProc	*setBodyAttributes;

	GDLBeginGroupProc		*gdlbegingroup;
	GDLEndGroupProc			*gdlendgroup;
	GDLClearGroupProc		*gdlcleargroup;
	GDLClearGroupsByMainGroupIdProc	*gdlcleargroupsbymaingroupid;
	GDLOperationGroupsProc	*gdloperationgroups;
	GDLPlaceGroupProc		*gdlplacegroup;
	GDLSweepGroupProc		*gdlsweepgroup;
	GDLCreateGroupWithMaterialProc	*gdlcreategroupwithmaterial;

	BodyProc				*body;
	NurbsBodyProc			*nurbsbody;

	SegmentProc				*segment;
	HotLineProc				*hotline;
	ArcProc					*arc;
	HotArcProc				*hotarc;
	CircleProc				*circle;
	RectProc				*rect;

	BrickProc				*brick;
	CylindProc				*cylind;
	GenCylProc				*gencyl;
	SphereProc				*sphere;
	EllipsProc				*ellips;
	ConeProc				*cone;
	ElbowProc				*elbow;
	NurbsCurve2DProc		*nurbscurve2d;
	NurbsCurve3DProc		*nurbscurve3d;
	NurbsSurfaceProc		*nurbssurface;

	WallHoleProc			*wallhole;
	PPrismProc				*pprism;
	SPrismProc				*sprism;
	BPrismProc				*bprism;
	FPrismProc				*fprism;
	MassProc				*mass;
	PyramidProc				*pyramid;
	RevolveProc				*revolve;
	SweepProc				*sweep;
	TubeProc				*tube;
	PlanarPathTubeProc		*planarPathTube;
	RuledProc				*ruled;
	RuledSegmentedProc		*ruledsegmented;
	GDLMeshProc				*mesh;
	CoonsProc				*coons;
	CutPolyProc				*cutPoly;

	WallProc				*wall;
	CWallProc				*cwall;
	BeamProc				*beam;
	BinaryProc				*binary;
	BinaryBufProc			*binarybuf;
	Text3Proc				*text3;
	RichText3Proc			*richtext3;
	LightProc				*light;
	GDLPictProc				*gdlpict;

	SetBaseProc				*setbase;
	VertProc				*vert;
	TeveProc				*teve;
	VectProc				*vect;
	EdgeProc				*edge;
	PgonProc				*pgon;
	NurbsVertProc			*nurbsvert;
	NurbsEdgeProc			*nurbsedge;
	NurbsTrimProc			*nurbstrim;
	NurbsTrimSingularProc	*nurbstrimsingular;
	NurbsFaceProc			*nurbsface;
	NurbsLumpProc			*nurbslump;

	PointCloudProc			*pointcloud;
	HotsProc				*hotspot;
	RtxtProc				*rtxt;
	CoorProc				*coor;
	CoorVertexBasedProc		*coorvertexbased;
	LineProc				*line;
	TriProc					*tri;

	PolyRoofProc			*polyroof;
	ExtrudedShellProc		*extrudedshell;
	RevolvedShellProc		*revolvedshell;
	RuledShellProc			*ruledshell;

	ForceBodyInfoClosingProc	*forcebodyinfoclosing;

	PlaceCutplaneProc			*placecutplane;
	RemoveLastCutplaneProc		*removelastcutplane;
	RemoveAllCutplanesProc		*removeallcutplanes;

	PushBodyInfoStateProc		*pushbodyinfostate;
	PopBodyInfoStateProc		*popbodyinfostate;

	GDL3DComponent	component;
};

/****************************************************************************/
/****************************************************************************/
/*																			*/
/*							TWO DIMENSIONAL ELEMENTS						*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

struct GDL2DComponent {
	void*	data;
};

typedef	GSErr	GDL_CALL	Hotspot2Proc (
					GDL2DComponent genData,
					GSUserData*	userDataPtr,
					short			layer,
					short color,		short drwIndex,
					double			x,	double y,
					short			type,
					short			subtype,
					UInt32			unID,
					Int32			paramIndex,
					Int32			arrIndex1,
					Int32			arrIndex2,
					Int32			flag,
					Int32			dispParamIndex,
					Int32			dispArrIndex1,
					Int32			dispArrIndex2,
					GS::UniString*	customDescription,
					const TRANMAT&	tran);
typedef	GSErr	GDL_CALL	Line2Proc (
					GDL2DComponent genData,
					GSUserData* userDataPtr,
					short				layer, PenType pen, short drwIndex,
					const ADB::AttributeIndex&	ltype,
					short lineProperty,
					double		x1, double y1,
					double		x2, double y2,
					const TRANMAT& tran);
typedef	GSErr	GDL_CALL	HotLine2Proc (
					GDL2DComponent genData,
					GSUserData* userDataPtr,
					short	layer,
					PenType pen, short drwIndex,
					const ADB::AttributeIndex& ltype,
					short lineProperty,
					double		x1, double y1,
					double		x2, double y2,
					UInt32		unID,
					const TRANMAT& tran);
typedef	GSErr	GDL_CALL	Rect2Proc (
					GDL2DComponent genData,
					GSUserData* userDataPtr,
					short				layer, PenType pen, short drwIndex,
					const ADB::AttributeIndex& ltype,
					short lineProperty,
					double		x1, double y1,
					double		x2, double y2,
					const TRANMAT& tran);
typedef	GSErr	GDL_CALL	Arc2Proc (
					GDL2DComponent genData,
					GSUserData* userDataPtr,
					short				layer, PenType pen, short drwIndex,
					const ADB::AttributeIndex& ltype,
					short lineProperty, const ADB::AttributeIndex& fillind,
					double		r,
					double		alpha, double beta,
					Int32		ncs,
					const TRANMAT& tran);
typedef	GSErr	GDL_CALL	HotArc2Proc (
					GDL2DComponent genData,
					GSUserData* userDataPtr,
					short	layer, PenType pen, short drwIndex,
					const ADB::AttributeIndex& ltype,
					short lineProperty,
					const ADB::AttributeIndex& fillind,
					double		x, double y,
					double		r,
					double		alpha, double beta,
					UInt32		unID,
					Int32		ncs,
					const TRANMAT& tran);
typedef	GSErr	GDL_CALL	Circle2Proc (
					GDL2DComponent genData,
					GSUserData* userDataPtr,
					short	layer, PenType pen, short drwIndex,
					const ADB::AttributeIndex& ltype,
					short lineProperty, const ADB::AttributeIndex& fillind,
					double		r,
					Int32		ncs,
					const TRANMAT& tran);
typedef	GSErr	GDL_CALL	Poly2Proc (
					GDL2DComponent genData,
					GSUserData* userDataPtr,
					short				layer, PenType pen, short drwIndex,
					const ADB::AttributeIndex& ltype,
					short lineProperty,
					double		offsX, double offsY,
					double		hatchmat00, double hatchmat10, double hatchmat01, double hatchmat11, GDL_HatchCompatibilityLevel compatlevel,
					double		gradInnerRadius,
					const ADB::AttributeIndex& fillind,
					short		fillframe, GDL_FillCategory fillcategory, Int32 flags,
					short		fillcolor, short bkgcolor,
					Int32		ncur,
					double		*curvx, double *curvy, double **angle,
					short		*mask, ADB::AttributeIndex *edgeLineType, short *edgeColor,
					const TRANMAT& tran,
					const SegmentationRule* segmentation,
					bool		closeIt,
					short		*ccerr);
typedef	GSErr	GDL_CALL	Spline2Proc (
					GDL2DComponent genData,
					GSUserData* userDataPtr,
					short				layer, PenType pen, short drwIndex,
					const ADB::AttributeIndex& ltype,
					short lineProperty, Int32 ncur,
					double		*curvx, double *curvy, double *ang, short stat,
					double		*lenPrev, double *lenNext,
					const TRANMAT& tran);
typedef	GSErr	GDL_CALL	Picture2Proc (
					GDL2DComponent genData,
					GSUserData* userDataPtr,
					GDL::IFileServices* fileservices,
					short				layer,
					PenType				pen,
					short				drwIndex,
					const GlimaIdx&		glima,
					const GS::UniString& imageName, short pictIndex, IMAGEREC *imageptr,
					double		a, double b,
					short		mask,
					const TRANMAT& tran);
typedef	GSErr	GDL_CALL	Text2Proc (
								GDL2DComponent			genData,
								GSUserData*				userDataPtr,
								short					layer,
								PenType					pen,
								short					drwIndex,
								Int32					styleind,
								const GS::UniString&	string,
								double		x, double y,
								double		length,
								short		paramInd, Int32 ind1, Int32 ind2,
								const TRANMAT& tran);
typedef	GSErr	GDL_CALL	FragmentProc (
											GDL2DComponent		genData,
											GSUserData*			userDataPtr,
											GDL::IFileRef*		fileRef,
											short				attribflag,
											short				layer,
											PenType				pen,
											short				drwIndex,
											const ADB::AttributeIndex& ltype,
											short				lineProperty,
											const ADB::AttributeIndex& fillind,
											const TRANMAT&		tran);
typedef	GSErr	GDL_CALL	RichText2Proc (
								GDL2DComponent					genData,
								GSUserData*						userDataPtr,
								short							layer,
								short							drwIndex,
								GdlTextBlockData*				textBlockData,
								GS::VAArray<GdlParagraphData>*	paragraphs,
								GSHandle						tabsHdl,		// double
								GS::VAArray<GdlStringData>*		stringsData,
								GSHandle						stringsHdl,		// Layout
								const TRANMAT&					tran);
typedef	GSErr	GDL_CALL	FragmentPrimProc (
						GDL2DComponent			gdl2Dcomponent,
						GDLAttributeComponent	gdlAttribComponent,
						GSUserData*				userDataPtr,
						GDL::IFileRef*			fileRef,
						short					attribflag,
						short					layer,
						PenType					pen,
						short					drwIndex,
						const ADB::AttributeIndex& ltype,
						short					lineProperty,
						const ADB::AttributeIndex& fillind,	Int32			styleind,
						Hotspot2Proc*	hotspot2,		Line2Proc*		line2,
						Picture2Proc*	picture2,		Arc2Proc*		arc2,
						Circle2Proc*	circle2,		Spline2Proc*	spline2,
						Poly2Proc*		poly2,			Text2Proc*		text2,
						RichText2Proc*	richtext2,
						TextLenProc*	textlen,		StyleGenProc*	stylegen,
						const TRANMAT&	tran);

enum Project2PartBits {
	Prj2_CutPolygons					= 0x01,
	Prj2_CutPolygonEdges				= 0x02,
	Prj2_ViewPolygons					= 0x04,
	Prj2_ViewPolygonEdges				= 0x08,
	Prj2_Project3DHotspotsAsStatic2D	= 0x10,
	Prj2_Project3DHotLinesAndHotArcs	= 0x20,
	Prj2_PointClouds					= 0x40,
	Prj2_UsedBitsUpToV3					= Prj2_CutPolygons | Prj2_CutPolygonEdges | Prj2_ViewPolygons | Prj2_ViewPolygonEdges | Prj2_Project3DHotspotsAsStatic2D | Prj2_Project3DHotLinesAndHotArcs,
	Prj2_UsedBitsSinceV4				= Prj2_CutPolygons | Prj2_CutPolygonEdges | Prj2_ViewPolygons | Prj2_ViewPolygonEdges | Prj2_Project3DHotspotsAsStatic2D | Prj2_Project3DHotLinesAndHotArcs | Prj2_PointClouds
};

enum Project2HotspotExportFlags {
	Prj2Hots_Project3DHotspotsAsStatic2D	= 0x1,
	Prj2Hots_Project3DHotLinesAndHotArcs	= 0x2,
	Prj2Hots_ProjectAllHots					= Prj2Hots_Project3DHotspotsAsStatic2D | Prj2Hots_Project3DHotLinesAndHotArcs
};

struct MultiCutAttributes {
	// contains attributes of each PROJECT2{4} multi-cut slice

	struct FillAndLineAttributes {
		// fill attributes
		ADB::AttributeIndex	fillind;
		short				fillForeColor;
		short				fillBackColor;
		Coord				fillOrigo;
		double				fillDir;	// radian

		// line attributes
		PenType				linePen;
		ADB::AttributeIndex	lineLtype;

		FillAndLineAttributes () :
			fillind (ADB::InvalidAttributeIndex),
			fillForeColor (0),
			fillBackColor (0),
			fillDir (0.0),
			linePen (0),
			lineLtype (ADB::InvalidAttributeIndex)
		{}
	};

	struct SliceAttributes {
		short		vmode;
		short		parts;

		FillAndLineAttributes	cutAttribs;
		FillAndLineAttributes	prjAttribs;

		SliceAttributes () : 
			vmode (0),
			parts (0)
		{}
	};

	GS::Array<double>			cutPlaneHeights;	// n cut plane heights (in local coordinate system)
	GS::Array<SliceAttributes>	sliceAttributes;	// n + 1 attributes of each slice

	void	Clear ()
	{
		cutPlaneHeights.Clear ();
		sliceAttributes.Clear ();
	}
};

typedef	GSErr	GDL_CALL	Project2_Proc (
					GDL2DComponent				comp2D,
					GSUserData*					userDataPtr,
					short						version,
					short						pmode,
					double						angle,
					bool						useTransparency,
					short						hotspotExportFlags,
					const MultiCutAttributes&	multiCutAttributes,
					const TRANMAT&				tran,
					GDL::IFileRef*				fileRef,
					const GDL::ParameterGetter&	globHdl,
					const GDL::ParameterGetter&	addParHdl,
					short						color,
					const GlimaIdx&				glima,
					short						drwIndex,
					bool						genDrawing3,
					Int32*						coGlobalsBitsFrom3D,
					Int32*						ipGlobalsBitsFrom3D);

typedef	GSErr	GDL_CALL	WallHole2Proc (
								GDL2DComponent	genData,
								GSUserData* userDataPtr,
								double		offsX, double offsY,
								double		m00, double m10, double m01, double m11,
								double		gradInnerRadius,
								const ADB::AttributeIndex& fillind,
								short		fillframe, GDL_FillCategory fillcategory, Int32 flags,
								short		fillcolor, short bkgcolor,
								Int32		ncur,
								double		*curvx, double *curvy, double **angle,
								short		*mask,
								bool		isWallhole,
								const TRANMAT& tran,
								const SegmentationRule* segmentation,
								short		*ccerr);
typedef	GSErr	GDL_CALL	WallLine2Proc (
								GDL2DComponent	genData,
								GSUserData* userDataPtr,
								short				layer, PenType pen, short drwIndex,
								const ADB::AttributeIndex& ltype,
								short lineProperty,
								double	x1, double y1,
								double	x2, double y2,
								const TRANMAT& tran);
typedef	GSErr	GDL_CALL	WallArc2Proc (
								GDL2DComponent	genData,
								GSUserData* userDataPtr,
								short				layer, PenType pen, short drwIndex,
								const ADB::AttributeIndex& ltype,
								short lineProperty, const ADB::AttributeIndex& fillind,
								double		r,
								double		alpha, double beta,
								Int32		ncs,
								const TRANMAT& tran);


struct GDL2DGenerators {
	Hotspot2Proc		*hotspot2;
	Line2Proc			*line2;
	HotLine2Proc		*hotline2;
	Rect2Proc			*rect2;
	Arc2Proc			*arc2;
	HotArc2Proc			*hotarc2;
	Circle2Proc			*circle2;
	Spline2Proc			*spline2;
	Poly2Proc			*poly2;
	Picture2Proc		*picture2;
	Text2Proc			*text2;
	RichText2Proc		*richtext2;

	FragmentProc		*fragment2;
	FragmentPrimProc	*fragment2prim;
	WallHole2Proc		*wallhole2;
	WallLine2Proc		*wallline2;
	WallArc2Proc		*wallarc2;

	GDL2DComponent	component;
};


/****************************************************************************/
/****************************************************************************/
/*																			*/
/*								FILE OPERATIONS								*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

typedef	GSErr	GDL_CALL	FileInitProc (GSUserData* userDataPtr, void* gdlIp);
typedef	GSErr	GDL_CALL	FileFreeProc (GSUserData* userDataPtr, void* gdlIp);

typedef	GSErr	GDL_CALL	GetAddOnInfoProc (GSUserData* userDataPtr, void* gdlIp, const char* filter, const GS::UniString& filename,
											  const GS::UniString& paramstring, bool* isDeterministicAddOn);
typedef	GSErr	GDL_CALL	OpenFileProc (GSUserData* userDataPtr, void* gdlIp,
										  const char* filter, const GS::UniString& filename,
										  const GS::UniString& paramstring, Int32 *channel,
										  bool isDeterministicFunction);
typedef	GSErr	GDL_CALL	InputFromFileProc (GSUserData* userDataPtr, void* gdlIp, Int32 channel, const GS::UniString& recordID, const GS::UniString& fieldID,
											   Int32 nrvals, Int32 *retValue, GDLRequestResult& values, bool isDeterministicFunction);
typedef	GSErr	GDL_CALL	OutputToFileProc (GSUserData* userDataPtr, void* gdlIp,
											  Int32 channel, const GS::UniString& recordID, const GS::UniString& fieldID,
											  const GDLRequestResult& values,
											  bool isDeterministicFunction);
typedef	GSErr	GDL_CALL	CloseFileProc (GSUserData* userDataPtr, void* gdlIp, Int32 channel);

struct GDLFileHandlers {
	FileInitProc		*fileinit;
	FileFreeProc		*filefree;
	GetAddOnInfoProc	*getaddoninfo;
	OpenFileProc		*openfile;
	InputFromFileProc	*inputfromfile;
	OutputToFileProc	*outputtofile;
	CloseFileProc		*closefile;
};

/****************************************************************************/
/****************************************************************************/
/*																			*/
/*						USER INTERFACE ELEMENTS								*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

struct GDLAttributeSetComponent {
	void*	data;
};

class UISComponent;

class	GDL_DLL_EXPORT	IGDLParamUIGenerators {
public:
	virtual ~IGDLParamUIGenerators ();

	virtual	GSErr	IntfDialog (const GS::UniString& title, Int32 dx, Int32 dy) = 0;

	virtual	GSErr	Button (short type, const GS::UniString& name,
							const GS::UniString& pictName, Int32 pictIndex, const GDL::IFileRef* ownFileRef,
							Int32 posx, Int32 posy,
							Int32 xsize, Int32 ysize,
							Int32 buttonId, const GS::UniString& url,
							const GS::UniString& tooltip) = 0;
	virtual	GSErr	PushCheckButton (char *parName, Int32 ind1, Int32 ind2, const GS::UniString& text,
									const GS::UniString& pictName, Int32 pictIndex, const GDL::IFileRef* ownFileRef,
									Int32 frameFlag, Int32 posx, Int32 posy,
									Int32 xsize, Int32 ysize, const GS::UniString& tooltip) = 0;

	virtual	GSErr	TextStyleInfield (char *parName, Int32 ind1, Int32 ind2, Int32 faceCodeMask,
									  Int32 posx, Int32 posy, Int32 xsize, Int32 ysize, Int32 offsetX) = 0;

	virtual	GSErr	RadioButton (char *parName, bool isStrValue, const GS::UniString& strValue, double numValue,
								 const GS::UniString& name,
								 const GS::UniString& pictName, Int32 pictIndex, const GDL::IFileRef* ownFileRef,
								 Int32 posx, Int32 posy,
								 Int32 xsize, Int32 ysize, const GS::UniString& tooltip,
								 Int32 ind1, Int32 ind2) = 0;

	virtual	GSErr	InField (char *parName,
							 Int32 arrIndex1, Int32 arrIndex2,
							 Int32 posx, Int32 posy,
							 Int32 xsize, Int32 ysize,
							 short version, short method,
							 const GS::UniString& pictName, Int32 pictIndex,
							 const GDL::IFileRef* ownFileRef,
							 Int32 nrPict, Int32 nrRows,
							 Int32 cellX, Int32 cellY, Int32 imageX, Int32 imageY,
							 Int32 n, Int32 *indexValues, Int32 *offsets, GS::UniChar::Layout* texts,
							 double* numValues, Int32 *strOffsets, GS::UniChar::Layout* strValues,
							 const GS::UniString& tooltip) = 0;

	virtual	GSErr	OutField (const GS::UniString* compName,
							  const GS::UniString* valueStr, double value,
							  Int32 posx, Int32 posy,
							  Int32 xsize, Int32 ysize,
							  short flags,
							  const GS::UniString& tooltip) = 0;

	virtual	GSErr	IntfPage (Int32 pageId, Int32 version, Int32 parentId, const GS::UniString& pageTitle, const GDL::IFileRef* ownFileRef, const GS::UniString& pictName, Int32 pictIndex) = 0;

	virtual	GSErr	SeparatorLine (Int32		x1, Int32 y1,
								   Int32		x2, Int32 y2) = 0;

	virtual	GSErr	GroupBox (const GS::UniString& title,
							  Int32		posx, Int32 posy,
							  Int32 	xsize, Int32 ysize) = 0;

	virtual	GSErr	UiPict (const GS::UniString&	fname,
							short					pictIndex,
							const GDL::IFileRef*	ownFileRef,
							Int32		posx, Int32 posy,
							Int32 		xsize, Int32 ysize,
							short		mask,
							const GS::UniString&	tooltip) = 0;

	virtual GSErr	UiStyle (short		fontSize,
							 short		facecode) = 0;

	virtual	GSErr	IntfCurrentPage (Int32 pageId) = 0;

	virtual	GSErr	UiListField (Int32 x, Int32 y,
								 Int32 width, Int32 height,
								 const GS::UniString&  descritpion_header,
								 const GS::UniString&  value_header,
								 Int32 fieldID, Int32 iconColumnFlag,
								 const GS::UniString& tooltip) = 0;

	virtual	GSErr	UiListItem (Int32 fieldID,
								Int32 imageIndex, const GS::UniString& imageName,
								char *parName, Int32 ind1, Int32 ind2,
								const GS::UniString& paramDescription,
								Int32 childFlag,
								Int32 itemID,
								const GS::UniString& tooltip) = 0;

	virtual	GSErr	UiColorPicker (char* redParName, Int32 redInd1, Int32 redind2,
								   char* greenParName, Int32 greenInd1, Int32 greenInd2,
								   char* blueParName, Int32 blueInd1, Int32 blueInd2,
								   double x0, double y0, double width, double height) = 0;

	virtual	GSErr	UiSlider (char *parName,
							  Int32 arrIndex1, Int32 arrIndex2,
							  Int32 x0, Int32 y0,
							  Int32 width, Int32 height,
							  Int32 nSegments, short sliderStyle) = 0;

	virtual	GSErr	UICustomPopupInField (char *parName,
										 Int32 arrIndex1, Int32 arrIndex2,
										 Int32 posx, Int32 posy,
										 Int32 xsize, Int32 ysize,
										 bool custom,
										 short storeHiddenId, Int32 treeDepth,
										 GS::Array<double>& numIdVals, GS::Array<double>& numVals,
										 GS::Array<GS::UniString>& stringIdVals, GS::Array<GS::UniString>& stringVals,								
										 const GS::UniString& selectedValDescription,
										 const GS::UniString& tooltip) = 0;

	virtual	GSErr	UICustomPopupListItem (Int32 fieldID,
										 Int32 imageIndex, const GS::UniString& imageName,
										 char *parName, Int32 ind1, Int32 ind2,
										 const GS::UniString& paramDescription,
										 Int32 childFlag,
										 Int32 itemID,
										 bool custom,
										 short storeHiddenId, Int32 treeDepth,
										 GS::Array<double>& numIdVals, GS::Array<double>& numVals,
										 GS::Array<GS::UniString>& stringIdVals, GS::Array<GS::UniString>& stringVals,								
										 const GS::UniString& selectedValDescription,
										 const GS::UniString& tooltip) = 0;
};

/****************************************************************************/
/****************************************************************************/
/*																			*/
/*							VALUE LIST ELEMENTS								*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

struct GDLParamVLComponent {
	IValueListComponent*	data;

	GDLParamVLComponent () : data (nullptr) {};
};

struct ValueListNumType {

		ValueListNumType () : value (0.0),  lowerLimit (0.0), upperLimit (0.0), stepBeg (0.0), stepVal (0.0), flags (0), dummy (0), valueDescription () {};
		~ValueListNumType (void) {};

	double			value;      // used when no limits defined
	double			lowerLimit; // used when Vlv_LowerLimit is set
	double			upperLimit; // used when Vlv_UpperLimit is set
	double			stepBeg;    // used when Vlv_Step is set
	double			stepVal;    // used when Vlv_Step is set
	UInt32			flags;
	UInt32			dummy;
	GS::UniString	valueDescription;	// optional description string of the value
};

inline bool operator== (const ValueListNumType& left, const ValueListNumType& right);
inline bool operator!= (const ValueListNumType& left, const ValueListNumType& right);


class GDL_DLL_EXPORT IValueListAttributeFilter {
	GS::AtomicCounter	m_counter;
public:
	IValueListAttributeFilter () : m_counter (0) {};
	virtual ~IValueListAttributeFilter ();

	void			AddRef (void) { ++m_counter; }
	void			Release (void)
	{
		--m_counter;
		if (m_counter == 0)
			delete this;
	}

	virtual bool Equals (const IValueListAttributeFilter& other) const = 0;

	virtual void GenerateFilteredList (GS::Array<ValueListNumType>&	numArray) const = 0;
};


using AttributeFilterCreator = std::function<GS::SharedPtr<IValueListAttributeFilter> (const ADB::IAttributeSetProvider&)>;


class	GDL_DLL_EXPORT	IGDLParamVLGenerators {
public:
	virtual ~IGDLParamVLGenerators ();

	virtual	GSErr	Values (InterpretationMode interpretationMode, char* parName, const Int32 paramInd, Int32 nrvals,
							GS::Array<ValueListNumType>& numvals, Int32 *stringOffsets, GSHandle stringvals,
							bool custom, const AttributeFilterCreator& attributeFilterCreator) = 0;

	virtual	GSErr	Values (InterpretationMode interpretationMode, char* parName, const Int32 paramInd, Int32 nrvals,
							GS::Array<ValueListNumType>& numvals, Int32 *stringOffsets, GSHandle stringvals,
							bool custom) = 0;

	virtual	GSErr	ParLock (bool lockAll, const GS::Array<Int32>& paramInds) = 0;

	virtual	GSErr	ParHide (bool hideAll, const GS::Array<Int32>& paramInds) = 0;

	virtual	GSErr	ParSet (const Int32 paramInd,
							Int32 dim1, Int32 dim2,
							Int32 ind1, Int32 ind2,
							double numValue, const void *arrVal, const GDL::Dictionary* dictVal) = 0;

	virtual	GSErr	NewPar (const GS::UniString& aParName,
							short dataType,
							Int32 aDim1, Int32 aDim2,
							short* errCode) = 0;
	virtual	Int32	GetNewParInd (const GS::UniString& aParName, bool* isArray, short* par_dataTyp, Int32* parDim1, Int32* parDim2) = 0;
};


/****************************************************************************/
/****************************************************************************/
/*																			*/
/*								PROPERTIES									*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

typedef GSErr	GDL_CALL	PropInitProc (GSUserData* userDataPtr);
typedef void	GDL_CALL	PropFreeProc (GSUserData* userDataPtr);
typedef GSErr	GDL_CALL	DescriptorProc (GSUserData*			userDataPtr,
											Int32					dbSetIndex,
											const GS::UniString&	name,
											short					bomposition,
											const GS::UniString&	code,
											const GS::UniString&	keycode,
											bool					reference);
typedef GSErr	GDL_CALL	ComponentProc  (GSUserData*			userDataPtr,
											Int32					dbSetIndex,
											const GS::UniString&	namestr,
											double					quantity,
											const GS::UniString&	measurestr,
											short					bomposition,
											short					propwith,
											const GS::UniString&	code,
											const GS::UniString&	keycode,
											const GS::UniString&	unitcode,
											bool					reference,
											bool					mul_quant);
typedef Int32	GDL_CALL	StoreDBSetNamesProc (GDL::IFileServices* fileServices, GSUserData* userDataPtr, const GS::UniString& mastergdlName,
												 const GS::UniString& dbsetName, const GS::UniString& descName, const GS::UniString& compName,
												 const GS::UniString& unitName, const GS::UniString& keyName, const GS::UniString& critName,
												 const GS::UniString& listsetName);
typedef Int32	GDL_CALL	FilterProc (GSUserData* userDataPtr, char *filterName, char *strVal, double numVal);
typedef	GSErr	GDL_CALL	DrawingProc (GDL3DComponent component, //M-256 only for ProcessControl&
										 GSUserData*		userDataPtr,
										 GDL::IFileRef*		fileRef,
										 const GDL::ParameterGetter& globHdl,
										 const GDL::ParameterGetter&		addParHdl,
										 PenType			pen,
										 const ADB::AttributeIndex& lType);
typedef	GSErr	GDL_CALL	BinaryPropProc (GSUserData*	userDataPtr,
											GDL::IFileRef*	fileRef,
											const GDL::ParameterGetter&	globHdl,
											const GDL::ParameterGetter&	addParHdl);
typedef	GSErr	GDL_CALL	Drawing2Proc (const GDL::ParameterGetter&		globHdl,
										  GSUserData*		userDataPtr,
										  const TRANMAT&	tran,
										  bool				label);

typedef	GSErr	GDL_CALL	TotalSurfaceVolumeProc (GDL3DComponent component,  //M-256 only for ProcessControl&
													GSUserData*		userDataPtr,
													GDL::IFileRef*	fileRef,
													const GDL::ParameterGetter&		externalGlobHdl,
													const GDL::ParameterGetter&	addParHdl,
													double		*surface,
													double		*volume);
struct GDLPropertyGenerators {
	Drawing2Proc			*drawing2;
	PropInitProc			*propinit;
	PropFreeProc			*propfree;
	DescriptorProc			*descriptor;
	ComponentProc			*component;
	StoreDBSetNamesProc		*dbsetnames;
	FilterProc				*filter;
	DrawingProc				*drawing;
	BinaryPropProc			*binaryprop;
	TotalSurfaceVolumeProc	*surfvol;
};


/****************************************************************************/
/****************************************************************************/
/*																			*/
/*								ERRORS AND WARNINGS							*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

typedef	GSErr	GSU_CALL		PrintStrProc (GSUserData* userDataPtr,
											  const char* str,
											  MessageProc *msgProc);

typedef	GSErr	GSU_CALL		InitWarnProc (GSUserData* userDataPtr);

typedef	GSErr	GSU_CALL		ReadWarnProc (GSUserData*			userDataPtr,
											  const char*			cFileName,
											  const char*			errtxt,
											  Int32					firstlin,
											  Int32					lastlin,
											  const GdlErrDisplayData*	errDisp,
											  MessageProc			*msgProc);

typedef	GSErr	GSU_CALL		ReadErrProc  (GSUserData*			userDataPtr,
											  const char*			cFileName,
											  const char*			errtxt,
											  Int32					firstlin,
											  Int32					lastlin,
											  Int32					syscod,
											  const GdlErrDisplayData*	errDisp,
											  MessageProc*				msgProc);

struct GDL_DLL_EXPORT GDLReportProcs {
	PrintStrProc*	printstr		= nullptr;
	InitWarnProc*	initwarn		= nullptr;
	ReadWarnProc*	readwarn		= nullptr;
	ReadErrProc*	readerr			= nullptr;

	static GDLReportProcs Create (PrintStrProc	*inPrintstr, InitWarnProc *inInitwarn, ReadWarnProc *inReadwarn, ReadErrProc *inReaderr);
	static GDLReportProcs CreateAllFilled ();
	static GDLReportProcs CreateAllNull ();
};

struct GDL_DLL_EXPORT GDLMessageProcs {
	MessageProc*	errorStrProc		= nullptr;
	MessageProc*	warningStrProc		= nullptr;
	MessageProc*	reportProc			= nullptr;
	MessageProc*	debugProc			= nullptr;

	static GDLMessageProcs	CreateAllFilled ();
	static GDLMessageProcs	CreateAllNull ();
};

struct GDL_DLL_EXPORT GDLMessageReporters {
	GDLReportProcs		reportHandlers;
	GDLMessageProcs		output;

	GDLMessageReporters ();
	GDLMessageReporters (const GDLReportProcs& reportHandlers, const GDLMessageProcs& output);

	GDLMessageReporters		DuplicateUsingReporterHandlers (const GDLReportProcs& reporterHandlers) const;

	static GDLMessageReporters	Create (const GDLReportProcs& reportHandlers, const GDLMessageProcs& output);
	static GDLMessageReporters	CreateAllFilled ();
	static GDLMessageReporters	CreateAllNull ();
	static GDLMessageReporters	CreateWithoutPrint ();
	static GDLMessageReporters	CreateWithoutWarningAndErrorHandling ();
	static GDLMessageReporters	CreateOnlyMessageProcs ();
	static GDLMessageReporters	CreateAllButErrorGoesToWarningOutput ();
};

/****************************************************************************/
/****************************************************************************/
/*																			*/
/*								UNUSED PARAMETERS							*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

typedef void GDL_CALL  AddParameterProc (const GS::UniString& aParName, bool addToUnused);
typedef void GDL_CALL  AddMacroNameProc (const GS::UniString& aMacroName);
typedef void GDL_CALL  DeleteParameterProc (const GS::UniString& aParName);
typedef void GDL_CALL  FinishParameterLoadProc (void);

struct GDLUnusedParameterManagers {
	AddParameterProc*			addParameter;
	AddMacroNameProc*			addMacroName;
	DeleteParameterProc*		deleteParameter;
	FinishParameterLoadProc*	finishParameterLoad;

};


/****************************************************************************/
/****************************************************************************/
/*																			*/
/*								MISCELLANEOUS								*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

// GDL Debugging
typedef GdlDebugMemento*	GDL_CALL	CreateDebugMementoProc (const GDL::IFileRef* fileRef, GdlGenProcs* genenv);

typedef GSErr	GDL_CALL	KillDebugMementoProc (GdlDebugMemento* debugEnvironment);

// LP Editor
typedef	GSErr	GDL_CALL	SelectLineProc (GSUserData* userDataPtr, GDL::IFileRef* fileRef,
											Int32 begLin, Int32 endLin, GDL_ScriptType scriptType);


/****************************************************************************/
/****************************************************************************/
/*																			*/
/*									GDLEnv									*/
/*																			*/
/****************************************************************************/
/****************************************************************************/

struct GDLEnv {
		IGDLRequests*			requests;
		GDLAttributeGenerators	genAttrib;
		IGDLGlobalAttrQueries*	queryGlobAttrib;
		GDL3DGenerators			gen3D;
		GDL2DGenerators			gen2D;
		GDLFileHandlers			fileHandlers;
		IGDLParamUIGenerators*	genUI;
		IGDLParamVLGenerators*	genVL;

		Project2_Proc			*project2;			// RZ 2003.2.18 property/drawing3 utasitas is ilyet hasznal

		TextLenProc				*textlen;

		GDL::FileOperations		*fileOperations;
		GDL::IFileServices		*fileServices;
};

inline bool operator== (const ValueListNumType& left, const ValueListNumType& right)
{
	return (fabs(left.value - right.value) < EPS &&
			fabs(left.lowerLimit - right.lowerLimit) < EPS &&
			fabs(left.upperLimit - right.upperLimit) < EPS &&
			fabs(left.stepBeg - right.stepBeg) < EPS &&
			fabs(left.stepVal - right.stepVal) < EPS &&
			left.flags == right.flags &&
			left.dummy == right.dummy &&
			left.valueDescription == right.valueDescription);
}


inline bool operator!= (const ValueListNumType& left, const ValueListNumType& right)
{
	return !(left==right);
}

#endif
