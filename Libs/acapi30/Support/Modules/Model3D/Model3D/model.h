/****************************************************************************/
/*																			*/
/*						GLOBAL CONSTANTS, TYPES AND MACROS					*/
/*								FOR 3D DATA STRUCTURE						*/
/*																			*/
/****************************************************************************/

#ifndef	_model_H_
#define	_model_H_

#pragma once

// from GSUtils
#include	"GSUtilsDefs.h"

// from Geometry
#include	"TRANMAT.h"
#include	"TM.h"

// from GDL
#include	"BodyTypes.hpp"

// from Brep
#include	"MeshBrep.hpp"

/*================================	CONSTANTS	============================*/

#define	MAXCUTP					10


/*--------------------------------------------------------------------------*/
/* ---------------------------- STATUS BITS FOR MODEL --------------------- */
/*--------------------------------------------------------------------------*/

/*
**	WARNING !!!
**		If you make any changes in status bits contact to
**		:E:AC3Xinc.h
**		vv94.02.03
*/

/*	For CUT_RECORDs deleted (or out of perspective area)						*/
/*	DEPRECATED, kept for asserts only											*/
#define	DELBIT			0x00008000		/*	0b00000000000000001000000000000000	*/

/*	For -----, BRETs		error during generation								*/
#define	GENERRBIT		0x00008000		/*	0b00000000000000000100000000000000	*/

/*	For -----,-----,PGONs,UPGONs	shadow body, polygon						*/
#define	SHADOW_MARK_BIT	0x00004000		/*	0b00000000000000000100000000000000	*/

/*	For UBODYs, RTXTs, SIGHT													*/
#define	INVALIDBIT		0x00002000		/*	0b00000000000000000010000000000000	*/

/*	For PGONs,UPGONs,EDGEs	parallel to light direction in SHADOW BODY			*/
#define	SHADOW_EDGE_BIT	0x00002000		/*	0b00000000000000000010000000000000	*/
/*	For PGONs,UPGONs,EDGEs	polygon is the same as its shadow in MODEL BODY	*/	/*vv17*/
#define	INSHADOWBIT		0x00002000		/*	0b00000000000000000010000000000000	*/


/*	For -----, -----		not a visible body (deleted or shadow body)			*/
//#define	NOTVISBODYBITS	0x0000C000		/*	0b00000000000000001100000000000000	*/
/* DELBIT | SHADOW_MARK_BIT	= NOTVISBODYBITS	*/

/*	For PGONs,UPGONs,EDGEs	on a cut plane/shape								*/
#define	ON_CUT_BIT				0x00001000   /*	0b00000000000000000001000000000000	*/
#define	ON_MODEL_CUT_BIT		0x00020000   /*	0b00000000000000010000000000000000	*/
#define ON_SECT_CUT_SPEC_BIT	0x00400000   /* 0b00000000001000000000000000000000  */

/*	For -----, -----		marking simplified storage of topology				*/
//#define	TOPOBIT			0x00002000		/*	0b00000000000000000010000000000000	*/
//#define	FTOPOBIT		0x00001000		/*	0b00000000000000000001000000000000	*/


/*	For TEDGEs				marking bits for rendering							*/
#define	REBIT1			0x00004000		/*	0b00000000000000000100000000000000	*/
#define	REBIT2			0x00002000		/*	0b00000000000000000010000000000000	*/
/* REBIT1 | REBIT2		= REBIT12	*/
#define	REBIT12			0x00006000		/*	0b00000000000000001100000000000000	*/


/*	For PGONs,UPGONs,CUT_RECORDs	(for wall)									*/
#define	CUT_EDGE1BIT	0x00000400		/*	0b00000000000000000000010000000000	*/
#define	CUT_EDGE2BIT	0x00000800		/*	0b00000000000000000000100000000000	*/
#define	CUT_EDGEBITS	0x00000C00		/*	0b00000000000000000000110000000000	*/

/* In cutin3d.h for CUT_RECORDs	(for wall)										*/
/*#define	CUT_USEOWNBIT	0x00000010					0b0000000000010000		*/
/*#define	CUT_U_SHAPEBIT	0x00000020					0b0000000000100000		*/
/*#define	CUT_L_SHAPEBIT	0x00000040					0b0000000001000000		*/


/*	For BODYs, BRETs		more than one raster texture used in body			*/
//#define	MULRTXTBIT		0x00000100		/*	0b00000000000000000000000100000000	*/
/*	For BODYs, BRETs		more than one color used in body					*/
//#define	MULCOLORBIT		0x00000200		/*	0b00000000000000000000001000000000	*/
/*	For BODYs, BRETs		more than one material used in body					*/
//#define	MULUMATBIT		0x00000400		/*	0b00000000000000000000010000000000	*/

