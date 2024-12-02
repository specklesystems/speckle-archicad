// *********************************************************************************************************************
// Description:		PropertyListImp.hpp
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	HK
//
// *********************************************************************************************************************

#if !defined PROPERTYLISTIMP_HPP
#define PROPERTYLISTIMP_HPP

#include "UniString.hpp"
#include "uchar_t.hpp"
#include "ClassManager.hpp"

#if defined (macintosh)
#include <math.h>
#endif

#include "MemoryIChannel32.hpp"
#include "MemoryOChannel32.hpp"

// --- Function definitions --------------------------------------------------------------------------------------------

namespace GS {

template<class UserDataType>
inline PropertyList<UserDataType>::PropertyList ()
{
	names = nullptr;
	namesUsed = namesAllocated = 0;
	data = nullptr;
	dataUsed = dataAllocated = 0;
}

template<class UserDataType>
inline PropertyList<UserDataType>::~PropertyList ()
{
	delete [] names;
	delete [] data;
}

template<class UserDataType>
PropertyList<UserDataType>::PropertyList (const PropertyList& source) :
	entries (source.entries),
	nameToIndex (source.nameToIndex)
{
	ULong alloc = source.namesUsed > 0 ? Max (minNamesAlloc, source.namesUsed) : 0;
	names = alloc > 0 ? new char[alloc] : nullptr;
	namesUsed = source.namesUsed;
	namesAllocated = alloc;

	alloc = source.dataUsed > 0 ? Max (minDataAlloc, source.dataUsed) : 0;
	try { data = alloc > 0 ? new char[alloc] : nullptr; }
	catch (...) { delete names; throw; }
	dataUsed = source.dataUsed;
	dataAllocated = alloc;

	memcpy (names, source.names, namesUsed);
	memcpy (data, source.data, dataUsed);
}

template<class UserDataType>
const PropertyList<UserDataType>& PropertyList<UserDataType>::operator= (const PropertyList& source)
{
	if (this == &source)
		return *this;

	char* newNames = nullptr;
	char* newData = nullptr;

	ULong newNamesAlloc = 0;
	ULong newDataAlloc = 0;

	try {
		if (namesAllocated < source.namesUsed) {
			newNamesAlloc = Max (minNamesAlloc, source.namesUsed);
			newNames = new char[newNamesAlloc];
		}
		if (dataAllocated < source.dataUsed) {
			newDataAlloc = Max (minDataAlloc, source.dataUsed);
			newData = new char[newDataAlloc];
		}

		entries = source.entries;
	}
	catch (...) {
		delete [] newNames;
		delete [] newData;
		throw;
	}

	try { nameToIndex = source.nameToIndex; }
	catch (const Exception&) { nameToIndex.Clear (); }

	if (namesAllocated < source.namesUsed) {
		delete [] names;
		names = newNames;
		namesAllocated = newNamesAlloc;
	} else if (source.namesUsed == 0 && namesAllocated > 0) {
		delete [] names;
		names = nullptr;
		namesAllocated = 0;
	}
	namesUsed = source.namesUsed;
	memcpy (names, source.names, namesUsed);

	if (dataAllocated < source.dataUsed) {
		delete [] data;
		data = newData;
		dataAllocated = newDataAlloc;
	} else if (source.dataUsed == 0 && dataAllocated > 0) {
		delete [] data;
		data = nullptr;
		dataAllocated = 0;
	}
	dataUsed = source.dataUsed;
	memcpy (data, source.data, dataUsed);

	return *this;
}

template<class UserDataType>
GS_FORCE_INLINE ULong PropertyList<UserDataType>::GetEntryNum () const
{
	return entries.GetSize ();
}

template<class UserDataType>
ULong PropertyList<UserDataType>::GetFixEntryNum () const
{
	ULong fn = 0;
	for (ULong i = 0; i < entries.GetSize (); i++)
		if (entries[i].fix)
			fn++;

	return fn;
}

template<class UserDataType>
inline bool PropertyList<UserDataType>::IsEntryFix (ULong index) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	return entries[index].fix;
}

template<class UserDataType>
inline void PropertyList<UserDataType>::SetEntryFix (ULong index, bool fix)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	entries[index].fix = fix;
}

template<class UserDataType>
void PropertyList<UserDataType>::SetEntryName (ULong index, const char* name)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	Entry& en = entries[index];
	if (en.fix)
		throw GSException ();

	nameToIndex.Delete (CalcStrHashValue (names + en.nameOffset));

	ULong newLen = Strlen32 (name) + 1;
	ULong oldLen = Strlen32 (names + en.nameOffset) + 1;

	MoveNamesBlock (index, Int32 (newLen) - Int32 (oldLen), en.nameOffset + oldLen);
	memcpy (names + en.nameOffset, name, newLen);

	try { nameToIndex.Add (CalcStrHashValue (name), index); }
	catch (const Exception&) {}
}

template<class UserDataType>
inline const char* PropertyList<UserDataType>::GetEntryName (ULong index) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	return names + entries[index].nameOffset;
}

template<class UserDataType>
void PropertyList<UserDataType>::GetEntryName (ULong index, char* str, ULong maxCh) const
{
	if (!maxCh)
		return;

	const char* name = GetEntryName (index);
	const char* strLast = str + maxCh - 1;

	while (str < strLast && *name)
		*str++ = *name++;
	*str = 0;
}

template<class UserDataType>
ULong PropertyList<UserDataType>::GetIndexFromName (const char* name) const
{
	ULong index;
	if (nameToIndex.Get (CalcStrHashValue (name), &index) && CHEqualASCII (name, names + entries[index].nameOffset, GS::CaseInsensitive))
		return index;

	if (nameToIndex.GetSize () < entries.GetSize ()) {
		for (ULong i = 0; i < entries.GetSize (); i++) {
			if (CHEqualASCII (name, names + entries[i].nameOffset, GS::CaseInsensitive))
				return i;
		}
	}

	return MaxUIndex;
}

template<class UserDataType>
inline const UserDataType& PropertyList<UserDataType>::GetUserData (ULong index) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	return entries[index].userData;
}

template<class UserDataType>
inline UserDataType& PropertyList<UserDataType>::GetUserData (ULong index)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	return entries[index].userData;
}

template<class UserDataType>
void PropertyList<UserDataType>::ModifyEntryType (ULong index, StorageType st, ArrayType ar, ULong d1, ULong d2)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	Entry& en = entries[index];

	if (en.fix)
		if (st != en.storage || (ar == Scalar) != (en.arrayTp == Scalar))
			throw GSException ();

	switch (ar) {
		case Scalar:
			d1 = d2 = 1;
			break;
		case OneDimensional:
			if (d1 == 0)
				throw GSException ();
			d2 = 1;
			break;
		case TwoDimensional:
			if (d1 == 0 || d2 == 0)
				throw GSException ();
			break;
		default:
			throw GSException ();
	}

	ULong newLen = RoundUp8 (CalcExtLen (st, ar, d1, d2));
	MoveDataBlock (index, Int32 (newLen) - Int32 (en.dataLen), en.dataOffset + en.dataLen);

	memset (data + en.dataOffset, 0, newLen);
	en.value = 0;

	en.storage = st;
	en.arrayTp = ar;
	en.dim1 = d1;
	en.dim2 = d2;
}

