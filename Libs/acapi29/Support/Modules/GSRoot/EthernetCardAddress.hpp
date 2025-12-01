// *****************************************************************************
//
// Module:			GSRoot\BasicEnvironment
// Class:
// Namespace:		GS
// Contact person: 	FM
//
//
// *****************************************************************************

#if ! defined GS_GSROOT_ETHERNETCARDADDRESS_HPP
#define GS_GSROOT_ETHERNETCARDADDRESS_HPP

// --- Includes ----------------------------------------------------------------

// from GSRoot
#include "GSRootExport.hpp"


// --- Predeclaration ----------------------------------------------------------

namespace GS {
	template <class Type> class Array;
	class UniString;
}

// --- namespace ---------------------------------------------------------------

namespace GS {


// --- Exported functions ------------------------------------------------------

bool GSROOT_DLL_EXPORT  GetEthernetCardAddress		(unsigned char addr[16]);
void GSROOT_DLL_EXPORT	GetEthernetCardAddresses	(GS::Array<GS::UniString>& addresses);


// --- struct EthernetCardAddress ----------------------------------------------

struct  MachineIdentifier
{
	enum MachineIdentifierType {
		EthernetMACType	= 0,
		TypeCount		= 1
	};

	MachineIdentifierType	type;
	unsigned int			size;
	unsigned char			data[16];

	MachineIdentifier ();

	void Clear ();
};


// --- class MachineIdentifierIterator -----------------------------------------

class MachineIdentifierIterator {
private:
	class MachineIdentifierIteratorImpl;
	MachineIdentifierIteratorImpl* impl;

public:
	MachineIdentifierIterator ();
	~MachineIdentifierIterator ();

	bool GetNext (MachineIdentifier* outIdentifier);
};

}

#endif // GS_GSROOT_ETHERNETCARDADDRESS_HPP
