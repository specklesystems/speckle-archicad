
// *****************************************************************************
//
// Declaration of ByteContentRange class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_BYTECONTENTRANGE_HPP
#define COMMUNICATION_HTTP_BYTECONTENTRANGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ContentRange.hpp"



// --- ByteContentRange class --------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API ByteContentRange : public ContentRange {

// Nested classes:
public:
	class COMMUNICATIONCOMMON_API RangeSpec {

	// Nested classes:
	private:
		class UnsatisfiedRangeSelectorClass {};
		class BoundRangeSelectorClass {};

	// Type definitions:
	public:
		using UnsatisfiedRangeSelector = void (&) (UnsatisfiedRangeSelectorClass);
		using BoundRangeSelector = void (&) (BoundRangeSelectorClass);

		enum RangeType {
			Unknown,
			Unsatisfied,
			Bound
		};

	// Data members:
	private:
		GS::UInt64			m_firstBytePosition;
		GS::UInt64			m_lastBytePosition;

		RangeType			m_type;

	// Construction / destruction:
	public:
				 RangeSpec ();
		explicit RangeSpec (UnsatisfiedRangeSelector);
		explicit RangeSpec (BoundRangeSelector, GS::UInt64 firstBytePosition, GS::UInt64 lastBytePosition);

	// Operator overloading:
	public:
		bool				operator == (const RangeSpec& rhs) const;
		bool				operator != (const RangeSpec& rhs) const;

	// Operations:
	public:
		GS::UInt64			GetFirstBytePosition () const;
		GS::UInt64			GetLastBytePosition () const;

		bool				IsUnsatisfied () const;
		bool				IsBound () const;

		RangeType			GetType () const;

		GS::UniString		ToString () const;
		GS::UniString		Format () const;

		void				Swap (RangeSpec& rhs);

		bool				IsValid () const;

	// Static operations:
	public:
		static bool			Parse (const GS::UniString& rangeSpecString,
								RangeSpec& rangeSpecParsed);

		static void			UnsatisfiedRange (UnsatisfiedRangeSelectorClass);
		static void			BoundRange (BoundRangeSelectorClass);

	};

// Data members:
private:
	GS::UInt64				m_completeLength;

	RangeSpec				m_range;

// Construction / destruction:
public:
	ByteContentRange ();
	ByteContentRange (GS::UInt64 completeLength, const RangeSpec& range);
	ByteContentRange (const RangeSpec& range);

// Operator overloading:
public:
	bool					operator == (const ByteContentRange& rhs) const;
	bool					operator != (const ByteContentRange& rhs) const;

// Operations:
public:
	void					SetCompleteLength (GS::UInt64 completeLength);
	GS::UInt64				GetCompleteLength () const;
	bool					HasCompleteLength () const;

	void					SetRange (const RangeSpec& range);
	const RangeSpec&		GetRange () const;

	bool					IsUnsatisfied () const;
	bool					IsBound () const;

	void					Swap (ByteContentRange& rhs);

// ContentRange interface implementation:
public:
	virtual RangeUnit		GetUnit () const override;

	virtual bool			Equals (const ContentRange& rhs) const override;

	virtual GS::UniString	ToString () const override;
	virtual GS::UniString	Format () const override;

	virtual bool			IsValid () const override;

// Static operations:
public:
	static bool				Parse (const GS::UniString& byteContentRangeString,
								ByteContentRange& byteContentRangeParsed);

};

////////////////////////////////////////////////////////////////////////////////
// ByteContentRange::RangeSpec inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ByteContentRange::RangeSpec::RangeSpec () :
	m_firstBytePosition (0),
	m_lastBytePosition (0),
	m_type (Unknown)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ByteContentRange::RangeSpec::RangeSpec (UnsatisfiedRangeSelector) :
	m_firstBytePosition (0),
	m_lastBytePosition (GS::MaxUInt64),
	m_type (Unsatisfied)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ByteContentRange::RangeSpec::RangeSpec (BoundRangeSelector, GS::UInt64 firstBytePosition, GS::UInt64 lastBytePosition) :
	m_firstBytePosition (firstBytePosition),
	m_lastBytePosition (lastBytePosition),
	m_type (Bound)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ByteContentRange::RangeSpec::operator == (const RangeSpec& rhs) const
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

