// *********************************************************************************************************************
// API definitions - managing Attributes
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_ATTRIBUTES_H)
#define	APIDEFS_ATTRIBUTES_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"
#include "APIdefs_LibraryParts.h"
#include "APIdefs_Environment.h"
#include "API_Guid.hpp"

namespace IO { class Location; }
namespace GS { class UniString; }
namespace PVI { typedef GS::Guid ProfileParameterId; }

// --- Compiler settings -----------------------------------------------------------------------------------------------

#define APIInvalidAttributeIndex	0

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Attribute types and common header
//
// =============================================================================

typedef enum API_AttrTypeID : int {		/* Attribute types */
	API_ZombieAttrID = 0,

	API_FirstAttributeID,
	API_PenID = API_FirstAttributeID,
	API_LayerID,
	API_LinetypeID,
	API_FilltypeID,
	API_CompWallID,
	API_MaterialID,
	API_LayerCombID,
	API_ZoneCatID,
	API_FontID,
	API_ProfileID,
	API_PenTableID,
	API_DimStandID,
	API_ModelViewOptionsID,
	API_MEPSystemID,
	API_OperationProfileID,
	API_BuildingMaterialID,
	API_LastAttributeID = API_BuildingMaterialID
} API_AttrTypeID;

struct API_Attr_Head {
	API_AttrTypeID	typeID;					/**< Type of the attribute; this identifies the attribute along
												with the @c index field.\n
												Refer to the API_AttrTypeID structure to see the possible attribute types. */
	API_AttributeIndex	index;				/**< The attribute index is the current database index of the given
												attribute. References to any attribute are done through these
												indexes. It goes from 1 to the maximum available attribute index
												for each attribute type. For pens the maximum value is always 255. */
	short			flags;					/**< The attribute flags, if applicable. They are described in the
													individual attribute sections. */
	short			filler_0[3];
	char			name[API_AttrNameLen];	/**< The name of the attribute, which appears in the appropriate dialogs. */
	API_Guid		guid;					/**< The GUID of the attribute. */
	UInt64			modiTime;				/**< The last time the attribute was modified. */
	GS::UniString*	uniStringNamePtr;		/**< Optional parameter for accessing attribute name in unistring format. */
};


	#define APIAttr_IsClientCreated		0x1000	/**< General attribute flag; the attribute has been created by the current teamwork user. */
	#define APIAttr_IsFromGDL			0x2000	/**< Attribute is generated from GDL Script of the loaded libraries (output only parameter) */



// =============================================================================
/**
 *	Pen attribute representation.
 *
 *	@remark
 *	This structure is used to manipulate pen attributes. You cannot
 *	create pens; you can just modify them.\n \n
 *	There is no additional data assigned to pen attributes in the
 *	API_AttributeDef structure.
 *
 *	@since DevKit 1.3
 *
 *	@sa
 *	API_Attr_Head, API_RGBColor, API_Attribute,\n
 *	Attribute Manager, API Types
 */

	#define APIPen_Transparent			0		/**< Transparent Pen Index (available only as a Fill background Pen) */
	#define APIPen_WindowBackground	   -1		/**< Window Background Pen Index (available only as a Fill background Pen) */

struct API_PenType {
	API_Attr_Head	head;				/**< Specifies the index of the pen. */

	API_RGBColor	rgb;				/**< Color of the pen. */
	double			width;				/**< Thickness of the pen defined in paper millimeters. */
	char			description[128];	/**< Description of the pen. */
};


// =============================================================================
/**
 *	@defgroup API_LayerType API_LayerType
 */
/*@{*/

	#define APILay_Hidden		0x0001	/**< The layer is hidden. */
	#define APILay_Locked		0x0002	/**< The layer is locked. */
	#define APILay_NotMine		0x0004	/**< The layer is not mine. */
	#define APILay_ForceToWire	0x0010	/**< Force the model to wireframe. */
	#define APILay_Xref			0x0020	/**< The layer belongs to an Xref. */

