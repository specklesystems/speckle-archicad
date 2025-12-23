// *********************************************************************************************************************
// Description:		Generic dll initialization/termination routines
//
// Module:			GSRoot
// Namespace:		-
// Contact person:	FM
//
// SG compatible
// *********************************************************************************************************************

// *********************************************************************************************************************
// Documentation:
//
//	DllMainImp.hpp is a cross platform DllInit implementation.
//
// Synopsis:
//		#define CALL_DLL_INIT
//		#define CALL_DLL_TERM
//		#include "DllMainImp.hpp"
//
//		static bool DllInit (const DllMainImp_InitContext* ctx)
//		{
//			IO::Location moduleLocation (DllMainImp_GetLocation (ctx));
//			GSResModule resModule = DllMainImp_OpenResModule (ctx);
//		}
//
//		static bool DllTerm (void)
//		{
//			DllMainImp_CloseResModule (resModule);
//		}
//
//
// Possible options:
//		DLLMAINIMP_PLUGIN
//		CALL_RAW_DLL_INIT, CALL_DLL_INIT, CALL_DLL_TERM, CALL_RAW_DLL_TERM, IMPLEMENT_DLL_MAINENTRY
//
//
// Windows only:
//		DllMainImp_GetWindowsHInstance
// *********************************************************************************************************************

// --- Predeclarations -------------------------------------------------------------------------------------------------

#ifndef DLL_MAIN_IMP_HPP
#define DLL_MAIN_IMP_HPP

#include "Definitions.hpp"

typedef struct DllMainImp_InitContext 	DllMainImp_InitContext;

#if defined(WINDOWS)
#include "Win32Interface.hpp"
#include "DebugHeap.hpp"
#endif

#if defined(macintosh)
#include <ApplicationServices/ApplicationServices.h>
#include "MacUtils/AutoCFTypeRef.hpp"
#endif

#if defined(__linux__)
#include <dlfcn.h>
#include <linux/limits.h>
#include <stdlib.h>
#endif

#if defined (macintosh) || (__linux__)
struct DllMainImp_LocationSpec {
	operator const char* () const {
		return mFullPath;
	};
	const char* mFullPath;
};
#endif


#if defined (WINDOWS)
struct DllMainImp_LocationSpec {
	operator const WCHAR* () const {
		return mFullPath;
	};
	const WCHAR* mFullPath;
};
#endif

// --- Prototypes ------------------------------------------------------------------------------------------------------


	// Get the location of the module
DllMainImp_LocationSpec DllMainImp_GetLocation (const DllMainImp_InitContext* ctx);

	// Get platform specific information about the module
#if defined(WINDOWS)
	HINSTANCE		DllMainImp_GetWindowsHInstance (const DllMainImp_InitContext* ctx);
#endif


#if defined(CALL_DLL_INIT)
	static bool DllInit (const DllMainImp_InitContext* ctx);
#endif

#if defined(CALL_DLL_TERM)
	static bool DllTerm ();
#endif

#if defined(CALL_RAW_DLL_INIT) && defined(WINDOWS)
	static bool RawDllInit (const DllMainImp_InitContext* ctx);
#endif

#if defined(CALL_RAW_DLL_TERM) && defined(WINDOWS)
	static bool RawDllTerm ();
#endif

// === Implementation ==================================================================================================

#include	"GSDebug.hpp"

// === WINDOWS =========================================================================================================

#if defined (WINDOWS)
#include	"Win32Interface.hpp"
#include    <stdlib.h>

#if defined (CALL_RAW_DLL_INIT) || defined (CALL_RAW_DLL_TERM)
	#if !defined (IMPLEMENT_DLL_MAINENTRY)
		#define IMPLEMENT_DLL_MAINENTRY 1
	#endif
#endif

#if !defined(_MSC_VER)
	#pragma error ("Only MSVC is supported on Windows")
#endif


