// *****************************************************************************
//
//                        Classes IChannel, OChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************

#ifndef CHANNEL_HPP
#define CHANNEL_HPP


// --------------------------------- Includes ----------------------------------

#include "Protocol.hpp"
#include "TypeTraits.hpp"
#include "SerializationContext.hpp"

#include <cstddef>

namespace GS { class Object; }
namespace GS { class Guid; }
namespace GS { class IChannel; }
namespace GS { class OChannel; }


namespace GS {

// ============================== Test PersistentTypeOf existing ===============

template <class T>
using	ExternalPersistentType = decltype (PersistentTypeOf (std::declval<T> ()));

template <class T>
constexpr bool	HasExternalPersistentType = IsSubstitutable<ExternalPersistentType, T>;



// ============================== Class IChannel ===============================


template <class Type>
constexpr bool IsObjectType = IsConvertible<Type*, Object*>;

template <class Type>
using HasNoObjectType = EnableIf<!IsObjectType<Type>, bool>;


class GSROOT_DLL_EXPORT IChannel {
private:
	IProtocol*			  iProtocol;		// input protocol for the serialization of built in types
	SerializationContext* context;			// context containing properties and settings for the serialization
	SerializationContext  defaultContext;	// default serialization context

protected:
	IChannel (IProtocol& ip);

public:
		// error codes

	enum {
		EndOfInput = IChannelErrors + 0,	// end of input has been reached, read operation is not completed
		ReadError  = IChannelErrors + 1		// read error on the input device, read operation is not completed
	};

		// destructor

	virtual ~IChannel ();

		// binary input

	virtual GSErrCode	ReadBin	  (char* destination, USize nOfCharToRead, USize* read = nullptr) = 0;
	GSErrCode			ReadBin	  (std::byte* destination, USize byteCount, USize* read = nullptr);
	virtual GSErrCode	CopyBin	  (char* destination, USize nOfCharToCopy, USize* copied = nullptr) = 0;
	virtual GSErrCode	Look	  (UIndex idx, char* c) = 0;
	virtual	GSErrCode	PushBack  (const char* source, USize nOfChar) = 0;
	virtual	GSErrCode	Skip	  (UInt64 nOfCharToSkip, UInt64* skipped = nullptr) = 0;
	virtual	GSErrCode	DirectInputAccess (USize nOfCharToAccess, char** source, USize* accessible = nullptr) = 0;

	virtual GSErrCode	GetInputPosition (UInt64* position) const = 0;
	virtual GSErrCode	GetAvailable     (UInt64* /*available*/) const;
	virtual	GSErrCode	GetAvailable     (USize* available) const;

	virtual bool		IsEOI (void);

	virtual	GSErrCode	PushBack (char c);

		// reading C++ base types and Object

	virtual	void		SetDefaultInputProtocol (void) = 0;
	virtual	void		SetInputProtocol		(IProtocol& ip);
	inline IProtocol&	GetInputProtocol		(void) const;

	GSErrCode	Read (char& c)			 { return iProtocol->Read (*this, c); }
	GSErrCode	Read (unsigned char& c)	 { return iProtocol->Read (*this, c); }
	GSErrCode	Read (bool& b)			 { return iProtocol->Read (*this, b); }
	GSErrCode	Read (short& s)			 { return iProtocol->Read (*this, s); }
	GSErrCode	Read (unsigned short& s) { return iProtocol->Read (*this, s); }
	GSErrCode	Read (int& i)			 { return iProtocol->Read (*this, i); }
	GSErrCode	Read (unsigned int& i)	 { return iProtocol->Read (*this, i); }
	GSErrCode	Read (long& l)			 { return iProtocol->Read (*this, l); }
	GSErrCode	Read (unsigned long& l)	 { return iProtocol->Read (*this, l); }
	GSErrCode	Read (Int64& l)			 { return iProtocol->Read (*this, l); }
	GSErrCode	Read (UInt64& l)		 { return iProtocol->Read (*this, l); }
	GSErrCode	Read (float& f)			 { return iProtocol->Read (*this, f); }
	GSErrCode	Read (double& d)		 { return iProtocol->Read (*this, d); }
	GSErrCode	Read (long double& d)	 { return iProtocol->Read (*this, d); }
	GSErrCode	Read (char* cStr)		 { return iProtocol->Read (*this, cStr); }
	GSErrCode	Read (Object& obj)		 { return iProtocol->Read (*this, obj); }
	GSErrCode	Read (Guid& guid)		 { return iProtocol->Read (*this, guid); }

