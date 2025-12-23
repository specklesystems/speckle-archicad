
// *****************************************************************************
//
//	                              Class MD5Channel
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined MD5CHANNEL_HPP
#define MD5CHANNEL_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "OChannelAdapter.hpp"

#include "Md5.hpp"



// ============================= Class MD5Channel ==============================

namespace IO {

class IO_DLL_EXPORT MD5Channel: public GS::OChannelAdapter,
								private GS::OutputBuffer::BinOutput
{
public:
	enum OwnershipType { OriginalOwnership, PassOwnership, GrantOwnership };

private:
	MD5::Generator	generator;		// MD5 generator
	bool			isFinished;		// indicates whether is MD5 generation finished

	MD5Channel (const MD5Channel& source);				// disabled
	MD5Channel&	operator= (const MD5Channel& source);	// disabled

	virtual GSErrCode	InternalWrite (const char* source, USize nOfCharToWrite, USize* written) override;

public:
		// Constructors

	MD5Channel ();
   ~MD5Channel ();

		// User interface

	void				Finish (MD5::FingerPrint* result);
	MD5::FingerPrint	Finish (void);

	virtual	void	SetDefaultOutputProtocol (void) override;
};

}	// namespace IO
// _____________________________ Class MD5Channel ______________________________


#endif
