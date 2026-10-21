// *****************************************************************************
// External buffer array
//
// Source Unit:		Brep
// Module:			Brep
// Namespace:		
// Contact person:	BeA
// *****************************************************************************

#ifndef	BREP_EXTERNAL_BUFFER_ARRAY_HPP
#define	BREP_EXTERNAL_BUFFER_ARRAY_HPP

#pragma once

#include	"Algorithms.hpp"	
#include	"RandomContainer.hpp"
#include	"RandomContainerIterator.hpp"

// GSRoot
#include "XMLChannel.hpp"

// ExternalBufferArray is similar to GS::ArrayFB with the following differences:
// - the fixed buffer size isn't decided at compile time
// - the fixed buffer is passed to the array as a constructor parameter
// - the fixed buffer is not owned (create/deleted) by the array
// - the array doesn't have a virtual function table (it's smaller, than GS::ArrayFB)


namespace Brep {


inline std::byte* EnsureBufferAlignment (std::byte* buffer, USize alignment)
{
	const USize addrModAlignment = (reinterpret_cast<GS::IntPtr> (buffer) % alignment);
	if (addrModAlignment == 0) {
		return buffer;
	} else {
		return buffer + alignment - addrModAlignment;
	}
}


template<typename Type>
std::byte*		EnsureBufferAlignment (std::byte* buffer)
{
	return EnsureBufferAlignment (buffer, alignof (Type));
}


template <class Type>
class ExternalBufferArray : public GS::RandomContainer<Type> {
private:
	Type*	array;		// array storing items
	USize	capacity;	// capacity of the array (in items)
	USize	size;		// number of items in the array
	Type*	extBuffer;	// externally allocated buffer

	inline void		IncreaseCapacity (USize minCapacity);
	inline void		DecreaseCapacity (USize minCapacity);
	void			AdjustCapacity (USize minCapacity);
	void			Reallocate (USize minCapacity);

	void			SetIncreasedSize (USize increasedSize);
	void			SetDecreasedSize (USize decreasedSize);

	USize			GetMinBufferCapacity (void) const;
	Type*			AllocateNewBuffer (USize bufferCapacity, const Type* oldBuffer);
	void			DeleteBuffer (Type* buffer);
	bool			IsIndependentBuffer (const Type* buffer) const { return buffer == nullptr || buffer != extBuffer; }

public:
	// Types

	typedef GS::RandomContainerIterator<ExternalBufferArray>		Iterator;
	typedef GS::ConstRandomContainerIterator<ExternalBufferArray>	ConstIterator;

	typedef Type*		 FastIterator;
	typedef const Type*	 ConstFastIterator;

	// Constructors

	ExternalBufferArray (std::byte* extBuffer = nullptr, std::size_t extBufferCapacityInBytes = 0);
	ExternalBufferArray (const ExternalBufferArray& source, std::byte* extBuffer = nullptr, std::size_t extBufferCapacityInBytes = 0);
	ExternalBufferArray (ExternalBufferArray&& source, std::byte* extBuffer = nullptr, std::size_t extBufferCapacityInBytes = 0);
	ExternalBufferArray&	operator= (const ExternalBufferArray& source);
	ExternalBufferArray&	operator= (ExternalBufferArray&& source);
	~ExternalBufferArray () { Clear ();  }

	// Item access

	inline Type&		operator[] (UIndex idx) { DBASSERT (idx < size); return array[idx]; }
	inline const Type&	operator[] (UIndex idx) const { DBASSERT (idx < size); return array[idx]; }

	// Content management

	void	Clear (bool keepCapacity = false);

	void	Push (const Type& item);
	void	Push (Type&& item);

	inline USize	GetSize (void) const { return size;  }
	inline bool		IsEmpty (void) const { return size == 0; }
	void			SetSize (USize newSize);

	// Content query

	inline Iterator				Begin (void) { return Iterator (*this, 0); }
	inline ConstIterator		Begin (void) const { return ConstIterator (*this, 0); }

	inline Iterator				End (void) { return Iterator (*this, size); }
	inline ConstIterator		End (void) const { return ConstIterator (*this, size); }

	inline FastIterator			BeginFast (void) { return array;  }
	inline ConstFastIterator	BeginFast (void) const { return array;  }

