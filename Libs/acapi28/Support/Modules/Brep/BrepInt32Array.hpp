// *********************************************************************************************************************
// Description:		Limited range Int32 container with optimized memory usage
//
// Module:			Brep
// Namespace:		Brep
// Contact person:	BeA
// *********************************************************************************************************************

#if !defined BREPINT32ARRAY_HPP
#define BREPINT32ARRAY_HPP

#include "BrepExternalBufferArray.hpp"
#include "BrepExport.hpp"

namespace Brep {

class BREP_DLL_EXPORT Int32Array {
private:
	ExternalBufferArray<char>	buffer;
	char						sizeExp;	//	size of the stored integer type is (1 << sizeExp)

	void SetSize (char newSizeExp, USize newSize);
	static char ValueSizeExp (Int32 value);

public:
	class ConstIterator;

	Int32Array ();

	USize GetSize () const;

	Int32	GetValue (UIndex index) const;
	void	SetValue (UIndex index, Int32 newValue);

	void	SetCapacity (USize capacity);
	USize	GetUsedBytes () const;


	ConstIterator Begin () const;
	ConstIterator End () const;


	USize AddNValues (const Int32* valuesPtr, USize valuesCount);

	std::byte* ClearAndSetExtBufferFromItemCount (std::byte* buffer, USize itemCount, Int32 maxAbsValue);

	void Clear ();
	
	Int32Array& operator = (const Int32Array& src);
	Int32Array& operator = (Int32Array&& src);

	static std::byte*	CalculateBufferEndFromItemCount (std::byte* unalignedBufferStart, USize itemCount, Int32 maxAbsValue);

	void WriteXML (GS::XMLOChannel& outXML, const char* rootTagName = "Int32Array", const char* itemTagName = "Item") const;
	void ReadXML (GS::XMLIChannel& inXML, const char* rootTagName = "Int32Array", const char* itemTagName = "Item");
};


class Int32Array::ConstIterator {
	const Int32Array* container;
	UIndex current;

public:

	ConstIterator (const Int32Array* container, UIndex current) : container (container), current (current)
	{
	}

	inline Int32	operator*  () const
	{
		return container->GetValue (current);
	}

	inline bool		operator== (const ConstIterator& rightOp) const
	{
		DBASSERT (container == rightOp.container);
		return current == rightOp.current;
	}

	inline bool		operator!= (const ConstIterator& rightOp) const
	{
		DBASSERT (container == rightOp.container);
		return current != rightOp.current;
	}

	inline ConstIterator&	operator++ ()
	{
		++current;
		return *this;
	}

	inline ConstIterator&	operator-- ()
	{
		--current;
		return *this;
	}

	inline ConstIterator	operator+  (GS::Offset offset) const
	{
		return ConstIterator (container, current + offset);
	}

	inline ConstIterator	operator-  (GS::Offset offset) const
	{
		return ConstIterator (container, current - offset);
	}

	inline GS::Offset operator-  (const ConstIterator& rightOp) const
	{
		DBASSERT (container == rightOp.container);
		return current - rightOp.current;
	}

	inline ConstIterator&	operator+= (GS::Offset offset)
	{
		current += offset;
		return *this;
	}

	inline ConstIterator&	operator-= (GS::Offset offset)
	{
		current -= offset;
		return *this;
	}

	inline bool		operator<  (const ConstIterator& rightOp) const
	{
		DBASSERT (container == rightOp.container);
		return current < rightOp.current;
	}
	inline bool		operator<= (const ConstIterator& rightOp) const
	{
		DBASSERT (container == rightOp.container);
		return current <= rightOp.current;
	}

	inline bool		operator>  (const ConstIterator& rightOp) const
	{
		DBASSERT (container == rightOp.container);
		return current > rightOp.current;
	}

	inline bool		operator>= (const ConstIterator& rightOp) const
	{
		DBASSERT (container == rightOp.container);
		return current >= rightOp.current;
	}

};


inline auto		begin (const Int32Array& array)
{
	return array.Begin ();
}


inline auto		end (const Int32Array& array)
{
	return array.End ();
}

inline void Int32Array::SetSize (char newSizeExp, USize newSize)
{
	if (newSizeExp > sizeExp) {
		const USize itemCountToConvert = GS::Min (GetSize (), newSize);
		buffer.SetSize (newSize << newSizeExp);

		if (sizeExp == 0) {
			if (newSizeExp == 1) {
				for (UIndex i = 1; i <= itemCountToConvert; ++i) {
					reinterpret_cast<short*>(buffer.GetContent ())[itemCountToConvert - i] = reinterpret_cast<char*>(buffer.GetContent ())[itemCountToConvert - i];
				}
			} else {
				DBASSERT (newSizeExp == 2);
				for (UIndex i = 1; i <= itemCountToConvert; ++i) {
					reinterpret_cast<Int32*>(buffer.GetContent ())[itemCountToConvert - i] = reinterpret_cast<char*>(buffer.GetContent ())[itemCountToConvert - i];
				}
			}
		} else {
			DBASSERT (sizeExp == 1);
			DBASSERT (newSizeExp == 2);
			for (UIndex i = 1; i <= itemCountToConvert; ++i) {
				reinterpret_cast<Int32*>(buffer.GetContent ())[itemCountToConvert - i] = reinterpret_cast<short*>(buffer.GetContent ())[itemCountToConvert - i];
			}
		}

		sizeExp = newSizeExp;
	} else {
		buffer.SetSize (newSize << sizeExp);
	}
}


inline char Int32Array::ValueSizeExp (Int32 value)
{
	const UInt32 absValue = GS::Abs (value);
	if (absValue <= 0x0000007f) {
		return 0;
	} else if (absValue <= 0x00007fff) {
		return 1;
	} else {
		return 2;
	}
}


inline Int32Array::Int32Array () : sizeExp (0)
{
}


inline USize Int32Array::GetSize () const
{
	return buffer.GetSize () >> sizeExp;
}


inline Int32 Int32Array::GetValue (UIndex index) const
{
	switch (sizeExp) {
	default:
		DBBREAK ();
		// no break
	case 0:
		return reinterpret_cast<const char*>(buffer.GetContent ())[index];
		break;
	case 1:
		return reinterpret_cast<const short*>(buffer.GetContent ())[index];
		break;
	case 2:
		return reinterpret_cast<const Int32*>(buffer.GetContent ())[index];
		break;
	}
}


inline void Int32Array::SetValue (UIndex index, Int32 newValue)
{
	const char newSizeExp = ValueSizeExp (newValue);
	if (newSizeExp > sizeExp) {
		SetSize (newSizeExp, GetSize ());
	}
	switch (sizeExp) {
	default:
		DBBREAK ();
	case 0:
		reinterpret_cast<char*>(buffer.GetContent ())[index] = static_cast<char> (newValue);
		break;
	case 1:
		reinterpret_cast<short*>(buffer.GetContent ())[index] = static_cast<short> (newValue);
		break;
	case 2:
		reinterpret_cast<Int32*>(buffer.GetContent ())[index] = static_cast<Int32> (newValue);
		break;
	}
}


inline void Int32Array::SetCapacity (USize capacity)
{
	buffer.SetCapacity (capacity << sizeExp);
}


inline USize	Int32Array::GetUsedBytes () const
{
	return buffer.GetSize ();
}


inline Int32Array::ConstIterator Int32Array::Begin () const
{
	return ConstIterator (this, 0);
}


inline Int32Array::ConstIterator Int32Array::End () const
{
	return ConstIterator (this, GetSize ());
}

} // namespace Brep

#endif