	template <class Type, EnableIf<!IsObjectType<Type> && !HasExternalPersistentType<Type>, bool> = true>
	GSErrCode	Read (Type& arg);

	template <class Type, EnableIf<!IsObjectType<Type> && HasExternalPersistentType<Type>, bool> = true>
	GSErrCode	Read (Type& arg);

	template <class T1, class T2, class... Ts>
	GSErrCode	Read (T1& t1, T2& t2, Ts&... ts);

	template <class PersistentType, class Enum>
	GSErrCode	ReadEnum (Enum& value);

	static GSErrCode	ConvertObjectReadError (GSErrCode ec);

		// input context

	virtual	void					SetInputContext (SerializationContext& newContext);
	inline SerializationContext&	GetInputContext (void) const;

		// input status

	virtual GSErrCode	GetInputStatus	 (void) const = 0;
	virtual void		ResetInputStatus (void) = 0;
};


inline IProtocol&	IChannel::GetInputProtocol (void) const
{
	return *iProtocol;
}


inline SerializationContext&	IChannel::GetInputContext (void) const
{
	return *context;
}


template <class T1, class T2, class... Ts>
GSErrCode IChannel::Read (T1& t1, T2& t2, Ts&... ts)
{
	GSErrCode errCode = IChannel::Read (t1);
	if (errCode != NoError)
		return errCode;

	return IChannel::Read (t2, ts...);
}


	// HasReadMethod

namespace Imp {

template <class T>
using	HasFullMatchingReadMethodRequirement = decltype (static_cast<GSErrCode (T::*) (IChannel&)> (&T::Read));


template <class T>
constexpr bool HasFullMatchingReadMethod = GS::IsSubstitutable<GS::Imp::HasFullMatchingReadMethodRequirement, T>;


template <class Type>
constexpr bool	HasInternalReadMethod (decltype (std::declval<Type> ().Read (std::declval<IChannel&> ()))*)
{
	static_assert (HasFullMatchingReadMethod<Type>, "Your 'Read' method has incorrect signature! It should be declared as 'GSErrCode Type::Read (IChannel&)'. Note that it should be a non-const method.");

	return true;
}


template <class Type>
constexpr bool	HasInternalReadMethod (...) { return false; }


template <class Type>
constexpr bool	HasInternalRead = HasInternalReadMethod<Type> (nullptr);

} // namespace Imp

template <class Type>
using HasReadMethod = EnableIf<Imp::HasInternalRead<Type>, bool>;

