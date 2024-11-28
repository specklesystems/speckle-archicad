// *****************************************************************************
// Description: VAArray is a classical expandable array (as std::vector).
//				A big difference is it uses memory handles
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FGY
//
// SG compatible
//
// *****************************************************************************
#if !defined (VAARRAY_HPP)
#define	VAARRAY_HPP

#pragma once

#include	"VA.hpp"
#include	"BMX.hpp"
#include	"Channel.hpp"


#include <new>

#if defined (_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4702) // Unreachable code
#endif

namespace GS {

DECLARE_EXCEPTION_CLASS (ContainerException,	RootException, Error, GSROOT_DLL_EXPORT)

DECLARE_EXCEPTION_CLASS (VAException,			ContainerException, Error, GSROOT_DLL_EXPORT)

DECLARE_EXCEPTION_CLASS2 (VAIllegalIndexException,		VAException, IllegalArgumentException, ErrParam, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS2 (VAIncompatibleTypeException,	VAException, IllegalArgumentException, ErrParam, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS2 (VALogicErrorException,		VAException, LogicErrorException,      Error, GSROOT_DLL_EXPORT)

template<class Type> class VAArray;

template<class Type> GSErrCode ReadVAArray  (VAArray<Type>* array, IChannel& ic);
template<class Type> GSErrCode WriteVAArray  (const VAArray<Type>& array, OChannel& ic);


template<class Type>
class VAArray
{
private:
	DESC	desc;
	mutable USize	unused;				// Must be zero
#if defined (DEBUVERS)
	mutable Type*	itemArray;			// It shows the contents as an array (can be inaccurate)
	mutable Type*	lastAccessedItem;	// It shows the last accessed item (can be inaccurate)
#else
	mutable Type*	filler1;			// These fillers ensure the same memory-layout
	mutable Type*	filler2;			// of the VAArray in DEBUVERS and in final versions
#endif

public:

	class Locker {
	private:
		const VAArray<Type>*	array;

		Locker (const Locker& source);				// disabled
		Locker& operator= (const Locker& source);	// disabled

	public:
		explicit Locker (const VAArray<Type>& a) noexcept :	array (&a) {}

		const Type* GetArrayPtr (void) const noexcept // Attention! This pointer is only valid under the lifetime of the locker!
		{
			return &(*array)[1];
		}

		~Locker ()	{}
	};

	inline explicit VAArray	(USize growingSize = 50)				noexcept;
	inline explicit VAArray	(const DESC& desc);						// the constructor can throw anything
	inline VAArray	(const VAArray& source);						// the constructor can throw anything
	inline VAArray&	operator= (const VAArray& source);				// the constructor can throw anything

	virtual ~VAArray	();

	friend bool	operator== (const VAArray<Type>& array1, const VAArray<Type>& array2)	noexcept;
	friend bool	operator!= (const VAArray<Type>& array1, const VAArray<Type>& array2) 	noexcept;
	friend GSErrCode ReadVAArray <Type>  (VAArray<Type>* array, IChannel& ic);
	friend GSErrCode WriteVAArray <Type>  (const VAArray<Type>& array, OChannel& ic);

	inline DESC*		GetDESCRef (void)							noexcept gs_lifebound;
	inline const DESC*	GetDESCRef (void) const						noexcept gs_lifebound;
	inline void			CopyToDESC (DESC* dest) const;

	inline Type&		operator[] (UIndex	idx) gs_lifebound;
	inline const Type&	operator[] (UIndex idx) const gs_lifebound;

	inline void		Lock (UIndex	idx) const;
	inline void		Unlock (UIndex	idx) const;

	inline void		LockAll (void) const							noexcept;
	inline void		UnlockAll (void) const;

	inline void		Insert		 (UIndex idx, const Type& item);	// the constructor can throw anything
	inline UIndex	Push		 (const Type& item);				// the constructor can throw anything
	inline bool		Pop			 (Type& item)						noexcept;
	inline Type		Pop			 (void)								noexcept;
	inline void		Fill		 (const Type& item)					noexcept;
	inline void		Fill		 (const Type& item, UIndex from, USize range);
	inline void		Delete		 (UIndex from, USize range = 1);
	inline void		Clear		 (void)								noexcept;

	inline void		Append		 (const VAArray<Type>& array2, UIndex from, USize itemCount);
	inline void		Append		 (const DESC& desc,            UIndex from, USize itemCount);
	inline void		Append		 (const Type** handle,         UIndex from, USize itemCount);
	inline void		Append		 (const Type* ptr,             UIndex from, USize itemCount);

	inline void		Append		 (const VAArray<Type>& array2);
	inline void		Append		 (const DESC& desc);

	inline bool		IsEmpty		 (void) const						noexcept;
	inline USize	GetItemCount (void) const						noexcept;
	inline void		SetItemCount (USize newSize);					// the constructor can throw anything

	inline void		SetCapacity		(USize newCapacity);
	inline void		EnsureCapacity  (USize minCapacity);
	inline USize	GetCapacity		(void) const					noexcept;

	inline void		Sort		 (GS::CmpFunction* cmpFunc)			noexcept;

	inline UIndex	Search		 (const Type* data, GS::CmpFunction* cmpFunc) const noexcept;

	inline void		Dump		 (OChannel& oc) const;

	inline void*	Allocate (void);		// use only in placement new operator!

	Type*			Begin	(void);
	Type*			End		(void);

	const Type*		Begin	(void) const;
	const Type*		End		(void) const;
};


template<class Type>
inline VAArray<Type>::VAArray (USize growingSize) noexcept :
	unused (0),
#if defined (DEBUVERS)
	itemArray (nullptr),
	lastAccessedItem (nullptr)
#else
	filler1 (nullptr),
	filler2 (nullptr)
#endif
{
	VAInitNoAlloc (&desc, growingSize, sizeof (Type));
	if (desc.arrhdl != nullptr) {
		BNZeroMemory (*desc.arrhdl, sizeof (Type));
#if defined (DEBUVERS)
		this->itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
#endif
	}
}


template<class Type>
inline VAArray<Type>::VAArray	(const DESC& descSource) : unused (0)
// the constructor can throw anything
{
	if (sizeof (Type) != descSource.size) {
		throw VAIncompatibleTypeException ("VA::copy constructor: the size must be equal!", __FILE__, __LINE__);
	}

	BNZeroMemory (&desc, sizeof (DESC));
	VACopyAll (&desc, &descSource);	// VACopyAll treats desc as garbage

	// making a new copy of content objects into the new container
	for (UIndex idx = 1; idx <= static_cast<USize> (desc.lastind); idx++) {
		new (*desc.arrhdl + idx * sizeof (Type)) Type (reinterpret_cast<Type*> (*descSource.arrhdl)[idx]);
	}
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
		lastAccessedItem = nullptr;
	}
#else
	filler1 = filler2 = nullptr;
#endif
}


template<class Type>
inline VAArray<Type>::VAArray	(const VAArray<Type>& source) : unused (0)
// the constructor can throw anything
{
	BNZeroMemory (&desc, sizeof (DESC));
	VACopyAll (&desc, &source.desc);	// VACopyAll treats desc as garbage

	// making a new copy of content objects into the new container
	for (UIndex idx = 1; idx <= static_cast<USize> (desc.lastind); idx++) {
		new (*desc.arrhdl + idx * sizeof (Type)) Type (reinterpret_cast<Type*> (*source.desc.arrhdl)[idx]);
	}
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
		lastAccessedItem = nullptr;
	}
#else
	filler1 = filler2 = nullptr;
#endif
}

template<class Type>
VAArray<Type>::~VAArray	()
{
	Clear ();
	VAFree (&desc);
}


template<class Type>
inline VAArray<Type>& VAArray<Type>::operator= (const VAArray<Type>& source)
// the constructor can throw anything
{
	if (this != &source) {
		EnsureCapacity (source.desc.lastind);

		UIndex idx;
		for (idx = 1; idx <= static_cast<USize> (source.desc.lastind); idx++) {
			if (idx <= static_cast<USize> (desc.lastind)) {
				(reinterpret_cast<Type*> (*desc.arrhdl))[idx] = reinterpret_cast<Type*> (*source.desc.arrhdl)[idx];
			} else {
				new (*desc.arrhdl + idx * sizeof (Type)) Type (reinterpret_cast<Type*> (*source.desc.arrhdl)[idx]);
			}
		}
		for ( ; idx <= static_cast<USize> (desc.lastind); idx++) {
			reinterpret_cast<Type*> (*desc.arrhdl)[idx].~Type ();
		}
		desc.lastind = source.desc.lastind;
	}
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
	return *this;
}


template<class Type>
bool operator== (const VAArray<Type>& array1, const VAArray<Type>& array2)
	noexcept
{
	if (&array1 == &array2) {
		return true;
	}
	if (array1.desc.lastind != array2.desc.lastind) {
		return false;
	}

	for (UIndex idx = 1; idx <= static_cast<USize> (array1.desc.lastind); idx++) {
		if (reinterpret_cast<Type*> (*array1.desc.arrhdl)[idx] != reinterpret_cast<Type*> (*array2.desc.arrhdl)[idx]) {
#if defined (DEBUVERS)
			array1.itemArray = reinterpret_cast<Type*> (*array1.desc.arrhdl);
			array1.lastAccessedItem = reinterpret_cast<Type*> (*array1.desc.arrhdl) + idx;
			array1.itemArray = reinterpret_cast<Type*> (*array2.desc.arrhdl);
			array1.lastAccessedItem = reinterpret_cast<Type*> (*array2.desc.arrhdl) + idx;
#endif
			return false;
		}
	}
	return true;
}


template<class Type>
bool operator!= (const VAArray<Type>& array1, const VAArray<Type>& array2)
	noexcept
{
	return !(array1 == array2);
}


template<class Type>
inline DESC* VAArray<Type>::GetDESCRef (void)	// use to pass DESC through C interface, lock count can't change!
	noexcept
{
	if (desc.arrhdl != nullptr) {
		BNZeroMemory (*desc.arrhdl, sizeof (Type));
	}
	return &desc;
}


template<class Type>
inline const DESC* VAArray<Type>::GetDESCRef (void) const	// use to pass DESC through C interface, lock count can't change!
	noexcept
{
	if (desc.arrhdl != nullptr) {
		BNZeroMemory (*desc.arrhdl, sizeof (Type));
	}
	return &desc;
}


template<class Type>
inline void	VAArray<Type>::CopyToDESC (DESC* destDesc) const
{
	VAInitNoAlloc (destDesc, desc.npage, desc.size);

	GSErr err = VAAddFromArr (destDesc, *desc.arrhdl + desc.size, desc.lastind);
	if (err != NoError) {
		throw BMOutOfMemoryException ("VA::Append: cannot allocate the needed memory!", __FILE__, __LINE__);
	}
	if (destDesc->arrhdl != nullptr) {
		BNZeroMemory (*destDesc->arrhdl, destDesc->size);
	}
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
}


template<class Type>
inline Type& VAArray<Type>::operator[] (UIndex	idx)
{
	if (idx < 1 || idx > static_cast<UIndex> (desc.lastind)) {
		throw VAIllegalIndexException ("VA::operator[]: wrong index", __FILE__, __LINE__);
	}
#if defined (DEBUVERS)
	itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	lastAccessedItem = reinterpret_cast<Type*> (*desc.arrhdl) + idx;
#endif
	return reinterpret_cast<Type*> (*desc.arrhdl)[idx];
}


template<class Type>
inline const Type& VAArray<Type>::operator[] (UIndex idx) const
{
	if (idx < 1 || idx > static_cast<UIndex> (desc.lastind)) {
		throw VAIllegalIndexException ("VA::operator[]: wrong index", __FILE__, __LINE__);
	}
#if defined (DEBUVERS)
	itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	lastAccessedItem = reinterpret_cast<Type*> (*desc.arrhdl) + idx;
#endif
	return reinterpret_cast<Type*> (*desc.arrhdl)[idx];
}


template<class Type>
inline void VAArray<Type>::Lock (UIndex idx) const
{
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
		lastAccessedItem = reinterpret_cast<Type*> (*desc.arrhdl) + idx;
	}
#else
	UNUSED_PARAMETER (idx);
#endif
}