/*	For UBODYs				body has a visible intersection point				*/
// #define	INTERSECTBIT	0x00000800		/*	0b00000000000000000000100000000000	*/
/*	For BODYs				special body										*/
//unset: #define	SPECIBODYBIT	0x00000800		/*	0b00000000000000000000100000000000	*/


/*	For BODYs, BRETs		always cast shadow						*GDL*		*/
//#define	SHADOWONBIT		0x00000020		/*	0b00000000000000000000000000100000	##	*/
/*	For BODYs, BRETs		never cast shadow						*GDL*		*/
//#define	SHADOWOFFBIT	0x00000040		/*	0b00000000000000000000000001000000	##	*/
/*	For BODYs, BRETs		no shadow on body									*/
//#define	SHADOWNOTBIT	0x00000080		/*	0b00000000000000000000000010000000	*/

/*	For UPGONs				polygon is backfacing	 							*/
#define	BACKFACEBIT		0x00000200		/*	0b00000000000000000000001000000000	*/	/*sl950619*/

/*	For PGONs, UPGONs		can be used as cover poly 							*/
//#define	COVERBIT		0x00000100		/*	0b00000000000000000000000100000000	*/	/*vv2*/
//COVERBIT has been removed due to the enhanced cover polygon processing in A-073-Wright

/*	For PGONs, UPGONs		gravity polygon of a ceil/roof/wall					*/
#define	GRAVITYBIT		0x00010000		/*	0b00000000000000000000000100000000	*/	/*vv120*/

/*	For PGONs,UPGONs		inner polygon (for cut)	TT#235442: something similar to INVISBIT but not that, only in planar cut and api. Bug?		*/
#define	INNERBIT		0x00000080		/*	0b00000000000000000000000010000000	##	*/

/*	For PGONs,UPGONs		polygon with concave outer loop				*GDL*		*/
#define	CONCAVBIT		0x00000010		/*	0b00000000000000000000000000010000	##	*/
/*	For PGONs,UPGONs		polygon	with holes						*GDL*		*/
#define	PHOLEBIT		0x00000020		/*	0b00000000000000000000000000100000	##	*/
/*	For PGONs,UPGONs		holes are convex						*GDL*		*/
#define	HOLESCNVBIT		0x00000040		/*	0b00000000000000000000000001000000	##	*/

/*	For CXdividePoly		!= CONCAVBIT && != ERROR							*/
#define	ZEROAREABIT		0x00000040		/*	0b00000000000000000000000001000000	*/

/*	For PGONs,UPGONs		polygon	concav or has hole							*/
#define	COMPLEXBITS		0x00000030		/*	0b00000000000000000000000000110000	##	*/

/*	For EDGEs, TEDGEs, HEDGEs	need eliminate the wall & slab lines			*/
#define	ELIMVERTLINE	0x00000100		/*	0b00000000000000000000000100000000	*/
#define	ELIMHORILINE	0x00000200		/*	0b00000000000000000000001000000000	*/

/*	For -----, BRETs		need check 3D datastructure							*/
//#define	NCHECKBIT		0x00000008		/*	0b00000000000000000000000000001000	*/
/*	For BODYs, BRETs		SURFACE model only						*GDL*		*/
//#define	SURFACEBIT		0x00000004		/*	0b00000000000000000000000000000100	##	*/
/*	For BODYs, BRETs		are closed								*GDL*		*/
//#define	CLOSEDBIT		0x00000001		/*	0b00000000000000000000000000000001	##	*/

/*	For PGONs,UPGONs, EDGEs	pgon for cut, invisible edge (for PEDG)	*GDL*		*/
#define	INVISBIT		0x00000001		/*	0b00000000000000000000000000000001	##	*/


/*	For EDGEs means that edge is visible only if contour		*GDL*		*/
#define	VISIBLEIFCONTOURBIT		0x00000002	/*	0b00000000000000000000000000000010	##	*/
/*	For BODYs, PGONs,UPGONs approximates a curved surface	*GDL*		*/
#define	CURVEDBIT		0x00000002		/*	0b00000000000000000000000000000010	##	*/
/*	For PGONs,UPGONs, EDGEs		approximates a curved surface		*GDL*		*/
#define	CURVEDBEG		0x00000006		/*	0b00000000000000000000000000000110	*/
#define	CURVEDEND		0x0000000A		/*	0b00000000000000000000000000001010	*/

/*	For RTXTs				using alpha channel									*/
/* defines in IMI.h */
#define	LOCKEDPIXS		0x00004000		/*	0b00000000000000000100000000000000	*/

