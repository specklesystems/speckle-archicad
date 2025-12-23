#ifndef GSABORT_HPP
#define GSABORT_HPP

#pragma once

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "GSException.hpp"
#include "Ref.hpp"


namespace GS {

// AbortInterfaceBase

class GSROOT_DLL_EXPORT AbortInterfaceBase
{
public:
	virtual bool ShouldAbort () noexcept = 0;

	virtual ~AbortInterfaceBase ();
};

typedef GS::Ref<AbortInterfaceBase> AbortInterfaceBaseRef;

// AbortException

class GSROOT_DLL_EXPORT AbortException : public GS::Exception  
{
public:
	AbortException ();

	virtual ~AbortException ();
};

// AbortInterface

class GSROOT_DLL_EXPORT AbortInterface
{
public:
	virtual void Test () = 0;

	virtual ~AbortInterface ();
};

typedef GS::Ref<AbortInterface>	AbortInterfaceRef;

} // namespace GS

#endif
