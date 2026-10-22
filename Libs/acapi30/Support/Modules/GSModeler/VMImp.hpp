/****************************************************************************/
/*																			*/
/*							VIRTUAL MEMORY HANDLING							*/
/*																			*/
/****************************************************************************/
#ifndef	_VMIMP_H_
#define	_VMIMP_H_

#include	<stdio.h>				/* sprintf	*/
#include	<stdlib.h>				/* qsort */

#include	"GSRoot.hpp"
#include	"Guard.hpp"
#include	"Owner.hpp"

#include	"FileDef.h"
#include	"GSUtilsres.h"

#include	"File.hpp"
#include	"Folder.hpp"
#include	"FileSystem.hpp"

#include	"DB.h"

#include	"GSModelerExport.h"

/*================================	CONSTANTS	============================*/

#define	USESWAPFILE_VM			0
#define	KEEPDATAINMEMORY_VM		1

/*================================	  MACROS	============================*/

#if defined (DEBUVERS)

#define	VMERROR(s)		VMDBStr(s)
#define	VMDBSTR(s)		if (debuInt == 1000) VMDBStr(s)

#else

#define	VMERROR(s)
#define	VMDBSTR(s)

#endif

/*============================	CONSTANTS	============================*/

/*============================	  MACROS	============================*/

/* ------------------------------- MACROS ------------------------------ */

#define		OPEN_FOR_INPUT			0x0001		/* bit 0. 		*/
#define		OPEN_FOR_OUTPUT			0x0002		/* bit 1. 		*/
#define		OPEN_FOR_IO				0x0003		/* bit 0 + 1.	*/




GSMODELER_DLL_EXPORT
bool VMGetFixString (char *str, short resID, short index);


template <class T>
inline	VMDESC<T>::VMDESC (void)
{
	ClearMembers ();
}


template <class T>
inline	VMDESC<T>::~VMDESC (void)
{
	Swappable::AboutToDestroy ();

	try {
		VMFree ();

		if (DBERROR (pagedArr != nullptr)) {
			delete pagedArr;
			pagedArr = nullptr;
		}
		if (DBERROR (vmFile != nullptr)) {
			GS::KillObject (vmFile);
		}

	} catch (GS::Exception& ex)
	{
		LogVMException ("internal", ex.GetMessage ().ToCStr ().Get ());
		DBBREAK ();
	} catch (...)
	{
		LogVMException ("", "");
		DBBREAK ();
	}
}


template <class T>
inline	Int32	VMDESC<T>::GetLastInd (void) const
{
	return lastind;
}


template <class T>
inline bool VMDESC<T>::VMFileValid (void) const
{
	if (vmFile == nullptr)
		return false;
	 if (vmFile->GetStatus () != NoError)
		 return false;
	 return true;
}


/****************************************************************************/
/****************************************************************************/



/****************************************************************************/
/*																			*/
/*								OPEN FILE OF VMDESC<T>						*/
/*																			*/
/****************************************************************************/

template <class T>
void	VMDESC<T>::VMCreateTmpFile (void)
{
	char		cfilnam [FINAMELEN], buff [560];
	short		i;
	GSErrCode	err;

	err = NoError;

	GS::KillObject (vmFile);
	if (vmFolder != nullptr) {
		IO::Folder folder (vmFolder->GetLocation ());
		if (nameInd) {
			VMGetFixString (cfilnam, TEMP_FILE_NAMES, nameInd);
			err = folder.CreateFile (IO::Name (cfilnam));
			if (err == IO::Folder::TargetExists) {
				folder.Delete (IO::Name (cfilnam));
				err = folder.CreateFile (IO::Name (cfilnam));
			}
			if (err == NoError) {
				vmFile = new IO::File (folder, IO::Name (cfilnam));
			}
		} else {
			VMGetFixString (cfilnam, TEMP_FILE_NAMES, TMP_GENERAL);			/* Archicad.Temp */
			cfilnam [FINAMELEN - 5] = '\0';
			for (i = 1; i <= 999; i++) {
				sprintf (buff, "%s%d", cfilnam, i);
				err = folder.CreateFile (IO::Name (buff));
				if (err != IO::Folder::TargetExists) {
					if (err == NoError) {
						vmFile = new IO::File (folder, IO::Name (buff));
						break;
					} else {
						throw GS::InternalErrorException ();
					}
				}
			}
		}
	} else {
		err = Error;
	}
	if (vmFile == nullptr)
		err = Error;

	if (err != NoError)
		throw GS::InternalErrorException ();
}


