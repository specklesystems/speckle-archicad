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

#ifndef GS_RSINIT_HPP
#define GS_RSINIT_HPP

// from GSRoot
#include "DllMainImp.hpp"

// from RS
#include "RS.hpp"


// === RS internal functions ===========================================================================================


namespace RS {

RS_DLL_EXPORT
void	ResModuleClosed (GSResModule);

} // namespace RS


// =====================================================================================================================


struct DllMainImp_ResModuleSpec;


GSResModule					DllMainImp_OpenResModule (const DllMainImp_InitContext* ctx);
void						DllMainImp_CloseResModule (GSResModule res);

DllMainImp_ResModuleSpec	DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* ctx);
GSResModule					DllMainImp_OpenResModuleFromSpec (const DllMainImp_ResModuleSpec* ctx);


// === WINDOWS =========================================================================================================

#if defined (WINDOWS)

struct DllMainImp_ResModuleSpec {
	HANDLE hInstance;
};

// --- Implementation --------------------------------------------------------------------------------------------------


DllMainImp_ResModuleSpec	DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* ctx)
{
	return { ctx->hInstance };
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
	RS::ResModuleClosed (module);
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


struct DllMainImp_ResModuleSpec {
	const char* mResPath;
};


PRIVATEEXTERN DllMainImp_ResModuleSpec		DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* ctx);
PRIVATEEXTERN GSResModule					DllMainImp_OpenResModule (const DllMainImp_InitContext* ctx);
PRIVATEEXTERN GSResModule					DllMainImp_OpenResModuleFromSpec (const DllMainImp_ResModuleSpec* spec);
PRIVATEEXTERN void							DllMainImp_CloseResModule (GSResModule res);


PRIVATEEXTERN DllMainImp_ResModuleSpec		DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* ctx)
{
	DllMainImp_ResModuleSpec result {};
	result.mResPath = GetBundlePath (ctx);

	return result;
}

PRIVATEEXTERN GSResModule	DllMainImp_OpenResModule (const DllMainImp_InitContext* ctx)
{
	const char* bundlePath = GetBundlePath (ctx);
	if (strlen (bundlePath) == 0)
		return InvalidResModule;

	GSResModule result = RSOpenResourceFile (bundlePath);
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

struct DllMainImp_ResModuleSpec {};


// --- Implementation --------------------------------------------------------------------------------------------------

DllMainImp_ResModuleSpec	DllMainImp_GetResModuleSpec (const DllMainImp_InitContext* /*ctx*/)
{
	return DllMainImp_ResModuleSpec {};
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


#endif /* GS_RSINIT_HPP */
