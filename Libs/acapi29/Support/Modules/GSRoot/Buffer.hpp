
// *****************************************************************************
//
//                                 Struct Buffer
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined BUFFER_HPP
#define BUFFER_HPP

#pragma once



// --------------------------------- Includes ----------------------------------

#include <new>



// =============================== Struct Buffer ===============================

namespace GS {

template <class Type, UInt32 FixBufferCapacity = 1>
class Buffer {
private:
	Type	FixBuffer[FixBufferCapacity];
	
public:
	const UInt32	capacity;
	Type* const		ptr;

	Buffer ();
	~Buffer ();

	void	Set (Type* newPtr, UInt32 newCapacity);
	void	EnsureCapacity (UInt32 newCapacity);
};

}	// namespace GS



template <class Type, UInt32 FixBufferCapacity>
inline GS::Buffer<Type, FixBufferCapacity>::Buffer ():
	capacity (FixBufferCapacity),
	ptr (FixBuffer)
{
}


template <class Type, UInt32 FixBufferCapacity>
inline GS::Buffer<Type, FixBufferCapacity>::~Buffer ()
{
	if (ptr != FixBuffer)
		delete [] ptr;
}


template <class Type, UInt32 FixBufferCapacity>
void	GS::Buffer<Type, FixBufferCapacity>::Set (Type* newPtr, UInt32 newCapacity)
{
	if (ptr != FixBuffer)
		delete [] ptr;

	const_cast<Type*&> (ptr) = newPtr;
	const_cast<UInt32&> (capacity) = newCapacity;
}


template <class Type, UInt32 FixBufferCapacity>
void	GS::Buffer<Type, FixBufferCapacity>::EnsureCapacity (UInt32 newCapacity)
{
   if (newCapacity > capacity) {
	   if (ptr != FixBuffer)
		   delete [] ptr;

	   const_cast<Type*&> (ptr) = new Type[newCapacity];
	   const_cast<UInt32&> (capacity) = newCapacity;
   }
}
// _______________________________ Struct Buffer _______________________________


#endif
