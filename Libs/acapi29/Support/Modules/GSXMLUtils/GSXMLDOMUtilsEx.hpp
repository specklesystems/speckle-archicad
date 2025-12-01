// *********************************************************************************************************************
// File:			GSXMLDOMUtilsEx.hpp
//
// Description:		XML DOM I/O related utility functions
//
// Project:			ARCHICAD
//
// Namespace:		GSXMLUtils
//
// Contact person:	RA
//
// SG compatible
// *********************************************************************************************************************

#ifndef GSXMLDOMUTILSEX_HPP
#define GSXMLDOMUTILSEX_HPP

#pragma once

#if defined (_INC_WINDOWSX)
	#undef GetNextSibling
	#undef GetFirstChild
#endif


// --- Includes --------------------------------------------------------------------------------------------------------

#include "GSXMLDOMUtils.hpp"

#include "Definitions.hpp"
#include "GSXMLUtilsExport.hpp"

#include "UniCHar.hpp"
#include "String.hpp"
#include "UniString.hpp"
#include "XMLUtils.h"

namespace GS {
	template<class T> class VAArray;
}

// --- Predeclarations -------------------------------------------------------------------------------------------------

XERCES_CPP_NAMESPACE_BEGIN

class DOMNode;
class DOMDocument;
class DOMElement;

XERCES_CPP_NAMESPACE_END

XERCES_CPP_NAMESPACE_USE

namespace GSXMLUtils {

	class GSXMLUTILS_EXPORT ConvException
	{
	public:
		ConvException () = default;
		ConvException (const GS::UniString& message, const xercesc::DOMNode* node);
		explicit ConvException (const GS::UniString& message, const NodeLocationInfo* nli = nullptr);
		explicit ConvException (const char* message, const NodeLocationInfo* nli = nullptr);

		void	StoreErrLoc (const xercesc::DOMNode* nd);

		GS::UniString		msg;
		NodeLocationInfo	nli;
	};

	class WarningData
	{
		GS::UniString	mMessage;
		Int32			mLine;

	public:
		WarningData ()										   : mMessage (),		 mLine (0)		{}
		WarningData (const GS::UniString& message, Int32 line) : mMessage (message), mLine (line)	{}

		void			SetMessage	(const GS::UniString& message)	{ mMessage = message;	}
		void			SetLine		(Int32 line)					{ mLine = line;			}
		GS::UniString	GetMessage	(void) const					{ return mMessage;		}
		Int32			GetLine		(void) const					{ return mLine;			}
	};

	typedef GS::VAArray<WarningData> Warnings;

	struct BitNames {
		UInt32		bit;
		const char*	name;
	};

	GSXMLUTILS_EXPORT char*		UnicodeToString		(const GS::UniString dstr, bool lossyConv = false);

	GSXMLUTILS_EXPORT void		CutTabSpace		(char *&ch);

	GSXMLUTILS_EXPORT void		CutWhSpace		(char *&ch);
	GSXMLUTILS_EXPORT void		CutWhSpaceU		(GS::UniChar::Layout *&ch);

	GSXMLUTILS_EXPORT UInt32	GetIntNum		(const char *intStr);
	GSXMLUTILS_EXPORT Int32		GetSignedLong	(const char *longStr);
	GSXMLUTILS_EXPORT UInt32	GetULong		(const char *ulStr);
	GSXMLUTILS_EXPORT double	GetDouble		(const char *dbStr);
	GSXMLUTILS_EXPORT char *	GetStringValue	(char *s);
	GSXMLUTILS_EXPORT GS::UniChar::Layout * GetStringValueU (GS::UniChar::Layout *s);

