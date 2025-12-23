/****************************************************************************/
/*																			*/
/*				PLATFORM DEPENDENT FILEDEFREC SPECIFICATION					*/
/*																			*/
/****************************************************************************/

#ifndef	FILEDEF_H
#define	FILEDEF_H

#pragma once

#include	<stdlib.h>	/* for _MAX_PATH */

/* Length of entry names	*/
#define		FINAMELEN				32
#if defined (WINDOWS)
#define		FIPATHLEN				_MAX_PATH
#else
#define		FIPATHLEN				260
#endif


#endif
