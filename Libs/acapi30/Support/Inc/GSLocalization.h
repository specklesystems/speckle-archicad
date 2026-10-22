// *********************************************************************************************************************
// Description:		Resource constants for localization
//
// Module:			Control
// Namespace:		-
// Contact Preson:	FM
//
//
// *********************************************************************************************************************

#ifndef GSLOCALIZATION_H
#define GSLOCALIZATION_H

#if defined (ARA__APP)		/* Arabic				*/
	#define		VERSION_APPENDIX	"ARA"
	#define		MAC_VERSION_CODE	16
	#define		MAC_REGION_NAME		"ar"
	#define		WIN_LANGUAGE_ID		0x401
	#define		WIN_CHARSET_ID		1256
	#define		WIN_LANGCHARSET_STR	"040104E8"
#endif

#if defined (AUS__APP)		/* Australian English	*/
	#define		VERSION_APPENDIX	"AUS"
	#define		MAC_VERSION_CODE	15			/* Britain: 2, Australia: 15, Ireland: 50 */
	#define		MAC_REGION_NAME		"en_AU"
	#define		WIN_LANGUAGE_ID		0x409
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040904E4"
	#define 	GS_COUNTRY_CODE_NUM	1
	#define 	GS_COUNTRY_CODE_STR	"1"
#endif

#if defined (AUT__APP)		/* Austrian				*/
	#define		VERSION_APPENDIX	"AUT"
	#define		MAC_VERSION_CODE	3			/* Switz: 19	*/
	#define		MAC_REGION_NAME		"de_AT"
	#define		WIN_LANGUAGE_ID		0x407		/* Switz: 0x807	*/
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040704E4"
	#define 	GS_COUNTRY_CODE_NUM	2
	#define 	GS_COUNTRY_CODE_STR	"2"
#endif

#if	defined (BUL__APP)		/* Bulgarien			*/
	#define		VERSION_APPENDIX	"BUL"
	#define		MAC_VERSION_CODE	72
	#define		MAC_REGION_NAME		"bg_BG"
	#define		WIN_LANGUAGE_ID		0x402
	#define		WIN_CHARSET_ID		1251
	#define		WIN_LANGCHARSET_STR	"040204E3"
#endif

#if defined (CHE__APP)		/* Swiss German				*/
	#define		VERSION_APPENDIX	"CHE"
	#define		MAC_VERSION_CODE	19			/* Switz: 19	*/
	#define		MAC_REGION_NAME		"de_CH"
	#define		WIN_LANGUAGE_ID		0x807		/* Switz: 0x807	*/
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"080704E4"
	#define 	GS_COUNTRY_CODE_NUM	3
	#define 	GS_COUNTRY_CODE_STR	"3"
#endif

#if defined (CHI__APP)		/* Simplified Chineese	*/
	#define		VERSION_APPENDIX	"CHI"
	#define		MAC_VERSION_CODE	52
	#define		MAC_REGION_NAME		"zh_CN"
	#define		WIN_LANGUAGE_ID		0x804
	#define		WIN_CHARSET_ID		936
	#define		WIN_LANGCHARSET_STR	"080403a8"
	#define 	GS_COUNTRY_CODE_NUM	4
	#define 	GS_COUNTRY_CODE_STR	"4"
#endif

#if defined (CRO__APP)		/* Croatian				*/
	#define		VERSION_APPENDIX	"CRO"
	#define		MAC_VERSION_CODE	68
	#define		MAC_REGION_NAME		"hr_HR"
	#define		WIN_LANGUAGE_ID		0x41A, 1250
	#define		WIN_CHARSET_ID		1250
	#define		WIN_LANGCHARSET_STR	"041A04E2"
#endif

#if defined (CZE__APP)		/* Czech				*/
	#define		VERSION_APPENDIX	"CZE"
	#define		MAC_VERSION_CODE	56
	#define		MAC_REGION_NAME		"cs_CZ"
	#define		WIN_LANGUAGE_ID		0x405
	#define		WIN_CHARSET_ID		1250
	#define		WIN_LANGCHARSET_STR	"040504E2"
	#define 	GS_COUNTRY_CODE_NUM	5
	#define 	GS_COUNTRY_CODE_STR	"5"