	// external Read functions

inline GSErrCode	Read (IChannel& ic, char& c)			{ return ic.Read (c); }
inline GSErrCode	Read (IChannel& ic, unsigned char& c)	{ return ic.Read (c); }
inline GSErrCode	Read (IChannel& ic, bool& b)			{ return ic.Read (b); }
inline GSErrCode	Read (IChannel& ic, short& s)			{ return ic.Read (s); }
inline GSErrCode	Read (IChannel& ic, unsigned short& s)	{ return ic.Read (s); }
inline GSErrCode	Read (IChannel& ic, int& i)				{ return ic.Read (i); }
inline GSErrCode	Read (IChannel& ic, unsigned int& i)	{ return ic.Read (i); }
inline GSErrCode	Read (IChannel& ic, long& l)			{ return ic.Read (l); }
inline GSErrCode	Read (IChannel& ic, unsigned long& l)	{ return ic.Read (l); }
inline GSErrCode	Read (IChannel& ic, Int64& l)			{ return ic.Read (l); }
inline GSErrCode	Read (IChannel& ic, UInt64& l)			{ return ic.Read (l); }
inline GSErrCode	Read (IChannel& ic, float& f)			{ return ic.Read (f); }
inline GSErrCode	Read (IChannel& ic, double& d)			{ return ic.Read (d); }
inline GSErrCode	Read (IChannel& ic, long double& d)		{ return ic.Read (d); }

template <class Type, HasReadMethod<Type> = true>
inline GSErrCode	Read (IChannel& ic, Type& arg)			{ return arg.Read (ic); }

template <class Type>
GSErrCode	CallRead (IChannel& ic, Type& arg) { return Read (ic, arg); }


template <class Type, EnableIf<!IsObjectType<Type> && !HasExternalPersistentType<Type>, bool>>
GSErrCode	IChannel::Read (Type& arg)
{
	return CallRead (*this, arg);
}


template <class PersistentType, class Enum>
GSErrCode	IChannel::ReadEnum (Enum& value)
{ 
	static_assert (IsIntegral<PersistentType>, "'PersistentType' should be an integral type.");
	static_assert (IsEnum<Enum>, "'Enum' should be an enum type.");

	PersistentType persistentType;
	GSErrCode errCode = IChannel::Read (persistentType);
	value = static_cast<Enum> (persistentType);

	return errCode;
}


template <class Type, EnableIf<!IsObjectType<Type> && HasExternalPersistentType<Type>, bool>>
GSErrCode	IChannel::Read (Type& value)
{
	static_assert (IsEnum<Type>, "Type must be an Enum type!");

	using PersistentType = ExternalPersistentType<Type>;
	static_assert (IsIntegral<PersistentType>, "Enum Persistent type must be integral! Change the return type of your PersistentTypeOf function!");

	return IChannel::ReadEnum<PersistentType, Type> (value);
}


}	// namespace GS


// ============================== Class OChannel ===============================


namespace GS {


class GSROOT_DLL_EXPORT OChannel {
private:
	OProtocol*			  oProtocol;		// output protocol for the serialization of built in types
	SerializationContext* context;			// context containing properties and settings for the serialization
	SerializationContext  defaultContext;	// default serialization context

protected:
	OChannel (OProtocol& op);

public:
		// error codes

	enum {
		OutputIsFull = OChannelErrors + 0,	// output device is full, write operation is not completed
		WriteError	 = OChannelErrors + 1	// write error on the output device, write operation is not completed
	};

		// destructor

	virtual ~OChannel ();

		// binary output

	virtual GSErrCode	WriteBin (const char* source, USize nOfCharToWrite, USize* written = nullptr) = 0;
	GSErrCode			WriteBin (const std::byte* source, USize byteCount, USize* written = nullptr);
	virtual	GSErrCode	DirectOutputAccess (UIndex startPosition, char** output, USize* accessibleDataSize) = 0;

	virtual GSErrCode   GetOutputPosition (UInt64* pos) const = 0;
	virtual GSErrCode	Flush (void);

		// writing C++ base types and Object

	virtual	void		SetDefaultOutputProtocol (void) = 0;
	virtual	void		SetOutputProtocol		 (OProtocol& op);
	inline OProtocol&	GetOutputProtocol		 (void) const;

	GSErrCode	Write (char c)			  { return oProtocol->Write (*this, c); }
	GSErrCode	Write (unsigned char c)	  { return oProtocol->Write (*this, c); }
	GSErrCode	Write (bool b)			  { return oProtocol->Write (*this, b); }
	GSErrCode	Write (short s)			  { return oProtocol->Write (*this, s); }
	GSErrCode	Write (unsigned short s)  { return oProtocol->Write (*this, s); }
	GSErrCode	Write (int i)			  { return oProtocol->Write (*this, i); }
	GSErrCode	Write (unsigned int i)	  { return oProtocol->Write (*this, i); }
	GSErrCode	Write (long l)			  { return oProtocol->Write (*this, l); }
	GSErrCode	Write (unsigned long l)	  { return oProtocol->Write (*this, l); }
	GSErrCode	Write (Int64 l)			  { return oProtocol->Write (*this, l); }
	GSErrCode	Write (UInt64 l)		  { return oProtocol->Write (*this, l); }
	GSErrCode	Write (float f)			  { return oProtocol->Write (*this, f); }
	GSErrCode	Write (double d)		  { return oProtocol->Write (*this, d); }
	GSErrCode	Write (long double d)	  { return oProtocol->Write (*this, d); }
	GSErrCode	Write (const char* cStr)  { return oProtocol->Write (*this, cStr); }
	GSErrCode	Write (const void* p)	  { return oProtocol->Write (*this, p); }
	GSErrCode	Write (const Object& obj) { return oProtocol->Write (*this, obj); }
	GSErrCode	Write (const Guid& guid)  { return oProtocol->Write (*this, guid); }

