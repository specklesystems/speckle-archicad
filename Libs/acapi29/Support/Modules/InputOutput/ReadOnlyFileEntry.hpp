
// *****************************************************************************
//
//	                        Interface ReadOnlyFileEntry
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined READONLYFILEENTRY_HPP
#define READONLYFILEENTRY_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "FileEntry.hpp"



// ======================== Interface ReadOnlyFileEntry ========================

namespace IO {

class IO_DLL_EXPORT ReadOnlyFileEntry: public FileEntry {
public:
   ~ReadOnlyFileEntry () {}

	virtual TimeStatus		SetCreationTime		(const GSTime& newTime) override;
	virtual TimeStatus		SetModificationTime (const GSTime& newTime) override;

	virtual WriteStatus		Write (const char* source, USize nOfCharToWrite, USize* written) override;
	virtual WriteStatus		Flush (void) override;

	virtual LengthStatus	SetDataLength (UInt64 newLength) override;

	virtual TypeStatus		SetTypeInfo (UInt32 newType, UInt32 newCreator) override;


	virtual AttributeStatus	IsWriteProtected   (bool* result) const override;
	virtual AttributeStatus SetWriteProtection (bool protect) override;

	virtual	void*			CreateMapping (OpenMode om, UInt64 offset, USize size) override;
	virtual	CloseStatus		CloseMapping (void* mapAddress, USize size) override;
};

}	// namespace IO
// ________________________ Interface ReadOnlyFileEntry ________________________


#endif
