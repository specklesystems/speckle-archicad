
// *********************************************************************************************************************
// Description:		Build a xerces DOM tree
//
// Module:			GSXMLUtils
// Namespace:		GSXML
// Contact person:	TaB
//
// SG compatible
// *********************************************************************************************************************

#ifndef	_GSXML_DOM_BUILDER_HPP_
#define	_GSXML_DOM_BUILDER_HPP_

// from GSRoot
#include "XMLChannel.hpp"

// from IO
#include "Location.hpp"

// from GSXML
#include "GSXMLUtilsExport.hpp"


namespace GS {
	class OChannel;
}

namespace xercesc_3_0 {
	class DOMElement;
	class DOMDocument;
}

namespace xercesc = xercesc_3_0;


namespace GSXML {

	DECLARE_EXCEPTION_CLASS (DOMBuilderException, GS::RunTimeErrorException, ErrIO, GSXMLUTILS_EXPORT);

	class GSXMLUTILS_EXPORT DOMBuilder : public GS::XMLOChannel {
	private:
		struct Message {
			GS::UniString	message;
			Int32			lineNum;

			Message (GS::UniString message, Int32 lineNum) : message (message), lineNum (lineNum) {}
		};

	private:
		IO::Location			fileLocation;
		xercesc::DOMDocument*	document;			//	DOM data
		xercesc::DOMElement*	actElement;

		GS::ClassVersion		xmlShemaVersion;	//	additional data
		GS::Array<Message>		messages;

		Int32					nLines;				//	format data
		Int32					depth;
		bool					autoTabsEnabled;
		bool					emptyNode;

		bool					owner;				// document release need or not
		bool					exportDoc;			// document export need or not
		bool					replaceCRInUnistring;
		bool					baseNodeIsSet;

	public:
		enum OwnershipType { OriginalOwnership, PassOwnership };

		DOMBuilder (xercesc::DOMDocument* doc, xercesc::DOMElement* elementToAppend, OwnershipType ownership, Int32 tabDepth);	// deprecated
		DOMBuilder (const char* topLevelTagName, bool tabsEnabled = true);
		DOMBuilder (const GS::XMLNoTopLevelTagType, bool tabsEnabled = true);													// deprecated
		DOMBuilder (const IO::Location& location, const char* topLevelTagName, bool tabsEnabled = true);
		DOMBuilder (const IO::Location& location, const GS::XMLNoTopLevelTagType, bool tabsEnabled = true);						// deprecated

	private:
		DOMBuilder (const DOMBuilder& source);							//	Not Implemented
		DOMBuilder& operator= (const DOMBuilder& source);				//	Not Implemented

	public:
		virtual ~DOMBuilder ();

		virtual void			SetXMLShemaVersion (const GS::ClassVersion& shemaVersion)					override;
		virtual void			GetXMLShemaVersion (GS::ClassVersion& shemaVersion)							override;

		virtual bool			GetLocation (IO::Location& fileLoc)											override;	//	Not Implemented

		virtual GSErrCode		WriteStartDocument ()														override;
		virtual GSErrCode		WriteEndDocument ()															override;

		virtual GSErrCode		WriteStartElement (const char* tagName)										override;
		virtual GSErrCode		WriteEndElement ()															override;

		virtual GSErrCode		WriteXML (const char* tagName, char c)										override;
		virtual GSErrCode		WriteXML (const char* tagName, unsigned char c)								override;
		virtual GSErrCode		WriteXML (const char* tagName, short s)										override;
		virtual GSErrCode		WriteXML (const char* tagName, unsigned short s)							override;
		virtual GSErrCode		WriteXML (const char* tagName, int i)										override;
		virtual GSErrCode		WriteXML (const char* tagName, unsigned int i)								override;
		virtual GSErrCode		WriteXML (const char* tagName, long l)										override;
		virtual GSErrCode		WriteXML (const char* tagName, unsigned long l)								override;
		virtual GSErrCode		WriteXML (const char* tagName, Int64 i)										override;
		virtual GSErrCode		WriteXML (const char* tagName, UInt64 i)									override;
		virtual GSErrCode		WriteXML (const char* tagName, const GS::UniString& uStr)					override;
		virtual GSErrCode		WriteXML (const char* tagName, const GS::Guid& guid)						override;
		virtual GSErrCode		WriteXMLTextNode (const GS::UniString& uStr)								override;
		virtual GSErrCode		WriteXMLCDATAString (const GS::UniString& uStr)								override;
		virtual GSErrCode		WriteXMLVersionAttr (const GS::ClassVersion& cv)							override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, char c)									override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, unsigned char c)						override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, short s)								override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, unsigned short s)						override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, Int32 i)								override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, UInt32 i)								override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, Int64 i)								override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, UInt64 i)								override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, const GS::UniString& uStr)				override;
		virtual GSErrCode		WriteXMLAttr (const char* attrName, const GS::Guid& guid)					override;

		virtual GSErrCode		WriteComment (const GS::UniString& commentText)								override;

		virtual void			AddMessage (const GS::UniString& msg)										override;
		virtual Int32			GetNumberOfMessage (void)													override;
		virtual void			GetMessage (Int32 msgIdx, GS::UniString& msg, Int32& lineNum)				override;

		virtual ErrorStatus		GetErrorStatus (void)														override;
		virtual void			ClearErrorStatus (void)														override;

		virtual void			SetAutoTabsHint (bool value)												override;
		virtual void			SetReplaceCR (bool set)														override;
		virtual bool			GetReplaceCR (void)															override;

	public:
		virtual void					Export (GS::OChannel& oChannel, bool IncludeXMLDeclaration = true);
		virtual GS::UniString			Export (bool includeXMLDeclaration = true);
		virtual xercesc::DOMDocument*	GetDOMDocument (void);
		virtual xercesc::DOMElement*	GetActualNode (void);

	private:
		IO::Location			NewScratchFileLocation () const;
		void					ConstructInternal (const IO::Location& location,
												   const bool exportToLocation,
												   const char* topLevelTagName,
												   const bool tabsEnabled);
		void					ExportInternal (std::function<void (const char*, USize)> doExport, bool includeXMLDeclaration = true);
		virtual void			WriteNewLineAndTabs (UInt32 nTabs);

	public:

		void					Export (std::function<void (const char*, USize)> doExport, bool includeXMLDeclaration = true);
	};

}

#endif
