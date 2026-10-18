
// *****************************************************************************
//
// Declaration of Process class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESS_HPP
#define GS_PROCESS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Array.hpp"
#include "IBinaryChannel.hpp"
#include "OBinaryChannel.hpp"
#include "ProcessAccessDeniedException.hpp"
#include "ProcessId.hpp"
#include "ProcessNotFoundException.hpp"
#include "Timeout.hpp"
#include "UniString.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class ProcessImpl;

}



// --- Process class -----------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Process {

// Type definitions:
public:
	enum CreateFlags {
		CreateNoWindow	= 0x01
	};

// Data members:
private:
	ProcessImpl*		m_impl;

// Construction / destruction:
public:
			 Process ();
private:
	explicit Process (ProcessImpl* impl);
public:
			 Process (const Process& rhs);
			~Process ();

// Operator overloading:
public:
	const Process&		operator =  (const Process& rhs);

	bool				operator == (const Process& rhs) const;
	bool				operator != (const Process& rhs) const;

	bool				operator == (std::nullptr_t) const;
	bool				operator != (std::nullptr_t) const;

// Operations:
public:
	ProcessId			GetId () const;

	UniString			GetFileName () const;
	UniString			GetName () const;

	bool				IsTerminated ();
	int					GetExitCode ();

	bool				IsStandardOutputRedirected () const;
	bool				IsStandardInputRedirected () const;
	bool				IsStandardErrorRedirected () const;

	IBinaryChannel&		GetStandardOutputChannel () const;
	OBinaryChannel&		GetStandardInputChannel	() const;
	IBinaryChannel&		GetStandardErrorChannel	() const;

	bool				WaitFor (const Timeout& timeout);
	bool				WaitFor (UInt32 timeout);
	void				WaitFor ();

	void				Kill ();

	bool				IsValid () const;

// Implementation:
private:
	void				CheckState (const char* sourceFile = __FILE__, UInt32 sourceLine = __LINE__) const;

// Static operations:
public:
	static ProcessId	GetCurrentProcessId ();
	static Process		GetCurrent ();

	static Process		Create (const GS::UniString& command, const GS::Array<GS::UniString>& argv, GSFlags createFlags, 
								bool redirectStandardOutput = false, 
								bool redirectStandardInput = false,
								bool redirectStandardError = false);
	static Process		Create (const GS::UniString& command, const GS::Array<GS::UniString>& argv = GS::Array<GS::UniString> ());
	static Process		Create (ProcessId processId);

};

////////////////////////////////////////////////////////////////////////////////
// Process inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Process::Process () :
	m_impl (nullptr)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		Process::operator == (std::nullptr_t) const
{
	return (m_impl == nullptr);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		Process::operator != (std::nullptr_t) const
{
	return (m_impl != nullptr);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// IsValid
// -----------------------------------------------------------------------------

inline bool		Process::IsValid () const
{
	return (m_impl != nullptr);
}

}

#endif // GS_PROCESS_HPP