/*	For HVERTs				starting edge of a hole								*/
#define	BEGHOLEHVERTBIT	0x00000001		/*	0b00000000000000000000000000000001	*/
/*	For HVERTs				last edge of a contoure or hole						*/
#define	ENDCONTHVERTBIT	0x00000002		/*	0b00000000000000000000000000000010	*/
/*	For HVERTs				invisible edge										*/
#define	INVISHVERTBIT	0x00000004		/*	0b00000000000000000000000000000100	*/
/*	For HVERTs				edge from a splitline								*/
#define	SPLITHVERTBIT	0x00000008		/*	0b00000000000000000000000000001000	*/

/*	For BODYs wstatus	*/
//#define	BODYINSTATUS	0x00000002		/*	0b00000000000000000000000000000010	*/

//#define	UNSELBIT		0x00000004		/*	0b00000000000000000000000000000100	*/		/*pcs990108*/

/* STATUS BITS FOR SIGHT -> sight.h */

/* For PGONs, BODYs*/
//#define	GENFROMSTORED	0x00080000		/*	0b00000000000010000000000000000000	*/
//#define VIRTMATUSED		0x00100000		/*	0b00000000000100000000000000000000	*/
#define GENERATEDBYREG	0x00200000		/*	0b00000000001000000000000000000000	*/

#define	SHBODY_IRTXT	0
#define	SHBODY_COLOR	1
#define	SHBODY_IUMAT	1

/*--------------------------------------------------------------------------*/
/*---------------------------------- BODY TYPES ----------------------------*/
/*--------------------------------------------------------------------------*/

// moved to BodyTypes.hpp

/*--------------------------------------------------------------------------*/
/*----------------------------- CONDITION TYPES ----------------------------*/
/*--------------------------------------------------------------------------*/

#define	N_DONTNEED		0x0000
#define	N_PROGRESS		0x0001
#define	N_NEEDGENER		0x0002

#define	C_MISSINGS		0x0000
#define	C_PARTIALLY		0x0004
#define	C_FULLVALID		0x0008
#define C_SOMETHING		0x000C

/*================================	 TYPES	================================*/

/*--------------------------------------------------------------------------*/
/*---------------------------- 3D DATA STRUCTURE ---------------------------*/
/*--------------------------------------------------------------------------*/

/* NCOOR == 4 */


/* PEDG == long */					/*  4 */	/* relative to (fedge - 1)				*/
typedef Brep::MeshBrep::Vertex VERT;
typedef Brep::MeshBrep::Edge EDGE;
namespace Modeler {
	typedef Brep::MeshBrep::Polygon PGON;
}

struct UV {
	double	u, v;
	UV (double u, double v) : u (u), v (v) {}
	UV () : u (0.0), v (0.0) {}
};


struct TEVE {
	float	u, v;
	TEVE (float u, float v) : u (u), v (v) {}
	TEVE () : u (0.0f), v (0.0f) {}
};

