
// *****************************************************************************
//
// Declaration of ProcessInfo class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESSINFO_HPP
#define GS_PROCESSINFO_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "HashTable.hpp"
#include "Process.hpp"
#include "ProcInfoFetchOptions.hpp"



// --- ProcessInfo class -------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ProcessInfo {

// Data members:
private:
	ProcessId					m_id;
	ProcessId					m_parentId;
    
    bool						m_accessAllowed;

	UInt64						m_startTime;

	Array<UniString>			m_commandLineArgs;

	UniString					m_fileName;
	UniString					m_name;

// Construction / destruction:
public:
	ProcessInfo ();
	ProcessInfo (ProcessId id, ProcessId parentId, bool accessAllowed, UInt64 startTime, const Array<UniString>& commandLineArgs, const UniString& fileName, const UniString& name);
	ProcessInfo (const ProcessInfo& rhs);
	ProcessInfo (ProcessInfo&& rhs);

// Operator overloading:
public:
	bool						operator == (const ProcessInfo& rhs) const;
	bool						operator != (const ProcessInfo& rhs) const;

	ProcessInfo&				operator = (const ProcessInfo& rhs);
	ProcessInfo&				operator = (ProcessInfo&& rhs);

// Operations:
public:
	ProcessId					GetId () const;
	ProcessId					GetParentId () const;
    
    bool						IsAccessAllowed () const;

	UInt64						GetStartTime () const;
	
	const Array<UniString>&		GetCommandLineArgs () const;

	const UniString&			GetFileName () const;
	const UniString&			GetName () const;

	Process						GetProcess () const;

	UniString					ToString () const;

	void						Swap (ProcessInfo& rhs);

	bool						IsValid () const;

// Implementation:
private:
	void						CheckValid (const char* sourceFile, UInt32 sourceLine) const;

// Static operations:
public:
	static USize				CreateSnapshotAsMap (const ProcessInfoFetchOptions& fetchOptions, HashTable<ProcessId, ProcessInfo>& processMap);
	static USize				CreateSnapshotAsMap (HashTable<ProcessId, ProcessInfo>& processMap);
	
	static USize				CreateSnapshot (const ProcessInfoFetchOptions& fetchOptions, PagedArray<ProcessInfo>& processes);
	static USize				CreateSnapshot (PagedArray<ProcessInfo>& processes);

	static ProcessInfo			Get (ProcessId processId, const ProcessInfoFetchOptions& fetchOptions = ProcessInfoFetchOptions::GetDefault ());

};

////////////////////////////////////////////////////////////////////////////////
// ProcessInfo inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ProcessInfo::ProcessInfo () :
	m_id (0),
	m_parentId (0),
    m_accessAllowed (false),
	m_startTime (0),
	m_commandLineArgs (),
	m_fileName (),
	m_name ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ProcessInfo::ProcessInfo (ProcessId id, ProcessId parentId, bool accessAllowed, UInt64 startTime,
	const Array<UniString>& arguments, const UniString& fileName, const UniString& name) :
	m_id (id),
	m_parentId (parentId),
    m_accessAllowed (accessAllowed),
	m_startTime (startTime),
	m_commandLineArgs (arguments),
	m_fileName (fileName),
	m_name (name)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ProcessInfo::ProcessInfo (const ProcessInfo& rhs) :
	m_id (rhs.m_id),
	m_parentId (rhs.m_parentId),
    m_accessAllowed (rhs.m_accessAllowed),
	m_startTime (rhs.m_startTime),
	m_commandLineArgs (rhs.m_commandLineArgs),
	m_fileName (rhs.m_fileName),
	m_name (rhs.m_name)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Move constructor
// -----------------------------------------------------------------------------

inline ProcessInfo::ProcessInfo (ProcessInfo&& rhs) :
	m_id (std::move (rhs.m_id)),
	m_parentId (std::move (rhs.m_parentId)),
    m_accessAllowed (std::move (rhs.m_accessAllowed)),
	m_startTime (std::move (rhs.m_startTime)),
	m_commandLineArgs (std::move (rhs.m_commandLineArgs)),
	m_fileName (std::move (rhs.m_fileName)),
	m_name (std::move (rhs.m_name))
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ProcessInfo::operator == (const ProcessInfo& rhs) const
{
	if (this != &rhs) {
		return (m_id == rhs.m_id &&
				m_parentId == rhs.m_parentId &&
                m_accessAllowed == rhs.m_accessAllowed &&
				m_startTime == rhs.m_startTime &&
				m_commandLineArgs == rhs.m_commandLineArgs &&
				m_fileName == rhs.m_fileName &&
				m_name == rhs.m_name);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ProcessInfo::operator != (const ProcessInfo& rhs) const
{
	return !operator == (rhs);
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline ProcessInfo&		ProcessInfo::operator = (const ProcessInfo& rhs)
{
	if (this != &rhs) {
		ProcessInfo (rhs).Swap (*this);
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline ProcessInfo&		ProcessInfo::operator = (ProcessInfo&& rhs)
{
	ProcessInfo (std::move (rhs)).Swap (*this);

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetId
// -----------------------------------------------------------------------------

inline ProcessId	ProcessInfo::GetId () const
{
	return m_id;
}

// -----------------------------------------------------------------------------
// GetParentId
// -----------------------------------------------------------------------------

inline ProcessId	ProcessInfo::GetParentId () const
{
	return m_parentId;
}

// -----------------------------------------------------------------------------
// IsAccessAllowed
// -----------------------------------------------------------------------------

inline bool     ProcessInfo::IsAccessAllowed () const
{
    return m_accessAllowed;
}

// -----------------------------------------------------------------------------
// GetStartTime
// -----------------------------------------------------------------------------

inline UInt64	ProcessInfo::GetStartTime () const
{
	return m_startTime;
}

// -----------------------------------------------------------------------------
// GetCommandLineArgs
// -----------------------------------------------------------------------------

inline const Array<UniString>&	ProcessInfo::GetCommandLineArgs () const
{
	return m_commandLineArgs;
}

// -----------------------------------------------------------------------------
// GetFileName
// -----------------------------------------------------------------------------

inline const UniString&		ProcessInfo::GetFileName () const
{
	return m_fileName;
}

// -----------------------------------------------------------------------------
// GetName
// -----------------------------------------------------------------------------

inline const UniString&		ProcessInfo::GetName () const
{
	return m_name;
}

// -----------------------------------------------------------------------------
// IsValid
// -----------------------------------------------------------------------------

inline bool		ProcessInfo::IsValid () const
{
	return (m_id > 0);
}

}

#endif // GS_PROCESSINFO_HPP