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
#include "APIdefs_ViewSettings.hpp"

namespace IO { class Location; }
namespace GS { class UniString; }
namespace PVI { typedef GS::Guid ProfileParameterId; }

// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Attribute types and common header
//
// =============================================================================

/**
 * @brief The type of an attribute.
 * @enum API_AttrTypeID
 * @ingroup Navigator
 * @since Archicad 26
 * @remarks This is a general constant which describes the different attributes types, and is used in most attribute-related operations.
 * 			Refer to the @ref API_Attr_Head structure to get more details on it.
 */
typedef enum API_AttrTypeID : int {		/* Attribute types */
	API_ZombieAttrID = 0,

	API_FirstAttributeID,
	API_LayerID = API_FirstAttributeID,
	API_LinetypeID,
	API_FilltypeID,
	API_CompWallID,
	API_MaterialID,
	API_LayerCombID,
	API_ZoneCatID,
	API_ProfileID,
	API_PenTableID,
	API_MEPSystemID,
	API_OperationProfileID,
	API_BuildingMaterialID,
	API_LastAttributeID = API_BuildingMaterialID

} API_AttrTypeID;

/**
 * @brief Contains common information related to all attribute types.
 * @struct API_Attr_Head
 * @ingroup Navigator
 * @remarks This structure contains general information about an attribute. Not all the fields are applicable to all attributes; see the description of the individual attributes.
 * 			As a general rule, before calling any of the Attribute Manager functions, clear the whole structure, fill the necessary fields, then call the function. Clearing all fields in the structure is important for future compatibility; in the next API releases the fillers may have meanings.
 * 			Note that the generalPtr pointer has been removed from the @ref API_Attr_Head structure. You can access long attribute names in C string format (name) or in GS::UniString format (uniStringNamePtr). For deleting more attributes with one attribute function call use @ref ACAPI_Attribute_DeleteMore.
 * 			From Archicad 11 attribute names are stored in GS::UniString format. You can use UniString format for attribute operations to avoid loss of information due to character conversion. To achieve this set the pointer of a GS::UniString variable in the uniStringNamePtr field of the @ref API_Attr_Head structure. Otherwise always set this field to nullptr.
 * 			You can identify attributes by their GUID or name. If you want to refer to an attribute by name, set the guid member to APINULLGuid. Note that Fonts, Pens and Model View Options do not have own GUID, in their case the guid field always contains APINULLGuid. If you set uniStringNamePtr to point to a valid GS::UniString object, the content of the name character buffer is ignored.
 */
struct API_Attr_Head {
	/**
	 * @brief Type of the attribute; this identifies the attribute along with the @c index field. Refer to the
	 * 		  API_AttrTypeID structure to see the possible attribute types.
	 * @var typeID
	 */
	API_AttrTypeID		typeID;

/**
 * @brief The attribute index is the current database index of the given attribute.
 * 		  References to any attribute are done through these indices. It goes from 1 to the maximum available attribute index for each attribute type.
 * 		  For pens the maximum value is always 255.
 * @var index
 */
	API_AttributeIndex	index;

/**
 * @brief The attribute flags. Attribute type specific values are described in the individual attribute sections (where applicable). The following values are common for all types of attributes:
 * 		  | Value | Description |
 * 		  |-------|-------------|
 * 		  |@c APIAttr_IsClientCreated | In teamwork mode, indicates whether an attribute was created by the client and not sent with the changes yet. Such an attribute can still be modified or deleted in teamwork mode (output only) |
 * @var flags
 */
	short				flags;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	short				filler_0[3];

/**
 * @brief The name of the attribute as UTF-8 encoded C string, which appears in the appropriate dialogs.
 * @var name
 */
	char				name[API_AttrNameLen];

/**
 * @brief The globally unique identifier (GUID) of the attribute; can be used for identifying attributes with @ref ACAPI_Attribute_Get and @ref ACAPI_Attribute_Search.
 * @var guid
 */
	API_Guid			guid;

	/**
	 * @brief The last time the attribute was modified as @c GSTime .
	 * @var modiTime
	 */
	UInt64				modiTime;

/**
 * @brief Optional parameter for accessing the name of the attribute in @c UniString (UTF-16 encoded) format.
 * @var uniStringNamePtr
 */
	GS::UniString*		uniStringNamePtr;

};


	#define APIAttr_IsClientCreated		0x1000	/**< General attribute flag; the attribute has been created by the current teamwork user. */
	#define APIAttr_IsFromGDL			0x2000	/**< Attribute is generated from GDL Script of the loaded libraries (output only parameter) */


// =============================================================================

	#define APILay_Hidden		0x0001
	#define APILay_Locked		0x0002
	#define APILay_NotMine		0x0004
	#define APILay_ForceToWire	0x0010
	#define APILay_Xref			0x0020

/**
 * @brief Layer attribute representation.
 * @ingroup Attribute
 * @remark
 * 			Layers work the same way as if you would use Archicad from the
 * 			user interface. This means you cannot create elements on a locked or
 * 			hidden layer. This is especially important if you write an I/O type
 * 			Add-On, as in this case you need to create elements on visible
 * 			layers, and then modify the visibility of the layers.\n \n
 * 			There is no additional data assigned to layer attributes in the
 * @ref API_AttributeDef structure.
 *
 * 		The `flags` field of the header can take the following values:
 * 		|Value|Description|
 * 		|--- |--- |
 * 		|APILay_Hidden|The layer is hidden.|
 * 		|APILay_Locked|The layer is locked.|
 * 		|APILay_NotMine|The layer is not mine.|
 * 		|APILay_ForceToWire|The elements on the layer are shown in wireframe mode in the corresponding Layer
 * 		Combination.| |APILay_Xref|The layer is coming from an XREF-ed (DWG or DXF) drawing. These layers are
 * 		grouped in the Layer Settings dialog.|
 *
 * @ingroup Attribute
 *
 * @sa API_Attr_Head, API_Attribute,\n
 * 	   Attribute Management
 */

struct API_LayerType {
/**
 * @brief Specifies the name, index, and flags of the layer attribute.
 * @var head
 */
	API_Attr_Head	head;

/**
 * @brief The connection class of the layer; elements on layers having the same class will be intersected.
 * @var conClassId
 */
	Int32			conClassId;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32			filler_1;
};

// =============================================================================

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

