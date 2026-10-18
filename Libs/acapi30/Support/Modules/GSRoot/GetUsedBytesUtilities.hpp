#ifndef GS_GETUSEDBYTESUTILITIES_HPP
#define GS_GETUSEDBYTESUTILITIES_HPP

#pragma once


#include "Definitions.hpp"
#include "Array.hpp"
#include "FixArray.hpp"
#include "ThreadSafeLazyData.hpp"
#include "Owner.hpp"
#include "BaseAlgorithms.hpp"
#include "EnumerationTraits.hpp"
#include "RangeElementType.hpp"


namespace GS {


template <class T>
ULong	GetContainerHeapUsedBytes (const T& v);


namespace Imp {

struct TestGetHeapUsedBytes {
	template <class T>
	static constexpr bool	Test (decltype (ULong { std::declval<T> ().GetHeapUsedBytes () })*)		{ return true; }

	template <class T>
	static constexpr bool	Test (...)																{ return false; }
};

template <class T>
constexpr bool	HasGetHeapUsedBytes = TestGetHeapUsedBytes::Test<T> (nullptr);



// Test GetSize member existence
struct TestGetSizeMember {
	template <class T>
	static constexpr bool	Test (decltype (std::size_t { std::declval<T> ().GetSize () })*)		{ return true; }

	template <class T>
	static constexpr bool	Test (...)																{ return false; }
};

template <class T>
constexpr bool	HasGetSizeMember = TestGetSizeMember::Test<T> (nullptr);



// GetContainerSize:
// - the value of .GetSize(), if the container has GetSize member
// - difference of end and begin, if it has a random access iterator
// - size of the array in case of a C-style array

struct TestSubtractableExternalRangeIterator {
	template <class T>
	static constexpr bool	Test (decltype (std::size_t { static_cast<std::size_t> (end (std::declval<T> ()) - begin (std::declval<T> ())) })*)		{ return true; }

	template <class T>
	static constexpr bool	Test (...)																												{ return false; }
};

template <class T>
constexpr bool	HasSubtractableExternalRangeIterator = TestSubtractableExternalRangeIterator::Test<T> (nullptr);

struct TestSubtractableInternalRangeIterator {
	template <class T>
	static constexpr bool	Test (decltype (std::size_t { static_cast<std::size_t> (std::declval<T> ().end () - std::declval<T> ().begin ()) })*)	{ return true; }

	template <class T>
	static constexpr bool	Test (...)																												{ return false; }
};

template <class T>
constexpr bool	HasSubtractableInternalRangeIterator = TestSubtractableInternalRangeIterator::Test<T> (nullptr);

template <class T>
GS::EnableIf<HasGetSizeMember<T>, std::size_t>	GetContainerSize (const T& container)
{
	return container.GetSize ();
}

template <class T>
GS::EnableIf<HasSubtractableExternalRangeIterator<T> && !HasGetSizeMember<T>, std::size_t>	GetContainerSize (const T& container)
{
	return static_cast<std::size_t> (end (container) - begin (container));
}

template <class T>
GS::EnableIf<HasSubtractableInternalRangeIterator<T> && !HasSubtractableExternalRangeIterator<T> && !HasGetSizeMember<T>, std::size_t> GetContainerSize (const T& container)
{
	return static_cast<std::size_t> (container.end () - container.begin ());
}

template <class T, std::size_t N>
std::size_t		GetContainerSize (const T (&)[N])
{
	return N;
}



// Test if GetContainerSize is available for a type
struct TestGetContainerSize {
	template <class T>
	static constexpr bool	Test (decltype (std::size_t { GetContainerSize (std::declval<T> ()) })*)	{ return true; }

