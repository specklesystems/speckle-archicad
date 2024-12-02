// *********************************************************************************************************************
// Description:		PropertyList.hpp
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	HK
//
// *********************************************************************************************************************

#ifndef PROPERTYLIST_HPP
#define PROPERTYLIST_HPP

#include "GDLExport.h"

#include "Definitions.hpp"
#include "PagedArray.hpp"
#include "HashTable.hpp"
#include "ClassInfo.hpp"
#include "Owner.hpp"
#include "XMLChannel.hpp"

namespace GS {

template<class UserDataType>
class PropertyList
{
	class ConstEntryRef;
	class EntryRef;

public:
	enum StorageType	{ Integer, Numeric, String };
	enum ArrayType		{ Scalar, OneDimensional, TwoDimensional };

	PropertyList ();
	~PropertyList ();

	PropertyList (const PropertyList& source);
	const PropertyList& operator= (const PropertyList& source);

	ULong GetEntryNum () const;
	ULong GetFixEntryNum () const;

	bool IsEntryFix (ULong index) const;
	void SetEntryFix (ULong index, bool fix);

	void SetEntryName (ULong index, const char* name);

	const char* GetEntryName (ULong index) const;
	void GetEntryName (ULong index, char* str, ULong maxCh) const;

	ULong GetIndexFromName (const char* name) const;

	const UserDataType& GetUserData (ULong index) const;
	UserDataType& GetUserData (ULong index);

	void ModifyEntryType (ULong index, StorageType st, ArrayType ar, ULong d1, ULong d2);
	void ModifyArrayDimensions (ULong index, ArrayType ar, ULong d1, ULong d2);

	StorageType GetEntryType (ULong index, ArrayType* ar = nullptr, ULong* d1 = nullptr, ULong* d2 = nullptr) const;
	bool IsEntryScalar (ULong index) const;

	Int32 GetIntEntry (ULong index) const;
	double GetNumEntry (ULong index) const;
	const uchar_t* GetStringEntry (ULong index) const;
	void GetStringEntry (ULong index, uchar_t* str, ULong maxCh) const;

	void SetIntEntry (ULong index, Int32 val);
	void SetNumEntry (ULong index, double val);
	void SetStringEntry (ULong index, const uchar_t* val);

	const Int32* GetIntArray (ULong index, ULong* len = nullptr, ULong* d1 = nullptr, ULong* d2 = nullptr) const;
	const double* GetNumArray (ULong index, ULong* len = nullptr, ULong* d1 = nullptr, ULong* d2 = nullptr) const;
	const uchar_t* GetStringArray (ULong index, ULong* len = nullptr, ULong* d1 = nullptr, ULong* d2 = nullptr) const;
	const void* GetArray (ULong index, ULong* len = nullptr, StorageType* st = nullptr, ULong* d1 = nullptr, ULong* d2 = nullptr) const;

	void SetIntArray (ULong index, const Int32* vals);
	void SetNumArray (ULong index, const double* vals);
	void SetStringArray (ULong index, const uchar_t* vals);

	Int32 GetIntArrayVal (ULong index, ULong i1, ULong i2) const;
	double GetNumArrayVal (ULong index, ULong i1, ULong i2) const;
	const uchar_t* GetStringArrayVal (ULong index, ULong i1, ULong i2) const;
	void GetStringArrayVal (ULong index, ULong i1, ULong i2, uchar_t* str, ULong maxCh) const;

	void SetIntArrayVal (ULong index, ULong i1, ULong i2, Int32 val);
	void SetNumArrayVal (ULong index, ULong i1, ULong i2, double val);
	void SetStringArrayVal (ULong index, ULong i1, ULong i2, const uchar_t* val);
	void Clear ();
	void DeleteEntries (ULong firstIndex, ULong lastIndex);
	void InsertEntries (const PropertyList& source, ULong firstIndex, ULong lastIndex, ULong destIndex);
	void InsertNewEntry (ULong index, const char* name, StorageType st, ArrayType ar, ULong d1, ULong d2);
	ULong PushEntry (const char* name, StorageType st, ArrayType ar, ULong d1, ULong d2);
	void CopyWithOverwrite (const PropertyList& source, ULong firstIndex, ULong lastIndex, ULong destIndex);
	void ReplaceEntry (ULong oldIndex, ULong newIndex);

	void Write (OChannel& oc) const;
	void Read (IChannel& ic);

	void WriteXML (GS::XMLOChannel& outXML) const;
	void ReadXML  (GS::XMLIChannel& inXML);