template<class UserDataType>
void PropertyList<UserDataType>::ModifyArrayDimensions (ULong index, ArrayType ar, ULong d1, ULong d2)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	Entry& en = entries[index];

	if (en.arrayTp == ar) {
		switch (ar) {
			case Scalar:
				return;
			case OneDimensional:
				if (d1 == en.dim1)
					return;
				break;
			case TwoDimensional:
				if (d1 == en.dim1 && d2 == en.dim2)
					return;
				break;
		}
	}

	switch (ar) {
		case Scalar:
			d1 = d2 = 1;
			break;
		case OneDimensional:
			if (d1 == 0)
				throw GSException ();
			d2 = 1;
			break;
		case TwoDimensional:
			if (d1 == 0 || d2 == 0)
				throw GSException ();
			break;
		default:
			throw GSException ();
	}

	ULong oldDim1, oldDim2;
	switch (en.arrayTp) {
		case Scalar:
		default:
			oldDim1 = oldDim2 = 1;
			break;
		case OneDimensional:
			oldDim1 = en.dim1;
			oldDim2 = 1;
			break;
		case TwoDimensional:
			oldDim1 = en.dim1;
			oldDim2 = en.dim2;
			break;
	}

	ULong min1 = Min (oldDim1, d1);
	ULong min2 = Min (oldDim2, d2);

	ULong len;
	switch (en.storage) {
		case Integer:
		default:
			if (ar == Scalar)
				len = 0;
			else
				len = d1 * d2 * sizeof (Int32);
			break;

		case Numeric:
			len = d1 * d2 * sizeof (double);
			break;

		case String:
			{
				len = 0;
				const uchar_t* s = (const uchar_t*) (data + en.dataOffset);
				for (ULong i = 0; i < min1; i++) {
					for (ULong j = 0; j < min2; j++) {
						while (*s++)
							len++;
						len++;
					}
					for (ULong j = min2; j < oldDim2; j++)
						while (*s++)
							;
					if (d2 > min2)
						len += d2 - min2;
				}
				if (d1 > min1)
					len += (d1 - min1) * d2;

				len *= sizeof (uchar_t);
			}
			break;
	}

	char* arr = len > 0 ? new char[len] : nullptr;

	switch (en.storage) {
		case Integer:
			if (ar == Scalar)
				en.value = *(Int32*)(data + en.dataOffset);
			else if (en.arrayTp == Scalar) {
				memset (arr, 0, len);
				*(Int32*)arr = en.value;
			} else {
				Int32* to = (Int32*) arr;
				const Int32* from = (Int32*)(data + en.dataOffset);
				for (ULong i = 0; i < min1; i++) {
					for (ULong j = 0; j < min2; j++)
						*to++ = *from++;
					if (oldDim2 > min2)
						from += oldDim2 - min2;
					for (ULong j = min2; j < d2; j++)
						*to++ = 0;
				}
				if (d1 > min1 && to != nullptr)
					memset (to, 0, (d1 - min1) * d2 * sizeof (Int32));
			}
			break;

		case Numeric:
			{
				double* to = (double*) arr;
				const double* from = (double*)(data + en.dataOffset);
				for (ULong i = 0; i < min1; i++) {
					for (ULong j = 0; j < min2; j++)
						*to++ = *from++;
					if (oldDim2 > min2)
						from += oldDim2 - min2;
					for (ULong j = min2; j < d2; j++)
						*to++ = 0;
				}
				if (d1 > min1 && to != nullptr)
					memset (to, 0, (d1 - min1) * d2 * sizeof (double));
			}
			break;

		case String:
			{
				uchar_t* to = (uchar_t*) arr;
				const uchar_t* from = (uchar_t*)(data + en.dataOffset);
				for (ULong i = 0; i < min1; i++) {
					for (ULong j = 0; j < min2; j++) {
						do
							*to++ = *from;
						while (*from++);
					}
					for (ULong j = min2; j < oldDim2; j++)
						while (*from++)
							;
					for (ULong j = min2; j < d2; j++)
						*to++ = 0;
				}
				if (d1 > min1 && to != nullptr)
					memset (to, 0, (d1 - min1) * d2 * sizeof (uchar_t));
			}
			break;
	}

	ULong roundUpLen = RoundUp8 (len);
	try {
		MoveDataBlock (index, Int32 (roundUpLen) - Int32 (en.dataLen), en.dataOffset + en.dataLen);
	} catch (...) {
		delete [] arr;
		throw;
	}

	memcpy (data + en.dataOffset, arr, len);
	memset (data + en.dataOffset + len, 0, roundUpLen - len);
	delete [] arr;

	en.arrayTp = ar;
	en.dim1 = d1;
	en.dim2 = d2;
}

template<class UserDataType>
typename PropertyList<UserDataType>::StorageType PropertyList<UserDataType>::GetEntryType (ULong index, ArrayType* ar /* = nullptr */,
																				  ULong* d1 /* = nullptr */, ULong* d2 /* = nullptr */) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];

	if (ar)
		*ar = en.arrayTp;
	if (d1)
		*d1 = en.dim1;
	if (d2)
		*d2 = en.dim2;

	return en.storage;
}

template<class UserDataType>
inline bool PropertyList<UserDataType>::IsEntryScalar (ULong index) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	return entries[index].arrayTp == Scalar;
}

template<class UserDataType>
Int32 PropertyList<UserDataType>::GetIntEntry (ULong index) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];

	if (en.storage != Integer || en.arrayTp != Scalar)
		throw GSException ();

	return en.value;
}

template<class UserDataType>
double PropertyList<UserDataType>::GetNumEntry (ULong index) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];

	if (en.storage != Numeric || en.arrayTp != Scalar)
		throw GSException ();

	return *(const double*) (data + en.dataOffset);
}

template<class UserDataType>
const uchar_t* PropertyList<UserDataType>::GetStringEntry (ULong index) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];

	if (en.storage != String || en.arrayTp != Scalar)
		throw GSException ();

	return (const uchar_t*) (data + en.dataOffset);
}

template<class UserDataType>
GS_FORCE_INLINE void PropertyList<UserDataType>::GetStringEntry (ULong index, uchar_t* str, ULong maxCh) const
{
	CopyUStr (GetStringEntry (index), str, maxCh);
}

template<class UserDataType>
void PropertyList<UserDataType>::SetIntEntry (ULong index, Int32 val)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	Entry& en = entries[index];

	if (en.storage != Integer || en.arrayTp != Scalar)
		throw GSException ();

	en.value = val;
}

template<class UserDataType>
void PropertyList<UserDataType>::SetNumEntry (ULong index, double val)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];

	if (en.storage != Numeric || en.arrayTp != Scalar)
		throw GSException ();

	*(double*) (data + en.dataOffset) = val;
}

template<class UserDataType>
void PropertyList<UserDataType>::SetStringEntry (ULong index, const uchar_t* val)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	Entry& en = entries[index];
	ULong newLen = (ucslen32 (val) + 1) * sizeof (uchar_t);
	ULong roundUpLen = RoundUp8 (newLen);
	MoveDataBlock (index, Int32 (roundUpLen) - Int32 (en.dataLen), en.dataOffset + en.dataLen);
	memcpy (data + en.dataOffset, val, newLen);
	memset (data + en.dataOffset + newLen, 0, roundUpLen - newLen);
}


template<class UserDataType>
const Int32* PropertyList<UserDataType>::GetIntArray (ULong index, ULong* len /* = nullptr */, ULong* d1 /* = nullptr */, ULong* d2 /* = nullptr */) const
{
	StorageType st;
	const void* dt = GetArray (index, len, &st, d1, d2);
	if (st != Integer)
		throw GSException ();
	return (const Int32*) dt;
}

template<class UserDataType>
const double* PropertyList<UserDataType>::GetNumArray (ULong index, ULong* len /* = nullptr */, ULong* d1 /* = nullptr */, ULong* d2 /* = nullptr */) const
{
	StorageType st;
	const void* dt = GetArray (index, len, &st, d1, d2);
	if (st != Numeric)
		throw GSException ();
	return (const double*) dt;
}

template<class UserDataType>
const uchar_t* PropertyList<UserDataType>::GetStringArray (ULong index, ULong* len /* = nullptr */, ULong* d1 /* = nullptr */, ULong* d2 /* = nullptr */) const
{
	StorageType st;
	const void* dt = GetArray (index, len, &st, d1, d2);
	if (st != String)
		throw GSException ();
	return (const uchar_t*) dt;
}

template<class UserDataType>
const void* PropertyList<UserDataType>::GetArray (ULong index, ULong* len /* = nullptr */, StorageType* st /* = nullptr */, ULong* d1 /* = nullptr */,
												  ULong* d2 /* = nullptr */) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];

	if (st)
		*st = en.storage;
	if (d1)
		*d1 = en.dim1;
	if (d2)
		*d2 = en.dim2;

	if (en.storage == Integer && en.arrayTp == Scalar) {
		if (len)
			*len = sizeof (en.value);
		return &en.value;
	} else {
		if (len)
			*len = en.dataLen;
		return data + en.dataOffset;
	}
}

template<class UserDataType>
void PropertyList<UserDataType>::SetIntArray (ULong index, const Int32* vals)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	Entry& en = entries[index];
	if (en.storage != Integer)
		throw GSException ();

	if (en.arrayTp == Scalar)
		en.value = *vals;
	else
		memcpy (data + en.dataOffset, vals, en.dim1 * en.dim2 * sizeof (Int32));
}

template<class UserDataType>
void PropertyList<UserDataType>::SetNumArray (ULong index, const double* vals)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];
	if (en.storage != Numeric)
		throw GSException ();

	memcpy (data + en.dataOffset, vals, en.dim1 * en.dim2 * sizeof (double));
}

template<class UserDataType>
void PropertyList<UserDataType>::SetStringArray (ULong index, const uchar_t* vals)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	Entry& en = entries[index];
	if (en.storage != String)
		throw GSException ();

	ULong newLen = CalcExtLen (en.storage, en.arrayTp, en.dim1, en.dim2, vals);
	ULong roundUpLen = RoundUp8 (newLen);
	MoveDataBlock (index, Int32 (roundUpLen) - Int32 (en.dataLen), en.dataOffset + en.dataLen);
	memcpy (data + en.dataOffset, vals, newLen);
	memset (data + en.dataOffset + newLen, 0, roundUpLen - newLen);
}