/**
 *	Layer attribute representation.
 *
 *	@remark
 *	Layers work the same way as if you would use Archicad from the
 *	user interface. This means you cannot create elements on a locked or
 *	hidden layer. This is especially important if you write an I/O type
 *	Add-On, as in this case you need to create elements on visible
 *	layers, and then modify the visibility of the layers.\n \n
 *	There is no additional data assigned to layer attributes in the
 *	API_AttributeDef structure.
 *
 *	@since DevKit 1.3
 *
 *	@sa
 *	API_Attr_Head, API_Attribute,\n
 *	Attribute Manager, API Types
 */

struct API_LayerType {
	API_Attr_Head	head;				/**< Specifies the name, index, and flags of the layer attribute. */

	Int32			conClassId;			/**< The connection class of the layer; elements on layers having the same
												class will be intersected. */
	Int32			filler_1;
};

/*@}*/

// =============================================================================
/**
 *	@defgroup API_LinetypeType API_LinetypeType
 */
/*@{*/

	#define APILine_FixScale				0x0001		/**< The line type parameters are defined with fixed values
															<I>in millimeters</I> as the line will appear on the printout. */
	#define APILine_ScaleWithPlan			0x0002		/**< The line type parameters are defined <I>in meters</I>
															at a given floor plan scale (@c defineScale);
															on the printout the lines of this line type will be scaled
															considering the actual scale. */

	typedef enum {
		APILine_SolidLine,				/**< Solid line. */
		APILine_DashedLine,				/**< Dashed line (contains dashes and gaps between them). */
		APILine_SymbolLine				/**< Symbol line (can contain different 2D shapes). */
	} API_LtypTypeID;

	typedef enum {
		APILine_IllegalItemType,
		APILine_SeparatorItemType,
		APILine_CenterDotItemType,
		APILine_CenterLineItemType,
		APILine_DotItemType,
		APILine_RightAngleItemType,
		APILine_ParallelItemType,
		APILine_LineItemType,
		APILine_CircItemType,
		APILine_ArcItemType
	} API_LtypItemID;

/**
 *	Describes the details of a symbol line.
 */

	struct API_LineItems {
		API_LtypItemID	itemType;		/**< The symbol line item type. */
		Int32			filler_1;
		double			itemCenterOffs;	/**< The vertical distance from the origin of the symbol line.
											Used in separator, center dot, and centerline item types. */
		double			itemLength;		/**< The length of the item, measured along the length of the
											item. Used in centerline, right angle, and parallel item types. */
		API_Coord		itemBegPos;		/**< The beginning position of an item. Used in dot, right angle,
											parallel, line, circle, and arc item types. */
		API_Coord		itemEndPos;		/**< The end position of an item. Used in line item type. */
		double			itemRadius;		/**< The radius of an item. Used in circle and arc item types. */
		double			itemBegAngle;	/**< The beginning angle of an item, measured from the vertical
											(!) axis. Used in arc item type. */
		double			itemEndAngle;	/**< The end angle of an item, measured from the vertical (!)
											axis. Used in arc item type. */
	};

/**
 *	Describes one segment of a dashed line.
 *
 *	@remark
 *	The total length of one segment is calculated by adding the two components together.
 *
 *	See: dashed_line.gif
 */

	struct API_DashItems {
		double			dash;			/**< The length of the dash of a dashed line. */
		double			gap;			/**< The length of the gap of a dashed line. */
	};

