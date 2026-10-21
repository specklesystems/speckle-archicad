
// *****************************************************************************
//
//                              Class OutputBuffer
//
// Module: GSRoot
// Namespace: GS
// Contact person: MB
//
//
// *****************************************************************************


#if !defined OUTPUTBUFFER_HPP
#define OUTPUTBUFFER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "Array.hpp"


// ============================ Class OutputBuffer =============================

namespace GS {

class GSROOT_DLL_EXPORT OutputBuffer {
public:
	class BinOutput;

private:
	ArrayFB<char*, 4> bufferPages;		// stores buffer pages
	USize				  bufferPageSize;	// size of a buffer page in characters

	UIndex		writePage;			// buffer page used for the next write (Put) operation
	char*		writePtr;			// pointer used for the next write (Put) operation (it can be nullptr when buffering is disabled or no buffer has been allocated yet)
	char*		writeEndPtr;		// limit for the writePtr, it points one character after the writePage (it can be nullptr when buffering is disabled or no buffer has been allocated yet)

	bool		isOffsetted;		// indicates whether is buffer in the offsetted mode
	char*		savedWritePtr;		// stores the writePtr when buffer is in offsetted mode

	ArrayFB<UIndex, 8>	marks;	// stores position markers

	BinOutput*	binOutput;			// output (destination) of the binary data
	UInt64      writtenBytes;       // number of bytes sent to BinOutput

	bool		isBufferingEnabled;	// indicates whether is the buffering enabled

	GSErrCode	status;				// state of the object


	OutputBuffer (const OutputBuffer& source);				// disabled
	OutputBuffer&	operator= (const OutputBuffer& source);	// disabled

	void	InitializeBuffer   ();
	void	ReinitializeBuffer ();
	void	DeleteBuffer	   ();

	void	WriteData (const char* source, USize nOfCharToWrite, USize* written);

	void	CopyToBuffer (const char* source, USize nOfCharToCopy, USize* written);

	USize	GetFreeSpace	 () const;
	UIndex	GetWritePosition () const;

public:
		// Constants

	static const USize	DefaultBufferPageSize;	// default size of a buffer page in characters

		// Constructors

	OutputBuffer (BinOutput* binOutput = nullptr, USize bufferPageSize = 0);
   ~OutputBuffer ();

		// User interface

	GSErrCode	GetStatus () const;
	void		ResetOutputStatus ();

	void		SetBinOutput (BinOutput& newBinOutput);
	BinOutput&	GetBinOutput () const;

	void		ClearBinOutput ();	// sets default binary output which always indicates that output is full

	GSErrCode	Put (const char* source, USize nOfCharToPut, USize* written = nullptr);
	GSErrCode	Put (char c);

	UInt64		GetWrittenBytes () const;

	GSErrCode	Flush		 ();
	void		ClearContent ();
	void		Reset		 ();

	bool		IsEmpty		 () const;
	USize		GetDataSize	 () const;

	GSErrCode	PushMark	 ();
	GSErrCode	PopMark		 ();
	USize		GetOffset	 () const;
	void		ResetOffset	 ();
	bool		IsInMarkMode () const;

	GSErrCode	DirectAccess (UIndex startPosition, char** output, USize* accessibleDataSize);

	void		EnableBuffering	   ();
	void		DisableBuffering   ();
	bool		IsBufferingEnabled () const;

		// Types

	class GSROOT_DLL_EXPORT BinOutput {		// destination of the binary data for the output buffer
	public:
		virtual GSErrCode	InternalWrite (const char* source, USize nOfCharToWrite, USize* written);
	};
};


inline GSErrCode	OutputBuffer::GetStatus () const
{
	return status;
}


inline UInt64	OutputBuffer::GetWrittenBytes () const
{
	return writtenBytes;
}


inline GSErrCode	OutputBuffer::Put (char c)
{
	return Put (&c, sizeof (char));
}

}	// namespace GS

// ____________________________ Class OutputBuffer _____________________________

#endif
