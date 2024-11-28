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
	#if defined (GS_64BIT)
		#include	<xercesc/util/Xerces_autoconf_config_Mac_64.hpp>
	#else
		#include	<xercesc/util/Xerces_autoconf_config_Mac_32.hpp>
	#endif
#endif

#if defined (WINDOWS)
	#if defined (GS_64BIT)
		#include	<xercesc/util/Xerces_autoconf_config_Win_64.hpp>
	#else
		#include	<xercesc/util/Xerces_autoconf_config_Win_32.hpp>
	#endif
#endif

#if defined (__linux__)
	#if defined (GS_64BIT)
		#include	<xercesc/util/Xerces_autoconf_config_Linux_64.hpp>
	#else
		#include	<xercesc/util/Xerces_autoconf_config_Linux_32.hpp>
	#endif
#endif

#endif
