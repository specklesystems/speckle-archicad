
// *****************************************************************************
//
//	                         Interface EntryEnumerator
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************



#if !defined ENTRYENUMERATOR_HPP
#define ENTRYENUMERATOR_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

namespace IO { class Name; }



// ========================= Interface EntryEnumerator =========================

namespace IO {

class EntryEnumerator {
public:
		// Destructor

	virtual ~EntryEnumerator ();

		// Interface

	virtual bool	operator() (const Name& entryName, bool isFolder) const = 0;
};

}	// namespace IO
// _________________________ Interface EntryEnumerator _________________________


#endif
