/****************************************************************************/
/*																			*/
/*				GLOBAL CONSTANTS, MACROS, VARIABLES AND PROTOTYPES			*/
/*							FOR VIRTUAL MEMORY HANDLING						*/
/*																			*/
/****************************************************************************/

#ifndef	_VM_H_
#define	_VM_H_

#pragma once

//from GSRoot
#include "Definitions.hpp"
#include "PagedArray.hpp"
#include "SpinLock.hpp"

#include "GSModelerPrivExp.h"
#include "Model3D/Swappable.hpp"
#include "Model3D/SwapFolder.hpp"

namespace IO {
	class Folder;
	class File;
}

/* -------------------- DATA TYPES FOR OWN MEMORY ROUTINES ---------------- */

GSMODELER_PRIVATE_EXPORT
void LogVMException (const char* exceptionType, const char* exceptionMessage);

template <class T>
class VMDESC : public Swappable {
	Int32							lastind;
	GS::PagedArray<T>* 	volatile	pagedArr;
	IO::File*						vmFile;
	short							nameInd;
	Modeler::SwapFolderRef			vmFolder;
	char							purgedhdl;

	char							partmode;
public:
	typedef	T ValueType;

	VMDESC (void);
	~VMDESC (void);

	Int32		GetLastInd (void) const;

	T*			VMElemPtr (Int32 i);
	void		VMReal (Int32 lasti);
	void		VMNspac (Int32  n, Int32 *nextind);
	void 		VMReInit ();
	void		VMCompress (Int32 fromind, Int32 offset, Int32 num);
	Int32		VMGetAllocatedBytes (void) const;
	void		VMInit (short nameInd, const Modeler::SwapFolderRef& pVMFolder, bool keepDataInMemory);	

	// Array-like interface
	USize		GetSize (void) const		{ return lastind; }

protected:
	virtual void Purge		() /*noexcept*/ override;
	virtual void ReadPurged () /*noexcept*/ override;
	virtual void ReInitImp	() /*noexcept*/ override;

private:
	// ReadElement and WriteElement methods can be specialized if a specific
	// element type T needs more than the generic implementation.
	static GSErrCode	ReadPagedArray	(GS::PagedArray<T>& toArray, IO::File& fromFile);
	static GSErrCode	WritePagedArray (const GS::PagedArray<T>& pagedArr, IO::File& toFile);
	static GSErrCode	ReadElement		(T& toElement, IO::File& fromFile);
	static GSErrCode	WriteElement	(const T& fromElement, IO::File& toFile);

	void		VMCloseFile (void);
	bool		VMFileValid (void) const;
	void		VMCreateTmpFile (void);
	void		VMOpenFile (short	accessCode);
	void		VMGetPurgedHandle (void);
	void		VMSimpleInit (short nameInd);
	void		VMSingleInit (short nameInd, const Modeler::SwapFolderRef& VMFolder);
	void 		VMSingleReInit ();
	void		VMSimpleNspac (Int32 n, Int32 *nextind);
	void		VMSingleWriteAllH (void);
	void		ClearMembers (void);
	void 		VMFree (void);

#ifdef CHECKED_VERSION
	void		GET_VMDESCNAM (char* thename) const;
#endif
};

/*================================	 VARIABLES	============================*/

/*================================	PROTOTYPES	============================*/

GSMODELER_PRIVATE_EXPORT
GSErrCode		VMDBInit (void);
GSMODELER_PRIVATE_EXPORT
void			VMDBStr (const char *str);

#include "VMImp.hpp"

#endif
