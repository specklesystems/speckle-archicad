
// *****************************************************************************
//
//	                             Class Reflectable
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined REFLECTABLE_HPP
#define REFLECTABLE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "RelativeLocation.hpp"
#include "Name.hpp"

#include "Array.hpp"

// ============================= Class Reflectable =============================

namespace IO {

class IO_DLL_EXPORT Reflectable {
public:
	struct IO_DLL_EXPORT Attribute {
		enum Type { Integer, UnsignedInteger, Real, Boolean, String, Pointer, Null };

		GS::UniString name;		// name of the attribute
		Type		  type;		// type of the attribute

		Attribute (): name (), type (Null) {}
		Attribute (const GS::UniString& name, Type type = String): name (name), type (type) {}
		Attribute (const char* name, Type type = String): name (name), type (type) {}

		bool			Write	 (GS::OChannel& oc) const;
		bool			Read	 (GS::IChannel& ic);
	};

	class IO_DLL_EXPORT AttributeValue {
	public:

		enum Type {
			Integer			=	1,
			UnsignedInteger	=	2,
			Real			=	3,
			Boolean			=	4,
			String			=	5,
			Pointer			=	6,
			Null			=	7
		};

		Type		  type;				// type of the attribute

		union {
			Int64	  integer;			// value of integer attributes
			UInt64	  unsignedInteger;	// value of unsigned integer attributes
			double    real;				// value of real attributes
			bool	  boolean;			// value of boolean attributes
			void*	  pointer;			// value of pointer attributes
		};
		GS::UniString string;			// value of string attributes

		inline AttributeValue (): type (Null) {}
		inline AttributeValue (short integerIn): type (Integer), integer (integerIn) {}
		inline AttributeValue (int integerIn): type (Integer), integer (integerIn) {}
		inline AttributeValue (long integerIn): type (Integer), integer (integerIn) {}
		inline AttributeValue (Int64 integerIn): type (Integer), integer (integerIn) {}
		inline AttributeValue (unsigned short unsignedIntegerIn): type (UnsignedInteger), unsignedInteger (unsignedIntegerIn) {}
		inline AttributeValue (unsigned int unsignedIntegerIn): type (UnsignedInteger), unsignedInteger (unsignedIntegerIn) {}
		inline AttributeValue (unsigned long unsignedIntegerIn): type (UnsignedInteger), unsignedInteger (unsignedIntegerIn) {}
		inline AttributeValue (UInt64 unsignedIntegerIn): type (UnsignedInteger), unsignedInteger (unsignedIntegerIn) {}
		inline AttributeValue (float realIn): type (Real), real (realIn) {}
		inline AttributeValue (double realIn): type (Real), real (realIn) {}
		inline AttributeValue (bool booleanIn): type (Boolean), boolean (booleanIn) {}
		inline AttributeValue (const GS::UniString& stringIn): type (String), string (stringIn) {}
		inline AttributeValue (const char* stringIn): type (String), string (stringIn) {}
		inline AttributeValue (void* pointerIn): type (Pointer), pointer (pointerIn) {}

		virtual ~AttributeValue ();

		GS::UniString	ToString (void) const;

		bool			Write	 (GS::OChannel& oc) const;
		bool			Read	 (GS::IChannel& ic);

	private:
		static bool		Write	(GS::OChannel& oc, const GS::UniString& string);
		static bool		Read	(GS::IChannel& ic, GS::UniString& string);
	};

	class Entry;
	class RootEntry;
	class StaticEntry;
	class CollectorEntry;
	class CustomEntryGroup;

private:
	bool				autoRegistering;	// true if automatic registering is used
	GS::Array<Entry*>	entries;			// stores reflection entries
	RootEntry*			rootEntry;			// root entry of the reflection DAG

	bool	CheckLocation (const RelativeLocation& location) const;

	void	CollectEntries (const Entry* entry, const Entry* target, GS::Array<const Entry*>* path, GS::Array<Name>* context, GS::Array<Name>* nodes, GS::Array<Name>* leaves) const;

protected:
	const Entry*		FindChild (const Entry* entry, const Name& name) const;
	const RootEntry*	GetRootEntry (void) const									{ return rootEntry; }

public:
	Reflectable ();
	Reflectable (const RelativeLocation& rootLocation);
	virtual ~Reflectable ();

		// Location based interface

	virtual bool	GetChildren			(const RelativeLocation& location, GS::Array<Name>* nodes, GS::Array<Name>* leaves) const;

	virtual bool	GetCommonAttributes	(const RelativeLocation& location, GS::Array<Attribute>* attributes) const;
	virtual bool	GetOwnAttributes	(const RelativeLocation& location, GS::Array<Attribute>* attributes) const;

	virtual bool	GetCommonAttributeValues (const RelativeLocation& location, GS::Array<AttributeValue>* attributeValues) const;
	virtual bool	GetOwnAttributeValues (const RelativeLocation& location, GS::Array<AttributeValue>* attributeValues) const;

