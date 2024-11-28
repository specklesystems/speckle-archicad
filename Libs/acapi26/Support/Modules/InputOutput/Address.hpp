
// *****************************************************************************
//
//                                Class Address
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ADDRESS_HPP
#define ADDRESS_HPP

#pragma once

#if defined (DEBUVERS)
#define DEBUG_SUPPORT
#endif


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "Name.hpp"

namespace IO { class Reflectable; }



// =============================== Class Address ===============================

namespace IO {

namespace Imp {		// implementation

const UIndex NullLink = GS::MaxUIndex;	// special value indicating nullptr link, defined here because of inline functions

class VSDebugSupport {		// debug support for the Visual Studio
private:
	void*	debugInfo;

protected:
	VSDebugSupport ();
};

}	// namespace Imp


class IO_DLL_EXPORT NameEnumerator {
public:
	virtual ~NameEnumerator ();

	virtual void	NameFound (const Name& /*name*/) {}
};


class IO_DLL_EXPORT Address: public GS::Object
#ifdef DEBUG_SUPPORT
							 , private Imp::VSDebugSupport
#endif
{
	DECLARE_CLASS_INFO

private:
	UIndex	id;		// identifier of the address in the address tree

public:
	static const Reflectable&	reflectionTree;		// for the reflection of the address tree

		// Constructors

	Address ();
	explicit Address (const GS::UniChar::Layout* nameSeq);
	Address (const Address& source);
	Address (Address&& source);
   ~Address ();
	Address&	operator= (const Address& source);
	Address&	operator= (Address&& source);

		// Interface

	inline GSErrCode	GetStatus (void) const;

	GSErrCode	Set   (const GS::UniChar::Layout* nameSeq);
	void		Clear (void);

	GSErrCode	GetName		(UIndex idx, Name* result) const;
	GSErrCode	SetName		(UIndex idx, const Name& name);
	GSErrCode	GetLastName (Name* result) const;
	GSErrCode	SetLastName	(const Name& name);

	GSErrCode	Append (const Name& name);
	GSErrCode	Append (const Address& address);

	GSErrCode	DeleteName	   (UIndex idx);
	GSErrCode	DeleteLastName (void);

	USize		GetLength (void) const;
	bool		IsEmpty	  (void) const;

	GSErrCode	EnumerateNames (NameEnumerator* enumerator) const;

	bool				operator==	(const Address& rightOp) const;
	bool				operator!=	(const Address& rightOp) const;
	bool				operator<	(const Address& rightOp) const;

	virtual	GSErrCode	Read  (GS::IChannel& ic) override;
	virtual	GSErrCode	Write (GS::OChannel& oc) const override;
			GSErrCode	Write (GS::OChannel& oc, USize maxNetworkLengthForOldPrograms = MaxUSize) const;
		// Other

	ULong	GenerateHashValue (void) const;

		// Debug

	static void		CCALL CleanUp (void);
	static void		CCALL PrintAddressTree (GS::OChannel& oc);
};

}	// namespace IO


inline GSErrCode	IO::Address::GetStatus (void) const
{
	return (id != Imp::NullLink ? NoError : ErrMemoryFull);
}

// _______________________________ Class Address _______________________________


#endif
