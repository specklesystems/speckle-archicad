
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

#include "ProcessException.hpp"
#include "ProcessId.hpp"



// --- ProcessMemorySnapshot class ---------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ProcessMemorySnapshot {

// Nested classes:
public:
	class GSROOT_DLL_EXPORT MemoryUsageDifference {

	// Data members:
	private:
		Int64						m_physicalMemoryDifference;
		Int64						m_privateMemoryDifference;
		Int64						m_virtualMemoryDifference;

	// Construction / destruction:
	public:
		explicit MemoryUsageDifference (Int64 physicalMemoryDifference = 0, Int64 privateMemoryDifference = 0, Int64 virtualMemoryDifference = 0);

	// Operations:
	public:
		Int64						GetPhysicalMemoryDifference () const;
		Int64						GetPrivateMemoryDifference () const;
		Int64						GetVirtualMemoryDifference () const;

		ProcessMemorySnapshot		ToSnapshot () const;

	};

// Data members:
private:
	UInt64							m_usedPhysicalMemory;
	UInt64							m_usedPrivateMemory;
	UInt64							m_usedVirtualMemory;

// Construction / destruction:
public:
	explicit ProcessMemorySnapshot (UInt64 usedPhysicalMemory = 0, UInt64 usedPrivateMemory = 0, UInt64 usedVirtualMemory = 0);

// Operations:
public:
	UInt64							GetUsedPhysicalMemory () const;
	UInt64							GetUsedPrivateMemory () const;
	UInt64							GetUsedVirtualMemory () const;

// Implementation:
private:
	void							SetUsedPhysicalMemory (UInt64 usedPhysicalMemory);
	void							SetUsedPrivateMemory (UInt64 usedPrivateMemory);
	void							SetUsedVirtualMemory (UInt64 usedVirtualMemory);

// Static operations:
public:
	static bool						CreateSnapshot (ProcessId processId, ProcessMemorySnapshot& processMemorySnapshot);
	static bool						CreateSnapshot (ProcessMemorySnapshot& processMemorySnapshot);

	static ProcessMemorySnapshot	CreateSnapshot (ProcessId processId);
	static ProcessMemorySnapshot	CreateSnapshot ();

	
	static MemoryUsageDifference	Difference (const ProcessMemorySnapshot& s1, const ProcessMemorySnapshot& s2);

	static ProcessMemorySnapshot	Min (const ProcessMemorySnapshot& s1, const ProcessMemorySnapshot& s2);
	static ProcessMemorySnapshot	Max (const ProcessMemorySnapshot& s1, const ProcessMemorySnapshot& s2);

	static ProcessMemorySnapshot	Sum (const ProcessMemorySnapshot& s1, const ProcessMemorySnapshot& s2);
};

////////////////////////////////////////////////////////////////////////////////
// ProcessMemorySnapshot::MemoryUsageDifference inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ProcessMemorySnapshot::MemoryUsageDifference::MemoryUsageDifference (Int64 physicalMemoryDifference, Int64 privateMemoryDifference, Int64 virtualMemoryDifference) :
	m_physicalMemoryDifference (physicalMemoryDifference),
	m_privateMemoryDifference (privateMemoryDifference),
	m_virtualMemoryDifference (virtualMemoryDifference)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetPhysicalMemoryDifference
// -----------------------------------------------------------------------------

inline Int64	ProcessMemorySnapshot::MemoryUsageDifference::GetPhysicalMemoryDifference () const
{
	return m_physicalMemoryDifference;
}

// -----------------------------------------------------------------------------
// GetPrivateMemoryDifference
// -----------------------------------------------------------------------------

inline Int64	ProcessMemorySnapshot::MemoryUsageDifference::GetPrivateMemoryDifference () const
{
	return m_privateMemoryDifference;
}

// -----------------------------------------------------------------------------
// GetVirtualMemoryDifference
// -----------------------------------------------------------------------------

inline Int64	ProcessMemorySnapshot::MemoryUsageDifference::GetVirtualMemoryDifference () const
{
	return m_virtualMemoryDifference;
}



////////////////////////////////////////////////////////////////////////////////
// ProcessMemorySnapshot inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ProcessMemorySnapshot::ProcessMemorySnapshot (UInt64 usedPhysicalMemory, UInt64 usedPrivateMemory, UInt64 usedVirtualMemory) :
	m_usedPhysicalMemory (usedPhysicalMemory),
	m_usedPrivateMemory (usedPrivateMemory),
	m_usedVirtualMemory (usedVirtualMemory)
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
// GetUsedVirtualMemory
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
// SetUsedVirtualMemory
// -----------------------------------------------------------------------------

inline void		ProcessMemorySnapshot::SetUsedVirtualMemory (UInt64 usedVirtualMemory)
{
	m_usedVirtualMemory = usedVirtualMemory;
}

}

#endif // GS_PROCESSMEMORYSNAPSHOT_CPP
