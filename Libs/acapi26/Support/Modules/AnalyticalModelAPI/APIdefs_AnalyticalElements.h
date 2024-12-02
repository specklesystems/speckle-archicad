#if !defined (APIDEFS_ANALYTICALELEMENTS_H)
#define APIDEFS_ANALYTICALELEMENTS_H

#include "AnalyticalModelAPIExport.hpp"

//from GSRoot
#include "Array.hpp"
#include "HashCommon.hpp"

//from ARCHICADAPI
#include "APIdefs_Base.h"
#include "APIdefs_Elements.h"


extern "C" {


ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalSupportID;
ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalLinkID;
ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalPointLoadID;
ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalEdgeLoadID;
ANALYTICALMODELAPI_EXPORT extern const API_Guid API_AnalyticalSurfaceLoadID;


enum API_AnalyticalMemberPartRefType : UInt16 {
	API_AMPartRef_BegVertex		= 1,
	API_AMPartRef_EndVertex		= 2,
	API_AMPartRef_CustomVertex	= 3,
	API_AMPartRef_Edge			= 4,
	API_AMPartRef_RatioEdge		= 5,
	API_AMPartRef_Surface		= 6,
	API_AMPartRef_CustomSurface = 7,
	API_AMPartRef_CustomEdge	= 8
};

class API_InternalAnalyticalMemberPartId {
public:
	UIndex contourIdx;
	UIndex edgeOrVertexIdx;
	UIndex edgeFragmentIndex;

	bool	operator==	(const API_InternalAnalyticalMemberPartId& right) const
	{ 
		return contourIdx			== right.contourIdx
			&& edgeOrVertexIdx		== right.edgeOrVertexIdx
			&& edgeFragmentIndex	== right.edgeFragmentIndex;
	}

	ULong	GenerateHashValue () const
	{
		return GS::CalculateHashValue (contourIdx, edgeOrVertexIdx, edgeFragmentIndex);
	}
};


typedef struct {
	API_Coord3D							customVertexCoord;
} API_AMPartRefCustomVertexData;


typedef struct {
	double								ratioStart;
	double								ratioEnd;
} API_AMPartRefRatioEdgeData;


typedef struct {
	API_Guid							elemGuid;
	API_AnalyticalMemberPartRefType		partRefType;
	API_InternalAnalyticalMemberPartId	partId;
	API_AMPartRefCustomVertexData		customVertexData;
	API_AMPartRefRatioEdgeData			ratioEdgeData;
} API_AnalyticalMemberPartRef;

// --- AnalyticalNode ----------------------------------------------------------

typedef struct {
	UInt32					nodeId;
	API_Coord3D				coord;
} API_AnalyticalNode;

// --- AnalyticalCurve ---------------------------------------------------------

typedef enum {
	API_AnalyticalCurve_LineType,
	API_AnalyticalCurve_ArcType,
	API_AnalyticalCurve_SplineType,
	API_AnalyticalCurve_BezierType,
	API_AnalyticalCurve_EllipseType,
} API_AnalyticalCurveType;

typedef struct {
	API_AnalyticalCurveType			type;
	API_AnalyticalNode				begNode;
	API_AnalyticalNode 				endNode;
	GS::Array<API_Coord3D>			midCoords;
} API_AnalyticalCurve;


// Analytical Support

enum API_AnalyticalCoordSysDirection : UInt16 {
	API_Global	= 1,
	API_Local	= 2,
};

enum API_AnalyticalRigidityType : UInt16 {
	API_FreeType					= 1,
	API_RigidType					= 2,
	API_CustomType					= 3,
	API_RigidCompressionOnlyType	= 4,
	API_RigidTensionOnlyType		= 5,
	API_CustomCompressionOnlyType	= 6,
	API_CustomTensionOnlyType		= 7,
};

enum API_AnalyticalSupport_SupportType : UInt16 {
	API_SimplePoint = 1,
	API_SingleLine	= 2,
	API_Surface		= 3
};

typedef struct {
	API_AnalyticalRigidityType				xType;
	double									xValue;
	API_AnalyticalRigidityType				yType;
	double									yValue;
	API_AnalyticalRigidityType				zType;
	double									zValue;
	API_AnalyticalRigidityType				rxType;
	double									rxValue;
	API_AnalyticalRigidityType				ryType;
	double									ryValue;
	API_AnalyticalRigidityType				rzType;
	double									rzValue;
} API_AnalyticalSupport_SupportValues;

typedef struct {
	API_AnalyticalSupport_SupportType		supportType;
	API_AnalyticalSupport_SupportValues		supportValues;
	API_AnalyticalCoordSysDirection			coordinateSystem;
} API_AnalyticalSupport_Settings;

typedef struct {
	API_AnalyticalSupport_Settings	supportSettings;
	API_AnalyticalMemberPartRef		supportedMemberPartRef;
} API_AnalyticalSupportType;


typedef struct {
	GS::Array<API_Coord3D>		coordinates;
	API_Vector3D				translationStiffnessVector;
	API_Vector3D				rotationStiffnessVector;
} API_AnalyticalSupportGeometry;


// Analytical Link

enum API_AnalyticalLink_LinkType : UInt16 {
	API_Rigid	= 1,
	API_Spring	= 2,
};

enum API_AnalyticalLink_LinkGeometry : UInt16 {
	API_Link1D	 = 1,
	API_Link2D	 = 2
};

enum API_AnalyticalLink_RigidLinkConnectionType : UInt16 {
	API_RigidConnection = 1,
	API_HingeConnection = 2,
};

typedef struct {
	API_AnalyticalRigidityType		kxType;
	double							kxValue;
	API_AnalyticalRigidityType		kyType;
	double							kyValue;
	API_AnalyticalRigidityType		kzType;
	double							kzValue;
	bool							resistanceFx;
	bool							resistanceFy;
	bool							resistanceFz;
	double							fxValue;
	double							fyValue;
	double							fzValue;
} API_AnalyticalLink_Translation;

typedef struct {
	API_AnalyticalRigidityType		kxxType;
	double							kxxValue;
	API_AnalyticalRigidityType		kyyType;
	double							kyyValue;
	API_AnalyticalRigidityType		kzzType;
	double							kzzValue;
	bool							resistanceMx;
	bool							resistanceMy;
	bool							resistanceMz;
	double							mxValue;
	double							myValue;
	double							mzValue;
} API_AnalyticalLink_Rotation;

typedef struct {
	API_AnalyticalLink_RigidLinkConnectionType startConnectionType;
	API_AnalyticalLink_RigidLinkConnectionType endConnectionType;
} API_AnalyticalLink_RigidSettings;

typedef struct {
	API_AnalyticalCoordSysDirection		direction;
	API_AnalyticalLink_Translation		translation;
	API_AnalyticalLink_Rotation			rotation;
} API_AnalyticalLink_SpringSettings;

typedef struct {
	API_AnalyticalLink_LinkGeometry		geometry;
	API_AnalyticalLink_LinkType			type;
	API_AnalyticalLink_RigidSettings	rigidSettings;
	API_AnalyticalLink_SpringSettings	springSettings;
} API_AnalyticalLink_Settings;

typedef struct {
	API_AnalyticalLink_Settings			linkSettings;
	API_AnalyticalMemberPartRef			startElementPartRef;
	API_AnalyticalMemberPartRef			endElementPartRef;
} API_AnalyticalLinkType;

typedef struct {
	GS::Array<API_Coord3D>			coordinates;
	GS::Array<API_AnalyticalCurve>	curves;
	API_Vector3D					translationStiffnessVector;
	API_Vector3D					rotationStiffnessVector;
} API_AnalyticalLinkGeometry;


// Loads

enum API_AnalyticalLoad_LoadForceType : UInt16 {
	API_Force	= 1,
	API_Moment	= 2
};

typedef struct {
	API_Guid									loadCaseId;
	API_AnalyticalLoad_LoadForceType			loadForceType;
	API_AnalyticalCoordSysDirection				coordinateSystemType;
	double										xValue;
	double										yValue;
	double										zValue;
} API_AnalyticalPointLoad_Settings;

typedef struct {
	API_AnalyticalPointLoad_Settings	analyticalPointLoadSettings;
	API_AnalyticalMemberPartRef			loadedMemberPartRef;
} API_AnalyticalPointLoadType;

typedef struct {
	API_Coord3D					coordinate;
} API_AnalyticalPointLoadGeometry;


enum API_AnalyticalLoad_LoadDistributionType : UInt16 {
	API_Uniform		= 1,
	API_Trapezoid	= 2
};

typedef struct {
	API_Guid									loadCaseId;
	API_AnalyticalLoad_LoadForceType			loadForceType;
	API_AnalyticalLoad_LoadDistributionType		loadDistributionType;
	API_AnalyticalCoordSysDirection				coordinateSystemType;
	API_Vector3D								startValue;
	API_Vector3D								endValue;
} API_AnalyticalEdgeLoad_Settings;


typedef struct {
	API_AnalyticalEdgeLoad_Settings		analyticalEdgeLoadSettings;
	API_AnalyticalMemberPartRef			loadedMemberPartRef;
} API_AnalyticalEdgeLoadType;


typedef struct {
	API_Guid									loadCaseId;
	API_AnalyticalCoordSysDirection				coordinateSystemType;
	double										xValue;
	double										yValue;
	double										zValue;
} API_AnalyticalSurfaceLoad_Settings;


typedef struct {
	API_AnalyticalSurfaceLoad_Settings		analyticalSurfaceLoadSettings;
	API_AnalyticalMemberPartRef				loadedMemberPartRef;
} API_AnalyticalSurfaceLoadType;


typedef struct {
	GS::Array<API_AnalyticalCurve>	curve;
} API_EdgeLoadCustomData;


typedef struct {
	GS::Array<API_AnalyticalCurve>	contour;
} API_SurfaceLoadCustomData;



} // extern "C"


#endif
