
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


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "Name.hpp"
#include "SharedPtr.hpp"

namespace IO { class Reflectable; }



// =============================== Class Address ===============================

namespace IO {

class IO_DLL_EXPORT NameEnumerator {
public:
	virtual ~NameEnumerator ();

	virtual void	NameFound (const Name& /*name*/) {}
};


class AddressTreeEntry;
using AddressTreeEntryPtr = GS::ConstSharedPtr<AddressTreeEntry>;

class IO_DLL_EXPORT Address: public GS::Object
{
	DECLARE_CLASS_INFO

private:
	AddressTreeEntryPtr entry;

public:

	// Constructors

	Address ();
	explicit Address (const GS::UniChar::Layout* nameSeq);
	Address (const Address& source);
	Address (Address&& source);
   ~Address ();
	Address&	operator= (const Address& source);
	Address&	operator= (Address&& source);

		// Interface

	void		Set   (const GS::UniChar::Layout* nameSeq);
	void		Clear (void);

	void		GetName		(UIndex idx, Name* result) const;
	void		SetName		(UIndex idx, const Name& name);
	void		GetLastName (Name* result) const;
	void		SetLastName	(const Name& name);

	void		Append (const Name& name);
	void		Append (const Address& address);

	void		DeleteName	   (UIndex idx);
	void		DeleteLastName (void);

	USize		GetLength (void) const;
	bool		IsEmpty	  (void) const;

	void		EnumerateNames (NameEnumerator* enumerator) const;

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
};

}	// namespace IO


// _______________________________ Class Address _______________________________


#endif