/**
 * @brief Describes the various item types of a symbol line.
 * @enum API_LtypItemID
 * @ingroup Attribute
 * @remarks These are the item types you can use to describe a symbol line.
 */
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
 * @brief Describes the details of a symbol line.
 * @struct API_LineItems
 * @ingroup Attribute
 * @remarks A detailed example can be found in the APIBases example of the Development Kit.
 */
	struct API_LineItems {

/**
 * @brief The symbol line item type.
 * @var itemType
 */
		API_LtypItemID	itemType;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
		Int32			filler_1;

/**
 * @brief The vertical distance from the origin of the symbol line. Used in separator, centerdot, and centerline item types.
 * @var itemCenterOffs
 */
		double			itemCenterOffs;

/**
 * @brief The length of the item, measured along the length of the item. Used in centerline, rightangle, and parallel item types.
 * @var itemLength
 */
		double			itemLength;

/**
 * @brief The beginning position of an item. Used in dot, rightangle, parallel, line, circle, and arc item types.
 * @var itemBegPos
 */
		API_Coord		itemBegPos;

/**
 * @brief The end position of an item. Used in line item type.
 * @var itemEndPos
 */
		API_Coord		itemEndPos;

/**
 * @brief The radius of an item. Used in circle and arc item types.
 * @var itemRadius
 */
		double			itemRadius;

/**
 * @brief The beginning angle of an item, measured from the vertical (!) axis. Used in arc item type.
 * @var itemBegAngle
 */
		double			itemBegAngle;

/**
 * @brief The end angle of an item, measured from the vertical (!) axis. Used in arc item type.
 * @var itemEndAngle
 */
		double			itemEndAngle;

	};

/**
 * @brief Describes one segment of a dashed line.
 * @struct API_DashItems
 * @ingroup Attribute
 * @remarks The total length of one segment is calculated by adding the two components together.
 * 			A detailed description can be found at @ref API_LinetypeType.
 */
	struct API_DashItems {

/**
 * @brief The length of the dash of a dashed line.
 * @var dash
 */
		double			dash;

/**
 * @brief The length of the gap of a dashed line.
 * @var gap
 */
		double			gap;

	};

/**
 * @brief Line type attribute representation.
 * @struct API_LinetypeType
 * @ingroup Attribute
 * @remarks The flags field of the header can take the following values:
 * 			| Value | Description |
 * 			|-------|-------------|
 * 			| @c APILine_FixScale | The line type parameters are defined with fixed values in millimeters as the line will appear on the printout.|
 * 			| @c APILine_ScaleWithPlan | The line type parameters are defined in meters at a given floor plan scale (`defineScale`); on the printout the lines of this line type will be scaled considering the actual scale. |
 * 			The type of the linetype can take the following values:
 * 			| Value | Description |
 * 			|-------|-------------|
 * 			| @c APILine_SolidLine | Solid line. |
 * 			| @c APILine_DashedLine | Dashed line (contains dashes and gaps between them). ||
 * 			| @c APILine_SymbolLine | Symbol line (can contain different 2D shapes). |
 * 			A solid line is a straight line, without any gaps. You need to fill only the fields of the @c API_LineTypeType structure to create such a line type.
 * 			To create a dashed line, you need to specify the following fields of the structure:
 * 			| Field | Description |
 * 			|-------|-------------|
 * 			| period | The length of the period of the dashed line type (the total length of one segment). |
 * 			| nItems | The number of items in the dashed line type. |
 * 			| ltype_dashItems in @ref API_AttributeDef | This is a handle of @ref API_DashItems, where the dash and gap fields describe the length of the visible and invisible part of one item, respectively.![Dashed line](@ref dashed_line.png) |
 * 			To create a symbol line, you need to specify the following fields of the structure:
 * 			| Field | Description |
 * 			|-------|-------------|
 * 			| period | The length of the period of the symbol line type (the total length of one segment). |
 * 			| nItems | The number of items in the symbol line type. |
 * 			| height | The height of the symbol line type. |
 * 			| ltype_lineItems in @ref API_AttributeDef | This is a handle of @ref API_LineItems, where the dash and gap fields describe the length of the visible and invisible part of one item, respectively. |
 * 			There are additional data assigned to line type attributes in the @ref API_AttributeDef structure; the definition of a line type dash pattern or symbol is passed through the `ltype_dashItems` and `ltype_lineItems` fields, respectively.
 * 			Refer to the @ref API_DashItems and @ref API_LineItems structures to get more details on them.
 *
 * @sa API_Attr_Head, API_Attribute, API_AttributeDef, Attribute Management
 */
struct API_LinetypeType {

/**
 * @brief Contains the name, index, and flags of the attribute.
 * @var head
 */
	API_Attr_Head	head;


/**
 * @brief The original scale the line type is defined with; this value is used only with @c APILine_ScaleWithPlan (otherwise it should be 1.0).
 * @var defineScale
 */
	double			defineScale;

/**
 * @brief Length of a period (except for solid lines).
 * @var period
 */
	double			period;

/**
 * @brief Height of the line type (0.0 for solid and dashed lines).
 * @var height
 */
	double			height;

/**
 * @brief Main selector for type parsing. The possible values are shown in the @c API_LtypTypeID enumeration.
 * @var type
 */
	API_LtypTypeID	type;

/**
 * @brief Number of items in the line type (for dashed/symbol type).
 * @var nItems
 */
	Int32			nItems;

};

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

/**
 * @brief Describes the details of a vectorial fill.
 * @struct API_FillLine
 * @ingroup Attribute
 * @remarks Most of the items here correspond to the various parts of the Fill Types dialog in Archicad.
 */
	struct API_FillLine {

/**
 * @brief The frequency of a fill line item, i.e. the distance between two 'instances' of this item.
 * @var lFreq
 */
		double			lFreq;

/**
 * @brief The angle of a fill line item, measured CCW from the horizontal axis.
 * @var lDir
 */
		double			lDir;

/**
 * @brief The parallel offset of a fill line item, measured from the (rotated) horizontal axis.
 * @var lOffsetLine
 */
		double			lOffsetLine;

/**
 * @brief The offset of a fill line item, given by its coordinates.
 * @var lOffset
 */
		API_Coord		lOffset;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
		short			filler_1;

/**
 * @brief The number of elements used for this fill line item in the @c fill_LineLength array. It should always be even.
 * @var lPartNumb
 */
		short			lPartNumb;

/**
 * @brief The offset (start) if this fill line item in the @c fill_LineLength array. It should always be even.
 * @var lPartOffs
 */
		Int32			lPartOffs;

	};

