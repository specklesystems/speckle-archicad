// *********************************************************************************************************************
// Description:		Generic dll initialization/termination routines
//
// Module:			RS
// Namespace:		-
// Contact person:	SzaM
//
// SG compatible
// *********************************************************************************************************************

// --- Predeclarations -------------------------------------------------------------------------------------------------

#ifndef RS_INIT_HPP
#define RS_INIT_HPP

#include "DllMainImp.hpp"

typedef struct DllMainImp_ResModuleSpec DllMainImp_ResModuleSpec;
typedef GS::IntPtr   GSResModule;

// --- Prototypes ------------------------------------------------------------------------------------------------------


	// Open resource of the module
GSResModule		DllMainImp_OpenResModule (const DllMainImp_InitContext* ctx);
void			DllMainImp_CloseResModule (GSResModule res);

DllMainImp_ResModuleSpec	DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* ctx);
GSResModule					DllMainImp_OpenResModuleFromSpec (const DllMainImp_ResModuleSpec* ctx);


// === Implementation ==================================================================================================

#include	"RS.hpp"

// === WINDOWS =========================================================================================================

#if defined (WINDOWS)

typedef struct DllMainImp_ResModuleSpec {
	HANDLE 	hInstance;
} DllMainImp_ResModuleSpec;

// --- Implementation --------------------------------------------------------------------------------------------------


DllMainImp_ResModuleSpec	DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* ctx)
{
	DllMainImp_ResModuleSpec result;
	result.hInstance = const_cast<HANDLE> (ctx->hInstance);
	return result;
}

GSResModule		DllMainImp_OpenResModule (const DllMainImp_InitContext* ctx)
{
	return RSInitModuleImageCache (reinterpret_cast<GSResModule> (ctx->hInstance));
}

GSResModule		DllMainImp_OpenResModuleFromSpec (const DllMainImp_ResModuleSpec* spec)
{
	return RSInitModuleImageCache (reinterpret_cast<GSResModule> (spec->hInstance));
}

void 			DllMainImp_CloseResModule (GSResModule module)
{
	RSRemoveModuleImageCache (module);
}


#endif // defined(WINDOWS)

// === Mac - MachO ======================================================================================================

#if defined __APPLE__

#ifndef MAXPATH
#define MAXPATH 1024
#endif

#define DLLEXPORT
#define PRIVATEEXTERN

// --- Implementation ---------------------------------------------------------------------------------------------------


typedef struct DllMainImp_ResModuleSpec
{
	const char* mResPath;
} DllMainImp_ResModuleSpec;


PRIVATEEXTERN DllMainImp_ResModuleSpec		DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* ctx);
PRIVATEEXTERN GSResModule					DllMainImp_OpenResModule (const DllMainImp_InitContext* ctx);
PRIVATEEXTERN GSResModule					DllMainImp_OpenResModuleFromSpec (const DllMainImp_ResModuleSpec* spec);
PRIVATEEXTERN void							DllMainImp_CloseResModule (GSResModule res);


PRIVATEEXTERN DllMainImp_ResModuleSpec		DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* ctx)
{
	DllMainImp_ResModuleSpec result = {0};
	result.mResPath = GetBundlePath (ctx);

	return result;
}

PRIVATEEXTERN GSResModule	DllMainImp_OpenResModule (const DllMainImp_InitContext* ctx)
{
	GSResModule result = InvalidResModule;

	const char *bundlePath = GetBundlePath (ctx);
	GS::AutoCFTypeRef<CFURLRef> bundleURL (CFBundleCopyBundleURL (ctx->bundle));
	if (strlen (bundlePath) == 0)
		return InvalidResModule;

	result = RSOpenResourceFile (bundlePath);
	DBASSERT (result != InvalidResModule);

	return result;
}

PRIVATEEXTERN GSResModule	DllMainImp_OpenResModuleFromSpec (const DllMainImp_ResModuleSpec* spec)
{
	GSResModule result = InvalidResModule;
	if (spec == nullptr || spec->mResPath == nullptr)
		return result;
	return RSOpenResourceFile (spec->mResPath);
}

PRIVATEEXTERN void  DllMainImp_CloseResModule (GSResModule res)
{
	RSRemoveModuleImageCache (res);
	RSCloseResourceFile (res);
}

#endif // __APPLE__

// === Linux ===========================================================================================================

#if defined (__linux__)

typedef struct DllMainImp_ResModuleSpec {
} DllMainImp_ResModuleSpec;


// --- Implementation --------------------------------------------------------------------------------------------------

DllMainImp_ResModuleSpec	DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* /*ctx*/)
{
	DllMainImp_ResModuleSpec result;
	return result;
}


GSResModule		DllMainImp_OpenResModule (const DllMainImp_InitContext* /*ctx*/)
{
	return GSResModule {};
}


GSResModule		DllMainImp_OpenResModuleFromSpec (const DllMainImp_ResModuleSpec* /*spec*/)
{
	return GSResModule {};
}


void	DllMainImp_CloseResModule (GSResModule /*module*/)
{
}

#endif // (__linux__)

#endif // RS_INIT_HPP
