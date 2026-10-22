#ifndef GSUTILS_FILEVERSIONINFO
#define GSUTILS_FILEVERSIONINFO

#pragma once

// from GSUtils
#include "GSUtilsExport.h"

namespace GS { class UniString; }
namespace IO { class Location; }

namespace FileVersionInfo {

/**
* @brief Retrieves the version of the file located at the given location.
* @param fileLocation The location of the file whose version is to be retrieved.
* @return The version string of the file. Version string format: "Major.Minor.Patch".
* @since Archicad 30
*/
GSUTILS_DLL_EXPORT_CPP
GS::UniString GetVersionString (const IO::Location& fileLocation);


/**
* @brief Tells if the given module file marked as auto-updatable.
* @param fileLocation The location of the file.
* @return Returns `true` if the module file is marked as auto-updatable in the Version resource.
* @since Archicad 30
*/
GSUTILS_DLL_EXPORT_CPP
bool	GetAutoUpdateFlag (const IO::Location& fileLocation);

}

#endif