#ifndef VECTORIMAGE_TYPEDEFS_HPP
#define VECTORIMAGE_TYPEDEFS_HPP

#pragma once

#include "GSGuid.hpp"
#include "UniString.hpp"
#include "XMLChannel.hpp"

template <int IndexTypeID>
class GUIDType
{
public:
	GUIDType () {}
	explicit GUIDType  (const GS::Guid& init) : myGuid (init) {}

	inline bool		operator== (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator!= (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator<  (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator>  (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator<= (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator>= (const GUIDType<IndexTypeID>& rightOp) const;

	GSErrCode		Generate (void)
	{
		return myGuid.Generate ();
	}

	inline GSErrCode	ReadXML (const char* XMLTag, GS::XMLIChannel& ic)
	{
		return ic.ReadXML (XMLTag, myGuid);
	}

	inline GSErrCode	WriteXML (const char* XMLTag, GS::XMLOChannel& oc) const
	{
		return oc.WriteXML (XMLTag, myGuid);
	}

	inline GS::UniString	ToUniString (void) const
	{ 
		return myGuid.ToUniString ();
	}

	inline GSErrCode	Read (GS::IChannel& ic)			{ return ic.Read (myGuid);  }
	inline GSErrCode	Write (GS::OChannel& oc) const	{ return oc.Write (myGuid); }
	inline ULong		GenerateHashValue () const		{ return GS::CalculateHashValue (myGuid); }

private:
	GS::Guid			myGuid; 

	GS::Guid&			CastToGuid () { return myGuid; }
	const GS::Guid&		CastToGuid () const { return myGuid; }
};



template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator== (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid == rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator!= (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid != rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator< (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid < rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator<= (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid <= rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator> (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid > rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator>= (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid >= rightOp.myGuid;
}



namespace PVI {

	typedef GS::Guid	ProfileParameterId;
	typedef GS::Guid	ProfileBuiltInParameterId;
	typedef GUIDType<1> ProfileParameterSetupId;
	typedef GUIDType<2> ProfileAnchorId;
	typedef GUIDType<3> ProfileDimControlToolId;

}


#endif