	template <class Type, EnableIf<!IsObjectType<Type> && !HasExternalPersistentType<Type>, bool> = true>
	GSErrCode	Write (const Type& arg);

	template <class Type, EnableIf<!IsObjectType<Type> && HasExternalPersistentType<Type>, bool> = true>
	GSErrCode	Write (const Type& value);

	template <class T1, class T2, class... Ts>
	GSErrCode	Write (const T1& t1, const T2& t2, Ts&... ts);

	template <class PersistentType, class Enum>
	GSErrCode	WriteEnum (Enum value);

    template <class Type>
    OChannel&	operator<< (const Type& arg)	{ OChannel::Write (arg); return *this; }

	GSErrCode	WriteChar	 (char c)			{ return oProtocol->Write (*this, c); }
	GSErrCode	WriteUChar	 (unsigned char c)	{ return oProtocol->Write (*this, c); }
	GSErrCode	WriteBool	 (bool b)			{ return oProtocol->Write (*this, b); }
	GSErrCode	WriteShort	 (short s)			{ return oProtocol->Write (*this, s); }
	GSErrCode	WriteUShort	 (unsigned short s) { return oProtocol->Write (*this, s); }
	GSErrCode	WriteInt	 (int i)			{ return oProtocol->Write (*this, i); }
	GSErrCode	WriteUInt	 (unsigned int i)	{ return oProtocol->Write (*this, i); }
	GSErrCode	WriteLong	 (Int32 l)			{ return oProtocol->Write (*this, l); }
	GSErrCode	WriteULong	 (UInt32 l)			{ return oProtocol->Write (*this, l); }
	GSErrCode	WriteInt64	 (Int64 l)			{ return oProtocol->Write (*this, l); }
	GSErrCode	WriteUInt64	 (UInt64 l)			{ return oProtocol->Write (*this, l); }
	GSErrCode	WriteFloat	 (float f)			{ return oProtocol->Write (*this, f); }
	GSErrCode	WriteDouble	 (double d)			{ return oProtocol->Write (*this, d); }
	GSErrCode	WriteLDouble (long double d)	{ return oProtocol->Write (*this, d); }

		// block support

	virtual GSErrCode	PushMark	(void) = 0;
	virtual GSErrCode	PopMark		(void) = 0;
	virtual USize		GetOffset	(void) const = 0;
	virtual void		ResetOffset	(void) = 0;

	GSErrCode			OpenBlock   (void);
	GSErrCode			CloseBlock  (void);

		// output context

	virtual	void					SetOutputContext (SerializationContext& newContext);
	inline SerializationContext&	GetOutputContext (void) const;

		// output status

	virtual GSErrCode	GetOutputStatus	  (void) const = 0;
	virtual void		ResetOutputStatus (void) = 0;
};


inline OProtocol&	OChannel::GetOutputProtocol (void) const
{
	return *oProtocol;
}


inline SerializationContext&	OChannel::GetOutputContext (void) const
{
	return *context;
}


	// HasWriteMethod

namespace Imp {

template <class T>
using	HasFullMatchingWriteMethodRequirement = decltype (static_cast<GSErrCode (T::*) (OChannel&) const> (&T::Write));


template <class T>
constexpr bool HasFullMatchingWriteMethod = GS::IsSubstitutable<GS::Imp::HasFullMatchingWriteMethodRequirement, T>;


template <class Type>
constexpr bool	HasInternalWriteMethod (decltype (std::declval<const Type> ().Write (std::declval<GS::OChannel&> ()))*)
{
	static_assert (HasFullMatchingWriteMethod<Type>, "Your 'Write' method has incorrect signature! It should be declared as 'GSErrCode Type::Write (IChannel&) const'.");

	return true;
}


template <class Type>
constexpr bool	HasInternalWriteMethod (...) { return false; }


template <class Type>
constexpr bool	HasInternalWrite = HasInternalWriteMethod<Type> (nullptr);

} // namespace Imp

template <class Type>
using HasWriteMethod = EnableIf<Imp::HasInternalWrite<Type>, bool>;


