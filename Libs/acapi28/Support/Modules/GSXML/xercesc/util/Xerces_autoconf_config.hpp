// *********************************************************************************************************************
// Description:		Xerces Autoconfiguration for MacOS, Windows 
//
// Module:			GSXML
// Namespace:		XERCES_C
// Contact person:	BGA
//
// *********************************************************************************************************************

#ifndef XERCESC_AUTOCONFIG_CONFIG_HPP
#define XERCESC_AUTOCONFIG_CONFIG_HPP

#if defined (macintosh)
	#include <xercesc/util/Xerces_autoconf_config_Mac_64.hpp>
#endif

#if defined (WINDOWS)
	#include <xercesc/util/Xerces_autoconf_config_Win_64.hpp>
#endif

#if defined (__linux__)
	#include <xercesc/util/Xerces_autoconf_config_Linux_64.hpp>
#endif

#endif
