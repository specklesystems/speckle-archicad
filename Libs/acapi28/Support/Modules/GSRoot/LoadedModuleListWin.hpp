// *********************************************************************************************************************
// Description:		Loaded module list
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	EP
//
// SG compatible
// *********************************************************************************************************************

#ifndef LOADEDMODULELISTWIN_HPP
#define LOADEDMODULELISTWIN_HPP

// --------------------------------- Includes ----------------------------------

#include "Array.hpp"
#include "Definitions.hpp"
#include "Win32Interface.hpp"

#include "LoadedModuleListDefs.hpp"

#include <shared_mutex>

// ---------------------------------------------------------------------------------------------------------------------
// IgnoredCRTBlockAllocatedArray class
// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
class IgnoredCRTBlockAllocatedArray : public GS::Array<T> {
protected:
	virtual T*		AllocateNewBuffer	 (USize bufferCapacity, const T* oldBuffer) override;
	virtual void	DeleteBuffer		 (T* buffer) override;
};


// ---------------------------------------------------------------------------------------------------------------------
// LoadedModuleList class
// ---------------------------------------------------------------------------------------------------------------------

// List of currently loaded modules, ordered by loadAddress
class LoadedModuleList {
public:
	typedef Int32  Size;
	typedef Size   Index;

	static const Index							NotFoundIndex;
	static const LoadedModuleListDefs::ModuleID	InvalidModuleID = 0;

	struct ModuleData {
		GS::IntPtr						lowAddress;
		GS::IntPtr						highAddress;
		LoadedModuleListDefs::ModuleID	ID;
		WCHAR*							moduleName;
	};

	struct ModuleDataCache {
		ModuleData cache1 = {};
		ModuleData cache2 = {};
	};

private:
	static const Size InitialCapacity = 512;
	static HANDLE currentProcess;

	mutable std::shared_mutex criticalSection;

	IgnoredCRTBlockAllocatedArray<ModuleData> array;	// Sorted by low address for fast lookup

	LoadedModuleList (void);

	Index	GetImp (LoadedModuleListDefs::ModuleID id) const;	// not synchronized
	Index	GetImp (const void* address) const;					// not synchronized

	void	PopulateWithSystemModules (void);	// not synchronized
	void	Clear (void);						// not synchronized
	void	Sort (void);						// not synchronized

public:
	static LoadedModuleList&				Instance (void);
	static LoadedModuleListDefs::ModuleID	GenerateModuleId (const WCHAR* moduleName, UInt32 pathLength);
	
	~LoadedModuleList ();

	void							InsertModule (const void* loadAddress);
	void							RemoveModule (const WCHAR* modulePath);
	Index							Get (LoadedModuleListDefs::ModuleID id) const;
	Index							Get (const void* address) const;
	LoadedModuleListDefs::ModuleID	GetModuleID (const void* address, ModuleDataCache* cache = nullptr) const;
	bool							Contains (const void* address) const;
	bool							Contains (LoadedModuleListDefs::ModuleID id) const;
	void*							RVAToVA (const LoadedModuleListDefs::RVAOrVA& rva) const;	// The module has to be loaded!
};

#endif	// #ifndef LOADEDMODULELISTWIN_HPP