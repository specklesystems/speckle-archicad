
// *****************************************************************************
//
// Declaration of ByteRange class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_BYTERANGE_HPP
#define COMMUNICATION_HTTP_BYTERANGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/Range.hpp"

	// from GSRoot
#include "HashSet.hpp"



// --- ByteRange class ---------------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API ByteRange : public Range {

// Nested classes:
public:
	class COMMUNICATIONCOMMON_API RangeSpec {

	// Nested classes:
	private:
		class LowerBoundRangeSelectorClass {};
		class SuffixRangeSelectorClass {};
		class BoundRangeSelectorClass {};

	// Type definitions:
	public:
		using LowerBoundRangeSelector = void (&) (LowerBoundRangeSelectorClass);
		using SuffixRangeSelector = void (&) (SuffixRangeSelectorClass);
		using BoundRangeSelector = void (&) (BoundRangeSelectorClass);

		enum RangeType {
			Unknown,
			LowerBound,
			Suffix,
			Bound,
		};

	// Data members:
	private:
		GS::UInt64			m_firstBytePosition;
		GS::UInt64			m_lastBytePosition;

		RangeType			m_type;

	// Construction / destruction:
	public:
		RangeSpec ();
		RangeSpec (BoundRangeSelector, GS::UInt64 firstBytePosition, GS::UInt64 lastBytePosition);
		RangeSpec (LowerBoundRangeSelector, GS::UInt64 firstBytePosition);
		RangeSpec (SuffixRangeSelector, GS::UInt64 suffixLength);

	// Operator overloading:
	public:
		bool				operator == (const RangeSpec& rhs) const;
		bool				operator != (const RangeSpec& rhs) const;

	// Operations:
	public:
		GS::UInt64			GetFirstBytePosition () const;
		GS::UInt64			GetLastBytePosition () const;

		GS::UInt64			GetLength () const;

		bool				IsLowerBound () const;
		bool				IsSuffix () const;
		bool				IsBound () const;

		RangeType			GetType () const;

		GS::ULong			GenerateHashValue () const;

		GS::UniString		ToString () const;
		GS::UniString		Format () const;

		bool				IsValid () const;

	// Static operations:
	public:
		static bool			Parse (const GS::UniString& rangeSpecString,
								RangeSpec& rangeSpecParsed);

		static void			LowerBoundRange (LowerBoundRangeSelectorClass);
		static void			SuffixRange (SuffixRangeSelectorClass);
		static void			BoundRange (BoundRangeSelectorClass);

	};

// Type definitions:
public:
	typedef GS::HashSet<RangeSpec> RangeSet;

// Data members:
private:
	RangeSet				m_ranges;

// Construction / destruction:
public:
			 ByteRange ();
	explicit ByteRange (const RangeSet& ranges);
	explicit ByteRange (RangeSet&& ranges);

// Operator overloading:
public:
	bool					operator == (const ByteRange& rhs) const;
	bool					operator != (const ByteRange& rhs) const;

// Operations:
public:
	void					SetRanges (const RangeSet& ranges);
	void					SetRanges (RangeSet&& ranges);
	const RangeSet&			GetRanges () const;
	RangeSet&				GetRanges ();

	void					Swap (ByteRange& rhs);

// Range interface implementation:
public:
	virtual RangeUnit		GetUnit () const override;

	virtual bool			Equals (const Range& rhs) const override;

	virtual GS::UniString	ToString () const override;
	virtual GS::UniString	Format () const override;

	virtual bool			IsValid () const override;

// Static operations:
public:
	static bool				Parse (const GS::UniString& byteRangeString,
								ByteRange& byteRangeParsed);

};