/**
 *	Line type attribute representation.
 *
 *	@remark
 *	A solid line is a straight line, without any gaps. You need to
 *	fill only the fields of the API_LineTypeType structure
 *	to create such a line type.\n
 *	There are additional data assigned to line type attributes in the
 *	API_AttributeDef structure; the definition of a line type dash pattern or symbol is passed through
 *	the @c ltype_dashItems and @c ltype_lineItems fields, respectively.\n \n
 *	To create a dashed line, you need to specify the following fields of the structure:
 *	@li @c period	The length of the period of the dashed line type (the total length of one segment).
 *	@li @c nItems	The number of items in the dashed line type.
 *	@li @c ltype_dashItems	This is a handle of API_DashItems, where the @c dash and @c gap fields
 *							describe the length of the visible and invisible part of one item, respectively.\n
 *	@remark
 *	To create a symbol line, you need to specify the following fields of the structure:
 *	@li @c period	The length of the period of the symbol line type (the total length of one segment).
 *	@li @c nItems	The number of items in the symbol line type.
 *	@li @c height	The height of the symbol line type.
 *	@li @c ltype_lineItems	This is a handle of API_LineItems, where the @c dash and @c gap fields
 *							describe the length of the visible and invisible part of one item, respectively.\n \n
 *	@remark
 *	There are additional data assigned to line type attributes in the
 *	API_AttributeDef structure; the definition of a line type dash pattern or symbol is passed through
 *	the @c ltype_dashItems and @c ltype_lineItems fields, respectively. Refer to the API_DashItems
 *	and API_LineItems structures to get more details on them.
 *
 *	@since DevKit 1.3
 *
 *	@sa
 *	API_Attr_Head, API_Attribute, API_AttributeDef,\n
 *	Attribute Manager, API Types
 */

struct API_LinetypeType {
	API_Attr_Head	head;				/**< Contains the name, index, and flags of the attribute. */

	double			defineScale;		/**< The original scale the line type is defined with;
											this value is used only with @c APILine_ScaleWithPlan
											(otherwise it should be 1.0). */
	double			period;				/**< The length of the period of the dashed or symbol line type (the
											total length of one segment). */
	double			height;				/**< The height of the symbol line type (0.0 for solid and dashed lines). */
	API_LtypTypeID	type;				/**< Main selector for type parsing. The possible values are shown
											in the API_LtypTypeID enumeration. */
	Int32			nItems;				/**< Number of items in the line type (for dashed/symbol type). */
};

/*@}*/

// =============================================================================
// Fill type
//
// =============================================================================

	#define APIFill_ScaleWithPlan	0x0001
	#define APIFill_ForWall			0x0002
	#define APIFill_ForPoly			0x0004
	#define APIFill_ForCover		0x0008

	#define	APITxtr_MirrorY			0x0800		/**< mirrored in Y direction */
	#define	APITxtr_MirrorX			0x0400		/**< mirrored in X direction */

	typedef enum {
		APIFill_Vector,
		APIFill_Symbol,
		APIFill_Solid,
		APIFill_Empty,
		APIFill_LinearGradient,
		APIFill_RadialGradient,
		APIFill_Image
	} API_FillSubtype;

	typedef unsigned char API_Pattern[8];

	struct API_FillLine {
		double			lFreq;			/**< frequency of line */
		double			lDir;			/**< angle of line */
		double			lOffsetLine;	/**< offset of line	(parallel...) */
		API_Coord		lOffset;		/**< offset of line */
		short			filler_1;
		short			lPartNumb;		/**< number of line parts */
		Int32			lPartOffs;		/**< line part offset in double array */
	};

	struct API_SFill_Line {
		API_Coord		begC;
		API_Coord		endC;
	};

	struct API_SFill_Arc {
		API_Coord		begC;
		API_Coord		origC;
		double			angle;
	};

struct API_FilltypeType {
	API_Attr_Head	head;

	API_FillSubtype	subType;
	bool			isPercentFill;		/* output-only; detected from the bitmap pattern content */
	bool			filler_1[3];

	API_Pattern		bitPat;				/**< pattern of fill */

	double			hXSpac;				/**< hatch spacing factor X */
	double			hYSpac;				/**< hatch spacing factor Y */
	double			hAngle;				/**< hatch angle */
	Int32			linNumb;			/**< number of hatch lines */
	Int32			hotNumb;			/**< number of hatch hotspots	*/
	Int32			arcNumb;			/**< number of hatch arcs	 */
	Int32			filNumb;			/**< number of hatch fills */

	API_Coord		c1;					/**< symbol hatch offset */
	API_Coord		c2;					/**< symbol hatch offset */

