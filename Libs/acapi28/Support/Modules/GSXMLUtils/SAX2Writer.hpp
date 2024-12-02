// *********************************************************************************************************************
// Description:		XML writer class based on the SAX2 api.
//
// Module:			GSXML
// Namespace:		GSXML
// Contact person:	FM
//
// *********************************************************************************************************************

#if !defined(SAX2WRITER_HPP)
#define SAX2WRITER_HPP

#include "GSXMLUtilsExport.hpp"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

#include <xercesc/sax2/ContentHandler.hpp>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

XERCES_CPP_NAMESPACE_BEGIN
class XMLFormatter;
XERCES_CPP_NAMESPACE_END



namespace GSXML {

class GSXMLUTILS_EXPORT SAX2Writer : public xercesc::ContentHandler
{
public :
public:
    /** @name Constructors and Destructor */
    //@{
    /** Default constructor */
    SAX2Writer	( xercesc::XMLFormatter&		output
				, const bool					expandNamespaces);

    /** Destructor */
    virtual ~SAX2Writer();
    //@}

    /** @name The virtual document handler interface */

    //@{
    /**
     * Receive notification of character data.
     *
     * <p>The Parser will call this method to report each chunk of
     * character data.  SAX parsers may return all contiguous character
     * data in a single chunk, or they may split it into several
     * chunks; however, all of the characters in any single event
     * must come from the same external entity, so that the Locator
     * provides useful information.</p>
     *
     * <p>The application must not attempt to read from the array
     * outside of the specified range.</p>
     *
     * <p>Note that some parsers will report whitespace using the
     * ignorableWhitespace() method rather than this one (validating
     * parsers must do so).</p>
     *
     * @param chars The characters from the XML document.
     * @param length The number of characters to read from the array.
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     * @see #ignorableWhitespace
     * @see Locator#Locator
     */
    virtual void characters
    (
        const   XMLCh* const    chars
        , const XMLSize_t    length
    ) override;

    /**
     * Receive notification of the end of a document.
     *
     * <p>The SAX parser will invoke this method only once, and it will
     * be the last method invoked during the parse.  The parser shall
     * not invoke this method until it has either abandoned parsing
     * (because of an unrecoverable error) or reached the end of
     * input.</p>
     *
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     */
    virtual void endDocument () override;

    /**
     * Receive notification of the end of an element.
     *
     * <p>The SAX parser will invoke this method at the end of every
     * element in the XML document; there will be a corresponding
     * startElement() event for every endElement() event (even when the
     * element is empty).</p>
     *
     * @param uri The URI of the asscioated namespace for this element
     * @param localname The local part of the element name
     * @param qname The QName of this element
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     */
    virtual void endElement
	(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	) override;

    /**
     * Receive notification of ignorable whitespace in element content.
     *
     * <p>Validating Parsers must use this method to report each chunk
     * of ignorable whitespace (see the W3C XML 1.0 recommendation,
     * section 2.10): non-validating parsers may also use this method
     * if they are capable of parsing and using content models.</p>
     *
     * <p>SAX parsers may return all contiguous whitespace in a single
     * chunk, or they may split it into several chunks; however, all of
     * the characters in any single event must come from the same
     * external entity, so that the Locator provides useful
     * information.</p>
     *
     * <p>The application must not attempt to read from the array
     * outside of the specified range.</p>
     *
     * @param chars The characters from the XML document.
     * @param length The number of characters to read from the array.
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     * @see #characters
     */
    virtual void ignorableWhitespace
    (
        const   XMLCh* const    chars
        , const XMLSize_t    length
    ) override;

    /**
     * Receive notification of a processing instruction.
     *
     * <p>The Parser will invoke this method once for each processing
     * instruction found: note that processing instructions may occur
     * before or after the main document element.</p>
     *
     * <p>A SAX parser should never report an XML declaration (XML 1.0,
     * section 2.8) or a text declaration (XML 1.0, section 4.3.1)
     * using this method.</p>
     *
     * @param target The processing instruction target.
     * @param data The processing instruction data, or null if
     *        none was supplied.
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     */
    virtual void processingInstruction
    (
        const   XMLCh* const    target
        , const XMLCh* const    data
    ) override;

