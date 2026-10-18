#ifndef	GS_COMMONUI_COMMONALERTS_HPP
#define	GS_COMMONUI_COMMONALERTS_HPP


#include "UDDefinitions.hpp"


namespace UD {


UD_DLL_EXPORT void InvokeXMLWriteErrorAlert ();
UD_DLL_EXPORT void InvokeXMLReadInvalidFileErrorAlert ();
UD_DLL_EXPORT void InvokeXMLReadInvalidFileErrorAlert (UInt32 lineNumber);
UD_DLL_EXPORT void InvokeGeneralReadInvalidFileErrorAlert ();
UD_DLL_EXPORT void InvokeXMLReadSomeDataInvalidErrorAlert ();

UD_DLL_EXPORT void InvokeNameAlreadyExistsAlert ();
UD_DLL_EXPORT void InvokeNameIsNotValidAlert ();
UD_DLL_EXPORT void InvokeNameIsEmptyAlert ();
UD_DLL_EXPORT bool InvokeReplaceExistingFilesAlert (const IO::Location& folderLocation, const UInt32 existingFilesCount);


} // namespace UD


#endif