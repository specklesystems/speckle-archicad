#ifndef DONTSHOWAGAINDIALOG_HPP
#define DONTSHOWAGAINDIALOG_HPP

#include "DGDialog.hpp"
#include "UDDefinitions.hpp"


namespace UD {

namespace DontShowAgainDialogUtils {


UD_DLL_EXPORT bool	GetDontShowAgainStatus (const GS::UniString&	registryValueName);


UD_DLL_EXPORT void	SetDontShowAgainStatus (const GS::UniString&	registryValueName,
											bool					newStatus);


UD_DLL_EXPORT void	InvokeDontShowAgainDialog (GSResModule			resModule,
											   short				dialogResId,
											   const GS::UniString&	registryValueName);


} // namespace DontShowAgainDialogUtils

} // namespace UD


#endif // DONTSHOWAGAINDIALOG_HPP
