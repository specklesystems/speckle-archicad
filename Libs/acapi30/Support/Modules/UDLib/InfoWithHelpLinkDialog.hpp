#ifndef	UD_INFOWITHHELPLINKDIALOG_HPP
#define	UD_INFOWITHHELPLINKDIALOG_HPP

// from DG
#include "UDDefinitions.hpp"

namespace UD {

UD_DLL_EXPORT void InvokeInfoWithHelpLinkDialog (GSResModule			dialResModule,
												 short					resId,
												 GSResModule			dialIconResModule,
												 short					parentTabPageId,
												 short					parentButtonId,
												 const GS::UniString&	helpStaticText = GS::EmptyUniString);

} // namespace UD


#endif
