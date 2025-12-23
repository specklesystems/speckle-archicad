// *****************************************************************************
//
//                        ChanelExceptions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_CHANELEXCEPTIONS_HPP
#define GS_CHANELEXCEPTIONS_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"GSException.hpp"

namespace GS {

// ============================== Exceptions declaration =======================

DECLARE_EXCEPTION_CLASS (IOException,  GeneralException, Error, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (ClosedChannelException, IOException, Error, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (EndOfInputException, IOException, IChannelErrors + 0 /* EndOfInput */, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (ReadErrorException, IOException, IChannelErrors + 1 /* ReadError */, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (OutputIsFullException, IOException, OChannelErrors + 0 /* OutputIsFull */, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (WriteErrorException, IOException, OChannelErrors + 1 /* WriteError */, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (DataIntegrityException, IOException, IntegrityError, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (UnexpectedEndOfInputDataIntegrityException, DataIntegrityException, IntegrityError, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (InterruptedIOException, IOException, Error, GSROOT_DLL_EXPORT)

// ______________________________ Exceptions declaration _______________________

}	// namespace GS


#endif
