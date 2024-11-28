// *********************************************************************************************************************
// Description:		GS::RawData stores a piece of raw memory. It can be used to store the serialized state of an object.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	BIM
//
// *********************************************************************************************************************


#ifndef RAWDATA_HPP
#define RAWDATA_HPP

#pragma once


#include "Owner.hpp"
namespace GS { class IChannel; }
namespace GS { class OChannel; }


namespace GS {


// === class RawData ===================================================================================================

class GSROOT_DLL_EXPORT RawData {
private:
	Owner<char[]>	data;
	USize			size = 0;

public:
	enum GSPtrSelector        { FromGSPtr };
	enum GSHandleSelector     { FromGSHandle };
	enum MemoryInitialization { LeaveUninitialized, FillWithZero };

	RawData ();
	explicit RawData (USize size, MemoryInitialization init = LeaveUninitialized);
	RawData (Owner<char[]> charArray, USize sizeInBytes);
	RawData (const void* startAddress, USize sizeInBytes);
	RawData (GSPtrSelector, GSConstPtr ptr);
	RawData (GSHandleSelector, GSConstHandle handle);
	RawData (const RawData& source);
	RawData (RawData&& source);

	void		Allocate (USize newSize, MemoryInitialization init = LeaveUninitialized);

	void		Set (Owner<char[]> charArray, USize sizeInBytes);
	void		Set (const void* startAddress, USize sizeInBytes);
	void		Set (GSPtrSelector, GSConstPtr ptr);
	void		Set (GSHandleSelector, GSConstHandle handle);

	RawData&	operator= (const RawData& source);
	RawData&	operator= (RawData&& source);

	void		Delete ();
	bool		IsEmpty () const;

	char*		GetData ();
	const char*	GetData () const;
	USize		GetSize () const;

	char*		CopyToCharArray () const;		// release the copy with delete [] charArray;
	GSPtr		CopyToGSPtr () const;			// release the copy with BMpKill (&ptr);
	GSHandle	CopyToGSHandle () const;		// release the copy with BMhKill (&handle);

	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Write (OChannel& oc) const;
};


// === RawData inline methods ==========================================================================================

inline RawData::RawData ()
{
}


inline RawData::RawData (RawData&& source) :
	data (source.data.Pass ()),
	size (source.size)
{
	source.size = 0;
}


inline RawData&		RawData::operator= (RawData&& source)
{
	data = source.data.Pass ();
	size = source.size;

	source.size = 0;

	return *this;
}


inline void		RawData::Delete ()
{
	data.Delete ();
	size = 0;
}


inline bool		RawData::IsEmpty () const
{
	return size == 0;
}


inline char*	RawData::GetData ()
{
	return data.Get ();
}


inline const char*		RawData::GetData () const
{
	return data.Get ();
}


inline USize	RawData::GetSize () const
{
	return size;
}


}	// namespace GS


#endif
