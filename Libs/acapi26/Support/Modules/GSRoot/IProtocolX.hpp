// *****************************************************************************
//
//                        IProtocolX
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_IPROTOCOLX_HPP
#define GS_IPROTOCOLX_HPP

// --------------------------------- Includes ----------------------------------

#include	"GSException.hpp"

namespace GS {

// --- Predeclarations ---------------------------------------------------------

class Guid;
class IBinaryChannel;
class UniString;

// === Class IProtocolX ========================================================

class GSROOT_DLL_EXPORT IProtocolX {
public:
		// User interface

	virtual void	Read (IBinaryChannel& input, char& c) const = 0;
	virtual void	Read (IBinaryChannel& input, unsigned char& c) const = 0;
	virtual void	Read (IBinaryChannel& input, bool& b) const = 0;
	virtual void	Read (IBinaryChannel& input, short& s) const = 0;
	virtual void	Read (IBinaryChannel& input, unsigned short& s) const = 0;
	virtual void	Read (IBinaryChannel& input, int& i) const = 0;
	virtual void	Read (IBinaryChannel& input, unsigned int& i) const = 0;
	virtual void	Read (IBinaryChannel& input, long& l) const = 0;
	virtual void	Read (IBinaryChannel& input, unsigned long& l) const = 0;
	virtual void	Read (IBinaryChannel& input, long long& l) const = 0;
	virtual void	Read (IBinaryChannel& input, unsigned long long& l) const = 0;
	virtual void	Read (IBinaryChannel& input, float& f) const = 0;
	virtual void	Read (IBinaryChannel& input, double& d) const = 0;
	virtual void	Read (IBinaryChannel& input, long double& d) const = 0;

	virtual void	Read (IBinaryChannel& input, UniString& string) const;
	virtual void	Read (IBinaryChannel& input, Guid& guid) const;

	// virtual void	Read (IBinaryChannel& input, Object& obj); -- TODO

	virtual			~IProtocolX ();
};

// ___ Class IProtocolX ________________________________________________________

}	// namespace GS


#endif
