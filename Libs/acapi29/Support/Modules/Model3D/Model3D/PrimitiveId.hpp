// *********************************************************************************************************************
// Template for IDs of 3D primitives (e.g. VERT, EDGE, PGON).
// *********************************************************************************************************************

#if !defined(MODEL3D_PRIMITIVEID_HPP)
#define MODEL3D_PRIMITIVEID_HPP

#pragma once

namespace Modeler {


template<typename PrimitiveT>
class PrimitiveId {
public:
	typedef Int32		ValueType;
	typedef PrimitiveT	PrimitiveType;

	PrimitiveId () : value ()
	{
		// The structure should have no padding. It is written as binary from body checksum.
		static_assert (sizeof (*this) == sizeof (value), "PrimitiveId binary layout!");
	}
	explicit PrimitiveId (const ValueType& v) : value (v) {}

	bool			operator==	(const PrimitiveId& rhs) const	{ return value == rhs.value;	}
	bool			operator!=	(const PrimitiveId& rhs) const	{ return !operator== (rhs);		}
	bool			IsUndefined (void) const					{ return (*this) == Invalid;	}
	Int32			GetValue	(void) const					{ return value;					}

	ULong			GenerateHashValue (void) const				{ return value;					}
	PrimitiveId&	operator++	(void)							{ ++value; return *this;		}

	void 			Read (GS::IChannel& ic);
	void 			Write (GS::OChannel& oc) const;

	GSErrCode		ReadXML		(GS::XMLIChannel& ic, const char* tagName);
	GSErrCode		WriteXML	(GS::XMLOChannel& oc, const char* tagName) const;

	static const PrimitiveId<PrimitiveT>	Invalid;

protected:
	ValueType	value;
};


template<typename PrimitiveT>
const PrimitiveId<PrimitiveT>	PrimitiveId<PrimitiveT>::Invalid = PrimitiveId<PrimitiveT> ();


template<typename PrimitiveT>
void Modeler::PrimitiveId<PrimitiveT>::Read (GS::IChannel& ic)
{
	ic.Read (value);
}


template<typename PrimitiveT>
void Modeler::PrimitiveId<PrimitiveT>::Write (GS::OChannel& oc) const
{
	oc.Write (value);
}


template<typename PrimitiveT>
GSErrCode Modeler::PrimitiveId<PrimitiveT>::ReadXML (GS::XMLIChannel& ic, const char* tagName)
{
	return ic.ReadXML (tagName, value);
}


template<typename PrimitiveT>
GSErrCode Modeler::PrimitiveId<PrimitiveT>::WriteXML (GS::XMLOChannel& oc, const char* tagName) const
{
	return oc.WriteXML (tagName, value);
}


}		// namespace Modeler

#endif	// MODEL3D_PRIMITIVEID_HPP