/**
 * @brief Describes a line item in a symbol fill.
 * @struct API_SFill_Line
 * @ingroup Attribute
 * @remarks None.
 */
	struct API_SFill_Line {

/**
 * @brief The beginning coordinate of the line item in the symbol fill.
 * @var begC
 */
		API_Coord		begC;

/**
 * @brief The end coordinate of the line item in the symbol fill.
 * @var endC
 */
		API_Coord		endC;

	};

	/**
	 * @brief Describes an arc item in a symbol fill.
	 * @struct API_SFill_Arc
	 * @ingroup Attribute
	 * @since Archicad 6.5
	 * @remarks The drawing below illustrates the meaning of the fields.
	 * @image html SymbolArc.png "Symbolic arc" width=50%
	 */
	struct API_SFill_Arc {

/**
 * @brief The beginning coordinate of the arc item in the symbol fill.
 * @var begC
 */
		API_Coord		begC;

/**
 * @brief The origin of the arc item in the symbol fill. The distance of the origin and the beginning coordinate defines the radius of the arc.
 * @var origC
 */
		API_Coord		origC;

/**
 * @brief The angle of the arc item in the symbol fill, measured CCW.
 * @var angle
 */
		double			angle;

	};

/**
 * @brief Fill type attribute representation.
 * @struct API_FilltypeType
 * @ingroup Attribute
 * @remarks The `flags` field of the header can take the following values:
 * 			| Value | Description |
 * 			|-------|-------------|
 * 			| @c APIFill_ScaleWithPlan | The fill type is scale dependent. |
 * 			| @c APIFill_ForWall | This fill can be used for cut fills. |
 * 			| @c APIFill_ForPoly | This fill can be used for drafting fills. |
 * 			| @c APIFill_ForCover | This fill can be used for cover fills. |
 * 			The subType of the fill can take the following values:
 * 			| Value | Description |
 * 			|-------|-------------|
 * 			| @c APIFill_Vector | Vectorial fill. |
 * 			| @c APIFill_Symbol | Symbol fill. |
 * 			| @c APIFill_Solid | Solid fill. Only one solid fill may exist for polygons, and one for walls. |
 * 			| @c APIFill_Empty | Empty fill. Only one empty fill may exist for polygons, and one for walls. |
 * 			| @c APIFill_LinearGradient | Linear gradient fill.![Linear gradient fill](@ref grad_fill_linear.png) |
 * 			| @c APIFill_RadialGradient | Radial gradient fill.![Radial gradient fill](@ref grad_fill_radial.png) |
 * 			| @c APIFill_Image | Image fill. |
 * 			Most of the fields in this structure correspond to the items of the Fill Types dialog in Archicad.
 * 			There is additional data assigned to fill attributes in the @ref API_AttributeDef structure; the
 * 			definition of a fill is passed through the `fill_lineItems` and `fill_lineLength` fields. Refer to the
 * @ref API_FillLine structure to get more details on them. Note that in AC17 the Energy Evaluation property
 * 		parameters (`thermalConductivity`, `density` and `heatCapacity`) have been removed from this structure;
 * 		they are now part of @ref API_BuildingMaterialType.
 */
	struct API_FilltypeType {
		/**
		 * @brief Contains the name and the index of the fill. The @c flags field tells whether the fill is
		 * 		  for drafting, cover, or cut fills, and scales with the plan or scale-independent.
		 * @var head
		 */
		API_Attr_Head head;


		/**
		 * @brief Describes the type of the fill. The possible values are enumerated in @c API_FillSubtype .
		 * @var subType
		 */
		API_FillSubtype subType;

		/**
		 * @brief Indicates a "percent" fill, e.g. 100%, 75%. This is an output-only parameter; detected from
		 * 		  the bitmap pattern.
		 * @var isPercentFill
		 */
		bool isPercentFill;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
		bool filler_1[3];


		/**
		 * @brief Pattern of the fill. It is an eight-character constant; the first character corresponds to
		 * 		  the the first line of the pattern, the second character to the second, etc. Example: the bitPat @c
		 * 		  0x8080808F888888F8 means the following pattern:           0x80 *-------
		 * @var bitPat
		 */
		API_Pattern bitPat;


		/**
		 * @brief The fill's spacing factor in the X direction.
		 * @var hXSpac
		 */
		double hXSpac;

		/**
		 * @brief The fill's spacing factor in the Y direction.
		 * @var hYSpac
		 */
		double hYSpac;

		/**
		 * @brief The angle of the fill.
		 * @var hAngle
		 */
		double hAngle;

		/**
		 * @brief The number of fill line items.
		 * @var linNumb
		 */
		Int32 linNumb;

		/**
		 * @brief The number of hotspot items (symbol fill only).
		 * @var hotNumb
		 */
		Int32 hotNumb;

		/**
		 * @brief The number of arc items (symbol fill only).
		 * @var arcNumb
		 */
		Int32 arcNumb;

		/**
		 * @brief The number of simple fill items (symbol fill only).
		 * @var filNumb
		 */
		Int32 filNumb;


		/**
		 * @brief The symbol fill offset. Corresponds to the X1, Y1 values in the Fill Types dialog.
		 * @var c1
		 */
		API_Coord c1;

		/**
		 * @brief The symbol fill offset. Corresponds to the X2, Y2 values in the Fill Types dialog.
		 * @var c2
		 */
		API_Coord c2;

		/**
		 * @brief The name of the texture file.
		 * @var textureName
		 */
		GS::uchar_t textureName[API_UniLongNameLen];

		/**
		 * @brief Texture status: @c APITxtr_MirrorY | @c APITxtr_MirrorX .
		 * @var textureStatus
		 */
		short textureStatus;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
		short filler_2[3];

		/**
		 * @brief The horizontal (x) size of the texture.
		 * @var textureXSize
		 */
		double textureXSize;

		/**
		 * @brief The vertical (y) size of the texture.
		 * @var textureYSize
		 */
		double textureYSize;

		/**
		 * @brief The rotation angle of the texture in radians.
		 * @var textureRotAng
		 */
		double textureRotAng;

		/**
		 * @brief Percent of the translucent fill.
		 * @var percent
		 */
		double percent;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
		Int32  filler_3[8];

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

/**
 * @brief Describes the simple fills contained in composite structures.
 * @struct API_CWallComponent
 * @ingroup Attribute
 * @remarks  In Archicad 17 composite skins contain a building material index and skin priority is inside the building material.
 */
	struct API_CWallComponent {

/**
 * @brief The index of the building material attribute.
 * @var buildingMaterial
 */
		API_AttributeIndex	buildingMaterial;

/**
 * @brief The index of the frame's pen attribute.
 * @var framePen
 */		short				framePen;

/**
 * @brief The meaning of the flags of the composite wall.
 * 		  |Value|Description|
 * 		  |--- |--- |
 * 		  |APICWallComp_Core|the composite skin is part of the core.|
 * 		  |APICWallComp_Finish|The composite skin is part of the finish.|
 * @var flagBits
 */
		short				flagBits;

/**
 * @brief The absolute thickness of the component in meters.
 * @var fillThick
 */
		double				fillThick;

	};

/**
 * @brief Describes the lines separate the simple fills contained in composite structures.
 * @struct API_CWallLineComponent
 * @ingroup Attribute
 */
	struct API_CWallLineComponent {

/**
 * @brief The index of the skin face's line type attribute (@c 1..n, where @c n is the number of not symbol line type attributes).
 * @var ltypeInd
 */
		API_AttributeIndex	ltypeInd;

/**
 * @brief The index of the skin's face line pen @c [0..255]. @c 0 means the skin face line is hidden.
 * @var linePen
 */
		short				linePen;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
		short				filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
		Int32				filler_2[7];

	};

	/**
	 * @brief Composite fill attribute representation.
	 * @struct API_CompWallType
	 * @ingroup Attribute
	 * @since Archicad 11
	 * @remarks The flags field of the header describes whether this composite fill can be used for walls,
	 * 			slabs, roofs or shells (`APICWall_ForWall`, `APICWall_ForSlab`, `APICWall_ForRoof` and `APICWall_ForShell`
	 * 			respectively). You cannot delete the last composite structure. Additional data are assigned to composite
	 * 			fill attributes in the @ref API_AttributeDefExt structure; the definition of a composite fill and separator line
	 * 			is passed through the `cwall_compItems` and `cwall_compLItems` fields. Refer to the @ref API_CWallComponent and
	 * @ref API_CWallLineComponent structures to get more details. Composite structures with negative fill indices are
	 * 		referenced from @ref API_WallType, @ref API_SlabType, @ref API_RoofType, and @ref API_ShellType.
	 */
	struct API_CompWallType {
		/**
		 * @brief Contains the name and the index of the attribute. The @c head.flags can be @c APICWall_xxx .
		 * @var head
		 */
		API_Attr_Head head;


		/**
		 * @brief Specifies the thickness of the whole wall.
		 * @var totalThick
		 */
		double totalThick;

		/**
		 * @brief Contains the number of components (simple fills) for the composite. The number of separator
		 * 		  lines is @c nComps+1 because of two contour lines.
		 * @var nComps
		 */
		short nComps;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
		short filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
		Int32 filler_2;
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

/**
 * @brief Texture reference.
 * @struct API_Texture
 * @ingroup  ModelAccess
 */
	struct API_Texture {

/**
 * @brief Texture status
 * @var status
 */
		short			status;

/**
 * @brief Picture is missing (output only)
 * @var missingPict
 */
		bool			missingPict;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
		bool			filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
		Int32			filler_2;

/**
 * @brief X size of the picture in model space.
 * @var xSize
 */
		double			xSize;

/**
 * @brief Y size of the picture in model space.
 * @var ySize
 */
		double			ySize;

/**
 * @brief Rotation angle in radians.
 * @var rotAng
 */
		double			rotAng;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
		Int32			filler_3;

/**
 * @brief for internal use
 * @var irtxt
 */
		Int32			irtxt;

/**
 * @brief The name of the texture file as UTF-8 encoded C string.
 * @var texName
 */
		GS::uchar_t		texName [API_UniLongNameLen];

/**
 * @brief Texture file location in the file system.
 * @var fileLoc
 */
		IO::Location	*fileLoc;

/**
 * @brief [in] Indicates that the extension was not appended to the texture name.
 * @var withoutExtension
 */
		bool			withoutExtension;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
		bool			filler_4;

/**
 * @brief Reserved for later use.
 * @var filler_5
 */
		short			filler_5;
	};

/**
 * @brief Enumeration of material types.
 * @enum API_MaterTypeID
 * @ingroup  ModelAccess
 * @remarks This type identifier can be used as mtype in @ref API_MaterialType.
 */
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

/**
 * @brief Description of a surface material attribute.
 * @struct API_MaterialType
 * @ingroup  ModelAccess
 * @remarks This attribute type is also used by the 3D components. The material of a 3D polygon can be accessed through the @ref API_UmatType structure.
 * 			There is no additional data assigned to material attributes in the @ref API_AttributeDef structure.
 * 			Pay attention to the texture member if its fileLoc pointer is dynamically allocadted.
 */
struct API_MaterialType {

/**
 * @brief Contains the header information, including type and database index.
 * @var head
 */
	API_Attr_Head	head;


/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32			filler_1;

/**
 * @brief The type of the material. Usable values are enumerated in @c API_MaterTypeID.
 * @var mtype
 */
	API_MaterTypeID	mtype;

/**
 * @brief The reflection of ambient light. @c [0..100]
 * @var ambientPc
 */
	short			ambientPc;

/**
 * @brief The reflection of diffuse light. @c [0..100]
 * @var diffusePc
 */
	short			diffusePc;

/**
 * @brief The reflection of specular light. @c [0..100]
 * @var specularPc
 */
	short			specularPc;

/**
 * @brief Transparency factor. @c [0..100]
 * @var transpPc
 */
	short			transpPc;

/**
 * @brief The shininess factor multiplied by 100. @c [0..10000]
 * @var shine
 */
	short			shine;

/**
 * @brief The transparency attenuation multiplied by 100. @c [0..400]
 * @var transpAtt
 */
	short			transpAtt;

/**
 * @brief The emission attenuation factor multiplied by 100. @c [0..65535]
 * @var emissionAtt
 */
	short			emissionAtt;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short			filler_2;

/**
 * @brief The color of the surface.
 * @var surfaceRGB
 */
	API_RGBColor	surfaceRGB;

/**
 * @brief The specular color.
 * @var specularRGB
 */
	API_RGBColor	specularRGB;

/**
 * @brief The emission color.
 * @var emissionRGB
 */
	API_RGBColor	emissionRGB;


/**
 * @brief Internal use
 * @var ifill
 */
	API_AttributeIndex	ifill;

/**
 * @brief Color number of defined 3D hatch (@c <=0 means: use BODY color)
 * @var fillCol
 */
	short				fillCol;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	short				filler_3;


/**
 * @brief The texture of the material.
 * @var texture
 */
	API_Texture		texture;

};


// =============================================================================

/**
 * @brief Describes one layer's characteristics in a layer combination.
 * @struct API_LayerStat
 * @ingroup Attribute
 * @remarks The layer combination attribute contains all the visibility and locking information for each
 * 			layer. This structure describes the characteristics of one layer in the layer combination.
 */
struct API_LayerStat {

	/**
	 * @brief Status of the layer (see @c APILay_...).
	 * @var lFlags
	 */
	short			   lFlags;

	/**
	 * @brief Reserved for later use.
	 * @var filler_1
	 */
	short			   filler_1;

	/**
	 * @brief Connection class of the layer; elements on layers having the same class will be intersected.
	 * @var conClassId
	 */
	Int32			   conClassId;
};


/**
 * @brief Layer combination attribute representation.
 * @struct API_LayerCombType
 * @ingroup Attribute
 * @remarks The layer combination attribute contains all the visibility and locking information for each
 * 			layer. This also means that the number of layers (the `lNumb` field) has the same value in all layer
 * 			combinations. When you create a new layer, it will appear in all layer combinations as unlocked and visible.
 * 			Additional data are assigned to the layer combination attributes in the @ref API_AttributeDef structure; the
 * 			status information to each layer is passed through the layer_statItems field. Refer to the @ref API_LayerStat
 * 			structure to get more details on it.
 */
struct API_LayerCombType {

/**
 * @brief Contains the name and the index of the layer combination.
 * @var head
 */
	API_Attr_Head	head;

/**
 * @brief The number of layers in this combination.
 * @var lNumb
 */
	Int32			lNumb;

/**
 * @brief The layers are currently set as in this layer combination.
 * @var inEffect
 */
	bool			inEffect;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool			filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short			filler_2;

};


// =============================================================================
// Zone category
//
// =============================================================================

/**
 * @brief Zone category attribute representation.
 * @struct API_ZoneCatType
 * @ingroup Attribute
 * @remarks This attribute exists in Archicad only.
 * 			One zone category always exists, i.e. you cannot delete the last zone category attribute.
 * 			There are additional data assigned to zone category attributes in the @ref API_AttributeDef structure;
 * 			the current values of the parameters are passed through the zone_addParItems field. Refer to the @ref API_AddParType structure to get more details on it.
 */
struct API_ZoneCatType {

/**
 * @brief Contains the name and the index of the zone category attribute.
 * @var head
 */
	API_Attr_Head	head;

/**
 * @brief Contains the code for the zone category attribute.
 * @var catCode
 */
	GS::uchar_t		catCode[API_UniLongNameLen];

/**
 * @brief Contains the name of the zone stamp library part for the zone category attribute.
 * @var stampName
 */
	GS::uchar_t		stampName[API_UniLongNameLen];

/**
 * @brief The main part of the unique identifier of the zone stamp library part.
 * @var stampMainGuid
 */
	API_Guid		stampMainGuid;

/**
 * @brief The revision part of the unique identifier of the zone stamp library part.
 * @var stampRevGuid
 */
	API_Guid		stampRevGuid;

/**
 * @brief The RGB components of the zone color.
 * @var rgb
 */
	API_RGBColor	rgb;

};


// =============================================================================
// Profile
//
// =============================================================================

	#define APISkin_HatchAngle	0x0001
	#define APISkin_Core		0x0002
	#define APISkin_Finish		0x0020
	#define APISkin_HatchFit	0x0040

/**
 * @brief Attribute representing the custom profiles for walls, beams, and columns.
 * @struct API_ProfileAttrType
 * @ingroup Attribute
 * @remarks Additional data for this attribute is contained in the `profile_vectorImageItems` field of the
 * @ref API_AttributeDefExt structure. This extended data holds simple 2D elements: hotspots, lines,
 * 		arcs, hatches, splines, texts, and images in a serialized form.
 * 		A simple example for creating and parsing a profile attribute can be found in the Attribute_Test example.
 * 		The `flags` in ProfileItem of ProfileFillData (the profile description) may have the following values:
 * 		|Value|Description|
 * 		|--- |--- |
 * 		|APISkin_HatchAngle|The fill direction is determined by the project origin (if not set), or the element's origin (if set).|
 * 		|APISkin_Core|The skin's fill is part of the core.|
 * 		|APISkin_Finish|The skin's fill is part of the finish.|
 * 		|APISkin_HatchFit|The skin's fill is distorted to fit the skin's polygon.|
 */
struct  API_ProfileAttrType {

/**
 * @brief The attribute header.
 * @var head
 */
	API_Attr_Head		head;

/**
 * @brief Profile available for walls.
 * @var wallType
 */
	bool				wallType;

/**
 * @brief Profile available for beams.
 * @var beamType
 */
	bool				beamType;

/**
 * @brief Profile available for columns.
 * @var coluType
 */
	bool				coluType;

/**
 * @brief Profile available for handrails.
 * @var handrailType
 */
	bool				handrailType;

/**
 * @brief Profile available for other GDL based objects.
 * @var otherGDLObjectType
 */
	bool				otherGDLObjectType;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool				filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool				filler_2;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool				filler_3;


/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32				filler_4[7];
};


// =============================================================================

/**
 * @brief Pen table attribute.
 * @struct API_PenTableType
 * @ingroup Attribute
 * @remarks Pen tables are new in Archicad 10, introduced because of the layouting functionality.
 * 			Each pen table contains 255 pens. Separate pen tables can be active for the layouting and for the model windows.
 * 			The pens of the pentable are passed in the penTable_Items field of the @ref API_AttributeDefExt structure.
 */
struct API_PenTableType {

/**
 * @brief Contains the name, guid and the index of the attribute.
 * @var head
 */
	API_Attr_Head		head;

/**
 * @brief This is the active pen table for the model space.
 * @var inEffectForModel
 */
	bool				inEffectForModel;

/**
 * @brief This is the active pen table for the layout.
 * @var inEffectForLayout
 */
	bool				inEffectForLayout;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short				filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32				filler_2[4];

};

// =============================================================================
// MEPSystem
//
// =============================================================================

/**
 * @brief MEP System attribute representation.
 * @struct API_MEPSystemType
 * @ingroup Attribute
 * @remarks One MEP System always exists, i.e. you cannot delete the last MEP System attribute.
 * 			There is no additional data assigned to MEP System attributes in the @ref API_AttributeDef structure.
 */
struct API_MEPSystemType {

/**
 * @brief Specifies the index and the name of the MEP System.
 * @var head
 */
	API_Attr_Head		head;


/**
 * @brief MEP System available for ductwork.
 * @var isForDuctwork
 */
	bool				isForDuctwork;

/**
 * @brief MEP System available for pipework.
 * @var isForPipework
 */
	bool				isForPipework;

/**
 * @brief MEP System available for cabling.
 * @var isForCabling
 */
	bool				isForCabling;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool				filler_1;

/**
 * @brief The index of the contour pen @c [1..255].
 * @var contourPen
 */
	short				contourPen;

/**
 * @brief The index of the fill (foreground) pen @c [1..255].
 * @var fillPen
 */
	short				fillPen;

/**
 * @brief Index of the background pen @c [0..255]. The special @c 0 value means transparent background.
 * @var fillBgPen
 */
	short				fillBgPen;

/**
 * @brief The index of the center line pen @c [1..255].
 * @var centerLinePen
 */
	short				centerLinePen;

/**
 * @brief The index of the fill pattern attribute (@c 1..n, where @c n is the number of simple fill attributes).
 * @var fillInd
 */
	API_AttributeIndex	fillInd;

/**
 * @brief The index of the center line type attribute (@c 1..n, where @c n is the number of simple line attributes).
 * @var centerLTypeInd
 */
	API_AttributeIndex	centerLTypeInd;

/**
 * @brief The index of the body material attribute (@c 1..n, where @c n is the number of simple material attributes).
 * @var materialInd
 */
	API_AttributeIndex	materialInd;

/**
 * @brief The index of the insulation material attribute (@c 1..n, where @c n is the number of simple material attributes).
 * @var insulationMatInd
 */
	API_AttributeIndex	insulationMatInd;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32				filler_2;

};


// =============================================================================

/**
 * @brief Describes coverage of an hour of an Operation Profile.
 * @struct API_HourlyProfile
 * @ingroup Attribute
 */
struct API_HourlyProfile {
/**
 * @brief The name of the hourly profile.
 * @var name
 */
	GS::uchar_t		name [API_UniLongNameLen];

/**
 * @brief Hourly desired minimum temperature.
 * @var minTemp
 */
	double			minTemp;

/**
 * @brief Minimum temperature define.
 * @var minTempDef
 */
	bool			minTempDef;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool			filler_1[7];

/**
 * @brief Hourly desired maximum temperature.
 * @var maxTemp
 */
	double			maxTemp;

/**
 * @brief Maximum temperature define.
 * @var maxTempDef
 */
	bool			maxTempDef;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool			filler_2[7];

/**
 * @brief Hourly occupancy count.
 * @var occupancyCount
 */
	double			occupancyCount;

/**
 * @brief Hourly light gain.
 * @var lightGain
 */
	double			lightGain;

/**
 * @brief Hourly equipment gain.
 * @var equipmentGain
 */
	double			equipmentGain;

};


// =============================================================================

/**
 * @brief Describes a daily profile contained in Operation Profile.
 * @struct API_DailyProfile
 * @ingroup Attribute
 */
struct API_DailyProfile {
/**
 * @brief The name of the daily profile.
 * @var name
 */
	GS::uchar_t		name [API_UniLongNameLen];

/**
 * @brief Hourly desired minimum temperature in a day.
 * @var minTemp
 */
	double			minTemp[24];

/**
 * @brief Minimum temperature defines.
 * @var minTempDefs
 */
	bool			minTempDefs[24];

/**
 * @brief Hourly desired maximum temperature in a day.
 * @var maxTemp
 */
	double			maxTemp[24];

/**
 * @brief Maximum temperature defines.
 * @var maxTempDefs
 */
	bool			maxTempDefs[24];

/**
 * @brief Hourly occupancy count in a day.
 * @var occupancyCount
 */
	double			occupancyCount[24];

/**
 * @brief Hourly light gain in a day.
 * @var lightGain
 */
	double			lightGain[24];

/**
 * @brief Hourly equipment gain in a day.
 * @var equipmentGain
 */
	double			equipmentGain[24];

};


// =============================================================================

/**
 * @brief Describes a daily profile usage contained in Operation Profile.
 * @struct API_DailyProfileUsage
 * @ingroup Attribute
 */
struct API_DailyProfileUsage {

/**
 * @brief Start month of the usage (profiled period).
 * @var startMonth
 */
	short		startMonth;

/**
 * @brief Start day of the usage (profiled period).
 * @var startDay
 */
	short		startDay;

/**
 * @brief End month of the usage (profiled period).
 * @var endMonth
 */
	short		endMonth;

/**
 * @brief End day of the usage (profiled period).
 * @var endDay
 */
	short		endDay;

/**
 * @brief Weekly recurrence of the usage. The @c [1,2,4,8,10,20,40] values correspond to Mon, Tue, Wed, Thu, Fri, Sat, Sun.
 * 		  All of these values can be combined so the max. value is 127.
 * @var recurrence
 */
	short		recurrence;

/**
 * @brief Index of the Daily Profile.
 * @var dailyProfileIndex
 */
	short		dailyProfileIndex;

};


// =============================================================================

/**
 * @brief Occupancy type of the Operation Profile.
 * @enum API_OccupancyTypeID
 * @ingroup Attribute
 */
typedef enum {
	APIOccupancyType_Residential = 1,			// Residential occupancy type
	APIOccupancyType_NonResidential	= 2			// Non residential occupancy type

} API_OccupancyTypeID;

/**
 * @brief An Energy Evaluation operation profile.
 * @struct API_OperationProfileType
 * @ingroup Attribute
 * @remarks There are additional data assigned to operation profile attributes in the @ref API_AttributeDefExt structure; the definition of an operation profile are passed through the op_dailyProfiles and op_dailyProfileUsages fields. Refer to the @ref API_DailyProfile and @ref API_DailyProfileUsage structures to get more details on it.
 * 			The coverage of an entire year (8760 hours) can be queried by the op_hourlyProfiles structure. Refer to the @ref API_HourlyProfile structure to get more details on it.
 */
struct API_OperationProfileType {

/**
 * @brief Contains the name and the index of the attribute.
 * @var head
 */
	API_Attr_Head		head;


/**
 * @brief Specifies the total number of Daily Profiles.
 * @var nDailyProf
 */
	short				nDailyProf;

/**
 * @brief Specifies the total number of Daily Profile Usages.
 * @var nDailyProfUsage
 */
	short				nDailyProfUsage;

/**
 * @brief Specifies the occupancy type.
 * @var occupancyType
 */
	API_OccupancyTypeID occupancyType;

/**
 * @brief Service hot water load per capita.
 * @var hotWaterLoad
 */
	double				hotWaterLoad;

/**
 * @brief Human heat gain per capita.
 * @var humanHeatGain
 */
	double				humanHeatGain;

/**
 * @brief Humidity load.
 * @var humidity
 */
	double				humidity;

};


// =============================================================================

/**
 * @brief Determines the orientation of the fill pattern.
 * @enum API_FillOrientationID
 * @ingroup Attribute
 */
typedef enum {
	APIFillOrientation_ProjectOrigin	= 0,
	APIFillOrientation_ElementOrigin	= 1,
	APIFillOrientation_FitToSkin		= 2

} API_FillOrientationID;

/**
 * @brief Building Material type attribute representation.
 * @struct API_BuildingMaterialType
 * @ingroup Attribute
 * @remarks Most of the fields in this structure correspond to the items of the Building Material dialog in Archicad.
 * 			Note that in AC17 the Energy Evaluation property parameters (thermalConductivity, density and heatCapacity) have
 * 			been removed from the @ref API_FilltypeType, they are now part of this structure.
 */
struct API_BuildingMaterialType {

/**
 * @brief Contains the name and the index of the building material.
 * @var head
 */
	API_Attr_Head				head;


/**
 * @brief The id of the building material.
 * @var id
 */
	GS::UniString*				id;

/**
 * @brief The manufacturer of the building material.
 * @var manufacturer
 */
	GS::UniString*				manufacturer;

/**
 * @brief The description of the building material.
 * @var description
 */
	GS::UniString*				description;


/**
 * @brief The connection priority of the building material. Used when multiple elements intersect, the higher priority element will be shown at the intersection.
 * @var connPriority
 */
	Int32						connPriority;

/**
 * @brief Index of the building material's cut fill.
 * @var cutFill
 */
	API_AttributeIndex			cutFill;

/**
 * @brief Index of the building material's cut fill foreground pen.
 * @var cutFillPen
 */
	short						cutFillPen;

/**
 * @brief Index of the building material's cut fill background pen.
 * @var cutFillBackgroundPen
 */
	short						cutFillBackgroundPen;

/**
 * @brief Index of the building material's cut material.
 * @var cutMaterial
 */
	API_AttributeIndex			cutMaterial;

/**
 * @brief Orientation of the building material's cut fill.
 * @var cutFillOrientation
 */
	API_FillOrientationID		cutFillOrientation;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	Int32						filler_0;


/**
 * @brief Thermal Conductivity of the building material.
 * @var thermalConductivity
 */
	double						thermalConductivity;

/**
 * @brief Density of the building material.
 * @var density
 */
	double						density;

/**
 * @brief Heat capacity of the building material.
 * @var heatCapacity
 */
	double						heatCapacity;

/**
 * @brief Embodied energy in the building material.
 * @var embodiedEnergy
 */
	double						embodiedEnergy;

/**
 * @brief Embodied carbon in the building material.
 * @var embodiedCarbon
 */
	double						embodiedCarbon;


/**
 * @brief Show Contours in Model Views.
 * @var showUncutLines
 */
	bool						showUncutLines;

/**
 * @brief Specifies if the building material participates in collision detection.
 * @var doNotParticipateInCollDet
 */
	bool						doNotParticipateInCollDet;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool						filler_1[6];

};


// =============================================================================

/**
 * @brief Describes the different attributes.
 * @union API_Attribute
 * @ingroup Attribute
 * @remarks Database items named attributes are global collections of layers, pen colors, surface materials, fill patterns, etc. that are available to all eligible tools. They are referenced by indices and changes to an attribute effects every element that uses that attribute. Attributes can be accessed and edited through the Options menu.
 * 			API functions operating on the attribute set begin with the @c ACAPI_Attribute_ prefix, refer to the Attribute Manager for more details.
 * 			Many attribute related functions use the @ref API_Attribute structure on the parameter list. As a general rule, you have to fill the required fields in the union, then Archicad parses the request based on the values, and passes the return parameters in the same parameter. This is why most of the functions do not have the const directive in the prototypes.
 */
union API_Attribute {

/**
 * @brief A common header for all the attribute types. It contains information which applies to all the attribute types.
 * @var header
 */
	API_Attr_Head				header;

/**
 * @brief A layer attribute.
 * @var layer
 */
	API_LayerType				layer;

/**
 * @brief A line type attribute.
 * @var linetype
 */
	API_LinetypeType			linetype;

/**
 * @brief A fill type attribute.
 * @var filltype
 */
	API_FilltypeType			filltype;

/**
 * @brief A composite wall attribute.
 * @var compWall
 */
	API_CompWallType			compWall;

/**
 * @brief A material attribute.
 * @var material
 */
	API_MaterialType			material;

/**
 * @brief A layer combination attribute.
 * @var layerComb
 */
	API_LayerCombType			layerComb;

/**
 * @brief A zone category attribute.
 * @var zoneCat
 */
	API_ZoneCatType				zoneCat;

/**
 * @brief A custom profile attribute for walls, beams, and columns.
 * @var profile
 */
	API_ProfileAttrType			profile;

/**
 * @brief A named pen table attribute..
 * @var penTable
 */
	API_PenTableType			penTable;

/**
 * @brief A MEP System attribute.
 * @var mepSystem
 */
	API_MEPSystemType			mepSystem;

/**
 * @brief An Energy Evaluation operation profile.
 * @var operationProfile
 */
	API_OperationProfileType	operationProfile;

/**
 * @brief A building material attribute.
 * @var buildingMaterial
 */
	API_BuildingMaterialType	buildingMaterial;

};


// =============================================================================
// Additional (dynamic) data of attributes
//
// =============================================================================

/**
 * @brief Describes the details of a symbol fill.
 * @struct API_SymbolHatchDef
 * @ingroup Attribute
 * @remarks None.
 */
	struct API_SymbolHatchDef {

/**
 * @brief The coordinates of the hotspots in the symbol fill. The number of hotspots is given in the @c hotNumb field of the @ref API_FilltypeType structure.
 * @var sfill_HotSpots
 */
		API_Coord			**sfill_HotSpots;

/**
 * @brief The description of the line items in the symbol fill. The number of line items is given in the @c linNumb field of the @ref API_FilltypeType structure.
 * @var sfill_Lines
 */
		API_SFill_Line		**sfill_Lines;

/**
 * @brief The description of the arc items in the symbol fill. The number of arc items is given in the @c arcNumb field of the @ref API_FilltypeType structure.
 * @var sfill_Arcs
 */
		API_SFill_Arc		**sfill_Arcs;

/**
 * @brief The description of all (!) the solid fill items in the symbol fill. The number of solid fill items is given in the @c filNumb field of the @ref API_FilltypeType structure. The polygons and all the related information is stored sequentially. The following three fields complete the description of the fill polygons.
 * @var sfill_SolidFills
 */
		API_Polygon			**sfill_SolidFills;

/**
 * @brief All the vertices of all the solid fill items in the symbol fill.
 * @var sfill_FillCoords
 */
		API_Coord			**sfill_FillCoords;

/**
 * @brief All the subpolygons of all the solid fill items in the symbol fill.
 * @var sfill_SubPolys
 */
		Int32				**sfill_SubPolys;

/**
 * @brief All the polygon arc segments of all the solid fill items in the symbol fill.
 * @var sfill_PolyArcs
 */
		API_PolyArc			**sfill_PolyArcs;

	};


/**
 * @brief Describes the extended information for different attributes.
 * @struct API_AttributeDef
 * @ingroup Attribute
 * @remarks This structure contains the extended information for certain attribute types.
 * 			Use the Attribute Manager functions to operate on this data.
 * 			See also the extension of this structure: @ref API_AttributeDefExt.
 * 			Use the Attribute Manager functions to operate on this data.
 */
struct API_AttributeDef {

/**
 * @brief Contains the data describing dashed lines.
 * @var ltype_dashItems
 */
	API_DashItems			**ltype_dashItems;

/**
 * @brief Contains the data describing symbol lines.
 * @var ltype_lineItems
 */
	API_LineItems			**ltype_lineItems;

/**
 * @brief Contains vectorial fill details.
 * @var fill_lineItems
 */
	API_FillLine			**fill_lineItems;

/**
 * @brief Contains the lengths of individual parts for vectorial fills. It contains the description of each fill line item in dash-gap length pairs.
 * @var fill_lineLength
 */
	double					**fill_lineLength;

/**
 * @brief Contains symbol fill details.
 * @var sfill_Items
 */
	API_SymbolHatchDef		sfill_Items;

/**
 * @brief Describes the simple fills contained in composite structures.
 * @var cwall_compItems
 */
	API_CWallComponent		**cwall_compItems;

/**
 * @brief Describes the visibility and openness of every layer in a layer set.
 * @var layer_statItems
 */
	GS::HashTable<API_AttributeIndex, API_LayerStat>	*layer_statItems;

/**
 * @brief Contains the library part parameters of a zone category.
 * @var zone_addParItems
 */
	API_AddParType			**zone_addParItems;

};


/**
 * @brief Describes the extended information for different attributes.
 * @struct API_AttributeDefExt
 * @ingroup Attribute
 * @remarks This structure contains the extended information for certain attribute types.
 * 			Use the Attribute Manager functions to operate on this data.
 * 			See also the extension of this structure: @ref API_AttributeDefExt.
 * 			Use the Attribute Manager functions to operate on this data.
 */
struct API_AttributeDefExt {

/**
 * @brief Contains the data describing dashed lines.
 * @var ltype_dashItems
 */
	API_DashItems											**ltype_dashItems;

/**
 * @brief Contains the data describing symbol lines.
 * @var ltype_lineItems
 */
	API_LineItems											**ltype_lineItems;

/**
 * @brief Contains vectorial fill details.
 * @var fill_lineItems
 */
	API_FillLine											**fill_lineItems;

/**
 * @brief Contains the lengths of individual parts for vectorial fills. It contains the description of each fill line item in dash-gap length pairs.
 * @var fill_lineLength
 */
	double												**fill_lineLength;

/**
 * @brief Contains symbol fill details.
 * @var sfill_Items
 */
	API_SymbolHatchDef										sfill_Items;

/**
 * @brief Describes the simple fills contained in composite structures.
 * @var cwall_compItems
 */
	API_CWallComponent										**cwall_compItems;

/**
 * @brief Describes the lines separate the simple fills contained in composite structures.
 * @var cwall_compLItems
 */
	API_CWallLineComponent									**cwall_compLItems;

/**
 * @brief Describes the visibility and openness of every layer in a layer set.
 * @var layer_statItems
 */
	GS::HashTable<API_AttributeIndex, API_LayerStat>				*layer_statItems;

/**
 * @brief Contains the library part parameters of a zone category.
 * @var zone_addParItems
 */
	API_AddParType											**zone_addParItems;

/**
 * @brief Elements of a custom profile for walls, beams, and columns. The handle contains a serialized @c HGX::VectorImage.
 * @var profile_vectorImageItems
 */
	ProfileVectorImage										*profile_vectorImageItems;

/**
 * @brief Parameter names of the new profiles.
 * @var profile_vectorImageParameterNames
 */
	GS::HashTable<PVI::ProfileParameterId, GS::UniString>	*profile_vectorImageParameterNames;

/**
 * @brief Contains the 255 pens of a named pen table.
 * @var penTable_Items
 */
	GS::Array<API_Pen>										*penTable_Items;

/**
 * @brief The daily profiles for an operation profile (Energy Evaluation)
 * @var op_dailyProfiles
 */
	API_DailyProfile										**op_dailyProfiles;

/**
 * @brief The daily profile usages for an operation profile (Energy Evaluation)
 * @var op_dailyProfileUsages
 */
	API_DailyProfileUsage									**op_dailyProfileUsages;

/**
 * @brief The hourly profile usages for an operation profile (Energy Evaluation)
 * @var op_hourlyProfiles
 */
	API_HourlyProfile										**op_hourlyProfiles;


/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32					filler_1[14];

};


/**
 * @brief An attribute folder.
 * @struct API_AttributeFolder
 * @ingroup Attribute
 * @since Archicad 26
 * @remarks The name of the folder is not used.
 */
struct API_AttributeFolder {

/**
 * @brief Type of the attribute folder; this identifies the folder along with the @c path or @c guid field.
 * @var typeID
 */
	API_AttrTypeID				typeID;

/**
 * @brief Path of the folder, list of the names of the parent folders and the current in order.
 * @var path
 */
	GS::Array<GS::UniString>	path;

/**
 * @brief The globally unique identifier (GUID) of the folder; can be used for identifying the folder with @ref ACAPI_Attribute_GetFolder.
 * @var guid
 */
	GS::Guid					guid;

};


/**
 * @brief Content of an attribute folder. Contains direct subfolders and attributes.
 * @struct API_AttributeFolderContent
 * @ingroup Attribute
 * @since Archicad 26
 * @remarks The name of the folder is not used.
 */
struct API_AttributeFolderContent {

/**
 * @brief Subfolders in this folder.
 * @var subFolders
 */
	GS::Array<API_AttributeFolder>	subFolders;

/**
 * @brief Attributes in this folder.
 * @var attributeIds
 */
	GS::Array<GS::Guid>				attributeIds;

};


/**
 * @brief Contains the deleted and replaced attribute indices grouped by attribute type.
 * @typedef API_AttributeReplaceIndexTable
 * @ingroup Attribute
 * @since Archicad 25
 */
typedef GS::HashTable<API_AttrTypeID, GS::HashTable<API_AttributeIndex, API_AttributeIndex>> API_AttributeReplaceIndexTable;


// ---------------------------------------------------------------------------------------------------------------------

#endif