template <class T>
void	VMDESC<T>::VMOpenFile (short accessCode)	// throws exception
{
	if (VMFileValid () && vmFile->IsOpen ())
		return;

	bool vmFileExists = VMFileValid ();
	if (!vmFileExists && accessCode == OPEN_FOR_INPUT) {
#ifdef	DEBUVERS
		sprintf(debuLine, "Missing file for INPUT in VMOpenFile (nameInd): %hd ", nameInd/*, vmfoldid*/);
		DBBREAK_STR (debuLine);
#endif
		throw GS::LogicErrorException();
	}

	if (!vmFileExists)
		VMCreateTmpFile ();

	IO::File::OpenMode	openMode;
	switch (accessCode) {
			case OPEN_FOR_INPUT:	openMode = IO::File::ReadMode; break;
			case OPEN_FOR_OUTPUT:	openMode = IO::File::WriteMode; break;
			default:
			case OPEN_FOR_IO:		openMode = IO::File::ReadWriteMode; break;
	}
	GSErrCode err = vmFile->Open (openMode);
	if (err == NoError && (accessCode != OPEN_FOR_INPUT)) {
		err = vmFile->SetDataLength (lastind * sizeof(T));
	}
	if (vmFile != nullptr && err != NoError)
		vmFile->Close ();

	if (err != NoError)
		throw GS::InternalErrorException();
}


template <class T>
void	VMDESC<T>::VMGetPurgedHandle (void)
{
	if (partmode != KEEPDATAINMEMORY_VM) {
		RestoreFromDisk ();
	}
}


#ifdef	DEBUVERS
template <class T>
void	VMDESC<T>::GET_VMDESCNAM (char* thename) const
{
	if (VMFileValid ()) {
		IO::Location	location;
		IO::Name		name;
		vmFile->GetLocation (&location);
		location.GetLastLocalName (&name);
		strcpy (thename, name.ToString ().ToCStr ());
	} else {
		VMGetFixString (thename, TEMP_FILE_NAMES, nameInd);
	}
}
#endif


/****************************************************************************/
/*																			*/
/*							INITIALIZE VIRTUAL MEMORY						*/
/*																			*/
/****************************************************************************/
template <class T>
void	VMDESC<T>::VMSimpleInit (short nameInd)		// throws exception
{
	pagedArr		= new GS::PagedArray<T> ();
	lastind			= 0;
	this->nameInd	= nameInd;
	vmFile			= nullptr;
	vmFolder		= nullptr;
}

template <class T>
void	VMDESC<T>::VMSingleInit (short nameInd, const Modeler::SwapFolderRef& VMFolder)		// throws exception
{
	pagedArr		= new GS::PagedArray<T> ();
	lastind			= 0;
	this->nameInd	= nameInd;
	vmFile			= nullptr;
	vmFolder		= VMFolder;
}


template <class T>
void	VMDESC<T>::VMInit (short nameInd, const Modeler::SwapFolderRef& pVMFolder, bool keepDataInMemory)			// throws exception
{
	if (keepDataInMemory) {
		partmode	= KEEPDATAINMEMORY_VM;
		VMSimpleInit (nameInd);
	} else {
		bool folderError = (pVMFolder == nullptr) || (IO::Folder (pVMFolder->GetLocation ()).GetStatus () != NoError);

		if (folderError) {
			ClearMembers ();
			partmode	= KEEPDATAINMEMORY_VM;
			VMSimpleInit (nameInd);
		} else {
			ClearMembers ();
			partmode	= USESWAPFILE_VM;
			VMSingleInit (nameInd, pVMFolder);
		}
	}
}