#define	MSIZE_VERSION	4043
								// [==>
									/* 4008 + 1, for BEXT.obody */
									/* 4009 + 1, for UMAT */
									/* 4010 + 1, for LGHT */
									/* 4012, 	 double VERT, VECT	*/
								//	ARCHICAD 5.1 <==]	[==>
									/* 4013, 	 BODY + BEXT = BODY	*/
									/* 4014, 	 TRANMAT	*/
									/* 4015, 	 STATW->STATL (PGON & EDGE)	*/
									/* 4016, 	 TEVE + MSIZ(60) ==> MSIZ(68)	*/
									/* 4017, 	 FILL510 ==> FILL520		*/
								//	ARCHICAD 6.0 <==]	[==>
									/* 4018,	 Fill index into BODY	*/
									/* 4019,	 HOTS	*/		/*pcs990114*/
									/* 4020,	 GSTime	*/	/*mm-GSTime*/
								//	ARCHICAD 6.5 <==]	[==>
									/* 4021,	 RTXT changes */
									/* 4022,	 LGHT changes */
								//	ARCHICAD 8.1 <==]	[==>
									/* 4023,	 GDL addParHdl changes */
									/* 4024,	 UMAT addParHdl introduction */
									/* 4025,	 LGHT addParHdl written place shift */
								//	ARCHICAD 9.0 <==]	[==>
									/* 4026,	 the background picture is no longer saved among the textures (HK, 2004.09.02) */
									/* 4027,	 linetype in section (FE 2005.03.09) */
								//	ARCHICAD 10.0 <==]	[==>
									/* 4028,	 RTXT unicode, AddPar unicode, long filename (VSZG, 2006.05.25.) */
									/* 4029,	 LGHT unId -> elemGuid (ZG, 2006.07.25.)*/
								//	ARCHICAD 13.0 <==]	[==>
									/* 4030,	RTXT, TXTA, ULGHT 64 - 32 bit compatibility (MM, 2008.09.23)*/
								//	ARCHICAD 13.0 <==]	[==>
									/* 4031,	PGON 64 - 32 bit compatibility - alignment correction (PP, 2009.07.22) */
									/* 4032,	PropertyList is used instead of the addParHdl in UMAT, LGHT (HK, 2009.08.25) */
								//	ARCHICAD 14.0 <==]	[==>
									/* 4033,	Write TEVE bugfix (read wasn't changed) */
								//	ARCHICAD 16.0 <==]	[==>
									/* 4034,	New, versioned writing. */
									/* 4035,	COVERBIT is unnecessary (PP, 2011.08.31) */
								//	ARCHICAD 17.0 <==]	[==>
									/* 4036,	RTXT + TXTA combination (PP, 2012.11.23) */
								//	ARCHICAD 18.0 <==]	[==>
									/* 4037,	introduction of LGHT::up (MA, 2013.12.09) */
									/* 4038,	REND_SHARP_EDGE removed from pgons (CsetA, 2014.02.12) */
									/* 4039,	TEVE elimination, convert to polygon texture parameter (BoB, 2013.11.15) */
									/* 4040,	Type of wrapping in body changed from @short to @Wrapping */
								//	ARCHICAD 19.0 <==]	[==>
									/* 4041,	RTXT: Binary write, read member functions instead of writing/reading the class as a whole object in binary (TG 2015.02.25.) */
								//	ARCHICAD 20.0 <==]	[==>
									/* 4042,	UFIL, UMAT: frame-version-less write functions were removed */
								//	ARCHICAD 25.0 <==]	[==>
									/* 4043,	INIT-24 - new body level attribute: LineEliminationBehaviour */

struct MSIZ {
	Int32				mvers;			/* 4028 */
	Int32				mshap;			/*  always 0 */

	Int32				mbody;			/* *128 */
	Int32				mpgon;			/* * 28 */
	Int32				mpedg;			/* *  4 */
	Int32				medge;			/* * 20	*/
	Int32				mvert;			/* * 24 */
	Int32				mvect;			/* * 24 */

	Int32				mbext;			/* * 36 */

	Int32				mlght;			/* * 56 */

	Int32				mrtxt;			/* * 60 */

	GSAttributeIndex	mufil;			/* * 12 */
	Int32				mumat;			/* * 68	*/

	Int32				mfide;			/* *  1 */
	Int32				mtran;			/* *104 */
	Int32				mteve;			/* *  8 */
	Int32				dummy;
};								/* 68 */

/*  SIGHT DATA STRUCTURE -> sight.h */

/*================================	  MACROS	============================*/

/*--------------------------------------------------------------------------*/
/*---------------------------- GENERAL STATUS MACROS -----------------------*/
/*--------------------------------------------------------------------------*/

#define	INVISIBLE(s)		(((s)->status & INVISBIT) != 0)
#define	VISIBLE(s)			(((s)->status & INVISBIT) == 0)

#define	IS_INVALID(s)		(((s)->status & INVALIDBIT) != 0)
#define	SET_VALID(s)		((s)->status &= ~INVALIDBIT)


/*--------------------------------------------------------------------------*/
/*---------------------------------- LOG BITS ------------------------------*/
/*--------------------------------------------------------------------------*/

#define	LOG_REFMAT_TO_HORI	1
#define	LOG_OPPMAT_TO_HORI	2
#define	LOG_WALLHALF_LOG	4
#define	LOG_QUADRIC_LOG		8

#define	LOG_STRETCHED		64
#define	LOG_RIGHT_DLOG		128
#define	LOG_LEFT_DLOG		256


// ---------------------------------------------------------------------------------------------------------------------
// Kept for GDL compatibility. In VBelements::Wall this property has changed to a bool member from a status bit.
// ---------------------------------------------------------------------------------------------------------------------
#define WALL_ALIGNTEXTURE	32		// GDL_WALLABSYZCOOR

/*--------------------------------------------------------------------------*/
/*------------------------------- MODEL TYPES ------------------------------*/
/*--------------------------------------------------------------------------*/

#define	M_WIRE		0
#define	M_SURFACE	1
#define	M_SOLID		2


#define		C_NORMAL		0	/* == NORMAL   in model.h */
#define		C_INVISBIT		1	/* == INVISBIT in model.h */

#endif
