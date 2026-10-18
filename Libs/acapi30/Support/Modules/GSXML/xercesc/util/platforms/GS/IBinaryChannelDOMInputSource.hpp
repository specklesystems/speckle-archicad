// *********************************************************************************************************************
// Description:		DOMInputSource adapter for IBinaryChannel
//
// Module:			GSXML
// Namespace:		GSXML
// Contact person:	FM
//
// *********************************************************************************************************************

#if !defined(IBINARYCHANNELDOMINPUTSOURCE_HPP)
#define IBINARYCHANNELDOMINPUTSOURCE_HPP

// bga #include <xercesc/dom/DOMInputSource.hpp>
#include <xercesc/sax/InputSource.hpp>

namespace GS { class IBinaryChannel; }

XERCES_CPP_NAMESPACE_BEGIN
class BinInputStream;
XERCES_CPP_NAMESPACE_END

namespace GSXML {
/**
 *  This class is a derivative of the standard InputSource class. It provides
 *  for the parser access to data which is referenced via a local file path,
 *  as apposed to remote file or URL. This is the most efficacious mechanism
 *  by which local files can be parsed, since the parse knows that it refers
 *  to a local file and will make no other attempts to interpret the passed
 *  path.
 *
 *  The path provided can either be a fully qualified path or a relative path.
 *  If relative, it will be completed either relative to a passed base path
 *  or relative to the current working directory of the process.
 *
 *  As with all InputSource derivatives. The primary objective of an input
 *  source is to create an input stream via which the parser can spool in
 *  data from the referenced source.
 */
class XMLPARSER_EXPORT IBinaryChannelDOMInputSource : public xercesc::InputSource
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------

    /** @name Constructors */
    //@{

    /**
     *  * A local file input source requires a path to the file to load. This
     *  * can be provided either as a fully qualified path, a path relative to
     *  * the current working directly, or a path relative to a provided base
     *  * path.
     *  *
     *  * The completed path will become the system id of this input source.
     *  * The constructors don't take any public id for local files, but you
     *  * still set them via the parent class' setPublicId() method of course.
     *  *
     *  * This constructor takes an explicit base path and a possibly relative
     *  * path. If the relative path is seen to be fully qualified, it is used
     *  * as is. Otherwise, it is made relative to the passed base path.
     *  *
     *  * @param  basePath    The base path from which the passed relative path
     *  *                     will be based, if the relative part is indeed
     *  *                     relative.
     *  *
     *  * @param  relativePath    The relative part of the path. It can actually
     *  *                         be fully qualified, in which case it is taken
     *  *                         as is.
     *  * @exception XMLException If the path is relative and doesn't properly
     *  *            resolve to a file.
     */
    IBinaryChannelDOMInputSource
    (
		GS::IBinaryChannel&		channel
    );

    //@}

    /** @name Destructor */
    //@{
    ~IBinaryChannelDOMInputSource();
    //@}


    // -----------------------------------------------------------------------
    //  Virtual input source interface
    // -----------------------------------------------------------------------

    /** @name Virtual methods */
    //@{

    /**
     * This method will return a binary input stream derivative that will
     * parse from the local file indicatedby the system id.
     *
     * @return A dynamically allocated binary input stream derivative that
     *         can parse from the file indicated by the system id.
     */
    virtual xercesc::BinInputStream* makeStream() const;



    // -----------------------------------------------------------------------
    /** @name Getter methods */
    //@{
  /**
   *  * <p><b>"Experimental - subject to change"</b></p>
   *  *
   *  * An input source can be set to force the parser to assume a particular
   *  * encoding for the data that input source reprsents, via the setEncoding()
   *  * method. This method will delegate to the wrapped input source to return
   *  * name of the encoding that is to be forced. If the encoding has never
   *  * been forced, it returns a null pointer.
   *  *
   *  * @return The forced encoding, or null if none was supplied.
   *  * @see #setEncoding
   */
    const XMLCh* getEncoding() const;


  /**
   *  * <p><b>"Experimental - subject to change"</b></p>
   *  *
   *  * Get the public identifier for this input source. Delegated to the
   *  * wrapped input source object.
   *  *
   *  * @return The public identifier, or null if none was supplied.
   *  * @see #setPublicId
   */
    const XMLCh* getPublicId() const;


  /**
   *  * <p><b>"Experimental - subject to change"</b></p>
   *  *
   *  * Get the system identifier for this input source. Delegated to the
   *  * wrapped input source object.
   *  *
   *  * <p>If the system ID is a URL, it will be fully resolved.</p>
   *  *
   *  * @return The system identifier.
   *  * @see #setSystemId
   */
    const XMLCh* getSystemId() const;

