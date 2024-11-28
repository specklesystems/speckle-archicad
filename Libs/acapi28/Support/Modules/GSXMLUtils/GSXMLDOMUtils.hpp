// *********************************************************************************************************************
// File:			GSXMLDOMUtils.hpp
//
// Description:		XML DOM I/O related utility functions
//
// Project:			ARCHICAD, Plotmaker
//
// Namespace:		GSXMLUtils
//
// Contact person:	PA, CSF
//
// SG compatible
// *********************************************************************************************************************

#ifndef GSXMLDOMUTILS_HPP
#define GSXMLDOMUTILS_HPP

#pragma once

#if defined (_INC_WINDOWSX)
	#undef GetNextSibling
	#undef GetFirstChild
#endif


// --- Includes --------------------------------------------------------------------------------------------------------

#include "Definitions.hpp"
#include "GSXMLUtilsExport.hpp"

#include "xercesc/dom/DOMException.hpp"

#include "UniString.hpp"
#include "XStr.h"

// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace GS {
	class String;
}

XERCES_CPP_NAMESPACE_BEGIN

class DOMNode;
class DOMDocument;
class DOMElement;

XERCES_CPP_NAMESPACE_END

XERCES_CPP_NAMESPACE_USE

namespace GSXMLUtils {

	// RAII (Resource Acquisition Is Initialization) for DOMDocument objects
	class GSXMLUTILS_EXPORT DOMDocumentSentry {
		xercesc::DOMDocument* mDoc;

	public:
		explicit DOMDocumentSentry (xercesc::DOMDocument* doc);
		~DOMDocumentSentry ();

		xercesc::DOMDocument*		operator-> ()						{ return mDoc; }
		const xercesc::DOMDocument*	operator-> () const					{ return mDoc; }
		bool						operator== (std::nullptr_t) const	{ return mDoc == nullptr; }
		bool						operator!= (std::nullptr_t) const	{ return mDoc != nullptr; }

	private:
		DOMDocumentSentry (const DOMDocumentSentry&);				// disabled
		DOMDocumentSentry& operator= (const DOMDocumentSentry&);	// disabled
	};


	// Element Traversal Specification (http://www.w3.org/TR/2008/REC-ElementTraversal-20081222/)
	// These are available in Xerces-C++ 3.1.1 as member functions of xercesc::DOMElement.
	// This is a simplified implementation: Entity Reference Nodes are not traversed.
	GSXMLUTILS_EXPORT xercesc::DOMElement* GetFirstElementChild		 (const xercesc::DOMElement* element);
	GSXMLUTILS_EXPORT xercesc::DOMElement* GetLastElementChild		 (const xercesc::DOMElement* element);
	GSXMLUTILS_EXPORT xercesc::DOMElement* GetPreviousElementSibling (const xercesc::DOMElement* element);
	GSXMLUTILS_EXPORT xercesc::DOMElement* GetNextElementSibling	 (const xercesc::DOMElement* element);
	GSXMLUTILS_EXPORT USize				   GetChildElementCount		 (const xercesc::DOMElement* element);


	//GSXMLUTILS_EXPORT bool	WriteHeader (xercesc::DOMDocument* document);
	GSXMLUTILS_EXPORT bool	WriteNewLine (xercesc::DOMElement* element);
	GSXMLUTILS_EXPORT bool	WriteTabs (xercesc::DOMElement* element, Int32 tabs);
	GSXMLUTILS_EXPORT bool	WriteStyleSheet	(xercesc::DOMDocument* doc, const char* xsl);
	GSXMLUTILS_EXPORT bool	BeginWriteElement (xercesc::DOMElement* parent, xercesc::DOMElement*& elem, const GS::UniString& tagStr);
	GSXMLUTILS_EXPORT bool	BeginWriteElement (xercesc::DOMElement* parent, xercesc::DOMElement*& elem, const GS::String& tagStr);
	GSXMLUTILS_EXPORT bool	EndWriteElement (xercesc::DOMElement* parent, xercesc::DOMElement* elem, const Int32 relDepth);