////////////////////////////////////////////////////////////////////////////////
// ByteRange::RangeSpec inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ByteRange::RangeSpec::RangeSpec () :
	m_firstBytePosition (0),
	m_lastBytePosition (0),
	m_type (Unknown)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ByteRange::RangeSpec::RangeSpec (BoundRangeSelector, GS::UInt64 firstBytePosition, GS::UInt64 lastBytePosition) :
	m_firstBytePosition (firstBytePosition),
	m_lastBytePosition (lastBytePosition),
	m_type (Bound)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ByteRange::RangeSpec::RangeSpec (LowerBoundRangeSelector, GS::UInt64 firstBytePosition) :
	m_firstBytePosition (firstBytePosition),
	m_lastBytePosition (GS::MaxUInt64),
	m_type (LowerBound)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ByteRange::RangeSpec::RangeSpec (SuffixRangeSelector, GS::UInt64 suffixLength) :
	m_firstBytePosition (GS::MaxUInt64 - suffixLength + 1),
	m_lastBytePosition (GS::MaxUInt64),
	m_type (Suffix)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		 ByteRange::RangeSpec::operator == (const RangeSpec& rhs) const
{
	if (this != &rhs) {
		return (m_firstBytePosition == rhs.m_firstBytePosition &&
				m_lastBytePosition == rhs.m_lastBytePosition &&
				m_type == rhs.m_type);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		 ByteRange::RangeSpec::operator != (const RangeSpec& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetFirstBytePosition
// -----------------------------------------------------------------------------

inline GS::UInt64	ByteRange::RangeSpec::GetFirstBytePosition () const
{
	return m_firstBytePosition;
}

// -----------------------------------------------------------------------------
// GetLastBytePosition
// -----------------------------------------------------------------------------

inline GS::UInt64	ByteRange::RangeSpec::GetLastBytePosition () const
{
	return m_lastBytePosition;
}

// -----------------------------------------------------------------------------
// GetLength
// -----------------------------------------------------------------------------

inline GS::UInt64	ByteRange::RangeSpec::GetLength () const
{
	if (m_firstBytePosition <= m_lastBytePosition) {
		return (m_lastBytePosition - m_firstBytePosition + 1);
	}

	return 0;
}

// -----------------------------------------------------------------------------
// IsLowerBound
// -----------------------------------------------------------------------------

inline bool		ByteRange::RangeSpec::IsLowerBound () const
{
	return (m_type == LowerBound);
}

// -----------------------------------------------------------------------------
// IsSuffix
// -----------------------------------------------------------------------------

inline bool		ByteRange::RangeSpec::IsSuffix () const
{
	return (m_type == Suffix);
}

// -----------------------------------------------------------------------------
// IsBound
// -----------------------------------------------------------------------------

inline bool		ByteRange::RangeSpec::IsBound () const
{
	return (m_type == Bound);
}

// -----------------------------------------------------------------------------
// GetType
// -----------------------------------------------------------------------------

inline ByteRange::RangeSpec::RangeType	ByteRange::RangeSpec::GetType () const
{
	return m_type;
}

////////////////////////////////////////////////////////////////////////////////
// Static operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// LowerBoundRange
// -----------------------------------------------------------------------------

inline void		ByteRange::RangeSpec::LowerBoundRange (LowerBoundRangeSelectorClass)
{
	// Empty method body
}

// -----------------------------------------------------------------------------
// SuffixRange
// -----------------------------------------------------------------------------

inline void		ByteRange::RangeSpec::SuffixRange (SuffixRangeSelectorClass)
{
	// Empty method body
}

// -----------------------------------------------------------------------------
// BoundRange
// -----------------------------------------------------------------------------

inline void		ByteRange::RangeSpec::BoundRange (BoundRangeSelectorClass)
{
	// Empty method body
}



////////////////////////////////////////////////////////////////////////////////
// ByteRange inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ByteRange::ByteRange () :
	m_ranges ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ByteRange::ByteRange (const RangeSet& ranges) :
	m_ranges (ranges)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ByteRange::ByteRange (RangeSet&& ranges) :
	m_ranges (std::move (ranges))
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ByteRange::operator == (const ByteRange& rhs) const
{
	if (this != &rhs) {
		return (m_ranges == rhs.m_ranges);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ByteRange::operator != (const ByteRange& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetRanges
// -----------------------------------------------------------------------------

inline void		ByteRange::SetRanges (const RangeSet& ranges)
{
	m_ranges = ranges;
}

// -----------------------------------------------------------------------------
// SetRanges
// -----------------------------------------------------------------------------

inline void		ByteRange::SetRanges (RangeSet&& ranges)
{
	m_ranges = std::move (ranges);
}

// -----------------------------------------------------------------------------
// GetRanges
// -----------------------------------------------------------------------------

inline const ByteRange::RangeSet&	ByteRange::GetRanges () const
{
	return m_ranges;
}

// -----------------------------------------------------------------------------
// GetRanges
// -----------------------------------------------------------------------------

inline ByteRange::RangeSet&		ByteRange::GetRanges ()
{
	return m_ranges;
}

}
}

#endif // COMMUNICATION_HTTP_BYTERANGE_HPP