	template <class T>
	static constexpr bool	Test (...)																	{ return false; }
};

template <class T>
constexpr bool HasGetContainerSize = TestGetContainerSize::Test<T> (nullptr);



// GetCustomHeapUsedBytes is implemented for a type if HeapUsedBytes for the type is not always 0

template <class T>
GS::EnableIf<HasGetHeapUsedBytes<T>, ULong>		GetCustomHeapUsedBytes (const T& cont)
{
	return cont.GetHeapUsedBytes ();
}

template <class T>
ULong	GetCustomHeapUsedBytes (const GS::ThreadSafeLazyData<T>& tsld)
{
	const T* data = tsld.GetIfCalculated ();
	if (data != nullptr) {
		return GetContainerHeapUsedBytes (*data);
	}
	return 0;
}

template <class T>
ULong	GetCustomHeapUsedBytes (const GS::Owner<T>& owner)
{
	if (owner == nullptr) {
		return 0;
	}
	return GetContainerHeapUsedBytes (*owner) + sizeof (T);
}

// Test if type is a (multidimensional) fixed size array with an element type that always has 0 size heap bytes
template <class T>
struct IsFixedSizeArrayWithoutCustomHeapBytes;

template <class T>
ULong	GetContainerCustomHeapUsedBytes (const T& cont);
    
template <class T>
GS::EnableIf<GS::IsEnumerable<T>, ULong>	GetCustomHeapUsedBytes (const T& cont)
{
	return GetContainerCustomHeapUsedBytes (cont);
}

template <class T, std::size_t N>
ULong	GetCustomHeapUsedBytes (const T(& cont) [N])
{
	if (IsFixedSizeArrayWithoutCustomHeapBytes<T>::value)
		return 0;

	return GetContainerCustomHeapUsedBytes (cont) - N * sizeof (T);
}

template <class T, ULong N>
ULong	GetCustomHeapUsedBytes (const GS::FixArray<T, N>& cont)
{
	if (IsFixedSizeArrayWithoutCustomHeapBytes<T>::value)
		return 0;

	return GetContainerCustomHeapUsedBytes (cont) - N * sizeof (T);
}

template <class T, ULong N>
ULong	GetCustomHeapUsedBytes (const GS::ArrayFB<T, N>& cont)
{
	return GetContainerCustomHeapUsedBytes (cont) - GS::Min (N, cont.GetSize ()) * sizeof (T);
}


// Test if GetCustomHeapUsedBytes is implemented for the type (otherwise it is assumed that HeapUsedBytes is 0)
struct TestCustomHeapUsedBytes {
	template <class T>
	static constexpr bool	Test (decltype (std::size_t { GetCustomHeapUsedBytes (std::declval<T> ()) })*)	{ return true; }

	template <class T>
	static constexpr bool	Test (...)																		{ return false; }
};

template <class T>
constexpr bool HasCustomHeapUsedBytes = TestCustomHeapUsedBytes::Test<T> (nullptr);


template <class T>
GS::EnableIf<HasGetContainerSize<T>, size_t>	GetContainerSize_DefaultToZero (const T& cont)
{
	return GetContainerSize (cont);
}

template <class T = void>
GS::EnableIf<!HasGetContainerSize<T>, size_t>	GetContainerSize_DefaultToZero (...)
{
	return 0;
}


template <class T>
ULong GetContainerCustomHeapUsedBytes (const T& cont)
{
	using ElementType = GS::RangeElementType<T>;

	const bool calculateOneByOne = HasCustomHeapUsedBytes<GS::RangeElementType<T>> || !HasGetContainerSize<T>;

	if (calculateOneByOne) {
		ULong res = 0;

		for (const ElementType& item : cont)
			res += GetContainerHeapUsedBytes (item) + sizeof (ElementType);

		return res;
	} else {
		return static_cast<ULong> (GetContainerSize_DefaultToZero (cont)) * sizeof (ElementType);
	}
}


template <class T>
struct  IsFixedSizeArrayWithoutCustomHeapBytes
{
	static const bool value = !HasCustomHeapUsedBytes<T>;
};

template <class T, ULong N>
struct IsFixedSizeArrayWithoutCustomHeapBytes<GS::FixArray<T, N>>
{
	static const bool value = IsFixedSizeArrayWithoutCustomHeapBytes<T>::value;
};

template <class T, std::size_t N>
struct IsFixedSizeArrayWithoutCustomHeapBytes<T[N]>
{
	static const bool value = IsFixedSizeArrayWithoutCustomHeapBytes<T>::value;
};

 
template <class T>
GS::EnableIf<HasCustomHeapUsedBytes<T>, ULong>		GetCustomHeapUsedBytes_DefaultToZero (const T& cont)
{
    return GetCustomHeapUsedBytes (cont);
}
    
template <class T>
GS::EnableIf<!HasCustomHeapUsedBytes<T>, ULong>		GetCustomHeapUsedBytes_DefaultToZero (const T&)
{
    return 0;
}
    
}	// namespace Imp


template <class T>
ULong	GetContainerHeapUsedBytes (const T& v)
{
	return Imp::GetCustomHeapUsedBytes_DefaultToZero (v);
}


}	// namespace GS


#endif
