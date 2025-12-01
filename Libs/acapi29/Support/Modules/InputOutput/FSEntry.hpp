
// *****************************************************************************
//
//	                             Interface FSEntry
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FSENTRY_HPP
#define FSENTRY_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

namespace IO { class BaseFileSystem; }

typedef	Int32 GSTime;	// definition from GSTime.h is repeated because GSTime is not of
						// class type and GSTime.h can not be included, but this is ugly



// ============================= Interface FSEntry =============================

namespace IO {

class IO_DLL_EXPORT FSEntry {
public:
		// Types

	enum TimeStatus	{ TM_Ok, TM_FileNotFound, TM_AccessDenied, TM_InvalidTime, TM_Error };

		// Destructor

    virtual ~FSEntry ();

		// Interface

	virtual TimeStatus	SetCreationTime		(const GSTime& newTime) = 0;
	virtual TimeStatus	GetCreationTime		(GSTime* result) const = 0;
	virtual TimeStatus	SetModificationTime (const GSTime& newTime) = 0;
	virtual TimeStatus	GetModificationTime (GSTime* result) const = 0;

	virtual BaseFileSystem&	GetOwnerFileSystem (void) const = 0;
};

}	// namespace IO
// _____________________________ Interface FSEntry _____________________________


#endif