template<class Type>
inline void VAArray<Type>::Unlock (UIndex idx) const
{
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
		lastAccessedItem = reinterpret_cast<Type*> (*desc.arrhdl) + idx;
	}
#else
	UNUSED_PARAMETER (idx);
#endif
}


template<class Type>
inline void VAArray<Type>::LockAll (void) const
	noexcept
{
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
}


template<class Type>
inline void VAArray<Type>::UnlockAll (void) const
{
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
}


template<class Type>
inline void VAArray<Type>::Insert (UIndex idx, const Type& item)
// the constructor can throw anything
{
	if (idx < 1 || idx > static_cast<UIndex> (desc.lastind) + 1) {
		throw VAIllegalIndexException ("VA::Insert: wrong index", __FILE__, __LINE__);
	}
	GSErr err = VAInsert (&desc, idx, &item);
	if (err != NoError) {
		throw BMOutOfMemoryException ("VA::Insert: cannot allocate the needed memory!", __FILE__, __LINE__);
	}

	new (*desc.arrhdl + idx * sizeof (Type)) Type (item);

#if defined (DEBUVERS)
	itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	lastAccessedItem = reinterpret_cast<Type*> (*desc.arrhdl) + idx;
#endif
}


template<class Type>
inline UIndex VAArray<Type>::Push (const Type& item)
// the constructor can throw anything
{
	UIndex index = VASpac (&desc);
	if (Int32 (index) < 0) {
		throw BMOutOfMemoryException ("VA::Push: cannot allocate the needed memory!", __FILE__, __LINE__);
	}
	new (*desc.arrhdl + index * sizeof (Type)) Type (item);

#if defined (DEBUVERS)
	itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	lastAccessedItem = reinterpret_cast<Type*> (*desc.arrhdl) + index;
#endif
	return index;
}