#endif

#if defined (DEN__APP)		/* Danish				*/
	#define		VERSION_APPENDIX	"DEN"
	#define		MAC_VERSION_CODE	9
	#define		MAC_REGION_NAME		"da_DK"
	#define		WIN_LANGUAGE_ID		0x406
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040604E4"
	#define 	GS_COUNTRY_CODE_NUM	29
	#define 	GS_COUNTRY_CODE_STR	"29"
#endif

#if defined (EST__APP)		/* Estonian			*/
	#define		VERSION_APPENDIX	"EST"
	#define		MAC_VERSION_CODE	44
	#define		MAC_REGION_NAME		"et_EE"
	#define		WIN_LANGUAGE_ID		0x425
	#define		WIN_CHARSET_ID		1257
	#define		WIN_LANGCHARSET_STR	"042504E9"
	#define 	GS_COUNTRY_CODE_NUM	7
	#define 	GS_COUNTRY_CODE_STR	"7"
#endif

#if defined (FIN__APP)		/* Finnish				*/
	#define		VERSION_APPENDIX	"FIN"
	#define		MAC_VERSION_CODE	17
	#define		MAC_REGION_NAME		"fi_FI"
	#define		WIN_LANGUAGE_ID		0x40B
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040B04E4"
	#define 	GS_COUNTRY_CODE_NUM	8
	#define 	GS_COUNTRY_CODE_STR	"8"
#endif

#if defined (FRA__APP)		/* French				*/
	#define		VERSION_APPENDIX	"FRA"
	#define		MAC_VERSION_CODE	1			/* BeLux: 6, 		Switz.: 18,		Canada: 11		*/
	#define		MAC_REGION_NAME		"fr_FR"
	#define		WIN_LANGUAGE_ID		0x40C		/* BeLux: 0x80C,	Switz.: 0x100C,	Canada: 0xC0C	*/
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040C04E4"
	#define 	GS_COUNTRY_CODE_NUM	9
	#define 	GS_COUNTRY_CODE_STR	"9"
#endif

#if defined (GER__APP)		/* German				*/
	#define		VERSION_APPENDIX	"GER"
	#define		MAC_VERSION_CODE	3			/* Switz: 19	*/
	#define		MAC_REGION_NAME		"de_DE"
	#define		WIN_LANGUAGE_ID		0x407		/* Switz: 0x807	*/
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040704E4"
	#define 	GS_COUNTRY_CODE_NUM	10
	#define 	GS_COUNTRY_CODE_STR	"10"
#endif

#if defined (GRE__APP)		/* Greek				*/
	#define		VERSION_APPENDIX	"GRE"
	#define		MAC_VERSION_CODE	20
	#define		MAC_REGION_NAME		"el_GR"
	#define		WIN_LANGUAGE_ID		0x408
	#define		WIN_CHARSET_ID		1253
	#define		WIN_LANGCHARSET_STR	"040804E5"
	#define 	GS_COUNTRY_CODE_NUM	11
	#define 	GS_COUNTRY_CODE_STR	"11"
#endif

#if defined (HUN__APP)		/* Hungarian			*/
	#define		VERSION_APPENDIX	"HUN"
	#define		MAC_VERSION_CODE	43
	#define		MAC_REGION_NAME		"hu_HU"
	#define		WIN_LANGUAGE_ID		0x40E
	#define		WIN_CHARSET_ID		1250
	#define		WIN_LANGCHARSET_STR	"040E04E2"
	#define 	GS_COUNTRY_CODE_NUM	12
	#define 	GS_COUNTRY_CODE_STR	"12"
#endif

#if defined (ICE__APP)		/* Icelandian			*/
	#define		VERSION_APPENDIX	"ICE"
	#define		MAC_VERSION_CODE	21
	#define		MAC_REGION_NAME		"is_IS"
	#define		WIN_LANGUAGE_ID		0x40F
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040F04E4"
#endif