	inline FastIterator			EndFast (void) { return array + size; }
	inline ConstFastIterator	EndFast (void) const { return array + size; }

	// Performance tuning

	USize	GetCapacity (void) const { return capacity;  }
	void	SetCapacity (USize newCapacity);

	// Low level access

	inline Type*		GetContent (void) { return array;  }
	inline const Type*	GetContent (void) const { return array; }
	
	void		ClearAndSetExtBuffer (std::byte* unalignedBufferStart, std::size_t extBufferCapacityInBytes);
	std::byte*	ClearAndSetExtBufferFromItemCount (std::byte* buffer, USize itemCount);

	static std::byte*	CalculateBufferEndFromItemCount (std::byte* unalignedBufferStart, USize itemCount);
};


template <class Type>
inline auto		begin (ExternalBufferArray<Type>& array)
{
	return array.Begin ();
}


template <class Type>
inline auto		end (ExternalBufferArray<Type>& array)
{
	return array.End ();
}


template <class Type>
inline auto		begin (const ExternalBufferArray<Type>& array)
{
	return array.Begin ();
}


template <class Type>
inline auto		end (const ExternalBufferArray<Type>& array)
{
	return array.End ();
}


template <class Type>
void WriteXMLExternalBufferArray (GS::XMLOChannel& outXML, const ExternalBufferArray<Type>& arr, const char* rootTagName = "ExternalBufferArray")
{
	GS::XMLTag tag (outXML, rootTagName);
	{
		for (const Type& item : arr)
		{
			item.WriteXML (outXML);
		}
	}
}


template <class Type>
void WriteXMLExternalBufferArray (GS::XMLOChannel& outXML, const ExternalBufferArray<Type>& arr, const char* rootTagName, const char* itemTagName)
{
	GS::XMLTag tag (outXML, rootTagName);
	{
		for (const Type& item : arr)
		{
			item.WriteXML (outXML, itemTagName);
		}
	}
}


template <class Type>
ExternalBufferArray<Type> ReadXMLExternalBufferArray (GS::XMLIChannel& inXML, const char* rootTagName = "ExternalBufferArray")
{
	ExternalBufferArray<Type> res;
	GS::XMLITag tag (inXML, rootTagName);
	{
		const char* itemTagName = Type::GetXMLTag ();
		GS::UniString nextTokenName;	// for loop conditions that read many similar elements, e.g. vertices
		for (inXML.GetNextTokenTypeName (nextTokenName)
			; nextTokenName == itemTagName
			; inXML.GetNextTokenTypeName (nextTokenName))
		{
			Type item;
			item.ReadXML (inXML);
			res.Push (item);
		}
	}
	return res;
}


template <class Type>
ExternalBufferArray<Type> ReadXMLExternalBufferArray (GS::XMLIChannel& inXML, const char* rootTagName, const char* itemTagName)
{
	ExternalBufferArray<Type> res;
	GS::XMLITag tag (inXML, rootTagName);
	{
		GS::UniString nextTokenName;	// for loop conditions that read many similar elements, e.g. vertices
		for (inXML.GetNextTokenTypeName (nextTokenName)
			; nextTokenName == itemTagName
			; inXML.GetNextTokenTypeName (nextTokenName))
		{
			Type item;
			item.ReadXML (inXML, itemTagName);
			res.Push (item);
		}
	}
	return res;
}


template <class Type>
inline void		ExternalBufferArray<Type>::IncreaseCapacity (USize minCapacity)
{
	if (minCapacity > capacity)
		AdjustCapacity (minCapacity);
}


template <class Type>
inline void		ExternalBufferArray<Type>::DecreaseCapacity (USize minCapacity)
{
	if (minCapacity <= capacity / 4)
		AdjustCapacity (minCapacity);
}


template <class Type>
void	ExternalBufferArray<Type>::AdjustCapacity (USize minCapacity)
{
	if (minCapacity <= capacity && minCapacity > capacity / 4)
		return;		// there is no need to reallocate

	Reallocate (GS::Max (minCapacity, size * 2));
}


template <class Type>
void	ExternalBufferArray<Type>::Reallocate (USize minCapacity)
{
	DBASSERT (minCapacity >= size);	// can't delete items with this method

	USize newCapacity = minCapacity;

	if (newCapacity < GetMinBufferCapacity ())
		newCapacity = GetMinBufferCapacity ();

	if (newCapacity == capacity)
		return;

	Type* newArray = nullptr;
	if (newCapacity != 0) {
		try {
			newArray = AllocateNewBuffer (newCapacity, array);
		} catch (const GS::OutOfMemoryException&) {
			if (capacity >= minCapacity)
				return;
			else
				throw;
		}

		for (UIndex i = 0; i < size; i++) {
			new (&newArray[i]) Type (std::move (array[i]));
			array[i].~Type ();
		}
	}

	DeleteBuffer (array);

	array = newArray;
	capacity = newCapacity;
}


template <class Type>
void	ExternalBufferArray<Type>::SetIncreasedSize (USize increasedSize)
{
	IncreaseCapacity (increasedSize);

	for (UIndex i = size; i < increasedSize; i++)
		new (&array[i]) Type ();

	size = increasedSize;
}


template <class Type>
void	ExternalBufferArray<Type>::SetDecreasedSize (USize decreasedSize)
{
	for (UIndex i = decreasedSize; i < size; i++)
		array[i].~Type ();

	size = decreasedSize;

	DecreaseCapacity (size);
}


template <class Type>
USize	ExternalBufferArray<Type>::GetMinBufferCapacity (void) const
{
	if (array == extBuffer) {
		return capacity;
	} else if (extBuffer != nullptr) { // the capacity of extBuffer is saved to the beginning of the buffer when it is not used (see DeleteBuffer)
		return *reinterpret_cast<USize*> (EnsureBufferAlignment<USize> (reinterpret_cast<std::byte*> (extBuffer)));
	} else {
		return 0;
	}
}


template <class Type>
Type*	ExternalBufferArray<Type>::AllocateNewBuffer (USize bufferCapacity, const Type* oldBuffer)
{
	if (IsIndependentBuffer (oldBuffer) && bufferCapacity <= GetMinBufferCapacity ())
		return extBuffer;
	else
		return reinterpret_cast<Type*> (new std::byte[bufferCapacity * sizeof (Type)]);
}


template <class Type>
void	ExternalBufferArray<Type>::DeleteBuffer (Type* buffer)
{
	if (IsIndependentBuffer (buffer))
		delete[] reinterpret_cast<std::byte*> (buffer);
	else // save the buffer capacity to the beginning of the buffer for GetMinBufferCapacity
		*reinterpret_cast<USize*> (EnsureBufferAlignment<USize> (reinterpret_cast<std::byte*> (extBuffer))) = capacity;
}


template <class Type>
ExternalBufferArray<Type>::ExternalBufferArray (std::byte* extBuffer /*= nullptr*/, std::size_t extBufferCapacityInBytes /*= 0*/)
	: array (nullptr), capacity (0), size (0), extBuffer (nullptr)
{
	ClearAndSetExtBuffer (extBuffer, extBufferCapacityInBytes);
}


template <class Type>
ExternalBufferArray<Type>::ExternalBufferArray (const ExternalBufferArray& source, std::byte* extBuffer /*= nullptr*/, std::size_t extBufferCapacityInBytes /*= 0*/)
	: array (nullptr), capacity (0), size (0), extBuffer (nullptr)
{
	ClearAndSetExtBuffer (extBuffer, extBufferCapacityInBytes);
	operator= (source);
}


template <class Type>
ExternalBufferArray<Type>::ExternalBufferArray (ExternalBufferArray&& source, std::byte* extBuffer /*= nullptr*/, std::size_t extBufferCapacityInBytes /*= 0*/)
	: array (nullptr), size (0), capacity (0), extBuffer (nullptr)
{
	ClearAndSetExtBuffer (extBuffer, extBufferCapacityInBytes);
	operator= (std::move (source));
}


template <class Type>
ExternalBufferArray<Type>&	ExternalBufferArray<Type>::operator= (const ExternalBufferArray& source)
{
	if (&source != this) {
		Clear ();

		IncreaseCapacity (source.size);

		for (UIndex i = 0; i < source.size; i++)
			new (&array[i]) Type (source.array[i]);
		size = source.size;
	}

	return *this;
}


template <class Type>
ExternalBufferArray<Type>&	ExternalBufferArray<Type>::operator= (ExternalBufferArray&& source)
{
	NULL_REF_CHECK (source);
	if (&source == this) {
		return *this;
	}

	if (source.IsIndependentBuffer (source.array)) {
		Clear ();

		array = source.array;
		capacity = source.capacity;
		size = source.size;
		source.array = nullptr;
		source.capacity = 0;
		source.size = 0;
	} else {
		operator= (source);
		source.Clear ();
	}
	return *this;
}


template <class Type>
void	ExternalBufferArray<Type>::Clear (bool keepCapacity)
{
	for (UIndex i = 0; i < size; i++)
		array[i].~Type ();

	if (!keepCapacity) {
		DeleteBuffer (array);
		array = nullptr;
		capacity = 0;
	}

	size = 0;
}


template <class Type>
void	ExternalBufferArray<Type>::Push (const Type& item)
{
	NULL_REF_CHECK (item);

	if (&item >= array && &item < array + size) {	// is item in the array ?
		Type temp = item;
		Push (std::move (temp));
		return;
	}

	IncreaseCapacity (size + 1);

	new (&array[size]) Type (item);
	size++;
}


template <class Type>
void	ExternalBufferArray<Type>::Push (Type&& item)
{
	NULL_REF_CHECK (item);
	DBASSERT (&item < array || &item >= array + size);		// item should not be in the array

	IncreaseCapacity (size + 1);

	new (&array[size]) Type (std::move (item));
	size++;
}


template <class Type>
void	ExternalBufferArray<Type>::SetSize (USize newSize)
{
	if (newSize < size)
		SetDecreasedSize (newSize);
	else if (newSize > size)
		SetIncreasedSize (newSize);
}


template <class Type>
void	ExternalBufferArray<Type>::SetCapacity (USize newCapacity)
{
	if (newCapacity < size)
		newCapacity = size;		// can't delete items with this method

	if (newCapacity == capacity)
		return;

	Reallocate (newCapacity);
}


template<typename Type>
void	ExternalBufferArray<Type>::ClearAndSetExtBuffer (std::byte* unalignedBufferStart, std::size_t extBufferCapacityInBytes)
{
	Clear ();
	if (extBufferCapacityInBytes == 0) {
		extBuffer = nullptr;
		capacity = 0;
	} else {
		std::byte* alignedBuffer = EnsureBufferAlignment<Type> (unalignedBufferStart);
		DBASSERT (alignedBuffer <= unalignedBufferStart + extBufferCapacityInBytes);
		const std::size_t alignedSizeInBytes = extBufferCapacityInBytes - (alignedBuffer - unalignedBufferStart);

		DBASSERT (alignedBuffer != nullptr);
		DBASSERT (EnsureBufferAlignment<USize> (alignedBuffer) - alignedBuffer + sizeof (USize) <= alignedSizeInBytes);
		extBuffer = reinterpret_cast<Type*> (alignedBuffer);
		array = extBuffer;
		capacity = static_cast<USize> (alignedSizeInBytes / sizeof (Type));
	}
}


template<typename Type>
std::byte* ExternalBufferArray<Type>::ClearAndSetExtBufferFromItemCount (std::byte* buffer, USize itemCount)
{
	std::byte* bufferEnd = ExternalBufferArray<Type>::CalculateBufferEndFromItemCount (buffer, itemCount);
	ClearAndSetExtBuffer (buffer, bufferEnd - buffer);
	return bufferEnd;
}


template<typename Type>
std::byte*	ExternalBufferArray<Type>::CalculateBufferEndFromItemCount (std::byte* unalignedBufferStart, USize itemCount)
{
	if (itemCount == 0) {
		return unalignedBufferStart;
	}

	std::byte* bufferEnd1 = EnsureBufferAlignment<Type> (unalignedBufferStart);
	bufferEnd1 += itemCount * sizeof (Type);

	std::byte* bufferEnd2 = EnsureBufferAlignment<USize> (EnsureBufferAlignment<Type> (unalignedBufferStart));
	bufferEnd2 += sizeof (USize);

	return GS::Max (bufferEnd1, bufferEnd2); // the buffer has to be big enough to store itemCount aligned items of Type, or the capacity of the buffer
}




} // namespace Brep

#endif // BREP_EXTERNAL_BUFFER_ARRAY_HPP