template<class Type>
inline bool VAArray<Type>::Pop (Type& item)
	noexcept
{
	if (desc.lastind < 1) {
		return false;
	}
	item = reinterpret_cast<Type*> (*desc.arrhdl)[desc.lastind];
	reinterpret_cast<Type*> (*desc.arrhdl)[desc.lastind].~Type ();

	desc.lastind--;
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
	return true;
}


template<class Type>
inline Type VAArray<Type>::Pop (void)
	noexcept
{
	Type item = reinterpret_cast<Type*> (*desc.arrhdl)[desc.lastind];
	reinterpret_cast<Type*> (*desc.arrhdl)[desc.lastind].~Type ();
	desc.lastind--;
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
	return item;
}



template<class Type>
inline void VAArray<Type>::Fill (const Type& item)
	noexcept
{
	for (UIndex idx = 1; idx <= static_cast<USize> (desc.lastind); idx++) {
		reinterpret_cast<Type*> (*desc.arrhdl)[idx] = item;
	}
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
}



template<class Type>
inline void VAArray<Type>::Fill (const Type& item, UIndex from, USize range)
{
	if (from < 1 ||
		range < 0 || from + range > static_cast<USize> (desc.lastind) + 1) {
		throw VAIllegalIndexException ("VA::Fill: wrong index", __FILE__, __LINE__);
	}

	for (UIndex idx = from; idx < from + range; idx++) {
		reinterpret_cast<Type*> (*desc.arrhdl)[idx] = item;
	}
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
}