template<class UserDataType>
Int32 PropertyList<UserDataType>::GetIntArrayVal (ULong index, ULong i1, ULong i2) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];
	if (en.storage != Integer)
		throw GSException ();

	if (en.arrayTp == Scalar)
		return en.value;
	else
		return ((Int32*)(data + en.dataOffset))[GetArrayElementIndex (en, i1, i2)];
}

template<class UserDataType>
double PropertyList<UserDataType>::GetNumArrayVal (ULong index, ULong i1, ULong i2) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];
	if (en.storage != Numeric)
		throw GSException ();

	return ((double*)(data + en.dataOffset))[GetArrayElementIndex (en, i1, i2)];
}

template<class UserDataType>
const uchar_t* PropertyList<UserDataType>::GetStringArrayVal (ULong index, ULong i1, ULong i2) const
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];
	if (en.storage != String)
		throw GSException ();

	return GetIthStr ((uchar_t*)(data + en.dataOffset), GetArrayElementIndex (en, i1, i2));
}

template<class UserDataType>
GS_FORCE_INLINE void PropertyList<UserDataType>::GetStringArrayVal (ULong index, ULong i1, ULong i2, uchar_t* str, ULong maxCh) const
{
	CopyUStr (GetStringArrayVal (index, i1, i2), str, maxCh);
}

template<class UserDataType>
void PropertyList<UserDataType>::SetIntArrayVal (ULong index, ULong i1, ULong i2, Int32 val)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	Entry& en = entries[index];
	if (en.storage != Integer)
		throw GSException ();

	if (en.arrayTp == Scalar)
		en.value = val;
	else
		((Int32*)(data + en.dataOffset))[GetArrayElementIndex (en, i1, i2)] = val;
}

template<class UserDataType>
void PropertyList<UserDataType>::SetNumArrayVal (ULong index, ULong i1, ULong i2, double val)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	const Entry& en = entries[index];
	if (en.storage != Numeric)
		throw GSException ();

	((double*)(data + en.dataOffset))[GetArrayElementIndex (en, i1, i2)] = val;
}

template<class UserDataType>
void PropertyList<UserDataType>::SetStringArrayVal (ULong index, ULong i1, ULong i2, const uchar_t* val)
{
	if (index >= entries.GetSize ())
		throw GSException ();

	Entry& en = entries[index];
	if (en.storage != String)
		throw GSException ();

	ULong elemIndex = GetArrayElementIndex (en, i1, i2);
	uchar_t* us = GetIthStr ((uchar_t*)(data + en.dataOffset), elemIndex);
	char* s = (char*) us;
	ULong oldUStringLen = ucslen32 (us) + 1;
	uchar_t* endUS = GetIthStr (us + oldUStringLen, en.dim1 * en.dim2 - elemIndex - 1);
	char* endS = (char*) endUS;

	ULong beforeLen = ULong (s - (data + en.dataOffset));
	ULong oldLen = oldUStringLen * sizeof (uchar_t);
	ULong afterLen = ULong (endS - (data + en.dataOffset) - beforeLen - oldLen);
	ULong newLen = (ucslen32 (val) + 1) * sizeof (uchar_t);

	if (newLen < oldLen)
		memmove (s + newLen, s + oldLen, afterLen);
	ULong newCompleteLen = beforeLen + newLen + afterLen;
	ULong roundUpLen = RoundUp8 (newCompleteLen);
	MoveDataBlock (index, Int32 (roundUpLen) - Int32 (en.dataLen), en.dataOffset + en.dataLen);
	s = data + en.dataOffset + beforeLen;
	if (newLen > oldLen)
		memmove (s + newLen, s + oldLen, afterLen);
	memcpy (s, val, newLen);
	memset (data + en.dataOffset + newCompleteLen, 0, roundUpLen - newCompleteLen);
}

template<class UserDataType>
void PropertyList<UserDataType>::Clear ()
{
	entries.Clear ();
	nameToIndex.Clear ();

	delete [] names;
	delete [] data;

	names = nullptr;
	data = nullptr;

	namesUsed = namesAllocated = dataUsed = dataAllocated = 0;
}

template<class UserDataType>
void PropertyList<UserDataType>::DeleteEntries (ULong firstIndex, ULong lastIndex)
{
	if (lastIndex >= entries.GetSize ())
		lastIndex = entries.GetSize () - 1;

	if (entries.GetSize () == 0 || lastIndex < firstIndex)
		return;

	for (ULong i = firstIndex; i <= lastIndex; i++)
		if (entries[i].fix)
			throw GSException ();

	for (ULong i = firstIndex; i <= lastIndex; i++)
		nameToIndex.Delete (CalcStrHashValue (names + entries[i].nameOffset));
	for (ULong i = lastIndex + 1, j = firstIndex; i < entries.GetSize (); i++, j++) {
		ULong* in;
		if (nameToIndex.Get (CalcStrHashValue (names + entries[i].nameOffset), &in))
			*in = j;
	}

	Entry& enBeg = entries[firstIndex];
	Entry& enEnd = entries[lastIndex];

	ULong off1 = enBeg.nameOffset;
	ULong off2 = lastIndex + 1 == entries.GetSize () ? namesUsed : entries[lastIndex + 1].nameOffset;

	memmove (names + off1, names + off2, namesUsed - off2);
	for (ULong i = lastIndex + 1; i < entries.GetSize (); i++)
		entries[i].nameOffset -= off2 - off1;
	namesUsed -= off2 - off1;

	off1 = enBeg.dataOffset;
	off2 = enEnd.dataOffset + enEnd.dataLen;

	memmove (data + off1, data + off2, dataUsed - off2);
	for (ULong i = lastIndex + 1; i < entries.GetSize (); i++)
		entries[i].dataOffset -= off2 - off1;
	dataUsed -= off2 - off1;

	entries.Delete (firstIndex, lastIndex - firstIndex + 1);
}

template<class UserDataType>
void PropertyList<UserDataType>::InsertEntries (const PropertyList& source, ULong firstIndex, ULong lastIndex, ULong destIndex)
{
	if (&source == this) {
		const PropertyList copySource = source;
		InsertEntries (copySource, firstIndex, lastIndex, destIndex);
		return;
	}

	if (lastIndex < firstIndex)
		return;

	ULong origSize = entries.GetSize ();

	if (lastIndex >= source.entries.GetSize () || destIndex > origSize)
		throw GSException ();

	ULong destNameOffset = destIndex < origSize ? entries[destIndex].nameOffset : namesUsed;
	ULong destDataOffset = destIndex < origSize ? entries[destIndex].dataOffset : dataUsed;

	Int32 nameOffs = Int32 (source.entries[firstIndex].nameOffset) - Int32 (destNameOffset);
	Int32 dataOffs = Int32 (source.entries[firstIndex].dataOffset) - Int32 (destDataOffset);

	ULong nOff1 = source.entries[firstIndex].nameOffset;
	ULong nOff2 = lastIndex + 1 < source.entries.GetSize () ? source.entries[lastIndex + 1].nameOffset : source.namesUsed;
	ULong newNamesUsed = namesUsed + nOff2 - nOff1;

	ULong dOff1 = source.entries[firstIndex].dataOffset;
	ULong dOff2 = source.entries[lastIndex].dataOffset + source.entries[lastIndex].dataLen;
	ULong newDataUsed = dataUsed + dOff2 - dOff1;

	ULong newNamesAlloc = 0;
	char* newNames = nullptr;

	ULong newDataAlloc = 0;
	char* newData = nullptr;

	try {
		if (newNamesUsed > namesAllocated) {
			newNamesAlloc = Max (minNamesAlloc, Max (newNamesUsed, namesAllocated * 2));
			newNames = new char[newNamesAlloc];
		}

		if (newDataUsed > dataAllocated) {
			newDataAlloc = Max (minDataAlloc, Max (newDataUsed, dataAllocated * 2));
			newData = new char[newDataAlloc];
		}

		entries.IncreaseSize (lastIndex - firstIndex + 1);
	}
	catch (...) {
		delete [] newNames;
		delete [] newData;
		throw;
	}

	if (newNamesUsed > namesAllocated) {
		memcpy (newNames, names, destNameOffset);
		memcpy (newNames + destNameOffset + nOff2 - nOff1, names + destNameOffset, namesUsed - destNameOffset);
		delete [] names;
		names = newNames;
		namesAllocated = newNamesAlloc;
	} else
		memmove (names + destNameOffset + nOff2 - nOff1, names + destNameOffset, namesUsed - destNameOffset);
	memcpy (names + destNameOffset, source.names + nOff1, nOff2 - nOff1);
	namesUsed = newNamesUsed;

	if (newDataUsed > dataAllocated) {
		memcpy (newData, data, destDataOffset);
		memcpy (newData + destDataOffset + dOff2 - dOff1, data + destDataOffset, dataUsed - destDataOffset);
		delete [] data;
		data = newData;
		dataAllocated = newDataAlloc;
	} else
		memmove (data + destDataOffset + dOff2 - dOff1, data + destDataOffset, dataUsed - destDataOffset);
	memcpy (data + destDataOffset, source.data + dOff1, dOff2 - dOff1);
	dataUsed = newDataUsed;

	for (ULong i = origSize, j = entries.GetSize (); i > destIndex; ) {
		entries[--j] = entries[--i];
		entries[j].nameOffset += nOff2 - nOff1;
		entries[j].dataOffset += dOff2 - dOff1;
	}

	for (ULong i = firstIndex, j = destIndex; i <= lastIndex; i++, j++) {
		entries[j] = source.entries[i];
		entries[j].nameOffset -= nameOffs;
		entries[j].dataOffset -= dataOffs;
		entries[j].fix = false;
	}

	for (ULong i = destIndex + lastIndex - firstIndex + 1; i < entries.GetSize (); i++) {
		ULong* in;
		if (nameToIndex.Get (CalcStrHashValue (names + entries[i].nameOffset), &in))
			*in = i;
	}

	try {
		for (ULong i = firstIndex, j = destIndex; i <= lastIndex; i++, j++)
			nameToIndex.Add (CalcStrHashValue (source.names + source.entries[i].nameOffset), j);
	}
	catch (const Exception&) {}
}

