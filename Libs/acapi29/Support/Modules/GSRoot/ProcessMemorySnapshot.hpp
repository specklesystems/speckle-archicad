
// *****************************************************************************
//
// Declaration of ProcessMemorySnapshot class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESSMEMORYSNAPSHOT_CPP
#define GS_PROCESSMEMORYSNAPSHOT_CPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"



// --- ProcessMemorySnapshot class ---------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ProcessMemorySnapshot {

// Data members:
private:
	UInt64			m_usedPhysicalMemory;
	UInt64			m_usedPrivateMemory;
	UInt64			m_usedVirtualMemory;

// Construction / destruction:
public:
	ProcessMemorySnapshot ();

// Operations:
public:
	UInt64			GetUsedPhysicalMemory () const;
	UInt64			GetUsedPrivateMemory () const;
	UInt64			GetUsedVirtualMemory () const;

// Implementation:
private:
	void			SetUsedPhysicalMemory (UInt64 usedPhysicalMemory);
	void			SetUsedPrivateMemory (UInt64 userPrivateMemory);
	void			SetUsedVirtualMemory (UInt64 usedVirtualMemory);

// Static operations:
public:
	static bool		CreateSnapshot (ProcessMemorySnapshot& processMemorySnapshot);

};

////////////////////////////////////////////////////////////////////////////////
// ProcessMemorySnapshot inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ProcessMemorySnapshot::ProcessMemorySnapshot () :
	m_usedPhysicalMemory (0),
	m_usedPrivateMemory (0),
	m_usedVirtualMemory (0)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetUsedPhysicalMemory
// -----------------------------------------------------------------------------

inline UInt64	ProcessMemorySnapshot::GetUsedPhysicalMemory () const
{
	return m_usedPhysicalMemory;
}

// -----------------------------------------------------------------------------
// GetUsedPrivateMemory
// -----------------------------------------------------------------------------

inline UInt64	ProcessMemorySnapshot::GetUsedPrivateMemory () const
{
	return m_usedPrivateMemory;
}

// -----------------------------------------------------------------------------
// GetUserVirtualMemory
// -----------------------------------------------------------------------------

inline UInt64	ProcessMemorySnapshot::GetUsedVirtualMemory () const
{
	return m_usedVirtualMemory;
}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetUsedPhysicalMemory
// -----------------------------------------------------------------------------

inline void		ProcessMemorySnapshot::SetUsedPhysicalMemory (UInt64 usedPhysicalMemory)
{
	m_usedPhysicalMemory = usedPhysicalMemory;
}

// -----------------------------------------------------------------------------
// SetUsedPrivateMemory
// -----------------------------------------------------------------------------

inline void		ProcessMemorySnapshot::SetUsedPrivateMemory (UInt64 usedPrivateMemory)
{
	m_usedPrivateMemory = usedPrivateMemory;
}

// -----------------------------------------------------------------------------
// SetUserVirtualMemory
// -----------------------------------------------------------------------------

inline void		ProcessMemorySnapshot::SetUsedVirtualMemory (UInt64 usedVirtualMemory)
{
	m_usedVirtualMemory = usedVirtualMemory;
}

}

#endif // GS_PROCESSMEMORYSNAPSHOT_CPP
