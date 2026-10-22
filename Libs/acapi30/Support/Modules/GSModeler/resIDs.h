/****************************************************************************/
/*                                                                          */
/*						RESOURCE ID-S OF DIFFERENT RESOURCES				*/
/*                                                                          */
/****************************************************************************/

#ifndef _resIDs_H_
#define	_resIDs_H_

#pragma once

/*------------------------------ STR# resource IDs -------------------------*/

/* WiTool.c */
#define	PROCESS_STRS	 2000	/* Resource ID of "Process texts"		STR#*/

/* In CONres.h :
		PROCESS_STRS	 2000

		INT_ERROR_STRS	 2005
		ERROR_STRS		 2006
		CONV_FIX_STRS	 2008
		MAT_TYPES_STRS	 2010
*/

/* DiModel.p */

/* In DDDres.h :
		TIME_REPORT_STRS 2015
		CONV_REPORT_STRS 2016
		PROJ_REPORT_STRS 2017
		HIDD_REPORT_STRS 2018
		REND_REPORT_STRS 2019

		PROJECTIONS_STRS 2020
*/

#define	S3D_REPORT_STRS  2022	/* Resource ID of "SaveAs 3D Report"	STR#*/

#define	MAIN_REPORTSTRS  2025	/* Resource ID of "Main Process Rep.3D"	STR#*/

#define	GDL3DOUT_STRS	 2030	/* Resource ID of "GDL 3D output str.s"	STRf*/

#define	SYMB_FILE_NAME	 2031	/* Resource ID of "GDL 3D filename str.s"	STRf*/

#define DLL_ERROR_STRS	 2100	/* Resource ID of "DLL Errors"			STR#*/

/* In DDDres.h :
		LIST3D_STRS		 2500
*/
#define	CHECK3D_STRS	 2510	/* Resource ID of "Check 3D data struc"	STR#*/
#define	UPDATELIBS_STRS	 2520	/* Resource ID of "Update library part"	STR#*/

/* EX.c */
#define	IO_REPORT_STRS	 2600	/* Resource ID of "I/O Report"			STR#*/

//!#define	TEMP_FILE_NAMES	10000	/* Names of predefined temporary files	STRf*/

/* F3.c, Convert.c, SymbEdit.c, IoConv.c, Window.c, WiUtil.c */
#define	SYHEAD_LOC_STRS	10005	/* Resource ID of "GDL header strings"	STR#*/
#define	SYHEAD_FIX_STRS	10006	/* Resource ID of "GDL header keywords"	STRf*/
#define	SYHEAD_WIN_STRS	10007	/* Resource ID of "GDL Windows strings"	STRf*/
#define	SYGDL_FIX_STRS	10008	/* Resource ID of "GDL lines"			STRf*/	/*vv25*/

/* In GDLres.h :
		GDLKEYWORDS		10010
		GDLFIXSTRS		10011
		GDLREQUESTS		10015

		GDLERRORS		10020
		GDLWARNINGS		10023
		GENERRORS		10025
		GENWARNINGS		10028
*/

/* 10030 deleted */		/*vv28*/
/* 10033 deleted */		/*vv28*/
/* 10034 deleted */		/*vv28*/
/* 10038 deleted */		/*vv28*/
/* 10039 deleted */		/*vv28*/

/* 10040 deleted */		/*vv138*/
/* 10041 deleted */		/*vv138*/

#define	ELEMTYPE_STRS	10100	/* Resource ID of Element type names	STR#*/


#define O3_GENERAL		10110	/* General strings for saving 3D 		STR#*/
#define	O3_SHAREDHEADS	10111	/* Shared dialog headers 				STR#*/
/* STR#(10112) deleted */
/* STR#(10113) deleted */
/* STR#(10114) deleted */

#define	COPYDLOGHEADS	10115	/* Dialog Header for 3D Copy 				*/
/* In DDDres.h :
		CAMERA_STRS		10120
*/

#endif