	GSXMLUTILS_EXPORT void		NewLine		(xercesc::DOMElement* elem);
	GSXMLUTILS_EXPORT void		Tabs		(xercesc::DOMElement* parent, int tabs);
	GSXMLUTILS_EXPORT void		CorrectCDATA	(GS::UniString& cdataStr);
	GSXMLUTILS_EXPORT void		MakeItGDLString (GS::UniString& str);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewTag (xercesc::DOMElement* parent,
								 const char *tagName,
								 const char *text,
								 int tabs,
								 bool cdata = false,
								 const GS::UniChar::Layout *layoutText = nullptr);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewULongTag	(xercesc::DOMElement* parent, const char *tagName, UInt32 ul, int tabs);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewSLongTag	(xercesc::DOMElement* parent, const char *tagName, Int32 sl, int tabs);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewDoubleTag (xercesc::DOMElement* parent, const char *tagName, double d, int tabs);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewStringWLenTag (xercesc::DOMElement* parent, const char *tagName, const GS::uchar_t *text, Int32 len, int tabs);
	GSXMLUTILS_EXPORT void SetSLongAttr		(xercesc::DOMElement* el, const char *attrName, Int32 sl);
	GSXMLUTILS_EXPORT void SetULongAttr		(xercesc::DOMElement* el, const char *attrName, UInt32 ul);
	GSXMLUTILS_EXPORT void SetBooleanAttr	(xercesc::DOMElement* el, const char *attrName, bool b);
	GSXMLUTILS_EXPORT void SetLegacyBooleanAttr	(xercesc::DOMElement* el, const char *attrName, bool b);
	GSXMLUTILS_EXPORT void WriteBits (xercesc::DOMElement* parent, const char *tagName, UInt32 val, const BitNames *bitNames, int tabs);

	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewBoolTag	 (xercesc::DOMElement* parent, const char* tagName, bool b, int tabs);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewLegacyBoolTag (xercesc::DOMElement* parent, const char* tagName, bool b, int tabs);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewStringTag (xercesc::DOMElement* parent, const char* tagName, const char* text, int tabs);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewStringTag (xercesc::DOMElement* parent, const char* tagName, const GS::UniChar::Layout* text, int tabs);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewTextTag	 (xercesc::DOMElement* parent, const char* tagName, const char* text, int tabs);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewTextTag	 (xercesc::DOMElement* parent, const GS::UniString& tagName, const GS::UniString& textContent, Int32 tabs);

	GSXMLUTILS_EXPORT bool		GetBooleanAttr	(const xercesc::DOMElement* elem, const GS::UniString& attr);
	GSXMLUTILS_EXPORT UInt32	GetULongAttr	(const xercesc::DOMElement* elem, const GS::UniString& attr);
	GSXMLUTILS_EXPORT Int32		GetSLongAttr	(const xercesc::DOMElement* elem, const GS::UniString& attr);
	GSXMLUTILS_EXPORT void		ConvertCDATA	(GS::UniString &str);
	GSXMLUTILS_EXPORT GS::UniString	GetCDATANodeUniString (const xercesc::DOMElement* elem);
	GSXMLUTILS_EXPORT char *	GetCDATANode	(const xercesc::DOMElement* elem, Warnings* warnings);
	GSXMLUTILS_EXPORT GS::UniChar::Layout*	GetCDATANodeU	(const xercesc::DOMElement* elem, Warnings* warnings);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	GetNextTag		(xercesc::DOMNode*& node);
	GSXMLUTILS_EXPORT char*					GetTagText		(const xercesc::DOMElement* tag);
	GSXMLUTILS_EXPORT GS::UniString			GetTagTextU		(const xercesc::DOMElement* tag);
	GSXMLUTILS_EXPORT Int32					GetSLongTag		(const xercesc::DOMElement* tag);
	GSXMLUTILS_EXPORT UInt32				GetULongTag		(const xercesc::DOMElement* tag);
	GSXMLUTILS_EXPORT double				GetDoubleTag	(const xercesc::DOMElement* tag);
	GSXMLUTILS_EXPORT bool					GetBoolTag		(const xercesc::DOMElement* tag);
	GSXMLUTILS_EXPORT char*					GetStringTag	(const xercesc::DOMElement* tag, Warnings* warnings);
	GSXMLUTILS_EXPORT GS::UniChar::Layout*	GetStringTagU	(const xercesc::DOMElement* tag, Warnings* warnings);

	//*/

}	// namespace GSXMLUtils

#endif
