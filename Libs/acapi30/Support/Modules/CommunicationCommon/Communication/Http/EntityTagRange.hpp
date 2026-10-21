
// *****************************************************************************
//
// Declaration of EntityTagRange class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_ENTITYTAGRANGE_HPP
#define COMMUNICATION_HTTP_ENTITYTAGRANGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/EntityTag.hpp"

	// from GSRoot
#include "PagedArray.hpp"



// --- EntityTagRange class ----------------------------------------------------

namespace Communication {
namespace Http {
	
class COMMUNICATIONCOMMON_API EntityTagRange {

// Data members:
private:
	GS::PagedArray<EntityTag>			m_entityTags; // Ordered collection of entity tags...

// Construction / destruction:
public:
			 EntityTagRange ();
	explicit EntityTagRange (const GS::PagedArray<EntityTag>& entityTags);

// Operator overloading:
public:
	bool								operator == (const EntityTagRange& rhs) const;
	bool								operator != (const EntityTagRange& rhs) const;

// Operations:
public:
	bool								IncludesStrong (const EntityTag& entityTag) const;
	bool								IncludesWeak (const EntityTag& entityTag) const;


	bool								IsExplicit () const;
	bool								IsAny () const;


	const GS::PagedArray<EntityTag>&	GetEntityTags () const;

	bool								Remove (const EntityTag& entityTag);
	bool								Add (const EntityTag& entityTag);

	void								Clear ();


	GS::UniString						ToString () const;

	GS::UniString						Format () const;

	void								Swap (EntityTagRange& rhs);

	bool								IsValid () const;

// Static operations:
public:
	static bool							Parse (const GS::UniString& entityTagRangeString,
											EntityTagRange& entityTagRangeParsed);

// Static implementation:
private:
	static bool							Parse (const GS::UniString& entityTagRangeString, GS::UIndex offset,
											GS::USize length, EntityTagRange& entityTagRangeParsed);

};

////////////////////////////////////////////////////////////////////////////////
// EntityTagRange inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline EntityTagRange::EntityTagRange () :
	m_entityTags ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline EntityTagRange::EntityTagRange (const GS::PagedArray<EntityTag>& entityTags) :
	m_entityTags ()
{
	for (const EntityTag& entityTag : entityTags) {
		Add (entityTag);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		EntityTagRange::operator == (const EntityTagRange& rhs) const
{
	if (this != &rhs) {
		return (m_entityTags == rhs.m_entityTags);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		EntityTagRange::operator != (const EntityTagRange& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// IsExplicit
// -----------------------------------------------------------------------------

inline bool		EntityTagRange::IsExplicit () const
{
	return (m_entityTags.GetSize () > 0);
}

// -----------------------------------------------------------------------------
// IsAny
// -----------------------------------------------------------------------------

inline bool		EntityTagRange::IsAny () const
{
	return m_entityTags.IsEmpty ();
}

// -----------------------------------------------------------------------------
// GetEntityTags
// -----------------------------------------------------------------------------

inline const GS::PagedArray<EntityTag>&		EntityTagRange::GetEntityTags () const
{
	return m_entityTags;
}

// -----------------------------------------------------------------------------
// Clear
// -----------------------------------------------------------------------------

inline void		EntityTagRange::Clear ()
{
	m_entityTags.Clear ();
}

}
}

#endif // COMMUNICATION_HTTP_ENTITYTAGRANGE_HPP