/****************************************************************************/
/*																			*/
/*							REINITIALIZE VIRTUAL MEMORY						*/
/*																			*/
/****************************************************************************/
template <class T>
void 	VMDESC<T>::VMSingleReInit ()
{
	if (VMFileValid ()) {
		VMOpenFile (OPEN_FOR_IO);
		VMCloseFile ();
	}
}


template <class T>
void 	VMDESC<T>::VMReInit ()
{
	ReInit ();
}


/****************************************************************************/
/*																			*/
/*			INCREMENT THE SIZE OF A VIRTUAL MEMORY BY  N  ELEMENTS			*/
/*																			*/
/****************************************************************************/
template <class T>
void	VMDESC<T>::VMSimpleNspac (Int32 n, Int32 *nextind)
{
	if (n < 0) {
		*nextind = lastind;
		throw GS::LogicErrorException();			/* !!! */
	}

	pagedArr->SetSize(pagedArr->GetSize() + n);
	*nextind = lastind + 1;
	lastind += n;
}


template <class T>
void	VMDESC<T>::VMNspac (Int32  n, Int32 *nextind)	// throws exception
{
	VMGetPurgedHandle ();
	DBASSERT_STR (pagedArr == nullptr || (Int32)pagedArr->GetSize() == lastind, "Integrity error in VM!!!");
	VMSimpleNspac (n, nextind);
	DBASSERT_STR (pagedArr == nullptr || (Int32)pagedArr->GetSize() == lastind, "Integrity error in VM!!!");
}


/****************************************************************************/
/*																			*/
/*						MODIFY THE SIZE OF A VIRTUAL MEMORY					*/
/*							  (Changes maxind)								*/
/*																			*/
/****************************************************************************/

template <class T>
void	VMDESC<T>::VMReal (Int32 lasti)	// throws exception
{
	VMGetPurgedHandle ();
	DBASSERT_STR (pagedArr == nullptr || (Int32)pagedArr->GetSize() == lastind, "Integrity error in VM!!!");

	//DBASSERT_STR (lasti <= (long)pagedArr->GetSize(), "VMReal: Reallocating to smaller size than the number of used elements!");

	pagedArr->SetSize(lasti);
	lastind = lasti;
}


/****************************************************************************/
/*																			*/
/*						RELEASE UNUSED PART OF A VIRTUAL MEMORY				*/
/*																			*/
/****************************************************************************/

/****************************************************************************/
/*																			*/
/*								RELEASE VIRTUAL MEMORY						*/
/*																			*/
/****************************************************************************/

template <class T>
void 	VMDESC<T>::VMFree (void)
{
	lastind	=  0;

	delete pagedArr;
	pagedArr = nullptr;

	purgedhdl = 0;

	if (VMFileValid ()) {
		/* Because of the stupid Norton */
		try {
			try {
				VMOpenFile (OPEN_FOR_OUTPUT);
				vmFile->SetDataLength (0);
			} catch (const GS::Exception& ) {}
			VMCloseFile ();
		} catch (const GS::Exception& ) {}

		IO::Name		name;
		IO::Location	location;
		vmFile->GetLocation (&location);
		location.GetLastLocalName (&name);
		bool vmFolderInvalid = false;
		if (vmFolder != nullptr) {
			IO::Folder folder (vmFolder->GetLocation ());
			if (folder.GetStatus () == NoError)
				folder.Delete (name);
			else
				vmFolderInvalid = true;
		} else {
			vmFolderInvalid = true;
		}
		if (vmFolderInvalid) {
			location.DeleteLastLocalName ();
			IO::Folder parentFolder (location);
			parentFolder.Delete (name);
		}
		GS::KillObject (vmFile);
	}

	vmFolder = nullptr;
	partmode = KEEPDATAINMEMORY_VM;
}