	virtual bool	GetContent			(const RelativeLocation& location, GS::OChannel& content) const;

		// Tree based interface

	virtual bool	GetEntries						(const CustomEntryGroup* customEntryGroup, const GS::Array<const Entry*>& path, const GS::Array<Name>& context, GS::Array<Name>* nodes, GS::Array<Name>* leaves) const;

	virtual bool	GetEntryOwnAttributes			(const CustomEntryGroup* customEntryGroup, const Name& entryName, const GS::Array<const Entry*>& path, const GS::Array<Name>& context, GS::Array<Attribute>* attributes) const;

	virtual bool	GetEntryCommonAttributeValues	(const CustomEntryGroup* customEntryGroup, const Name& entryName, const GS::Array<const Entry*>& path, const GS::Array<Name>& context, GS::Array<AttributeValue>* attributeValues) const;
	virtual bool	GetEntryOwnAttributeValues		(const CustomEntryGroup* customEntryGroup, const Name& entryName, const GS::Array<const Entry*>& path, const GS::Array<Name>& context, GS::Array<AttributeValue>* attributeValues) const;

	RootEntry*			CreateRootEntry        (void);
	StaticEntry*		CreateStaticEntry      (const Name& name);
	CollectorEntry*		CreateCollectorEntry   (const Name& name, const Entry* root, const Entry* target);
	CustomEntryGroup*	CreateCustomEntryGroup (void);

	static void		Connect					(Entry* parent, Entry* child);

	static void		AddCommonAttribute		(Entry* target, const GS::UniString& name, Attribute::Type type = Attribute::String);
	static void		AddCommonAttribute		(Entry* target, const char* name, Attribute::Type type = Attribute::String);
	static void		AddCommonAttributes		(Entry* target, const GS::Array<Attribute>& attributes);
	static void		CopyCommonAttributes	(Entry* target, const Entry* source);

		// Helper methods

	static Name		GetName     (const RelativeLocation& location, UIndex idx);
	static Name		GetLastName (const RelativeLocation& location);

	static bool		Matches     (const RelativeLocation& location, const RelativeLocation& pattern);
	static bool		Matches     (const RelativeLocation& location, const char* pattern);

	static Name				ToName  (UInt32 l);
	static Name				ToPaddedName (UInt32 l);
	static UInt32			ToULong (const Name& name);

	static Name				ToName  (Int32 l);
	static Int32			ToSLong (const Name& name);

	static Name				ToName   (double d);
	static double			ToDouble (const Name& name);

	static Name				ToName    (const void* p);
	static const void*		ToPointer (const Name& name);

};

}	// namespace IO


class IO_DLL_EXPORT IO::Reflectable::Entry {	// reflectable entry
private:
	GS::Array<const Entry*>	 children;		// stores pointers to connected child entries
	GS::Array<Attribute>     attributes;	// attributes of the entry

public:
	virtual ~Entry () {}

	void			ConnectChild  (const Entry* entry);
	USize			GetChildCount (void) const;
	const Entry*	GetChild      (UIndex i) const;
	const Entry*	FindChild     (const Name& name) const;

	void				AddAttribute      (const Attribute& attribute);
	void				CopyAttributes    (const Entry& source);
	USize				GetAttributeCount (void) const;
	const Attribute&	GetAttribute      (UIndex i) const;

	virtual	bool	HasName (const Name& name) const;
	virtual	Name	GetName (void) const;
};


class IO_DLL_EXPORT IO::Reflectable::RootEntry: public IO::Reflectable::Entry {
public:
	virtual			~RootEntry ();
};

class IO_DLL_EXPORT IO::Reflectable::StaticEntry: public IO::Reflectable::Entry {
private:
	Name name;	// name of the static entry

public:
	StaticEntry ();
	StaticEntry (const Name& name);

	virtual	bool	HasName (const Name& name) const override;
	virtual	Name	GetName (void) const override;
};


class IO_DLL_EXPORT IO::Reflectable::CollectorEntry: public IO::Reflectable::Entry {
private:
	Name         name;		// name of the collector entry
	const Entry* root;		// root of the subtree to be searched in
	const Entry* target;	// entry to be searched for

public:
	CollectorEntry ();
	CollectorEntry (const Name& name, const Entry* root, const Entry* target);

	virtual	bool	HasName (const Name& name) const override;
	virtual	Name	GetName (void) const override;

	const Entry*	GetRoot   (void) const;
	const Entry*	GetTarget (void) const;
};


class IO_DLL_EXPORT IO::Reflectable::CustomEntryGroup: public IO::Reflectable::Entry {
public:
	virtual	bool	HasName (const Name& name) const override;
};
// _____________________________ Class Reflectable _____________________________


#endif
