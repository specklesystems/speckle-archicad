#if !defined (MODEL3DMAIN_HPP)
#define MODEL3DMAIN_HPP

#pragma once

#include "RSTypes.hpp"
#include "Definitions.hpp"
#include "GSException.hpp"
#include "Channel.hpp"
#include "RS.hpp" // GSResModule

#include "Model3D/Model3DPrivExp.h"
#include "Model3D/Model3DExport.h"

#include "GSUtilsDefs.h"

// ------------------------------- Exceptions ----------------------------------

DECLARE_EXCEPTION_CLASS (ModelerException, GS::RootException, Error, MODEL3D_DLL_EXPORT)

DECLARE_EXCEPTION_CLASS2 (ModelerOutOfMemoryException,  ModelerException, GS::OutOfMemoryException,     ErrMemoryFull, MODEL3D_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS2 (ModelerOutOf_Big_MemoryException,  ModelerException, GS::OutOfMemoryException,     ErrMemoryFull, MODEL3D_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS2 (ModelerInternalErrorException, ModelerException, GS::InternalErrorException,  ErrParam,      MODEL3D_DLL_EXPORT)

struct List3dRec {
		short	filterIbody, filterBtype, filterBstat;
		short	filterIpgon, filterPstat;
		GSAttributeIndex filterPiumat, filterBiumat;
		Int32	ibody_from_val, ibody_to_val;
		Int32	ipgon_from_val, ipgon_to_val;
		short	btype_from_val, btype_to_val;
		char	stat1_val_str [5], stat2_val_str [5];
		Int32	stat1_val, stat2_val;
		Int32	stat1_include, stat2_include, stat1_exclude, stat2_exclude;
		GSAttributeIndex	iumat1_val, iumat2_val;
};

namespace IO {
	class Folder;
	class Location;
}

namespace Modeler {

enum DiskCachingMethod {
	Cache_UseSwapFile,
	Cache_KeepDataInMemory
};

struct PropertyPair {
	ULong		key;
	GS::Object* value;
};

MODEL3D_PRIVATE_EXPORT IO::Folder* GetTemporaryFolder ();
GSErrCode	Create3DTemporaryFolder (IO::Folder& parentFolder);
void		Free3DTemporaryFolder ();

}; // namespace Modeler

MODEL3D_DLL_EXPORT GSErr MODEL3D_CALL M3DInit (const IO::Location& tempFolder, GSResModule locStringModule, GSResModule fixStringModule);
MODEL3D_DLL_EXPORT void MODEL3D_CALL M3DExit (void);

MODEL3D_DLL_EXPORT	void  CPrintf (GS::OChannel& outChannel, const char* format, ...);


#endif
