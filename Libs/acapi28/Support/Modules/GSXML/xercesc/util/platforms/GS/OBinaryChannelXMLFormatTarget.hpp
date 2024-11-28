// *********************************************************************************************************************
// Description:		XMLFormatTarget adapter for OChannel
//
// Module:			GSXML
// Namespace:		GSXML
// Contact person:	FM
//
// *********************************************************************************************************************

#if !defined(OBINARYCHANNELFORMATTER_HPP)
#define OBINARYCHANNELFORMATTER_HPP

#include <xercesc/framework/XMLFormatter.hpp>


namespace GS { class OBinaryChannel; }

namespace GSXML {

/**
 *  This class is a derivative of the standard XMLFormatTarget class. 
 */
class XMLPARSER_EXPORT OBinaryChannelXMLFormatTarget : public xercesc::XMLFormatTarget
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------

    /** @name Constructors */
    //@{

    /**
     *  * 
     *  * @exception XMLException If the path is relative and doesn't properly
     *  *            resolve to a file.
     */
    OBinaryChannelXMLFormatTarget
    (
		GS::OBinaryChannel&		channel
    );

    //@}

    /** @name Destructor */
    //@{
    virtual ~OBinaryChannelXMLFormatTarget();
    //@}


    // -----------------------------------------------------------------------
    //  Virtual input source interface
    // -----------------------------------------------------------------------

    /** @name Virtual methods */
    //@{

    /**
     * This method will write the bytes to an OBinaryChannel stream
     */
    virtual void writeChars
    (
        const   XMLByte* const      toWrite
        , const XMLSize_t        count
        ,       xercesc::XMLFormatter* const formatter
	); // throw GSException, std::bad_alloc

    //@}
private:
	GS::OBinaryChannel& fOutputChannel;
};

}

#endif
