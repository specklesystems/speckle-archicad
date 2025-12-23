
// *****************************************************************************
//
//	                          Class OChannelAdapter
//
// Module: GSRoot
// Namespace: GS
// Contact person: MB
//
//
// *****************************************************************************


#if !defined OCHANNELADAPTER_HPP
#define OCHANNELADAPTER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Protocol.hpp"
#include "OutputBuffer.hpp"


// =========================== Class OChannelAdapter ===========================

namespace GS {

class GSROOT_DLL_EXPORT OChannelAdapter: public OChannel {
private:
	OutputBuffer	outputBuffer;	// output buffer for the OChannelAdapter

	OChannelAdapter (const OChannelAdapter& source);				// disabled
	OChannelAdapter&	operator= (const OChannelAdapter& source);	// disabled

protected:
		// Constructors

	explicit OChannelAdapter (OProtocol& op);

		// Protected user interface

	void	SetBinOutput   (OutputBuffer::BinOutput& bo);
	void	ClearBinOutput (void);	// sets binary output which always indicates error

	OutputBuffer::BinOutput&	GetBinOutput (void) const;

	USize	GetDataSizeInOutputBuffer (void) const;

	void	ResetOutputBuffer (void);

public:
		// Destructor

   ~OChannelAdapter () {}

		// User interface

	using OChannel::WriteBin;

	virtual GSErrCode	WriteBin (const char* source, USize nOfCharToWrite, USize* written = nullptr) override;
	virtual	GSErrCode	DirectOutputAccess (UIndex startPosition, char** output, USize* accessibleDataSize) override;
	virtual	GSErrCode	GetOutputPosition (UInt64* pos) const override;

	virtual GSErrCode	Flush (void) override;

	virtual GSErrCode	PushMark	(void) override;
	virtual GSErrCode	PopMark		(void) override;
	virtual USize		GetOffset	(void) const override;
	virtual void		ResetOffset	(void) override;

	virtual GSErrCode	GetOutputStatus	  (void) const override;
	virtual void		ResetOutputStatus (void) override;

	void	EnableOutputBuffering	 (void);
	void	DisableOutputBuffering   (void);
	bool	IsOutputBufferingEnabled (void) const;
};

}	// namespace GS

// ___________________________ Class OChannelAdapter ___________________________

#endif