	GS::uchar_t		textureName [API_UniLongNameLen];	/**< texture file name */
	short			textureStatus;		/**< texture status APITxtr_MirrorY | APITxtr_MirrorX */
	short			filler_2[3];
	double			textureXSize;		/**< x size of the texture */
	double			textureYSize;		/**< y size of the texture */
	double			textureRotAng;		/**< rotation angle of the texture in radians */
	double			percent;			/**< percent of the translucent fill */
	Int32			filler_3[8];
};

// =============================================================================
// Composite structures
//
// =============================================================================

	#define APICWall_ForWall	0x0001
	#define APICWall_ForSlab	0x0002
	#define APICWall_ForRoof	0x0004
	#define APICWall_ForShell	0x0008

	#define APICWallComp_Core	0x0002
	#define APICWallComp_Finish	0x0020

	struct API_CWallComponent {
		API_AttributeIndex	buildingMaterial;	/**< index of the building material */
		short				framePen;			/**< index of the frame pen */
		short				flagBits;			/**< component flags APICWallComp_xxx */
		double				fillThick;			/**< absolute thickness of the component in m	*/
	};

	struct API_CWallLineComponent {
		API_AttributeIndex	ltypeInd;			/**< line type index of the skin face line */
		short				linePen;			/**< pen index of the skin face line */
		short				filler_1;
		Int32				filler_2[7];
	};

struct API_CompWallType {
	API_Attr_Head		head;				/**< head.flags contains APICWall_ */

	double				totalThick;			/**< thickness of the whole wall */
	short				nComps;				/**< number of components */
	short				filler_1;
	Int32				filler_2;
};


// =============================================================================
// Materials
//
// =============================================================================

	#define	APITxtr_LinkMat			0x1000		/**< texture linked to a material	*/

	#define	APITxtr_MirrorY			0x0800		/**< mirrored in Y direction */
	#define	APITxtr_MirrorX			0x0400		/**< mirrored in X direction */
	#define	APITxtr_RandomShift		0x0200		/**< shifted randomly */

	#define	APITxtr_SurfacePattern	0x0100		/**< alpha channel changes the surface color of the texture */
	#define	APITxtr_AmbientPattern	0x0080		/**< alpha channel changes the ambient color of the texture */
	#define	APITxtr_SpecularPattern	0x0040		/**< alpha channel changes the specular color of the texture */
	#define	APITxtr_DiffusePattern	0x0020		/**< alpha channel changes the diffuse color of the texture */
	#define	APITxtr_BumpPattern		0x0010		/**< bump mapping or surface normal perturbation */
	#define	APITxtr_TransPattern	0x0008		/**< alpha channel changes the transparency of the texture */

	#define	APITxtr_FillRectNatur	0x0004		/**< fit the rectangle with the picture in a central position	*/
												/**< using the natural aspect ratio of the picture */
	#define	APITxtr_FitPictNatur	0x0002		/**< fit the the picture in the middle of the rectangle */
												/**< using the natural aspect ratio of the picture */
	#define	APITxtr_UseAlpha		0x0001		/**< use alpha channel */

	struct API_Texture {
		short			status;			/**< texture status */
		bool			missingPict;	/**< picture is missing -- output only */
		bool			filler_1;
		Int32			filler_2;
		double			xSize;			/**< X size of the picture in model space */
		double			ySize;			/**< Y size of the picture in model space */
		double			rotAng;			/**< rotation angle in radians */
		Int32			filler_3;
		Int32			irtxt;			/**< internal use */
		GS::uchar_t		texName [API_UniLongNameLen];	/**< texture file name */
		IO::Location	*fileLoc;		/**< texture file specification */
		bool			withoutExtension;
		bool			filler_4;
		short			filler_5;
	};

	typedef enum {
		APIMater_GeneralID,				/**< General material type */
		APIMater_SimpleID,				/**< Reduced parameter set material type */
		APIMater_MatteID,				/**< Matte material type */
		APIMater_MetalID,				/**< Metal material type */
		APIMater_PlasticID,				/**< Plastic material type */
		APIMater_GlassID,				/**< Glass material type */
		APIMater_GlowingID,				/**< Glowing material type */
		APIMater_ConstID				/**< Constant material (light independent) */
	} API_MaterTypeID;

