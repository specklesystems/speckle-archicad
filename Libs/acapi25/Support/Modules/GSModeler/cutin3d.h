/*==========================================================================**
**																			**
**					CONSTANTS AND TYPES FOR CUTTING PLANES					**
**																			**
**==========================================================================*/

#ifndef _cutin3d_H_
#define _cutin3d_H_

#pragma once

#include	"Array.hpp"
#include	"GSUtilsDefs.h"

#include	"Coord3d.h"

#include	"Model3D/LocalCoordSys.hpp"
#include	"GSModelerExport.h"

/*================================	CONSTANTS	============================*/

/*---------------------------- CUT STATUS BITS  ----------------------------*/

/*	For CUT_RECORDs															*/
#define	CUT_USEOWNBIT	0x0010					/*	0b0000000000010000		*/	/* status & 1   in the GDL script */
#define	CUT_U_SHAPEBIT	0x0020					/*	0b0000000000100000		*/
#define	CUT_L_SHAPEBIT	0x0040					/*	0b0000000001000000		*/
#define CUT_CONVPGONBIT	0x0080					/*	0b0000000010000000		*/

#define CUT_INTERSECT	0x0100					/*	0b0000000100000000		*/	/* status & 32  in the GDL script */

#define CUT_BOTTOM_GEN_EDGES	0x0200			/*	0b0000001000000000		*/	/* status & 64  in the GDL script */
#define CUT_TOP_GEN_EDGES		0x0400			/*	0b0000010000000000		*/	/* status & 128  in the GDL script */
#define CUT_REMOVE_ON_PLANE_VERT	0x0800		/*	0b0000100000000000		*/	/* status & 256  in the GDL script */

/* In model.h for PGONs,CUT_RECORDs	(for wall)								*/
/*#define	CUT_EDGE1BIT	0x0400				0b0000010000000000			*/
/*#define	CUT_EDGE2BIT	0x0800				0b0000100000000000			*/
/*#define	CUT_EDGEBITS	0x0C00				0b0000110000000000			*/
/*In model.h for BODYs, -----, CUT_RECORDs									*/
/*#define	DELBIT			0x8000				0b1000000000000000			*/

/*	For CUT_RECORD.invisb													*/
#define	CUT_DIS_INVIS_E	  0x0001				/*	0b0000000000000001		*/											// Disable making cut edges invisible
#define	CUT_DIS_INVIS_P	  0x0010				/*	0b0000000000010000		*/											// Disable making cut polygons invisible
#define	CUT_DIS_MCUT_P	  0x0020				/*	0b0000000000100000		*/	/* status & 2  in the GDL script */		// Disable putting ON_CUT_BIT on cut polygons
#define	CUT_M_INVIS_E	  0x0040				/*	0b0000000001000000		*/	/* status & 4  in the GDL script */		// Make (all) cut edges invisible
#define	CUT_MODEL_BIT	  0x0080				/*	0b0000000010000000		*/
#define CUT_SECT_SPECPL0  0x0100                /*  0b0000000100000000      */  /* cut elem is maked SECT_SPEC if */
#define CUT_SECT_SPECPL1  0x0200                /*  0b0000001000000000      */  /* all the cutplanes it is on are */
#define CUT_SECT_SPECPL2  0x0400                /*  0b0000010000000000      */  /* marked SPECPL#				  */
#define CUT_DIS_CUT_E	  0x0800				/*  0b0000100000000000		*/  /* status & 512 in GDL script (generated cut edges will be treated as normal edges)*/		// Disable putting ON_CUT_BIT on cut edges
#define CUT_ONPLANE		  0x1000				/*  0b0001000000000000		*/  /* onplane cut */

#define CUT_LIMIT_MASK			0x0003			/* 0b00000000000000011		*/	/* status & 24  in the GDL script */
#define CUT_LIMIT_FINITE		0x0000			/* 0b00000000000000000		*/
#define CUT_LIMIT_HALFFINITE	0x0002			/* 0b00000000000000010		*/
#define CUT_LIMIT_INFINITE		0x0003			/* 0b00000000000000011		*/
#define CUT_LIMIT_UNDEFINED		0x0001			/* 0b00000000000000001		*/  /*used only for testing the input! */

/*================================	 TYPES	================================*/

/*------------------------------- CUT RECORD  ------------------------------*/

struct CUT_RECORD {
	STATW				status;
	STATW				invisb;				/* Bits for edge/pgon invisibility		*/
	short				dummy1;
	short				cutColor;			/* Color of EDGEs on cut planes			*/
	GSAttributeIndex	cutGlima;			/* Material index of PGONs on cut planes*/

	LocalCoordSys		lcs;				/* texture wrapping mode and			*/
											/* local coordinate system			*/