	bool Equals (const PropertyList& op) const;
	Int32 CheckSum (double* sumVars) const;

	ULong GetAllocatedBytes () const;

	ConstEntryRef operator[] (ULong index) const;
	ConstEntryRef operator[] (const char* name) const;

	EntryRef operator[] (ULong index);
	EntryRef operator[] (const char* name);

private:
	class ConstEntryRef
	{
		const PropertyList* propList;

	protected:
		ULong entryIndex;
		ULong i1, i2;
		ArrayType arrayTp;

		ConstEntryRef ();

	public:
		ConstEntryRef (const PropertyList* pl, ULong ind);

		operator Int32 () const;
		operator double () const;
		const uchar_t* ToUStr () const;

		ConstEntryRef operator[] (ULong index) const;

		bool IsFix () const;

		const char* GetName () const;
		void GetName (char* str, ULong maxCh) const;

		const UserDataType& GetUserData () const;

		StorageType GetType (ArrayType* ar = nullptr, ULong* d1 = nullptr, ULong* d2 = nullptr) const;

		Int32 GetInt () const;
		double GetNum () const;
		const uchar_t* GetString () const;
		void GetString (Owner<char[]>* str) const;
		void GetString (uchar_t* str, ULong maxCh) const;
		void GetString (char* str, ULong maxCh) const;
	};

	class EntryRef : public ConstEntryRef
	{
		PropertyList* propList;

		EntryRef ();

	public:
		EntryRef (PropertyList* pl, ULong ind);

		Int32 operator= (Int32 val) const;
		double operator= (double val) const;
		const uchar_t* operator= (const uchar_t* val) const;
		const char* operator= (const char* val) const;

		EntryRef operator[] (ULong index) const;

		void SetFix (bool fix) const;

		void SetName (const char* name) const;

		UserDataType& GetUserData () const;

		void ModifyType (StorageType st, ArrayType ar, ULong d1, ULong d2) const;
		void ModifyArrayDimensions (ArrayType ar, ULong d1, ULong d2) const;

		void SetInt (Int32 val) const;
		void SetNum (double val) const;
		void SetString (const uchar_t* val) const;
		void SetString (const char* val) const;
	};

	struct Entry
	{
		StorageType		storage		: 16;
		ArrayType		arrayTp		: 8;
		bool			fix			: 8;
		ULong			dim1, dim2;
		Int32			value;
		ULong			nameOffset;
		ULong			dataOffset;
		ULong			dataLen;
		UserDataType	userData;
	};

	PagedArray<Entry>		entries;

	char*					names; // array of C-strings
	ULong					namesUsed;
	ULong					namesAllocated;

	char*					data;
	ULong					dataUsed;
	ULong					dataAllocated;

	HashTable<ULong,ULong>	nameToIndex;

	static const ULong minNamesAlloc = 256;
	static const ULong minDataAlloc = 512;

	static ULong Max (ULong a, ULong b);

	static ULong CalcStrHashValue (const char* str);

	static void CopyUStr (const uchar_t* source, Owner<char[]>* str);
	static void CopyUStr (const uchar_t* source, uchar_t* dest, ULong maxCh);
	static void CopyUStr (const uchar_t* source, char* dest, ULong maxCh);

	void MoveNamesBlock (ULong index, Int32 moveUCharNum, ULong offset);
	void MoveDataBlock (ULong index, Int32 moveNum, ULong offset);

	template<typename TChar>
	static TChar* GetIthStr (TChar* start, ULong i);

	static ULong GetArrayElementIndex (const Entry& en, ULong i1, ULong i2);
	static ULong CalcExtLen (StorageType st, ArrayType at, ULong d1, ULong d2, const uchar_t* s = nullptr);

	template<typename TChar>
	static ULong GetStringArraySizeWithCheck (const TChar* buffer, ULong strNum, const TChar* bufferEnd);

	static Int32 CalcLongCheckSum (const void* data, ULong len);

	void WriteVersion (OChannel& oc, const ClassVersion& plVersion, const ClassVersion& userDataVersion) const;
	void ReadVersion (IChannel& ic, const ClassVersion& plVersion, const ClassVersion& userDataVersion);

	void CheckIntegrity () const;

protected:
	static void ThrowErr (GSErrCode err);
	static void ThrowFalse (bool b);
};

GDL_DLL_EXPORT const ClassInfo*	GetPropertyListTemplateClassInfo ();

}


#include "PropertyListImp.hpp"

#endif
