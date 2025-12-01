// *********************************************************************************************************************
// Description:		BinInputStream adapter for IChannel
//
// Module:			GSXML
// Namespace:		GSXML
// Contact person:	FM
//
// *********************************************************************************************************************

#if !defined(IBINARYCHANNELBININPUTSTREAM_HPP)
#define IBINARYCHANNELBININPUTSTREAM_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/util/PlatformUtils.hpp>

namespace GS { class IBinaryChannel; }

namespace GSXML {

class XMLUTIL_EXPORT IBinaryChannelBinInputStream : public XERCES_CPP_NAMESPACE::BinInputStream
{
public :
			IBinaryChannelBinInputStream (GS::IBinaryChannel&	channel);
    virtual ~IBinaryChannelBinInputStream();

    XMLFilePos curPos() const;
    XMLSize_t readBytes
    (
                XMLByte* const  toFill
        , const XMLSize_t		maxToRead
    );

    virtual const XMLCh* getContentType() const;

private :
	GS::IBinaryChannel&	fChannel;
	unsigned int	fCurrentPos;
};

} // namespace GSXML

#endif
