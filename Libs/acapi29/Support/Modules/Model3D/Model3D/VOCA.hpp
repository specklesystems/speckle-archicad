// *********************************************************************************************************************
// Description:		Data binding one Model3D Elem to an external elem.
// 					Specially in AC to a GeneralElem: elemGuid is the guid of the elem's Ref
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	FGY
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODEL3D_VOCA_HPP)
#define GS_MODEL3D_VOCA_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"FlagSupport.hpp"
#include	"GSGuid.hpp"
#include	"XMLChannel.hpp"

// from GSUtils
#include	"GSUtilsDefs.h"

// from Model3D
#include	"Model3D/Model3DExport.h"
// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {

// --- Constant definitions	--------------------------------------------------------------------------------------------

/*--------------------------------------------------------------------------*/
/*------------------------------ VOCA ELEM TYPES   -------------------------*/
/*--------------------------------------------------------------------------*/

/* #define	FROM_WALL			1	not used from AC6.00   *//* STR# ELEMTYPE_STRS */
/* #define	FROM_WALL_LINES		2	not used from AC5.00d1 */
#define		FROM_DOOR			3
#define		FROM_WINDOW			4
#define		FROM_OBJECT			5
#define		FROM_CEIL			6
/* #define	FROM_CEIL_LINES		7	not used from AC5.00d1 */
/* #define	FROM_HIP_ROOF		8	not used from AC5.20xx */
#define		FROM_PITCHED_ROOF	9
#define		FROM_LIGHT			10
/* #define	FROM_ELIM_LINES		11	not used */
#define		FROM_COLUMN			12	/*ba30*/
#define		FROM_WALL2			13	/* RJ(W)023 */
#define		FROM_MESH			14
#define		FROM_BEAM			15
#define		FROM_ROOM			16	/*pcs990428*/
#define		FROM_CWALL			17	/*Robur B-082*/
#define		FROM_CWFRAME		18
#define		FROM_CWPANEL		19
#define		FROM_CWJUNCTION		20
#define		FROM_CWACCESSORY	21
#define		FROM_CWSEGMENT		22
#define		FROM_SHELL			23
#define		FROM_SKYLIGHT		24
#define		FROM_FREESHAPE		25
#define		FROM_STAIR			26 // HEADROOM
#define		FROM_RISER			27
#define		FROM_TREAD			28
#define		FROM_STAIRSTRUCTURE	29
#define		FROM_DEBUG_ELEM		30
#define		FROM_RAILING		31
#define		FROM_RAILINGNODE	32
#define		FROM_RAILINGSEGMENT	33
#define		FROM_TOPRAIL		34
#define		FROM_RAILINGPANEL	35
#define		FROM_RAILINGPOST	36
#define		FROM_HANDRAIL		37
#define		FROM_RAIL			38
#define		FROM_RAILINGPATTERN	39
#define		FROM_BALUSTER		40
#define		FROM_BALUSTERSET	41
#define		FROM_INNERPOST		42
#define		FROM_TOPRAILEND		43
#define		FROM_HANDRAILEND	44
#define		FROM_RAILINGFINISHGDLOBJECT	45
#define		FROM_TOPRAILCONNECTION		46
#define		FROM_HANDRAILCONNECTION		47
#define		FROM_RAILCONNECTION			48
#define		FROM_RAILEND				49
#define		FROM_OPENING				50
//#define	FROM_ANALYTICALSUPPORT		51	// not used (AC28)
//#define	FROM_ANALYTICALLINK			52	// not used (AC28)
#define		FROM_OPENINGFRAMEINFILL		53
#define		FROM_OPENINGPATCHINFILL		54
#define		FROM_COLUMNSEGMENT			55
#define		FROM_BEAMSEGMENT			56
#define		FROM_OTHERELEM				60

// --- Type definitions	------------------------------------------------------------------------------------------------

struct MODEL3D_DLL_EXPORT VOCA {
	GS::Guid		elemGuid;		/* Global Unique ID of the 2D element	*/								/* 16 bytes */
private:
	GS::UInt64		dummy1;			/* Not used								*/								/*  8 bytes */
	STATL			dummy2;			/* Not used. previously: status of the 2D part, for future use*/		/*  4 bytes */
private:
	[[maybe_unused]] short dummy5;	/* Not used. previously: layer index	*/								/*  2 bytes */
public:	
	short			etype;			/* 2D element type						*/								/*  2 bytes */
	short			story;			/* story index							*/								/*  2 bytes */
private:
	short			dummy3;			/* Not used								*/								/*  2 bytes */
public:
	STATL			bstatus;		/* status of the 3D part, for future use*/								/*  4 bytes */
									/* bstatus bits are defined in Connect.h [C3_MODEL_...]		*/
									/* used bits: 0x0020 .. 0x8000								*/
									/* NOT USED bits: 0x0001..0x0010			(2012.02.01)	*/
private:
	Int32			dummy4;			/* Not used								*/		/*  4 bytes */
public:

	VOCA	();
	void	SetEmpty ();	// sets only generStamp to current

	void	WriteXML (GS::XMLOChannel& outXML) const;
	void	ReadXML	 (GS::XMLIChannel& inXML);

	bool	operator== (const VOCA& other) const;
	bool	operator!= (const VOCA& other) const { return !operator== (other);  }

	enum ComparisonMethod {
		IncludeElemGuid = 0b0001
	};

	static constexpr ComparisonMethod FullComparison = ComparisonMethod (IncludeElemGuid);

	ENABLE_FLAG_SUPPORT_IN_CLASS (ComparisonMethod);

	bool	Compare		(const VOCA& other, const ComparisonMethod comparisonMethod) const;

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);
};																					/* 44 bytes sum*/

MODEL3D_DLL_EXPORT extern const VOCA NULLVoca;

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

}	// namespace Modeler

#endif
