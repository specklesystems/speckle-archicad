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

// --- Includes	-------------------------------------------------------------------------

//from GSRoot
#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "Array.hpp"
#include "CPUType.hpp"

inline constexpr UInt32 CPU_TYPE_STR_LENGTH		= 0x40;
inline constexpr UInt32 CPU_IDS_STR_LENGTH		= 0x40;
inline constexpr UInt32 VOLUME_NAME_SIZE		= 256;
inline constexpr UInt32 MOUNT_POINT_SIZE		= 256;
inline constexpr UInt32 FILESYS_TYPE_SIZE		= 56;
inline constexpr UInt32 HW_RELATED_UNIQ_ID_SIZE	= 128;

// --- HardwareInfo namespace -----------------------------------------------------------

namespace HW {


// --- Predeclarations ------------------------------------------------------------------

class HardwareInfoImpl;


// --- HardwareInfo class --------------------------------------------------------------

class GSROOT_DLL_EXPORT HardwareInfo {
public:
	struct VolumeInfoStructure
	{
		char	volumeName[VOLUME_NAME_SIZE];
		char	mountPoint[MOUNT_POINT_SIZE];
		char	fileSystemType[FILESYS_TYPE_SIZE];
		UInt64	freeBytes;
		UInt64	totalBytes;
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

	virtual GSErrCode	GetPhysicalRAMSize				(UInt64& physicalRamSize);
	virtual GSErrCode	GetPageFileSize					(UInt64& pageFileSize);
	virtual GSErrCode	GetProcessorTypeStringLegacy	(char* result, USize resultSize);
	virtual GSErrCode	GetCPUIDString 					(GS::UniString& result);
	virtual GSErrCode	GetCPUFamily 					(GS::UniString& result);
	virtual GSErrCode	GetCPUModel 					(GS::UniString& result);
	virtual GSErrCode	GetCPUStepping 					(GS::UniString& result);
	virtual GSErrCode	GetCPUMicrocodeVersion				(GS::UniString& result);
	virtual UInt32		GetNumberOfVolumes				(void);
	virtual GSErrCode   GetVolumeInfo					(UIndex volumeIndex, VolumeInfoStructure* volumeInfo);
	virtual PowerState	GetPowerState					(void);
	virtual bool		IsBatteryPowered				(void);
#if defined macintosh
	virtual void		AdjustAppNap					(bool disableAppNapIfPowerCableConnected);
#endif

	GS::CPUType			GetSystemCPUType (void);
	GS::CPUType			GetProgramCPUType (void);


	GS::Guid			GetHWRelatedUniqIdLegacy (void); // It is based on the "main" volume ID, on Mac it is not reliable
	GS::Guid			GetHWRelatedUniqId		(void);
};

} // namespace HW

#endif
