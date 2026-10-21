/****************************************************************************/
/*                                                                          */
/*						RESOURCE ID-S FOR 3D DATABASE						*/
/*                                                                          */
/****************************************************************************/

#ifndef _DDDres_H_
#define	_DDDres_H_

#pragma once

#include	"GSUtilsres.h"

/*--------------------------- STR#, STRf resource IDs ----------------------*/

#define	MAT_TYPES_STRS	 2010	/* Resource ID of "Material types"		STR#*/

//!#define	TIME_REPORT_STRS 2015	/* Resource ID of "Time Report"			STR#*/
//!#define	CONV_REPORT_STRS 2016	/* Resource ID of "Conversion Report"	STR#*/
#define	PROJ_REPORT_STRS 2017	/* Resource ID of "Projection Report"	STR#*/
#define	HIDD_REPORT_STRS 2018	/* Resource ID of "Hidden Line Report"	STR#*/

#define	PROJECTIONS_STRS 2020	/* Resource ID of "Projection names"	STR#*/

#define	LIST3D_STRS		 2500	/* Resource ID of "List 3D data struc."	STRf*/
#define	ATTRIBUTES_REPORT_STRS		2501	/* Resource ID of "List 3D Attributes."	STRf*/
#define	MODEL3D_REPORT_STRS			2502	/* Resource ID of "List 3D Model."	STRf*/
#define	SIGHT_REPORT_STRS			2503	/* Resource ID of "List Sight."	STRf*/

#define	COPYRIGHT1_STRS	 7000	/* Resource ID of "Copyright Movie"		STRf*/
#define	COPYRIGHT2_STRS	 7001	/* Resource ID of "Copyright Movie"		STR#*/

// TEMP_FILE_NAMES --> GSUtilsres.h
#define	TMP_MOVIE		3
//#define	TMP_APPLY		4 --> RE.c
#define	TMP_RENDER		5

#define	TMP_BODY		6
#define	TMP_PGON		7
#define	TMP_PEDG		8
#define	TMP_EDGE		9
#define	TMP_VERT		10
#define	TMP_VECT		11
#define	TMP_VOCA		12

#define	TMP_SBODY		13
#define	TMP_SPGON		14
#define	TMP_SPEDG		15
#define	TMP_SEDGE		16
#define	TMP_SVERT		17
#define	TMP_SVECT		18

#define	TMP_RBODY		19
#define	TMP_RVECT		20

#define	TMP_UBODY		21
#define	TMP_UPGON		22
#define	TMP_UEDGE		23
#define	TMP_UVERT		24

#define	TMP_HEDGE		25
#define	TMP_HVERT		26

#define	TMP_OHPGON		27		/*vv19*/
#define	TMP_OHPVER		28
#define	TMP_CHPGON		29
#define	TMP_CHPVER		30

#define	TMP_HEPGO		31
#define	TMP_HETRI		32

#define	TMP_SIGHT		33

#define TMP_HBODY		34

#define	TMP_SFOLD		35

#define	TMP_HI1			36
#define	TMP_HI2			37
#define	TMP_HI3			38
#define	TMP_HI4			39
#define	TMP_HI5			40
#define	TMP_HI6			41

#define	TMP_TRAN		42
#define	TMP_STRAN		43

#define	TMP_TEVE		44
#define	TMP_STEVE		45

#define	TMP_HOTS		46
#define	TMP_SHOTS		47

#define	TMP_MFOLD		49

#define TMP_POLYGONINSHADOWBITS 51
#define TMP_PROJECTEDPOINTCLOUD	52
#define TMP_HIDDENPOINTCLOUD	53

#define	TMP_OHPGON_SUN	54
#define	TMP_OHPVER_SUN	55
#define	TMP_CHPGON_SUN	56
#define	TMP_CHPVER_SUN	57
#define TMP_HBODY_SUN	58
#define	TMP_HEPGO_SUN	59
#define	TMP_HETRI_SUN	60
#define	TMP_UBODY_SUN	61
#define	TMP_UPGON_SUN	62
#define	TMP_UEDGE_SUN	63
#define	TMP_UVERT_SUN	64
#define	TMP_HEDGE_SUN	65
#define	TMP_HVERT_SUN	66
#define TMP_PROJECTEDPOINTCLOUD_SUN 67
#define TMP_HIDDENPOINTCLOUD_SUN	68
#define	CAMERA_STRS		10120	/* Resource ID of Camera export strings	STRf*/

#endif
