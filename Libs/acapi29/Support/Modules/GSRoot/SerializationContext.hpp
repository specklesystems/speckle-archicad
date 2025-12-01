// *****************************************************************************
//
//                        Class SerializationContext
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
//
//
// *****************************************************************************

#ifndef SERIALIZATIONCONTEXT_HPP
#define SERIALIZATIONCONTEXT_HPP


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"


// ======================== Class SerializationContext =========================

namespace GS {

class GSROOT_DLL_EXPORT SerializationContext {
private:
	UInt32 flags;	// each bit is a separate flag

	enum { PointerCount = 10 };

	void* pointers[PointerCount];

public:
	class Flag;
	class Pointer;

	SerializationContext ();

	void	Set (const Flag& flag);
	void	Set (const Flag& flag, bool newValue);
	void	Clear (const Flag& flag);
	bool	Get (const Flag& flag) const;
	bool	IsSet (const Flag& flag) const;

	void	Set (const Pointer& pointer, void* newValue);
	void	Clear (const Pointer& pointer);
	void*	Get (const Pointer& pointer) const;
	bool	IsSet (const Pointer& pointer) const;

	template <class Type>
	Type*	Get (const Pointer& pointer) const;


	// types

	class GSROOT_DLL_EXPORT Flag {
	private:
		static UInt32 maskGenerator;

		UInt32 mask;	// mask value of a bit in flags field

	public:
		Flag ();

		friend class SerializationContext;
	};

	class GSROOT_DLL_EXPORT Pointer {
	private:
		static UInt32 indexGenerator;

		UInt32 index;	// index of the pointer in the pointers field

	public:
		Pointer ();

		friend class SerializationContext;
	};
};


inline void		SerializationContext::Set (const Flag& flag)
{
	flags |= flag.mask;
}


inline void		SerializationContext::Set (const Flag& flag, bool newValue)
{
	if (newValue == true)
		flags |= flag.mask;
	else
		flags &= ~flag.mask;
}


inline void		SerializationContext::Clear (const Flag& flag)
{
	flags &= ~flag.mask;
}


inline bool		SerializationContext::Get (const Flag& flag) const
{
	return ((flags & flag.mask) != 0);
}


inline bool		SerializationContext::IsSet (const Flag& flag) const
{
	return ((flags & flag.mask) != 0);
}


inline void		SerializationContext::Set (const Pointer& pointer, void* newValue)
{
	pointers[pointer.index] = newValue;
}


inline void		SerializationContext::Clear (const Pointer& pointer)
{
	pointers[pointer.index] = nullptr;
}


inline void*	SerializationContext::Get (const Pointer& pointer) const
{
	return pointers[pointer.index];
}


template <class Type>
Type*	SerializationContext::Get (const Pointer& pointer) const
{
	return static_cast<Type*> (pointers[pointer.index]);
}


inline bool		SerializationContext::IsSet (const Pointer& pointer) const
{
	return (pointers[pointer.index] != nullptr);
}


} // namespace GS

#endif
