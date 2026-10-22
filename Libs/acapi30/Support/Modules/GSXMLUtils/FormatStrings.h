// *********************************************************************************************************************
// Description:
//
// Module:			GSXML
// Contact person:	HK
//
// *********************************************************************************************************************

#ifndef _FORMAT_STRINGS_H__
#define _FORMAT_STRINGS_H__

// this file was copied from the DOMPrint example of Xerces.


#include <xercesc/util/XMLUniDefs.hpp>

// ---------------------------------------------------------------------------
//	Local const data
//
//	Note: This is the 'safe' way to do these strings. If your compiler supports
//		  L"" style strings, and portability is not a concern, you can use
//		  those types constants directly.
// ---------------------------------------------------------------------------
static const XMLCh	gEndElement[] = { xercesc::chOpenAngle, xercesc::chForwardSlash, xercesc::chNull };
static const XMLCh	gEndPI[] = { xercesc::chQuestion, xercesc::chCloseAngle, xercesc::chNull};
static const XMLCh	gStartPI[] = { xercesc::chOpenAngle, xercesc::chQuestion, xercesc::chNull };
static const XMLCh	gXMLDecl1[] =
{
	xercesc::chOpenAngle, xercesc::chQuestion, xercesc::chLatin_x, xercesc::chLatin_m, xercesc::chLatin_l
		,	xercesc::chSpace, xercesc::chLatin_v, xercesc::chLatin_e, xercesc::chLatin_r, xercesc::chLatin_s, xercesc::chLatin_i
		,	xercesc::chLatin_o, xercesc::chLatin_n, xercesc::chEqual, xercesc::chDoubleQuote, xercesc::chNull
};
static const XMLCh	gXMLDecl2[] =
{
	xercesc::chDoubleQuote, xercesc::chSpace, xercesc::chLatin_e, xercesc::chLatin_n, xercesc::chLatin_c
		,	xercesc::chLatin_o, xercesc::chLatin_d, xercesc::chLatin_i, xercesc::chLatin_n, xercesc::chLatin_g, xercesc::chEqual
		,	xercesc::chDoubleQuote, xercesc::chNull
};
static const XMLCh	gXMLDecl3[] =
{
	xercesc::chDoubleQuote, xercesc::chSpace, xercesc::chLatin_s, xercesc::chLatin_t, xercesc::chLatin_a
		,	xercesc::chLatin_n, xercesc::chLatin_d, xercesc::chLatin_a, xercesc::chLatin_l, xercesc::chLatin_o
		,	xercesc::chLatin_n, xercesc::chLatin_e, xercesc::chEqual, xercesc::chDoubleQuote, xercesc::chNull
};
static const XMLCh	gXMLDecl4[] =
{
	xercesc::chDoubleQuote, xercesc::chQuestion, xercesc::chCloseAngle
		,	xercesc::chLF, xercesc::chNull
};

static const XMLCh	gStartCDATA[] =
{
	xercesc::chOpenAngle, xercesc::chBang, xercesc::chOpenSquare, xercesc::chLatin_C, xercesc::chLatin_D,
		xercesc::chLatin_A, xercesc::chLatin_T, xercesc::chLatin_A, xercesc::chOpenSquare, xercesc::chNull
};

static const XMLCh	gEndCDATA[] =
{
	xercesc::chCloseSquare, xercesc::chCloseSquare, xercesc::chCloseAngle, xercesc::chNull
};
static const XMLCh	gStartComment[] =
{
	xercesc::chOpenAngle, xercesc::chBang, xercesc::chDash, xercesc::chDash, xercesc::chNull
};

static const XMLCh	gEndComment[] =
{
	xercesc::chDash, xercesc::chDash, xercesc::chCloseAngle, xercesc::chNull
};

static const XMLCh	gStartDoctype[] =
{
	xercesc::chOpenAngle, xercesc::chBang, xercesc::chLatin_D, xercesc::chLatin_O, xercesc::chLatin_C, xercesc::chLatin_T,
		xercesc::chLatin_Y, xercesc::chLatin_P, xercesc::chLatin_E, xercesc::chSpace, xercesc::chNull
};
static const XMLCh	gPublic[] =
{
	xercesc::chLatin_P, xercesc::chLatin_U, xercesc::chLatin_B, xercesc::chLatin_L, xercesc::chLatin_I,
		xercesc::chLatin_C, xercesc::chSpace, xercesc::chDoubleQuote, xercesc::chNull
};
static const XMLCh	gSystem[] =
{
	xercesc::chLatin_S, xercesc::chLatin_Y, xercesc::chLatin_S, xercesc::chLatin_T, xercesc::chLatin_E,
		xercesc::chLatin_M, xercesc::chSpace, xercesc::chDoubleQuote, xercesc::chNull
};
static const XMLCh	gStartEntity[] =
{
	xercesc::chOpenAngle, xercesc::chBang, xercesc::chLatin_E, xercesc::chLatin_N, xercesc::chLatin_T, xercesc::chLatin_I,
		xercesc::chLatin_T, xercesc::chLatin_Y, xercesc::chSpace, xercesc::chNull
};
static const XMLCh	gNotation[] =
{
	xercesc::chLatin_N, xercesc::chLatin_D, xercesc::chLatin_A, xercesc::chLatin_T, xercesc::chLatin_A,
		xercesc::chSpace, xercesc::chDoubleQuote, xercesc::chNull
};

#endif
