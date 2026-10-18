
// *****************************************************************************
//
// Declaration of SystemMemorySnapshot class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SYSTEMMEMORYSNAPSHOT_HPP
#define GS_SYSTEMMEMORYSNAPSHOT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"



// --- SystemMemorySnapshot class ----------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT SystemMemorySnapshot {

// Data members:
private:
	UInt64			m_totalPhysicalMemory;
	UInt64			m_usedPhysicalMemory;

	UInt64			m_totalVirtualMemory;
	UInt64			m_usedVirtualMemory;

// Construction / destruction:
public:
	SystemMemorySnapshot ();

// Operations:
public:
	UInt64			GetTotalPhysicalMemory () const;
	UInt64			GetUsedPhysicalMemory () const;
	UInt64			GetFreePhysicalMemory () const;

	UInt64			GetTotalVirtualMemory () const;
	UInt64			GetUsedVirtualMemory () const;
	UInt64			GetFreeVirtualMemory () const;

// Implementation:
private:
	void			SetTotalPhysicalMemory (UInt64 totalPhysicalMemory);
	void			SetUsedPhysicalMemory (UInt64 usedPhysicalMemory);

	void			SetTotalVirtualMemory (UInt64 totalVirtualMemory);
	void			SetUsedVirtualMemory (UInt64 usedVirtualMemory);

// Static operations:
public:
	static bool		CreateSnapshot (SystemMemorySnapshot& systemMemorySnapshot);

};

////////////////////////////////////////////////////////////////////////////////
// SystemMemorySnapshot inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline SystemMemorySnapshot::SystemMemorySnapshot () :
	m_totalPhysicalMemory (0),
	m_usedPhysicalMemory (0),
	m_totalVirtualMemory (0),
	m_usedVirtualMemory (0)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetTotalPhysicalMemory
// -----------------------------------------------------------------------------

inline UInt64	SystemMemorySnapshot::GetTotalPhysicalMemory () const
{
	return m_totalPhysicalMemory;
}

// -----------------------------------------------------------------------------
// GetUsedPhysicalMemory
// -----------------------------------------------------------------------------

inline UInt64	SystemMemorySnapshot::GetUsedPhysicalMemory () const
{
	return m_usedPhysicalMemory;
}

// -----------------------------------------------------------------------------
// GetFreePhysicalMemory
// -----------------------------------------------------------------------------

inline UInt64	SystemMemorySnapshot::GetFreePhysicalMemory () const
{
	return (m_totalPhysicalMemory - m_usedPhysicalMemory);
}

// -----------------------------------------------------------------------------
// GetTotalVirtualMemory
// -----------------------------------------------------------------------------

inline UInt64	SystemMemorySnapshot::GetTotalVirtualMemory () const
{
	return m_totalVirtualMemory;
}

// -----------------------------------------------------------------------------
// GetUsedVirtualMemory
// -----------------------------------------------------------------------------

inline UInt64	SystemMemorySnapshot::GetUsedVirtualMemory () const
{
	return m_usedVirtualMemory;
}

// -----------------------------------------------------------------------------
// GetFreeVirtualMemory
// -----------------------------------------------------------------------------

inline UInt64	SystemMemorySnapshot::GetFreeVirtualMemory () const
{
	return (m_totalVirtualMemory - m_usedVirtualMemory);
}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetTotalPhysicalMemory
// -----------------------------------------------------------------------------

inline void		SystemMemorySnapshot::SetTotalPhysicalMemory (UInt64 totalPhysicalMemory)
{
	m_totalPhysicalMemory = totalPhysicalMemory;
}

// -----------------------------------------------------------------------------
// SetUsedPhysicalMemory
// -----------------------------------------------------------------------------

inline void		SystemMemorySnapshot::SetUsedPhysicalMemory (UInt64 usedPhysicalMemory)
{
	m_usedPhysicalMemory = usedPhysicalMemory;
}

// -----------------------------------------------------------------------------
// SetTotalVirtualMemory
// -----------------------------------------------------------------------------

inline void		SystemMemorySnapshot::SetTotalVirtualMemory (UInt64 totalVirtualMemory)
{
	m_totalVirtualMemory = totalVirtualMemory;
}

// -----------------------------------------------------------------------------
// SetUserVirtualMemory
// -----------------------------------------------------------------------------

inline void		SystemMemorySnapshot::SetUsedVirtualMemory (UInt64 usedVirtualMemory)
{
	m_usedVirtualMemory = usedVirtualMemory;
}

}

#endif // GS_SYSTEMMEMORYSNAPSHOT_HPP
