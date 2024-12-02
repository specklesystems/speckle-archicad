#ifndef VECTORIMAGE_TYPEDEFS_HPP
#define VECTORIMAGE_TYPEDEFS_HPP

#include "GSGuid.hpp"
#include "Typed.hpp"
#include "UniString.hpp"
#include "XMLChannel.hpp"


namespace PVI {

	using ProfileParameterId		= GS::Guid;
	using ProfileBuiltInParameterId	= GS::Guid;

	using ProfileParameterSetupId	= GS::Typed<GS::Guid, class ProfileParameterSetupIdTag>;

	bool		EnableComparison (ProfileParameterSetupId);
	ULong		EnableGenerateHashValue (ProfileParameterSetupId);
	GSErrCode	EnableReadWrite (ProfileParameterSetupId);

	using ProfileAnchorId			= GS::Typed<GS::Guid, class ProfileAnchorIdTag>;

	bool		EnableComparison (ProfileAnchorId);
	ULong		EnableGenerateHashValue (ProfileAnchorId);
	GSErrCode	EnableReadWrite (ProfileAnchorId);

	using ProfileDimControlToolId	= GS::Typed<GS::Guid, class ProfileDimControlToolIdTag>;

	bool		EnableComparison (ProfileDimControlToolId);
	ULong		EnableGenerateHashValue (ProfileDimControlToolId);
	GSErrCode	EnableReadWrite (ProfileDimControlToolId);
}


#endif
