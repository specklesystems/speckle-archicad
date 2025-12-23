// *****************************************************************************
//
//                        OBinarySubChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_OBINARYSUBCHANNEL_HPP
#define GS_OBINARYSUBCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"FilterOBinaryChannel.hpp"


namespace GS {

// === Class OBinarySubChannel =================================================

class GSROOT_DLL_EXPORT OBinarySubChannel : public FilterOBinaryChannel {
public:
						OBinarySubChannel (OBinaryChannel&			oc);
						OBinarySubChannel (const OBinaryChannelRef&	ocr);
	virtual				~OBinarySubChannel ();

	virtual void			Write (const char* source, USize nOfCharToWrite) override = 0;
	virtual void			Flush () override = 0;
	virtual void			Close () override = 0;

private:
							OBinarySubChannel (const OBinarySubChannel& source);	// disabled
	OBinarySubChannel&		operator= (const OBinarySubChannel& source);			// disabled
};


// ___ Class OBinarySubChannel __________________________________________________

}	// namespace GS


#endif