template<class UserDataType>
void PropertyList<UserDataType>::InsertNewEntry (ULong index, const char* name, StorageType st, ArrayType ar, ULong d1, ULong d2)
{
	if (index > entries.GetSize ())
		throw GSException ();

	ULong newAlloc = 0;
	char* newNames = nullptr;

	ULong nameLen = Strlen32 (name) + 1;
	ULong newUsed = namesUsed + nameLen;
	if (newUsed > namesAllocated) {
		newAlloc = Max (minDataAlloc, Max (newUsed, namesAllocated * 2));
		newNames = new char[newAlloc];
	}

	Entry entry;

	entry.storage = Integer;
	entry.arrayTp = Scalar;
	entry.fix = false;
	entry.dim1 = entry.dim2 = 1;
	entry.value = 0;
	if (index == entries.GetSize ()) {
		entry.nameOffset = namesUsed;
		entry.dataOffset = dataUsed;
	} else {
		entry.nameOffset = entries[index].nameOffset;
		entry.dataOffset = entries[index].dataOffset;
	}
	entry.dataLen = 0;

	try { entries.Insert (index, entry); }
	catch (...) {
		delete [] newNames;
		throw;
	}

	if (newUsed > namesAllocated) {
		memcpy (newNames, names, entry.nameOffset);
		memcpy (newNames + entry.nameOffset + nameLen, names + entry.nameOffset, namesUsed - entry.nameOffset);
		delete [] names;
		names = newNames;
		namesAllocated = newAlloc;
	} else
		memmove (names + entry.nameOffset + nameLen, names + entry.nameOffset, namesUsed - entry.nameOffset);
	memcpy (names + entry.nameOffset, name, nameLen);
	namesUsed = newUsed;

	for (ULong i = index + 1; i < entries.GetSize (); i++) {
		entries[i].nameOffset += nameLen;
		ULong* in;
		if (nameToIndex.Get (CalcStrHashValue (names + entries[i].nameOffset), &in))
			*in = i;
	}

	try { nameToIndex.Add (CalcStrHashValue (name), index); }
	catch (const Exception&) {}

	try { ModifyEntryType (index, st, ar, d1, d2); }
	catch (...) {
		DeleteEntries (index, index);
		throw;
	}
}

template<class UserDataType>
GS_FORCE_INLINE ULong PropertyList<UserDataType>::PushEntry (const char* name, StorageType st, ArrayType ar, ULong d1, ULong d2)
{
	ULong insertPos = entries.GetSize ();

	InsertNewEntry (insertPos, name, st, ar, d1, d2);
	return insertPos;
}

template<class UserDataType>
void PropertyList<UserDataType>::CopyWithOverwrite (const PropertyList& source, ULong firstIndex, ULong lastIndex, ULong destIndex)
{
	for (ULong i = destIndex, j = firstIndex; i < entries.GetSize () && j <= lastIndex; i++, j++)
		if (entries[i].fix)
			throw GSException ();

	InsertEntries (source, firstIndex, lastIndex, destIndex);
	DeleteEntries (destIndex + lastIndex - firstIndex + 1, destIndex + (lastIndex - firstIndex) * 2 + 1);

	try {
		for (ULong i = destIndex, j = firstIndex; j <= lastIndex; i++, j++)
			nameToIndex.Add (CalcStrHashValue (names + entries[i].nameOffset), i);
	} catch (const Exception&) {}
}

template<class UserDataType>
void PropertyList<UserDataType>::ReplaceEntry (ULong oldIndex, ULong newIndex)
{
	if (oldIndex >= entries.GetSize () || newIndex >= entries.GetSize ())
		throw GSException ();

	if (oldIndex == newIndex)
		return;

	PropertyList pl;
	pl.InsertEntries (*this, oldIndex, oldIndex, 0);

	bool fix = entries[oldIndex].fix;

	if (oldIndex < newIndex) {
		InsertEntries (pl, 0, 0, newIndex + 1);
		entries[oldIndex].fix = false;
		DeleteEntries (oldIndex, oldIndex);
	} else {
		InsertEntries (pl, 0, 0, newIndex);
		entries[oldIndex + 1].fix = false;
		DeleteEntries (oldIndex + 1, oldIndex + 1);
	}

	try { nameToIndex.Add (CalcStrHashValue (names + entries[newIndex].nameOffset), newIndex); }
	catch (const Exception&) {}

	entries[newIndex].fix = fix;
}

template<class UserDataType>
void PropertyList<UserDataType>::Write (OChannel& oc) const
{
	OutputFrame plFrame (oc, *GetPropertyListTemplateClassInfo ());
	if (oc.GetOutputStatus () != NoError)
		throw GSException ();

	ClassVersion userDataVersion = UserDataType::GetClassInfo ()->GetVersion (classManager.GetOutputVersion ());
	if (userDataVersion.Write (oc) != NoError)
		throw GSException ();

	WriteVersion (oc, plFrame.GetVersion (), userDataVersion);
}

template<class UserDataType>
void PropertyList<UserDataType>::Read (IChannel& ic)
{
	Clear ();

	try {
		InputFrame plFrame (ic, *GetPropertyListTemplateClassInfo ());
		if (plFrame.GetStatus () != NoError)
			throw GSException ();

		ClassVersion userDataVersion;
		if (userDataVersion.Read (ic) != NoError || userDataVersion > UserDataType::GetClassInfo ()->GetVersion ())
			throw GSException ();

		ReadVersion (ic, plFrame.GetVersion (), userDataVersion);

		CheckIntegrity ();
	}
	catch (...) {
		Clear ();
		throw;
	}

	try {
		for (ULong i = 0; i < entries.GetSize (); i++)
			nameToIndex.Add (CalcStrHashValue (names + entries[i].nameOffset), i);
	} catch (const Exception&) {}
}

