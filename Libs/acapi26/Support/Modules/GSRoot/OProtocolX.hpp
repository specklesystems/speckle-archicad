// *****************************************************************************
//
//                        OProtocolX - OProtocol with exception interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_OPROTOCOLX_HPP
#define GS_OPROTOCOLX_HPP

// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"


namespace GS {

// --- Predeclarations ---------------------------------------------------------

class Guid;
class OBinaryChannel;
class UniString;

// === Class OProtocolX ========================================================

class GSROOT_DLL_EXPORT OProtocolX {
public:
		// User interface

	virtual void	Write (OBinaryChannel& output, char c) const = 0;
	virtual void	Write (OBinaryChannel& output, unsigned char c) const = 0;
	virtual void	Write (OBinaryChannel& output, bool b) const = 0;
	virtual void	Write (OBinaryChannel& output, short s) const = 0;
	virtual void	Write (OBinaryChannel& output, unsigned short s) const = 0;
	virtual void	Write (OBinaryChannel& output, int i) const = 0;
	virtual void	Write (OBinaryChannel& output, unsigned int i) const = 0;
	virtual void	Write (OBinaryChannel& output, long l) const = 0;
	virtual void	Write (OBinaryChannel& output, unsigned long l) const = 0;
	virtual void	Write (OBinaryChannel& output, long long l) const = 0;
	virtual void	Write (OBinaryChannel& output, unsigned long long l) const = 0;
	virtual void	Write (OBinaryChannel& output, float f) const = 0;
	virtual void	Write (OBinaryChannel& output, double d) const = 0;
	virtual void	Write (OBinaryChannel& output, long double d) const = 0;

	virtual void	Write (OBinaryChannel& output, const UniString& string) const;
	virtual void	Write (OBinaryChannel& output, const Guid& guid) const;

	// virtual void	Write (GS::OBinaryChannel& output, const GS::Object& object); -- TODO

	virtual			~OProtocolX ();
};


// ___ Class OProtocolX ________________________________________________________

}	// namespace GS


#endif
