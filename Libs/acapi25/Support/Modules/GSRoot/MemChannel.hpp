// *****************************************************************************
//
//									Memory Channel (Use MemoryOChannel instead)
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MM
//
// SG compatible
//
// *****************************************************************************

#ifndef	MEMCHANNEL_HPP
#define	MEMCHANNEL_HPP

#include "GSRootExport.hpp"

#include "Definitions.hpp"
#include "Channel.hpp"
#include "GSDebug.hpp"
#include "Protocol.hpp"
#include "BM.hpp"
#include "VA.hpp"

#include <string.h>

namespace GS {

// =============================================================================
//									INPUT CHANNEL
// =============================================================================

class GSROOT_DLL_EXPORT IMemProtocol : public IProtocol {
	virtual	GSErrCode	Read (IChannel& input, char& c)				 override { return  input.ReadBin ((char*) &c, sizeof (c));	}
	virtual GSErrCode	Read (IChannel& input, unsigned char& c)	 override { return  input.ReadBin ((char*) &c, sizeof (c));	}
	virtual GSErrCode	Read (IChannel& input, bool& b)				 override { return  input.ReadBin ((char*) &b, sizeof (b));	}
	virtual GSErrCode	Read (IChannel& input, short& s)			 override { return  input.ReadBin ((char*) &s, sizeof (s));	}
	virtual GSErrCode	Read (IChannel& input, unsigned short& s)	 override { return  input.ReadBin ((char*) &s, sizeof (s));	}
	virtual GSErrCode	Read (IChannel& input, int& i)				 override { return  input.ReadBin ((char*) &i, sizeof (i));	}
	virtual GSErrCode	Read (IChannel& input, unsigned int& i)		 override { return  input.ReadBin ((char*) &i, sizeof (i));	}
	virtual GSErrCode	Read (IChannel& input, long& l)				 override { return  input.ReadBin ((char*) &l, sizeof (l));	}
	virtual GSErrCode	Read (IChannel& input, unsigned long& l)	 override { return  input.ReadBin ((char*) &l, sizeof (l));	}
	virtual GSErrCode	Read (IChannel& input, Int64& l)			 override { return  input.ReadBin ((char*) &l, sizeof (l));	}
	virtual GSErrCode	Read (IChannel& input, UInt64& l)			 override { return  input.ReadBin ((char*) &l, sizeof (l));	}
	virtual GSErrCode	Read (IChannel& input, float& f)			 override { return  input.ReadBin ((char*) &f, sizeof (f));	}
	virtual GSErrCode	Read (IChannel& input, double& d)			 override { return  input.ReadBin ((char*) &d, sizeof (d));	}
	virtual GSErrCode	Read (IChannel& input, long double& d)		 override { return  input.ReadBin ((char*) &d, sizeof (d));	}
	virtual GSErrCode	Read (IChannel& input, char* cStr) override
							{
								Int32 nBytes = 0;
								GSErrCode errCode = Read (input, nBytes);
								if (errCode == NoError)
									errCode = input.ReadBin (cStr, nBytes);
								return  errCode;
							}

	virtual GSErrCode	Read (IChannel& input, Object& obj) override;
};


class GSROOT_DLL_EXPORT IMemChannel : public IChannel {
private:
	IMemProtocol	memProtocol;
	const char*		pData;
	const char*		pCurr;
	const char*		pGuard;
	GSErrCode		status;

public:

	IMemChannel (const void* p, GSSize size) :
		IChannel (memProtocol),
		pData ((const char*) p),
		pCurr ((const char*) p),
		pGuard ((const char*) p + size),
		status (NoError)
		{
		}

	virtual ~IMemChannel ();

	virtual GSErrCode ReadBin (char* destination, USize nOfCharToRead, USize* read) override
		{
			if (status != NoError)
				return  status;
			if (pCurr + nOfCharToRead > pGuard) {
				nOfCharToRead = TruncateTo32Bit (pGuard - pCurr);
				status = EndOfInput;
			}
			BNCopyMemory (destination, pCurr, nOfCharToRead);
			pCurr += nOfCharToRead;
			if (read != nullptr)
				*read = nOfCharToRead;
			return  status;
		}

	virtual GSErrCode	GetAvailable     (UInt64* available) const override
		{
			*available =  (pGuard - pCurr);
			return NoError;
		}

	virtual GSErrCode CopyBin (char* /*destination*/, USize /*nOfCharToCopy*/, USize* /*copied*/) override
		{
			DBBREAK ();
			return  Error;
		}

	virtual GSErrCode Look (UIndex /*idx*/, char* /*c*/) override
		{
			DBBREAK ();
			return  Error;
		}

	virtual	GSErrCode PushBack (const char* /*source*/, USize /*nOfChar*/) override
		{
			DBBREAK ();
			return  Error;
		}

	virtual	GSErrCode Skip (UInt64 nOfCharToSkip, UInt64* skipped) override
		{
			if (status != NoError)
				return  status;
			if (pCurr + nOfCharToSkip > pGuard) {
				status = EndOfInput;
				nOfCharToSkip = pGuard - pCurr;
			}
			pCurr = pGuard;
			if (skipped != nullptr)
				*skipped = nOfCharToSkip;
			return  status;
		}

	virtual	GSErrCode DirectInputAccess (USize /*nOfCharToAccess*/, char** /*source*/, USize* /*accessible*/) override
		{
			DBBREAK ();
			return  Error;
		}