#if defined (ITA__APP)		/* Italian				*/
	#define		VERSION_APPENDIX	"ITA"
	#define		MAC_VERSION_CODE	4			/* Switz: 36	*/
	#define		MAC_REGION_NAME		"it_IT"
	#define		WIN_LANGUAGE_ID		0x410		/* Switz: 0x810	*/
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"041004E4"
	#define 	GS_COUNTRY_CODE_NUM	13
	#define 	GS_COUNTRY_CODE_STR	"13"
#endif

#if defined (INT__APP)		/* International English	*/
	#define		VERSION_APPENDIX	"INT"
	#define		MAC_VERSION_CODE	37			/* Britain: 2, Australia: 15, Ireland: 50 */
	#define		MAC_REGION_NAME		"English"
	#define		WIN_LANGUAGE_ID		0x409
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040904E4"
	#define 	GS_COUNTRY_CODE_NUM	30
	#define 	GS_COUNTRY_CODE_STR	"30"
#endif

#if defined (ISR__APP)		/* Israeli				*/
	#define		VERSION_APPENDIX	"ISR"
	#define		MAC_VERSION_CODE	13
	#define		MAC_REGION_NAME		"he_IL"
	#define		WIN_LANGUAGE_ID		0x40D
	#define		WIN_CHARSET_ID		1255
	#define		WIN_LANGCHARSET_STR	"040D04E7"
#endif

#if defined (JPN__APP)		/* Japaneese			*/
	#define		VERSION_APPENDIX	"JPN"
	#define		MAC_VERSION_CODE	14
	#define		MAC_REGION_NAME		"ja_JP"
	#define		WIN_LANGUAGE_ID		0x411
	#define		WIN_CHARSET_ID		932
	#define		WIN_LANGCHARSET_STR	"041103A4"
	#define 	GS_COUNTRY_CODE_NUM	14
	#define 	GS_COUNTRY_CODE_STR	"14"
#endif

#if defined (KOR__APP)		/* Korean				*/
	#define		VERSION_APPENDIX	"KOR"
	#define		MAC_VERSION_CODE	51
	#define		MAC_REGION_NAME		"ko_KR"
	#define		WIN_LANGUAGE_ID		0x412
	#define		WIN_CHARSET_ID		949
	#define		WIN_LANGCHARSET_STR	"041203B5"
	#define 	GS_COUNTRY_CODE_NUM	15
	#define 	GS_COUNTRY_CODE_STR	"15"
#endif

#if defined (NED__APP)		/* Dutch				*/
	#define		VERSION_APPENDIX	"NED"
	#define		MAC_VERSION_CODE	5
	#define		MAC_REGION_NAME		"nl_NL"
	#define		WIN_LANGUAGE_ID		0x0413		/* Belg. Dutch: 0x813 */
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"041304E4"
	#define 	GS_COUNTRY_CODE_NUM	16
	#define 	GS_COUNTRY_CODE_STR	"16"
#endif

#if defined (NZE__APP)		/* New Zealand English	*/
	#define		VERSION_APPENDIX	"NZE"
	#define		MAC_VERSION_CODE	15			/* Britain: 2, Australia: 15, Ireland: 50 */
	#define		MAC_REGION_NAME		"en_NZ"
	#define		WIN_LANGUAGE_ID		0x409
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040904E4"
	#define 	GS_COUNTRY_CODE_NUM	17
	#define 	GS_COUNTRY_CODE_STR	"17"
#endif

#if defined (NOR__APP)		/* Norwegian			*/
	#define		VERSION_APPENDIX	"NOR"
	#define		MAC_VERSION_CODE	12
	#define		MAC_REGION_NAME		"no_NO"
	#define		WIN_LANGUAGE_ID		0x414		/* Nynorsk : 0x814 */
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"041404E4"
	#define 	GS_COUNTRY_CODE_NUM	18
	#define 	GS_COUNTRY_CODE_STR	"18"
#endif

