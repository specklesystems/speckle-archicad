/*==========================================================================**
**									projCode.h								**
**																			**
**									PROJECTION CODES						**
**==========================================================================*/

#ifndef _projCode_H_
#define _projCode_H_

#pragma once

/*================================	CONSTANTS	============================*/

/* -------------------------------- PROJECTIONS --------------------------- */

								/* Projection types		*/
#define ProjYZ		 1			/* YZ projection		*/
#define ProjXZ		 2			/* XZ projection		*/
#define ProjXY		 3			/* XY projection		*/
#define ProjFront	 4			/* Frontal axonometry	*/
#define ProjMonom	 5			/* Monometric axonometry*/
#define ProjIzo		 6			/* Isometric axonometry	*/
#define ProjDim		 7			/* Dimetric  axonometry	*/
#define ProjPersp	 8			/* Perspective			*/
#define ProjBottom	 9			/* Bottom view			*/
#define ProjFrontB	10			/* Frontal axonometry down-up	*/
#define ProjMonomB	11			/* Monometric axonometry down-up*/
#define ProjIzoB	12			/* Izometric axonometry down-up	*/
#define ProjDimB	13			/* Dimetric  axonometry down-up	*/

#define ProjParal	14			/* Parallel projection	*/
#define ProjFreeAx	15			/* Free axonometry	*/

/*	For PROJCODE															*/
#define	P_FRONT		0
#define	P_BACK		1		/* ProjXZ	  =  2 */
#define	P_OVER		2
#define	P_TOP		3		/* ProjXY	  =  3 */
#define	P_LEFT		4		/* ProjYZ	  =  1 */
#define	P_RIGHT		5
#define	P_FROAX		6		/* ProjFront  =  4 */
#define	P_ISOAX		7		/* ProjIzo	  =  6 */
#define	P_MONAX		8		/* ProjMonom  =  5 */
#define	P_DIMAX		9		/* ProjDim	  =  7 */
#define	P_PERSP		10		/* ProjPersp  =  8 */

#define	P_BOTTOM	11		/* ProjBottom =  9 */
#define	P_FROAX_B	12		/* ProjFrontB = 10 */
#define	P_ISOAX_B	13		/* ProjIzoB	  = 12 */
#define	P_MONAX_B	14		/* ProjMonomB = 11 */
#define	P_DIMAX_B	15		/* ProjDimB	  = 13 */

#define	P_FREE_AX	19		/* ProjFreeAx = 15 */
#define	P_PARALLEL	20		/* ProjParal  = 14 */

#define	P_TOP_REFL	21		

#define	PROJCODE1	P_LEFT
#define	PROJCODE2	P_BACK
#define	PROJCODE3	P_TOP

#define	LAYOUT(i)	i


/*
			ProjYZ		 1			{YZ projection}
			ProjXZ		 2			{XZ projection}
			ProjXY		 3			{XY projection}
			ProjFront 	 4			{Frontal axonometry}
			ProjMonom 	 5			{Monometric axonometry}
			ProjIzo 	 6			{Isometric axonometry}
			ProjDim 	 7			{Dimetric  axonometry}
			ProjPersp 	 8			{Perspective}
			ProjBottom	 9			{Bottom view}
			ProjFrontB	10			{Frontal axonometry down-up}
			ProjMonomB	11			{Monometric axonometry down-up}
			ProjIzoB	12			{Izometric axonometry down-up}
			ProjDimB	13			{Dimetric  axonometry down-up}
			ProjParal	14			{Parallel projection}
			ProjFreeAx	15			{Free axonometry}
*/

enum	ProjectedModelPartBits {
	P_Export_CutPolygons	= 0x0001,		/* export cut polygons and fills */
	P_Export_CutEdges		= 0x0002,		/* export cut edges */
	P_Export_ViewPolygons	= 0x0004,		/* export view polygons and fills */
	P_Export_ViewEdges		= 0x0008,		/* export view edges  */
	P_Export_SectCutElems	= 0x0010,		/* export elements cut by Section  */
	P_Export_PointClouds	= 0x0020,		/* export point clouds  */
	P_Export_AllParts		= 0x003F		/* All parts */
};

#ifdef _TR_TRANSL_
static	short	projequ[] =
			{0, P_LEFT, P_BACK, P_TOP, P_FROAX, P_MONAX, P_ISOAX, P_DIMAX, P_PERSP,
				P_BOTTOM, P_FROAX_B, P_MONAX_B, P_ISOAX_B, P_DIMAX_B, P_PARALLEL, P_FREE_AX};
#endif

#endif
