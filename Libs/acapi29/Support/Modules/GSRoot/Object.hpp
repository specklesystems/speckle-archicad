
// *****************************************************************************
//
//                                 Class Object
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#ifndef OBJECT_HPP
#define OBJECT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "ClassInfo.hpp"
#include "ErrorStatus.hpp"
#include "GSDebug.hpp"
#include "IOFrame.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace GS { class IChannel; }
namespace GS { class OChannel; }
namespace GS { class MethodResult; }
namespace GS { class ObjectState; }


// =============================== Class Object ================================

namespace GS {

class GSROOT_DLL_EXPORT Object {
protected:
	Object () = default;

	virtual ErrorStatus	Validate (const ObjectState& os, bool* isSchemaEmpty);
	virtual ErrorStatus	RestoreValidated (const ObjectState& os);

public:
	using CurrentClass = Object;

		// Constructors, virtual destructor

	virtual	Object*		Clone (void) const;

	virtual ~Object ();

		// Class information

	virtual const ClassInfo*	GetClassInfo (void) const;

	inline const Guid&	GetClassId (void) const;

	inline const char*	GetClassName (void) const;
	inline ClassType	GetClassType (void) const;

	inline ClassVersion	GetClassVersion (void) const;
	inline ClassVersion	GetClassOldVersion (void) const;

		// I/O

	virtual	GSErrCode	Read  (IChannel& ic);
	virtual	GSErrCode	Write (OChannel& oc) const;

	virtual ErrorStatus	Store	(ObjectState& os) const;
	virtual ErrorStatus	Restore	(const ObjectState& os);

		// Debug & test

	virtual void		Print	   (OChannel& oc) const;
	virtual bool		CheckState (void) const;
};

	// external Print functions

inline GSErrCode	Print (OChannel& oc, char c)			{ return oc.Write (c); }
inline GSErrCode	Print (OChannel& oc, unsigned char c)	{ return oc.Write (c); }
inline GSErrCode	Print (OChannel& oc, bool b)			{ return oc.Write (b); }
inline GSErrCode	Print (OChannel& oc, short s)			{ return oc.Write (s); }
inline GSErrCode	Print (OChannel& oc, unsigned short s)	{ return oc.Write (s); }
inline GSErrCode	Print (OChannel& oc, int i)				{ return oc.Write (i); }
inline GSErrCode	Print (OChannel& oc, unsigned int i)	{ return oc.Write (i); }
inline GSErrCode	Print (OChannel& oc, long l)			{ return oc.Write (l); }
inline GSErrCode	Print (OChannel& oc, unsigned long l)	{ return oc.Write (l); }
inline GSErrCode	Print (OChannel& oc, Int64 l)			{ return oc.Write (l); }
inline GSErrCode	Print (OChannel& oc, UInt64 l)			{ return oc.Write (l); }
inline GSErrCode	Print (OChannel& oc, float f)			{ return oc.Write (f); }
inline GSErrCode	Print (OChannel& oc, double d)			{ return oc.Write (d); }
inline GSErrCode	Print (OChannel& oc, long double d)		{ return oc.Write (d); }
inline GSErrCode	Print (OChannel& oc, const char* cStr)	{ return oc.Write (cStr); }
inline GSErrCode	Print (OChannel& oc, const void* p)		{ return oc.Write (p); }
inline GSErrCode	Print (OChannel& oc, const Object& obj)	{ obj.Print (oc); return GS::NoError; }

template <class Type>
inline GSErrCode	PrintType (OChannel& oc, const Type& arg) { return Print (oc, arg); }


GSROOT_DLL_EXPORT GSErrCode	Store	(GS::ObjectState& os, const GS::Object& object);
GSROOT_DLL_EXPORT GSErrCode	Restore	(const GS::ObjectState& os, GS::Object& object);


}	// namespace GS


inline const GS::Guid&	GS::Object::GetClassId (void) const
{
	return GetClassInfo ()->GetId ();
}


inline const char*		GS::Object::GetClassName (void) const
{
	return GetClassInfo ()->GetName ();
}


inline GS::ClassType	GS::Object::GetClassType (void) const
{
	return GetClassInfo ()->GetType ();
}


inline GS::ClassVersion		GS::Object::GetClassVersion (void) const
{
	return GetClassInfo ()->GetVersion ();
}


inline GS::ClassVersion		GS::Object::GetClassOldVersion (void) const
{
	return GetClassInfo ()->GetOldVersion ();
}
// _______________________________ Class Object ________________________________


#endif
