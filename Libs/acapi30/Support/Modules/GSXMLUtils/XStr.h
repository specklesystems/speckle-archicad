// *********************************************************************************************************************
// Description:
//
// Module:			GSXML
// Contact person:	RA
//
// *********************************************************************************************************************

#ifndef __XSTR_H__
#define __XSTR_H__

#pragma once

#include "UniString.hpp"
#include "String.hpp"
#include "uchar_t.hpp"
#include <xercesc/util/XercesDefs.hpp>

#define XMLStr(str)						(const XMLCh*)L(str)
#define UNISTR_TO_XMLCH_PTR(uniStr)		((const XMLCh*)(const GS::UniChar::Layout*)(uniStr).ToUStr ())
#define STRING_TO_XMLCH_PTR(string)		UNISTR_TO_XMLCH_PTR (GS::UniString ((string).ToCStr ()))
#define CHARPTR_TO_XMLCH_PTR(string)	UNISTR_TO_XMLCH_PTR (GS::UniString (CheckEmptyString (string)))


inline const XMLCh* CheckEmptyString (const XMLCh* xmlStr)
{
	if (xmlStr == nullptr)
		return XMLStr ("");
	else
		return xmlStr;
}


inline const char* CheckEmptyString (const char* str)
{
	if (str == nullptr)
		return "";
	else
		return str;
}


#endif
