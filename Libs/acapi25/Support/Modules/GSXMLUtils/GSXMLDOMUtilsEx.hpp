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
		ConvException ();
		ConvException (const GS::UniString& message, const xercesc::DOMNode* node);
		explicit ConvException (const GS::UniString& message, const NodeLocationInfo *nli = nullptr);
		explicit ConvException (const char* message, const NodeLocationInfo *nli = nullptr);
		ConvException (const ConvException &ce);
		virtual ~ConvException ();

		const ConvException& StoreErrLoc (const xercesc::DOMNode* nd);

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
		const char			*name;
	};

	GSXMLUTILS_EXPORT char*		UnicodeToString		(const GS::UniString dstr, bool lossyConv = false) throw (ConvException);

	GSXMLUTILS_EXPORT void		CutTabSpace		(char *&ch);

	GSXMLUTILS_EXPORT void		CutWhSpace		(char *&ch);
	GSXMLUTILS_EXPORT void		CutWhSpaceU		(GS::UniChar::Layout *&ch);

	GSXMLUTILS_EXPORT UInt32	GetIntNum		(const char *intStr)	throw (ConvException);
	GSXMLUTILS_EXPORT Int32		GetSignedLong	(const char *longStr)	throw (ConvException);
	GSXMLUTILS_EXPORT UInt32	GetULong		(const char *ulStr)		throw (ConvException);
	GSXMLUTILS_EXPORT double	GetDouble		(const char *dbStr)		throw (ConvException);
	GSXMLUTILS_EXPORT char *	GetStringValue	(char *s)				throw (ConvException);
	GSXMLUTILS_EXPORT GS::UniChar::Layout * GetStringValueU (GS::UniChar::Layout *s) throw (ConvException);

	GSXMLUTILS_EXPORT void		NewLine		(xercesc::DOMElement* elem)				throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT void		Tabs		(xercesc::DOMElement* parent, int tabs) throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT void		CorrectCDATA	(GS::UniString& cdataStr)		throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT void		MakeItGDLString (GS::UniString& str)			throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewTag (xercesc::DOMElement* parent,
								 const char *tagName,
								 const char *text,
								 int tabs,
								 bool cdata = false,
								 const GS::UniChar::Layout *layoutText = nullptr)		throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewULongTag	(xercesc::DOMElement* parent, const char *tagName, UInt32 ul, int tabs)		throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewSLongTag	(xercesc::DOMElement* parent, const char *tagName, Int32 sl, int tabs)		throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewDoubleTag (xercesc::DOMElement* parent, const char *tagName, double d, int tabs)		throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement* NewStringWLenTag (xercesc::DOMElement* parent, const char *tagName, const GS::uchar_t *text, Int32 len, int tabs)	throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT void SetSLongAttr		(xercesc::DOMElement* el, const char *attrName, Int32 sl)		throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT void SetULongAttr		(xercesc::DOMElement* el, const char *attrName, UInt32 ul)		throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT void SetBooleanAttr	(xercesc::DOMElement* el, const char *attrName, bool b)			throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT void SetLegacyBooleanAttr	(xercesc::DOMElement* el, const char *attrName, bool b)		throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT void WriteBits (xercesc::DOMElement* parent, const char *tagName, UInt32 val, const BitNames *bitNames, int tabs) throw (xercesc::DOMException);

	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewBoolTag	 (xercesc::DOMElement* parent, const char* tagName, bool b, int tabs)									throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewLegacyBoolTag (xercesc::DOMElement* parent, const char* tagName, bool b, int tabs)								throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewStringTag (xercesc::DOMElement* parent, const char* tagName, const char* text, int tabs)								throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewStringTag (xercesc::DOMElement* parent, const char* tagName, const GS::UniChar::Layout* text, int tabs)				throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewTextTag	 (xercesc::DOMElement* parent, const char* tagName, const char* text, int tabs)								throw (xercesc::DOMException);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	NewTextTag	 (xercesc::DOMElement* parent, const GS::UniString& tagName, const GS::UniString& textContent, Int32 tabs)	throw (xercesc::DOMException);

	GSXMLUTILS_EXPORT bool		GetBooleanAttr	(const xercesc::DOMElement* elem, const GS::UniString& attr) throw (ConvException);
	GSXMLUTILS_EXPORT UInt32	GetULongAttr	(const xercesc::DOMElement* elem, const GS::UniString& attr) throw (ConvException);
	GSXMLUTILS_EXPORT Int32		GetSLongAttr	(const xercesc::DOMElement* elem, const GS::UniString& attr) throw (ConvException);
	GSXMLUTILS_EXPORT void		ConvertCDATA	(GS::UniString &str);
	GSXMLUTILS_EXPORT GS::UniString	GetCDATANodeUniString (const xercesc::DOMElement* elem)							throw (ConvException);
	GSXMLUTILS_EXPORT char *	GetCDATANode	(const xercesc::DOMElement* elem, Warnings* warnings)				throw (ConvException);
	GSXMLUTILS_EXPORT GS::UniChar::Layout*	GetCDATANodeU	(const xercesc::DOMElement* elem, Warnings* warnings) throw (ConvException);
	GSXMLUTILS_EXPORT xercesc::DOMElement*	GetNextTag		(xercesc::DOMNode*& node)						throw (ConvException);
	GSXMLUTILS_EXPORT char*					GetTagText		(const xercesc::DOMElement* tag)				throw (ConvException);
	GSXMLUTILS_EXPORT GS::UniString			GetTagTextU		(const xercesc::DOMElement* tag)				throw (ConvException);
	GSXMLUTILS_EXPORT Int32					GetSLongTag		(const xercesc::DOMElement* tag)				throw (ConvException);
	GSXMLUTILS_EXPORT UInt32				GetULongTag		(const xercesc::DOMElement* tag)				throw (ConvException);
	GSXMLUTILS_EXPORT double				GetDoubleTag	(const xercesc::DOMElement* tag)				throw (ConvException);
	GSXMLUTILS_EXPORT bool					GetBoolTag		(const xercesc::DOMElement* tag)				throw (ConvException);
	GSXMLUTILS_EXPORT char*					GetStringTag	(const xercesc::DOMElement* tag, Warnings* warnings) throw (ConvException);
	GSXMLUTILS_EXPORT GS::UniChar::Layout*	GetStringTagU	(const xercesc::DOMElement* tag, Warnings* warnings) throw (ConvException);

	//*/

}	// namespace GSXMLUtils

#endif
