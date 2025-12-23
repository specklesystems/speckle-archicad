/****************************************************************************/
/*																			*/
/*			GLOBAL DEFINITIONS, MACROS AND COMMON SYSTEM INCLUDE FILES		*/
/*																			*/
/*									NO VARIABLES!							*/
/****************************************************************************/

#ifndef	_iGSUtilsDefs_H_
#define	_iGSUtilsDefs_H_

#pragma once

/* ---------------------------------- Limits ------------------------------ */

#define	MINSMO		6
#define	MAXSMO		360

/* ---------------------------- Masks for surfaces ------------------------	*/

#define	M_BOTTOM		 1
#define	M_TOP			 2
#define	M_SIDE1			 4
#define	M_SIDE2			 8

/* ---------------------------- Masks for edges ------------------------	*/

#define	M_BOTEDGES						16
#define	M_TOPEDGES						32
#define	M_ALLEDGES						64
#define M_ELIMHORLINES					128
#define M_ELIMVERLINES					256
#define M_ALLEDGESINVIS					512

#define M_MESHTOPEDGESINVIS				512
#define M_SHELLOFFSETEDGESINVIS			1
#define M_SHELLSURFACEEDGESINVIS		2

#define M_TUBECURVEDPROFILESEGMENTATION	256
#define M_REVOLVECURVEDSEGMENTATION		1024
#define M_TUBEELIMBOTTOMLINES		512
#define M_TUBEELIMTOPLINES			1024
#define M_TUBEELIMLONGITUDINALLINES	2048
#define M_TUBEELIMCROSSLINES		4096

/* --------------- Masks for CreateGroupWithMaterial ----------------------	*/

#define M_CHANGEPEN					1
#define M_CHANGEMATERIAL			2
#define M_CHANGEPOLYGONID			4
#define M_MAKEEDGESINVISIBLE		8

#endif
