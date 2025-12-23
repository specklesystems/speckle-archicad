
// *****************************************************************************
//
//						         Class SessionUnId
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *****************************************************************************


#if !defined SESSIONUNID_HPP
#define SESSIONUNID_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"


// ================================ Class Event ================================

namespace GS {

class GSROOT_DLL_EXPORT SessionUnId {
private:
	static UInt32 sid1;
	static UInt32 sid2;

public:
	UInt32 m_id1;
	UInt32 m_id2;

public:
	SessionUnId ();
	SessionUnId (const GS::UInt64& id)					{ m_id1 = (Int32) (id & 0xFFFFFFFF); m_id2 = (Int32) (id >> 32); }
	void Generate ();
	void Clear () { m_id1 = 0; m_id2 = 0; }
	bool operator== (const SessionUnId& other) const	{ return m_id1 == other.m_id1 && m_id2 == other.m_id2; }
	bool operator!= (const SessionUnId& other) const	{ return m_id1 != other.m_id1 || m_id2 != other.m_id2; }
	bool operator<	(const SessionUnId& other) const	{ return m_id2 < other.m_id2 || (m_id2 == other.m_id2 && m_id1 < other.m_id1); }
	bool operator<=	(const SessionUnId& other) const	{ return *this == other || *this < other; }
	bool operator>	(const SessionUnId& other) const	{ return m_id2 > other.m_id2 || (m_id2 == other.m_id2 && m_id1 > other.m_id1); }
	bool operator>=	(const SessionUnId& other) const	{ return *this == other || *this > other; }
};

extern GSROOT_DLL_EXPORT const SessionUnId NullSessionUnId;

}	// namespace GS

// ________________________________ Class Event ________________________________


#endif
