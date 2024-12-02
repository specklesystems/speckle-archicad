
// *****************************************************************************
//
//                            Class RelativeLocation
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined RELATIVELOCATION_HPP
#define RELATIVELOCATION_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "Address.hpp"
#include "UniString.hpp"

namespace IO { class Location; }
namespace IO { class LocationResolver; }



// ========================== Class RelativeLocation ===========================

namespace IO {

class IO_DLL_EXPORT RelativeLocation: public GS::Object {
	DECLARE_CLASS_INFO

private:

friend class Location;	// only for efficiency: otherwise when a RelativeLocation is appended
						// to a Location its parts should have been queried one by one

	// !!! DON'T PLACE ANY FIELDS BEFORE address, BECAUSE DEBUG ADDON (GSDbgAddIn.dll) WON'T WORK !!!!
	Address		address;	// holds the relative location
	GSErrCode	status;		// object state (error code saved in constructor)

	friend class LocationResolver;	// resolvers are allowed to set content of a RelativeLocation using
									// the corresponding Set method defined in class LocationResolver,
									// which in turn uses the following method:
	void	SetContent (const GS::UniChar::Layout* nameSeq);

	static bool		IsURL      (const GS::UniString& path);
	bool			ResolveURL (const GS::UniString& path);

	inline static GS::UniChar::Layout	GetValue (GS::UniChar::Layout hexaDigit);

public:
		// Error codes

	enum {
		IllegalAddress = RelativeLocationErrors + 0		// relative location has not properly initialized, because illegal address was passed
	};

		// Constructors

	RelativeLocation ();
	RelativeLocation (const RelativeLocation& source);
	RelativeLocation (RelativeLocation&& source);
	explicit RelativeLocation (const Name& name);
	explicit RelativeLocation (const GS::UniString& targetPath);	// Unicode representation of the target
	explicit RelativeLocation (const char* targetPath);				// ASCII representation of the target
	RelativeLocation (const RelativeLocation& parent, const Name& name);
   ~RelativeLocation ();

	RelativeLocation& operator= (const RelativeLocation& source);
	RelativeLocation& operator= (RelativeLocation&& source);

		// State query

	inline GSErrCode	GetStatus (void) const;

		// Setting

	GSErrCode	Set	(const GS::UniString& targetPath);
	GSErrCode	Set	(const char* targetPath);

	void		Clear (void);

	static bool	IsRelative (const GS::UniString& targetPath);

	static bool	IsRelativeURL (const GS::UniString& targetPath);
	static bool	IsRelativeURL (const char* targetPath);

		// Basic address operations

	GSErrCode	GetName		(UIndex idx, Name* result) const;
	GSErrCode	SetName		(UIndex idx, const Name& name);
	GSErrCode	GetLastName	(Name* result) const;
	GSErrCode	SetLastName (const Name& name);

	GSErrCode	Append		(const Name& name);
	GSErrCode	Append		(const RelativeLocation& relLoc);

	GSErrCode	DeleteName	   (UIndex idx);
	GSErrCode	DeleteLastName (void);
	GSErrCode	MoveLastName   (Name* result);

	USize		GetLength	(void) const;
	bool		IsEmpty		(void) const;

		// Comparing

	bool	operator==	 (const RelativeLocation& rightOp) const;
	bool	operator!=	 (const RelativeLocation& rightOp) const;

	bool	IsAncestorOf (const RelativeLocation& rightOp) const;

		// Conversions

	GSErrCode	ToURL (GS::UniString* result) const;

	GS::UniString	ToDisplayText (void) const;

	GS::UniString	ToLogText (void) const;

		// Platform dependency support

	bool	IsLegal			(void) const;
	bool	IsMultiplatform (void) const;

		// I/O

	virtual	GSErrCode	Read  (GS::IChannel& ic) override;
	virtual	GSErrCode	Write (GS::OChannel& oc) const override;

		// Other

	ULong	GenerateHashValue (void) const;

		// Debug

	virtual void	Print (GS::OChannel& oc) const override;
};


IO_DLL_EXPORT void	Append (GS::FastLogger::LogComposer& logComposer, const IO::RelativeLocation& relativeLocation);

}	// namespace IO


inline GSErrCode	IO::RelativeLocation::GetStatus (void) const
{
	return status;
}


#endif
