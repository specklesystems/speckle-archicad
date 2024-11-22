/************************************************************************/
/*																		*/
/*																		*/
/************************************************************************/

#ifndef	_ProcessNum_H_
#define	_ProcessNum_H_

#pragma once

/*==========================		CONSTANTS		========================*/

#define ProcSleepTicks		(1 * TicksPerSecond)

/* Conversion */
#define	PNUM_ConvertTo3D	1			/* ba95 02.27. */
#define	PNUM_Conv2DScript	4			/* PROJECT2 miatt 3 ==> 4 */
#define	PNUM_Conv3DScript	2
#define	PNUM_CutModel		1
#define	PNUM_CutToWindow	1
#define	PNUM_Projection		1
#define	PNUM_DTConvert		2			/* PNUM_CutToWindow + PNUM_Projection */

/* DumpPlan */
#define	PNUM_PDumpPlan		7

/* Convert oldroofs to newroofs */
#define	PNUM_ORoofToNew		1

/* Section generation */
#define	PNUM_SectElevation	2
#define	PNUM_DTCutFills		1
#define	PNUM_AddSideFills	1
#define	PNUM_AddHotspots	1

/* Hidden methods */
#define	PNUM_HiddLineAnal	2
#define	PNUM_EliminLines	1
#define	PNUM_ShadingAnal	1
#define	PNUM_ClipShadAnal	1
#define	PNUM_ClipPointCloud	1

/* Export methods of 3D Window */
#define	PNUM_ExportFills	1
#define	PNUM_ExportLines	1

/* Rendering & Shadow generation */
#define	PNUM_LightMarkBody	1
#define	PNUM_ConvLightSpace	2			/* PNUM_CutToWindow + PNUM_Projection */
#define	PNUM_Conv2Pano		2			/* PNUM_CutModel + PNUM_Projection */
#define	PNUM_Bucketing		1
#define	PNUM_RDGenNormals	1
#define	PNUM_REimager		1
#define	PNUM_GenShBodies	1
#define	PNUM_ConvShBodies	2			/* PNUM_CutToWindow + PNUM_Projection */
#define	PNUM_VSShadLin		1

/* Lista */
#define	PNUM_GenListData	16		/* fe210 */

#endif