	virtual GSErrCode	GetInputPosition (UInt64* /*position*/) const override
		{
			DBBREAK ();
			return  Error;
		}

	virtual	void SetDefaultInputProtocol (void) override
		{
			SetInputProtocol (memProtocol);
		}

	virtual GSErrCode GetInputStatus (void) const override
		{
			return  status;
		}

	virtual void ResetInputStatus (void) override
		{
			status = NoError;
		}
};


// =============================================================================
//									OUTPUT CHANNEL
// =============================================================================

class GSROOT_DLL_EXPORT OMemProtocol: public OProtocol {
	virtual GSErrCode	Write (OChannel& output, char c)			 override { return  output.WriteBin ((char*)&c, sizeof (c));	}
	virtual GSErrCode	Write (OChannel& output, unsigned char c)	 override { return  output.WriteBin ((char*)&c, sizeof (c));	}
	virtual GSErrCode	Write (OChannel& output, bool b)			 override { return  output.WriteBin ((char*)&b, sizeof (b));	}
	virtual GSErrCode	Write (OChannel& output, short s)			 override { return  output.WriteBin ((char*)&s, sizeof (s));	}
	virtual GSErrCode	Write (OChannel& output, unsigned short s)	 override { return  output.WriteBin ((char*)&s, sizeof (s));	}
	virtual GSErrCode	Write (OChannel& output, int i)				 override { return  output.WriteBin ((char*)&i, sizeof (i));	}
	virtual GSErrCode	Write (OChannel& output, unsigned int i)	 override { return  output.WriteBin ((char*)&i, sizeof (i));	}
	virtual GSErrCode	Write (OChannel& output, long l)			 override { return  output.WriteBin ((char*)&l, sizeof (l));	}
	virtual GSErrCode	Write (OChannel& output, unsigned long l)	 override { return  output.WriteBin ((char*)&l, sizeof (l));	}
	virtual GSErrCode	Write (OChannel& output, Int64 l)			 override { return  output.WriteBin ((char*)&l, sizeof (l));	}
	virtual GSErrCode	Write (OChannel& output, UInt64 l)			 override { return  output.WriteBin ((char*)&l, sizeof (l));	}
	virtual GSErrCode	Write (OChannel& output, float f)			 override { return  output.WriteBin ((char*)&f, sizeof (f));	}
	virtual GSErrCode	Write (OChannel& output, double d)			 override { return  output.WriteBin ((char*)&d, sizeof (d));	}
	virtual GSErrCode	Write (OChannel& output, long double d)		 override { return  output.WriteBin ((char*)&d, sizeof (d));	}
	virtual GSErrCode	Write (OChannel& /*output*/, const void* /*p*/) override
							{
								DBBREAK ();
								return  Error;
							}
	virtual GSErrCode	Write (OChannel& output, const char* cStr) override
							{
								Int32 nBytes = Strlen32 (cStr) + 1;
								Write (output, nBytes);
								return  output.WriteBin (cStr, nBytes);
							}
	virtual GSErrCode	Write (OChannel& output, const Object& obj) override;
};


class GSROOT_DLL_EXPORT OMemChannel : public OChannel {
private:
	OMemProtocol	memProtocol;
	DESC			data;
	GSErrCode		status;
public:

	OMemChannel () : OChannel (memProtocol), status (NoError)
		{
			status = VAInit (&data, 4096, sizeof (char));
		}

	virtual ~OMemChannel ();

	virtual GSErrCode WriteBin (const char* source, USize nOfCharToWrite, USize* written) override
		{
			if (status != NoError)
				return  status;
			Int32 offset = VANspac (&data, nOfCharToWrite);
			if (offset < 0) {
				status = offset;
				if (written != nullptr)
					*written = 0;
			} else {
				BNCopyMemory (*data.arrhdl + offset, source, nOfCharToWrite);

				if (written != nullptr)
					*written = nOfCharToWrite;
			}

			return  status;
		}

	virtual	GSErrCode DirectOutputAccess (UIndex /*startPosition*/, char** /*output*/, USize* /*accessibleDataSize*/) override
		{
			DBBREAK ();
			return  Error;
		}

	virtual	void SetDefaultOutputProtocol (void) override
		{
			SetOutputProtocol (memProtocol);
		}

	virtual GSErrCode PushMark	(void) override
		{
			DBBREAK ();
			return  Error;
		}

	virtual GSErrCode PopMark		(void) override
		{
			DBBREAK ();
			return  Error;
		}

	virtual USize GetOffset	(void) const override
		{
			DBBREAK ();
			return  0;
		}

	virtual void ResetOffset (void) override
		{
			DBBREAK ();
		}

	virtual GSErrCode GetOutputPosition (UInt64* /*out*/) const override
		{
			DBBREAK ();
			return  Error;
		}

	virtual GSErrCode GetOutputStatus (void) const override
		{
			return  status;
		}

	virtual void ResetOutputStatus (void) override
		{
			status = NoError;
		}

	virtual const void* LockData (void)
		{
			if (status != NoError)
				return  nullptr;

			return  *data.arrhdl + data.size;
		}

	virtual void UnlockData (void)
		{
		}

	virtual USize DataSize (void) const
		{
			if (status != NoError)
				return  0;
			return  data.lastind;
		}
};


}	// namespace GS

#endif	// MEMCHANNEL_HPP