template<class UserDataType>
void PropertyList<UserDataType>::WriteXML (GS::XMLOChannel& outXML) const
{
	// XML tags
	static const char* XMLTag_PropertyList		= "PropertyList";
	static const char* XMLTag_Entry				= "Entry";
	static const char* XMLTag_EntryStorage		= "storage";
	static const char* XMLTag_EntryArrayTp		= "arrayTp";
	static const char* XMLTag_EntryFix			= "fix";
	static const char* XMLTag_EntryDim1			= "dim1";
	static const char* XMLTag_EntryDim2			= "dim2";
	static const char* XMLTag_EntryUserData		= "UserData";
	static const char* XMLTag_EntryUserDataSize	= "size";
	static const char* XMLTag_EntryName			= "name";
	static const char* XMLTag_EntryDataArray	= "DataArray";
	static const char* XMLTag_EntryData			= "data";

	DBASSERT (outXML.GetErrorStatus () == GS::XMLOChannel::Ok);

	outXML.WriteStartElement (XMLTag_PropertyList); {
		for (ULong i = 0; i < entries.GetSize (); i++) {
			const Entry& en = entries[i];
			outXML.WriteStartElement (XMLTag_Entry); {
				// Write the data stored in the Entry itself
				outXML.WriteXML (XMLTag_EntryStorage, en.storage);
				outXML.WriteXML (XMLTag_EntryArrayTp, en.arrayTp);
				outXML.WriteXML (XMLTag_EntryFix, en.fix);
				outXML.WriteXML (XMLTag_EntryDim1, en.dim1);
				outXML.WriteXML (XMLTag_EntryDim2, en.dim2);

				// Name offset, data offset and data len are not saved (to keep the xml modifiable).
				// The en.value is only non-zero, if the entry is an integer scalar, and then there is no
				// data. However the xml gets clearer, if the en.value is saved as data too.
					
				// Write the name of this entry
				const char* name = GetEntryName (i);
				outXML.WriteXML (XMLTag_EntryName, name, Strlen32(name));

				// Write the entry data
				outXML.WriteStartElement (XMLTag_EntryDataArray); {
					switch (en.storage) {
					case Integer:
						{
							if (en.arrayTp == Scalar) {
								outXML.WriteXML (XMLTag_EntryData, en.value);
							} else {
								ULong n = en.dim1 * en.dim2;
								const Int32* ip = (const Int32*) (data + en.dataOffset);
								for (ULong j = 0; j < n; j++) {
									outXML.WriteXML (XMLTag_EntryData, ip[j]);
								}
							}
						}
						break;
					case Numeric:
						{
							ULong n = en.dim1 * en.dim2;
							const double* dp = (const double*) (data + en.dataOffset);
							for (ULong j = 0; j < n; j++) {
								outXML.WriteXML (XMLTag_EntryData, dp[j]);
							}
						}
						break;
					case String:
						{
							ULong n = en.dim1 * en.dim2;
							ULong elemOffset = 0;
							for (ULong j = 0; j < n; j++) {
								const uchar_t* cp = (const uchar_t*) (data + en.dataOffset + elemOffset);
								GS::UniString uniString = GS::UniString (cp);
								outXML.WriteXML (XMLTag_EntryData, uniString);
								elemOffset += (uniString.GetLength ()+1) * sizeof (uchar_t);
							}
						}
						break;
					}
				} outXML.WriteEndElement (); // DataArray

				// write userData as CDATA
				outXML.WriteStartElement (XMLTag_EntryUserData); {
					GS::MemoryOChannel32 oc;
					ClassVersion userDataVersion = UserDataType::GetClassInfo ()->GetVersion (classManager.GetOutputVersion ());
					en.userData.Write (oc, userDataVersion);
					ULong userDataSize = oc.GetDataSize ();
					outXML.WriteXML (XMLTag_EntryUserDataSize, userDataSize);
					outXML.WriteStartElement (XMLTag_EntryData); {
						outXML.WriteXMLCDATABinToHex (oc.GetDestination (), userDataSize);
					} outXML.WriteEndElement ();
				} outXML.WriteEndElement (); // user data
			} outXML.WriteEndElement (); // entry
		} // for loop
	} outXML.WriteEndElement (); // property list

	DBASSERT (outXML.GetErrorStatus () == GS::XMLOChannel::Ok);
}

template<class UserDataType>
void PropertyList<UserDataType>::ReadXML (GS::XMLIChannel& inXML) 
{
	// XML tags
	static const char* XMLTag_PropertyList		= "PropertyList";
	static const char* XMLTag_Entry				= "Entry";
	static const char* XMLTag_EntryStorage		= "storage";
	static const char* XMLTag_EntryArrayTp		= "arrayTp";
	static const char* XMLTag_EntryFix			= "fix";
	static const char* XMLTag_EntryDim1			= "dim1";
	static const char* XMLTag_EntryDim2			= "dim2";
	static const char* XMLTag_EntryUserData		= "UserData";
	static const char* XMLTag_EntryUserDataSize	= "size";
	static const char* XMLTag_EntryName			= "name";
	static const char* XMLTag_EntryDataArray	= "DataArray";
	static const char* XMLTag_EntryData			= "data";

	if (!DBVERIFY (inXML.GetErrorStatus () == GS::XMLIChannel::Ok)) {
		throw GS::Exception ("Error in PropertyList<UserDataType>::ReadXML.", __FILE__, __LINE__);
	}

	Clear ();

	inXML.ReadStartElement (XMLTag_PropertyList); {
		Entry en;
		short s;
		bool b;
		GS::UniString uStr;
		GS::UniString nextTokenName; // unused, but required by GetNextTokenTypeName
		GS::MemoryOChannel32 dataMemChannel;

		while (inXML.GetNextTokenTypeName (nextTokenName) != GS::XMLEndTag) {
			inXML.ReadStartElement (XMLTag_Entry); {
				ULong entryIndex = GetEntryNum ();

				// read the data stored in the Entry itself
				inXML.ReadXML (XMLTag_EntryStorage, s);
				en.storage = static_cast<StorageType> (s);
				inXML.ReadXML (XMLTag_EntryArrayTp, s);
				en.arrayTp = static_cast<ArrayType> (s);
				inXML.ReadXML (XMLTag_EntryFix, b);
				en.fix = b;
				inXML.ReadXML (XMLTag_EntryDim1, en.dim1);
				inXML.ReadXML (XMLTag_EntryDim2, en.dim2);
					
				// read the name
				inXML.ReadXML (XMLTag_EntryName, uStr);
				const auto& cstr = uStr.ToCStr ();
				ULong strLen = Strlen32 (cstr);

				// allocate space for the read name (if needed)
				ULong requiredSize = namesUsed + strLen + 1;
				if (requiredSize > namesAllocated) {
					ULong newAlloc = Max (minNamesAlloc, Max (requiredSize, namesAllocated * 2));
					char* newNames = new char[newAlloc];
					memcpy (newNames, names, namesUsed);
					delete [] names;
					names = newNames;
					namesAllocated = newAlloc;
				}

				// mark the start of the name of this entry
				en.nameOffset = namesUsed;	

				// copy the name into the names array
				memcpy (names + en.nameOffset, cstr, strLen + 1);
				namesUsed += strLen + 1;

				// add it to the hash table
				try { nameToIndex.Add (CalcStrHashValue (cstr), entryIndex); }
				catch (const Exception&) {}

				en.value = 0;

				// read the data
				inXML.ReadStartElement (XMLTag_EntryDataArray); {
					// the current data starts at the end of the previously read data
					en.dataOffset = dataMemChannel.GetDataSize ();

					switch (en.storage) {
						case Integer:
							{
								if (en.arrayTp == Scalar) {
									inXML.ReadXML (XMLTag_EntryData, en.value);
								} else {
									Int32 temp;
									ULong n = en.dim1 * en.dim2;
									for (ULong j = 0; j < n; j++) {
										inXML.ReadXML (XMLTag_EntryData, temp);
										dataMemChannel.Write (temp);
									}
								}
							}
							break;
						case Numeric:
							{
								double temp;
								ULong n = en.dim1 * en.dim2;
								for (ULong j = 0; j < n; j++) {
									inXML.ReadXML (XMLTag_EntryData, temp);
									dataMemChannel.Write (temp);
								}
							}
							break;
						case String:
							{
								GS::UniString temp;
								ULong n = en.dim1 * en.dim2;
								for (ULong j = 0; j < n; j++) {
									inXML.ReadXML (XMLTag_EntryData, temp);
									ULong stringSize = (temp.GetLength ()+1) * sizeof (uchar_t);
									dataMemChannel.WriteBin ((char*)temp.ToUStr ().Get (), stringSize, nullptr);
									
								}
								ULong sumSize = dataMemChannel.GetDataSize () - en.dataOffset;
								ULong paddingSize = RoundUp8 (sumSize) - sumSize;
								for (ULong i = 0; i < paddingSize; i++) {
									dataMemChannel.WriteUChar (0);
								}
							}
							break;
					}
				
					// The length of the data is the number of bytes written into the MemChannel
					en.dataLen = dataMemChannel.GetDataSize () - en.dataOffset;
				} inXML.ReadEndElement (XMLTag_EntryDataArray);

				// read the userData (which is CDATA)
				inXML.ReadStartElement (XMLTag_EntryUserData); {
					ULong userDataSize;
					inXML.ReadXML (XMLTag_EntryUserDataSize, userDataSize);
					GS::Owner<char[]> userData (new char[userDataSize]);

					inXML.ReadStartElement (XMLTag_EntryData); {
						inXML.ReadXMLCDATAHexToBin (userData.Get (), userDataSize);
					} inXML.ReadEndElement (XMLTag_EntryData);
					GS::MemoryIChannel32 ic (userData.Get (), userDataSize);
					ClassVersion userDataVersion = UserDataType::GetClassInfo ()->GetVersion (classManager.GetOutputVersion ());
					en.userData.Read (ic, userDataVersion);
				} inXML.ReadEndElement (XMLTag_EntryUserData);
			} inXML.ReadEndElement (XMLTag_Entry);

			entries.Push(en);
		} // while the next XML node is not an XMLEndTag 

		dataUsed = dataMemChannel.GetDataSize ();
		dataAllocated = dataUsed > 0 ? Max (minDataAlloc, dataUsed) : 0;
		if (dataAllocated > 0) {
			data = new char[dataAllocated];
			memcpy (data, dataMemChannel.GetDestination (), dataUsed);
		} else {
			data = nullptr;
		}
	} inXML.ReadEndElement (XMLTag_PropertyList);

	if (!DBVERIFY (inXML.GetErrorStatus () == GS::XMLIChannel::Ok)) {
		Clear();
		throw GS::Exception ("Error in PropertyList<UserDataType>::ReadXML.", __FILE__, __LINE__);
	}
}