struct API_MaterialType {
	API_Attr_Head	head;

	Int32			filler_1;
	API_MaterTypeID	mtype;				/**< material type */
	short			ambientPc;			/**< ambiance reflection			[0..100] */
	short			diffusePc;			/**< diffuse reflection				[0..100] */
	short			specularPc;			/**< specular reflection			[0..100] */
	short			transpPc;			/**< transparency					[0..100] */
	short			shine;				/**< shininess*100					[0..10000] */
	short			transpAtt;			/**< transparency attenuation*100	[0..400] */
	short			emissionAtt;		/**< emission attenuation*100		[0..65535] */
	short			filler_2;
	API_RGBColor	surfaceRGB;			/**< surface color */
	API_RGBColor	specularRGB;		/**< specular color */
	API_RGBColor	emissionRGB;		/**< emission color */

	API_AttributeIndex	ifill;
	short				fillCol;			/**< Color number of defined 3D hatch (<=0 Use BODY color)	*/
	short				filler_3;

	API_Texture		texture;
};

// =============================================================================
// Layer combination
//
// =============================================================================

// =============================================================================
/**
 *	@defgroup API_LayerStat API_LayerStat
 */
/*@{*/

/**
 *	Describes one layer's characteristics in a layer combination.
 */

	struct API_LayerStat {
		API_AttributeIndex	lInd;				/**< index of the layer */
		short				lFlags;				/**< status of the layer */
		short				filler_1;
		Int32				conClassId;			/**< connection class of the layer */
		Int32				filler_2;
	};

/*@}*/

struct API_LayerCombType {
	API_Attr_Head	head;

	Int32			lNumb;				/**< number of layers */
	bool			inEffect;			/**< the layers are set according to this combination */
	bool			filler_1;
	short			filler_2;
};


// =============================================================================
// Zone category
//
// =============================================================================

struct API_ZoneCatType {
	API_Attr_Head	head;

	GS::uchar_t		catCode[API_UniLongNameLen];	/**< code for this category */
	GS::uchar_t		stampName[API_UniLongNameLen];	/**< stamp library part for this category */
	API_Guid		stampMainGuid;					/**< main part of the unique identifier of the stamp library part */
	API_Guid		stampRevGuid;					/**< revision part of the unique identifier of the stamp library part */
	API_RGBColor	rgb;							/**< RGB components of room color */
};


// =============================================================================
// Font
//
// =============================================================================

struct API_FontType {
	API_Attr_Head	head;

	GSCharCode		charCode;
	double			ascent;
	double			descent;
	double			widMax;
	double			externalLeading;
	short			substituteInd;
	short			filler_1;
};


// =============================================================================
// Profile
//
// =============================================================================

	#define APISkin_HatchAngle	0x0001
	#define APISkin_Core		0x0002
	#define APISkin_Finish		0x0020
	#define APISkin_HatchFit	0x0040

struct  API_ProfileAttrType {
	API_Attr_Head		head;

	bool				wallType;			/**< profile available for walls */
	bool				beamType;			/**< profile available for beams */
	bool				coluType;			/**< profile available for columns */
	bool				handrailType;		/**< profile available for handrails */

	bool				otherGDLObjectType;	/**< profile available for other GDL based objects */
	bool				filler_1;
	bool				filler_2;
	bool				filler_3;

	Int32				filler_4[7];
};


// =============================================================================
// Pen table
//
// =============================================================================

struct API_PenTableType {
	API_Attr_Head		head;

	bool				inEffectForModel;	/**< the active pen table for the model */
	bool				inEffectForLayout;	/**< the active pen table for the layout */
	short				filler_1;
	Int32				filler_2[4];
};


// =============================================================================
// Dimension attribute
//
// =============================================================================

struct API_DimensionAttrType {
	API_Attr_Head		head;

	API_DimensionPrefs	dim;
	Int32				filler_2[8];
};


