// *********************************************************************************************************************
// Description:
//
// Module:			GSXML
// Contact person:	HK
//
// *********************************************************************************************************************

#ifndef __XML_UTILITIES_H__
#define __XML_UTILITIES_H__

#include "GSXMLUtilsExport.hpp"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

#include "xercesc/parsers/XercesDOMParser.hpp"

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include "UniCHar.hpp"
#include "UniString.hpp"
#include "XStr.h"
#include "Location.hpp"


XERCES_CPP_NAMESPACE_BEGIN
class Locator;
XERCES_CPP_NAMESPACE_END


XERCES_CPP_NAMESPACE_USE


struct NodeLocationInfo
{
	UInt32 lineNumber = 0;
};


class GSXMLUTILS_EXPORT NodeLocations
{
public:
	NodeLocations ();
	~NodeLocations ();

	void					AddNew (const xercesc::DOMNode* node, UInt32 lineNumber);
	const NodeLocationInfo* Find (const xercesc::DOMNode* node) const;

private:
	NodeLocations (const NodeLocations&);						// disabled
	NodeLocations& operator= (const NodeLocations& source);		// disabled

	struct NLICollection
	{
		enum { NumNLI = 255 };

		NodeLocationInfo		ndLocInfos[NumNLI];
		const xercesc::DOMNode*	nodes[NumNLI];
		NLICollection*			next;
	};

	NLICollection*	nliColl;
	NLICollection*	nliLast;
	UInt32			numFilled;
};


// A validating XML parser (it can check XML validity against an XML Schema)
class GSXMLUTILS_EXPORT ValidatingXMLParser
{
public:
	// Use LoadSchema() to load the XML Schema only once (optional),
	// and use Parse() to parse many XMLs with the preloaded schema.
	bool LoadSchema (const IO::Location&	schemaLoc,
					 NodeLocationInfo*		errLine,
					 GS::UniString*			errMsg);

	// Reads XML document from a file.
	xercesc::DOMDocument* Parse (const IO::Location&					xmlFileLoc,
								 xercesc::XercesDOMParser::ValSchemes	val_sch,
								 bool									entity_refs,
								 NodeLocations*							nl,
								 NodeLocationInfo*						errLine,
								 GS::UniString*							errMsg);

	// Reads XML document from the memory.
	xercesc::DOMDocument* Parse (const unsigned char*					mem,
								 UInt32									size,
								 xercesc::XercesDOMParser::ValSchemes	val_sch,
								 bool									entity_refs,
								 const GS::UniString&					identifier,
								 NodeLocations*							nl,
								 NodeLocationInfo*						errLine,
								 GS::UniString*							errMsg);

	// Reads XML document from the memory.
	xercesc::DOMDocument* Parse (const unsigned char*					mem,
								 UInt32									size,
								 xercesc::XercesDOMParser::ValSchemes	val_sch,
								 bool									entity_refs,
								 const IO::Location&					identifierURI,
								 NodeLocations*							nl,
								 NodeLocationInfo*						errLine,
								 GS::UniString*							errMsg);

private:
	xercesc::DOMDocument* Parse (xercesc::InputSource&					src,
								 xercesc::XercesDOMParser::ValSchemes	val_sch,
								 bool									entity_refs,
								 NodeLocations*							nl,
								 NodeLocationInfo*						errLine,
								 GS::UniString*							errMsg);

	class GSXMLUTILS_EXPORT LineInfoParser : public xercesc::XercesDOMParser
	{
	public:
		LineInfoParser ();
		void SetNodeLocations (NodeLocations* nl);

	private:
		NodeLocations*			nodeLocations;			// if not nullptr, AbstractDOMParser::parse() will collect XML node locations (line numbers) into this
		const xercesc::Locator*	locator;

		void InsertNodeLocInfo ();

		virtual void docCharacters (const XMLCh* const chars, const XMLSize_t length, const bool cdataSection) override;
		virtual void docComment (const XMLCh* const comment) override;
		virtual void startElement (const xercesc::XMLElementDecl& elemDecl, const unsigned int urlId, const XMLCh* const elemPrefix,
								   const xercesc::RefVectorOf<xercesc::XMLAttr>& attrList, const XMLSize_t attrCount, const bool isEmpty, const bool isRoot) override;
		virtual void startEntityReference (const xercesc::XMLEntityDecl& entDecl) override;
	};

	LineInfoParser parser;
};


// Reads XML document from a file.
GSXMLUTILS_EXPORT xercesc::DOMDocument* ParseXMLDoc (const IO::Location&					xmlFileLoc,
													 xercesc::XercesDOMParser::ValSchemes	val_sch,
													 bool									entity_refs,
													 NodeLocations*							nl      = nullptr,
													 NodeLocationInfo*						errLine = nullptr,
													 GS::UniString*							errMsg  = nullptr);


// Reads XML document from the memory.
GSXMLUTILS_EXPORT xercesc::DOMDocument* ParseXMLDoc (const unsigned char*					mem,
													 UInt32									size,
													 xercesc::XercesDOMParser::ValSchemes	val_sch,
													 bool									entity_refs,
													 const GS::UniString&					identifier,
													 NodeLocations*							nl      = nullptr,
													 NodeLocationInfo*						errLine = nullptr,
													 GS::UniString*							errMsg  = nullptr);

GSXMLUTILS_EXPORT xercesc::DOMDocument* ParseXMLDoc (const unsigned char*					mem,
													 UInt32									size,
													 xercesc::XercesDOMParser::ValSchemes	val_sch,
													 bool									entity_refs,
													 const IO::Location&					identifierURI,
													 NodeLocations*							nl      = nullptr,
													 NodeLocationInfo*						errLine = nullptr,
													 GS::UniString*							errMsg  = nullptr);


GSXMLUTILS_EXPORT bool FormatXMLDoc (const xercesc::DOMNode* doc, GS::OChannel* outch, const XMLCh* EncodingName = nullptr, bool force_enc = true);


GSXMLUTILS_EXPORT bool FormatXMLDocUTF8 (const xercesc::DOMNode*, GS::OChannel* outch);


namespace GSXML {
class TypeInfoProvider;
}

// Enumerates XML recursively from given root object
class GSXMLUTILS_EXPORT XMLContentProcessor {
private:
	const GSXML::TypeInfoProvider* attributeProvider = nullptr;
public:
	XMLContentProcessor (const GSXML::TypeInfoProvider* attributeProvider = nullptr);
	virtual ~XMLContentProcessor ();

	const GSXML::TypeInfoProvider*		GetAttributeProvider () const;

	virtual void	NameFound	  (const GS::UniString& fieldName);
	virtual void	BoolFound	  (bool value);
	virtual void	IntFound      (Int64 value);
	virtual void	UIntFound     (UInt64 value);
	virtual void	RealFound     (double value);
	virtual void	StringFound   (const GS::UniString& value);
	virtual void	ObjectEntered ();
	virtual void	ObjectExited  ();
	virtual void	ListEntered   ();
	virtual void	ListExited    ();
};

GSXMLUTILS_EXPORT GSErrCode	EnumerateXML (const xercesc::DOMNode* xmlDocument, XMLContentProcessor& processor);


#endif