    /**
     * Receive an object for locating the origin of SAX document events.
     *
     * SAX parsers are strongly encouraged (though not absolutely
     * required) to supply a locator: if it does so, it must supply
     * the locator to the application by invoking this method before
     * invoking any of the other methods in the DocumentHandler
     * interface.
     *
     * The locator allows the application to determine the end
     * position of any document-related event, even if the parser is
     * not reporting an error.  Typically, the application will
     * use this information for reporting its own errors (such as
     * character content that does not match an application's
     * business rules). The information returned by the locator
     * is probably not sufficient for use with a search engine.
     *
     * Note that the locator will return correct information only
     * during the invocation of the events in this interface. The
     * application should not attempt to use it at any other time.
     *
     * @param locator An object that can return the location of
     *                any SAX document event. The object is only
     *                'on loan' to the client code and they are not
     *                to attempt to delete or modify it in any way!
     *
     * @see Locator#Locator
     */
    virtual void setDocumentLocator(const xercesc::Locator* const locator) override;

    /**
     * Receive notification of the beginning of a document.
     *
     * <p>The SAX parser will invoke this method only once, before any
     * other methods in this interface or in DTDHandler (except for
     * setDocumentLocator).</p>
     *
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     */
    virtual void startDocument() override;

    /**
     * Receive notification of the beginning of an element.
     *
     * <p>The Parser will invoke this method at the beginning of every
     * element in the XML document; there will be a corresponding
     * endElement() event for every startElement() event (even when the
     * element is empty). All of the element's content will be
     * reported, in order, before the corresponding endElement()
     * event.</p>
     *
     * <p>Note that the attribute list provided will
     * contain only attributes with explicit values (specified or
     * defaulted): #IMPLIED attributes will be omitted.</p>
     *
     * @param uri The URI of the asscioated namespace for this element
     * @param localname The local part of the element name
     * @param qname The QName of this element
     * @param attrs The attributes attached to the element, if any.
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     * @see #endElement
     * @see Attributes#Attributes
     */
    virtual void startElement
    (
        const   XMLCh* const    uri,
        const   XMLCh* const    localname,
        const   XMLCh* const    qname,
        const   xercesc::Attributes&     attrs
    ) override;

    /**
     * Receive notification of the start of an namespace prefix mapping.
     *
     * <p>By default, do nothing.  Application writers may override this
     * method in a subclass to take specific actions at the start of
     * each namespace prefix mapping.</p>
     *
     * @param prefix The namespace prefix used
     * @param uri The namespace URI used.
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     */
	virtual void startPrefixMapping
	(
		const	XMLCh* const	prefix,
		const	XMLCh* const	uri
	) override;

    /**
     * Receive notification of the end of an namespace prefix mapping.
     *
     * <p>By default, do nothing.  Application writers may override this
     * method in a subclass to take specific actions at the end of
     * each namespace prefix mapping.</p>
     *
     * @param prefix The namespace prefix used
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     */
	virtual void endPrefixMapping
	(
		const	XMLCh* const	prefix
	) override;

    /**
     * Receive notification of a skipped entity
     *
     * <p>The parser will invoke this method once for each entity
     * skipped.  All processors may skip external entities,
     * depending on the values of the features:<br>
     * http://xml.org/sax/features/external-general-entities<br>
     * http://xml.org/sax/features/external-parameter-entities</p>
     *
     * <p>Note: Xerces (specifically) never skips any entities, regardless
     * of the above features.  This function is never called in the
     * Xerces implementation of SAX2.</p>
     *
     * <p>Introduced with SAX2</p>
     *
     * @param name The name of the skipped entity.  If it is a parameter entity,
     * the name will begin with %, and if it is the external DTD subset,
     * it will be the string [dtd].
     * @exception SAXException Any SAX exception, possibly
     *            wrapping another exception.
     */
	virtual void skippedEntity
	(
		const	XMLCh* const	name
	) override;



private :
	const xercesc::Locator*			fLocator;
	const bool                      fExpandNS ;
	xercesc::XMLFormatter&          fFormatter;
};

} // namespace GSXML


#endif