template<class UserDataType>
bool PropertyList<UserDataType>::Equals (const PropertyList& op) const
{
	if (entries.GetSize () != op.entries.GetSize ())
		return false;

	for (ULong i = 0; i < entries.GetSize (); i++) {
		const Entry& en = entries[i];
		const Entry& enOp = op.entries[i];

		if (en.storage != enOp.storage || en.arrayTp != enOp.arrayTp || en.dim1 != enOp.dim1 || en.dim2 != enOp.dim2)
			return false;

		if (!CHEqualASCII (names + en.nameOffset, op.names + enOp.nameOffset, GS::CaseInsensitive))
			return false;

		if (en.storage == Integer && en.arrayTp == Scalar) {
			if (en.value != enOp.value)
				return false;
		} else if (en.storage == Numeric) {
			ULong itemNum = en.dim1 * en.dim2;
			const double* dVals = (const double*) (data + en.dataOffset);
			const double* dValsOp = (const double*) (op.data + enOp.dataOffset);
			for (ULong j = 0; j < itemNum; j++)
				if (fabs (dVals[j] - dValsOp[j]) > 1e-5)
					return false;
		} else {
			if (en.dataLen != enOp.dataLen || memcmp (data + en.dataOffset, op.data + enOp.dataOffset, en.dataLen) != 0)
				return false;
		}
	}

	return true;
}

template<class UserDataType>
Int32 PropertyList<UserDataType>::CheckSum (double* sumVars) const
{
	Int32 checkSum = entries.GetSize ();
	if (sumVars)
		*sumVars = entries.GetSize ();

	for (ULong i = 0; i < entries.GetSize (); i++) {
		const Entry& en = entries[i];

		checkSum += en.storage;
		checkSum += en.arrayTp;
		checkSum += en.dim1;
		checkSum += en.dim2;

		checkSum += CalcLongCheckSum (names + en.nameOffset, Strlen32 (names + en.nameOffset));

		if (en.storage == Integer && en.arrayTp == Scalar) {
			if (sumVars)
				*sumVars += en.value;
			checkSum += en.value;
		} else if (en.storage == Numeric) {
			const double* pVal = (const double*) (data + en.dataOffset);
			ULong nVals = en.dim1 * en.dim2;
			for (ULong j = 0; j < nVals; j++) {
				if (sumVars)
					*sumVars += pVal[j];

				checkSum += Int32 (pVal[j] * 10000);
			}
		} else
			checkSum += CalcLongCheckSum (data + en.dataOffset, en.dataLen);
	}

	return checkSum;
}

template<class UserDataType>
GS_FORCE_INLINE ULong PropertyList<UserDataType>::GetAllocatedBytes () const
{
	return entries.GetSize () * sizeof (Entry) + namesAllocated + dataAllocated;
}

template<class UserDataType>
GS_FORCE_INLINE typename PropertyList<UserDataType>::ConstEntryRef PropertyList<UserDataType>::operator[] (ULong index) const
{
	return ConstEntryRef (this, index);
}

template<class UserDataType>
inline typename PropertyList<UserDataType>::ConstEntryRef PropertyList<UserDataType>::operator[] (const char* name) const
{
	ULong index = GetIndexFromName (name);
	if (index == MaxUIndex)
		throw GSException ();

	return ConstEntryRef (this, index);
}

template<class UserDataType>
GS_FORCE_INLINE typename PropertyList<UserDataType>::EntryRef PropertyList<UserDataType>::operator[] (ULong index)
{
	return EntryRef (this, index);
}

template<class UserDataType>
inline typename PropertyList<UserDataType>::EntryRef PropertyList<UserDataType>::operator[] (const char* name)
{
	ULong index = GetIndexFromName (name);
	if (index == MaxUIndex)
		throw GSException ();

	return EntryRef (this, index);
}

template<class UserDataType>
GS_FORCE_INLINE PropertyList<UserDataType>::ConstEntryRef::ConstEntryRef ()
{
}

template<class UserDataType>
PropertyList<UserDataType>::ConstEntryRef::ConstEntryRef (const PropertyList* pl, ULong ind) :
	propList (pl),
	entryIndex (ind),
	i1 (MaxUIndex),
	i2 (MaxUIndex)
{
	if (ind >= pl->entries.GetSize ())
		throw GSException ();

	arrayTp = pl->entries[ind].arrayTp;
}

template<class UserDataType>
GS_FORCE_INLINE PropertyList<UserDataType>::ConstEntryRef::operator Int32 () const
{
	return GetInt ();
}

template<class UserDataType>
inline PropertyList<UserDataType>::ConstEntryRef::operator double () const
{
	return propList->entries[entryIndex].storage == Integer ? double (GetInt ()) : GetNum ();
}

template<class UserDataType>
GS_FORCE_INLINE const uchar_t* PropertyList<UserDataType>::ConstEntryRef::ToUStr () const
{
	return GetString ();
}

template<class UserDataType>
typename PropertyList<UserDataType>::ConstEntryRef PropertyList<UserDataType>::ConstEntryRef::operator[] (ULong i) const
{
	ConstEntryRef rf = *this;
	switch (arrayTp) {
		case Scalar:
			throw GSException ();
		case OneDimensional:
			rf.arrayTp = Scalar;
			if (i1 == MaxUIndex) {
				if (i < 1 || i > propList->entries[entryIndex].dim1)
					throw GSException ();
				rf.i1 = i;
			} else {
				if (i < 1 || i > propList->entries[entryIndex].dim2)
					throw GSException ();
				rf.i2 = i;
			}
			break;
		case TwoDimensional:
			rf.arrayTp = OneDimensional;
			if (i < 1 || i > propList->entries[entryIndex].dim1)
				throw GSException ();
			rf.i1 = i;
			break;
	}

	return rf;
}

template<class UserDataType>
GS_FORCE_INLINE bool PropertyList<UserDataType>::ConstEntryRef::IsFix () const
{
	return propList->IsEntryFix (entryIndex);
}

template<class UserDataType>
GS_FORCE_INLINE const char* PropertyList<UserDataType>::ConstEntryRef::GetName () const
{
	return propList->GetEntryName (entryIndex);
}

template<class UserDataType>
GS_FORCE_INLINE void PropertyList<UserDataType>::ConstEntryRef::GetName (char* str, ULong maxCh) const
{
	propList->GetEntryName (entryIndex, str, maxCh);
}

template<class UserDataType>
GS_FORCE_INLINE const UserDataType& PropertyList<UserDataType>::ConstEntryRef::GetUserData () const
{
	return propList->GetUserData (entryIndex);
}

template<class UserDataType>
GS_FORCE_INLINE typename PropertyList<UserDataType>::StorageType PropertyList<UserDataType>::ConstEntryRef::GetType (ArrayType* ar /* = nullptr */,
																								ULong* d1 /* = nullptr */, ULong* d2 /* = nullptr */) const
{
	return propList->GetEntryType (entryIndex, ar, d1, d2);
}

template<class UserDataType>
Int32 PropertyList<UserDataType>::ConstEntryRef::GetInt () const
{
	if (arrayTp != Scalar)
		throw GSException ();

	if (propList->entries[entryIndex].arrayTp == Scalar)
		return propList->GetIntEntry (entryIndex);
	else
		return propList->GetIntArrayVal (entryIndex, i1, i2);
}

template<class UserDataType>
double PropertyList<UserDataType>::ConstEntryRef::GetNum () const
{
	if (arrayTp != Scalar)
		throw GSException ();

	if (propList->entries[entryIndex].arrayTp == Scalar)
		return propList->GetNumEntry (entryIndex);
	else
		return propList->GetNumArrayVal (entryIndex, i1, i2);
}

template<class UserDataType>
const uchar_t* PropertyList<UserDataType>::ConstEntryRef::GetString () const
{
	if (arrayTp != Scalar)
		throw GSException ();

	if (propList->entries[entryIndex].arrayTp == Scalar)
		return propList->GetStringEntry (entryIndex);
	else
		return propList->GetStringArrayVal (entryIndex, i1, i2);
}

template<class UserDataType>
GS_FORCE_INLINE void PropertyList<UserDataType>::ConstEntryRef::GetString (Owner<char[]>* str) const
{
	CopyUStr (GetString (), str);
}

template<class UserDataType>
GS_FORCE_INLINE void PropertyList<UserDataType>::ConstEntryRef::GetString (uchar_t* str, ULong maxCh) const
{
	CopyUStr (GetString (), str, maxCh);
}

template<class UserDataType>
GS_FORCE_INLINE void PropertyList<UserDataType>::ConstEntryRef::GetString (char* str, ULong maxCh) const
{
	CopyUStr (GetString (), str, maxCh);
}

