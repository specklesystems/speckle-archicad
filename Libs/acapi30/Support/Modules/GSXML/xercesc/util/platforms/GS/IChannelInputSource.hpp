// *********************************************************************************************************************
// Description:		InputSource adapter for IChannel
//
// Module:			GSXML
// Namespace:		GSXML
// Contact person:	FM
//
// *********************************************************************************************************************

#if !defined(ICHANNELINPUTSOURCE_HPP)
#define ICHANNELINPUTSOURCE_HPP

#include "xercesc/sax/InputSource.hpp"

namespace GS { class IChannel; }

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
class XMLPARSER_EXPORT IChannelInputSource : public xercesc::InputSource
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
    IChannelInputSource
    (
		GS::IChannel&		channel
    );

    //@}

    /** @name Destructor */
    //@{
    ~IChannelInputSource();
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
    virtual xercesc::BinInputStream* makeStream() const override;

    //@}
private:
	GS::IChannel& fInputChannel;
};

} // namespace GSXML

#endif