template<class Type>
inline void	VAArray<Type>::Delete (UIndex from, USize range)
{
	if (from < 1 || /*range < 0 ||*/ from + range > static_cast<UIndex> (desc.lastind) + 1) {
		throw VAIllegalIndexException ("VA::Delete: wrong index", __FILE__, __LINE__);
	}

	for (UIndex i = from; i < from + range; i++) {
		reinterpret_cast<Type*> (*desc.arrhdl)[i].~Type ();
	}
	VADelete (&desc, from, range);
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
}


template<class Type>
inline void	VAArray<Type>::Clear (void)
	noexcept
{
	Delete (1, desc.lastind);
}


template<class Type>
inline void	VAArray<Type>::Append (const VAArray<Type>& array2, UIndex from, USize itemCount)
{
	Append (array2.desc, from, itemCount);
}


template<class Type>
inline void	VAArray<Type>::Append (const DESC& desc2, UIndex from, USize itemCount)
{
	Append ((const Type**) desc2.arrhdl, from, itemCount);
}


template<class Type>
inline void	VAArray<Type>::Append (const Type** handle, UIndex from, USize itemCount)
{
	if (itemCount != 0)
		Append (*handle, from, itemCount);
}


template<class Type>
inline void	VAArray<Type>::Append (const Type* ptr, UIndex from, USize itemCount)
{
	GSErr err = VAAddFromArr (&desc, ptr + from, itemCount);
	if (err != NoError) {
		throw BMOutOfMemoryException ("VA::Append: cannot allocate the needed memory!", __FILE__, __LINE__);
	}
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
}


