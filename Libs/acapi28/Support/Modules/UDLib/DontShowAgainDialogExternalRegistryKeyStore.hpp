#ifndef GS_UD_DONTSHOWAGAINDIALOGEXTERNALREGISTRYKEYSTORE_HPP
#define GS_UD_DONTSHOWAGAINDIALOGEXTERNALREGISTRYKEYSTORE_HPP

#include "DGDialog.hpp"
#include "UDDefinitions.hpp"


namespace UD {
namespace DontShowAgainDialogUtils {

UD_DLL_EXPORT void RegisterExternalRegistryKey (const GS::UniString& registryValueName);

UD_DLL_EXPORT void UnregisterExternalRegistryKey (const GS::UniString& registryValueName);

UD_DLL_EXPORT void SetExternalRegistryKeyStatuses (bool	newStatus);

} // namespace DontShowAgainDialogUtils
} // namespace UD


#endif // GS_UD_DONTSHOWAGAINDIALOGEXTERNALREGISTRYKEYSTORE_HPP