typedef struct DllMainImp_InitContext {
	HANDLE 	hInstance;
} DllMainImp_InitContext;


// --- Implementation --------------------------------------------------------------------------------------------------

HINSTANCE		DllMainImp_GetWindowsHInstance (const DllMainImp_InitContext* ctx)
{
	return const_cast<HINSTANCE> (reinterpret_cast<HINSTANCE> (ctx->hInstance));
}


DllMainImp_LocationSpec			DllMainImp_GetLocation (const DllMainImp_InitContext* ctx)
{
	DllMainImp_LocationSpec locationSpec = {0};
	static WCHAR filename[MAX_PATH];
	if (DBERROR (GetModuleFileNameW (reinterpret_cast<HINSTANCE> (const_cast<HANDLE> (ctx->hInstance)), filename, sizeof(filename)/sizeof (WCHAR)) == 0)) {
	  locationSpec.mFullPath = L"";
	}
	locationSpec.mFullPath = filename;
	return locationSpec;
}


#pragma warning (push)
#pragma warning (disable: 4995)

static WCHAR gDllFileName [_MAX_PATH];
static char gDllFileNameAnsi [_MAX_PATH];
BOOL WINAPI
DllMain (HANDLE hInstance, ULONG uReason, LPVOID reserved)
{
#if defined(CALL_DLL_INIT)
	DllMainImp_InitContext ctx;
	ctx.hInstance = hInstance;
#else
	UNUSED_PARAMETER (hInstance);
#endif

	switch (uReason) {
		case DLL_PROCESS_ATTACH:
			#if defined (DEBUVERS) && defined (HEAP_DEBUG)
				if (GetModuleFileNameW ((HMODULE)hInstance, gDllFileName, _MAX_PATH) == 0)
					return FALSE;
				if (DBGetFlags (DBGeneral) & DBEnableLoadTrace) {
					if (GetModuleFileNameA ((HMODULE)hInstance, gDllFileNameAnsi, _MAX_PATH) == 0) {
						return FALSE;
					}
					DBPRINTF ("\n++++++ DLL Loaded: 0x%p from %s\n", hInstance, gDllFileNameAnsi);
				}
				DebugHeap::addmodule ((HMODULE)hInstance, gDllFileName);
			#endif
			#if defined(CALL_DLL_INIT)
				if (!DllInit (&ctx))
					return FALSE;
			#endif

			break;
		case DLL_PROCESS_DETACH:
			#if defined (DEBUVERS) && defined (HEAP_DEBUG)
				/* reserved != nullptr means that the process is terminating (for details, see the MSDN documentation of DllMain)
				 * Upon process termination, DLLs don't actually get unloaded
				 * (calling DebugHeap::removemodule on termination interferes with our memory leak detection code) */
				if (reserved == nullptr)
					DebugHeap::removemodule (gDllFileName);
			#else
				UNUSED_PARAMETER (reserved);
			#endif
			#if defined (DEBUVERS)
				if (DBGetFlags (DBGeneral) & DBEnableLoadTrace) {
					if (GetModuleFileNameA ((HMODULE)hInstance, gDllFileNameAnsi, _MAX_PATH) == 0) {
						return FALSE;
					}
					DBPRINTF ("\n------ DLL Unloaded: %s\n", gDllFileNameAnsi);
				}
			#endif

			#if defined(CALL_DLL_TERM)
				DllTerm ();
			#endif

			break;
	}
	return TRUE;
}

#pragma warning (pop)

#if IMPLEMENT_DLL_MAINENTRY
BOOL WINAPI RawDllMain (HANDLE hInstance, DWORD uReason, LPVOID)
{
	switch (uReason) {
		case DLL_PROCESS_ATTACH:
			DllMainImp_InitContext initContext;
			initContext.hInstance = hInstance;

			#if defined (CALL_RAW_DLL_INIT)
			if (RawDllInit (&initContext) == false)
				return FALSE;
			#endif

			break;
		case DLL_PROCESS_DETACH:
			#if defined (CALL_RAW_DLL_TERM)
			if (RawDllTerm () == false)
				return FALSE;
			#endif

			break;
		default:
			break;
	}
	return TRUE;
}