inline bool		ByteContentRange::RangeSpec::operator != (const RangeSpec& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetFirstBytePosition
// -----------------------------------------------------------------------------

inline GS::UInt64	ByteContentRange::RangeSpec::GetFirstBytePosition () const
{
	return m_firstBytePosition;
}

// -----------------------------------------------------------------------------
// GetLastBytePosition
// -----------------------------------------------------------------------------

inline GS::UInt64	ByteContentRange::RangeSpec::GetLastBytePosition () const
{
	return m_lastBytePosition;
}

// -----------------------------------------------------------------------------
// IsUnsatisfied
// -----------------------------------------------------------------------------

inline bool		ByteContentRange::RangeSpec::IsUnsatisfied () const
{
	return (m_type == Unsatisfied);
}

// -----------------------------------------------------------------------------
// IsBound
// -----------------------------------------------------------------------------

inline bool		ByteContentRange::RangeSpec::IsBound () const
{
	return (m_type == Bound);
}

// -----------------------------------------------------------------------------
// GetType
// -----------------------------------------------------------------------------

inline ByteContentRange::RangeSpec::RangeType	ByteContentRange::RangeSpec::GetType () const
{
	return m_type;
}

////////////////////////////////////////////////////////////////////////////////
// Static operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// UnsatisfiedRange
// -----------------------------------------------------------------------------

inline void		ByteContentRange::RangeSpec::UnsatisfiedRange (UnsatisfiedRangeSelectorClass)
{
	// Empty method body
}

// -----------------------------------------------------------------------------
// BoundRange
// -----------------------------------------------------------------------------

inline void		ByteContentRange::RangeSpec::BoundRange (BoundRangeSelectorClass)
{
	// Empty method body
}



////////////////////////////////////////////////////////////////////////////////
// ByteContentRange inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ByteContentRange::ByteContentRange () :
	m_completeLength (0),
	m_range ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ByteContentRange::ByteContentRange (GS::UInt64 completeLength, const RangeSpec& range) :
	m_completeLength (completeLength),
	m_range (range)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ByteContentRange::ByteContentRange (const RangeSpec& range) :
	m_completeLength (GS::MaxUInt64),
	m_range (range)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ByteContentRange::operator == (const ByteContentRange& rhs) const
{
	if (this != &rhs) {
		return (m_completeLength == rhs.m_completeLength && m_range == rhs.m_range);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ByteContentRange::operator != (const ByteContentRange& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetCompleteLength
// -----------------------------------------------------------------------------

inline void		ByteContentRange::SetCompleteLength (GS::UInt64 completeLength)
{
	m_completeLength = completeLength;
}

// -----------------------------------------------------------------------------
// GetCompleteLength
// -----------------------------------------------------------------------------

inline GS::UInt64	ByteContentRange::GetCompleteLength () const
{
	return m_completeLength;
}

// -----------------------------------------------------------------------------
// HasCompleteLength
// -----------------------------------------------------------------------------

inline bool		ByteContentRange::HasCompleteLength () const
{
	return (m_completeLength < GS::MaxUInt64);
}

// -----------------------------------------------------------------------------
// SetRange
// -----------------------------------------------------------------------------

inline void		ByteContentRange::SetRange (const RangeSpec& range)
{
	m_range = range;
}

// -----------------------------------------------------------------------------
// GetRange
// -----------------------------------------------------------------------------

inline  const ByteContentRange::RangeSpec&	ByteContentRange::GetRange () const
{
	return m_range;
}

}
}

#endif // COMMUNICATION_HTTP_BYTECONTENTRANGE_HPP