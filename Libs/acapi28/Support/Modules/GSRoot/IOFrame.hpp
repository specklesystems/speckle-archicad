// *********************************************************************************************************************
// Description:		Class InputFrame and OutputFrame.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef IOFRAME_HPP
#define IOFRAME_HPP

#pragma once


#include "ClassInfo.hpp"


namespace GS {


// === class InputFrame ================================================================================================

class GSROOT_DLL_EXPORT [[nodiscard]] InputFrame {
private:
	IChannel&	 input;				// input channel
	ClassVersion inputVersion;		// version of the data read from the input
	USize		 length;			// length of the data block
	UInt64		 beginPosition;		// input position on the input channel at beginning of the block
	GSErrCode	 status;			// indicates whether is the frame successfully created

	InputFrame (const InputFrame& source) = delete;
	InputFrame&	operator= (const InputFrame& source) = delete;

public:
	InputFrame	(IChannel& ic, const ClassInfo& classInfo);
	~InputFrame ();

	GS_FORCE_INLINE ClassVersion	GetVersion	   (void) const	{ return inputVersion; }
	GS_FORCE_INLINE unsigned char	GetMainVersion (void) const	{ return inputVersion.GetMainVersion (); }
	GS_FORCE_INLINE unsigned char	GetSubVersion  (void) const	{ return inputVersion.GetSubVersion (); }

	USize		GetDataLength (void) const;

	GS_FORCE_INLINE GSErrCode	GetStatus (void) const { return status; }
};


// === class OutputFrame ===============================================================================================

class GSROOT_DLL_EXPORT [[nodiscard]] OutputFrame {
private:
	OChannel&	 output;			// output channel
	ClassVersion outputVersion;		// version of the data written to the output

	OutputFrame (const OutputFrame& source) = delete;
	OutputFrame&	operator= (const OutputFrame& source) = delete;

public:
	OutputFrame	(OChannel& oc, const ClassInfo& classInfo);
	~OutputFrame ();

	GS_FORCE_INLINE ClassVersion	GetVersion	   (void) const	{ return outputVersion;	}
	GS_FORCE_INLINE unsigned char	GetMainVersion (void) const	{ return outputVersion.GetMainVersion (); }
	GS_FORCE_INLINE unsigned char	GetSubVersion  (void) const	{ return outputVersion.GetSubVersion (); }
};


}	// namespace GS


#endif
