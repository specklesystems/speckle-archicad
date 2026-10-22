// *****************************************************************************
//
//                        FilterIBinaryChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_FILTERIBINARYCHANNEL_HPP
#define GS_FILTERIBINARYCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"IBinaryChannel.hpp"
#include	"Ref.hpp"


namespace GS {

// ============================== Class FilterIBinaryChannel ===================

class GSROOT_DLL_EXPORT FilterIBinaryChannel : public IBinaryChannel {
public:
						FilterIBinaryChannel (IBinaryChannel&			ic);
						FilterIBinaryChannel (const IBinaryChannelRef&	icr);
	virtual				~FilterIBinaryChannel () = 0;

	virtual USize			Read (char* destination, USize nOfCharToRead, ReadSomeModeSelector readSomeMode = ReadSomeMode) override;
	virtual UInt64			GetAvailable () const override;
	virtual void			Close () override;

protected:
	IBinaryChannel&			GetBaseChannel ()		{ PRECOND_R_DEPRECATED(ic); return *ic; }
	const IBinaryChannel&	GetBaseChannel () const { PRECOND_R_DEPRECATED(ic);  return *ic; }
private:
							FilterIBinaryChannel (const FilterIBinaryChannel& source);	// disabled
	FilterIBinaryChannel&	operator= (const FilterIBinaryChannel& source);				// disabled

	IBinaryChannel*			ic;
	IBinaryChannelRef		icref;
};


// ______________________________ Class FilterIBinaryChannel ____________________

}	// namespace GS


#endif
