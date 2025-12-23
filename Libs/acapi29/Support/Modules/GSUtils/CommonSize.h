/****************************************************************************/
/*																			*/
/*							COMMON SIZE CONSTANTS							*/
/*																			*/
/****************************************************************************/

#ifndef _CommonSize_H_
#define _CommonSize_H_

#pragma once

/*================================ CONSTANTS ============================*/

#define MAXLIN      256 // Maximal length of a line
						// Every common string and local string variables must fit into this length.
						// Otherwise use own constant !!!

#define MAXNAMUTF8	128 // Limit for length of any (file)name. Increased for UTF8.
#define MAXNAM		32 // Limit for length of any (file)name

#define MAXLONGNAME	256 // Limit for length of any long (file)name
#define MAXURL		1024 // Limit for length of Unified Resource Locator

#define MAXDBCODEUTF8	128 // Max. length of codes used in list database
#define MAXDBCODE		32 // Max. length of codes used in list database

#define MAXCOMPNAME 128 // Max. length of component name
#define MAXKEYNAME  128 // Max. length of key name
#define MAXDESCNAME 256 // Max. length of descriptor name


#endif