// =============================================================================
// DisplayOutput
//
// =============================================================================

struct API_ModelViewOptionsType {
	API_Attr_Head			head;

	API_ModelViewOptions	modelViewOpt;
	Int32					filler_2[8];
};


// =============================================================================
// MEPSystem
//
// =============================================================================

struct API_MEPSystemType {
	API_Attr_Head		head;

	bool				isForDuctwork;			/**< may be used in the Ductwork domain */
	bool				isForPipework;			/**< may be used in the Pipework domain */
	bool				isForCabling;			/**< may be used in the Cabling domain */
	bool				filler_1;				//align + reserved for future domain
	short				contourPen;				/**< contour pen index */
	short				fillPen;				/**< fill (foreground) pen index */
	short				fillBgPen;				/**< fill background pen index */
	short				centerLinePen;			/**< center line pen index */
	API_AttributeIndex	fillInd;				/**< fill pattern index */
	API_AttributeIndex	centerLTypeInd;			/**< center line type index */
	API_AttributeIndex	materialInd;			/**< body material index */
	API_AttributeIndex	insulationMatInd;		/**< insulation material index */
	Int32				filler_2;				//align to 8 bytes, reserve for the future (is this enough?)
};


// =============================================================================
// HourlyProfile
//
// =============================================================================

struct API_HourlyProfile {
	GS::uchar_t		name [API_UniLongNameLen];	// name of the Daily Profile
	double			minTemp;					// desired minimum temperature
	bool			minTempDef;					// minimum temperature define
	bool			filler_1[7];
	double			maxTemp;					// desired maximum temperature
	bool			maxTempDef;					// maximum temperature define
	bool			filler_2[7];
	double			occupancyCount;				// area in square meters per capita
	double			lightGain;					// lightings heat gain
	double			equipmentGain;				// equipments heat gain
};



// =============================================================================
// DailyProfile
//
// =============================================================================

struct API_DailyProfile {
	GS::uchar_t		name [API_UniLongNameLen];	// name of the Daily Profile
	double			minTemp[24];				// desired minimum temperature a day in hour break down
	bool			minTempDefs[24];			// minimum temperature defines
	double			maxTemp[24];				// desired maximum temperature a day in hour break down
	bool			maxTempDefs[24];			// maximum temperature defines
	double			occupancyCount[24];			// area in square meters per capita a day in hour break down
	double			lightGain[24];				// lightings heat gain a day in hour break down
	double			equipmentGain[24];			// equipments heat gain a day in hour break down
};


// =============================================================================
// DailyProfileUsage
//
// =============================================================================

struct API_DailyProfileUsage {
	short		startMonth;						// start month/day of the profiled period
	short		startDay;
	short		endMonth;						// end month/day of the profiled period
	short		endDay;
	short		recurrence;						// weekly recurrence
	short		dailyProfileIndex;				// used DailyProfile in this period
};


// =============================================================================
// OperationProfile
//
// =============================================================================

typedef enum {
	APIOccupancyType_Residential = 1,			// Residential occupancy type
	APIOccupancyType_NonResidential	= 2			// Non residential occupancy type
} API_OccupancyTypeID;

struct API_OperationProfileType {
	API_Attr_Head		head;

	short				nDailyProf;				// number of daily profiles
	short				nDailyProfUsage;
	API_OccupancyTypeID occupancyType;			// Occupancy type
	double				hotWaterLoad;			// Hot Water load per capita
	double				humanHeatGain;			// Human heat gain per capita
	double				humidity;				// Humidity
};


// =============================================================================
// Building Material type
//
// =============================================================================

typedef enum {
	APIFillOrientation_ProjectOrigin	= 0,
	APIFillOrientation_ElementOrigin	= 1,
	APIFillOrientation_FitToSkin		= 2
} API_FillOrientationID;

struct API_BuildingMaterialType {
	API_Attr_Head				head;

	GS::UniString*				id;
	GS::UniString*				manufacturer;
	GS::UniString*				description;