#if defined (POL__APP)		/* Polish				*/
	#define		VERSION_APPENDIX	"POL"
	#define		MAC_VERSION_CODE	42
	#define		MAC_REGION_NAME		"pl_PL"
	#define		WIN_LANGUAGE_ID		0x415
	#define		WIN_CHARSET_ID		1250
	#define		WIN_LANGCHARSET_STR	"041504E2"
	#define 	GS_COUNTRY_CODE_NUM	19
	#define 	GS_COUNTRY_CODE_STR	"19"
#endif

#if defined (POR__APP)		/* Portugeese			*/
	#define		VERSION_APPENDIX	"POR"
	#define		MAC_VERSION_CODE	10
	#define		MAC_REGION_NAME		"pt_PT"
	#define		WIN_LANGUAGE_ID		0x816		/* Brasil: 0x416	*/
	#define		WIN_CHARSET_ID		1252
	#define 	WIN_LANGCHARSET_STR	"081604E4"
	#define 	GS_COUNTRY_CODE_NUM	20
	#define 	GS_COUNTRY_CODE_STR	"20"
#endif

#if defined (ENG__APP)		/* British English	*/
	#define		VERSION_APPENDIX	"ENG"
	#define		MAC_VERSION_CODE	2			/* Britain: 2, Australia: 15, Ireland: 50 */
	#define		MAC_REGION_NAME		"en_GB"
	#define		WIN_LANGUAGE_ID		0x409
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040904E4"
	#define 	GS_COUNTRY_CODE_NUM	6
	#define 	GS_COUNTRY_CODE_STR	"6"
#endif

#if defined (ROM__APP)		/* Romanian				*/
	#define		VERSION_APPENDIX	"ROM"
	#define		MAC_VERSION_CODE	39
	#define		MAC_REGION_NAME		"ro_RO"
	#define		WIN_LANGUAGE_ID		0x418
	#define		WIN_CHARSET_ID		1250
	#define		WIN_LANGCHARSET_STR	"041804E2"
	#define 	GS_COUNTRY_CODE_NUM	21
	#define 	GS_COUNTRY_CODE_STR	"21"
#endif

#if defined (RUS__APP)		/* Russian				*/
	#define		VERSION_APPENDIX	"RUS"
	#define		MAC_VERSION_CODE	49
	#define		MAC_REGION_NAME		"ru_RU"
	#define		WIN_LANGUAGE_ID		0x419
	#define		WIN_CHARSET_ID		1251
	#define		WIN_LANGCHARSET_STR	"041904E3"
	#define 	GS_COUNTRY_CODE_NUM	22
	#define 	GS_COUNTRY_CODE_STR	"22"
#endif

#if defined (SLO__APP)		/* Slovak				*/
	#define		VERSION_APPENDIX	"SLO"
	#define		MAC_VERSION_CODE	57
	#define		MAC_REGION_NAME		"sk_SK"
	#define		WIN_LANGUAGE_ID		0x041B
	#define		WIN_CHARSET_ID		1250
	#define		WIN_LANGCHARSET_STR	"040304E2"
	#define 	GS_COUNTRY_CODE_NUM	32
	#define 	GS_COUNTRY_CODE_STR	"32"
#endif

#if defined (SPA__APP)		/* Spanish				*/
	#define		VERSION_APPENDIX	"SPA"
	#define		MAC_VERSION_CODE	8
	#define		MAC_REGION_NAME		"es_ES"
	#define		WIN_LANGUAGE_ID		0x40A		/* Mexico: 0x80A	*/
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040A04E4"
	#define 	GS_COUNTRY_CODE_NUM	24
	#define 	GS_COUNTRY_CODE_STR	"24"
#endif

#if defined (SWE__APP)		/* Swedish				*/
	#define		VERSION_APPENDIX	"SWE"
	#define		MAC_VERSION_CODE	7
	#define		MAC_REGION_NAME		"sv_SE"
	#define		WIN_LANGUAGE_ID		0x41D
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"041D04E4"
	#define 	GS_COUNTRY_CODE_NUM	25
	#define 	GS_COUNTRY_CODE_STR	"25"
#endif

