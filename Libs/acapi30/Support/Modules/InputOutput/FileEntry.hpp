
// *****************************************************************************
//
//	                            Interface FileEntry
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FILEENTRY_HPP
#define FILEENTRY_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "FSEntry.hpp"

namespace IO { class UniString; }



// ============================ Interface FileEntry ============================

namespace IO {

class IO_DLL_EXPORT FileEntry: public FSEntry {
public:
		// Types

	enum OpenStatus   { OP_Ok, OP_FileNotFound, OP_AccessDenied, OP_NoMoreOSFile, OP_Error };
	enum ReadStatus   { RD_Ok, RD_EOF, RD_Error };
	enum WriteStatus  { WR_Ok, WR_DeviceIsFull, WR_Error };
	enum SeekStatus   { SK_Ok, SK_IllegalPosition, SK_Error };
	enum CloseStatus  { CL_Ok, CL_WriteError, CL_DeviceIsFull, CL_Error };
	enum LengthStatus { LN_Ok, LN_FileNotFound, LN_AccessDenied, LN_DeviceIsFull, LN_Error };
	enum TypeStatus	  { TP_Ok, TP_FileNotFound, TP_AccessDenied, TP_Error };
	enum AttributeStatus { AT_Ok, AT_FileNotFound, AT_AccessDenied, AT_Error };

	enum OpenMode { OM_Read, OM_Write, OM_WriteEmpty, OM_ReadWrite, OM_ReadSharedRW, OM_WriteSharedR, OM_WriteEmptySharedR, OM_ReadWriteSharedR };

	enum SeekOrigin { SO_Start, SO_Current, SO_End };

	enum WriteAccessFailureReason { Authorization, Exclusion, Unknown };

		// Destructor

    ~FileEntry ();

		// Interface

	virtual OpenStatus		Open  (OpenMode om) = 0;
	virtual ReadStatus		Read  (char* destination,  USize nOfCharToRead,  USize* read) = 0;
	virtual WriteStatus		Write (const char* source, USize nOfCharToWrite, USize* written) = 0;
	virtual SeekStatus		Seek  (SeekOrigin so, Int64 offset, UInt64* newPos) = 0;
	virtual WriteStatus		Flush (void) = 0;
	virtual CloseStatus		Close (void) = 0;

	virtual LengthStatus	SetDataLength (UInt64 newLength) = 0;
	virtual LengthStatus	GetDataLength (UInt64* result) const = 0;

	virtual TypeStatus		SetTypeInfo (UInt32 newType, UInt32 newCreator) = 0;
	virtual TypeStatus		GetTypeInfo (UInt32* type, UInt32* creator) const = 0;

	virtual AttributeStatus	IsWriteProtected   (bool* result) const = 0;
	virtual AttributeStatus SetWriteProtection (bool protect) = 0;

	virtual	void*			CreateMapping (OpenMode om, UInt64 offset, USize size) = 0;
	virtual	CloseStatus		CloseMapping (void* mapAddress, USize size) = 0;

	virtual WriteAccessFailureReason	DetermineWriteAccessFailureReason (GS::UniString* /*reasonParameters*/) const { return Unknown; }
};

}	// namespace IO
// ____________________________ Interface FileEntry ____________________________



#endif
