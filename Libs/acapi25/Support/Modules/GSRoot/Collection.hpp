
// *****************************************************************************
//
//                      Classes Collection and CollectionFB
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined COLLECTION_HPP
#define COLLECTION_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "GSDebug.hpp"



// ============================= Class Collection ==============================

namespace GS {

template <class Type>
class Collection {
private:
	Type*	array;		// item array
	USize	capacity;	// capacity of the item array (in items)
	USize	size;		// number of items in the collection
	bool	ownsArray;	// true if the instance owns the item array

	bool	Init (USize initialCapacity);

public:
		// Constructors

	explicit Collection (USize initialCapacity = 0);
	Collection (Type* buffer, USize bufferCapacity, bool isBufferDeletable = false);
	Collection (const Collection& source);
   ~Collection ();
	Collection&	operator= (const Collection& source);

		// User interface

	inline Type&		operator[] (UIndex idx);
	inline const Type&	operator[] (UIndex idx) const;

	GSErrCode		Add	   (const Type& item);
	GSErrCode		Insert (UIndex to, const Type& item);
	void			Delete (UIndex idx);
	void			Clear  (void);

	inline USize	GetSize		(void) const;
};



template <class Type>
Collection<Type>::Collection (USize initialCapacity)
{
	Init (initialCapacity);
}


template <class Type>
Collection<Type>::Collection (Type* buffer, USize bufferCapacity, bool isBufferDeletable)
{
	DBASSERT (buffer != nullptr);

	array	  = buffer;
	capacity  = bufferCapacity;
	size	  = 0;
	ownsArray = isBufferDeletable;
}


template <class Type>
Collection<Type>::Collection (const Collection& source)
{
	DBASSERT (&source != nullptr);

	if (Init (source.size)) {
		for (UIndex i = 0; i < source.size; i++)
			array[i] = source.array[i];
		size = source.size;
	}
}


template <class Type>
bool	Collection<Type>::Init (USize initialCapacity)
{
	array	  = nullptr;
	capacity  = 0;
	size	  = 0;
	ownsArray = false;

	if (initialCapacity > 0) {
		try {
			array = new Type[initialCapacity];
		}
		catch (...) {}
		if (array == nullptr)
			return false;

		capacity  = initialCapacity;
		ownsArray = true;
	}

	return true;
}


template <class Type>
Collection<Type>::~Collection ()
{
	if (ownsArray)
		delete [] array;
}


template <class Type>
Collection<Type>&	Collection<Type>::operator= (const Collection<Type>& source)
{
	DBASSERT (&source != nullptr);

	if (this != &source) {
		if (size < source.size) {
			if (ownsArray)
				delete [] array;
			if (!Init (source.size))
				return *this;	// error
		}

		for (UIndex i = 0; i < source.size; i++)
			array[i] = source.array[i];
		size = source.size;
	}

	return *this;
}


template <class Type>
inline Type&	Collection<Type>::operator[] (UIndex idx)
{
	DBASSERT (idx < size);

	return array[idx];
}


template <class Type>
inline const Type&	Collection<Type>::operator[] (UIndex idx) const
{
	DBASSERT (idx < size);

	return array[idx];
}


template <class Type>
GSErrCode	Collection<Type>::Add (const Type& item)
{
	DBASSERT (&item != nullptr);

	if (size == capacity) {
		USize newCapacity = capacity * 2;
		if (newCapacity == 0)
			newCapacity = 100;	// default initial capacity
		Type* newArray = nullptr;
		try {
			newArray = new Type[newCapacity];
		}
		catch (...) {}
		if (newArray == nullptr)
			return ErrMemoryFull;

		for (UIndex i = 0; i < size; i++)
			newArray[i] = array[i];
		newArray[size] = item;		// note that the new item can be an item from the old array,
									// therefore the old array can be deleted only after this assigment
		if (ownsArray)
			delete [] array;
		array	  = newArray;
		capacity  = newCapacity;
		ownsArray = true;
	} else {
		array[size] = item;
	}

	size++;

	return NoError;
}


template <class Type>
GSErrCode	Collection<Type>::Insert (UIndex to, const Type& item)
{
	DBASSERT (to <= size);
	DBASSERT (&item != nullptr);

	if (to == size) {
		return Add (item);
	} else {
		Type copy = item;	// item can be located in this array
		GSErrCode errorCode = Add (array[size - 1]);
		if (errorCode != NoError)
			return errorCode;
		for (UIndex i = size - 2; i > to; i--)
			array[i] = array[i - 1];
		array[to] = copy;
		return NoError;
	}
}


template <class Type>
void	Collection<Type>::Delete (UIndex idx)
{
	DBASSERT (idx < size);

	for (UIndex i = idx + 1; i < size; i++)
		array[i - 1] = array[i];

	size--;
}


template <class Type>
void	Collection<Type>::Clear (void)
{
	if (ownsArray) {
		delete [] array;
		Init (0);
	} else {
		size = 0;
	}
}


template <class Type>
inline USize	Collection<Type>::GetSize (void) const
{
	return size;
}

}	// namespace GS
// _____________________________ Class Collection ______________________________



// ============================ Class CollectionFB =============================

namespace GS {

template <class Type, USize BufferCapacity>
class CollectionFB: public Collection<Type> {
private:
	Type	buffer[BufferCapacity];		// fix initial buffer for the Collection

public:
		// Constructors

	CollectionFB ();
	CollectionFB (const Collection<Type>& source);
	CollectionFB&	operator= (const Collection<Type>& source);
};



template <class Type, USize BufferCapacity>
CollectionFB<Type, BufferCapacity>::CollectionFB ():
	Collection<Type> (buffer, BufferCapacity, false)
{
}


template <class Type, USize BufferCapacity>
CollectionFB<Type, BufferCapacity>::CollectionFB (const Collection<Type>& source):
	Collection<Type> (buffer, BufferCapacity, false)
{
	Collection<Type>::operator= (source);
}


template <class Type, USize BufferCapacity>
CollectionFB<Type, BufferCapacity>&		CollectionFB<Type, BufferCapacity>::operator= (const Collection<Type>& source)
{
	Collection<Type>::operator= (source);

	return *this;
}

}	// namespace GS
// ____________________________ Class CollectionFB _____________________________


#endif
