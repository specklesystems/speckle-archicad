// *****************************************************************************
//
//                    Class ClassManager, dynamic typed New
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************

#ifndef CLASSMANAGER_HPP
#define CLASSMANAGER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "ClassInfo.hpp"
#include "FunctionRef.hpp"


// ============================ Class ClassManager =============================

namespace GS {

class GSROOT_DLL_EXPORT ClassManager {
private:
	ClassInfo::SystemVersion	outputVersion;	// output version of the system (application) used at object serialization

public:
		// Types

	class ClassInfoEnumerator;
	class VersionEnumerator;

		// Creation and Destructon

	ClassManager ();	// only one singleton instance can be created
   ~ClassManager ();

		// User interface

	void		Register	 (ClassInfo& classInfo);
	void		Unregister	 (ClassInfo& classInfo);
	bool		IsRegistered (const ClassInfo& classInfo) const;

	ClassInfo*	Find (const char* className) const;
	ClassInfo*	Find (ClassType classType) const;
	ClassInfo*	Find (const Guid& classId) const;
	ClassInfo*	Find (const ExportedClassName& exportedName) const;
	ClassInfo*	Find (const ClassInfo& currentClassInfo, ClassVersion maxVersion) const;

	bool		Contains (const char* className) const;
	bool		Contains (const Guid& classId) const;

	void		EnumerateClassInfos (GS::FunctionRef<void (const ClassInfo*)> processor) const;
	bool		EnumerateClassInfos (ClassInfoEnumerator& enumerator) const;

	void							SetOutputVersion (ClassInfo::SystemVersion outputVersion);
	ClassInfo::SystemVersion		GetOutputVersion (void) const;

	GSErrCode			WriteVersions	(OChannel& oc) const;
	static	GSErrCode	ReadVersions	(IChannel& ic, VersionEnumerator& versionEnumerator);
	GSErrCode			ReadOldVersions (IChannel& ic);

	Object*		CreateNewInstance	(const char* className) const;
	Object*		CreateNewInstance	(ClassType classType) const;
	Object*		CreateNewInstance	(const Guid& classId) const;
	Object*		CreateNewInstance	(const ExportedClassName& exportedName) const;

	void		PrintClassInfoTable (OChannel& output) const;

	GSErrCode	CheckInheritance	(void) const;

	// Types

	class GSROOT_DLL_EXPORT ClassInfoEnumerator {
	public:
		virtual ~ClassInfoEnumerator ();

		virtual bool	ClassInfoFound (const ClassInfo* /*classInfo*/) { return true; }
	};

	class GSROOT_DLL_EXPORT VersionEnumerator {
	public:
		virtual ~VersionEnumerator ();

		virtual void	ClassFound (const Guid& /*classId*/, ClassVersion /*version*/) {}
	};

	class GSROOT_DLL_EXPORT [[nodiscard]] OutputVersionBlock {
	private:
		ClassInfo::SystemVersion	previousOutputVersion;	// saves previous output version to be restored in destructor

	public:
		explicit OutputVersionBlock (ClassInfo::SystemVersion outputVersion);
		~OutputVersionBlock ();
	};

private:
	static GSErrCode	ReadVersions		 (IChannel& ic, VersionEnumerator* versionEnumerator);
	static GSErrCode	ReadVersionsVersion2 (IChannel& ic, VersionEnumerator* versionEnumerator);
};

extern GSROOT_DLL_EXPORT ClassManager	classManager;

}	// namespace GS


// ____________________________ Class ClassManager _____________________________


	/*
	 * The following New functions are intended for creating Objects based
	 * on class name, class type or class id similarly to C++ new operator.
	 * They simply invoke the appropriate ClassManager::CreateNewInstance method.
	 */

namespace GS {

GSROOT_DLL_EXPORT	Object*	New (const char* className);
GSROOT_DLL_EXPORT	Object*	New (ClassType classType);
GSROOT_DLL_EXPORT	Object*	New (const Guid& classId);
GSROOT_DLL_EXPORT	Object*	New (const ExportedClassName& exportedName);

}	// namespace GS

#endif