template<class Type>
inline void	VAArray<Type>::Append (const VAArray<Type>& array2)
{
	Append (array2.desc, 1, array2.desc.lastind);
}


template<class Type>
inline void	VAArray<Type>::Append (const DESC& desc2)
{
	Append ((const Type**) (desc.arrhdl), 1, desc2.lastind);
}


template<class Type>
inline bool	VAArray<Type>::IsEmpty (void) const
	noexcept
{
	return desc.lastind == 0;
}



template<class Type>
inline USize VAArray<Type>::GetItemCount (void) const
	noexcept
{
	return desc.lastind;
}



template<class Type>
inline void VAArray<Type>::SetItemCount (USize newSize)
// the constructor can throw anything
{
	if ((newSize & (1 << 31)) != 0) {
		throw BMOutOfMemoryException ("VA::SetSize: cannot allocate the needed memory!", __FILE__, __LINE__);
	}
	if (newSize == static_cast<UIndex> (desc.lastind)) {
		return;
	}

	if (newSize < static_cast<UIndex> (desc.lastind)) {
		Delete (newSize + 1, desc.lastind - newSize);
	}

	if (newSize > static_cast<UIndex> (desc.lastind)) {
		UIndex	firstNew = static_cast<UIndex> (desc.lastind) + 1;

		if (VANspac (&desc, newSize - desc.lastind) < 0) {
			throw BMOutOfMemoryException ("VA::SetSize: cannot allocate the needed memory!", __FILE__, __LINE__);
		}
		UIndex i;
		for (i = firstNew; i <= newSize; i++) {
			new (*desc.arrhdl + i * sizeof (Type)) Type;
		}
	}
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
	return;
}



