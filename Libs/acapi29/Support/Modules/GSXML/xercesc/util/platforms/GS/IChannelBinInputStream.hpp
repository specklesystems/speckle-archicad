// *********************************************************************************************************************
// Description:		BinInputStream adapter for IChannel
//
// Module:			GSXML
// Namespace:		GSXML
// Contact person:	FM
//
// *********************************************************************************************************************

#if !defined(ICHANNELBININPUTSTREAM_HPP)
#define ICHANNELBININPUTSTREAM_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/util/PlatformUtils.hpp>

namespace GS { class IChannel; }

namespace GSXML {

class XMLUTIL_EXPORT IChannelBinInputStream : public XERCES_CPP_NAMESPACE::BinInputStream
{
public :
			IChannelBinInputStream (GS::IChannel&	channel);
    virtual ~IChannelBinInputStream();

    XMLFilePos curPos() const;
    XMLSize_t readBytes
    (
                XMLByte* const  toFill
        , const XMLSize_t		maxToRead
    );

    virtual const XMLCh* getContentType() const ;

private :
	GS::IChannel&	fChannel;
	unsigned int	fCurrentPos;
};

} // namespace GSXML

#endif