template<class UserDataType>
GS_FORCE_INLINE PropertyList<UserDataType>::EntryRef::EntryRef ()
{
}

template<class UserDataType>
inline PropertyList<UserDataType>::EntryRef::EntryRef (PropertyList* pl, ULong ind) :
	ConstEntryRef (pl, ind),
	propList (pl)
{
}

template<class UserDataType>
inline Int32 PropertyList<UserDataType>::EntryRef::operator= (Int32 val) const
{
	if (propList->entries[this->entryIndex].storage == Numeric)
		SetNum (val);
	else
		SetInt (val);
	return val;
}

template<class UserDataType>
GS_FORCE_INLINE double PropertyList<UserDataType>::EntryRef::operator= (double val) const
{
	SetNum (val);
	return val;
}

template<class UserDataType>
GS_FORCE_INLINE const uchar_t* PropertyList<UserDataType>::EntryRef::operator= (const uchar_t* val) const
{
	SetString (val);
	return val;
}

template<class UserDataType>
GS_FORCE_INLINE const char* PropertyList<UserDataType>::EntryRef::operator= (const char* val) const
{
	SetString (val);
	return val;
}

template<class UserDataType>
typename PropertyList<UserDataType>::EntryRef PropertyList<UserDataType>::EntryRef::operator[] (ULong i) const
{
	EntryRef rf;
	*(ConstEntryRef*) &rf = ConstEntryRef::operator[] (i);
	rf.propList = propList;
	return rf;
}

template<class UserDataType>
inline void PropertyList<UserDataType>::EntryRef::SetFix (bool fix) const
{
	if (this->i1 != MaxUIndex)
		throw GSException ();
	propList->SetEntryFix (this->entryIndex, fix);
}

template<class UserDataType>
inline void PropertyList<UserDataType>::EntryRef::SetName (const char* name) const
{
	if (this->i1 != MaxUIndex)
		throw GSException ();
	propList->SetEntryName (this->entryIndex, name);
}

template<class UserDataType>
GS_FORCE_INLINE UserDataType& PropertyList<UserDataType>::EntryRef::GetUserData () const
{
	return propList->GetUserData (this->entryIndex);
}

template<class UserDataType>
inline void PropertyList<UserDataType>::EntryRef::ModifyType (StorageType st, ArrayType ar, ULong d1, ULong d2) const
{
	if (this->i1 != MaxUIndex)
		throw GSException ();
	propList->ModifyEntryType (this->entryIndex, st, ar, d1, d2);
}

template<class UserDataType>
inline void PropertyList<UserDataType>::EntryRef::ModifyArrayDimensions (ArrayType ar, ULong d1, ULong d2) const
{
	if (this->i1 != MaxUIndex)
		throw GSException ();
	propList->ModifyArrayDimensions (this->entryIndex, ar, d1, d2);
}

template<class UserDataType>
void PropertyList<UserDataType>::EntryRef::SetInt (Int32 val) const
{
	if (this->arrayTp != Scalar)
		throw GSException ();

	if (propList->entries[this->entryIndex].arrayTp == Scalar)
		propList->SetIntEntry (this->entryIndex, val);
	else
		propList->SetIntArrayVal (this->entryIndex, this->i1, this->i2, val);
}

template<class UserDataType>
void PropertyList<UserDataType>::EntryRef::SetNum (double val) const
{
	if (this->arrayTp != Scalar)
		throw GSException ();

	if (propList->entries[this->entryIndex].arrayTp == Scalar)
		propList->SetNumEntry (this->entryIndex, val);
	else
		propList->SetNumArrayVal (this->entryIndex, this->i1, this->i2, val);
}

template<class UserDataType>
void PropertyList<UserDataType>::EntryRef::SetString (const uchar_t* val) const
{
	if (this->arrayTp != Scalar)
		throw GSException ();

	if (propList->entries[this->entryIndex].arrayTp == Scalar)
		propList->SetStringEntry (this->entryIndex, val);
	else
		propList->SetStringArrayVal (this->entryIndex, this->i1, this->i2, val);
}

template<class UserDataType>
inline void PropertyList<UserDataType>::EntryRef::SetString (const char* val) const
{
	SetString (UniString (val).ToUStr ());
}

template<class UserDataType>
GS_FORCE_INLINE ULong PropertyList<UserDataType>::Max (ULong a, ULong b)
{
	return a > b ? a : b;
}

template<class UserDataType>
ULong PropertyList<UserDataType>::CalcStrHashValue (const char* str)
{
	const ULong HashPrime = 65599;

	ULong len = 0;
	while (str[len])
		len++;

	ULong step = len < 16 ? 1 : len / 8;
	ULong hash = 0;
	for (ULong i = 0; i < len; i += step)
		hash = hash * HashPrime + ULong (::tolower (str[i]));
	return hash;
}

template<class UserDataType>
void PropertyList<UserDataType>::CopyUStr (const uchar_t* source, Owner<char[]>* str)
{
	ULong srcLen = ucslen32 (source);
	ULong physicalLength = UniChar::GetANSILength (source, srcLen);

	char* chStr = new char[physicalLength + 1];
	memset (chStr, 0, physicalLength + 1);

	if (!UniChar::UnicodeToANSI (source, srcLen, chStr, physicalLength)) {
		delete [] chStr;
		throw GSException ();
	}

	*str = PassArray (chStr);
}

template<class UserDataType>
void PropertyList<UserDataType>::CopyUStr (const uchar_t* source, uchar_t* dest, ULong maxCh)
{
	if (!maxCh)
		return;

	while (*source && --maxCh)
		*dest++ = *source++;

	*dest = 0;
}

template<class UserDataType>
void PropertyList<UserDataType>::CopyUStr (const uchar_t* source, char* dest, ULong maxCh)
{
	if (!maxCh)
		return;

	memset (dest, 0, maxCh);

	ULong srcLen = ucslen32 (source);
	ULong physicalLength = UniChar::GetANSILength (source, srcLen);
	if (physicalLength >= maxCh)
		physicalLength = maxCh - 1;

	if (!UniChar::UnicodeToANSI (source, srcLen, dest, physicalLength))
		throw GSException ();
}

template<class UserDataType>
void PropertyList<UserDataType>::MoveNamesBlock (ULong index, Int32 moveUCharNum, ULong offset)
{
	if (moveUCharNum == 0)
		return;

	ULong newUsed = namesUsed + moveUCharNum;
	if (newUsed > namesAllocated) {
		ULong newAlloc = Max (minNamesAlloc, Max (newUsed, namesAllocated * 2));
		char* newNames = new char[newAlloc];
		memcpy (newNames, names, offset);
		memcpy (newNames + offset + moveUCharNum, names + offset, namesUsed - offset);
		delete [] names;
		names = newNames;
		namesAllocated = newAlloc;
	} else
		memmove (names + offset + moveUCharNum, names + offset, namesUsed - offset);

	namesUsed = newUsed;

	for (index++; index < entries.GetSize (); index++)
		entries[index].nameOffset += moveUCharNum;
}

template<class UserDataType>
void PropertyList<UserDataType>::MoveDataBlock (ULong index, Int32 moveNum, ULong offset)
{
	if (moveNum == 0)
		return;

	ULong newUsed = dataUsed + moveNum;
	if (newUsed > dataAllocated) {
		ULong newAlloc = Max (minDataAlloc, Max (newUsed, dataAllocated * 2));
		char* newData = new char[newAlloc];
		memcpy (newData, data, offset);
		memcpy (newData + offset + moveNum, data + offset, dataUsed - offset);
		delete [] data;
		data = newData;
		dataAllocated = newAlloc;
	} else
		memmove (data + offset + moveNum, data + offset, dataUsed - offset);

	dataUsed = newUsed;

	entries[index].dataLen += moveNum;
	for (index++; index < entries.GetSize (); index++)
		entries[index].dataOffset += moveNum;
}

template<class UserDataType>
template<typename TChar>
TChar* PropertyList<UserDataType>::GetIthStr (TChar* start, ULong i)
{
	while (i--)
		while (*start++)
			;

	return start;
}

template<class UserDataType>
ULong PropertyList<UserDataType>::GetArrayElementIndex (const Entry& en, ULong i1, ULong i2)
{
	switch (en.arrayTp) {
		default:
		case Scalar:
			return 0;

		case OneDimensional:
			i1--;
			if (i1 >= en.dim1)
				throw GSException ();
			return i1;

		case TwoDimensional:
			i1--;
			i2--;
			if (i1 >= en.dim1 || i2 >= en.dim2)
				throw GSException ();
			return i1 * en.dim2 + i2;
	}
}

