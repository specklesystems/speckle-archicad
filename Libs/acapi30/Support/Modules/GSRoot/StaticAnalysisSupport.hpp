// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_STATICANALYSISSUPPORT_HPP
#define GS_STATICANALYSISSUPPORT_HPP


#ifdef _WIN64

#include <sal.h>

#else

#ifdef __clang_analyzer__
	#define _Analysis_assume_(expr) [[assume(static_cast<bool> (expr))]]
#else
	#define _Analysis_assume_(expr)
#endif

// === Function parameter and return value annotations =========================

#define _In_			[[gnu::nonnull]]
#define _Out_
#define _Inout_
#define _In_z_			[[gnu::nonnull]]

#define _Out_writes_(n)

#define _Ret_notnull_	[[gnu::returns_nonnull]]

#define _Post_satisfies_(expr)


// === Class and struct annotations ============================================

#endif


#endif /* GS_STATICANALYSISSUPPORT_HPP */
