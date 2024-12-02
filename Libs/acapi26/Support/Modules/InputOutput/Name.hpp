
// *****************************************************************************
//
//                                  Class Name
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined NAME_HPP
#define NAME_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "UniString.hpp"



// ================================ Class Name =================================

namespace IO {

class IO_DLL_EXPORT Name: public GS::Object {
	DECLARE_CLASS_INFO

private:
	GS::UniString	name;	// holds a name

public:
		// Constructors

	inline Name ();
	inline Name (const Name& source);
	inline Name (Name&& source);
	explicit inline Name (const GS::UniString& string);
	explicit inline	Name (GS::UniString&& string);
	explicit inline Name (const char* cStr);

	inline Name&	operator= (const Name& source);
	inline Name&	operator= (Name&& source);
	inline Name&	operator= (const GS::UniString& source);
	inline Name&	operator= (GS::UniString&& source);
	inline Name&	operator= (const char* cStr);

		// Content manipulation

	inline void		Append (const GS::UniString& string);
	inline void		Append (const GS::UniChar::Layout* uStr);
	inline void		Append (const char* cStr);

	inline void		Clear  (void);
	inline void		ClearContent (void);

		// Content query

	inline GS::UniChar	operator[] (UIndex idx) const;

	inline USize	GetLength (void) const;
	inline bool		IsEmpty (void) const;

	inline	const GS::UniString&	ToString (void) const;
	inline	operator const GS::UniString& () const;

		// Capacity management

	inline void		SetCapacity	(USize newCapacity);
	inline USize	GetCapacity	(void) const;

		// Extension management

	GS::UniString	GetBase		    (void) const;
	GS::UniString	GetExtension    (void) const;
	bool			HasExtension    (void) const;
	void			AppendExtension (const GS::UniString& extension);
	void			AppendExtension (const char* extension);
	void			DeleteExtension (void);

		// Comparing

	bool	operator== (const Name& rightOp) const;
	bool	operator== (const GS::UniString& rightOp) const;
	bool	operator== (const char* rightOp) const;

	bool	operator!= (const Name& rightOp) const;
	bool	operator!= (const GS::UniString& rightOp) const;
	bool	operator!= (const char* rightOp) const;
	bool    operator<  (const Name& rightOp) const;

		// Platform dependency support

	bool	IsLegal				(void) const;
	bool	IsMultiplatform		(void) const;
	void	MakeLegal			(void);
	void	MakeMultiplatform	(void);

		// I/O

	virtual	GSErrCode	Read  (GS::IChannel& ic) override;
	virtual	GSErrCode	Write (GS::OChannel& oc) const override;

		// Other

	ULong	GenerateHashValue (void) const;

		// Debug

	virtual void	Print (GS::OChannel& oc) const override;
};

}	// namespace IO



inline IO::Name::Name ()
{
}


inline IO::Name::Name (const Name& source):
	name (source.name)
{
}


inline IO::Name::Name (Name&& source):
	name (std::move (source.name))
{
}


inline IO::Name::Name (const GS::UniString& string):
	name (string)
{
}


inline IO::Name::Name (GS::UniString&& string):
	name (std::move (string))
{
}


inline IO::Name::Name (const char* cStr):
	name (cStr)
{
}


inline IO::Name&	IO::Name::operator= (const Name& source)
{
	name = source.name;

	return *this;
}


inline IO::Name&	IO::Name::operator= (Name&& source)
{
	name = std::move (source.name);

	return *this;
}


inline IO::Name&	IO::Name::operator= (const GS::UniString& string)
{
	name = string;

	return *this;
}


inline IO::Name&	IO::Name::operator= (GS::UniString&& string)
{
	name = std::move (string);

	return *this;
}


inline IO::Name&	IO::Name::operator= (const char* cStr)
{
	name = cStr;

	return *this;
}


inline void		IO::Name::Append (const GS::UniString& string)
{
	name.Append (string);
}


inline void		IO::Name::Append (const GS::UniChar::Layout* uStr)
{
	name.Append (uStr);
}


inline void		IO::Name::Append (const char* cStr)
{
	name.Append (cStr);
}


inline void		IO::Name::Clear (void)
{
	name.Clear ();
}


inline void		IO::Name::ClearContent (void)
{
	name.ClearContent ();
}


inline GS::UniChar	IO::Name::operator[] (UIndex idx) const
{
	return name[idx];
}


inline USize	IO::Name::GetLength (void) const
{
	return name.GetLength ();
}


inline bool		IO::Name::IsEmpty (void) const
{
	return name.IsEmpty ();
}


inline const GS::UniString&		IO::Name::ToString (void) const
{
	return name;
}


inline	IO::Name::operator const GS::UniString& () const
{
	return name;
}


inline void		IO::Name::SetCapacity (USize newCapacity)
{
	name.SetCapacity (newCapacity);
}


inline USize	IO::Name::GetCapacity (void) const
{
	return name.GetCapacity ();
}


#endif