template <class T>
void VMDESC<T>::Purge ()
{
	try {
		if (partmode != KEEPDATAINMEMORY_VM && DBVERIFY (pagedArr != nullptr)) {
			VMSingleWriteAllH ();

			delete pagedArr;
			pagedArr = nullptr;
			purgedhdl = 1;
		}
	} catch (const GS::Exception& /*ex*/) {
		// leave data in memory
		DBBREAK_STR ("VMDESC::Purge failed!");
		throw;
	}
}


template <class T>
void VMDESC<T>::ReadPurged ()
{
	if (purgedhdl > 0 && DBVERIFY (pagedArr == nullptr)) {
		try {
			GS::Owner<GS::PagedArray<T>> newPagedArr (new GS::PagedArray<T> ());
			newPagedArr->SetSize(lastind);
			if (lastind > 0) {
#ifdef	DEBUVERS
				char	cfilnam [FINAMELEN];
				GET_VMDESCNAM(cfilnam);
				sprintf(debuLine, "						VMSingleReadH\t%s\t\tnumelems: %6ld", cfilnam, (GS::LongForStdio) lastind);
				VMDBSTR (debuLine);
#endif

				VMOpenFile (OPEN_FOR_INPUT);
				if (vmFile != nullptr) {
					GSErrCode ret = vmFile->Seek (IO::File::Start, 0);
					if (ret == NoError) {
						ret = ReadPagedArray (*newPagedArr, *vmFile);
					}

					VMCloseFile ();
					if (ret != NoError)
						throw GS::InternalErrorException();
				}

			}

			purgedhdl = 0;
			pagedArr = newPagedArr.Release ();
		} catch (const GS::Exception& /*ex*/) {
			// leave purgedhdl > 0 and pagedArray == nullptr
			DBBREAK_STR ("VMDESC::ReadPurged failed!");
			if (vmFile != nullptr) {
				VMCloseFile ();
			}
			throw;
		}
	}
}


template <class T>
void VMDESC<T>::ReInitImp ()
{
	lastind	= 0;
	delete pagedArr;
	pagedArr = new GS::PagedArray<T> ();

	if (partmode != KEEPDATAINMEMORY_VM) {
		VMSingleReInit ();	// may throw
	}
}

// =====================================================================================================================
// I/O method definitions
// =====================================================================================================================


// ---------------------------------------------------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------------------------------------------------

template <class T>
GSErrCode	VMDESC<T>::ReadElement (T& toElement, IO::File& fromFile)
{
	return fromFile.ReadBin ((GSPtr)&(toElement), sizeof(T));
}

template <class T>
GSErrCode	VMDESC<T>::WriteElement (const T& fromElement, IO::File& toFile)
{
	return toFile.WriteBin ((const GSPtr)&(fromElement), sizeof(T));
}

// ---------------------------------------------------------------------------------------------------------------------
// Reads up the contents of @pagedArr from the given file. The size of @pagedArr must be set before.
// ---------------------------------------------------------------------------------------------------------------------
template <class T>
GSErrCode	VMDESC<T>::ReadPagedArray (GS::PagedArray<T>& toArray, IO::File& fromFile)
{
	GSErrCode ret = NoError;
	for (UIndex i = 0; i < toArray.GetSize () && ret == NoError; ++i) {
		ret = ReadElement (toArray[i], fromFile);
	}

	return ret;
}

// ---------------------------------------------------------------------------------------------------------------------
// Writes the contents of @pagedArr to the given file.
// ---------------------------------------------------------------------------------------------------------------------
template <class T>
GSErrCode	VMDESC<T>::WritePagedArray (const GS::PagedArray<T>& pagedArr, IO::File& toFile)
{
	GSErrCode ret = NoError;
	for (UIndex i = 0; i < pagedArr.GetSize () && ret == NoError; ++i) {
		ret = WriteElement (pagedArr[i], toFile);
	}

	return ret;
}


