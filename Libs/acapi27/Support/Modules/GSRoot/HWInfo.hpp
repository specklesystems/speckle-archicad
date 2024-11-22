// **************************************************************************************
// Description:		Hardware related informations
//
// Namespaces:		HW
// Contact persons:	MM
//
// [SG compatible]
// **************************************************************************************

#ifndef HWINFO_HPP
#define HWINFO_HPP

#pragma once

#define CPU_TYPE_STR_LENGTH 0x40
#define VOLUME_NAME_SIZE 256
#define FILESYS_TYPE_SIZE 56
#define HW_RELATED_UNIQ_ID_SIZE 128

// --- Includes	-------------------------------------------------------------------------

//from GSRoot
#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "Array.hpp"
#include "CPUType.hpp"

// --- HardwareInfo namespace -----------------------------------------------------------

namespace HW {


// --- Predeclarations ------------------------------------------------------------------

class HardwareInfoImpl;


// --- HardwareInfo class --------------------------------------------------------------

class GSROOT_DLL_EXPORT HardwareInfo {
public:
	struct VolumeInfoStructure
	{
		char	VolumeName[VOLUME_NAME_SIZE];
		char	FileSystemType[FILESYS_TYPE_SIZE];
		UInt64			FreeBytes;
		UInt64			TotalBytes;
	};

	enum PowerState {
		BatteryHigh,
		BatteryLow,
		BatteryCritical,
		Charging,
		NoBattery,
		PowerStateUnknown
	};

friend class HardwareInfoImpl;

private:
	HardwareInfoImpl* impl;

private:
	static GSErrCode	GetNetworkInterfaceAddressBasedClientId		(GS::Guid& guid);
	static GSErrCode	GetDiskSerialNumberBasedClientId			(GS::Guid& guid);
	static GS::Guid		GetHWRelatedGuidLegacy						();
	
	HardwareInfoImpl*	GetHardwareInfoImplInstance					(void);

public:
	HardwareInfo ();
	~HardwareInfo();

	virtual GSErrCode	GetPhysicalRAMSize		(UInt64& physicalRamSize);
	virtual GSErrCode	GetPageFileSize			(UInt64& pageFileSize);
	virtual GSErrCode	GetProcessorTypeString	(char* result, USize resultSize);
	virtual UInt32		GetNumberOfVolumes		(void);
	virtual GSErrCode   GetVolumeInformations	(UIndex volumeIndex, VolumeInfoStructure* volumeInfo);
	virtual PowerState	GetPowerState			(void);
	virtual bool		IsBatteryPowered		(void);
#if defined macintosh
	virtual void		AdjustAppNap			(bool disableAppNapIfPowerCableConnected);
#endif

	GS::CPUType			GetSystemCPUType (void);
	GS::CPUType			GetProgramCPUType (void);

	GS::Guid			GetHWRelatedUniqIdLegacy (void); // It is based on the "main" volume ID, on Mac it is not reliable
	GS::Guid			GetHWRelatedUniqId		(void);
};

} // namespace HW

#endif
