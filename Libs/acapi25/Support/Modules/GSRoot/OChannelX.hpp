// *****************************************************************************
//
//                        OChannelX - facade for OBinaryChannel and OProtocolX
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_OCHANNELX_HPP
#define GS_OCHANNELX_HPP

// --------------------------------- Includes ----------------------------------

#include	"OBinaryChannel.hpp"
#include	"OProtocolX.hpp"

namespace GS {

// --- Predeclarations ---------------------------------------------------------

// === Class OChannelX =========================================================

class GSROOT_DLL_EXPORT OChannelX {
public:
		// User interface

			OChannelX (OBinaryChannel&			ich, const OProtocolX& protocol);
			OChannelX (const OBinaryChannelRef&	ichRef, const OProtocolX& protocol);


	void	Write (char c)						{ GetOP ().Write (GetOBC (), c); }
	void	Write (unsigned char c)				{ GetOP ().Write (GetOBC (), c); }
	void	Write (bool b)						{ GetOP ().Write (GetOBC (), b); }
	void	Write (short s)						{ GetOP ().Write (GetOBC (), s); }
	void	Write (unsigned short s)			{ GetOP ().Write (GetOBC (), s); }
	void	Write (int i)						{ GetOP ().Write (GetOBC (), i); }
	void	Write (unsigned int i)				{ GetOP ().Write (GetOBC (), i); }
	void	Write (long l)						{ GetOP ().Write (GetOBC (), l); }
	void	Write (unsigned long l)				{ GetOP ().Write (GetOBC (), l); }
	void	Write (long long l)					{ GetOP ().Write (GetOBC (), l); }
	void	Write (unsigned long long l)		{ GetOP ().Write (GetOBC (), l); }
	void	Write (float f)						{ GetOP ().Write (GetOBC (), f); }
	void	Write (double d)					{ GetOP ().Write (GetOBC (), d); }
	void	Write (long double d)				{ GetOP ().Write (GetOBC (), d); }

	void	Write (const UniString& string)		{ GetOP ().Write (GetOBC (), string); }
	void	Write (const Guid& guid)			{ GetOP ().Write (GetOBC (), guid); }

	virtual			~OChannelX ();

	virtual void				WriteBin (const char* source, USize nOfCharToWrite);
	virtual void				Flush ();
	virtual void				Close ();

	virtual	void				SetOutputProtocol (const OProtocolX& ip);
	virtual	const OProtocolX&	GetOutputProtocol ();

	virtual void				SetOBinaryChannel (OBinaryChannel& ch);
	virtual void				SetOBinaryChannel (const OBinaryChannelRef& ch);
	virtual OBinaryChannel&		GetOBinaryChannel ();
	virtual OBinaryChannelRef&	GetOBinaryChannelRef ();
protected:
	const OProtocolX*	oprotocol;
	OBinaryChannel*		obinaryChannel;
	OBinaryChannelRef*	obinaryChannelRef;

	OBinaryChannel&		GetOBC ()				{ return *obinaryChannel; }
	OBinaryChannel&		GetOBC () const			{ return *obinaryChannel; }
	const OProtocolX&	GetOP ()				{ return *oprotocol; }
};



// ___ Class IChannelX _________________________________________________________

}	// namespace GS


#endif