extern "C" BOOL WINAPI _CRT_INIT (HANDLE, DWORD, LPVOID);
BOOL (WINAPI *_pRawDllMain) (HANDLE, DWORD, LPVOID) = RawDllMain;

static int __proc_attached = 0 ;
BOOL WINAPI _CRT_INIT_MY(
	HANDLE  hDllHandle,
	DWORD   dwReason,
	LPVOID  lpreserved
)
{
	/*
	* If this is a process detach notification, check that there has
	* been a prior (successful) process attachment.
	*/
	if ( dwReason == DLL_PROCESS_DETACH ) {
		if ( __proc_attached > 0 )
			__proc_attached--;
		else
			/*
			* no prior process attach. just return failure.
			*/
			return FALSE;
	}
	if ( dwReason == DLL_PROCESS_ATTACH ) {
		BOOL result = _CRT_INIT (hDllHandle, dwReason, lpreserved);
		if (result)
			__proc_attached++;
		return result;
	} else {
		return _CRT_INIT (hDllHandle, dwReason, lpreserved);
	}
}


extern "C" BOOL WINAPI
DllMainEntry (HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
{
	BOOL retcode = TRUE;

	/*
	 * If this is a process detach notification, check that there has
	 * been a prior process attach notification.
	 */
	if ( (dwReason == DLL_PROCESS_DETACH) && (__proc_attached == 0) )
		return FALSE;

	if ( dwReason == DLL_PROCESS_ATTACH || dwReason == DLL_THREAD_ATTACH )
	{
		if ( _pRawDllMain )
			retcode = (*_pRawDllMain)(hDllHandle, dwReason, lpreserved);

	#if defined(CALL_RAW_DLL_INIT)
		if (dwReason == DLL_PROCESS_ATTACH && !RawDllInit (ctx))
			retcode = FALSE;
	#endif

		if ( retcode )
			retcode = _CRT_INIT_MY (hDllHandle, dwReason, lpreserved);

		if ( !retcode )
			return FALSE;
	}

	retcode = DllMain(hDllHandle, dwReason, lpreserved);


	if ( (dwReason == DLL_PROCESS_ATTACH) && !retcode )
		/*
		 * The user's DllMain routine returned failure, the C runtime
		 * needs to be cleaned up. Do this by calling _CRT_INIT again,
		 * this time imitating DLL_PROCESS_DETACH. Note this will also
		 * clear the __proc_attached flag so the cleanup will not be
		 * repeated upon receiving the real process detach notification.
		 */
		_CRT_INIT_MY (hDllHandle, DLL_PROCESS_DETACH, lpreserved);

	if ( (dwReason == DLL_PROCESS_DETACH) ||
		 (dwReason == DLL_THREAD_DETACH) )
	{
		if ( _CRT_INIT_MY (hDllHandle, dwReason, lpreserved) == FALSE )
			retcode = FALSE ;

	#if defined(CALL_RAW_DLL_TERM)
		if (dwReason == DLL_PROCESS_DETACH)
			RawDllTerm ();
	#endif

		if ( retcode && _pRawDllMain )
			retcode = (*_pRawDllMain)(hDllHandle, dwReason, lpreserved);
	}

	return retcode ;
}

#endif // IMPLEMENT_DLL_MAINENTRY

#endif // defined(WINDOWS)

// === Mac - MachO ======================================================================================================

#if defined macintosh

#include <mach-o/ldsyms.h>
#include <mach-o/dyld.h>
#include "MacUtils/GSCFXBundle.hpp"

#ifndef MAXPATH
#define MAXPATH 1024
#endif

#define DLLEXPORT
#define PRIVATEEXTERN

// --- Implementation ---------------------------------------------------------------------------------------------------

typedef struct DllMainImp_InitContext
{
	CFBundleRef		bundle;
} DllMainImp_InitContext;

static char 			gDllFileName [256] = {0};

PRIVATEEXTERN DllMainImp_LocationSpec		DllMainImp_GetLocation (const DllMainImp_InitContext* ctx);

static const char * GetBundlePath (const DllMainImp_InitContext* ctx)
{
	static char bundlePath [MAXPATH] = {0};
	static char emptyStr [2] = {0};

	GS::AutoCFTypeRef<CFURLRef> bundleURL (CFBundleCopyBundleURL (ctx->bundle));
	if (bundleURL.Get () == nullptr) {
		DBBREAK ();
		return emptyStr;
	}

	GS::AutoCFTypeRef<CFStringRef> autocfstring (CFURLCopyFileSystemPath (bundleURL.Get (), kCFURLPOSIXPathStyle));
	GS::AutoCFTypeRef<CFMutableStringRef> normalizedName (CFStringCreateMutableCopy (kCFAllocatorDefault, 0, autocfstring.Get ()));
	CFStringNormalize (normalizedName.Get (), kCFStringNormalizationFormC);

	if (normalizedName.Get () != nullptr && CFStringGetCString (normalizedName.Get (), bundlePath, sizeof (bundlePath), kCFStringEncodingUTF8)) {
		return bundlePath;
	}

	DBBREAK ();
	return emptyStr;

}	// GetBundlePath


PRIVATEEXTERN DllMainImp_LocationSpec	DllMainImp_GetLocation (const DllMainImp_InitContext* ctx)
{
	DllMainImp_LocationSpec result = {0};
	result.mFullPath = GetBundlePath (ctx);

	return result;
}

#if defined(__GNUC__)
		extern "C" int 					GSInitImage (void)	__attribute__ ((constructor));
		extern "C" PRIVATEEXTERN void 	GSTermImage (void)	__attribute__ ((destructor));
#else
	#error "Not implemented!"
#endif


extern GSROOT_DLL_EXPORT bool GSRoot_DelayInitImage (int (*initfunc) (void));

extern "C" int GSInitImage (void)
{
	if (GSRoot_DelayInitImage (GSInitImage)) {
		return 0;
	}

	DllMainImp_InitContext init_context = {0};

	#if defined(DLLMAINIMP_PLUGIN)
	CFBundleRef theBundle = GSCFXBundleCreateFromMachHeader (kCFAllocatorDefault, (mach_header*)(&_mh_bundle_header));
	#else
	CFBundleRef theBundle = GSCFXBundleCreateFromMachHeader (kCFAllocatorDefault, (mach_header*)(&_mh_dylib_header));
	#endif
	CFURLRef theURL = CFBundleCopyBundleURL (theBundle);
	if (theURL) {
		CFStringRef theString = CFURLCopyLastPathComponent (theURL);
		CFStringGetCString (theString, gDllFileName, sizeof(gDllFileName), kCFStringEncodingUTF8);
		CFRelease (theString);
		CFRelease (theURL);
	}
	#if defined (DEBUVERS)
	if (DBGetFlags (DBGeneral) & DBEnableLoadTrace) {
		DBPrintf ("\n++++++ Shared Library Started: %s\n", gDllFileName);
	}
	#endif

	if (theBundle != 0) {
		init_context.bundle = theBundle;
	}
	#if defined(CALL_RAW_DLL_INIT)
		DllInit (&init_context);
	#endif

	#if defined(CALL_DLL_INIT)
		DllInit (&init_context);
	#endif

	if (init_context.bundle)
		CFRelease (init_context.bundle);


	#if defined (DEBUVERS)
	if (DBGetFlags (DBGeneral) & DBEnableLoadTrace) {
		#if defined(DLLMAINIMP_PLUGIN)
		DBPrintf ("\n++++++ Shared Library Loaded: %s (PLUGIN)\n",gDllFileName);
		#else
		DBPrintf ("\n++++++ Shared Library Loaded: %s\n",gDllFileName);
		#endif
	}
	#endif

	return 0;
}

extern "C" PRIVATEEXTERN void GSTermImage (void)
{
	#if defined (DEBUVERS)
		if (DBGetFlags (DBGeneral) & DBEnableLoadTrace) {
			#if defined(DLLMAINIMP_PLUGIN)
			DBPRINTF ("\n++++++ Shared Library Unloaded: %s (PLUGIN)\n",gDllFileName);
			#else
			DBPRINTF ("\n++++++ Shared Library Unloaded: %s\n",gDllFileName);
			#endif
		}
	#endif

	#if defined(CALL_DLL_TERM)
		DllTerm ();
	#endif
}

#endif // macintosh

// === Linux ===========================================================================================================

#if defined (__linux__)

typedef struct DllMainImp_InitContext {
} DllMainImp_InitContext;


// --- Implementation --------------------------------------------------------------------------------------------------

int		GetSharedLibraryPath (char* sharedLibraryPath, size_t sharedLibraryPathSize)
{
	static int PlaceHolder;

	Dl_info dlInfo;
	if (::dladdr (&PlaceHolder, &dlInfo) == 0) {
		if (dlInfo.dli_fname != nullptr && dlInfo.dli_fname [0] != '\0') {
			size_t dli_fname_len = ::strlen (dlInfo.dli_fname);
			if (dli_fname_len < sharedLibraryPathSize) {
				::strcpy (sharedLibraryPath, dlInfo.dli_fname);
				return dli_fname_len;
			}
		}
	}

	return -1;
}


DllMainImp_LocationSpec	DllMainImp_GetLocation (const DllMainImp_InitContext* ctx)
{
	static char sharedLibraryPath [PATH_MAX];

	DllMainImp_LocationSpec result = { 0 };
	if (GetSharedLibraryPath (sharedLibraryPath, sizeof (sharedLibraryPath)) > 0) {
		result.mFullPath = sharedLibraryPath;
	}

	return result;
}


extern "C" int GSInitImage (void)	__attribute__ ((constructor));
extern "C" void GSTermImage (void) 	__attribute__ ((destructor));

extern "C" int	GSInitImage ()
{
#if defined (CALL_DLL_INIT) || defined (DEBUVERS)
	char imagePath [PATH_MAX];
	if (GetSharedLibraryPath (imagePath, sizeof (imagePath)) == -1) {
		imagePath [0] = '\0';
	}
#endif

#if defined (CALL_DLL_INIT)
	DllMainImp_InitContext init_context;
#endif

#if defined (DEBUVERS)
	if (DBGetFlags (DBGeneral) & DBEnableLoadTrace) {
		DBPrintf ("\n++++++ Shared Library Started: %s\n", imagePath);
	}
#endif

#if defined (CALL_DLL_INIT)
	DllInit (&init_context);
#endif

#if defined (DEBUVERS)
	if (DBGetFlags (DBGeneral) & DBEnableLoadTrace) {
		DBPrintf ("\n++++++ Shared Library Loaded: %s\n", imagePath);
	}
#endif

	return 0;
}


extern "C" void		GSTermImage ()
{
#if defined (DEBUVERS)
	char imagePath [PATH_MAX];
	if (GetSharedLibraryPath (imagePath, sizeof (imagePath)) == -1) {
		imagePath [0] = '\0';
	}

	if (DBGetFlags (DBGeneral) & DBEnableLoadTrace) {
		DBPRINTF ("\n++++++ Shared Library Unloaded: %s\n", imagePath);
	}
	#endif

#if defined (CALL_DLL_TERM)
	DllTerm ();
#endif
}

#endif // __linux__

#endif // DLL_MAIN_IMP_HPP