	Int32						connPriority;				/**< connection priority */
	API_AttributeIndex			cutFill;					/**< cut fill index */
	short						cutFillPen;					/**< cut fill pen index */
	short						cutFillBackgroundPen;		/**< cut fill background pen index */
	API_AttributeIndex			cutMaterial;				/**< material index */
	API_FillOrientationID		cutFillOrientation;			/**< cut fill orientation */
	Int32						filler_0;

	double						thermalConductivity;
	double						density;
	double						heatCapacity;
	double						embodiedEnergy;
	double						embodiedCarbon;

	bool						showUncutLines;
	bool						doNotParticipateInCollDet;
	bool						filler_1[6];
};


// =============================================================================
// General attribute
//
// =============================================================================

typedef union {
	API_Attr_Head				header;
	API_PenType					pen;
	API_LayerType				layer;
	API_LinetypeType			linetype;
	API_FilltypeType			filltype;
	API_CompWallType			compWall;
	API_MaterialType			material;
	API_LayerCombType			layerComb;
	API_ZoneCatType				zoneCat;
	API_FontType				font;
	API_ProfileAttrType			profile;
	API_PenTableType			penTable;
	API_DimensionAttrType		dimension;
	API_ModelViewOptionsType	modelViewOpt;
	API_MEPSystemType			mepSystem;
	API_OperationProfileType	operationProfile;
	API_BuildingMaterialType	buildingMaterial;
} API_Attribute;


// =============================================================================
// Additional (dynamic) data of attributes
//
// =============================================================================

	struct API_SymbolHatchDef {
		API_Coord			**sfill_HotSpots;
		API_SFill_Line		**sfill_Lines;
		API_SFill_Arc		**sfill_Arcs;
		API_Polygon			**sfill_SolidFills;			/**< All the solid fill symbols */
		API_Coord			**sfill_FillCoords;			/**< All the vertexes of ALL the fill symbols */
		Int32				**sfill_SubPolys;
		API_PolyArc			**sfill_PolyArcs;
	};


struct API_AttributeDef {
	API_DashItems			**ltype_dashItems;
	API_LineItems			**ltype_lineItems;
	API_FillLine			**fill_lineItems;			/**< Vector fill details */
	double					**fill_lineLength;
	API_SymbolHatchDef		sfill_Items;				/**< Symbol fill details */
	API_CWallComponent		**cwall_compItems;
	API_LayerStat			**layer_statItems;
	API_AddParType			**zone_addParItems;
};


struct API_AttributeDefExt {
	API_DashItems											**ltype_dashItems;
	API_LineItems											**ltype_lineItems;
	API_FillLine											**fill_lineItems;			/**< Vector fill details */
	double													**fill_lineLength;
	API_SymbolHatchDef										sfill_Items;				/**< Symbol fill details */
	API_CWallComponent										**cwall_compItems;
	API_CWallLineComponent									**cwall_compLItems;			/**< Skin face lines */
	API_LayerStat											**layer_statItems;
	API_AddParType											**zone_addParItems;
	ProfileVectorImage										*profile_vectorImageItems;
	GS::HashTable<PVI::ProfileParameterId, GS::UniString>	*profile_vectorImageParameterNames;
	API_PenType												**penTable_Items;
	API_DailyProfile										**op_dailyProfiles;
	API_DailyProfileUsage									**op_dailyProfileUsages;
	API_HourlyProfile										**op_hourlyProfiles;

	Int32					filler_1[14];
};


struct API_AttributeFolder {
	API_AttrTypeID				typeID;
	GS::Array<GS::UniString>	path;
	GS::Guid					guid;
};


struct API_AttributeFolderContent {
	GS::Array<API_AttributeFolder>	subFolders;
	GS::Array<GS::Guid>				attributeIds;
};


// =============================================================================
// Attribute changes
//
// =============================================================================

typedef GS::HashTable<API_AttrTypeID, GS::HashTable<API_AttributeIndex, API_AttributeIndex>> API_AttributeReplaceIndexTable;


// ---------------------------------------------------------------------------------------------------------------------

#endif