   /**
    *  * Get the base URI to be used for resolving relative URIs to absolute
    *  * URIs. If the baseURI is itself a relative URI, the behavior is
    *  * implementation dependent. Delegated to the wrapped intput source
    *  * object.
    *  *
    *  * <p><b>"Experimental - subject to change"</b></p>
    *  *
    *  * @return The base URI.
    *  * @see #setBaseURI
    *  * @since DOM Level 3
    */
    const XMLCh* getBaseURI() const;

 /**
  *   * <p><b>"Experimental - subject to change"</b></p>
  *   *
  *   * Get the flag that indicates if the parser should issue fatal error if this input source
  *   * is not found. Delegated to the wrapped input source object.
  *   *
  *   * @return True if the parser should issue fatal error if this input source is not found.
  *   *         False if the parser issue warning message instead.
  *   * @see #setIssueFatalErrorIfNotFound
  */
    bool getIssueFatalErrorIfNotFound() const;

    //@}


    // -----------------------------------------------------------------------
    /** @name Setter methods */
    //@{

  /**
   *  * <p><b>"Experimental - subject to change"</b></p>
   *  *
   *  * Set the encoding which will be required for use with the XML text read
   *  * via a stream opened by this input source. This will update the wrapped
   *  * input source object.
   *  *
   *  * <p>This is usually not set, allowing the encoding to be sensed in the
   *  * usual XML way. However, in some cases, the encoding in the file is known
   *  * to be incorrect because of intermediate transcoding, for instance
   *  * encapsulation within a MIME document.
   *  *
   *  * @param encodingStr The name of the encoding to force.
   */
    void setEncoding(const XMLCh* const encodingStr);


  /**
   *  * <p><b>"Experimental - subject to change"</b></p>
   *  *
   *  * Set the public identifier for this input source. This will update the
   *  * wrapped input source object.
   *  *
   *  * <p>The public identifier is always optional: if the application writer
   *  * includes one, it will be provided as part of the location information.</p>
   *  *
   *  * @param publicId The public identifier as a string.
   *  * @see Locator#getPublicId
   *  * @see SAXParseException#getPublicId
   *  * @see #getPublicId
   */
    void setPublicId(const XMLCh* const publicId);

  /**
   *  * <p><b>"Experimental - subject to change"</b></p>
   *  *
   *  * Set the system identifier for this input source. This will update the
   *  * wrapped input source object.
   *  *
   *  * <p>The system id is always required. The public id may be used to map
   *  * to another system id, but the system id must always be present as a fall
   *  * back.</p>
   *  *
   *  * <p>If the system ID is a URL, it must be fully resolved.</p>
   *  *
   *  * @param systemId The system identifier as a string.
   *  * @see #getSystemId
   *  * @see Locator#getSystemId
   *  * @see SAXParseException#getSystemId
   */
    void setSystemId(const XMLCh* const systemId);

   /**
    * Set the base URI to be used for resolving relative URIs to absolute
    * URIs. If the baseURI is itself a relative URI, the behavior is
    * implementation dependent. This will update the wrapped input source
    * object.
    *
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * @param baseURI The base URI.
    * @see #getBaseURI
    * @since DOM Level 3
    */
    void setBaseURI(const XMLCh* const baseURI);

  /**
   *  * <p><b>"Experimental - subject to change"</b></p>
   *  *
   *  * Indicates if the parser should issue fatal error if this input source
   *  * is not found.  If set to false, the parser issue warning message
   *  * instead. This will update the wrapped input source object.
   *  *
   *  * @param flag  True if the parser should issue fatal error if this input
   *  *              source is not found.
   *  *              If set to false, the parser issue warning message instead.
   *  *              (Default: true)
   *  *
   *  * @see #getIssueFatalErrorIfNotFound
   */
    void setIssueFatalErrorIfNotFound(const bool flag);

   /**
    * Called to indicate that this DOMInputSource is no longer in use
    * and that the implementation may relinquish any resources associated with it.
    *
    * Access to a released object will lead to unexpected result.
    */
    void              release();

    //@}


private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    IBinaryChannelDOMInputSource(const IBinaryChannelDOMInputSource&);
    IBinaryChannelDOMInputSource& operator=(const IBinaryChannelDOMInputSource&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    GS::IBinaryChannel& fInputChannel;


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fEncoding
    //      This is the encoding to use. Usually this is null, which means
    //      to use the information found in the file itself. But, if set,
    //      this encoding will be used without question.
    //
    //  fPublicId
    //      This is the optional public id for the input source. It can be
    //      null if none is desired.
    //
    //  fSystemId
    //      This is the system id for the input source. This is what is
    //      actually used to open the source.
    //
    //  fFatalErrorIfNotFound
    // -----------------------------------------------------------------------
    xercesc::MemoryManager* const fMemoryManager;
    XMLCh*         fEncoding;
    XMLCh*         fPublicId;
    XMLCh*         fSystemId;
    XMLCh*         fBaseURI;
    bool           fFatalErrorIfNotFound;

};

} // namespace GSXML

#endif
