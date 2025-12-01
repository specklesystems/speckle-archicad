#if !defined (CUT2DINTERNAL_H)
#define CUT2DINTERNAL_H

#pragma once
/****************************************************************************/
/*																			*/
/*							CUT A 2D OLDPOLY BY A LINE						*/
/*																			*/
/****************************************************************************/

struct	HalfPlane2DData;
struct	PolyArcRec;

enum	CutPolyRes {
	Empty,
	NotEmpty,
	Failed
};

GEOMETRY_DLL_EXPORT
CutPolyRes 	CUCutNumPoly (	short					cutNum,				/* -> number of cutline			*/
							HalfPlane2DData			*cutlines,			/* -> line params. 				*/
							Int32 ipa, 				Int32 *parts,		/* -> parts						*/
							Int32 ipb, 				UInt32 *pends,		/* -> ends						*/
							Int32 ipc, 				double *pcoos,		/* -> coord. array  			*/
							Int32 ipr,      		PolyArcRec *parcs,	/* -> arcs array				*/
							bool isPLine,			bool forceOpen,		/* -> polyline or polygon, open pl.*/	
							bool elimin,								/* -> eliminate identic. points */
							const Box2DData*pBox,	bool limState,		/* -> polygon box and state 	*/
							Int32 *pcind,   		Int32 *ppind,		/* -> edge & corn. ind. array 	*/
							Int32 *jpa, 			Int32 **cparts,		/* <- parts						*/
							Int32 *jpb, 			UInt32 **cpends,	/* <- ends						*/
							Int32 *jpc, 			double **cpcoos,	/* <- coord. array  			*/
							Int32 *jpr,     		PolyArcRec **cparcs,/* <- arcs array				*/
							Int32 **cpcind, 		Int32 **cppind,		/* <- edge & corn. ind. array 	*/
							bool *fullin,								/* <- full inside 				*/
							Int32 *wrcode,		 				 		/* <- warning error code   		*/
							bool *degen = nullptr);		 				/* <- one line result   		*/

GEOMETRY_DLL_EXPORT
short	CXCorrectPolyCCWArc (Int32 npb, UInt32 *pends,			/* ->  ends						*/
							 Int32 /*npc*/, double *pcoos,	/* <-> coord. array 			*/
							 USize npr, PolyArcRec *parcsPar,	/* <-> arcs array				*/
							 Int32 *pcind, Int32 *ppind);		/* <-> edge & corn. ind. array 	*/

#endif