template<class Type>
inline void VAArray<Type>::SetCapacity (USize newCapacity)
{
	for (UIndex idx = newCapacity + 1; idx <= static_cast<USize> (desc.lastind); idx++) {
		try {
			reinterpret_cast<Type*> (*desc.arrhdl)[idx].~Type ();
		} catch (...) {
			// the destructor cannot throw exception!
			DBBREAK_STR ("Serious error: a destructor thrown an exception in VAArray::SetCapacity!");
		}
	}
	if (VAReal (&desc, desc.lastind, newCapacity) != 0) {
		throw BMOutOfMemoryException ("VA::SetCapacity: cannot allocate the needed memory!", __FILE__, __LINE__);
	}
#if defined (DEBUVERS)
	if (desc.arrhdl != nullptr) {
		itemArray = reinterpret_cast<Type*> (*desc.arrhdl);
	}
#endif
	return;
}


template<class Type>
inline void VAArray<Type>::EnsureCapacity (USize minCapacity)
{
	if (minCapacity > GetCapacity ()) {
		SetCapacity (minCapacity);
	}
	return;
}


template<class Type>
inline USize VAArray<Type>::GetCapacity (void) const
	noexcept
{
	if (desc.arrhdl != nullptr)
		return desc.maxind - 1;	// The maxind includes the unused 0th element
	else
		return 0;
}


template<class Type>
inline void VAArray<Type>::Sort (GS::CmpFunction* cmpFunc)
	noexcept
{
	VASort (&desc, cmpFunc);
}


template<class Type>
inline UIndex VAArray<Type>::Search (const Type* data, GS::CmpFunction* cmpFunc) const
	noexcept
{
	return (UIndex) VASearch (&desc, reinterpret_cast<const void*>(data), cmpFunc);
}


#if defined (DEBUVERS)
template<class Type>
inline void VAArray<Type>::Dump (OChannel& oc) const

{
	oc << "Size:";
	DBPRINTF ("Size: %d; Capacity: %d\n", GetItemCount (), GetCapacity ());
	DBPRINTF ("[ ");
	for (UIndex i = 1; i <= GetItemCount (); i++) {
		DBPRINTF ("?\?\?");	//		it needs the common Read/Write methods!!!
		if (i != GetItemCount ()) {
			DBPRINTF (", ");
		}
	}
	DBPRINTF ("]");
}

#else
template<class Type>
inline void VAArray<Type>::Dump (OChannel& /*oc*/) const

{
}
#endif

template<class Type>
inline void* VAArray<Type>::Allocate (void)
{
	UIndex index = VASpac (&desc);
	if (Int32 (index) < 0) {
		throw BMOutOfMemoryException ("VA::Allocate: cannot allocate the needed memory!", __FILE__, __LINE__);
	}
	return &reinterpret_cast<Type*> (*desc.arrhdl)[index];
}


template <class Type>
Type*	VAArray<Type>::Begin (void)
{
	if (desc.arrhdl != nullptr)
		return reinterpret_cast<Type*> (*desc.arrhdl) + 1;

	return nullptr;
}


template <class Type>
Type*	VAArray<Type>::End (void)
{
	if (desc.arrhdl != nullptr)
		return reinterpret_cast<Type*> (*desc.arrhdl) + 1 + desc.lastind;

	return nullptr;
}


template <class Type>
const Type*		VAArray<Type>::Begin (void) const
{
	if (desc.arrhdl != nullptr)
		return reinterpret_cast<const Type*> (*desc.arrhdl) + 1;

	return nullptr;
}


template <class Type>
const Type*		VAArray<Type>::End (void) const
{
	if (desc.arrhdl != nullptr)
		return reinterpret_cast<const Type*> (*desc.arrhdl) + 1 + desc.lastind;

	return nullptr;
}


template <class Type>
auto	begin (VAArray<Type>& array)
{
	return array.Begin ();
}


template <class Type>
auto	end (VAArray<Type>& array)
{
	return array.End ();
}


template <class Type>
auto	begin (const VAArray<Type>& array)
{
	return array.Begin ();
}


template <class Type>
auto	end (const VAArray<Type>& array)
{
	return array.End ();
}


}	// namespace GS



#if defined (_MSC_VER)
#pragma warning (pop)
#endif

#endif	/* VAARRAY_HPP */
