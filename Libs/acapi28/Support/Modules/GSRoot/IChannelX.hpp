// *****************************************************************************
//
//                        IChannelX - facade for IBinaryChannel and IProtocolX
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_ICHANNELX_HPP
#define GS_ICHANNELX_HPP

// --------------------------------- Includes ----------------------------------

#include	"IBinaryChannel.hpp"
#include	"IProtocolX.hpp"

namespace GS {

// --- Predeclarations ---------------------------------------------------------

// === Class IChannelX =========================================================

class GSROOT_DLL_EXPORT IChannelX {
public:
		// User interface

			IChannelX (const IBinaryChannelRef& ic, const IProtocolX& protocol);
			IChannelX (IBinaryChannel& ic, const IProtocolX& protocol);

	void	Read (char& c)						{ GetIP ().Read (GetIBC (), c); }
	void	Read (unsigned char& c)				{ GetIP ().Read (GetIBC (), c); }
	void	Read (bool& b)						{ GetIP ().Read (GetIBC (), b); }
	void	Read (short& s)						{ GetIP ().Read (GetIBC (), s); }
	void	Read (unsigned short& s)			{ GetIP ().Read (GetIBC (), s); }
	void	Read (int& i)						{ GetIP ().Read (GetIBC (), i); }
	void	Read (unsigned int& i)				{ GetIP ().Read (GetIBC (), i); }
	void	Read (long& l)						{ GetIP ().Read (GetIBC (), l); }
	void	Read (unsigned long& l)				{ GetIP ().Read (GetIBC (), l); }
	void	Read (long long& l)					{ GetIP ().Read (GetIBC (), l); }
	void	Read (unsigned long long& l)		{ GetIP ().Read (GetIBC (), l); }
	void	Read (float& f)						{ GetIP ().Read (GetIBC (), f); }
	void	Read (double& d)					{ GetIP ().Read (GetIBC (), d); }
	void	Read (long double& d)				{ GetIP ().Read (GetIBC (), d); }

	void	Read (UniString& string)			{ GetIP ().Read (GetIBC (), string); }
	void	Read (Guid& guid)					{ GetIP ().Read (GetIBC (), guid); }

	char			ReadChar ()					{ char ch; Read (ch); return ch; }
	unsigned char	ReadUChar ()				{ unsigned char ch; Read (ch); return ch; }
	bool			ReadBool ()					{ bool b; Read (b); return b; }
	short			ReadShort ()				{ short s; Read (s); return s; }
	unsigned short	ReadUShort ()				{ unsigned short s; Read (s); return s; }
	int				ReadInt ()					{ int i; Read (i); return i; }
	unsigned int	ReadUInt ()					{ unsigned int i; Read (i); return i; }
	Int64			ReadInt64 ()				{ Int64 i; Read (i); return i; }
	UInt64			ReadUInt64 ()				{ UInt64 i; Read (i); return i; }
	float			ReadFloat ()				{ float f; Read (f); return f; }
	double			ReadDouble ()				{ double d; Read (d); return d; }
	long double		ReadLongDouble ()			{ long double d; Read (d); return d; }

	virtual			~IChannelX ();

	virtual UInt64						Skip (UInt64 nOfCharToSkip);
	virtual USize						ReadBin (char* destination, USize nOfCharToRead);
	virtual UInt64						GetAvailable () const;
	virtual void						Close ();

	virtual	void						SetInputProtocol (const IProtocolX& ip);
	virtual	const IProtocolX&			GetInputProtocol ();

	virtual void						SetIBinaryChannel (const IBinaryChannelRef& ic);
	virtual void						SetIBinaryChannel (IBinaryChannel& ic);
	virtual IBinaryChannel&				GetIBinaryChannel ();
protected:
	const IProtocolX*			iprotocol;
	IBinaryChannel*				ibinaryChannel;
	IBinaryChannelRef			ibinaryChannelRef;

	IBinaryChannel&		GetIBC ()				{ return *ibinaryChannel; }
	IBinaryChannel&		GetIBC () const			{ return *ibinaryChannel; }
	const IProtocolX&	GetIP ()				{ return *iprotocol; }
};



// ___ Class IChannelX _________________________________________________________

}	// namespace GS


#endif