template <class T>
void	VMDESC<T>::VMCompress (Int32 fromind, Int32 offset, Int32 num)	// throws exception
{
	if (offset < 0) {
		DBINT("VMCompress parameter error ! offset", offset);
		throw GS::IllegalArgumentException();
	}

	VMGetPurgedHandle ();

	DBASSERT_STR (pagedArr == nullptr || (Int32)pagedArr->GetSize() == lastind, "Integrity error in VM!!!");

	if (offset == 0)
		return;	// items would be moved to their original positions

	Int32 fromoffs = (fromind - 1);
	Int32 tooffs   = (fromind - offset - 1);

	if (fromoffs + num > (Int32) (pagedArr->GetSize ())) {
		DBPRINTF("VMCompress parameter error! fromoffs + num > pagedArr->GetSize ()");
		throw GS::IllegalArgumentException();
	}

	if (tooffs < 0) {
		DBPRINTF("VMCompress parameter error! tooffs < 0");
		throw GS::IllegalArgumentException();
	}

	for (Int32 j = 1; j<= num; j++)
		(*pagedArr)[tooffs++] = (*pagedArr)[fromoffs++];
}




/****************************************************************************/
/*																			*/
/*																			*/
/****************************************************************************/

/****************************************************************************/
/*																			*/
/*							  CLOSE FILE OF VMDESC<T>						*/
/*																			*/
/****************************************************************************/

template <class T>
void	VMDESC<T>::VMCloseFile (void)	// throws exception
{
	GSErrCode	ret = NoError;

	if (partmode == KEEPDATAINMEMORY_VM)
		return;

	if (VMFileValid () && vmFile->IsOpen ())
		ret = vmFile->Close ();

	if (ret != NoError)
		throw GS::InternalErrorException ();
}


template <class T>
inline T*	VMDESC<T>::VMElemPtr (Int32 i)	// throws exception
{
	if (DBERROR (i < 1 || i > lastind))
		throw GS::LimitViolationException ();

	VMGetPurgedHandle ();
	return &(*pagedArr)[i-1];
}


/****************************************************************************/
/*																			*/
/*					WRITE CONTENT OF ARRHDL && PARTHDL TO FILE				*/
/*																			*/
/****************************************************************************/

template <class T>
void	VMDESC<T>::VMSingleWriteAllH (void)		// throws exception
{
	if (lastind < 1)
		return;

#ifdef	DEBUVERS
	char	cfilnam [FINAMELEN];
	GET_VMDESCNAM(cfilnam);
	sprintf(debuLine, "					VMSingleWriteAllH\t%s\t\tnumelems: %6ld", cfilnam, (GS::LongForStdio)lastind);
	VMDBSTR (debuLine);
#endif

	GSErrCode ret = NoError;
	VMOpenFile (OPEN_FOR_OUTPUT);
	if (VMFileValid ()) {
		ret = vmFile->SetDataLength (lastind * sizeof(T));
		if (ret == NoError)
			ret = vmFile->Seek (IO::File::Start, 0);
		if (ret == NoError) {
			ret = WritePagedArray (*pagedArr, *vmFile);
		}

		VMCloseFile ();
	}

	if (ret != NoError)
		throw GS::InternalErrorException();
}


template <class T>
Int32	VMDESC<T>::VMGetAllocatedBytes (void) const
{
	return lastind * sizeof(T);
}


template <class T>
void	VMDESC<T>::ClearMembers (void)
{
	lastind		= 0;
	pagedArr	= nullptr;
	vmFile		= nullptr;
	nameInd		= 0;
	vmFolder	= nullptr;
	purgedhdl	= 0;
	partmode	= KEEPDATAINMEMORY_VM;
}

#endif
