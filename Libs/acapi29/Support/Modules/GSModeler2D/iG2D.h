/****************************************************************************/
/*																			*/
/*						PROTOTYPES FOR G2D PRIVATE ROUTINES					*/
/*																			*/
/****************************************************************************/

#ifndef _iG2D_H_
#define _iG2D_H_

#pragma once

/*================================	PROTOTYPES	============================*/

#include	"GSModeler2DExport.h"
#include	"HatchTran.hpp"

struct PolyArcRec;
struct GS_RGBColor;

extern "C" {

typedef	void	GSM2D_CALL	API_PutPointProc (short pen, const Coord *c);
typedef	void	GSM2D_CALL	API_PutLineProc (short pen, short pattern, double penWeight,
											 const Coord *c1, const Coord *c2);
typedef	void	GSM2D_CALL	API_PutPLineProc (short pen, short pattern, double penWeight,
											  Int32 nCo, const Coord * const pCo, Int32 di);
typedef	void	GSM2D_CALL	API_PutArcProc (short pen, short pattern, double penWeight,
											const Coord *orig, double r, double begAng, double endAng,
											bool filled, bool whole,
											double ratio, double angle);
typedef	void	GSM2D_CALL	API_PutTextProc (short pen,
											 const Coord *loc,
											 double heightMM, double widthMM, double angle, double slant,
											 short font, short familytype, char *fontName,
											 char centre, short just, short face,
											 const char *value, short paramInd, short ind1, short ind2,
											 double *alx, double *aly, short drwIndex,
											 short status);
typedef	void	GSM2D_CALL	API_PutPixMapProc (short pen,
											 const Coord *loc, double angle,
											 char centre);
typedef	void	GSM2D_CALL	API_PutPolyProc (short pen, short pattern, double penWeight,
											 Int32 npc, const Coord *myPolyCoordsPtr,
											 Int32 npb, const UInt32 *mySubPolyEndsPtr,
											 Int32 npa, const PolyArcRec *myPolyArcsPtr,
											 bool filled);

typedef	bool	GSM2D_CALL	API_HatchBorderBegProc (bool doFrame, short fillInd, short fillPen, short fillbkgPen, short determination,
												const GS_RGBColor* foreRgb, const GS_RGBColor* bkgRgb, short transparency,
												bool isGradient, bool isLinear, const GX::Pattern::HatchTran* hatchTran);
typedef	void	GSM2D_CALL	API_HatchBorderEndProc (void);
typedef	bool	GSM2D_CALL	API_HatchLinesBegProc (bool doFrame, short fillInd, short fillPen, short fillbkgPen, short determination,
											   const GS_RGBColor* foreRgb, const GS_RGBColor* bkgRgb, short transparency,
											   bool isGradient, bool isLinear, const GX::Pattern::HatchTran* hatchTran);
typedef	void	GSM2D_CALL	API_HatchLinesEndProc (void);

}	/* extern "C" */

#endif
