#ifndef GS_UD_DONTSHOWAGAINDIALOG_HPP
#define GS_UD_DONTSHOWAGAINDIALOG_HPP

#include "DGDialog.hpp"
#include "UDDefinitions.hpp"


namespace UD {

namespace DontShowAgainDialogUtils {

UD_DLL_EXPORT bool	GetDontShowAgainStatus (const GS::UniString&	registryValueName);

UD_DLL_EXPORT void	SetDontShowAgainStatus (const GS::UniString&	registryValueName,
											bool					newStatus);

UD_DLL_EXPORT void	InvokeDontShowAgainDialog (GSResModule					resModule,
											   short						dialogResId,
											   const GS::UniString&			registryValueName, 
											   GSResModule					dialIconResModule = InvalidResModule);

UD_DLL_EXPORT bool	InvokeDontShowAgainDialogWithCancelButton (GSResModule			resModule,
															   short				dialogResId,
															   const GS::UniString& registryValueName,
															   GSResModule			dialIconResModule = InvalidResModule);


} // namespace DontShowAgainDialogUtils

} // namespace UD


#endif // GS_UD_DONTSHOWAGAINDIALOG_HPP