#if defined (TAI__APP)		/* Traditional Chineese	*/
	#define		VERSION_APPENDIX	"TAI"
	#define		MAC_VERSION_CODE	53
	#define		MAC_REGION_NAME		"zh_TW"
	#define		WIN_LANGUAGE_ID		0x404
	#define		WIN_CHARSET_ID		950
	#define		WIN_LANGCHARSET_STR	"040403b6"
	#define 	GS_COUNTRY_CODE_NUM	26
	#define 	GS_COUNTRY_CODE_STR	"26"
#endif

#if defined (TUR__APP)		/* Turkish				*/
	#define		VERSION_APPENDIX	"TUR"
	#define		MAC_VERSION_CODE	24
	#define		MAC_REGION_NAME		"tr_TR"
	#define		WIN_LANGUAGE_ID		0x41F
	#define		WIN_CHARSET_ID		1254
	#define		WIN_LANGCHARSET_STR	"041F04E6"
	#define 	GS_COUNTRY_CODE_NUM	27
	#define 	GS_COUNTRY_CODE_STR	"27"
#endif

#if defined (USA__APP)		/* USA English			*/
	#define		VERSION_APPENDIX	"USA"
	#define		MAC_VERSION_CODE	0
	#define		MAC_REGION_NAME		"en_US"
	#define		WIN_LANGUAGE_ID		0x409
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040904E4"
	#define 	GS_COUNTRY_CODE_NUM	28
	#define 	GS_COUNTRY_CODE_STR	"28"
#endif

#if defined (IND__APP)		/* IND Indic			*/
	#define		VERSION_APPENDIX	"IND"
	#define		MAC_VERSION_CODE	0
	#define		MAC_REGION_NAME		"en_IN"
	#define		WIN_LANGUAGE_ID		0x409
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040904E4"
	#define 	GS_COUNTRY_CODE_NUM	33
	#define 	GS_COUNTRY_CODE_STR	"33"
#endif

#if defined (BRA__APP)		/* Brasil				*/
	#define		VERSION_APPENDIX	"BRA"
	#define		MAC_VERSION_CODE	71
	#define		MAC_REGION_NAME		"pt_BR"
	#define		WIN_LANGUAGE_ID		0x416
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"041604E4"
	#define 	GS_COUNTRY_CODE_NUM	34
	#define 	GS_COUNTRY_CODE_STR	"34"
#endif

#if defined (UKI__APP)		/* United Kingdom & Ireland */
	#define		VERSION_APPENDIX	"UKI"
	#define		MAC_VERSION_CODE	37
	#define		MAC_REGION_NAME		"English"
	#define		WIN_LANGUAGE_ID		0x409
	#define		WIN_CHARSET_ID		1252
	#define		WIN_LANGCHARSET_STR	"040904E4"
	#define 	GS_COUNTRY_CODE_NUM	35
	#define 	GS_COUNTRY_CODE_STR	"35"
#endif

#if defined (IRN__APP)		/* Iran */
	#define		VERSION_APPENDIX	"IRN"
	#define		MAC_VERSION_CODE	48
	#define		MAC_REGION_NAME		"fa_IR"
	#define		WIN_LANGUAGE_ID		0x429
	#define		WIN_CHARSET_ID		1256
	#define		WIN_LANGCHARSET_STR	"042904E8"
	#define 	GS_COUNTRY_CODE_NUM	36
	#define 	GS_COUNTRY_CODE_STR	"36"
#endif

#if defined (UKR__APP)		/* Ukraine */
	#define		VERSION_APPENDIX	"UKR"
	#define		MAC_VERSION_CODE	50
	#define		MAC_REGION_NAME		"uk_UA"
	#define		WIN_LANGUAGE_ID		0x422
	#define		WIN_CHARSET_ID		1251
	#define		WIN_LANGCHARSET_STR	"042204E3"
	#define 	GS_COUNTRY_CODE_NUM	37
	#define 	GS_COUNTRY_CODE_STR	"37"
#endif

#if !defined (VERSION_APPENDIX)
	ERROR: Missing Country Specification !!!
#endif

#endif