	GSXMLUTILS_EXPORT void	SkipTextNodes (xercesc::DOMNode*& node);
	GSXMLUTILS_EXPORT void	SkipTextNodes (xercesc::DOMElement*& element);
	GSXMLUTILS_EXPORT void	GetNextSibling (const xercesc::DOMNode* in_node, DOMNode*& out_node);
	GSXMLUTILS_EXPORT void	GetNextSibling (const xercesc::DOMNode* in_node, DOMElement*& out_node);
	GSXMLUTILS_EXPORT void	GetFirstChild (const xercesc::DOMNode* parent_node, DOMNode*& child_node);
	GSXMLUTILS_EXPORT void	GetFirstChild (const xercesc::DOMNode* parent_node, DOMElement*& child_node);
	GSXMLUTILS_EXPORT bool	IsNodeOk (const xercesc::DOMNode* xml_node, const GS::UniString& nodeStr);
	GSXMLUTILS_EXPORT bool	IsNodeOk (const xercesc::DOMNode* xml_node, const GS::String& nodeStr);

	GSXMLUTILS_EXPORT bool	ReadTextNode (const xercesc::DOMNode* elementNode, const GS::UniString& elementStr, GS::UniString& nodeText);
	GSXMLUTILS_EXPORT bool	ReadShortNode (const xercesc::DOMNode* elementNode, const GS::UniString& elementStr, short& number);
	GSXMLUTILS_EXPORT bool	ReadUShortNode (const xercesc::DOMNode* elementNode, const GS::UniString& elementStr, unsigned short& number);
	GSXMLUTILS_EXPORT bool	ReadLongNode (const xercesc::DOMNode* elementNode, const GS::UniString& elementStr, Int32& number);
	GSXMLUTILS_EXPORT bool	ReadULongNode (const xercesc::DOMNode* elementNode, const GS::UniString& elementStr, UInt32& number);
	GSXMLUTILS_EXPORT bool	ReadBooleanNode (const xercesc::DOMNode* elementNode, const GS::UniString& elementStr, bool& boolFlag);

	GSXMLUTILS_EXPORT bool	WriteTextElement (xercesc::DOMElement* parent, const GS::UniString& tagStr, const GS::UniString& valueStr, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteShortElement (xercesc::DOMElement* parent, const GS::UniString& tagStr, const short& number, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteUShortElement (xercesc::DOMElement* parent, const GS::UniString& tagStr, const unsigned short& number, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteLongElement (xercesc::DOMElement* parent, const GS::UniString& tagStr, const Int32& number, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteULongElement (xercesc::DOMElement* parent, const GS::UniString& tagStr, const UInt32& number, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteBooleanElement (xercesc::DOMElement* parent, const GS::UniString& tagStr, const bool& boolFlag, const Int32 depth);

	GSXMLUTILS_EXPORT bool	ReadTextNode (const xercesc::DOMNode* elementNode, const GS::String& elementStr, GS::String& nodeText);
	GSXMLUTILS_EXPORT bool	ReadShortNode (const xercesc::DOMNode* elementNode, const GS::String& elementStr, short& number);
	GSXMLUTILS_EXPORT bool	ReadUShortNode (const xercesc::DOMNode* elementNode, const GS::String& elementStr, unsigned short& number);
	GSXMLUTILS_EXPORT bool	ReadLongNode (const xercesc::DOMNode* elementNode, const GS::String& elementStr, Int32& number);
	GSXMLUTILS_EXPORT bool	ReadULongNode (const xercesc::DOMNode* elementNode, const GS::String& elementStr, UInt32& number);
	GSXMLUTILS_EXPORT bool	ReadBooleanNode (const xercesc::DOMNode* elementNode, const GS::String& elementStr, bool& boolFlag);

	GSXMLUTILS_EXPORT bool	WriteTextElement (xercesc::DOMElement* parent, const GS::String& tagStr, const GS::String& valueStr, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteShortElement (xercesc::DOMElement* parent, const GS::String& tagStr, const short& number, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteUShortElement (xercesc::DOMElement* parent, const GS::String& tagStr, const unsigned short& number, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteLongElement (xercesc::DOMElement* parent, const GS::String& tagStr, const Int32& number, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteULongElement (xercesc::DOMElement* parent, const GS::String& tagStr, const UInt32& number, const Int32 depth);
	GSXMLUTILS_EXPORT bool	WriteBooleanElement (xercesc::DOMElement* parent, const GS::String& tagStr, const bool& boolFlag, const Int32 depth);

}	// namespace GSXMLUtils

#endif
