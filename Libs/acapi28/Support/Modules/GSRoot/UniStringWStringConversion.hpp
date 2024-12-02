/*********************************************************************/
//
//	! Assumes UCS2 encoding on Windows, UTF-32 on other platforms !
//
/*********************************************************************/

#ifndef UNISTRING_WSTRING_CONVERSION_HPP
#define UNISTRING_WSTRING_CONVERSION_HPP
#pragma once


#include "GSRootExport.hpp"
#include "UniString.hpp"
#include <string>


namespace GS {

GSROOT_DLL_EXPORT GS::UniString	ToUniString (const std::wstring&  str);
GSROOT_DLL_EXPORT std::wstring	ToWString	(const GS::UniString& str);

}

#endif
