// *****************************************************************************
//
//							Operator new and delete
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MM
//
// SG compatible
//
// *****************************************************************************

#ifndef GSNEW_HPP
#define GSNEW_HPP

#pragma once

#include	<new>

#include	"Definitions.hpp"
#include	"GSException.hpp"
#include	"MemoryManager.hpp"


namespace GS {
	template <class Type>
	inline void		KillObject (Type* &aPointer)
	{
		delete aPointer;
		aPointer = nullptr;
	}

	template <class Type>
	inline void		KillArray (Type* &arrayPointer)
	{
		delete [] arrayPointer;
		arrayPointer = nullptr;
	}
}


#if defined (macintosh)

__attribute__((visibility("default")))
void *CCALL operator new (size_t nBytes);

__attribute__((visibility("default")))
void CCALL operator delete (void *p) throw ();

__attribute__ ((visibility ("default")))
void CCALL operator delete (void* p, size_t nBytes) throw ();

__attribute__((visibility("default")))
void *CCALL operator new[] (size_t nBytes);

__attribute__((visibility("default")))
void CCALL operator delete[] (void *p) throw ();

__attribute__ ((visibility ("default")))
void CCALL operator delete[] (void *p, size_t nBytes) throw ();

__attribute__((visibility("default")))
void *CCALL operator new (size_t nBytes, const std::nothrow_t&) throw ();

__attribute__((visibility("default")))
void CCALL operator delete (void *p, const std::nothrow_t&) throw ();

__attribute__ ((visibility ("default")))
void CCALL operator delete (void *p, size_t nBytes, const std::nothrow_t&) throw ();

__attribute__((visibility("default")))
void *CCALL operator new[] (size_t nBytes, const std::nothrow_t&) throw ();

__attribute__((visibility("default")))
void CCALL operator delete[] (void *p, const std::nothrow_t&) throw ();

__attribute__ ((visibility ("default")))
void CCALL operator delete[] (void *p, size_t nBytes, const std::nothrow_t&) throw ();


#else	// defined (macintosh)


inline void *CCALL operator new (size_t nBytes)
{
	void* p = GS::MemoryManager::Allocate (nBytes, GS::MemoryManager::ThrowGSMemoryFull);
	return  p;
}

inline void CCALL operator delete (void *p) throw ()
{
	GS::MemoryManager::Free (p);
}


inline void CCALL operator delete (void* p, size_t) throw ()
{
	GS::MemoryManager::Free (p);
}

inline void *CCALL operator new[] (size_t nBytes)
{
	void* p = GS::MemoryManager::Allocate (nBytes, GS::MemoryManager::ThrowGSMemoryFull);
	return  p;
}

inline void CCALL operator delete[] (void *p) throw ()
{
	GS::MemoryManager::Free (p);
}

inline void CCALL operator delete[] (void* p, size_t) throw () 
{
	GS::MemoryManager::Free (p);
}

inline void *CCALL operator new (size_t nBytes, const std::nothrow_t&) throw ()
{
	void* p = GS::MemoryManager::Allocate (nBytes);
	return  p;
}

inline void CCALL operator delete (void *p, const std::nothrow_t&) throw ()
{
	GS::MemoryManager::Free (p);
}

inline void CCALL operator delete (void* p, size_t, std::nothrow_t&) throw ()
{
	GS::MemoryManager::Free (p);
}

inline void *CCALL operator new[] (size_t nBytes, const std::nothrow_t&) throw ()
{
	void* p = GS::MemoryManager::Allocate (nBytes);
	return  p;
}

inline void CCALL operator delete[] (void *p, const std::nothrow_t&) throw ()
{
	GS::MemoryManager::Free (p);
}

inline void CCALL operator delete[] (void* p, size_t, const std::nothrow_t&) throw () 
{
	GS::MemoryManager::Free (p);
}

#endif // defined (macintosh)


#endif
