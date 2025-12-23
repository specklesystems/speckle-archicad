/****************************************************************************/
/*																			*/
/*					 VARIABLES AND PROTOTYPES FOR DB... ROUTINES				*/
/*																			*/
/****************************************************************************/

#ifndef	_DB_H_
#define	_DB_H_

#pragma once

#ifndef	GSUTILSPRIVEXP_H
	#include	"GSUtilsPrivExp.h"
#endif

#ifdef	_DB_TRANSL_
	#define	ext	GSUTILS_PRIVATE_EXPORT
#else
	#if defined (macintosh)
		#define	ext	extern
	#endif
	#if defined (WINDOWS)
		#define	ext	extern GSUTILS_PRIVATE_EXPORT
	#endif
#endif

#ifdef CHECKED_VERSION

	#define	DBINIT			DBInit()
	#define	DBSTR(s)		DBStr(s)
	#define	DBINT(s, n)		DBInt((s), (n))
	#define	DBHEX(s, n)		DBHex((s), (n))
	#define	DBREAL(s, n)	DBReal((s), (n))
	#define	DBTXT(s, t)		DBTxt((s), (t))
	#define	DBRESET			DBReset()
	#define	DBINTIF(b,s,n)	if (b)  DBInt ((s), (n))

	#define DB0(i, f)		if (debuInt == (i)) DBSTR(f)
	#define DB1(i, f, v1)	if (debuInt == (i)) { sprintf (debuLine, f, v1); DBSTR(debuLine); }
	#define DB2(i, f, v1, v2)	\
							if (debuInt == (i)) { sprintf (debuLine, f, v1, v2); DBSTR(debuLine); }
	#define DB3(i, f, v1, v2, v3)	\
							if (debuInt == (i)) { sprintf (debuLine, f, v1, v2, v3); DBSTR(debuLine); }
	#define DB4(i, f, v1, v2, v3, v4)	\
							if (debuInt == (i)) { sprintf (debuLine, f, v1, v2, v3, v4); DBSTR(debuLine); }
	#define DB5(i, f, v1, v2, v3, v4, v5)	\
							if (debuInt == (i)) { sprintf (debuLine, f, v1, v2, v3, v4, v5); DBSTR(debuLine); }

#else

	#define	DBINIT
	#define	DBSTR(s)
	#define	DBINT(s, n)
	#define	DBHEX(s, n)
	#define	DBREAL(s, n)
	#define	DBTXT(s, t)
	#define	DBRESET
	#define	DBINTIF(b,s,n)

	#define DB0(i, f)
	#define DB1(i, f, v1)
	#define DB2(i, f, v1, v2)
	#define DB3(i, f, v1, v2, v3)
	#define DB4(i, f, v1, v2, v3, v4)
	#define DB5(i, f, v1, v2, v3, v4, v5)

#endif

#ifdef CHECKED_VERSION
	#define	DBTIME(s)		DBTime(s)
#else
	#define	DBTIME(s)
#endif



/*================================	 VARIABLES	============================*/

#ifdef CHECKED_VERSION
		ext	Int32	debuInt;
		ext	char	*debuLine;
#endif	/* DEBUVERS */

#undef	ext

/*================================	PROTOTYPES	============================*/

GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBInitVars (void);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBExitVars (void);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBSetDebuInt (short di);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBStr (const char *str);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBInt (const char *str, Int32 num);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBHex (const char *str, short num);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBHex (const char *str, Int32 num);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBHex (const char *str, Int64 num);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBReal (const char *str, double num);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBTxt (const char *str, const char *txt);

GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBReset (void);
GSUTILS_PRIVATE_EXPORT
void	GSU_PRIV		DBTime (const char *str);

#endif
