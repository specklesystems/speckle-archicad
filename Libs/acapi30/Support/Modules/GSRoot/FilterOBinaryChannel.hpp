// *****************************************************************************
//
//                        FilterOBinaryChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_FILTEROBINARYCHANNEL_HPP
#define GS_FILTEROBINARYCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"OBinaryChannel.hpp"
#include	"Ref.hpp"


namespace GS {

// ============================== Class FilterIBinaryChannel ===================

class GSROOT_DLL_EXPORT FilterOBinaryChannel : public OBinaryChannel {
public:
						FilterOBinaryChannel (OBinaryChannel&			oc);
						FilterOBinaryChannel (const OBinaryChannelRef&	ocr);
	virtual				~FilterOBinaryChannel () = 0;

	virtual void			Write (const char* source, USize nOfCharToWrite) override;
	virtual void			Flush () override;
	virtual void			Close () override;

protected:
	OBinaryChannel&			GetBaseChannel ()		{ PRECOND_R_DEPRECATED(oc);  return *oc; }
	const OBinaryChannel&	GetBaseChannel () const { PRECOND_R_DEPRECATED(oc);  return *oc; }
private:
							FilterOBinaryChannel (const FilterOBinaryChannel& source);	// disabled
	FilterOBinaryChannel&	operator= (const FilterOBinaryChannel& source);				// disabled

	OBinaryChannel*			oc;
	OBinaryChannelRef		ocref;
};


// ______________________________ Class FilterIBinaryChannel ____________________

}	// namespace GS


#endif
