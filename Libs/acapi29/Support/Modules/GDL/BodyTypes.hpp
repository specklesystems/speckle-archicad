// *********************************************************************************************************************
// Description:		Body types
//
// Module:			GSModeler
// Namespace:		
// Contact person:	PP
//
// SG compatible
// ********************************************************************************************************************* 

#ifndef BODYTYPES_HPP
#define BODYTYPES_HPP

#pragma once

#include	"GDLExport.h"



//-----------------------------------------------------------------
//
//
//
//
// If you add new BodyTypes, you have to update the SkipBodyTest!
//
//
//
//
//-----------------------------------------------------------------




typedef	short	BTType;


const BTType	B_PRIMITIVE				=	0;
const BTType	B_BRICK					=		100;
const BTType	B_CYLIND				=		200;
const BTType	B_CYLSEC				=		300;
const BTType	B_PIPE					=		400;
const BTType	B_SPHERE				=		500;
const BTType	B_CONE					=		600;
const BTType	B_ELBOW					=		700;

const BTType	B_GENCYLS				=	1000;
const BTType	B_RING					=		1100;
const BTType	B_GENCONE				=		1200;
const BTType	B_GENCYL				=		1300;
const BTType	B_ARMC					=		1400;
const BTType	B_ARME					=		1500;
const BTType	B_ELLIPS				=		1600;

const BTType	B_PROFILE				=	2000;		/* not used */

const BTType	B_WALL					=	3000;
const BTType	B_NEWALL				=		3100;
const BTType	B_CUT_WALL				=		3200;
const BTType	B_BEWALL				=		3300;
const BTType	B_CUT_BEWALL			=		3400;
const BTType	B_PWALL_LINES			=		3500;
const BTType	B_BWALL_LINES			=		3600;

const BTType	B_GDL					=	4000;
const BTType	B_ANYGDL				=		4100;
const BTType	B_GDLBIN				=		4500;
const BTType	B_BINARY				=		4600;

const BTType	B_CURVE1				=	5000;
const BTType	B_REVOLVE				=		5100;
const BTType	B_EXTRUDE				=		5200;
const BTType	B_PYRAMID				=		5300;
const BTType	B_GENPRISM				=		5400;

const BTType	B_PRISM					=		5410;
//const BTType	B_CPRISM				=		5411;
const BTType	B_SPRISM_				=		5412;
const BTType	B_PRISM_2D				=		5413;
const BTType	B_PRISM_REVEAL			=		5414;
const BTType	B_PRISM_				=		5415;
const BTType	B_CPRISM_				=		5416;		/* B_PRISM_ + 1 */
//const BTType	B_COLUMN				=		5417;
const BTType	B_BPRISM_				=		5418;
const BTType	B_FPRISM_				=		5419;
const BTType	B_SLAB					=		5420;
//const BTType	B_CSLAB				=		5421;
const BTType	B_SLAB_2D				=		5423;		/*vv2*/
const BTType	B_SLAB_					=		5425;
const BTType	B_CSLAB_				=		5426;		/* B_SLAB_ + 1 */
const BTType	B_POLY					=		5430;
const BTType	B_POLY_					=		5435;
const BTType	B_PLANE					=		5440;
const BTType	B_PLANE_				=		5445;
const BTType	B_CROOF_				=		5456;
const BTType	B_CWSUBELEM				=		5457;
const BTType	B_PRISM_SLOPED			=		5460;
const BTType	B_PRISM_SLOPED_ROD		=		5461;
const BTType	B_CPRISM_EANG			=		5462;
const BTType	B_SPRISM_3_ELIM			=		5463;
const BTType	B_SPRISM_3_SLOPED_ELIM	=		5464;
const BTType	B_CPRISM_3_ELIM			=		5465;
const BTType	B_MASS2					=		5466;
const BTType	B_CROOF_3				=		5467;

const BTType	B_EXTRUDEDSHELL			=		5500;
const BTType	B_REVOLVEDSHELL			=		5600;

const BTType	B_CURVE2				=	6000;
const BTType	B_SWEEP					=		6100;
const BTType	B_TUBE					=		6200;
const BTType	B_TUBEA					=		6300;
const BTType	B_PLANARPATHTUBE		=		6400;
const BTType	B_RULED					=		6500;
const BTType	B_RULEDSHELL			=		6600;

const BTType	B_CURVES				=	7000;
const BTType	B_MESH					=		7100;
const BTType	B_COON					=		7200;
const BTType	B_MASS					=		7300;
const BTType	B_BEAM					=		7400;

const BTType	B_PLANAR				=	8000;
const BTType	B_SEGMENT				=		8100;
const BTType	B_POLYGON				=		8200;
const BTType	B_TWOD					=		8300;

const BTType	B_ARC					=		8500;
const BTType	B_CIRCLE				=		8600;
const BTType	B_RECT					=		8700;


	/*
	**	WARNING !!!
	**		If you make any changes in light type codes contact to
	**		:E:AC3Xinc.h
	**		vv94.02.03
	*/
const BTType	B_LIGHT					=	9000;
const BTType	B_DIST_LIGHT			=		9100;
const BTType	B_DIR_LIGHT				=		9200;
const BTType	B_SPOT_LIGHT			=		9300;
const BTType	B_POINT_LIGHT			=		9400;
const BTType	B_SUN_LIGHT				=		9500;		/* After 5.00 */
const BTType	B_EYE_LIGHT				=		9600;		/* After 5.00 */

const BTType	B_PICT					=	10000;

const BTType	B_NURBS					=	20000;

const BTType	B_OTHER					=	30000;
const BTType	B_EMPTY					=		30100;
const BTType	B_CUT					=		30200;
const BTType	B_INTERS				=		30300;
const BTType	B_SHADOW				=		30500;
const BTType	B_VECTSHADOW			=		30600;
const BTType	B_SHADOWSIZE			=		30700;	/* Do not generate this */
//const BTType	B_ELIM_LINES			=		30800;	// The class ElimBody was born in D043.

const BTType	B_UNKNOWN				=	30900;

const BTType	B_CUT_PGONS				=	31000;	/*body containing the cut polygons of the elem*/

const BTType	B_NOTHING				=	32766;
const BTType	B_MULTI					=	32767;


#define		PRISM_3D	B_PRISM_2D
#define		SLAB_3D		B_SLAB_2D


GDL_DLL_EXPORT	BTType	GetMainType (const BTType btype);
GDL_DLL_EXPORT	BTType	GetSubType (const BTType btype);


#endif // BODYTYPES_HPP
