
// *****************************************************************************
//
//	                          Class IChannelAdapter
//
// Module: GSRoot
// Namespace: GS
// Contact person: MB
//
//
// *****************************************************************************


#if !defined ICHANNELADAPTER_HPP
#define ICHANNELADAPTER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "InputBuffer.hpp"
#include "Channel.hpp"


// =========================== Class IChannelAdapter ===========================

namespace GS {

class GSROOT_DLL_EXPORT IChannelAdapter: public IChannel {
private:
	InputBuffer		inputBuffer;	// input buffer for the IChannelAdapter

	IChannelAdapter (const IChannelAdapter& source);				// disabled
	IChannelAdapter&	operator= (const IChannelAdapter& source);	// disabled

protected:
		// Constructors

	explicit IChannelAdapter (IProtocol& ip, char* inputBuffer = nullptr, USize inputBufferCapacity = 0);

		// Protected user interface

	void	SetBinInput	  (InputBuffer::BinInput& bi);
	void	ClearBinInput ();	// sets binary input which always indicates end-of-input

	InputBuffer::BinInput&	GetBinInput () const;

	USize	GetDataSizeInInputBuffer () const;

	void	ResetInputBuffer ();

public:
		// Destructor

   ~IChannelAdapter () {}

		// User interface

	using IChannel::ReadBin;

	virtual GSErrCode	ReadBin	 (char* destination, USize nOfCharToRead, USize* read = nullptr) override;
	virtual GSErrCode	CopyBin	 (char* destination, USize nOfCharToCopy, USize* copied = nullptr) override;
	virtual GSErrCode	Look	 (UIndex idx, char* c) override;
	virtual	GSErrCode	PushBack (const char* source, USize nOfChar) override;
	virtual	GSErrCode	PushBack (char c) override;
	virtual	GSErrCode	Skip	 (UInt64 nOfCharToSkip, UInt64* skipped = nullptr) override;
	virtual	GSErrCode	DirectInputAccess (USize nOfCharToAccess, char** source, USize* accessible = nullptr) override;

	virtual GSErrCode	GetInputStatus	 () const override;
	virtual void		ResetInputStatus () override;

	void	EnableInputBuffering	();
	void	DisableInputBuffering   ();
	bool	IsInputBufferingEnabled () const;
};

} // namespace GS

// ___________________________ Class IChannelAdapter ___________________________

#endif