template<class UserDataType>
ULong PropertyList<UserDataType>::CalcExtLen (StorageType st, ArrayType at, ULong d1, ULong d2, const uchar_t* s /* = nullptr */)
{
	ULong arrElems;
	switch (at) {
		case Scalar:
			if (st == Integer)
				return 0;
			arrElems = 1;
			break;
		case OneDimensional:
			if (d1 == 0)
				throw GSException ();
			arrElems = d1;
			break;
		case TwoDimensional:
			if (d1 == 0 || d2 == 0)
				throw GSException ();
			arrElems = d1 * d2;
			break;
		default:
			throw GSException ();
	}

	switch (st) {
		case Integer:
			return arrElems * sizeof (Int32);
		case Numeric:
			return arrElems * sizeof (double);
		case String:
			if (s == nullptr)
				return arrElems * sizeof (uchar_t);
			else
				return ULong (GetIthStr (s, arrElems) - s) * sizeof (uchar_t);
		default:
			throw GSException ();
	}
}

template<class UserDataType>
template<typename TChar>
ULong PropertyList<UserDataType>::GetStringArraySizeWithCheck (const TChar* buffer, ULong strNum, const TChar* bufferEnd)
{
	ULong size = 0;

	bufferEnd = (const TChar*) (((const char*) (bufferEnd - 1)) + 1);

	while (strNum--) {
		do {
			if (buffer >= bufferEnd)
				throw GSException ();

			size++;
		} while (*buffer++);
	}

	return size;
}

template<class UserDataType>
Int32 PropertyList<UserDataType>::CalcLongCheckSum (const void* data, ULong len)
{
	Int32 checkSum = 0;
	ULong arrayLen = len / sizeof (Int32);

	const Int32* lp = (const Int32*) data;
	for (ULong i = 0; i < arrayLen; i++, lp++)
		checkSum += *lp;

	const char* cp = (const char*) lp;
	arrayLen = len - arrayLen * sizeof (Int32);
	for (ULong i = 0; i < arrayLen; i++)
		checkSum += cp[i];

	return checkSum;
}

template<class UserDataType>
void PropertyList<UserDataType>::WriteVersion (OChannel& oc, const ClassVersion& /* plVersion */, const ClassVersion& userDataVersion) const
{
	ThrowErr (oc.WriteULong (entries.GetSize ()));
	ThrowErr (oc.Write (namesUsed));
	ThrowErr (oc.Write (dataUsed));

	for (ULong i = 0; i < entries.GetSize (); i++) {
		const Entry& en = entries[i];
		ThrowErr (oc.WriteShort (en.storage));
		ThrowErr (oc.WriteShort (en.arrayTp));
		ThrowErr (oc.Write (en.fix));
		ThrowErr (oc.Write (en.dim1));
		ThrowErr (oc.Write (en.dim2));
		ThrowErr (oc.Write (en.value));
		ThrowErr (oc.Write (en.nameOffset));
		ThrowErr (oc.Write (en.dataOffset));
		ThrowErr (oc.Write (en.dataLen));

		en.userData.Write (oc, userDataVersion);
	}

	for (ULong i = 0; i < namesUsed; i++)
		ThrowErr (oc.Write (names[i]));

	for (ULong i = 0; i < entries.GetSize (); i++) {
		const Entry& en = entries[i];
		if (en.dataLen > 0) {
			switch (en.storage) {
				case Integer:
					{
						ULong n = en.dim1 * en.dim2;
						const Int32* ip = (const Int32*) (data + en.dataOffset);
						for (ULong j = 0; j < n; j++)
							ThrowErr (oc.Write (ip[j]));
					}
					break;
				case Numeric:
					{
						ULong n = en.dim1 * en.dim2;
						const double* dp = (const double*) (data + en.dataOffset);
						for (ULong j = 0; j < n; j++)
							ThrowErr (oc.Write (dp[j]));
					}
					break;
				case String:
					{
						ULong n = en.dataLen / sizeof (uchar_t);
						const uchar_t* cp = (const uchar_t*) (data + en.dataOffset);
						for (ULong j = 0; j < n; j++)
							ThrowErr (oc.Write (cp[j]));
					}
					break;
			}
		}
	}
}

template<class UserDataType>
void PropertyList<UserDataType>::ReadVersion (IChannel& ic, const ClassVersion& plVersion, const ClassVersion& userDataVersion)
{
	if (plVersion.GetMainVersion () != 1)
		throw GSException ();

	ULong entryNum;
	ThrowErr (ic.Read (entryNum));
	ThrowErr (ic.Read (namesUsed));
	ThrowErr (ic.Read (dataUsed));

	namesAllocated = namesUsed > 0 ? Max (minNamesAlloc, namesUsed) : 0;
	names = namesAllocated > 0 ? new char[namesAllocated] : nullptr;

	dataAllocated = dataUsed > 0 ? Max (minDataAlloc, dataUsed) : 0;
	data = dataAllocated > 0 ? new char[dataAllocated] : nullptr;
	memset (data, 0, dataUsed);

	entries.SetSize (entryNum);

	for (ULong i = 0; i < entryNum; i++) {
		short sh;
		bool b;
		Entry& en = entries[i];

		ThrowErr (ic.Read (sh));
		ThrowFalse (sh == Integer || sh == Numeric || sh == String);
		en.storage = StorageType (sh);

		ThrowErr (ic.Read (sh));
		ThrowFalse (sh == Scalar || sh == OneDimensional || sh == TwoDimensional);
		en.arrayTp = ArrayType (sh);

		ThrowErr (ic.Read (b));
		en.fix = b;

		ThrowErr (ic.Read (en.dim1));
		ThrowErr (ic.Read (en.dim2));
		ThrowErr (ic.Read (en.value));
		ThrowErr (ic.Read (en.nameOffset));
		ThrowErr (ic.Read (en.dataOffset));
		ThrowErr (ic.Read (en.dataLen));

		ThrowFalse (en.nameOffset <= namesUsed);
		ThrowFalse (en.dataOffset + en.dataLen <= dataUsed);

		en.userData.Read (ic, userDataVersion);

		switch (en.arrayTp) {
			case Scalar:
				en.dim1 = 1;
				en.dim2 = 1;
				break;
			case OneDimensional:
				en.dim2 = 1;
				break;
			case TwoDimensional:
				// nothing to do
				break;
		}
	}

	for (ULong i = 0; i < namesUsed; i++)
		ThrowErr (ic.Read (names[i]));

	for (ULong i = 0; i < entries.GetSize (); i++) {
		const Entry& en = entries[i];
		if (en.dataLen > 0) {
			switch (en.storage) {
				case Integer:
					{
						ULong n = en.dim1 * en.dim2;
						Int32* ip = (Int32*) (data + en.dataOffset);
						ThrowFalse (ip + n <= (Int32*) (data + en.dataOffset + en.dataLen));
						for (ULong j = 0; j < n; j++)
							ThrowErr (ic.Read (ip[j]));
					}
					break;
				case Numeric:
					{
						ULong n = en.dim1 * en.dim2;
						double* dp = (double*) (data + en.dataOffset);
						ThrowFalse (dp + n <= (double*) (data + en.dataOffset + en.dataLen));
						for (ULong j = 0; j < n; j++)
							ThrowErr (ic.Read (dp[j]));
					}
					break;
				case String:
					{
						ULong n = en.dataLen / sizeof (uchar_t);
						uchar_t* cp = (uchar_t*) (data + en.dataOffset);
						for (ULong j = 0; j < n; j++)
							ThrowErr (ic.Read (cp[j]));
					}
					break;
			}
		}
	}
}

template<class UserDataType>
void PropertyList<UserDataType>::CheckIntegrity () const
{
	ULong nameOffset = 0;
	ULong dataOffset = 0;

	for (ULong i = 0; i < entries.GetSize (); i++) {
		const Entry& en = entries[i];

		ThrowFalse (nameOffset == en.nameOffset);
		ThrowFalse (dataOffset == en.dataOffset);

		nameOffset += GetStringArraySizeWithCheck (names + nameOffset, 1, names + namesUsed);

		ULong extLen = CalcExtLen (en.storage, en.arrayTp, en.dim1, en.dim2);
		if (en.storage == String)
			extLen = sizeof (uchar_t) * GetStringArraySizeWithCheck ((const uchar_t*) (data + dataOffset), extLen / sizeof (uchar_t),
																		(const uchar_t*) (data + dataUsed));
		extLen = RoundUp8 (extLen);

		ThrowFalse (extLen == en.dataLen);
		dataOffset += extLen;

		ThrowFalse (nameOffset <= namesUsed);
		ThrowFalse (dataOffset <= dataUsed);

		en.userData.CheckIntegrity ();
	}

	ThrowFalse (nameOffset == namesUsed);
	ThrowFalse (dataOffset == dataUsed);
}

template<class UserDataType>
GS_FORCE_INLINE void PropertyList<UserDataType>::ThrowErr (GSErrCode err)
{
	if (err != NoError)
		throw GSException ();
}

template<class UserDataType>
GS_FORCE_INLINE void PropertyList<UserDataType>::ThrowFalse (bool b)
{
	if (!b)
		throw GSException ();
}

}

#endif