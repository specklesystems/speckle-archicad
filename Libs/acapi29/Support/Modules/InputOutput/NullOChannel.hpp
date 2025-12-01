// *****************************************************************************
//                            Class NullOChannel
//
// Module: IO
// Namespace: IO
// Contact person: HK
//
// *****************************************************************************


#if !defined NULLOCHANNEL_HPP
#define NULLOCHANNEL_HPP

#include "IOBase.hpp"
#include "OChannelAdapter.hpp"


namespace IO {

class IO_DLL_EXPORT NullOChannel: public GS::OChannelAdapter,
								  private GS::OutputBuffer::BinOutput
{
	UInt64 size;

	NullOChannel (const NullOChannel& source);
	NullOChannel& operator= (const NullOChannel& source);

	virtual GSErrCode InternalWrite (const char* source, USize nOfCharToWrite, USize* written) override;

public:
	NullOChannel ();

	UInt64 GetDataSize () const;

	virtual void SetDefaultOutputProtocol () override;
};

}


#endif
