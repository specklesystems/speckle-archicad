
// *****************************************************************************
//
// Declaration of EntityTag class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_ENTITYTAG_HPP
#define COMMUNICATION_HTTP_ENTITYTAG_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "UniString.hpp"



// --- EntityTag class ---------------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API EntityTag { // RFC2616, RFC7232

// Nested classes:
public:
	class COMMUNICATIONCOMMON_API Strength {

	// Type definition:
	public:
		enum Type {
			Strong,
			Weak
		};

	// Data members:
	private:
		Type				m_type;

	// Construction / destruction:
	public:
		Strength (Type type = Strong);

	// Operator overloading:
	public:
		bool				operator == (const Strength& rhs) const;
		bool				operator != (const Strength& rhs) const;

		bool				operator == (Type type) const;
		bool				operator != (Type type) const;

							operator int () const;

	// Operations:
	public:
		GS::UniString		ToString () const;

		void				Swap (Strength& rhs);
	
	};

// Friend classes:
friend class EntityTagRange;

// Data members:
private:
	Strength				m_strength;

	GS::UniString			m_tag;

// Construction / destruction:
public:
			 EntityTag ();
	explicit EntityTag (const GS::UniString& tag, const Strength& strength = Strength::Strong);
		
// Operator overloading:
public:
	bool					operator == (const EntityTag& rhs) const;
	bool					operator != (const EntityTag& rhs) const;

// Operations:
public:
	void					SetStrength (const Strength& strength);
	const Strength&			GetStrength () const;

	void					SetTag (const GS::UniString& tag);
	const GS::UniString&	GetTag () const;


	bool					MatchesStrong (const EntityTag& entityTag) const;
	bool					MatchesWeak (const EntityTag& entityTag) const;


	GS::UniString			ToString () const;

	GS::UniString			Format () const;

	void					Swap (EntityTag& rhs);

	bool					IsValid () const;

// Static operations:
public:
	static bool				Parse (const GS::UniString& entityTagString,
								EntityTag& entityTagParsed);

// Static implementation:
private:
	static bool				Parse (const GS::UniString& entityTagString, GS::UIndex offset,
								GS::USize length, EntityTag& entityTagParsed);

};

////////////////////////////////////////////////////////////////////////////////
// EntityTag::Strength inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline EntityTag::Strength::Strength (Type type) :
	m_type (type)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		EntityTag::Strength::operator == (const Strength& rhs) const
{
	return (m_type == rhs.m_type);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		EntityTag::Strength::operator != (const Strength& rhs) const
{
	return (m_type != rhs.m_type);
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		EntityTag::Strength::operator == (Type type) const
{
	return (m_type == type);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		EntityTag::Strength::operator != (Type type) const
{
	return (m_type != type);
}

// -----------------------------------------------------------------------------
// operator int
// -----------------------------------------------------------------------------

inline EntityTag::Strength::operator int () const
{
	return static_cast<int> (m_type);
}



////////////////////////////////////////////////////////////////////////////////
// EntityTag inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline EntityTag::EntityTag () :
	m_strength (),
	m_tag ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline EntityTag::EntityTag (const GS::UniString& tag, const Strength& strength) :
	m_strength (strength),
	m_tag (tag)
{
	// Empty constructor body
}
		
////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		EntityTag::operator == (const EntityTag& rhs) const
{
	if (this != &rhs) {
		return (m_strength == rhs.m_strength &&
				m_tag == rhs.m_tag);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		EntityTag::operator != (const EntityTag& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetStrength
// -----------------------------------------------------------------------------

inline void		EntityTag::SetStrength (const Strength& strength)
{
	m_strength = strength;
}

// -----------------------------------------------------------------------------
// GetStrength
// -----------------------------------------------------------------------------

inline const EntityTag::Strength&	EntityTag::GetStrength () const
{
	return m_strength;
}

// -----------------------------------------------------------------------------
// SetTag
// -----------------------------------------------------------------------------

inline void		EntityTag::SetTag (const GS::UniString& tag)
{
	m_tag = tag;
}

// -----------------------------------------------------------------------------
// GetTag
// -----------------------------------------------------------------------------

inline const GS::UniString&		EntityTag::GetTag () const
{
	return m_tag;
}

}
}

#endif // COMMUNICATION_HTTP_ENTITYTAG_HPP