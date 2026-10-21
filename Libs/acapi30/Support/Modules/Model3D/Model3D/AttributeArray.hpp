// *********************************************************************************************************************
// Description:		Lockless container, thread-safe for concurrent reads and append from single thread
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	BeA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (ATTRIBUTE_ARRAY_HPP)
#define ATTRIBUTE_ARRAY_HPP

// from GSRoot
#include "Definitions.hpp"
#include "GSDebug.hpp"
#include "GSException.hpp"
#include "MemoryBarrier.hpp"

// from GSModeler
#include "Model3D/Model3DExport.h"

namespace Modeler {

MODEL3D_DLL_EXPORT 
short Log2Int (ULong val);


template <typename Type> 
class AttributeArray {
private:

	static const ULong log2IndexSize = 32;
	static const ULong log2FirstPageSize = 5;

	static const ULong pageTableSize = log2IndexSize - log2FirstPageSize;
	
	ULong	nextPage;
	Type*	volatile pageTable [pageTableSize];
	volatile ULong size;

	ULong PageSize (UInt32 pageIndex) 
	{
		return (1 << (pageIndex + log2FirstPageSize));
	}

	ULong	GetCapacity (ULong nextPageIndex) 
	{
		return PageSize (nextPageIndex) - (1 << log2FirstPageSize);
	}

	void	IncreaseCapacity (ULong newCapacity)
	{
		while (newCapacity > GetCapacity (nextPage)) {
			if (DBVERIFY (nextPage < pageTableSize)) {
				pageTable [nextPage] = reinterpret_cast<Type *> (new char [PageSize (nextPage) * sizeof (Type)]);
				++nextPage;
			} else {
				throw GS::InternalErrorException ();
			}
		}
	}

	Type*	Get (ULong index)
	{
		const ULong pageIndex = Log2Int (index + (1 << log2FirstPageSize)) - log2FirstPageSize;
		return &pageTable [pageIndex][index - GetCapacity (pageIndex)];
	}

public:
	AttributeArray () : size (0), nextPage (0)
	//lint -esym(1401, Modeler::AttributeArray<*>::pageTable)
	{

	}

	const Type&	operator [] (ULong index) const
	{
		return *(const_cast<AttributeArray*>(this)->Get (index));
	}

	Type&		operator [] (ULong index)
	{
		return *Get (index);
	}

	ULong	GetSize () const 
	{
		ULong retval = size;
		GS::MemoryBarrierForVolatile ();
		return retval;
	}

	void	Push (const Type& val)
	{
		IncreaseCapacity (size + 1);
		new (Get (size)) Type (val);
		GS::MemoryBarrierForVolatile ();
		++size;
	}
	
	~AttributeArray ()
	{
		Clear ();
	}

	void Clear ()
	{
		for (ULong i = 0; i < size; ++i) {			
			Get (i)->~Type ();
		}
		for (ULong i = 0; i < nextPage; ++i) {
			delete [] reinterpret_cast<char*> (pageTable [i]);
		}
		size = 0;
		nextPage = 0;
	}
};
	
} // namespace Modeler

#endif
