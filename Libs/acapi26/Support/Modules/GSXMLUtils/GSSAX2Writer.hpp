// *********************************************************************************************************************
// Description:		XML writer class based on the SAX2 api with convience functions.
//
// Module:			GSXML
// Namespace:		GSXML
// Contact person:	FM
//
// *********************************************************************************************************************

#if !defined(GSSAX2WRITER_HPP)
#define GSSAX2WRITER_HPP

// from GSRoot
#include "Channel.hpp"
#include "OBinaryChannel.hpp"
#include "Owner.hpp"
#include "UniString.hpp"
#include "HashTable.hpp"

// from GSUtils
#include "GSXMLUtilsExport.hpp"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

#include <xercesc/sax/DocumentHandler.hpp>
#include <xercesc/internal/VecAttributesImpl.hpp>
#include <xercesc/util/platforms/GS/OChannelXMLFormatTarget.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include "SAX2Writer.hpp"


XERCES_CPP_NAMESPACE_BEGIN
class XMLFormatter;
XERCES_CPP_NAMESPACE_END


namespace GSXML {

class GSXMLUTILS_EXPORT GSSAX2Writer : public xercesc::ContentHandler
{
public:
    class GSXMLUTILS_EXPORT Attrs : public xercesc::Attributes {
    public:
                Attrs ();
                ~Attrs ();
        void    Add (const GS::UniString& attr, const GS::UniString& value);

        virtual XMLSize_t getLength() const ;

        virtual const XMLCh* getURI(const XMLSize_t index) const;
        virtual const XMLCh* getLocalName(const XMLSize_t index) const;
        virtual const XMLCh* getQName(const XMLSize_t index) const;
        virtual const XMLCh* getType(const XMLSize_t index) const;
        virtual const XMLCh* getValue(const XMLSize_t index) const;

        virtual bool getIndex(const XMLCh* const uri, const XMLCh* const localPart, XMLSize_t& index ) const;
        virtual int getIndex(const XMLCh* const uri, const XMLCh* const localPart ) const;
        virtual bool getIndex(const XMLCh* const qName, XMLSize_t& index ) const  ;
        virtual int getIndex(const XMLCh* const qName ) const  ;

        virtual const XMLCh* getType(const XMLCh* const uri, const XMLCh* const localPart ) const;
        virtual const XMLCh* getType(const XMLCh* const qName) const ;

        virtual const XMLCh* getValue(const XMLCh* const qName) const;
        virtual const XMLCh* getValue(const XMLCh* const uri, const XMLCh* const localPart ) const;

    protected:
        GS::Array<xercesc::XMLAttr*>    store;
    };

    GSSAX2Writer (GS::OChannel& ch);
	GSSAX2Writer (GS::OBinaryChannel& ch);

    // convience functions
	void	SimpleElement (const GS::UniString& element, const xercesc::Attributes& attrs, const GS::UniString& text);
	void	SimpleElement (const GS::UniString& element, const GS::UniString& text);

    void    StartDocument (void);
    void    StartElement (const GS::UniString& element);
    void    StartElement (const GS::UniString& element, const xercesc::Attributes& attrs);
    void    Characters (const GS::UniString& text);
    void    EndElement (const GS::UniString& element);
    void    EndDocument (void);

    // low-level SAX2 interface
    virtual void characters (const   XMLCh* const chars, const XMLSize_t length);
    virtual void endDocument ();
    virtual void endElement (const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
    virtual void ignorableWhitespace (const XMLCh* const chars, const XMLSize_t length);
    virtual void processingInstruction (const XMLCh* const target , const XMLCh* const data);
    virtual void setDocumentLocator(const xercesc::Locator* const locator);
    virtual void startDocument();
    virtual void startElement (const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const xercesc::Attributes& attrs);
	virtual void startPrefixMapping (const	XMLCh* const prefix, const XMLCh* const uri);
	virtual void endPrefixMapping (const	XMLCh* const prefix);
	virtual void skippedEntity (const	XMLCh* const name);

    virtual		 ~GSSAX2Writer ();
private:

	void writeTabs ();

	GS::Owner<xercesc::XMLFormatTarget>		formattertarget;
	xercesc::XMLFormatter					formatter;
	GSXML::SAX2Writer						writer;
	Int32									tablevel;
	bool									wasbegin;
};

} // namespace GSXML


#endif
