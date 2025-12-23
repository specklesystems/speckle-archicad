/*==========================================================================**
**								Projection.h								**
**																			**
**					GLOBAL CONSTANTS, TYPES FOR PROJECTIONS					**
**==========================================================================*/

#ifndef _Projection_H_
#define _Projection_H_

#pragma once

#include "GSUtilsDefs.h"		// STATW

/*------------------------------- PROJECTION  ------------------------------*/

struct PERSDEF {					/* Data of perspective projection		*/
	short		projCode;			/* Projection code					 (2)*/
	STATW		status;
	Int32		dummy;
	double		eyex, eyey, eyez;
	double		rigx, rigy, rigz;
	double		topx, topy, topz;
	double		dirx, diry, dirz;
	double		distance, focus;
	double		fov, dirtg;
	double		dummy1, dummy2;
};		/* 152 */

struct AXONDEF {					/* Data of orthogonal projection		*/
	short		projCode;			/* Projection code					 (2)*/
	STATW		status;
	Int32		dummy;
	double		tran[9];
	double		invtran[9];
};		/* 152 */

union PEAXDEF {
	PERSDEF		pdef;
	AXONDEF		adef;
};		/* 152 */

/*	For SHOW_TYPE															*/
#define	S_BLOCK			 4
#define	S_LCOOR			 5

// RA = raster
// AN = analytic

// LI = lines
// PO = polygons

// PA = paint
// HI = hidden

#define	S_REND			 9
#define	S_WIRE			10
#define	S_ANLI			14
#define	S_PAPO			16
#define	S_PAPOLI		17
#define	S_HIPO			18
#define	S_HIPOLI		19

#endif