	Int32				cutPolygonId;		/* polygonId of PGONs on cut planes		*/
	short				method;				/* only if (status & CUT_CONVPGONBIT)	*/
											/* see the CUT_METHOD_* bits		*/
	short				limit;				/* only if (status & CUT_CONVPGONBIT)	*/
											/* see the CUT_LIMIT_* bits			*/
	double				pa, pb, pc, pd;		/* Equation of plane #0					*/
											/* pa*x + pb*y + pc*z > pd => outside	*/
											/* (pa, pb, pc) is a unit vector		*/
											/* if (status & CUT_CONVPGONBIT) :		*/
											/* pa*x + pb*y + pc*z + pd == 0		*/
											/* is the base plane of cut			*/
											/* (pa, pb, pc) is a unit vector	*/

											/* if (status & CUT_U_SHAPEBIT) :		*/
	double				px, py, pz;			/* Point on planes #0 and #1		*/
											/* pa*px + pb*py + pc*pz == pd		*/
											/* if (status & CUT_CONVPGONBIT) :		*/
											/* if (method == CUT_METHOD_WEDGE)	*/
											/*		dirvector of top of wedge	*/
	double				na, nb, nc;			/* Unit normal vector of plane #1	*/
											/*				  and (-)plane #2	*/
											/* na*pa + nb*pb + nc*pc == 0		*/
	double				nd;					/* na*px + nb*py + nc*pz == nd		*/
	double				dd;					/* Distance of planes #1 and #2		*/
											/* if (status & CUT_L_SHAPEBIT)		*/
	double				va, vb, vc;			/* (pa, pb, pc) x (na, nb, nc)		*/
											/* only if (status & CUT_CONVPGONBIT) :	*/
	Int32				nplan;				/* number of cutting planes			*/
	GS::Array<short>	cutmasks;			/* mask of the planes				*/
	GS::Array<COORD3>	planeNormal;		/* normal vectors of planes			*/
	GS::Array<COORD3>	cornerPoint;		/* corner points					*/
	GS::Array<GSAttributeIndex>	cutMats;	/* color of planes					*/
	GS::Array<Int32>	cutPolygonIds;		/* polygonId of planes				*/
	double				ra, rb, rc;			/* if (status & CUT_CONVPGONBIT)		*/
											/* if (method == CUT_METHOD_PRISM)	*/
											/*		dirvector of cutting edges	*/
											/* if (method == CUT_METHOD_PYRAMID)*/
											/*		top as dirvector			*/
	COORD3				top;				/* if (method == CUT_METHOD_PYRAMID)*/
											/*		top as point				*/
											/* if (method == CUT_METHOD_WEDGE)	*/
											/*		top	as point				*/

	CUT_RECORD (void) :
		status		(0),
		invisb		(0),
		dummy1		(0),
		cutColor	(0),
		cutGlima	(0),
		lcs			(),		// invalid by default
		cutPolygonId (0),	/*Modeler::PolygonId::Invalid.GetValue ()*/
		method (0),
		limit (0),
		pa (0.0),
		pb (0.0),
		pc (0.0),
		pd (0.0),
		px (0.0),
		py (0.0),
		pz (0.0),
		na (0.0),
		nb (0.0),
		nc (0.0),
		nd (0.0),
		dd (0.0),
		va (0.0),
		vb (0.0),
		vc (0.0),
		nplan (0),
		ra (0.0),
		rb (0.0),
		rc (0.0)
	{
		top.x = top.y = top.z = 0.0;
	}

	void	Clear (void)
	{
		status = 0;
		invisb = 0;
		dummy1 = 0;
		cutColor = 0;
		cutGlima = 0;
		lcs = LocalCoordSys ();
		method = 0;
		limit = 0;
		pa = pb = pc = pd = 0.0;
		px = py = pz = 0.0;
		na = nb = nc = nd = 0.0;
		dd = 0.0;
		va = vb = vc = 0.0;
		nplan = 0;
		cutmasks.Clear ();
		planeNormal.Clear ();
		cornerPoint.Clear ();
		cutMats.Clear ();
		cutPolygonIds.Clear ();
		ra = rb = rc = 0.0;
		top.x = top.y = top.z = 0.0;
	}

	GSErrCode GSMODELER_DLL_EXPORT WriteXML (GS::XMLOChannel& xml, const char* tagname = nullptr) const;
	GSErrCode GSMODELER_DLL_EXPORT ReadXML (GS::XMLIChannel& xml, const char* tagname = nullptr);
};

enum CutElemHandling
{
	KeepCutElems,
	ThrowCutElems
};


/*================================	FUNCTIONS	============================*/

#endif
