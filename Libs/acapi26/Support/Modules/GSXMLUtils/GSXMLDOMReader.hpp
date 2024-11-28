// *********************************************************************************************************************
// Description:		Read a xerces DOM tree
//
// Module:			GSXMLUtils
// Namespace:		GSXML
// Contact person:	TaB
//
// SG compatible
// *********************************************************************************************************************

#ifndef	_GSXML_DOM_READER_HPP_
#define	_GSXML_DOM_READER_HPP_

// from GSRoot
#include "Owner.hpp"
#include "XMLChannel.hpp"
#include "GSException.hpp"

// from GSXML
#include "GSXMLUtilsExport.hpp"

namespace GS {
	class IChannel;
}
namespace IO {
	class Location;
}

namespace xercesc_3_0 {
	class DOMElement;
	class DOMDocument;
}

namespace xercesc = xercesc_3_0;

class NodeLocations;

namespace GSXML {
	DECLARE_EXCEPTION_CLASS (DOMReaderException, GS::RunTimeErrorException, ErrIO, GSXMLUTILS_EXPORT);

	class GSXMLUTILS_EXPORT DOMReader : public GS::XMLIChannel {
	private:
		struct Message {
			GS::UniString	message;
			UInt32			lineNum;

			Message (GS::UniString message, UInt32 lineNum) : message (message), lineNum (lineNum) {}
		};

		xercesc::DOMDocument*			actDocument;
		xercesc::DOMElement*			actElement;
		GS::ClassVersion				xmlShemaVersion;
		GS::Array<Message>				messages;
		GS::PlatformSign				channelPlatform;
		GS::XMLIChannel::ErrorStatus	errStatus;
		GS::XMLTokenType				actTokenType;
		GS::Owner<NodeLocations>		nodeLocations;
		bool							messagesHandled;

	public:
		DOMReader (xercesc::DOMElement* startNode, const char* topLevelTagName = nullptr);				// deprecated
		DOMReader (const unsigned char* xmlInMemory, USize xmlLength, const char* topLevelTagName);
		DOMReader (const unsigned char* xmlInMemory, USize xmlLength, const GS::XMLNoTopLevelTagType);	// deprecated
		DOMReader (const IO::Location& fileLoc, const char* topLevelTagName);
		DOMReader (const IO::Location& fileLoc, const GS::XMLNoTopLevelTagType);						// deprecated
		virtual ~DOMReader ();

		virtual void SetXMLShemaVersion (const GS::ClassVersion& shemaVersion)							override;
		virtual void GetXMLShemaVersion (GS::ClassVersion& shemaVersion)								override;

		virtual bool GetLocation (IO::Location& fileLoc)												override;

		GS::XMLTokenType	GetTokenType (void)															override;
		GS::XMLTokenType	GetNextTokenType (void)														override;
		GS::XMLTokenType	GetTokenTypeName (GS::UniString& name)										override;
		GS::XMLTokenType	GetNextTokenTypeName (GS::UniString& name)									override;

		virtual GSErrCode	ReadStartElement (const char* tagName)										override;
		virtual GSErrCode	ReadEndElement (const char* tagName)										override;
		virtual GSErrCode	ReadToken (unsigned int tokenType)											override;

		virtual bool		HasXMLTag (const char* tagName)												override;
		virtual GSErrCode	ReadXML (const char* tagName, char& c)										override;
		virtual GSErrCode	ReadXML (const char* tagName, unsigned char& c)								override;
		virtual GSErrCode	ReadXML (const char* tagName, bool& b)										override;
		virtual GSErrCode	ReadXML (const char* tagName, short& s)										override;
		virtual GSErrCode	ReadXML (const char* tagName, unsigned short& s)							override;
		virtual GSErrCode	ReadXML (const char* tagName, int& i)										override;
		virtual GSErrCode	ReadXML (const char* tagName, unsigned int& i)								override;
		virtual GSErrCode	ReadXML (const char* tagName, long& l)										override;
		virtual GSErrCode	ReadXML (const char* tagName, unsigned long& l)								override;
		virtual GSErrCode	ReadXML (const char* tagName, Int64& i)										override;
		virtual GSErrCode	ReadXML (const char* tagName, UInt64& i)									override;
		virtual GSErrCode	ReadXML (const char* tagName, float& f)										override;
		virtual GSErrCode	ReadXML (const char* tagName, double& d)									override;
		virtual GSErrCode	ReadXML (const char* tagName, char* cStr, UInt32 length)					override;
		virtual GSErrCode	ReadXML (const char* tagName, GS::UniString& uStr)							override;
		virtual GSErrCode	ReadXML (const char* tagName, GS::Guid& guid)								override;
		virtual GSErrCode	ReadXMLCDATAString (GS::UniString& uStr)									override;

		virtual bool		HasXMLAttr (const char* attrName)											override;
		virtual GSErrCode	ReadXMLVersionAttr (GS::ClassVersion& cv)									override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, char& c)									override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, unsigned char& c)						override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, bool& b)									override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, short& s)								override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, unsigned short& s)						override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, float& f)								override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, double& d)								override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, Int32& i)								override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, UInt32& i)								override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, Int64& i)								override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, UInt64& i)								override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, char* cStr, UInt32 length)				override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, GS::UniString& uStr)						override;
		virtual GSErrCode	ReadXMLAttr (const char* attrName, GS::Guid& guid)							override;

		virtual GS::PlatformSign	GetChannelPlatform (void)											override;
		virtual void				SetChannelPlatform (GS::PlatformSign platform)						override;

		virtual UInt32		GetActLineNumber ()															override;
		virtual void		AddMessage (const GS::UniString& msg)										override;
		virtual Int32		GetNumberOfMessage (void)													override;
		virtual void		GetMessage (Int32 msgIdx, GS::UniString& msg, Int32& lineNum)				override;

		virtual ErrorStatus		GetErrorStatus (void)													override;
		virtual void			ClearErrorStatus (void)													override;

		virtual xercesc::DOMElement*	GetActualNode (void);

	private:
		void				ConstructInternal (xercesc::DOMDocument* document, const char* topLevelTagName, const GS::UniString& errorMessage);
		bool				CheckTopLevelTag (const char* topLevelTagName);
		GS::XMLTokenType	GetNextStartTokenName (GS::UniString& name);
		GSErrCode			ReadTokenWithName (const GS::UniString& name, GS::XMLTokenType type);
		GSErrCode			ReadToken ();

		virtual xercesc::DOMElement* GetFirstElementChild (void);
		virtual xercesc::DOMElement* GetNextElementSibling (void);
		template <typename T> GSErrCode ReadXMLNumberTemplate (const char* tagName, T& t);
		template <typename T> GSErrCode ReadXMLAttrNumberTemplate (const char* tagName, T& t);
	};

} // namespace GSXML



#endif