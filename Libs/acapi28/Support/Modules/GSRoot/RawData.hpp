// *********************************************************************************************************************
// Description:		GS::RawData stores a piece of raw memory. It can be used to store the serialized state of an object.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef RAWDATA_HPP
#define RAWDATA_HPP

#include "GSDebug.hpp"
#include "Owner.hpp"

// from STL
#include <cstddef>


namespace GS { class IChannel; }
namespace GS { class OChannel; }


namespace GS {


// === class RawData ===================================================================================================

class GSROOT_DLL_EXPORT RawData {
private:
	Owner<std::byte[]>	data;
	USize				size = 0;

public:
	enum GSPtrSelector        { FromGSPtr };
	enum GSHandleSelector     { FromGSHandle };
	enum MemoryInitialization { LeaveUninitialized, FillWithZero };

	RawData () = default;
	explicit RawData (USize size, MemoryInitialization init = LeaveUninitialized);
	RawData (Owner<std::byte[]> byteArray, USize size);
	RawData (const void* startAddress, USize sizeInBytes);
	RawData (GSPtrSelector, GSConstPtr ptr);
	RawData (GSHandleSelector, GSConstHandle handle);
	RawData (const RawData& source);
	RawData (RawData&& source) noexcept;

	bool		operator== (const RawData& other) const;
	bool		operator!= (const RawData& other) const;

	void		Allocate (USize newSize, MemoryInitialization init = LeaveUninitialized);

	void		SetSize (USize newSize, MemoryInitialization initOnIncrement = LeaveUninitialized);

	void		Set (Owner<std::byte[]> byteArray, USize size);
	void		Set (const void* startAddress, USize sizeInBytes);
	void		Set (GSPtrSelector, GSConstPtr ptr);
	void		Set (GSHandleSelector, GSConstHandle handle);

	RawData&	operator= (const RawData& source);
	RawData&	operator= (RawData&& source) noexcept;

	void		Delete ();
	bool		IsEmpty () const;

	std::byte*			GetData () gs_lifebound;
	const std::byte*	GetData () const gs_lifebound;

	std::byte*			GetData (USize offset) gs_lifebound;
	const std::byte*	GetData (USize offset) const gs_lifebound;

	USize				GetSize () const;

	std::byte*	CopyToByteArray () const;		// release the copy with delete [] byteArray;
	GSPtr		CopyToGSPtr () const;			// release the copy with BMpKill (&ptr);
	GSHandle	CopyToGSHandle () const;		// release the copy with BMhKill (&handle);

	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Write (OChannel& oc) const;
};


GSROOT_DLL_EXPORT extern const RawData EmptyRawData;


// === RawData inline methods ==========================================================================================


inline RawData::RawData (RawData&& source) noexcept :
	data (source.data.Pass ()),
	size (source.size)
{
	source.size = 0;
}


inline bool		RawData::operator!= (const RawData& other) const
{
	return !operator == (other);
}


inline RawData&		RawData::operator= (RawData&& source) noexcept
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


inline std::byte*	RawData::GetData ()
{
	return data.Get ();
}


inline const std::byte*		RawData::GetData () const
{
	return data.Get ();
}


inline std::byte*	RawData::GetData (USize offset)
{
	DBASSERT (offset < size);

	return data.Get () + offset;
}


inline const std::byte*		RawData::GetData (USize offset) const
{
	DBASSERT (offset < size);

	return data.Get () + offset;
}


inline USize	RawData::GetSize () const
{
	return size;
}


}	// namespace GS


#endif