	// external Write functions

inline GSErrCode	Write (OChannel& oc, char c)			{ return oc.Write (c); }
inline GSErrCode	Write (OChannel& oc, unsigned char c)	{ return oc.Write (c); }
inline GSErrCode	Write (OChannel& oc, bool b)			{ return oc.Write (b); }
inline GSErrCode	Write (OChannel& oc, short s)			{ return oc.Write (s); }
inline GSErrCode	Write (OChannel& oc, unsigned short s)	{ return oc.Write (s); }
inline GSErrCode	Write (OChannel& oc, int i)				{ return oc.Write (i); }
inline GSErrCode	Write (OChannel& oc, unsigned int i)	{ return oc.Write (i); }
inline GSErrCode	Write (OChannel& oc, long l)			{ return oc.Write (l); }
inline GSErrCode	Write (OChannel& oc, unsigned long l)	{ return oc.Write (l); }
inline GSErrCode	Write (OChannel& oc, Int64 l)			{ return oc.Write (l); }
inline GSErrCode	Write (OChannel& oc, UInt64 l)			{ return oc.Write (l); }
inline GSErrCode	Write (OChannel& oc, float f)			{ return oc.Write (f); }
inline GSErrCode	Write (OChannel& oc, double d)			{ return oc.Write (d); }
inline GSErrCode	Write (OChannel& oc, long double d)		{ return oc.Write (d); }
inline GSErrCode	Write (OChannel& oc, const void* p)		{ return oc.Write (p); }
inline GSErrCode	Write (OChannel& oc, const char* cStr)	{ return oc.Write (cStr); }


template <class Type, HasWriteMethod<Type> = true>
inline GSErrCode	Write (OChannel& oc, const Type& arg)	{ return arg.Write (oc); }


template <class Type>
inline GSErrCode	CallWrite (OChannel& oc, const Type& arg) { return Write (oc, arg); }


template <class Type, EnableIf<!IsObjectType<Type> && !HasExternalPersistentType<Type>, bool>>
GSErrCode	OChannel::Write (const Type& arg)
{
	return CallWrite (*this, arg);
}


template <class T1, class T2, class... Ts>
GSErrCode	OChannel::Write (const T1& t1, const T2& t2, Ts&... ts)
{
	GSErrCode errCode = OChannel::Write (t1);
	if (errCode != NoError)
		return errCode;

	return OChannel::Write (t2, ts...);
}


template <class PersistentType, class Enum>
GSErrCode	OChannel::WriteEnum (Enum value)
{
	static_assert (IsIntegral<PersistentType>, "'PersistentType' should be an integral type.");
	static_assert (IsEnum<Enum>, "'Enum' should be an enum type.");

	return OChannel::Write (static_cast<PersistentType> (value));
}


template <class Type, EnableIf<!IsObjectType<Type> && HasExternalPersistentType<Type>, bool>>
GSErrCode	OChannel::Write (const Type& value)
{
	static_assert (IsEnum<Type>, "Type must be an Enum type!");

	using PersistentType = ExternalPersistentType<Type>;
	static_assert (IsIntegral<PersistentType>, "Enum Persistent type must be integral! Change the return type of your PersistentTypeOf function!");

	return OChannel::WriteEnum<PersistentType, Type> (value);
}

}	// namespace GS
// ______________________________ Class OChannel _______________________________



// =============================================================================

namespace GS {

GSROOT_DLL_EXPORT GSErrCode		Copy (IChannel& from, OChannel& to, UInt64 maxLength = MaxUInt64);

}	// namespace GS
// _____________________________________________________________________________


#endif
